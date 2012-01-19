/********************************************************************/
/* Copyright (C) SSE-USTC, 2011                                     */
/*                                                                  */
/*  FILE NAME             :  tcpcli.c                               */
/*  PRINCIPAL AUTHOR      :  Runzhen Wang                           */
/*  SUBSYSTEM NAME        :                                         */
/*  MODULE NAME           :                                         */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2011/12/10                             */
/*  DESCRIPTION           :                                         */
/********************************************************************/


#include"../lab4.h"
#include"../protocol/msg.h"

char name[NAME_LEN];

static int login(int sockfd)
{
    char         login_msg[MAX_NUM_STR];
    tChatSysMsg  msg;
    msg.Version=1;
    msg.MsgType=MSG_LOGIN;
    msg.MsgLen=0;
    printf("Login name:");
    fflush(stdout);
    Fgets(msg.Name,NAME_LEN,stdin);
    msg.Name[strlen(msg.Name)-1]='\0';

    strcpy(name,msg.Name);

    ChatSysPduFormat(login_msg,&msg);
    Write(sockfd,login_msg,sizeof(tChatSysPdu));
    Read(sockfd,login_msg,MAX_NUM_STR);
    ChatSysPduParser(login_msg,&msg);
    //printMsg(&msg);
    if(msg.MsgType==MSG_ACK)
    {
        return 1;
    }
    else
        return 0;
}

static void logout(int sockfd)
{
    char         logout_msg[MAX_NUM_STR];
    tChatSysMsg  msg;
    msg.Version=1;
    msg.MsgType=MSG_LOGOUT;
    msg.MsgLen=0;
    strcpy(msg.Name,name);
    ChatSysPduFormat(logout_msg,&msg);
    Write(sockfd,logout_msg,sizeof(tChatSysPdu));
}

static void chat(int sockfd)
{
    char         chat_msg[MAX_NUM_STR];
    tChatSysMsg  msg;
    msg.Version=1;
    msg.MsgType=MSG_CHAT;
    strcpy(msg.Name,name);
    msg.MsgLen=0;
    while(1)
    {
        printf("[%s]:\n",name);
        Fgets(msg.Msg,MAX_MSG_LEN,stdin);
        msg.Msg[strlen(msg.Msg)-1]='\0';
        if((strcmp(msg.Msg,"exit")==0))
        {
            printf("%s logout\n",msg.Name);
            logout(sockfd);
            break;
        }
        ChatSysPduFormat(chat_msg,&msg);
        Write(sockfd,chat_msg,sizeof(tChatSysPdu));
        //printf("in chat,i have written\n");
    }
}

static void cli_recv(int sockfd)
{
    ssize_t      n;
    tChatSysMsg  msg;
    char         buf[MAX_NUM_STR];
    //printf("in cli_recv\n");
    while(1)
    {
        //printf("in while\n");
        if((n=Read(sockfd,buf,MAX_NUM_STR))>0)
        {
            ChatSysPduParser(buf,&msg);
            printf("[%s]:%s\n",msg.Name,msg.Msg);
        }
        else
        {
            printf("error in cli_recv\n");
            exit(1);
        }

    }
}

static void cli_msg(int sockfd)
{
    pthread_t pid;
    if(login(sockfd)==1)
    {
       // printf("login ok\n");
        pthread_create(&pid,NULL,(void*)cli_recv,(void*)sockfd);
       // printf("after pthread,before chat\n");
        chat(sockfd);
    }
    else
    {
        printf("login error!\n");
        exit(1);
    }
    pthread_cancel(pid);
}



int main(int argc,char ** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc!=2)
    {
        printf("Usage: ./cli 127.0.0.1");
        exit(0);
    }

    sockfd=Socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

    Connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
    cli_msg(sockfd);
    return 0;
}

