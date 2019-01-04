/*************************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.	
 *	Version		:	km1.0
 *	Filename	:	websAPI.c
 *	Description	:	provides API for webservers
 *	Creator		:	zeed
 *	Date		:	2017-7-21
 *	History		:	
 *	<author>    <time>    <version >    <desc>
 *	zeed	    17/07/31  1.0			build this moudle  
 *
 *************************************************************/

/************************ Descriptions ***********************/

/*
 *	This module provides API functions for kinan webservers
 */

/************************ Includes ***************************/

#include "sometest.h"    //header of webserver api 

/*************************************************************/
/*
 *  Get user privilege from kimain 
 */

void getPrivilege(UserCfg_t *username)
{
    username->cType = 2;
/*	username->privilege->bNetPrev = 1;
	username->privilege->bNetPlay = 0;
	username->privilege->bLocalPlay = 0;
	username->privilege->bLogView = 1;
	username->privilege->bPTZ = 0;
	*/
	memcpy(username, 5, sizeof(UserCfg_t));
}

/*************************************************************/
/*
 *  Get port informations from kimain 
 */
void getBackup(BackupCfg_t * backup)
{
	backup->cMethod = 1;
	backup->backTime[0] = 630;
	backup->backTime[1] = 690;
	backup->backTime[2] = 720;
}


/*************************************************************/
/*
 *  Get port informations from kimain 
 */
int getPortInfo (PortAccessStatus_t *portInfo)
{
	int i = 0;
	char str[8] = {};
	for(i=0; i<64; i++)
	{
		portInfo[i].sNum = i+1;
		sprintf(str, "%s%d", "port", i+1);
		strcpy(portInfo[i].cName, str);
		portInfo[i].AccessType = ACCESS_NETWORK;
		portInfo[i].cStatus = '1';
		portInfo[i].availability = '1';
	}
	return 0;
}
/*************************************************************/
/*
 *  Get system informations from kimain
 */
int  getKvmSystemInfo (KvmSystemInfo_t *systemInfo)
{
	struct tm *gt;
	time_t it;
	it = time(NULL);
	gt = localtime(&it);
	memcpy((void*)&(systemInfo->curLogin.t), gt, sizeof(struct tm));
	strcpy(systemInfo->loginUser, "admin");
//    ctime(&systemInfo.curLogin.t);	        
	strcpy(systemInfo->curLogin.sIp,"192.168.2.118");
	strcpy(systemInfo->cKvmName, "KvM100");
	strcpy(systemInfo->cKvmIp, "192.168.2.110");
	strcpy(systemInfo->cFirmware, "R2.2.2");
	strcpy(systemInfo->cKvmModel, "SHALDOM");
	strcpy(systemInfo->cLogServerIp, "127.0.0.1");
	systemInfo->cPowerIn = 0;
	return 0;
}
/*************************************************************/
/*
 *  Get system time 
 */
void getSystemTime (timeCtr_t *datet)
{
	datet->t = time(NULL);
	datet->bNet = 0;
}
/*************************************************************/
/*
 *  Get ntp server 
 */
void getNTPserver (CfgNTP_t *ntpt)
{
	ntpt->bNTP = 1;
	strncpy(ntpt->IP, "192.168.2.110", sizeof(ntpt->IP));
}

/*************************************************************/
/*
 *  Get port configure information 
 */

void getPortCfgInfo (PortAccessCfg_t *portCfgInfo)
{
	int i = 0;
	char str[8] = {};
	for(i=0; i<64; i++)
	{
		portCfgInfo[i].sNum = i+1;
		sprintf(str, "%s%d", "port", i+1);
		strncpy(portCfgInfo[i].cPortName, str, 
				sizeof(portCfgInfo[i].cPortName));
		portCfgInfo[i].cPortType = 0x01;
		portCfgInfo[i].cResolution[0] = 1920;
		portCfgInfo[i].cResolution[1] = 1080;
		portCfgInfo[i].cRefresh = 60;
	}
}
/*************************************************************/
/*
 *  从secureset.info 获取安全设置信息 
 */

void getSecureInfo (SecureCfg_t *scrInfo)
{
	int fd, res;
	fd = open("secureset.info", O_RDONLY);
	if (fd < 0) {
        perror("getSecureInfo::open failed");
		return;
	}
    res = read(fd, scrInfo, sizeof(SecureCfg_t));
	if (res != sizeof(SecureCfg_t)) {
        printf("getSecureInfo::read failed\n");
		return ;
	}
	close(fd);
}

/*************************************************************/
/*
 *  安全设置信息存于 secureset.info 
 */

void saveSecureInfo(SecureCfg_t *srcInfo)
{
     int fd, res;
	 fd = open("tempsecure.info", O_WRONLY|O_CREAT, 0666);
	 if (fd < 0) {
         perror("saveSecureInfo::open failed!");
		 return;
	 }
	 res = write(fd, srcInfo, sizeof(SecureCfg_t));
	 if (res != sizeof(SecureCfg_t)) {
         perror("saveSecureInfo::write failed!");
		 return;
	 }
	 unlink("secureset.info");
	 rename("tempsecure.info", "secureset.info");
	 close(fd);
}


/*************************************************************/
/*
 *  Get port configure information 
 */

void getConfirmInfo(VerifyCft_t *cfInfo)
{
	cfInfo->verify = VERIFY_WAY_LOCAL;

	strncpy(cfInfo->ldap.cLdapServer, "192.168.2.118", 
			sizeof(cfInfo->ldap.cLdapServer));
	cfInfo->ldap.cPort = 1234;
	cfInfo->ldap.cLadpServerType = 1;
	strncpy(cfInfo->ldap.cScanDNS, "192.168.2.114",
			sizeof(cfInfo->ldap.cScanDNS));
	strncpy(cfInfo->ldap.cTestUserName, "testzeed", 
			sizeof(cfInfo->ldap.cTestUserName));
	strncpy(cfInfo->ldap.cTestPsswd, "1683", 
			sizeof(cfInfo->ldap.cTestPsswd));

	strncpy(cfInfo->radius.cServer, "192.168.2.222",
			sizeof(cfInfo->radius.cServer));
	strncpy(cfInfo->radius.cShareCode, "0122",
			sizeof(cfInfo->radius.cShareCode));
	cfInfo->radius.lPort = 4321;
	cfInfo->radius.sTimeOut = 10;
	cfInfo->radius.sRetry = 3;
}

/*************************************************************/
/*
 *  验证设置信息存于confirmset.info 
 */

void saveConfirmInfo(VerifyCft_t *cfInfo)
{
     int fd, res;
	 fd = open("tempconfirm.info", O_WRONLY|O_CREAT, 0666);
	 if (fd < 0) {
         perror("saveConfirmInfo::open failed!");
		 return;
	 }
	 res = write(fd, cfInfo, sizeof(VerifyCft_t));
	 if (res != sizeof(VerifyCft_t)) {
         perror("saveConfirmInfo::write failed!");
		 return;
	 }
	 unlink("confirmset.info");
	 rename("tempconfirm.info", "confirmset.info");
	 close(fd);
}

/*************************************************************/
/*
 *  Get net work information 
 */
#if 1
void getNetWorkInfo (eth_t *ethInfo)
{
	strncpy(ethInfo[0].MAC, "11:1c:11:1e:1b:af", 
			sizeof(ethInfo[0].MAC));
	strncpy(ethInfo[0].IP, "192.168.2.111",
			sizeof(ethInfo[0].IP));
	strncpy(ethInfo[0].Mask, "255.255.255.0", 
			sizeof(ethInfo[0].Mask));
	strncpy(ethInfo[0].Gateway, "192.168.2.1",
			sizeof(ethInfo[0].Gateway));

	strncpy(ethInfo[1].MAC, "22:2c:22:2e:2b:bf", 
			sizeof(ethInfo[1].MAC));
	strncpy(ethInfo[1].IP, "192.168.2.222",
			sizeof(ethInfo[1].IP));
	strncpy(ethInfo[1].Mask, "255.255.255.0", 
			sizeof(ethInfo[1].Mask));
	strncpy(ethInfo[1].Gateway, "192.168.2.1",
			sizeof(ethInfo[1].Gateway));
}
#endif
void getLogSearch(logSearch_t *logS)
{
	strncpy(logS->cPath,"/home/zeed/test/log", sizeof(logS->cPath));
}





