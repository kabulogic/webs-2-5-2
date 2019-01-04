/*****************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:	km1.0
 *	Filename	:	websSession.h 
 *	Description	:	Create the session for webservers
 *	Creator		:	zeed
 *	Date		:	2017-8-14
 *****************************************************/

#ifndef		__KM1_KINAN_WEBSSESSION_H
#define		__KM1_KINAN_WEBSSESSION_H

/********************* Includes ***********************/

#include <time.h>
#include "../des/tables.h"

/*********************** Define ***********************/

#define  MAX_SESSIONID_NUM     512 //最大链表节点个数
#define  ORG_SESSIONID_LEN     32  //源sessionid长度
#define  C_SESSSIONID_LEN      64  //sessionid长度
#define  MAX_SESSION_FILE_LEN  32
#define  STR_TIME              10  //time_t长度
#define  DEFAUTL_BEHIND_TIME   3600ul //默认过期时间
#define  USRN_LEN              20  //用户名长度
#define  SESSIONID_SAVE_PATH   "../www/km01/cgi-bin/sessions.log"
#define  SESSIONID_SAVE_FILE   "sessions.log"

typedef struct logoutTime {
    unsigned char  enable;
	time_t  times;
}logoutTime_t;

typedef struct sessionNode{
	char    username[USRN_LEN+1];
	time_t  sessiontime;
	char    sessionid[C_SESSSIONID_LEN+1];
	struct sessionNode *snpNext;
}sessionNode;

typedef struct {
	sessionNode *sessionHead;
	int count;	
}sessionList; 

typedef sessionList *session_t;

/*********************** Prototypes *********************/
// 获取logout_s选项
logoutTime_t* get_logout_s ();
// 获取sessions链表
extern session_t get_sessions ();
// 初始化sessions链表
extern int sessionOpen ();
// 关闭sessions链表
extern int sessionClose ();
// 创建一个新节点的功能
extern sessionNode* createSession(char *username);
// 判断链表是否为空
extern int isEmpty(session_t spl);
// 判断链表是否为满
extern int isFull(session_t spl);
// 从头添加session节点
extern void pushHeadSession(session_t spl, char *username);
// 从尾添加session节点
extern void pushTailSession(session_t spl, char *username);
// 计算链表中元素的个数
extern int sizeSession (session_t spl);
// 遍历链表中的所有元素
extern void travelDelSession(session_t spl);
// 向指定的下标位置插入指定的节点 下标从0开始
extern void insertSession(session_t spl, int pos, char *username);
// 查找指定元素值所在的链表的下标
extern int findSession(session_t spl, char *username);
// 查找指定元素值所在的链表的下标
extern int findSessionByid(session_t spl, char *sessionid);
// 修改指定下表的元素值
extern int modifySession(session_t spl, int pos, char *username);
// 读取指定下标的元素值
extern sessionNode *readSession (session_t spl, int pos);
// 删除指定下标的元素
extern int delSession (session_t spl, int pos);
//清空链表中所有的节点
extern void clearSession(session_t spl);

// 产生sessionid
extern time_t genSessionid(char *username, char *sessionid, int size);

// 解密
extern void decString (const char *secrText, char *clearText, int size);
// 加密
extern void encString (const char *clearText, char *secrText, int size);

// 分解字符串
extern int parseKeyValue (char *buf, char **key, char **value, char *d);
// 提取字符串
extern int extractKeyValue2(char *buf, char *key, char *d, char **value);

// 保存至文件
extern int sessionSave(session_t slp, logoutTime_t *logoutPtr, char *filename);
// 从文件中加载到链表
extern sessionNode* sessionLoad(logoutTime_t* logouts, int *count, char *filename);

#endif		//__KM1_KINAN_WEBSSESSION_H

