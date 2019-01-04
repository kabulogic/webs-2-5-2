/***************************************************************************************
* file name:    session.h
* description:  this file is the header of static lib session.a, 
*               it defines the function protypes which are used to exchange info in
*               processes in a unix like system, the communication betweem two processes 
*               is called a session, and one of these two processes is server and the another 
*               is client. the server is able to talk to more than one client, while the client
*               is just able to only one server, communication in clients is impossible.
* creator:      Alex
* date:         2017-07-10
***************************************************************************************/
#ifndef _SESSION_H
#define _SESSION_H

#ifdef _cplusplus
extern "c" {
#endif

#include "./inf_public.h"

#define	DOMAIN_SER	0
#define	DOMAIN_CLI	1

/* channge this accroding your application, it must be unique in the system
 * NOTE: the length of name must be less than 13 */
#define SESSION_NAME	INF-DF1000

#ifdef _SESSION_C
#define SESSION_API
#else
#define SESSION_API    extern
#endif


#if 0
#ifndef _INF_TYPES
#define _INF_TYPES
typedef int            fd_t;
typedef unsigned char  u_8;
typedef char           s_8;
typedef unsigned short u_16;
typedef short          s_16;
typedef unsigned int   u_32;
typedef int            s_32;
#endif
#endif

/* communication header */
typedef struct PeerHeader {
    s_8 cWho[20]; 	//用户名
    s_8 IP[16];		//用户IP
    u_8 cAction;    //会话动作
    s_8 cStatus;	//会话状态
    u_16 sLen;		//会话头后的数据长度
}PeerHdr_t;
typedef struct MsgHeader {
    u_8 cType;		//会话操作类型，如获取设备基本信息等
    u_8 cNum;		//保留
}MsgHdr_t;


/*
  communicate PDU format:  PeerHdr_t + MsgHdr_t + Msg 
*/

/* define the max PDU length according your need */
#define MAX_PDU_LEN    2048
#define MAX_MSG_LEN    ( MAX_PDU_LEN - sizeof(PeerHdr_t) - sizeof(MsgHdr_t) )

/* used to open a session, called by both server and client which is indecated by cType.
   NOTE: server should called this API befor client */
SESSION_API fd_t INF_OpenSession_API( u_8 cType );
/* used to close a session */
SESSION_API void INF_CloseSession_API( fd_t fd, u_8 cType );
/* used to accept a client, just called by the server process */
SESSION_API fd_t INF_AcceptPeer_API( fd_t fd );
/* used to end a session with a client, just called by the server process */
SESSION_API void INF_ClosePeer_API( fd_t fd );
/* used to send information to other */
SESSION_API s_32 INF_SpeakToPeer_API( fd_t fd, void *pdu, u_32 len, struct timeval *ptimeout );
/* used to recv information from other */
SESSION_API s_32 INF_ListenToPeer_API( fd_t fd, void *buf, u_32 len, struct timeval *ptimeout );

#ifdef _cplusplus
}
#endif

#endif


