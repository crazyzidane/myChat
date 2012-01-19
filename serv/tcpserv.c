/********************************************************************/
/* Copyright (C) SSE-USTC, 2011                                     */
/*                                                                  */
/*  FILE NAME             :  tcpserv.c                              */
/*  PRINCIPAL AUTHOR      :  Runzhen Wang                           */
/*  SUBSYSTEM NAME        :                                         */
/*  MODULE NAME           :                                         */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2011/12/10                             */
/*  DESCRIPTION           :                                         */
/********************************************************************/

#include"tcpserv.h"

pthread_mutex_t  mutex;

client_info* head=NULL;
client_info* tmp=NULL;

int          count=0;

static void serv_msg(void * fd)
{
    int          sockfd = *(int*)fd;
    ssize_t      n;
    tChatSysMsg  msg;
    tChatSysMsg  notice;
    char         buf[MAX_NUM_STR];

    //notice other client who is exiting
    notice.Version=1;
    notice.MsgType=MSG_CHAT;
    notice.MsgLen=0;

    while((n=Read(sockfd,buf,MAX_NUM_STR))>0)
    {
        ChatSysPduParser(buf,&msg);
        //printMsg(&msg);
        if(msg.MsgType==MSG_LOGIN)
        {
            //mutex
            pthread_mutex_lock(&mutex);
            count++;
            //add a client infomation
            tmp=(client_info*)malloc(sizeof(client_info));
            tmp->fd=sockfd;
            tmp->flag=VALID;
            tmp->next=head;
            head=tmp;
            pthread_mutex_unlock(&mutex);

            msg.MsgType=MSG_ACK;
            ChatSysPduFormat(buf,&msg);
            Write(sockfd,buf,sizeof(tChatSysPdu));
            printf("System:[%s] login.  Welcome!  [%d] people online.\n",msg.Name,count);
        }
        else if(msg.MsgType==MSG_CHAT)
        {
        	pthread_mutex_lock(&mutex);
            printf("[%s]:%s\n",msg.Name,msg.Msg);
            msg.Msg[strlen(msg.Msg)-1]='\0';
            for(tmp=head;tmp!=NULL&&tmp->flag!=INVALID;tmp=tmp->next)
            {
                if(tmp->fd!=sockfd)
                {
                    Write(tmp->fd,buf,sizeof(tChatSysPdu));
                }
            }
            pthread_mutex_unlock(&mutex);
        }
        else if(msg.MsgType==MSG_LOGOUT)
        {
            pthread_mutex_lock(&mutex);
            count--;
            for(tmp=head; tmp!=NULL; tmp=tmp->next)
            {
                if(tmp->fd==sockfd)
                {
                    tmp->flag=INVALID;
                    printf("System:[%s] logout.  Goodbye!  [%d] people online.\n",msg.Name,count);
                }
                else
                {
                    strcpy(notice.Name,"System");
                    strcpy(notice.Msg,msg.Name);
                    strcat(notice.Msg," log out,Goodbye!");
                    ChatSysPduFormat(buf,&notice);
                    Write(tmp->fd,buf,sizeof(tChatSysPdu));
                }
            }
            pthread_mutex_unlock(&mutex);

        }
    }

}


int main(void)
{
    int       listenfd,connfd;
    socklen_t clilen;
    pthread_t pid;
    struct sockaddr_in cliaddr,servaddr;

    listenfd=Socket(AF_INET,SOCK_STREAM,0);

    /*initialize the server address*/
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERV_PORT);
    /*end*/

    Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    Listen(listenfd,20);

    pthread_mutex_init(&mutex,NULL);
    while(1)
    {
        clilen=sizeof(cliaddr);
        connfd=Accept(listenfd,(SA*)&cliaddr,&clilen);

        //create a thread
        pthread_create(&pid, NULL,(void*)serv_msg, (void*)&connfd);

    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
