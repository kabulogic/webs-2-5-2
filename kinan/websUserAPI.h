/*****************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:   km1.0
 *	Filename	:	websUserAPI.h 
 *	Description	:	API for user manage
 *	Creator		:	zeed
 *	Date		:	2017-7-28
 *****************************************************/

#ifndef		__WEBSUSERAPI_H
#define		__WEBSUSERAPI_H

/********************* Includes ***********************/

#include  "../um.h"
#include  "websLoginAPI.h"

/********************* Prototypes *********************/ 

extern void formAddUserGroup (webs_t wp, char_t *path, char_t *query);
extern void formAddUser (webs_t wp, char_t *path, char_t *query);
extern void formAddUserInfo (webs_t wp, char_t *path, char_t *query);

extern void formDelUser (webs_t wp, char_t *path, char_t *query);
extern void formDelUserGroup (webs_t wp, char_t *path, char_t *query);

extern void formChaPasswd (webs_t wp, char_t *path, char_t *query);

extern void formEditUser (webs_t wp, char_t *path, char_t *query);
extern void formEditUserInfo (webs_t wp, char_t *path, char_t *query);
extern void formEditUserGroup (webs_t wp, char_t *path, char_t *query);
extern void formEditUserGroupInfo (webs_t wp, char_t *path, char_t *query);

extern void formUserGroupList (webs_t wp, char_t *path, char_t *query);
extern void formUserList (webs_t wp, char_t *path, char_t *query);

extern void formSearchUser (webs_t wp, char_t *path, char_t *query);
extern void formSearchUserGroup (webs_t wp, char_t *path, char_t *query);

#endif		//__WEBSUSERAPI_H
