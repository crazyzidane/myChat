/********************************************************************/
/* Copyright (C) SSE-USTC, 2011                                     */
/*                                                                  */
/*  FILE NAME             :  warpsock.c                             */
/*  PRINCIPAL AUTHOR      :  Runzhen Wang                           */
/*  SUBSYSTEM NAME        :                                         */
/*  MODULE NAME           :                                         */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2011/12/10                             */
/*  DESCRIPTION           :                                         */
/********************************************************************/


#include"../lab4.h"

int Socket(int family,int type,int protocol){
    int  n;
    if((n=socket(family,type,protocol))<0){
        perror("socket");
        exit(1);
    }
    return n;
}

void Bind(int fd,const struct sockaddr *sa,socklen_t salen){
    if(bind(fd,sa,salen)<0){
        perror("bind");
        exit(1);
    }
}

void Connect(int fd,const struct sockaddr *sa,socklen_t salen){
    if(connect(fd,sa,salen)<0){
        perror("connect");
        exit(1);
    }
}

int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr){
    int n;
    if((n=accept(fd,sa,salenptr))<0){
        perror("accept");
        exit(1);
    }
    return n;
}

void Listen(int fd,int backlog){
    if(listen(fd,backlog)<0){
        perror("listen");
    }
}

void Write(int fd, void *ptr, int nbytes)
{
    if (write(fd, ptr, nbytes) != nbytes)
		perror("writen error");
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;
	if ( (n = read(fd, ptr, nbytes)) < 0)
		perror("readn error");
	return(n);
}

void Fgets(char *s, int n, FILE *stream)
{
    if(fgets(s,n,stream)==NULL)
    {
        perror("fgets");
    }

}

