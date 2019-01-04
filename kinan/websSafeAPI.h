/*****************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:   km1.0
 *	Filename	:	websSafeAPI.h 
 *	Description	:	API for safe manage
 *	Creator		:	zeed
 *	Date		:	2017-8-4
 *****************************************************/

#ifndef		__KM1_KINAN_WEBSSAFEAPI_H
#define		__KM1_KINAN_WEBSSAFEAPI_H

#include  "websLoginAPI.h"
#include  "sometest.h"

//include "../cfg.h"
extern void formSafeSetting(webs_t wp, char_t *path, char_t *query);
extern void formSafeSetInfo(webs_t wp, char_t *path, char_t *query);
extern void formConfirmSetInfo(webs_t wp, char_t *path, char_t *query);
extern void formConfirmSet(webs_t wp, char_t *path, char_t *query);

extern void formAuditLog (webs_t wp, char_t *path, char_t *query);
#endif		//__KM1_KINAN_WEBSSAFEAPI_H

