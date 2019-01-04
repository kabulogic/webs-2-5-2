/*************************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd. 
 *  Version     :   km1.0
 *  Filename    :   websSafeAPI.c
 *  Description :   provides API for safe manage
 *  Creator     :   zeed
 *  Date        :   2017-8-4
 *  History     :   
 *  <author>    <time>    <version >    <desc>
 *  zeed        17/08/4  1.0           build this moudle  
 *
 *************************************************************/

/*************************Descriptions************************/

/*
 *  This module provides API functions for safe manage
 */

/************************* Includes **************************/

#include	"websSafeAPI.h"

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
//登录锁定模式
typedef enum {
    LOCK_BAN=0,
	LOCK_ACCOUNT,
	LOCK_DEADLINE
}LoginLock;

/***************************Code******************************/
/*
 *	安全设置
 */
void formSafeSetting (webs_t wp, char_t* path, char_t* query)
{
    printf("--- kinan-formSafeSetting ---\n");
	PeerHdr_t    phdr_security_info = {};
	MsgHdr_t     mhdr_security_info = {};
	SecureCfg_t  security_info = {};
	char_t       *safeset_ptr = NULL;
	char_t       *strong_passwd_rule = NULL;
	char_t       *lock_style = NULL;
	char_t       *login_lock_ptr = NULL;
    char_t       *encrypt_mode = NULL;
	int          res;
	int          quit_flag;
	
	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, 
	        phdr_security_info.cWho, 
			sizeof(phdr_security_info.cWho),
			&quit_flag)) {
        //单点登录 (0/1)
		safeset_ptr = websGetVar(wp, T("isSingleSignOn"), T(""));
        if (safeset_ptr == NULL || *safeset_ptr == '\0') {
            printf("formSafeSet::isSingleSignOn is NULL\n");
			security_info.cSSO = 0;
            //goto FAIL;
		} else {
            if (1 == atoi(safeset_ptr)) {
				security_info.cSSO = 1;
			} else {
			    security_info.cSSO = 0;
			}
		}
		printf("formSafeSet::csso-->>%d\n", security_info.cSSO);
				
        //密码过期 (0/1)
        safeset_ptr = websGetVar(wp, T("isPasswordOverdue"), T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
            printf("formSafeSet::isPasswordOverdue is NULL\n");
			security_info.cPsswdAging = 0;
            //goto FAIL;
		} else {
            if (1 == atoi(safeset_ptr)) {
				security_info.cPsswdAging = 1;
			} else {
			    security_info.cPsswdAging = 0;
			}
		}
		printf("formSafeSet::cPsswdAging-->>%d\n", security_info.cPsswdAging);

		//密码过期时间 (1~365)(day)
		safeset_ptr = websGetVar(wp, T("day"),	T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
			printf("formSafeSet::day is NULL\n");
			goto FAIL;
		} else {
			security_info.cPsswdAgingDays = atoi(safeset_ptr);
			if (security_info.cPsswdAgingDays <= 0 || 
				    security_info.cPsswdAgingDays > 365) {
				goto FAIL;
			}	
		}
        printf("formSafeSet::cPsswdAgingDays-->>%d\n", security_info.cPsswdAgingDays);

		//注销空闲用户 (0/1)
		safeset_ptr = websGetVar(wp, T("isCancellationFreeUser"), T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
			printf("formSafeSet::isCancellationFreeUser is NULL\n");
			security_info.cLogoutIdleUser = 0;
            //goto FAIL;
		} else {
		    if (1 == atoi(safeset_ptr)) {
				security_info.cLogoutIdleUser = 1;
			} else {
			    security_info.cLogoutIdleUser = 0;
			}
		}	
		printf("formSafeSet::cLogoutIdleUser-->>%d\n", security_info.cLogoutIdleUser);
		
		//注销时间      (1~365)(minute)
        safeset_ptr = websGetVar(wp, T("setLayOutTime"), T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
			printf("formSafeSet::setLayOutTime is NULL\n");
            goto FAIL;   
		} else { 
			security_info.cLogoutIdleUserMin = atoi(safeset_ptr);
			if (security_info.cLogoutIdleUserMin < 1 || 
			   	    security_info.cLogoutIdleUserMin > 365) {
		        goto FAIL;
			}
		}
        printf("formSafeSet::cLogoutIdleUserMin-->>%d\n", security_info.cLogoutIdleUserMin);

        //是否注销空闲用户信息存于sessions.log
        printf("formSafeSet::open sessions.log\n");
		FILE *sessionid_fp = fopen(SESSIONID_SAVE_PATH, "r+");
		if (sessionid_fp == NULL) {
            printf("formSafeSet::open sessions.log failed\n");
		    goto FAIL;
		}
		fprintf(sessionid_fp, "%d%-10u\n", security_info.cLogoutIdleUser, 
		    60*security_info.cLogoutIdleUserMin);
		fclose(sessionid_fp);
		
		
		//启动强密码设置
        strong_passwd_rule = websGetVar(wp, T("isStrongPassword"), T(""));
        if (strong_passwd_rule == NULL || *strong_passwd_rule == '\0') {
			printf("formSafeSet::isStrongPassword is NULL\n");
			security_info.cPsswdStrongRule = 0;
            //goto FAIL;
		} else {
			if (1 == atoi(strong_passwd_rule)) {
                security_info.cPsswdStrongRule = 1;
			    //小写字母
			    strong_passwd_rule = websGetVar(wp, T("isLowerCase"), T(""));
				if (strong_passwd_rule == NULL || 
					*strong_passwd_rule == '\0') {
					printf("formSafeSet::isLowerCase is NULL\n");
                    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<1));
				} else {
					if (1 == atoi(strong_passwd_rule)) {
                        security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)|(0x01<<1);
					} else {
					    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<1));
                    }
				}
				
				//大写字母
				strong_passwd_rule = websGetVar(wp, T("isUpperCase"), T(""));
				if (strong_passwd_rule == NULL || 
					*strong_passwd_rule == '\0') {
					printf("formSafeSet::isUpperCase is NULL\n");
                    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<2));
				} else {
					if (1 == atoi(strong_passwd_rule)) {
                        security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)|(0x01<<2);
					} else {
					    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<2));
                    }
				}
				
				//数字字符
				strong_passwd_rule = websGetVar(wp, T("isFigure"), T(""));
				if (strong_passwd_rule == NULL || 
					*strong_passwd_rule == '\0') {
					printf("formSafeSet::isFigure is NULL\n");
                    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<3));
				} else {
					if (1 == atoi(strong_passwd_rule)) {
                        security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)|(0x01<<3);
					} else {
					    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<3)); 
					}
				}
				
				//特殊字符
				strong_passwd_rule = websGetVar(wp, T("isSymbol"), T(""));
				if (strong_passwd_rule == NULL || 
					*strong_passwd_rule == '\0') {
					printf("formSafeSet::isSymbol is NULL\n");
                    security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<4));
				} else {
					if (1 == atoi(strong_passwd_rule)) {
                        security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)|(0x01<<4);
					} else {
                        security_info.cPsswdStrongRule = (security_info.cPsswdStrongRule)&(~(0x01<<4));
					}
				}
			} else {
                security_info.cPsswdStrongRule = 0;	
		    }  
	    }
		printf("formSafeSet::cPsswdStrongRule-->>%d\n", security_info.cPsswdStrongRule);

		
		//密码历史深度 (必须要有值)
		safeset_ptr = websGetVar(wp, T("historyDepth"), T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
			printf("formSafeSet::historyDepth is NULL\n");
			goto FAIL;
		} else {
			security_info.sPsswdDepth = atoi(safeset_ptr);
			//判断密码历史深度合法性？？
		}
		printf("formSafeSet::sPsswdDepth-->>%d\n", security_info.sPsswdDepth);
		
		//密码最小长度 (必须要有值)
		safeset_ptr = websGetVar(wp, T("minLength"), T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
			printf("formSafeSet::minLength is NULL\n");
			goto FAIL;
		} else {
			security_info.sPsswdLenMin = atoi(safeset_ptr);
			//判断密码最小长度的合法性？？
		}
		printf("formSafeSet::sPsswdLenMin-->>%d\n", security_info.sPsswdLenMin);
		
		//密码最大长度 (必须要有值)
		safeset_ptr = websGetVar(wp, T("maxLength"), T(""));
		if (safeset_ptr == NULL || *safeset_ptr == '\0') {
			printf("formSafeSet::maxLength is NULL\n");
			goto FAIL;
		} else {
			security_info.sPsswdLenMax = atoi(safeset_ptr);
			//判断密码最大长度的合法性？？
		}		
		printf("formSafeSet::sPsswdLenMax-->>%d\n", security_info.sPsswdLenMax);

        //登录锁定模式
		lock_style = websGetVar(wp, T("LockStyle"), T(""));
		if (lock_style == NULL || *lock_style == '\0') {
			printf("formSafeSet::LockStyle is NULL\n");
            goto FAIL;
		} else {
			switch (atoi(lock_style)) 
			{
				case LOCK_BAN:
					security_info.cEnableLock = 1;    //禁用锁定
					security_info.cLockAccount = 0;    
				    security_info.cLockAccountTimeing = 0;    
					break;
			    case LOCK_ACCOUNT:
					security_info.cEnableLock = 0;
					security_info.cLockAccount = 1;    //锁定账户
				    security_info.cLockAccountTimeing = 0;
					break;
				case LOCK_DEADLINE:
					security_info.cEnableLock = 0;
					security_info.cLockAccount = 0;  
				    security_info.cLockAccountTimeing = 1;    //限时锁定
					break;
				default:
				    goto FAIL;
				    break;
			}
		}
		printf("formSafeSet::cEnableLock-->>%d\n", security_info.cEnableLock);
		printf("formSafeSet::cLockAccount-->>%d\n", security_info.cLockAccount);
		printf("formSafeSet::cLockAccountTimeing-->>%d\n", security_info.cLockAccountTimeing);

        //尝试次数
        if (security_info.cLockAccount) {
            login_lock_ptr = websGetVar(wp, T("maxErrorCount_stopLogin"), T(""));
		    if (login_lock_ptr == NULL || *login_lock_ptr == '\0') {
			    printf("formSafeSet::maxErrorCount_stopLogin is NULL\n");
                goto FAIL;
		    } else {
                security_info.cTryUnlockTime = atoi(login_lock_ptr);
		    }
		} else {
            login_lock_ptr = websGetVar(wp, T("maxErrorCount_timer"), T(""));
		    if (login_lock_ptr == NULL || *login_lock_ptr == '\0') {
			    printf("formSafeSet::maxErrorCount_timer is NULL\n");
                goto FAIL;
		    } else {
                security_info.cTryUnlockTime = atoi(login_lock_ptr);
		    }
		}
		printf("formSafeSet::cTryUnlockTime-->>%d\n", security_info.cTryUnlockTime);
		
		//锁定时间
	    login_lock_ptr = websGetVar(wp, T("lockTime"), T(""));
		if (login_lock_ptr == NULL || *login_lock_ptr == '\0') {
			printf("formSafeSet::lockTime is NULL\n");
            goto FAIL;
		} else {
            security_info.sLockTime = atoi(login_lock_ptr);
		}		
		printf("formSafeSet::sLockTime-->>%d\n", security_info.sLockTime);

        //本地信息加密模式
	    encrypt_mode = websGetVar(wp, T("setSecurityMode"), T(""));
		if (encrypt_mode == NULL || *encrypt_mode == '\0') {
			printf("formSafeSet::day is NULL\n");
            goto FAIL;
		} else {
            switch (atoi(encrypt_mode))
			{
				case 0:
				    security_info.encryp = NO_ENCRYP;		
					break;
				case 1:
                    security_info.encryp = ENCRYP_DES;
					break;
				case 2:
                    security_info.encryp = ENCRYP_AES128;
				    break;
				case 3:
                    security_info.encryp = ENCRYP_AES256;
				    break;
				default:
				    goto FAIL;
					break;
			}
		}
		printf("formSafeSet::encryp-->>%d\n", security_info.encryp);

        //加密模式应用于KVM和虚拟媒体
		encrypt_mode = websGetVar(wp, T("isApplySecurityMode"), T(""));
		if (encrypt_mode == NULL || *encrypt_mode == '\0') {
			printf("formSafeSet::isApplySecurityMode is NULL\n");
			security_info.cEncrypKvm = 0;
			//goto FAIL;
        } else {
            if (1 == atoi(encrypt_mode)) {
                security_info.cEncrypKvm = 1;
			} else {
                security_info.cEncrypKvm = 0;
			}
		}
		printf("formSafeSet::cEncrypKvm-->>%d\n", security_info.cEncrypKvm);

        //本地设备复位模式
		encrypt_mode = websGetVar(wp, T("setLocalDeviceResetMode"), T(""));
		if (encrypt_mode == NULL || *encrypt_mode == '\0') {
			printf("formSafeSet::day is NULL\n");
            goto FAIL;
		} else {
            switch (atoi(encrypt_mode))
            {
			    case 0:
					security_info.localReset = 0;
					break;
				case 1:
					security_info.localReset = 1;
					break;
				default:
					goto FAIL;
					break;
			}
		}
		printf("formSafeSet::localReset-->>%d\n", security_info.localReset);
		
#ifdef  PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_security_info, NULL, wp->ipaddr, PEER_SET);
		
		initMsgHdr(&mhdr_security_info, CFG_SECURE);

        INF_ClientTalkToKing_API(&phdr_security_info, 
            &mhdr_security_info, 
            (void*)&security_info, 
            sizeof(security_info));
#else
		//模拟存储
		saveSecureInfo(&security_info);
#endif		
		sendRspHeadObj(wp, SET_SUCCESS_MSG);
		sendRspFooterObj(wp);
	} else {
		if (quit_flag == 1) {
            Quit(phdr_security_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
	return ;
FAIL:
	sendRspHeadObj(wp, ARG_ERROR_MSG);
	sendRspFooterObj(wp);
	websDone(wp, 200);
	return ;
}

/*************************************************************/
/*
 *	安全设置信息
 */

void formSafeSetInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formSafeSetInfo ---\n");
	PeerHdr_t    phdr_security_info = {};
	MsgHdr_t     mhdr_security_info = {};
	SecureCfg_t  security_info = {};
	int          lock_style = 0;
    int          quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_security_info.cWho, 
			sizeof(phdr_security_info.cWho), 
			&quit_flag)) {
			
#ifdef PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_security_info, 
		    NULL, wp->ipaddr, PEER_GET);

		//CFG_SECURE???
		initMsgHdr(&mhdr_security_info, CFG_SECURE);

		INF_ClientTalkToKing_API(&phdr_security_info, 
	        &mhdr_security_info,
			(void*)security_info, 
			sizeof(security_info));

		//判断会话头的状态是否正常
#else			
		getSecureInfo(&security_info);
#endif			
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
		websWrite (wp, T("\"isSingleSignOn\":\"%d\","), 
				security_info.cSSO);
		websWrite (wp, T("\"isPasswordOverdue\":\"%d\","),
				security_info.cPsswdAging);
		websWrite (wp, T("\"day\":\"%hd\","),
				security_info.cPsswdAgingDays);
		websWrite (wp, T("\"isCancellationFreeUser\":\"%d\","),
				security_info.cLogoutIdleUser);
		websWrite (wp, T("\"setLayOutTime\":\"%hd\","),
				security_info.cLogoutIdleUserMin);

		printf("formSafeSetInfo::cPsswdStrongRule-->>%d\n", 
			security_info.cPsswdStrongRule);
		websWrite (wp, T("\"isStrongPassword\":\"%d\","),
				security_info.cPsswdStrongRule&0x01);
		websWrite (wp, T("\"isLowerCase\":\"%d\","),
				(security_info.cPsswdStrongRule>>1)&0x01);
		websWrite (wp, T("\"isUpperCase\":\"%d\","),
				(security_info.cPsswdStrongRule>>2)&0x01);
		websWrite (wp, T("\"isFigure\":\"%d\","),
				(security_info.cPsswdStrongRule>>3)&0x01);
		websWrite (wp, T("\"isSymbol\":\"%d\","),
				(security_info.cPsswdStrongRule>>4)&0x01);
		websWrite (wp, T("\"historyDepth\":\"%d\","),
				security_info.sPsswdDepth);
		//密码长度
		websWrite (wp, T("\"minLength\":\"%d\","),
				security_info.sPsswdLenMin);
		websWrite (wp, T("\"maxLength\":\"%d\","),
				security_info.sPsswdLenMax);
        if (security_info.cEnableLock) {
            lock_style = 0;
		} else if (security_info.cLockAccount) {
            lock_style = 1;
		} else if (security_info.cLockAccountTimeing) {
            lock_style = 2;
		}
		websWrite (wp, T("\"LockStyle\":\"%d\","), lock_style);
		websWrite (wp, T("\"maxErrorCount_stopLogin\":\"%d\","),
				security_info.cTryUnlockTime);
		websWrite (wp, T("\"maxErrorCount_timer\":\"%d\","),
				security_info.cTryUnlockTime);
		websWrite (wp, T("\"lockTime\":\"%hd\","),
				security_info.sLockTime);

        printf("formSafeSetInfo::setSecurityMode-->>%d\n", 
			security_info.encryp);
		websWrite (wp, T("\"setSecurityMode\":\"%d\","),
				security_info.encryp);
		websWrite (wp, T("\"isApplySecurityMode\":\"%d\","),
				security_info.cEncrypKvm);
		websWrite (wp, T("\"setLocalDeviceResetMode\":\"%d\""),
				security_info.localReset);
		sendRspFooterObj(wp);
	} else {
		if (quit_flag == 1) {
            Quit(phdr_security_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *	验证设置信息
 */

void formConfirmSetInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formConfirmSetInfo ---\n");
	PeerHdr_t    phdr_verify_config = {};
	MsgHdr_t     mhdr_verify_config = {};
	VerifyCft_t  verify_config = {};
	int          quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_verify_config.cWho, 
			sizeof(phdr_verify_config.cWho), 
			&quit_flag)) {
			
#ifdef PROJECT_KM01_FINISHED
        initPeerHdr(&phdr_verify_config, 
            NULL, wp->ipaddr, PEER_GET);

		//CFG_SYSTEM_INFO
		initMsgHdr(&mhdr_verify_config, CFG_SYSTEM_INFO);

		INF_ClientTalkToKing_API(&phdr_verify_config, 
	        &mhdr_verify_config,
			(void*)verify_config, 
			sizeof(verify_config));
#else
		getConfirmInfo (&verify_config);
#endif			
		sendRspHeadObj (wp, AUTHEN_SUCCESS_MSG);
		websWrite(wp, T("\"verify\":\"%d\","),
		    	  verify_config.verify);
		websWrite(wp, T("\"ldap_server\":\"%s\","),
				  verify_config.ldap.cLdapServer);
		websWrite(wp, T("\"ldap_port\":\"%d\","),
				  verify_config.ldap.cPort);
		websWrite(wp, T("\"ldap_severtype\":\"%d\","),
				  verify_config.ldap.cLadpServerType);
		websWrite(wp, T("\"ldap_cscandns\":\"%s\","),
				  verify_config.ldap.cScanDNS);
		websWrite(wp, T("\"ldap_ctestusername\":\"%s\","),
				  verify_config.ldap.cTestUserName);
		websWrite(wp, T("\"ldap_ctestpsswd\":\"%s\","),
				  verify_config.ldap.cTestPsswd);
		websWrite(wp, T("\"radius_sever\":\"%s\","),
				  verify_config.radius.cServer);
		websWrite(wp, T("\"radius_code\":\"%s\","),
				  verify_config.radius.cShareCode);
		websWrite(wp, T("\"radius_lport\":\"%d\","),
				  verify_config.radius.lPort);
		websWrite(wp, T("\"radius_stime\":\"%d\","),
				  verify_config.radius.sTimeOut);
		websWrite(wp, T("\"radius_sretry\":\"%d\""),
				  verify_config.radius.sRetry);
		sendRspFooterObj (wp);
	} else {
		if (quit_flag == 1) {
            Quit(phdr_verify_config.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *	验证设置
 */

void formConfirmSet (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formConfirmSet ---\n");
	char_t       *verify_flag = NULL;
	char_t       *ldap_ptr = NULL;
	char_t       *radius_ptr = NULL;
	PeerHdr_t    phdr_verify_config = {};
	MsgHdr_t     mhdr_verify_config = {};
	VerifyCft_t  verify_config = {};
	int          quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_verify_config.cWho, 
			sizeof(phdr_verify_config), 
			&quit_flag)) {
		verify_flag = websGetVar (wp, T("checkType"), T(""));
		if (verify_flag == NULL || *verify_flag == '\0') {
			goto FAIL;
		} else {
			switch (atoi(verify_flag))
			{
				case 0:
					verify_config.verify = VERIFY_WAY_LOCAL;
					printf("formConfirmSet::verify-->>%d\n", verify_config.verify);
					break;
				case 1:
					verify_config.verify = VERIFY_WAY_LDAP;
					printf("formConfirmSet::verify-->>%d\n", verify_config.verify);
				
					ldap_ptr = websGetVar(wp, T("primaryLDAPServer"), T(""));
				    if (ldap_ptr == NULL || *ldap_ptr == '\0') {
                        goto FAIL;
					} else {
                        strncpy(verify_config.ldap.cLdapServer,
							    ldap_ptr,
							    sizeof(verify_config.ldap.cLdapServer));
					}
                    printf("formConfirmSet::ldap.cLdapServer-->>%s\n", 
                           verify_config.ldap.cLdapServer);

					ldap_ptr = websGetVar(wp, T("ldapPort"), T(""));
					if (ldap_ptr == NULL || *ldap_ptr == '\0') {
                        goto FAIL;
					} else {
                        verify_config.ldap.cPort = atoi(ldap_ptr);
					}
					printf("formConfirmSet::ldap.cPort-->>%d\n", 
					       verify_config.ldap.cPort);

					ldap_ptr = websGetVar(wp, T("ldapServerType"), T(""));
					if (ldap_ptr == NULL || *ldap_ptr == '\0') {
                        verify_config.ldap.cLadpServerType = 0;
					} else {
                        verify_config.ldap.cLadpServerType = atoi(ldap_ptr);
					}
					printf("formConfirmSet::ldap.cLadpServerType-->>%d\n", 
					       verify_config.ldap.cLadpServerType);

					ldap_ptr = websGetVar(wp, T("searchDn"), T(""));
					if (ldap_ptr == NULL || *ldap_ptr == '\0') {
                        goto FAIL;
					} else {
                        strncpy(verify_config.ldap.cScanDNS,
							    ldap_ptr,
							    sizeof(verify_config.ldap.cScanDNS));
					}
					printf("formConfirmSet::ldap.cScanDNS-->>%s\n", 
					       verify_config.ldap.cScanDNS);

					ldap_ptr = websGetVar(wp, T("testLDAPName"), T(""));
					if (ldap_ptr == NULL || *ldap_ptr == '\0') {
                        goto FAIL;
					} else {
                        strncpy(verify_config.ldap.cTestUserName,
							    ldap_ptr,
							    sizeof(verify_config.ldap.cTestUserName));
					}					
					printf("formConfirmSet::ldap.cTestUserName-->>%s\n", 
					       verify_config.ldap.cTestUserName);

					ldap_ptr = websGetVar(wp, T("testLDAPPwd"), T(""));
					if (ldap_ptr == NULL || *ldap_ptr == '\0') {
                        goto FAIL;
					} else {
                        strncpy(verify_config.ldap.cTestPsswd,
							    ldap_ptr,
							    sizeof(verify_config.ldap.cTestPsswd));
					}
					printf("formConfirmSet::ldap.cTestPsswd-->>%s\n", 
					       verify_config.ldap.cTestPsswd);
					break;
				case 2:
					verify_config.verify = VERIFY_WAY_RADIUS;
					printf("formConfirmSet::verify-->>%d\n", verify_config.verify);

					radius_ptr = websGetVar(wp, T("hostname"), T(""));
					if (radius_ptr == NULL || *radius_ptr == '\0') {
                        goto FAIL;
					} else {
                        strncpy(verify_config.radius.cServer,
							    radius_ptr,
							    sizeof(verify_config.radius.cServer));
					}
					printf("formConfirmSet::radius.cServer-->>%s\n", 
					       verify_config.radius.cServer);

					radius_ptr = websGetVar(wp, T("shared_secret"), T(""));
					if (radius_ptr == NULL || *radius_ptr == '\0') {
                        goto FAIL;
					} else {
                        strncpy(verify_config.radius.cShareCode,
							    radius_ptr,
							    sizeof(verify_config.radius.cShareCode));
					}
					printf("formConfirmSet::radius.cShareCode-->>%s\n", 
					       verify_config.radius.cShareCode);

					radius_ptr = websGetVar(wp, T("port"), T(""));
					if (radius_ptr == NULL || *radius_ptr == '\0') {
                        goto FAIL;
					} else {
                       verify_config.radius.lPort = atoi(radius_ptr);
					}
					printf("formConfirmSet::radius.lPort-->>%d\n", 
					       verify_config.radius.lPort);

					radius_ptr = websGetVar(wp, T("socket_timeout"), T(""));
					if (radius_ptr == NULL || *radius_ptr == '\0') {
                        goto FAIL;
					} else {
                       verify_config.radius.sTimeOut = atoi(radius_ptr);
					}
					printf("formConfirmSet::radius.sTimeOut-->>%d\n", 
					       verify_config.radius.sTimeOut);

					radius_ptr = websGetVar(wp, T("retires"), T(""));
					if (radius_ptr == NULL || *radius_ptr == '\0') {
                        goto FAIL;
					} else {
                       verify_config.radius.sRetry = atoi(radius_ptr);
					}
					printf("formConfirmSet::radius.sRetry-->>%d\n", 
					       verify_config.radius.sRetry);
					break;
				default:
					goto FAIL;
					break;
			}
#ifdef PROJECT_KM01_FINISHED

			initPeerHdr(&phdr_verify_config, 
			    NULL, wp->ipaddr, PEER_SET);

			initMsgHdr(&mhdr_verify_config CFG_SECURE);

            INF_ClientTalkToKing_API(&phdr_verify_config, 
                &mhdr_verify_config, 
                (void*)&verify_config, 
                sizeof(verify_config));
#else
            saveConfirmInfo(&verify_config);
#endif
			sendRspHeadObj(wp, SET_SUCCESS_MSG);
			sendRspFooterObj(wp);	
		}
	} else {
	    if (quit_flag) {
            Quit(phdr_verify_config.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
	return ;
FAIL:
	sendRspHeadObj(wp, ARG_ERROR_MSG);
	sendRspFooterObj(wp);
	websDone(wp, 200);
	return ;
}

/*************************************************************/
/*
 *	审计日志 -->> 改用CGI的处理方式
 */

void formAuditLog (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formAuditLog ---\n");
	PeerHdr_t       pHdr_srchLog = {};
	MsgHdr_t        mHdr_srchLog = {};
	logSearch_t     srchLog = {};         //获取日志文件路径
	log_res_head_t  headLog = {};         //日志头
	log_t           infoLog = {};         //日志内容
	char            *timeHide = NULL;
	char            *majorPtr = NULL, *minorPtr = NULL;
	int             major, minor, fd_auditLog, res, i;
	struct tm       *timePtr;
	int             sendc;
    int             quit_flag = 0;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    pHdr_srchLog.cWho, 
		    sizeof(pHdr_srchLog.cWho), 
		    &quit_flag)) {
		    
#ifdef PROJECT_KM01_FINISHED
		initPeerHdr(&pHdr_srchLog, NULL, wp->ipaddr,
				PEER_CTR);

        //CTRL_LOG ???
		initMsgHdr(&mHdr_srchLog, CTRL_LOG);
#endif
		//如果没有传递参数则默认请求当天凌晨至当前时间的日志数据
		if(query == NULL || *query == '\0')
		{
			srchLog.t2 = time(NULL);     
			printf("  end_time:%ld\n", srchLog.t2);
			
			timePtr = localtime(&srchLog.t2);
			timePtr->tm_hour = 0;
			timePtr->tm_min = 0;
			timePtr->tm_sec = 0;          
			srchLog.t1 = mktime(timePtr);
			printf("start_time:%ld\n", srchLog.t1);

			srchLog.sMajorType = 0x00FF;
			srchLog.sMinorType = 0x00FF;

			sendc = 5000;
		}

		//如果有参数则按照搜索条件进行搜索
		else
		{
			majorPtr = websGetVar (wp, T("mainType"), T(""));
			minorPtr = websGetVar (wp, T("sonType"), T(""));
					
			if(majorPtr == NULL || *majorPtr == '\0' ||
					minorPtr == NULL || *minorPtr == '\0')
			{
				sendRspHeadObj (wp, ARG_ERROR_MSG);
				sendRspFooterObj (wp);
			}
			else
			{

                //获取日志的主次类型
 				major = atoi(majorPtr);
				minor = atoi(minorPtr);
			
				if(!major) 
				{
					srchLog.sMajorType = 0x00FF;
					srchLog.sMinorType = 0x00FF;
				}
				else
				{
					srchLog.sMajorType = major<<8;
					printf("majorType:%d\n", srchLog.sMajorType);
					if(!minor) 
					{
						srchLog.sMinorType = 0x00FF;
					}
					else
					{
						srchLog.sMinorType = srchLog.sMajorType|minor;
					}
					printf("minorType:%d\n", srchLog.sMinorType);
				}

				//获取日志搜索的时间范围
 				timeHide = websGetVar (wp, T("starttimeM2"), T(""));
				printf("timeHide1:%s\n", timeHide);
				srchLog.t1 = atol(timeHide);
				printf("t1:%ld\n", srchLog.t1);

				timeHide = websGetVar (wp, T("endtimeM2"), T(""));
				printf("timeHide2:%s\n", timeHide);
				srchLog.t2 = atol(timeHide);
				printf("t2:%ld\n", srchLog.t2);

				sendc = 64;
			}
		}
		
#ifdef PROJECT_KM01_FINISHED		
        INF_ClientTalkToKing_API(&pHdr_srchLog, &mHdr_srchLog,
            (void*)srchLog, sizeof(srchLog));
#endif
		getLogSearch(&srchLog);
		printf("auditLog.cPath:%s\n", srchLog.cPath);

        //打开日志文件 读取日志内容
		fd_auditLog = open (srchLog.cPath, O_RDWR);
		if(-1 == fd_auditLog)
		{
			perror("open auditLog.cPath");
			sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return ;
		}

		//读取日志的头部
 		lseek(fd_auditLog, 0, SEEK_SET);
		res = read(fd_auditLog, 
				(void*)&headLog, sizeof(headLog));
		printf("headlog:%d\n", sizeof(headLog));
		printf("%d\n", headLog.fileCnt);
		printf("%d\n", headLog.flag);

		if(headLog.fileCnt <= 0)
		{
			sendRspHeadObj(wp, LOG_EMPTY);
			sendRspFooterObj(wp);
		}

        //发送日志内容给前端
 		else
		{
			websWrite (wp, T("{\"status\":\"true\","));

			timePtr = localtime(&srchLog.t1);    
			websWrite (wp, T("\"msg\":{"));
			websWrite (wp, T("\"start_time\":\"%d-%02d-%02d %02d:%02d:%02d\","),
					timePtr->tm_year+1900, timePtr->tm_mon+1, timePtr->tm_mday,
					timePtr->tm_hour, timePtr->tm_min, timePtr->tm_sec);

			timePtr = localtime(&srchLog.t2);     
			websWrite (wp, T("\"end_time\":\"%d-%02d-%02d %02d:%02d:%02d\""),
					timePtr->tm_year+1900, timePtr->tm_mon+1,timePtr->tm_mday,
					timePtr->tm_hour, timePtr->tm_min, timePtr->tm_sec);

			websWrite (wp, T("},\"data\":["));
			for(i=0; i<sendc; i++)
			{
				res = read(fd_auditLog, (void*)&infoLog, sizeof(infoLog));
				timePtr = localtime(&infoLog.t);
				websWrite (wp, T("{\"time\":\"%d-%02d-%02d %02d:%02d:%02d\","),
						timePtr->tm_year+1900, timePtr->tm_mon+1, timePtr->tm_mday,
						timePtr->tm_hour, timePtr->tm_min, timePtr->tm_sec);
				websWrite (wp, T("\"number\":\"%d\","), i+1);

				switch (infoLog.sMajorType)
				{
					case LOG_ALM:
						websWrite(wp, T("\"majorType\":\"%s\","), 
							gLog_alm_Str[infoLog.sMajorType & ~LOG_ALM]);
						websWrite(wp, T("\"minorType\":\"%s\","),
							gLog_alm_Str[infoLog.sMinorType & ~LOG_ALM]);
						websWrite(wp, T("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}"),
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_ALM]);
						break;
					case LOG_EXP:
						websWrite(wp, T("\"majorType\":\"%s\","), 
							gLog_exp_Str[infoLog.sMajorType & ~LOG_ALM]);
						websWrite(wp, T("\"minorType\":\"%s\","),
							gLog_exp_Str[infoLog.sMinorType & ~LOG_ALM]);
						websWrite(wp, T("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}"),
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_ALM]);
						break;
					case LOG_CFG:
						websWrite(wp, T("\"majorType\":\"%s\","), 
							gLog_cfg_Str[infoLog.sMajorType & ~LOG_CFG]);
						websWrite(wp, T("\"minorType\":\"%s\","),
							gLog_cfg_Str[infoLog.sMinorType & ~LOG_CFG]);
						websWrite(wp, T("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}"),
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_CFG]);
						break;
					case LOG_OPS:
						websWrite(wp, T("\"majorType\":\"%s\","), 
							gLog_ops_Str[infoLog.sMajorType & ~LOG_OPS]);
						websWrite(wp, T("\"minorType\":\"%s\","),
							gLog_ops_Str[infoLog.sMinorType & ~LOG_OPS]);
						websWrite(wp, T("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}"),
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_OPS]);
						break;
					case LOG_VIW:
						websWrite(wp, T("\"majorType\":\"%s\","), 
							gLog_viw_Str[infoLog.sMajorType & ~LOG_VIW]);
						websWrite(wp, T("\"minorType\":\"%s\","),
							gLog_viw_Str[infoLog.sMinorType & ~LOG_VIW]);
						websWrite(wp, T("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}"),
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_VIW]);
						break;
					case LOG_REC:
						websWrite(wp, T("\"majorType\":\"%s\","), 
							gLog_rec_Str[infoLog.sMajorType & ~LOG_REC]);
						websWrite(wp, T("\"minorType\":\"%s\","),
							gLog_rec_Str[infoLog.sMinorType & ~LOG_REC]);
						websWrite(wp, T("\"explain\":\"用户'%s'在主机'%s'上'%s'\"}"),
							infoLog.cUser, infoLog.IP,
							gLog_ops_Str[infoLog.sMinorType & ~LOG_REC]);
						break;
				}
				
				if(i<sendc-1)
				{
					websWrite(wp, T(","));
				}
			}
			sendRspFooterArray(wp);
		}

        //读取日志结束 向主控程序再次请求一次 
        //消息体auditLog带有路径

#ifdef PROJECT_KM01_FINISHED		
        INF_ClientTalkToKing_API(&pHdr_srchLog, &mHdr_srchLog,
            (void*)srchLog, sizeof(srchLog));
        close(fd_auditLog);
#endif		
    } else {
        if (quit_flag) {
            Quit(pHdr_srchLog.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
	printf("log message send over!\n");
}

