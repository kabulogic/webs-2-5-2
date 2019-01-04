/*****************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:   km1.0
 *	Filename	:	websEquipAPI.h 
 *	Description	:	API for setting equipment 
 *	Creator		:	zeed
 *	Date		:	2017-7-28
 *****************************************************/

#ifndef		__KM1_KINAN_WEBSEQUIPAPI_H
#define		__KM1_KINAN_WEBSEQUIPAPI_H

#include	"../wsIntrn.h"
#include    "websLoginAPI.h"
#include	"sometest.h"

extern void formNetSetting (webs_t wp, char_t* path, char_t* query);
extern void formNetDefaultInfo (webs_t wp, char_t *path, char_t *query);
extern void formDateTimeInfo (webs_t wp, char_t *path, char_t *query);
extern void formDateTime (webs_t wp, char_t* path, char_t* query);

extern void formEventManage (webs_t wp, char_t *path, char_t *query);
extern void formModifyPort (webs_t wp, char_t *path, char_t *query);
extern void formConfigPortInfo (webs_t wp, char_t *path, char_t *query);

extern void formSetLocalPort (webs_t wp, char_t *path, char_t *query);
extern void formLocalPortInfo (webs_t wp, char_t *path, char_t *query);

extern void formDeviceConfig (webs_t wp, char_t *path, char_t *query);
#endif		//__KM1_KINAN_WEBSEQUIPAPI_H

