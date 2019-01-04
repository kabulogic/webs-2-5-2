/*****************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:	km1.0
 *	Filename	:	websAPI.h 
 *	Description	:	WebServer API Header
 *	Creator		:	zeed
 *	Date		:	2017-7-21
 *****************************************************/

#ifndef		__KM1_KINAN_WEBSAPI_H
#define		__KM1_KINAN_WEBSAPI_H

#include	"websUserAPI.h"			//user manage
#include    "websLoginAPI.h"        //user login
#include    "websSafeAPI.h"         //safe manage
#include	"websEquipAPI.h"		//equipment manage
#include    "websSystemMtcAPI.h"    //system maintenance
#include    "sometest.h"
//#include    "kingAPI.h"      

extern int  websApiOpen ();
extern int  websApiClose ();
#endif		//__KM1_KINAN_WEBSAPI_H