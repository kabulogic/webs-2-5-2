/****************************************************************
*  Copyright (c) 2017-2021,Kinan Tech. Co., Ltd.
*  Version     :    km1.0
*  Filename    :    websLoginAPI.c
*  Description :    此模块包括 用户登录登出API
*					用户的身份认证
*					发送Json数据格式的框架
*  Creator     :    Zeed
*  Date        :    2017-08-02
*  History     :
*  <author>    <time>    <version>    <desc>
*  Zeed        17/08/02   1.0          build this moudle
*  
******************************************************************/
/*************************** Includes ****************************/
#include "websLoginAPI.h"

/***************************** Code ******************************
*   
*  登出
*  将用户名传递给主控程序
*/
void Quit(char_t *username, char_t *ip)
{
    PeerHdr_t   phdr_logout = {};
	MsgHdr_t    mhdr_logout = {};
	sysCtrl_t   logout = {}; 
	
#ifdef  PROJECT_KM01_FINISHED
	initPeerHdr(&phdr_logout, NULL, ip, PEER_CTR);
	initMsgHdr(&mhdr_logout, CFG_LOGIN); 

	//初始化登录消息体
	logout.cType = CFG_LOGIN;
	logout.ctrl.login.bOn = FALSE;
	logout.ctrl.login.User.Cfg.cType = USER_OFF;   
	strncpy(logout.ctrl.login.User.Cfg.Name, 
		phdr_logout.cWho, sizeof(logout.ctrl.login.User.Cfg.Name));
	
	INF_ClientTalkToKing_API(&phdr_logout, 
		&mhdr_logout, (void*)logout, sizeof(sysCtrl_t));
#endif

#ifdef  PORJECT_KM01_DEBUG
    printf("Quit::%s is quit\n", username);
#endif
}

/*****************************************************************
*   
*  登出
*  通过身份验证 获取退出操作用户名
*  将用户名传递给主控程序
*  并删除该用户对应的sessionid
*  刷新sessions.log文件数据
*/
void formQuit(webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formQuit ---\n");
	char_t        *sessionid_key = NULL;  
	char_t        *sessionid_value = NULL;               
	sessionNode   *sessionid_q = NULL;  //初始化session节点获取sessionid
	sessionList   sessionList_vale = {};
	logoutTime_t  logouts = {};  //注销用户
	int           sessions_pos = -1; 
	int           loadflag = 0;
	int           deletflag = 0;
	time_t        current_time;
	
	a_assert(wp);
	goformHead(wp);
	if (wp->cookie == NULL) {
		goto FAIL;	
	} else {
	    // 从cookie中获取sessionid
		extractKeyValue2(wp->cookie, "CSESSIONID", ";", &sessionid_value);

        // 从文件中加载数据到链表中
		sessionList_vale.sessionHead = sessionLoad(&logouts, 
     		    &sessionList_vale.count, SESSIONID_SAVE_PATH);
		loadflag = 1;
		
#ifdef  PORJECT_KM01_DEBUG
        // 测试读取到sessions表中的数据
		sessionNode *tmp_sessionid_ptr = sessionList_vale.sessionHead;
		printf("formQuit::--- test what we found from file ---\n");
		while (tmp_sessionid_ptr) {
			printf("formQuit::username-->>%s\n", 
		        tmp_sessionid_ptr->username);
		    printf("formQuit::sessiontime-->>%lu\n",
		  	    tmp_sessionid_ptr->sessiontime);
			printf("formQuit::sessionid-->>%s\n",
				tmp_sessionid_ptr->sessionid);
			tmp_sessionid_ptr = tmp_sessionid_ptr->snpNext;
		}
		printf("formQuit::count-->>%d\n", sessionList_vale.count);
#endif

		// 根据sessionid查询位置
		sessions_pos = findSessionByid(&sessionList_vale, sessionid_value);
		printf("formQuit::pos-->>%d\n", sessions_pos);
		
		if (sessions_pos < 0) {
			goto FAIL;
		} else {
		    sessionid_q = readSession(&sessionList_vale, sessions_pos);

            Quit(sessionid_q->username, wp->ipaddr);

		    printf("formQuit::--- %s is quit! ---\n", sessionid_q->username);
		    delSession(&sessionList_vale, sessions_pos);

			// 如果设定了注销用户选项 则遍历删除过期用户
			if (logouts.enable) {
                sessionid_q = sessionList_vale.sessionHead;
				time(&current_time);
				while (sessionid_q != NULL) {
					if (sessionid_q->sessiontime < current_time) {
						deletflag = 1;
						sessions_pos = findSession(&sessionList_vale, sessionid_q->username);
					    Quit(sessionid_q->username, wp->ipaddr);
					} 
					// 指向下一个节点
					sessionid_q = sessionid_q->snpNext;
					if (1 == deletflag) {
						delSession(&sessionList_vale, sessions_pos);
						deletflag = 0;
					}
				}
			}
			
			sessionSave(&sessionList_vale, &logouts, SESSIONID_SAVE_PATH);
			sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			if (loadflag) {
				printf("formQuit::s clear sessions\n");
                clearSession(&sessionList_vale);
			}
			return ;
		}
	}
FAIL:
    sendRspHeadObj(wp, ARG_ERROR_MSG);
	sendRspFooterObj(wp);
	websDone(wp, 200);
	if (loadflag) {
		printf("formQuit::f clear sessions\n");
        clearSession(&sessionList_vale);
	}
	return ;
}

/*****************************************************************
*   
*  登录
*  从网页获取用户名和密码 将密码解密后传给主控程序
*  验证通过后 遍历sessions链表 清除过期的sessionid
*  产生新的sessionid节点 并存入文件 
*  文件路径暂定 ../www/km01/cgi-bin/sessions.log
*/

void formLogin(webs_t wp, char_t* path, char_t* query)
{
    printf("--- kinan-formLogin ---\n");
	PeerHdr_t    phdr_login = {};
	MsgHdr_t     mhdr_login = {};
	sysCtrl_t    login = {}; 
	
    char         passwd_cleartext[MAX_OG_SESSIONID_LEN] = {};     
    char         *username_for_login = NULL;
	char         *password_for_login = NULL;  	
	sessionList  sessionList_vale = {};
	sessionNode   *sessionid_tmp = NULL;  
	logoutTime_t logouts = {};
	int          loadflag = 0;
	int          deletflag = 0;
	int          sessions_pos = -1;
	time_t       current_time;

	// 模拟验证
	char       *name_from_file, *tmp;
	int        fd, sta;	
	char       password_from_file[MAX_PSWD_LEN] = {};
	char       cSessionid[MAX_SESSIONID_LEN] = {};     
		
	printf("formLogin::sessionid-->>%s\n",wp->cookie);
	printf("formLogin::ip-->>%s\n", wp->ipaddr);

	a_assert(wp);
    username_for_login = websGetVar(wp, T("username"), T(""));    
	password_for_login = websGetVar(wp, T("password"), T(""));

    if (username_for_login == NULL || password_for_login == NULL || 
		*username_for_login == '\0' || *password_for_login == '\0') {
        goto FAIL;
	} else {
		// 判断用户名的合法性
		if (strncmp(username_for_login, "admin", 
			sizeof(username_for_login))) {
			if (strlen(username_for_login) < 6 || strlen(username_for_login) >20) {
	        	goto FAIL;
			}
		}
		if (strlen(password_for_login) < 16 || strlen(password_for_login) > 32) {
            goto FAIL;
		}
		
	    // 解密密码
		decString((const char*)password_for_login, (char*)passwd_cleartext, 
		    	  sizeof(passwd_cleartext));
	}
	printf("formLogin::username_for_login-->%s\n", username_for_login);
	printf("formLogin::passwd_cleartext-->%s\n", passwd_cleartext);
	
#ifdef PROJECT_KM01_FINISHED
	// 初始化会话头
	initPeerHdr(&phdr_login, username_for_login, wp->ipaddr, PEER_CTR);

	// 初始化消息头
	initMsgHdr(&mhdr_login, CFG_LOGIN);

	// 初始化登录消息体
	login.cType = CFG_LOGIN;
	// 登录
	login.ctrl.login.bOn = TRUE;
	// 用户登录
	login.ctrl.login.User.Cfg.cType = USER_ON;   
	strncpy(login.ctrl.login.User.Cfg.Name, 
		username_for_login, 
		sizeof(login.ctrl.login.User.Cfg.Name));
	strncpy(login.ctrl.login.User.Cfg.Pswd, 
		passwd_cleartext, 
		sizeof(login.ctrl.login.User.Cfg.Pswd));
	
	INF_ClientTalkToKing_API(&phdr_login, &mhdr_login, 
		(void*)login, sizeof(login));	

    // 验证用户名密码并发送验证结果给前端
	websWrite(wp, T("HTTP/1.0 200 OK\n"));
	websWrite(wp, T("Pragma: no-cache\n"));
	websWrite(wp, T("Cache-control: no-cache\n"));
	websWrite(wp, T("Content-Type: text/html\n"));

	// 判断是否登录成功 将登录结果发送给前端
	if (phdr_login.cStatus) {
	    sessionList_vale.sessionHead = sessionLoad(&logouts,
		    &sessionList_vale.count, SESSIONID_SAVE_PATH);
        loadflag = 1;

		printf("formLogin::logouts.enable-->>%d\n", logouts.enable);
		if (logouts.enable) {
		    // 遍历链表将过期的节点删除
			sessionid_tmp = sessionList_vale.sessionHead;
			time(&current_time);
			while (sessionid_tmp != NULL) {
				if (sessionid_tmp->sessiontime < current_time) {
					deletflag = 1;
					sessions_pos = findSession(&sessionList_vale, sessionid_tmp->username);
				    Quit(sessionid_tmp->username, wp->ipaddr);
				} 
				// 指向下一个节点
				sessionid_tmp = sessionid_tmp->snpNext;
				if (1 == deletflag) {
					delSession(&sessionList_vale, sessions_pos);
					deletflag = 0;
				}
			}
		}
		// 添加新节点到尾部
		pushTailSession(&sessionList_vale, username_for_login);
		
		sessionSave(&sessionList_vale, &logouts, SESSIONID_SAVE_PATH);

		// 将新节点的sessionid发送至前端COOKIE中
		websWrite(wp, T("Set-Cookie: CSESSIONID=%s; path=/\r\n"),
			readSession(&sessionList_vale,sessionList_vale.count-1)->sessionid);
		websWrite(wp, T("\n"));
		sendRspHeadObj(wp, LOGIN_SUCCESS_MSG);
		websWrite(wp,T("\"result\":\"ok\""));
		sendRspFooterObj(wp);
	} else {
		websWrite(wp, T("\n"));
		sendRspHeadObj(wp, LOGIN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
#else
    // 模拟主控程序验证登录
    name_from_file = username_for_login;	    
	fd = open ("pd.txt", O_RDONLY|O_CREAT, 0664);
	if(fd == -1)
		perror("login-open");
	sta = read(fd, password_from_file, sizeof(password_from_file));

	tmp = password_from_file;
	if (password_from_file[strlen(password_from_file)-1] == '\n') {
		password_from_file[strlen(password_from_file)-1] = '\0';
	}

    // 验证用户名密码并发送验证结果给前端
    websWrite(wp, T("HTTP/1.0 200 OK\n"));
    websWrite(wp, T("Pragma: no-cache\n"));
    websWrite(wp, T("Cache-control: no-cache\n"));
    websWrite(wp, T("Content-Type: text/html\n"));

	// 将主控程序判断结果发送给前端
    if (!strncmp(username_for_login, name_from_file/*"admin"*/,
		     sizeof(username_for_login))) {
        if (!strncmp(passwd_cleartext, password_from_file,
			     sizeof(passwd_cleartext))) { 
			printf("formLogin::sessionLoad\n");
			
			sessionList_vale.sessionHead = sessionLoad(&logouts,
				&sessionList_vale.count, SESSIONID_SAVE_PATH);
            loadflag = 1;
			
            printf("formLogin::logouts.enable-->>%d\n", logouts.enable);
			if (logouts.enable) {
			    // 遍历链表将过期的节点删除
			    sessionid_tmp = sessionList_vale.sessionHead;
				time(&current_time);
				while (sessionid_tmp != NULL) {
					if (sessionid_tmp->sessiontime < current_time) {
						deletflag = 1;
						sessions_pos = findSession(&sessionList_vale, sessionid_tmp->username);
					    Quit(sessionid_tmp->username, wp->ipaddr);
					} 
					// 指向下一个节点
					sessionid_tmp = sessionid_tmp->snpNext;
					if (1 == deletflag) {
						delSession(&sessionList_vale, sessions_pos);
						deletflag = 0;
					}
				}
			}
			//添加到尾部
			pushTailSession(&sessionList_vale, username_for_login);
			
			sessionSave(&sessionList_vale, &logouts, SESSIONID_SAVE_PATH);
			websWrite(wp, T("Set-Cookie: CSESSIONID=%s; path=/\r\n"),
					readSession(&sessionList_vale,sessionList_vale.count-1)->sessionid);
			websWrite(wp, T("\n"));
			sendRspHeadObj(wp, LOGIN_SUCCESS_MSG);
			websWrite(wp,T("\"result\":\"ok\""));
			sendRspFooterObj(wp);
		} else {
			websWrite(wp, T("\n"));
			sendRspHeadObj(wp, LOGIN_ERRO_MSG);
			sendRspFooterObj(wp);
        }
    }else {
		websWrite(wp, T("\n"));
		sendRspHeadObj(wp, LOGIN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
#endif
    websDone(wp, 200);
    if (loadflag) {
		printf("formLogin::s clear sessions\n");
        clearSession(&sessionList_vale);
	}
    return ;
FAIL:
	goformHead(wp);
    sendRspHeadObj(wp, ARG_ERROR_MSG);
	sendRspFooterObj(wp);
	websDone(wp, 200);
	if (loadflag) {
		printf("formLogin::f clear sessions\n");
        clearSession(&sessionList_vale);
	}
	return ;
}

/*************************************************************
 *
 *  goform接口的登录验证
 *  分解cookie得到sessionid 并查找sessionid在链表中的位置
 *  如果在内存中sessions的链表无对应的sessionid
 *  需要读取sessions.log文件中的数据首先将sessions链表清空
 *  然后加载数据到sessions中
 *	(这种情况一般在服务器重启后保证页面仍可以请求)
 * 
 *  @param [in    ] wp：webs结构体指针
 *  @param [out   ] username：根据cookie中的sessionid获取对应的用户名
 *  @param [in    ] size: username的最大长度
 *  @param [in out] flag: 1用户验证未通过 需要退出该用户  
 *  @return 0  验证通过     -1 验证失败
 *  
 */

int authenLogin (webs_t wp, char *username, int size, int *flag)
{
	printf("*** kinan-authenlogin ***\n");
	char           *key_sessinid = NULL;  
	char           *value_sessionid = NULL; 
	time_t         current_time;               
	sessionNode    *authen_sessionid = NULL;  //初始化session节点获取sessionid
	sessionList    sessionList_vale = {};
	logoutTime_t   logouts = {};  //注销用户
	int            pos_sessions = -1; 
	int            loadflag = 0;
	
	a_assert(wp);
	*flag = 0;
	if (wp->cookie == NULL) {
		printf("authenLogin::OMG this request have not cookie!\n");
		printf("authenLogin::return -1\n");
	    return -1;//-1	
	} else {
	    // 从cookie中获取sessionid
	    extractKeyValue2(wp->cookie, "CSESSIONID", "; ", &value_sessionid);
		printf("authenLogin::get the sessionid-->>%s\n", value_sessionid);

        // 从文件中获取数据到链表中
		printf("authenLogin::get sessionlist from file\n");
		sessionList_vale.sessionHead = sessionLoad(&logouts, 
			&sessionList_vale.count, SESSIONID_SAVE_PATH);
		loadflag = 1;

#ifdef  PORJECT_KM01_DEBUG
		// 测试读取到sessions表中的数据
		sessionNode *tmp_sessionid_ptr = sessionList_vale.sessionHead;
        printf("authenLogin::test what we found from file\n");
		while (tmp_sessionid_ptr) {
			printf("authenLogin::username-->>%s\n", 
		        tmp_sessionid_ptr->username);
		    printf("authenLogin::sessiontime-->>%lu\n",
   			    tmp_sessionid_ptr->sessiontime);
			printf("authenLogin::sessionid-->>%s\n",
				tmp_sessionid_ptr->sessionid);
			tmp_sessionid_ptr = tmp_sessionid_ptr->snpNext;
		}
		printf("authenLogin::count-->>%d\n", sessionList_vale.count);
#endif		
		pos_sessions = findSessionByid(&sessionList_vale, value_sessionid);
		printf("authenLogin::pos-->>%d\n", pos_sessions);
		
		if (pos_sessions < 0) {
			if (loadflag) {
				clearSession(&sessionList_vale);
				printf("authenLogin::f clear sessions\n");
			}
			printf("authenLogin::pos_sessions<0 so return -1\n");
			return -1;//-1
		} else {
			authen_sessionid = readSession(&sessionList_vale, pos_sessions);
			if (logouts.enable) {
			    time(&current_time);
			    if (current_time <= authen_sessionid->sessiontime) {
                    // 将得到的用户名存入username
				    strncpy(username, authen_sessionid->username, size);
                    // 更新过期时间
				    authen_sessionid->sessiontime = current_time + logouts.times;
				    printf("authenLogin::newtime-->>%lu\n", authen_sessionid->sessiontime);
			        printf("authenLogin::update the time and save to file\n");
			        sessionSave(&sessionList_vale, &logouts, SESSIONID_SAVE_PATH);
					if (loadflag) {
						clearSession(&sessionList_vale);
						printf("authenLogin::s clear sessions\n");
			        }
					printf("authenLogin::return 0\n");
					return 0;
			    } else {
                    // 删除此过期节点
                    printf("authenLogin::this sessionid is overdue\n");
					strncpy(username, authen_sessionid->username, size);
					*flag = 1;
				    delSession(&sessionList_vale, pos_sessions);
				    sessionSave(&sessionList_vale, &logouts, SESSIONID_SAVE_PATH);
					if (loadflag) {
						clearSession(&sessionList_vale);
						printf("authenLogin::f clear sessions\n");
			        }
					printf("authenLogin::return -1\n");
					return -1; //-1
			    }
		    } else {
		        strncpy(username, authen_sessionid->username, size);
				if (loadflag) {
					printf("authenLogin::s clear sessions\n");
                    clearSession(&sessionList_vale);
			    }
				printf("authenLogin::return 0\n");
				return 0;
			}
		}
	}
}

/*************************************************************
 *
 *  向网页发送数据 data为数组 (头)
 */
void sendRspHeadArray (webs_t wp, char_t *rspStatus, char_t *rspMsg)
{
	a_assert(websValid(wp));
	websWrite(wp, T("{\"status\":\"%s\",\"msg\":\"%s\",\"data\":["), rspStatus, rspMsg);	

}

/*************************************************************
 *
 *  向网页发送数据 data为数组 (尾)
 */
void sendRspFooterArray (webs_t wp)
{
	a_assert(websValid(wp));
	websWrite(wp, T("]}"));
}

/*************************************************************
 *
 *  向网页发送数据 data为对象 (头)
 */
void sendRspHeadObj (webs_t wp, char_t *rspStatus, char_t *rspMsg)
{
	a_assert(websValid(wp));
	websWrite(wp, T("{\"status\":\"%s\",\"msg\":\"%s\",\"data\":{"), rspStatus, rspMsg);	

}

/*************************************************************
 *
 *  向网页发送数据 data为对象 (尾)
 */
void sendRspFooterObj (webs_t wp)
{
	a_assert(websValid(wp));
	websWrite(wp, T("}}"));
}

/*************************************************************
 *
 *  goform发送响应头
 */
void goformHead (webs_t wp)
{
	websWrite(wp, T("HTTP/1.1 200 OK\n"));
	websWrite(wp, T("Pragma: no-cache\n"));
	websWrite(wp, T("Cache-control: no-cache\n"));
	websWrite(wp, T("Content-Type: text/html\n"));
	websWrite(wp, T("\n"));
}


