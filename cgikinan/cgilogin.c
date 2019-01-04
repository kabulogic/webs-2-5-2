#include "../kinan/websSession.h"
#include "cgic.h"

int cgiMain(void)
{
	char         username[21] = {};
	char         erpt_Passwd[33] = {};  //已加密的密码
	char         decd_Passwd[17] = {};  //解密后的密码
	sessionList  *sessions = (session_t)malloc(sizeof(sessionList));
	
	/* 获取前端用户名和密码 */
    cgiFormString("username", username, sizeof(username));
	cgiFormString("password", erpt_Passwd, sizeof(erpt_Passwd));
	
	fprintf(stderr, "username:%s\n", username);
	fprintf(stderr, "password:%s\n", erpt_Passwd);
	
    /* 密码解密 */
	decString(erpt_Passwd, decd_Passwd, sizeof(decd_Passwd));
//	printf("decd_passwd:%s\n", decd_Passwd);
	
    /* 将用户名和密码传递给主控程序 */
   
	/* 判断是否通过验证 */
	
	/* 加载sessions.dt  文件到sessions链表中 */
	sessions->sessionHead = sessionLoad(&sessions->count, "sessions.dt");
	
	/* 遍历sessions链表 删除时间过期的节点 */
	travelDelSession(sessions);
	/* 生成新的节点sessionid 向链表尾部添加新节点 */
	pushTailSession(sessions, username);
	/* 将链表保存到文件sessions.dt中 */
	sessionSave(sessions, "sessions.dt");
	/* 将sessionid和验证结果发给网页 */
	cgiHeaderCookieSetString("CSESSIONID", 
			readSession(sessions,sessions->count-1)->sessionid,
			86400, "/", cgiServerName);

	cgiHeaderContentType("text/html");
	if(!strcmp(username, username))
    {
        if(!strcmp(decd_Passwd, decd_Passwd))
		{ 
			printf("{\"status\":\"true\",\"msg\":\"login success\"}");
		}
        else
        {
			printf("{\"status\":\"false\",\"msg\":\"login failed\"}");
        }
    }	
	return 0;
}
