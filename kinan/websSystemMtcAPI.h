/*****************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:	km1.0
 *	Filename	:	websSystemMAPI.h 
 *	Description	:	WebServer API Header
 *	Creator		:	zeed
 *	Date		:	2017-7-21
 *****************************************************/

#ifndef		__KM1_KINAN_WEBSSYSTEMTCMAPI_H
#define		__KM1_KINAN_WEBSSYSTEMTCMAPI_H

#include    "websLoginAPI.h"        //user login
#include    "sometest.h"

#if 0

#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <math.h>

#define ICMP_DATA_LEN 56		//ICMP默认数据长度
#define ICMP_HEAD_LEN 8			//ICMP默认头部长度
#define ICMP_LEN  (ICMP_DATA_LEN + ICMP_HEAD_LEN)
#define SEND_BUFFER_SIZE 128		//发送缓冲区大小
#define RECV_BUFFER_SIZE 128		//接收缓冲区大小
#define SEND_NUM 3 			//发送报文数
#define MAX_WAIT_TIME 3

extern struct hostent *pHost;
extern int sock_icmp;
extern int nSend;
extern char *IP;

static int Call(char *pingIP);

//发送ICMP报文
void SendPacket(int sock_icmp, struct sockaddr_in *dest_addr, int nSend);
//接收ICMP报文
int RecvePacket(int sock_icmp, struct sockaddr_in *dest_addr);
//计算校验和
u_int16_t Compute_cksum(struct icmp *pIcmp);
//设置ICMP报文
void SetICMP(u_int16_t seq);
//剥去报头
int unpack(struct timeval *RecvTime);
//计算往返时间
double GetRtt(struct timeval *RecvTime, struct timeval *SendTime);
//统计信息
void Statistics(int signo);
#endif


extern void formSystemCtrl (webs_t wp, char_t *path, char_t *query);
extern void formBackup (webs_t wp, char_t *path, char_t *query);
extern void formBackupInfo (webs_t wp, char_t *path, char_t *query);
extern void formPingHost  (webs_t wp, char_t *path, char_t *query);
//extern void formPingHost2 (webs_t wp, char_t *path, char_t *query);
extern void formPingHostv3 (webs_t wp, char_t *path, char_t *query);

extern void formRemoteUpgrade (webs_t wp, char_t *path, char_t *query);

#endif		//__KM1_KINAN_WEBSSYSTEMTCMAPI_H