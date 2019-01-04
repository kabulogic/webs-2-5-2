/*****************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:   km1.0
 *	Filename	:	websLoginAPI.h 
 *	Description	:	API for Login
 *	Creator		:	zeed
 *	Date		:	2017-08-02
 *****************************************************/

#ifndef		__KM1_KINAN_WEBSLOGINAPI_H
#define		__KM1_KINAN_WEBSLOGINAPI_H

/********************* Includes ***********************/

#include	"websMacro.h"       
#include    "../wsIntrn.h"
#include	"websSession.h"  //管理sessionid
#include    "../kmain/kingAPI.h"  //主控程序

/*********************** Define ***********************/

/*********************** Prototypes *********************/ 
extern void Quit(char_t *username, char_t *ip);
extern void formLogin(webs_t wp, char_t *path, char_t *query);
extern int  authenLogin(webs_t wp, char *userLogin, int size, int *flag);
extern void formQuit(webs_t wp, char_t *path, char_t *query);

extern void sendRspHeadArray (webs_t wp, char_t *rspStatus, char_t *rspMsg);
extern void sendRspFooterArray (webs_t wp);

extern void sendRspHeadObj (webs_t wp, char_t *rspStatus, char_t *rspMsg);
extern void sendRspFooterObj (webs_t wp);

extern void goformHead(webs_t wp);

#endif		//__KM1_KINAN_WEBSLOGINAPI_H