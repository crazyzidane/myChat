/********************************************************************/
/* Copyright (C) SSE-USTC, 2010                                     */
/*                                                                  */
/*  FILE NAME             :  msg.h                                  */
/*  PRINCIPAL AUTHOR      :  Runzhen Wang                           */
/*  SUBSYSTEM NAME        :                                         */
/*  MODULE NAME           :                                         */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  Linux                                  */
/*  DATE OF FIRST RELEASE :  2011/12/16                             */
/*  DESCRIPTION           :                                         */
/********************************************************************/


#ifndef   _MSG_H_
#define   _MSG_H_

#define    MAX_NUM_STR     1024
#define    MAX_MSG_LEN     512
#define    NAME_LEN        20

#define    MSG_ERROR           0
#define    MSG_ACK             1
#define    MSG_LOGIN           2
#define    MSG_CHAT            3
#define    MSG_LOGOUT          4

typedef struct ChatSysPdu
{
    char    Version:4;
    char    MsgType:4;
    char    Name[NAME_LEN];
    int     MsgLen;
    char    Msg[MAX_MSG_LEN];
} tChatSysPdu;


typedef struct ChatSysMsg
{
    int     Version;
    int     MsgType;
    char    Name[NAME_LEN];
    int     MsgLen;
    char    Msg[MAX_MSG_LEN];
} tChatSysMsg;



int ChatSysPduParser(char * pdu,tChatSysMsg *Msg);

int ChatSysPduFormat(char * pdu,tChatSysMsg *Msg);

void printMsg(tChatSysMsg *Msg);

#endif
