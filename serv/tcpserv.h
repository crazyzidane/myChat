#ifndef  _TCPSERV_H_
#define  _TCPSERV_H_

#include"../lab4.h"
#include"../protocol/msg.h"


#define       VALID      1
#define       INVALID    0

typedef struct c_info
{
    int             fd;
    int             flag;
    struct  c_info* next;
}client_info;


#endif
