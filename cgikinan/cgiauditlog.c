/****************************************************************
*  Copyright (c) 2017-2021,Kinan Tech. Co., Ltd.
*  Version     :    km1.0
*  Filename    :    cgiauditlog.c
*  Description :    auditlog
*  Creator     :    zeed
*  Date        :    2017-09-20
*  History     :
*  <author>    <time>    <version>    <desc>
*  zeed        17/09/20   1.0          build this moudle
*
******************************************************************/
#include "../kinan/websSession.h"
#include "cgic.h"
#include "authenBySessionid.h"
#include "../kmain/kingAPI.h"

/*********************Forward Declarations********************/

static s_8 *gLog_alm_Str[]   = { "警告",
                                 "motion alarm start",   "motion alarm stop",
                                 "obstruct alarm start", "obstruct alarm stop", 
                                 "alarm in",             "alarm out"          
                               };
static s_8 *gLog_exp_Str[]   = { "异常",
                                 "video lost",           "network broken",
                                 "network fail",         "illegal access",
                                 "hard disk full",       "hard disk error", 
                                 "illegal power off",    "ip confict"
                               };

static s_8 *gLog_cfg_Str[]   = { "配置",
                                 "配置录像",  "配置端口",
                                 "配置网络",  "配置用户",
                                 "配置硬盘",  "配置用户组"
                               };

static s_8 *gLog_viw_Str[]   = { "预览",
                                 "get config.",    "video preview",
                                 "video playback",       "get log"
                               };

static s_8 *gLog_ops_Str[]  = {  "操作",  "备份录像",  "备份配置",  "删除录像",  "删除日志",           
						         "系统升级", "恢复出厂默认", "格式化硬盘", "修改系统时间",   
                                 "启动系统", "重启系统", "关闭系统", "登录",  "登出"            	  };

static s_8 *gLog_rec_Str[]  = {  "录像",
                                 "timer record start",  "alarm record start",   
                                 "timer record stop",   "alarm record stop",     
                              };

int cgiMain(void)
{
	PeerHdr_t       pHdr_srchLog = {};
	MsgHdr_t        mHdr_srchLog = {};
	logSearch_t     srchLog = {};         //获取日志文件路径
	log_res_head_t  headLog = {};         //日志头
	log_t           infoLog = {};         //日志内容
	char            *timeHide = NULL;
	char            timeRange[11] = {};   //时间范围
	int             major, minor, fd_auditLog, res, i;
	struct tm       *timePtr;
	int             sendc;
	char            **arrayCookie, **arrayCookieStep;
	char            cookieValue[65];
    int             deleteflag = 0;
	
/*
 *  获取cookie值
 */
 	if (cgiCookies(&arrayCookie) != cgiFormSuccess) {
		fprintf(stderr, "cgiauditlog::could not get cookies\n");
		goto FAIL;
	}
	
	arrayCookieStep = arrayCookie;
	while(*arrayCookieStep){
		if(!strcmp(*arrayCookieStep, "CSESSIONID")){
			break;
		}
		arrayCookieStep++;
	}
	
	cgiCookieString(*arrayCookieStep, cookieValue, sizeof(cookieValue));
	fprintf(stderr, "cgiauditlog::cookieValue=%s\n", cookieValue);
	fprintf(stderr, "cgiauditlog::ipaddr=%s\n", getenv("REMOTE_ADDR"));
	cgiHeaderContentType("text/html");

	if(!authenBySessionid(cookieValue, pHdr_srchLog.cWho, sizeof(pHdr_srchLog.cWho), &deleteflag))
	{
#ifdef FINISH
		initPeerHdr(&pHdr_srchLog, NULL, getenv("REMOTE_ADDR"),
				PEER_CTR);

		//CTRL_LOG ???
		initMsgHdr(&mHdr_srchLog, CTRL_LOG);
#else
		;
/*
 *      如果没有传递参数则默认请求当天凌晨至当前时间的日志数据
 */
		if(cgiFormInteger("mainType", &major, -1) == cgiFormNotFound)
		{
			srchLog.t2 = time(NULL);     
			fprintf(stderr, "cgiauditlog::end_time=%ld\n", srchLog.t2);
			
			timePtr = localtime(&srchLog.t2);
			timePtr->tm_hour = 0;
			timePtr->tm_min = 0;
			timePtr->tm_sec = 0;          
			srchLog.t1 = mktime(timePtr);
			fprintf(stderr, "start_time:%ld\n", srchLog.t1);

			srchLog.sMajorType = 0x00FF;
			srchLog.sMinorType = 0x00FF;

			sendc = 5000; //测试数目
		}
/*
 *      如果有参数则按照搜索条件进行搜索
 */
		else
		{
/*
 *			获取日志的主次类型
 */			fprintf(stderr, "cgiauditlog::major=%d\n", major);
			fprintf(stderr, "cgiauditlog::return=%d\n", cgiFormInteger("mainType", &major, -1));	
			cgiFormInteger("sonType", &minor, -1);	
			if (-1 == major || -1 == minor) {
				fprintf(stderr, "cgiauditlog::get major/minor failed\n");
				goto FAIL;
			}
			else
			{
				if(!major) 
				{
					srchLog.sMajorType = 0x00FF;
					srchLog.sMinorType = 0x00FF;
				}
				else
				{
					srchLog.sMajorType = major<<8;
					fprintf(stderr, "cgiauditlog::majorType:%d\n", srchLog.sMajorType);
					if(!minor) 
					{
						srchLog.sMinorType = 0x00FF;
					}
					else
					{
						srchLog.sMinorType = srchLog.sMajorType|minor;
					}
					fprintf(stderr, "cgiauditlog::minorType:%d\n", srchLog.sMinorType);
				}
/*
 *				获取日志搜索的时间范围
 */
 				if (cgiFormSuccess == cgiFormString("starttimeM2", timeRange, sizeof(timeRange))) {
					srchLog.t1 = atol(timeRange);
					fprintf(stderr, "t1:%ld\n", srchLog.t1);
				} else {
					fprintf(stderr, "cgiauditlog::get starttimeM2 failed\n");
					goto FAIL;
				}

				if (cgiFormSuccess == cgiFormString("endtimeM2", timeRange, sizeof(timeRange))) {
					srchLog.t2 = atol(timeRange);
					fprintf(stderr, "t2:%ld\n", srchLog.t2);
				} else {
					fprintf(stderr, "cgiauditlog::get endtimeM2 failed\n");
					goto FAIL;
				}
				sendc = 64;
			}
		}
//		INF_ClientTalkToKing_API(&pHdr_auditLog, &mHdr_auditLog,
//				(void*)auditLog, sizeof(auditLog));

//		getLogSearch(&srchLog);
		strncpy(srchLog.cPath,"/home/zeed/ctest/log", sizeof(srchLog.cPath));
		fprintf(stderr, "cgiauditLog::cPath=%s\n", srchLog.cPath);
/*
 *		打开日志文件 读取日志内容
 */
		fd_auditLog = open (srchLog.cPath, O_RDWR);
		if(-1 == fd_auditLog)
		{
			perror("cgiauditLog::open");
			goto FAIL;
		}
/*
 *      读取日志的头部
 */
		lseek(fd_auditLog, 0, SEEK_SET);
		res = read(fd_auditLog, 
				(void*)&headLog, sizeof(headLog));
		fprintf(stderr, "cgiauditLog::headlog=%d\n", sizeof(headLog));
		fprintf(stderr, "cgiauditLog::filecnt=%d\n", headLog.fileCnt);
		fprintf(stderr, "cgiauditLog::flag= %d\n", headLog.flag);

		if(headLog.fileCnt <= 0)
		{
			printf("{\"status\":\"%s\",\"msg\":\"%s\"}", "false", "无该内容");
			return 0;
		}
/*
 *		发送日志内容给前端
 */
		else
		{
			printf ("{\"status\":\"true\",");

			timePtr = localtime(&srchLog.t1);    
			printf ("\"msg\":{");
			printf ("\"start_time\":\"%d-%02d-%02d %02d:%02d:%02d\",",
					timePtr->tm_year+1900, timePtr->tm_mon+1, timePtr->tm_mday,
					timePtr->tm_hour, timePtr->tm_min, timePtr->tm_sec);

			timePtr = localtime(&srchLog.t2);     
			printf ("\"end_time\":\"%d-%02d-%02d %02d:%02d:%02d\"",
					timePtr->tm_year+1900, timePtr->tm_mon+1,timePtr->tm_mday,
					timePtr->tm_hour, timePtr->tm_min, timePtr->tm_sec);

			printf ("},\"data\":[");
			for(i=0; i<sendc; i++)
			{
				res = read(fd_auditLog, (void*)&infoLog, sizeof(infoLog));
				timePtr = localtime(&infoLog.t);
				printf ("{\"time\":\"%d-%02d-%02d %02d:%02d:%02d\",",
						timePtr->tm_year+1900, timePtr->tm_mon+1, timePtr->tm_mday,
						timePtr->tm_hour, timePtr->tm_min, timePtr->tm_sec);
				printf ("\"number\":\"%d\",", i+1);

				switch (infoLog.sMajorType)
				{
					case LOG_ALM:
						printf ("\"majorType\":\"%s\",", 
							gLog_alm_Str[infoLog.sMajorType & ~LOG_ALM]);
						printf ("\"minorType\":\"%s\",",
							gLog_alm_Str[infoLog.sMinorType & ~LOG_ALM]);
						printf ("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}",
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_ALM]);
						break;
					case LOG_EXP:
						printf ("\"majorType\":\"%s\",", 
							gLog_exp_Str[infoLog.sMajorType & ~LOG_ALM]);
						printf ("\"minorType\":\"%s\",",
							gLog_exp_Str[infoLog.sMinorType & ~LOG_ALM]);
						printf ("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}",
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_ALM]);
						break;
					case LOG_CFG:
						printf ("\"majorType\":\"%s\",", 
							gLog_cfg_Str[infoLog.sMajorType & ~LOG_CFG]);
						printf ("\"minorType\":\"%s\",",
							gLog_cfg_Str[infoLog.sMinorType & ~LOG_CFG]);
						printf ("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}",
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_CFG]);
						break;
					case LOG_OPS:
						printf ("\"majorType\":\"%s\",", 
							gLog_ops_Str[infoLog.sMajorType & ~LOG_OPS]);
						printf ("\"minorType\":\"%s\",",
							gLog_ops_Str[infoLog.sMinorType & ~LOG_OPS]);
						printf ("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}",
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_OPS]);
						break;
					case LOG_VIW:
						printf ("\"majorType\":\"%s\",", 
							gLog_viw_Str[infoLog.sMajorType & ~LOG_VIW]);
						printf ("\"minorType\":\"%s\",",
							gLog_viw_Str[infoLog.sMinorType & ~LOG_VIW]);
						printf ("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}",
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_VIW]);
						break;
					case LOG_REC:
						printf ("\"majorType\":\"%s\",", 
							gLog_rec_Str[infoLog.sMajorType & ~LOG_REC]);
						printf ("\"minorType\":\"%s\",",
							gLog_rec_Str[infoLog.sMinorType & ~LOG_REC]);
						printf ("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}",
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_REC]);
						break;
				}
				
				if(i<sendc-1)
				{
					printf (",");
				}
			}
			printf("]}");
		}
/*
 *		读取日志结束 向主控程序再次请求一次 
 *		消息体auditLog带有路径
 */
 
/*		
		INF_ClientTalkToKing_API(&pHdr_auditLog, &mHdr_auditLog,
				(void*)&auditLog, sizeof(auditLog));		
		close(fd_auditLog);
*/		return 0;
#endif			
	}
	else
	{
	    if (deleteflag) {
            PeerHdr_t   phdr_logout = {};
	        MsgHdr_t    mhdr_logout = {};
	        sysCtrl_t   logout = {}; 
#ifdef PROJECT_KM01_FINISHED
	        initPeerHdr(&phdr_logout, NULL, getenv("REMOTE_ADDR"), PEER_CTR);
	        initMsgHdr(&mhdr_logout, CFG_LOGIN); 

	        //初始化登录消息体
	        logout.cType = CFG_LOGIN;
	        logout.ctrl.login.bOn = FALSE;
	        logout.ctrl.login.User.Cfg.cType = USER_OFF;   
	        strncpy(logout.ctrl.login.User.Cfg.Name, 
		        pHdr_srchLog.cWho, sizeof(logout.ctrl.login.User.Cfg.Name));

		    INF_ClientTalkToKing_API(&phdr_logout, 
		        &mhdr_logout, (void*)logout, sizeof(sysCtrl_t));
#endif
            printf("cgiauditlog::%s is quit because of authen failed\n", pHdr_srchLog.cWho);
		}
		fprintf(stderr, "cgiauditlog::authen by sessionid failed\n");
		goto FAIL;
	}
FAIL:
	fprintf(stderr, "cgiauditlog::Failed to search\n");
	printf("{\"status\":\"false\",\"msg\":\"failed to search\"}");
	return 1;
END:
	printf("{\"status\":\"true\",\"msg\":\"send success\"}");
	return 0;
}
