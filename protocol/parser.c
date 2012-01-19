
/********************************************************************/
/* Copyright (C) SSE-USTC, 2010                                     */
/*                                                                  */
/*  FILE NAME             :  parser.c                               */
/*  PRINCIPAL AUTHOR      :  Runzhen Wang                           */
/*  SUBSYSTEM NAME        :  ChatSys                                */
/*  MODULE NAME           :  ChatSys                                */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2010/11/26                             */
/*  DESCRIPTION           :  implement of ChatSys PDU parser        */
/********************************************************************/


#include"msg.h"
#include<stdio.h>
#include<string.h>
/*
 * Parse the ChatSys PDU to ChatSys Msg
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 */
int ChatSysPduParser(char * pdu,tChatSysMsg *msg)
{
    tChatSysPdu *p = (tChatSysPdu *)pdu;
    msg->Version = p->Version;
    msg->MsgType = p->MsgType;
    strcpy(msg->Name,p->Name);
    msg->MsgLen=p->MsgLen;
    strcpy(msg->Msg,p->Msg);
    return 0;

}
/*
 * Format the ChatSys Msg to ChatSys PDU
 * input	: char * pdu , Memory allocate outside
 * output	: tChatSysMsg *Msg , Memory allocate outside
 * return	: SUCCESS(0)/FAILURE(-1)
 *
 */
int ChatSysPduFormat(char * pdu,tChatSysMsg *msg)
{
    tChatSysPdu *p = (tChatSysPdu *)pdu;
    p->MsgType = msg->MsgType;
    p->Version = msg->Version;
    strcpy(p->Name,msg->Name);
    p->MsgLen=msg->MsgLen;
    strcpy(p->Msg,msg->Msg);
    return 0;
}

void printMsg(tChatSysMsg *msg)
{
//    printf("tChatSysMsg\n");
//    printf("Version=%d\n",msg->Version);
//    printf("MsgType=%d\n",msg->MsgType);
//    printf("SerialNumber=%d\n",msg->SerialNumber);
//    printf("MsgLen=%d\n",msg->MsgLen);
    printf("Msg=%s\n",msg->Msg);
}
