/****************************************************************
*  Copyright (c) 2017-2021,Kinan Tech. Co., Ltd.
*  Version     :    km1.0
*  Filename    :    authenBySessionid.c
*  Description :    authentic by sessionid 
*  Creator     :    zeed
*  Date        :    2017-9-20
*  History     :
*  <author>    <time>    <version>    <desc>
*  zeed        17/09/20   1.0          build this moudle
*
******************************************************************/

#include "authenBySessionid.h"

/*****************************************************************
*   
*  authentic by sessionid
*/
int authenBySessionid(char * sessionid, char * username, int size, int *flag)
{
	int            pos;                    //用户名对应sessions列表的位置
	int            loadflag = 0;
	time_t         curTime;                //当前时间
	sessionNode    *authenSession = NULL;  //初始化session节点获取sessionid
	sessionList    sessions;
	logoutTime_t   logouts;
	
    *flag = 0;
    // 打开文件加载数据到链表 
	sessions.sessionHead = sessionLoad(&logouts, 
	    &sessions.count, SESSIONID_SAVE_FILE);
    loadflag = 1;
	if (sessions.sessionHead == NULL) {
		fprintf(stderr, "authenBySessionid::sessionLoad NULL\n");
		return -1;
	}
	sessionNode  *tmpP = sessions.sessionHead;
	fprintf(stderr, "authenBySessionid::boundry---\n");
	while(tmpP){
		fprintf(stderr, "authenBySessionid::username=%s\n",
		    tmpP->username);
		fprintf(stderr, "authenBySessionid::sessionid=%s\n",
			tmpP->sessionid); 
		fprintf(stderr, "authenBySessionid::sessiontime=%lu\n",
		    tmpP->sessiontime);
		tmpP = tmpP->snpNext;
	}
	fprintf(stderr, "authenBySessionid::count=%d\n", sessions.count);
	
	pos = findSessionByid(&sessions, sessionid);
	fprintf(stderr, "authenBySessionid::pos=%d\n",pos);

 	if (pos < 0) {
		if (loadflag) {
            clearSession(&sessions);
		}
		return -1;//-1
	} else {
		authenSession = readSession(&sessions, pos);
		if (logouts.enable) {
            time(&curTime);
            if (curTime <= authenSession->sessiontime) {
                authenSession->sessiontime = curTime + logouts.times;
				sessionSave(&sessions, &logouts, SESSIONID_SAVE_FILE);
			    if (loadflag) {
                    clearSession(&sessions);
				}
                return 0;				
			} else {
                delSession(&sessions, pos);
				sessionSave(&sessions, &logouts, SESSIONID_SAVE_FILE);
				if (loadflag) {
                    clearSession(&sessions);
				}
				*flag = 1;
				return -1;
			}
		} else {
            if (loadflag) {
                clearSession(&sessions);
			}
			return 0;
		}         		 
	}
}

