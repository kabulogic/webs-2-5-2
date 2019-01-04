/*****************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:   km1.0
 *	Filename	:	kingAPI.h 
 *	Description	:	API for communicate with king proc
 *	Creator		:	zeed
 *	Date		:	2017-8-1
 *****************************************************/

#ifndef		__KINGAPI_H
#define		__KINGAPI_H

#include    "./session.h"
#include    "./inf_public.h"
#include	"./syscfg.h"
#include	"./sysctrl.h"
#include	"./sysstat.h"
#include	"./system.h"
#include	"./types.h"
#include	"./usercfg.h"
#include	"./macro.h"
#include    "./log.h"

/* peer action define */
#define PEER_GET    0x0  //获取系统参数
#define PEER_SET    0x1  //设置系统参数
#define PEER_CTR    0x2  //系统控制
#define PEER_STA    0x3  //系统状态
#define PEER_RET    0x4  //回复

/*初始化通用的会话头*/
extern void initPeerHdr (PeerHdr_t *pHdr, char *cWho, char *cIP,
		char cAction);
/*初始化通用的消息头*/
extern void initMsgHdr (MsgHdr_t *mHdr, char cType);

/*初始化与主控程序的会话*/
extern int Inf_initDataAccess_API(int SessionID, void *Pdu);
/*关闭与主控程序的会话*/
extern int Inf_closeDataAccess_API(int SessionID, void *Pdu);

/*与主控程序的交互*/
extern int INF_ClientTalkToKing_API(PeerHdr_t *PeerHdr, 
		MsgHdr_t *MsgHdr, void *buf, size_t size);

#endif		//__KINGAPI_H
