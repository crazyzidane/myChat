/********************************************************************/
/* Copyright (C) SSE-USTC, 2011                                     */
/*                                                                  */
/*  FILE NAME             :  lab4.h                                 */
/*  PRINCIPAL AUTHOR      :  Runzhen Wang                           */
/*  SUBSYSTEM NAME        :                                         */
/*  MODULE NAME           :                                         */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2011/12/16                             */
/*  DESCRIPTION           :                                         */
/********************************************************************/


#ifndef _LAB4_H_
#define _LAB4_H_


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <pthread.h>

#define    SA              struct sockaddr
#define    SERV_PORT       3459


int        Socket(int family,int type,int protocol);
int        Accept(int fd,struct sockaddr*sa,socklen_t *salenptr);
void       Bind(int fd,const struct sockaddr *sa,socklen_t salen);
void       Connect(int fd,const struct sockaddr *sa,socklen_t salen);
void       Listen(int fd,int backlog);
void       Write(int fd, void *ptr, int nbytes);
ssize_t    Read(int fd, void *ptr, size_t nbytes);
void       Fgets(char *s, int n, FILE *stream);

#endif
