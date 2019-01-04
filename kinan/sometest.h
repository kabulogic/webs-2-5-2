/*****************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.
 *  Version		:	km1.0
 *	Filename	:	sometest.h 
 *	Description	:	WebServer API Header
 *	Creator		:	zeed
 *	Date		:	2017-7-21
 *****************************************************/

#ifndef		__SOMETEST_H
#define		__SOMETEST_H

#include "../kmain/kingAPI.h"
extern void getPrivilege(UserCfg_t *username);
extern int getPortInfo(PortAccessStatus_t *portInfo);
extern int getKvmSystemInfo(KvmSystemInfo_t *systemInfo);
extern void getSystemTime(timeCtr_t *datet);
extern void getNTPserver (CfgNTP_t *ntpt);
extern void getPortCfgInfo(PortAccessCfg_t *portCfgInfo);
extern void getSecureInfo (SecureCfg_t *scrInfo);
extern void getConfirmInfo(VerifyCft_t *cfInfo);
extern void getNetWorkInfo(eth_t *ethInfo);
extern void getLogSearch (logSearch_t *logS);
extern void getBackup (BackupCfg_t *backup);

extern void saveSecureInfo(SecureCfg_t *srcInfo);
extern void saveConfirmInfo(VerifyCft_t *cfInfo);

#endif		//__SOMETEST_H
