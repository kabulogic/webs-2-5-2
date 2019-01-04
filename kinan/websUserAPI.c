/*************************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd. 
 *  Version     :   km1.0
 *  Filename    :   websUserAPI.c
 *  Description :   provides API for user manage
 *  Creator     :   zeed
 *  Date        :   2017-7-28
 *  History     :   
 *  <author>    <time>    <version >    <desc>
 *  zeed        17/07/28  1.0           build this moudle  
 *
 *************************************************************/

/************************ Descriptions ***********************/

/*
 *  用户管理模块，提供各项用户管理的API
 */

/************************* Includes ***************************/

#include	"websUserAPI.h"

/***************************************************************/
/*
 *	显示用户列表/查询用户/编辑用户发送的信息
 */

void formUserList (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formUserList ---\n");
	PeerHdr_t      phdr_userlist = {};
	MsgHdr_t       mhdr_userlist = {};
	AllUserPrew_t  userlist = {}; 
	char           *username, *usergroupname;
	int            i, user_pos = -1;  //查询位置   
	int            quit_flag = 0;

	//模拟
	int            nBytes, nBytesSent, row;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_userlist.cWho, 
	        sizeof(phdr_userlist.cWho), 
	        &quit_flag)) {
	        
#ifdef PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_userlist, NULL, 
		    wp->ipaddr, PEER_GET);

		initMsgHdr(&mhdr_userlist, CFG_USER);

		userlist.cCmd = USER_GET_ALL;

		INF_ClientTalkToKing_API(
			&phdr_userlist, 
			&mhdr_userlist, 
			(void*)userlist, 
			sizeof(userlist)
		);

 		//通过判断有无query请求 判断前端具体操作
		//无query 则请求用户列表
		//有query 从中获取前端请求的用户名 并发送对应的基本信息
		if (query == NULL || *query == '\0') {
			sendRspHeadArray(wp, AUTHEN_SUCCESS_MSG);
			for (i=0; i<userlist.cNum; i++) {
				websWrite (wp, T("{\"userName\":\"%s\","), 
					userlist.cUserName[i]);
				websWrite (wp, T("\"userStatus\":\"%s\","),
					userlist.cStatus[i]?"在线":"离线");
				websWrite (wp, T("\"userGroupName\":\"%s\","),
					userlist.cGrpName[i]);
				websWrite (wp, T("\"userGroupID\":\"%u\"}"),
					userlist.sGrpId[i]);
				if (i<userlist.cNum-1) {
					websWrite (wp, T(","));
				}
			} 
			sendRspFooterArray(wp);
		} else {
			username = websGetVar (wp, T("userN"), T(""));
			if (username == NULL || *username == '\0') {
				sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
			} else {
				//将用户与用户列表中的用户进行对比
				//如果有则flag对应其列表中的位置
				//如果没有则flag为初值-1
				for (i=0; i<(MAX_USER_GROUP_NUM<<3); i++) {
					if (!strcmp(username, userlist.cUserName)) {
						user_pos = i;
						break;
					}
				}
				if (-1 == user_pos) {
					sendRspHeadObj(wp, SRCH_USR_NOFND);
					sendRspFooterObj(wp);
				} else {
					sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
					websWrite (wp, T("\"username\":\"%s\","),
							userlist.cUserName[user_pos]);
					websWrite (wp, T("\"userstatus\":\"%s\","),
							userlist.cStatus[user_pos]?"在线":"离线");
					websWrite (wp, T("\"usergroupname\":\"%s\""),
							userlist.cGrpName[user_pos]);
					sendRspFooterObj(wp);
				}
			}
		}
#else
		nBytes = 1;
		nBytesSent = 0;

		username = umGetFirstUser();
		sendRspHeadArray(wp, AUTHEN_SUCCESS_MSG);
		while (username && (nBytes > 0))
		{
			row = umSearchStr("users","name",username);
			umReadStr("users", "group", row, &usergroupname);

			nBytes = websWrite(wp, T("{\"userName\":\"%s\","), username);
			nBytes += websWrite (wp, T("\"userStatus\":\"在线\","));
			nBytes += websWrite (wp, T("\"userGroupName\":\"%s\"}"),usergroupname);
			username = umGetNextUser(username);

			if(username && (nBytes > 0))
			{
				websWrite(wp, T(","));
			}
		}
		sendRspFooterArray(wp);
#endif			
	} else {
	    if (quit_flag) {
            Quit(phdr_userlist.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *	添加用户
 */
void formAddUser (webs_t wp, char_t* path, char_t* query)
{
	printf("--- kinan-formAddUser ---\n");
	PeerHdr_t   phdr_adduser = {};
	MsgHdr_t    mhdr_adduser = {};
	UserInfo_t  adduser = {};
	char_t      *adduser_ptr = NULL;
	char_t      passwd_clear[MAX_PSWD_LEN] = {};
	int         quit_flag = 0;
	
	char_t	    *username, *passwd, *group, *enabled;
	bool_t      bDisable;
	int	        nCheck;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_adduser.cWho, 
			sizeof(phdr_adduser.cWho), 
			&quit_flag)) {
			
#ifdef PROJECT_KM01_FINISHED
        adduser_ptr = websGetVar(wp, T("userName"), T(""));
        if (adduser_ptr == NULL || adduser_ptr == '\0') {
            goto FAIL;
		} else {
            if (strlen(adduser_ptr) < 6 || strlen(adduser_ptr) > 20) {
                goto FAIL;
			} else {
                initPeerHdr(&phdr_adduser, NULL, wp->ipaddr, PEER_SET);
			    initMsgHdr(&mhdr_adduser, CFG_USER);
   		        adduser.Cfg.cType = USER_ADD;
				strncpy(adduser.Cfg.Name, 
					adduser_ptr, sizeof(adduser.Cfg.Name));
			}
		}
		printf("formAddUser::Name-->>%s\n", adduser.Cfg.Name);
		
        adduser_ptr = websGetVar(wp, T("password"), T(""));
		if (adduser_ptr == NULL || *adduser_ptr == '\0') {
            goto FAIL;
		} else {
            decString(adduser_ptr, passwd_clear, sizeof(passwd_clear));
			if (*passwd_clear == '\0') {
                goto FAIL;
			}
			strncpy(adduser.Cfg.Pswd, passwd_clear, sizeof(adduser.Cfg.Pswd));
		}
		printf("formAddUser::Pswd-->>%s\n", adduser.Cfg.Pswd);
		
		adduser_ptr = websGetVar(wp, T("groupId"), T(""));
        if (adduser_ptr == NULL || *adduser_ptr == '\0') {
            goto FAIL;
		} else {
		    if (strlen(adduser_ptr) < 6 || strlen(adduser_ptr) > 20) {
                goto FAIL;
			} else {
                strncpy(adduser.Cfg.sGroup, adduser_ptr, sizeof(adduser.Cfg.sGroup));
			}
		}
		printf("formAddUser::sGroup-->>%s\n", adduser.Cfg.sGroup);
		
		INF_ClientTalkToKing_API(
			&phdr_adduser, 
			&mhdr_adduser,
			(void*)&adduser, 
			sizeof(adduser)
		);
#else
		username = websGetVar(wp, T("userName"), T("")); 
		passwd = websGetVar(wp, T("password"), T("")); 
		group = websGetVar(wp, T("groupId"), T("")); 
		printf("group:%s\n",group);
		enabled = websGetVar(wp, T("load"), T("")); 
		printf("passwd:%s\n", passwd);

		if(0 < strlen(username) && 
			strlen(username) <= MAX_USRN_LEN &&
			strlen(passwd)%16 == 0 &&
			strlen(group) > 0)
		{
			printf("done!\n");
		}
		else
		{
			printf("not yet\n");
		}
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);

		if (enabled && *enabled && (gstrcmp(enabled, T("1")) == 0)) 
		{
			bDisable = FALSE;
		} 
		else 
		{
			bDisable = TRUE;
		}

		nCheck = umAddUser(username, passwd, group, 0, bDisable);
		if (nCheck != 0) {
			char_t * strError;

			switch (nCheck) {
				case UM_ERR_DUPLICATE:
					strError = T("User already exists.");
					break;

				case UM_ERR_BAD_NAME:
					strError = T("Invalid user name.");
					break;

				case UM_ERR_BAD_PASSWORD:
					strError = T("Invalid password.");
					break;

				case UM_ERR_NOT_FOUND:
					strError = T("Invalid or unselected group.");
					break;

				default:
					strError = T("Error writing user record.");
					break;
			}

			websWrite(wp, T("Unable to add user, \"%s\".  %s"),
					username, strError);
		} else {
			if(umCommit(NULL) != 0)			
			{
				printf("ERROR: Unable to save user configuration.\n");	
			}else
			{
				websWrite(wp, T("User, \"%s\" was successfully added."),
						username);
			}
		}
		sendRspFooterObj(wp);
#endif
	} else {
	    if (quit_flag) {
            Quit(phdr_adduser.cWho, wp->ipaddr);
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

/************************************************************/
/*
 *	删除用户组
 *	分解query 分离出要删除的用户组名
 *	del_fail_num == -1 表示参数错误
 *	del_fail_num == 0  表示删除成功
 *	del_fail_num > 0   表示删除失败
 *		               并将失败的用户名存入failName中
 */

void formDelUserGroup (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formDelUserGroup ---\n");
	PeerHdr_t  phdr_usergroup_del = {};
	MsgHdr_t   mhdr_usergroup_del = {};
	UserGrp_t  usergroup_del = {};
	char_t     *query_ptr = NULL;
	char_t     *save_ptr = NULL;
	char_t     *usergrp_keyvalue = NULL;
	char_t     *group_key = NULL, *group_value = NULL;  
	char       failName[MAX_GRP_NUM][MAX_GRPN_LEN] = {};  
	int        del_fail_num = 0;   
	int        j = 0;
	int        quit_flag = 0;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
			phdr_usergroup_del.cWho, 
			sizeof(phdr_usergroup_del.cWho),
			&quit_flag)) {
		if (query == NULL || *query == '\0') {
			sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
		} else {
/*
		   
*/
    		query_ptr = query;
			while ((usergrp_keyvalue = strtok_r(query_ptr, "&", &save_ptr)) 
		        != NULL) {   
				if (-1 == parseKeyValue(usergrp_keyvalue, &group_key, &group_value, "=")) {
                    //分解失败 参数不符合分解规范
					printf("formDelUserGroup::delete group error!\n");
					del_fail_num = -1;
					break;
				} else {
					printf("formDelUserGroup::valueGRP:%s\n", group_value);

#ifdef PROJECT_KM01_FINISHED
                    initPeerHdr(&phdr_usergroup_del, NULL, 
					   wp->ipaddr, PEER_SET);

		            initMsgHdr(&mhdr_usergroup_del, CFG_USER_GRP);

		            usergroup_del.cCmd = USER_GRP_DEL;

					strncpy(usergroup_del.Name, group_value, 
							sizeof(usergroup_del.Name));

					INF_ClientTalkToKing_API(&phdr_usergroup_del,
							&mhdr_usergroup_del, (void*)&usergroup_del,
							sizeof(usergroup_del));
#else
					if((group_value == NULL) || (*group_value == '\0'))
					{
						del_fail_num = -1;
						break;
					}
					else 
					{	
						if(umGetGroupInUse(group_value))
						{
							strncpy(failName[del_fail_num], group_value, sizeof(failName[del_fail_num]));
							del_fail_num++;
						}
						else
						{
							if(umDeleteGroup(group_value) != 0)
							{
								strncpy(failName[del_fail_num], group_value, sizeof(failName[del_fail_num]));
								del_fail_num++;

							}
							else
							{
								if(umCommit(NULL) != 0)
								{
									printf("save group failed\n");
								}
							}
						}
					}
					query_ptr = NULL;
					memset (group_value, 0, sizeof(group_value));
				}
			}
			printf("del_fail_num:%d\n", del_fail_num);
			if(0 == del_fail_num)
			{
				sendRspHeadObj(wp, DEL_GRP_SUCCESS);
				sendRspFooterObj(wp);
			}
			else if(-1 == del_fail_num)
			{
				sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
			}
			else 
			{
				websWrite(wp, T("{\"status\":\"false\",\"msg\":\"删除"));
				for(j=0; j<del_fail_num; j++)
				{
					websWrite(wp, T("%s"), failName[j]);
					if(j < del_fail_num-1)
					{
						websWrite(wp, T(","));
					}
				}
				websWrite(wp, T("用户组失败\",\"data\":{}}"));
			}
		}
#endif			
	} else {
	    if (quit_flag) {
            Quit(phdr_usergroup_del.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *  用户组列表/查询用户组/(添加用户页面需要用到)
 */

void formUserGroupList (webs_t wp, char_t *path, char_t *query)
{
	printf("---- kinan-formUserGroupList ----\n");
	PeerHdr_t         phdr_grouplist = {};
	MsgHdr_t          mhdr_grouplist = {};
	AllUserGrpPrew_t  grouplist = {};
	char_t            *groupname = NULL;
	int               i, flag = -1;
	int               quit_flag = 0;

	//模拟
	char              *userGroupName;
	int               portAccess, userManager, diviceSetting, securityManager;
	int               systemMaintenance;
	int               nBytes, nBytesSent, row;
	nBytes = 1;
	nBytesSent = 0;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_grouplist.cWho, 
			sizeof(phdr_grouplist.cWho),
			&quit_flag
			)) {
			
#ifdef PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_grouplist, NULL, wp->ipaddr, 
			PEER_GET);

		initMsgHdr(&mhdr_grouplist, CFG_USER_GRP);

		grouplist.cCmd = USER_GRP_GET_ALL;

		INF_ClientTalkToKing_API(&phdr_grouplist, 
			&mhdr_grouplist, 
			(void*)&grouplist, 
			sizeof(grouplist));
/*
 *		通过query判断前端操作
 *		无query 发送用户组列表
 *		有query 具体某个用户组信息 发送对应的用户组信息
 */
		if (query == NULL || *query == '\0') {
			sendRspHeadArray(wp, AUTHEN_SUCCESS_MSG);
			for (i=0; i<grouplist.cNum; i++) {
				websWrite (wp, T("{\"userGroupName\":\"%s\","), 
						grouplist.Name[i]);
				websWrite (wp, T("\"userGroupID\":\"%u\"}"),
						grouplist.sID[i]);
				if (i<grouplist.cNum-1) {
					websWrite (wp, T(","));
				}
			}
			sendRspFooterArray(wp);
		} else {
			groupname = websGetVar (wp, T("userG"), T(""));
			if (groupname == NULL || *groupname == '\0') {
				goto FAIL;
			} else {
				for (i=0; i<MAX_USER_GROUP_NUM; i++) {
					if (!strcmp(groupname, grouplist.Name[i])) {
						flag = i;
						break;
					}
				}
				
				if (flag == -1) {
					sendRspHeadObj(wp, SRCH_GRP_NOFND);
					sendRspFooterObj(wp);
				} else {
					//发送flag对应的数据
					sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
					websWrite(wp, T("\"usergroupname\":\"%s\","),
							grouplist.Name[flag]);
					websWrite(wp, T("\"usergroupid\":\"%s\""),
							grouplist.sID[flag]);
				}
			}
		}
#else			
		sendRspHeadArray(wp, AUTHEN_SUCCESS_MSG);

		userGroupName = umGetFirstGroup();

		i = 0;
		while (userGroupName && (nBytes > 0))
		{
			row = umSearchStr("groups","name", userGroupName);
			portAccess = umReadInt("groups", "portAccess", row);
			userManager = umReadInt("groups", "userManager", row);
			diviceSetting = umReadInt("groups", "diviceSetting", 
					row);
			securityManager = umReadInt("groups", "securityManager",
					row);
			systemMaintenance = umReadInt("groups", 
					"systemMaintenance", row);

			nBytes = websWrite(wp, T("{\"userGroupName\":\"%s\","),userGroupName);
			nBytes = websWrite(wp, T("\"userGroupID\":\"%d\","), i+1);
			nBytes += websWrite(wp, T("\"portAccess\":\"%d\","),portAccess);
			nBytes += websWrite(wp, T("\"userManager\":\"%d\","),userManager);
			nBytes += websWrite(wp, T("\"diviceSetting\":\"%d\","),diviceSetting);
			nBytes += websWrite(wp, T("\"securityManager\":\"%d\","),securityManager);
			nBytes += websWrite(wp, T("\"systemMaintenance\":\"%d\"}"),systemMaintenance);
			userGroupName = umGetNextGroup(userGroupName);
			i++;
			nBytesSent += nBytes;
			if(userGroupName && (nBytes > 0))
			{
				websWrite(wp, T(","));
			}
		}
		sendRspFooterArray(wp);
#endif			
	} else {
	    if (quit_flag) {
            Quit(phdr_grouplist.cWho, wp->ipaddr);
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
 *	添加用户组
 */

void formAddUserGroup (webs_t wp, char_t* path, char_t* query)
{
	printf("----kinan-formAddUserGroup----\n");
	PeerHdr_t  phdr_usergroup_add = {};
	MsgHdr_t   mhdr_usergroup_add = {};
	UserGrp_t  usergroup_add = {};
	char_t     *usergroup_add_ptr = NULL;
	int        quit_flag = 0;

	//模拟
	char       *group, *userGroupName, *portAccess, *userManager;
	char       *diviceSetting, *securityManager, *systemMaintenance;
	char       *ok, *pChar;
	int        nCheck, nBytes, nBytesSent;
	bool_t     bDisable, bportA, buserM, bdiviceS, bsecurityM, bsystemM;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_usergroup_add.cWho, 
			sizeof(phdr_usergroup_add.cWho), 
			&quit_flag)) {
				
#ifdef  PROJECT_KM01_FINISHED
        usergroup_add_ptr = websGetVar(wp, T("userGroupName"), T(""));
        if (usergroup_add_ptr == NULL || *usergroup_add_ptr == '\0') {
            goto FAIL;
		} else {
            if (strlen(usergroup_add_ptr) < 6 || 
					strlen(usergroup_add_ptr) > 20) {
                goto FAIL;
			} else {
/*                initPeerHdr(&phdr_usergroup_add, 
					NULL, 
					wp->ipaddr, 
					PEER_SET);
				initMsgHdr(&mhdr_usergroup_add, CFG_USER_GRP);*/
				usergroup_add.cCmd = USER_GRP_ADD;
				strncpy(usergroup_add.Name, 
					usergroup_add_ptr, 
					sizeof(usergroup_add.Name));
			}
		}
        printf("formAddUserGroup::usergroupname-->>%s\n",
            usergroup_add.Name);

		usergroup_add_ptr = websGetVar(wp, T("portAccess"), T(""));
		if (usergroup_add_ptr == NULL || *usergroup_add_ptr == '\0') {
            goto FAIL;
		} else {
            if (!strcmp(usergroup_add_ptr, "1")) {
                usergroup_add.privilege.bPort = 1;
			} else {
                usergroup_add.privilege.bPort = 0;
			}  
		}

		usergroup_add_ptr = websGetVar(wp, T("userManager"), T(""));
		if (usergroup_add_ptr == NULL || *usergroup_add_ptr == '\0') {
            goto FAIL;
		} else {
            if (!strcmp(usergroup_add_ptr, "1")) {
                usergroup_add.privilege.bUserMng = 1;
			} else {
                usergroup_add.privilege.bUserMng = 0;
			}  
		}
		
		usergroup_add_ptr = websGetVar(wp, T("diviceSetting"), T(""));
		if (usergroup_add_ptr == NULL || *usergroup_add_ptr == '\0') {
            goto FAIL;
		} else {
            if (!strcmp(usergroup_add_ptr, "1")) {
                usergroup_add.privilege.bSysMan = 1;
			} else {
                usergroup_add.privilege.bSysMan = 0;
			}  
		}
		
		usergroup_add_ptr = websGetVar(wp, T("securityManager"), T(""));
		if (usergroup_add_ptr == NULL || *usergroup_add_ptr == '\0') {
            goto FAIL;
		} else {
            if (!strcmp(usergroup_add_ptr, "1")) {
                usergroup_add.privilege.bSecure = 1;
			} else {
                usergroup_add.privilege.bSecure = 0;
			}  
		}
		
		usergroup_add_ptr = websGetVar(wp, T("systemMaintenance"), T(""));
		if (usergroup_add_ptr == NULL || *usergroup_add_ptr == '\0') {
            goto FAIL;
		} else {
            if (!strcmp(usergroup_add_ptr, "1")) {
                usergroup_add.privilege.bSysMaintenance = 1;
			} else {
                usergroup_add.privilege.bSysMaintenance = 0;
			}  
		}
		printf("formAddUserGroup::privilege-->>%d\n",
		    usergroup_add.privilege);

/*        INF_ClientTalkToKing_API(&phdr_usergroup_add, 
			&mhdr_usergroup_add, 
			&usergroup_add,
			sizeof(usergroup_add));*/
#else			
		userGroupName = websGetVar(wp, T("userGroupName"), T(""));
		portAccess = websGetVar(wp, T("portAccess"), T(""));
		userManager = websGetVar(wp, T("userManager"), T(""));
		diviceSetting = websGetVar(wp, T("diviceSetting"), T(""));
		securityManager = websGetVar(wp, T("securityManager"), T(""));
		systemMaintenance = websGetVar(wp, T("systemMaintenance"), T(""));
		ok = websGetVar(wp, T("ok"), T(""));
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);

		/****判断要添加的用户组名是否与已有的用户组重名****/
		if ((userGroupName == NULL) || (*userGroupName == 0)) 
		{
			printf("No Group Name was entered.\n");
		} 
		else if (umGroupExists(userGroupName)) 
		{
			websWrite(wp, 
					T("\"ERROR\": \"%s is already exists\""), 
					userGroupName);
		} 
		else 
		{
			if (portAccess && *portAccess 
					&& (gstrcmp(portAccess, T("1")) == 0)) 
			{
				bportA = TRUE;
			} 
			else 
			{
				bportA = FALSE;
			}
			if (userManager && *userManager 
					&& (gstrcmp(userManager, T("1")) == 0)) 
			{
				buserM = TRUE;
			} 
			else 
			{
				buserM = FALSE;
			}
			if (diviceSetting && *diviceSetting 
					&& (gstrcmp(diviceSetting, T("1")) == 0)) 
			{
				bdiviceS = TRUE;
			} 
			else 
			{
				bdiviceS = FALSE;
			}
			if (securityManager && *securityManager 
					&& (gstrcmp(securityManager, T("1")) == 0)) 
			{
				bsecurityM = TRUE;
			} 
			else 
			{
				bsecurityM = FALSE;
			}
			if (systemMaintenance && *systemMaintenance 
					&& (gstrcmp(systemMaintenance, T("1")) == 0)) 
			{
				bsystemM = TRUE;
			} 
			else 
			{
				bsystemM = FALSE;
			}
			nCheck = umAddGroup(userGroupName, bportA, buserM, \
					bdiviceS, bsecurityM, bsystemM);
			if (nCheck != 0) 
			{
				printf("Unable to add group, \"%s\", code: %d \n",
						userGroupName, nCheck);
			} 
			else 
			{
				printf("Group, \"%s\" was successfully added.\n",
						userGroupName);
			}
			if (umCommit(NULL) != 0) 
			{
				printf("ERROR: Unable to save user configuration.\n");
			} 
			else 
			{
				printf("User configuration was saved successfully.\n");
				websWrite(wp, 
						T("\"SUCCESS\": \"create user group successful\"")
						, userGroupName);
			}
		}
		sendRspFooterObj(wp);
#endif			
	} else {
	    if (quit_flag) {
            Quit(phdr_usergroup_add.cWho, wp->ipaddr);
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

/************************** Code ******************************/
/*
 *	修改密码
 */

void formChaPasswd (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formChaPasswd----\n");
	PeerHdr_t   phdr_passwd_change = {};
	MsgHdr_t    mhdr_passwd_change = {};
	UserInfo_t  passwd_change = {};
	char_t      *passwd_ptr = NULL;
	char_t      passwd_old_clear[MAX_PSWD_LEN] = {};
	char_t      passwd_new_clear[MAX_PSWD_LEN] = {};
    int         quit_flag = 0;

//  模拟 从文件中获取原密码	
	int         fd, sta;    
	char_t      uPasswd[MAX_PSWD_LEN] = {};             
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
			phdr_passwd_change.cWho, 
			sizeof(phdr_passwd_change.cWho),
			&quit_flag)) {	
        passwd_ptr = websGetVar (wp, T("oldPassword_check"), T(""));
		if (passwd_ptr == NULL || *passwd_ptr == '\0') {
            goto FAIL;
		} else {
            decString(
				(const char*)passwd_ptr, 
				passwd_old_clear, 
				sizeof(passwd_old_clear));
		}
		printf("formChaPasswd::passwd_old_clear-->>%s\n",
		    passwd_old_clear);
		
		passwd_ptr = websGetVar (wp, T("password"), T(""));
		if (passwd_ptr == NULL || *passwd_ptr == '\0') {
            goto FAIL;
		} else {
            decString(
				(const char*)passwd_ptr, 
				passwd_new_clear, 
				sizeof(passwd_new_clear));
		}
		printf("formChaPasswd::passwd_new_clear-->>%s\n",
		    passwd_new_clear);
		
#ifdef PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_passwd_change, 
			NULL, wp->ipaddr, PEER_SET);

		initMsgHdr(&mhdr_passwd_change, CFG_USER);

		passwd_change.Cfg.cType = USER_MOD;
		strncpy(passwd_change.Cfg.Name, 
			phdr_passwd_change.cWho, 
			sizeof(passwd_change.Cfg.Name));
		strncpy(passwd_change.Cfg.Pswd, 
			passwd_old_clear,
			sizeof(passwd_change.Cfg.Pswd));
		strncpy(passwd_change.Cfg.newPswd, 
			passwd_new_clear,
			sizeof(passwd_change.Cfg.newPswd));

		INF_ClientTalkToKing_API(&phdr_passwd_change, 
			&mhdr_passwd_change, 
			(void*)passwd_change, 
			sizeof(UserInfo_t));
#else			
		fd = open("pd.txt", O_CREAT|O_RDWR, 0664);
		if (fd == -1)
			perror("open pd.txt");
		sta = read(fd, uPasswd, sizeof(uPasswd));

		if(uPasswd[strlen(uPasswd)-1] == '\n')
		{
			uPasswd[strlen(uPasswd)-1] = '\0';
		}
		close(fd);

		if(!strcmp(uPasswd, passwd_old_clear))
		{
			fd = open("pd.txt", O_CREAT|O_RDWR|O_TRUNC, 0664);
			sta = write(fd, passwd_new_clear, strlen(passwd_new_clear));
			close(fd);
			sendRspHeadObj(wp, SET_SUCCESS_MSG);
			sendRspFooterObj(wp);
		}
		else
		{
			sendRspHeadObj(wp, PASSWD_ERRO_MSG);
			sendRspFooterObj(wp);
		}
#endif				
	} else {
	    if (quit_flag) {
            Quit(phdr_passwd_change.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	/*响应结束*/
	websDone(wp, 200);
	return ;
FAIL:
	sendRspHeadObj(wp, ARG_ERROR_MSG);
	sendRspFooterObj(wp);
	websDone(wp, 200);
	return;

}

/************************************************************/
/*
 *	删除用户 
 */

void formDelUser (webs_t wp, char_t* path, char_t* query)
{
	printf("----kinan-formDeleteUser----\n");
	char        *keyValue = NULL;    
	char        *keyUsr = NULL, *valueUsr = NULL;     
	char        failName[MAX_GRP_NUM<<3][MAX_USRN_LEN] = {}; 
	char        *str = NULL, *saveptr = NULL;
	int         del_fail_num = 0;		
	int         j = 0;
	PeerHdr_t   pHdr_delUser = {};
	MsgHdr_t    mHdr_delUser = {};
	UserInfo_t  delUser = {};
	int         quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, 
		    pHdr_delUser.cWho, 
			sizeof(pHdr_delUser.cWho), 
			&quit_flag)) {
/*
 *		判断是否有query参数 
 *		无：表示参数传递失败
 */
		if(query == NULL || *query == '\0')
		{
			sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
		}
		else
		{
			str = query;			
/*
			initPeerHdr(&pHdr_delUser, requestUser, wp->ipaddr, 
					   PEER_SET);

			initMsgHdr(&mHdr_delUser, CFG_USER);

			delUser.Cfg.cType = USER_DEL;
*/			

/*
 *			分解query 分离出要删除的用户
 *			如果删除成功则del_fail_num为0
 *			如果参数错误则del_fail_num为-1
 *			如果删除是被则将删除失败的用户名存入failName中 
 *				并由del_fail_num 记录
 */
			while((keyValue = strtok_r(str, "&", &saveptr)) != NULL)
			{   
				if(-1 == parseKeyValue(keyValue, &keyUsr, &valueUsr, "="))
				{
					printf("delete user error!\n");
					del_fail_num = -1;
					break ;
				}
				else
				{
#ifdef PROJECT_KM01_FINISHED
					strncpy(delUser.Cfg.Name, valueUsr, 
							sizeof(delUser.Cfg.Name));

					INF_ClientTalkToKing_API(&pHdr_delUser,
							&mHdr_delUser, (void*)&delUser,
							sizeof(delUser));
#else
					if(valueUsr == NULL || *valueUsr == '\0')
					{
						del_fail_num = -1;
						break;
					}
					else
					{
						if (umDeleteUser(valueUsr) != 0)
						{   
							strncpy(failName[del_fail_num], valueUsr, sizeof(failName[del_fail_num]));	
							del_fail_num++;
						} 
						else
						{
							if(umCommit(NULL) != 0)
							{
								printf("User deleted, save failed\n");
							}
						}
						str = NULL;
						memset(valueUsr, 0, sizeof(valueUsr));
					}
				}
			}
			if(0 == del_fail_num)
			{
				sendRspHeadObj(wp, DEL_USR_SUCCESS);
				sendRspFooterObj(wp);
			}
			else if(-1 == del_fail_num)
			{
				sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
			}
			else
			{
				websWrite(wp, T("{\"status\":\"false\",\"msg\":\"删除"));
				for(j=0; j<del_fail_num; j++)
				{
					websWrite(wp, T("%s"), failName[j]);
					if(j< del_fail_num-1)
					{
						websWrite(wp, T(","));
					}
				}
				websWrite(wp, T("用户失败\",\"data\":{}}"));
			}
		}
#endif			
	}
	else
	{
	    if (quit_flag) {
            Quit(pHdr_delUser.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *	添加用户页面 发送用户组信息 (改成/goform/UserGroupList)
 */

void formAddUserInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formAddUserInfo\n");
	char              *userGroupName = NULL;
	int               row = 0, nBytes = 1;
	PeerHdr_t         pHdr_userGrpAll = {};
	MsgHdr_t          mHdr_userGrpAll = {};
	AllUserGrpPrew_t  userGrpAll = {};
    int               quit_flag = 0;
	
	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, pHdr_userGrpAll.cWho, 
				sizeof(pHdr_userGrpAll.cWho),
				&quit_flag))
	{
#ifdef FINISH			
		initPeerHdr(pHdr_userGrpAll, NULL, wp->ipaddr, 
				PEER_GET);

		initMsgHdr(mHdr_userGrpAll, CFG_USER_GRP);

		userGrpAll.cCmd = USER_GRP_GET_ALL;

		INF_ClientTalkToKing_API(&pHdr_userGrpAll,
				&mHdr_userGrpAll, (void*)&userGrpAll,
				sizeof(userGrpAll));
#else
		sendRspHeadArray(wp, AUTHEN_SUCCESS_MSG);
		userGroupName = umGetFirstGroup();

		while (userGroupName && (nBytes > 0))
		{
			row = umSearchStr("groups","name", userGroupName);
			nBytes = websWrite(wp,
					T("{\"userGroupName\":\"%s\"}"),userGroupName);
			userGroupName = umGetNextGroup(userGroupName);
			if(userGroupName && (nBytes > 0))
			{
				websWrite(wp, T(","));
			}
		}
		sendRspFooterArray(wp);
#endif			
	}
	else
	{
	    if (quit_flag) {
            Quit(pHdr_userGrpAll.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone (wp, 200);
}

/****************************************************************/
/*
 *  编辑用户组(未完待续)
 */

void formEditUserGroup (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formEditUserGroup\n");
	char       *portAccess, *userManager;
	char       *diviceSetting, *securityManager, *systemMaintenance;
	char       *editUserGroup = NULL;
	int        result = 0;
	int        row;
	PeerHdr_t  pHdr_editUserGrp = {};
	MsgHdr_t   mHdr_editUserGrp = {};
	UserGrp_t  editUserGrp = {};
	int        quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, pHdr_editUserGrp.cWho, 
				sizeof(pHdr_editUserGrp.cWho),
				&quit_flag))
	{

#ifdef FINISH
		portAccess = websGetVar(wp, T("portAccess"), T(""));
		userManager = websGetVar(wp, T("userManager"), T(""));
		diviceSetting = websGetVar(wp, T("diviceSetting"), T(""));
		securityManager = websGetVar(wp, T("securityManager"), T(""));
		systemMaintenance = websGetVar(wp, T("systemMaintenance"), T(""));

		initPeerHdr(&pHdr_editUserGrp, requestUser, wp->ipaddr, PEER_SET);

		initMsgHdr(&mHdr_editUserGrp,  CFG_USER_GRP);

		editUserGrp.cCmd = USER_GRP_MOD;
		strncpy(editUserGrp.Name, editUserGroup, sizeof(editUserGrp.Name));
		if(portAccess && *portAccess && 
				(!strcmp(portAccess, "1")))
		{
			addUserGrp.privilege |= PRI_PORT; 
		}
		if(userManager && *userManager && 
				(!strcmp(userManager, "1")))
		{
			addUserGrp.privilege |= PRI_USERMAN;
		}
		if(diviceSetting && *diviceSetting && 
				(!strcmp(diviceSetting, "1")))
		{
			addUserGrp.privilege |= PRI_SYSMAN;
		}
		if(securityManager && *securityManager && 
				(!strcmp(securityManager, "1")))
		{
			addUserGrp.privilege |= PRI_DATAMAN;
		}

		INF_ClientTalkToKing_API(&pHdr_addUserGrp, &mHdr_addUserGrp, 
				(void*)addUserGrp, sizeof(UserGrp_t));
#else			
		//获取编辑用户名
		editUserGroup = websGetVar (wp, T("userG"), T(""));
		portAccess = websGetVar(wp, T("portAccess"), T(""));
		userManager = websGetVar(wp, T("userManager"), T(""));
		diviceSetting = websGetVar(wp, T("diviceSetting"), T(""));
		securityManager = websGetVar(wp, T("securityManager"), T(""));
		systemMaintenance = websGetVar(wp, T("systemMaintenance"), T(""));
		printf("name:%s\n", editUserGroup);
		printf("port:%s\n", portAccess);
		printf("usermanager:%s\n", userManager);
		printf("diviceSet:%s\n", diviceSetting);
		printf("securityM:%s\n", securityManager);
		printf("systemMaintenance:%s\n", systemMaintenance);

		row = umSearchStr ("groups", "name", editUserGroup);
		umWriteInt("groups", "portAccess", row, atoi(portAccess));
		umWriteInt("groups", "userManager", row, atoi(userManager));
		umWriteInt("groups", "diviceSetting", row, atoi(diviceSetting));
		umWriteInt("groups", "securityManager", row, atoi(securityManager));
		umWriteInt("groups", "systemMaintenance", row, atoi(systemMaintenance));
		umCommit(NULL);
		//编辑用户信息
		sendRspHeadObj(wp, "true", "设置成功");
		sendRspFooterObj(wp);
		//将结果发前端
#endif

	}
	else
	{
	    if (quit_flag) {
            Quit(pHdr_editUserGrp.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/****************************************************************/
/*
 *  编辑用户(未完待续)
 */

void formEditUser (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formEditUser\n");
	char        *oldPasswd;
	char        *newPasswd, *confirmPasswd;
	char        *newUsergroup;
	char        *editUserName = NULL;
	char        oldPsswdDec[MAX_PSWD_LEN] = {}, newPsswdDec[MAX_PSWD_LEN] = {};
	char        conPsswdDec[MAX_PSWD_LEN] = {};
	int         result = 0;
	PeerHdr_t   pHdr_editUser = {};
	MsgHdr_t    mHdr_editUser = {};
	UserInfo_t  editUser = {};
	int         quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, pHdr_editUser.cWho,
				sizeof(pHdr_editUser.cWho),
				&quit_flag))
	{
		editUserName = websGetVar (wp, T("userN"), T(""));
#ifdef FINISH
		/*只允许改变密码*/
		initPeerHdr(&pHdr_editUser, NULL, wp->ipaddr, 
				PEER_SET);

		initMsgHdr(&mHdr_editUser,USER_MOD);

#else			
		//获取编辑用户名
		//newUsername = websGetVar (wp, T("userName"), T(""));

		oldPasswd = websGetVar (wp, T("old_password"), T(""));
		newPasswd = websGetVar (wp, T("new_password"), T(""));
		confirmPasswd = websGetVar (wp, T("password"), T(""));
		printf("ol:%s\n", oldPasswd);
		printf("ne:%s\n", newPasswd);

		decString(oldPasswd, oldPsswdDec, sizeof(oldPsswdDec));
		decString(newPasswd, newPsswdDec, sizeof(newPsswdDec));
		decString(confirmPasswd, conPsswdDec, sizeof(conPsswdDec));

		//			newUsergroup = websGetVar (wp, T("groupId"), T(""));
		printf("name:%s\n", editUserName);
		printf("oldpswd:%s\n", oldPsswdDec);
		printf("newpswd:%s\n", newPsswdDec);
		//编辑用户信息
		//1.判断密码是否符合规定
		if(!strcmp(newPsswdDec, conPsswdDec))
		{
			//2.判断用户是否存在
			//3.修改用户密码
			if((result=umSetUserPassword(editUserName, newPsswdDec))<0)
			{
				printf("result:%d\n",result);
				sendRspHeadObj(wp, "false", "密码设置失败");
				sendRspFooterObj(wp);
				websDone(wp, 200);
				return;
			}
/*			//4.修改用户组
			if(umSetUserGroup(editUsername, newUsergroup) < 0)
			{
				sendRspHeadObj(wp, "false", "用户组设置失败");
				sendRspFooterObj(wp);
				websDone(wp, 200);
				return;
			}
			//5.修改用户名
			if(umSetUserName(editUsername, newUsername) < 0)
			{
			sendRspHeadObj(wp, "false", "用户名设置失败");
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return;
			}
*/				
			else if(umCommit(NULL) != 0)
			{
				sendRspHeadObj(wp, "false", "设置失败");
				sendRspFooterObj(wp);
				websDone(wp, 200);
				return;
			}
			else
			{
				sendRspHeadObj(wp, "true", "设置成功");
				websWrite(wp, T("\"result\":\"success\""));
				sendRspFooterObj(wp);
			}
			//将结果发前端
		}
#endif		

	}
	else
	{
	    if (quit_flag) {
            Quit(pHdr_editUser.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/***************************************************************/
/*
 *  test编辑用户页面要发送的数据 
 */

void formEditUserInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formEditUserInfo\n");
	char   *editUserName = NULL, *editUserGroup = NULL;
	char   tmp[16] = {};
	int    row = 0, nBytes = 1;
	char   *userGroupName = NULL;
	char   requestUser[MAX_USRN_LEN] = {};
	int    quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, requestUser, sizeof(requestUser), &quit_flag))
	{
		editUserName = websGetVar (wp, T("userN"), T(""));
		editUserGroup = websGetVar (wp, T("userG"), T(""));

		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
		websWrite(wp, T("\"userInfo\":{"));
		websWrite(wp, T("\"edituser\":\"%s\","), editUserName);
		websWrite(wp, T("\"editgroup\":\"%s\""), editUserGroup);
		websWrite(wp, T("},"));
		websWrite(wp, T("list:["));

		userGroupName = umGetFirstGroup();
		while (userGroupName && (nBytes > 0))
		{
			row = umSearchStr("groups","name", userGroupName);
			nBytes = websWrite(wp,
					T("{\"userGroupName\":\"%s\"}"), \
					userGroupName);
			userGroupName = umGetNextGroup(userGroupName);
			if(userGroupName && (nBytes > 0))
			{
				websWrite(wp, T(","));
			}
		}
		websWrite(wp, T("]"));
		sendRspFooterObj(wp);
	}
	else
	{
	    if (quit_flag) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/***************************************************************/
/*
 *  编辑用户组对应信息 (未完待续)
 */

void formEditUserGroupInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formEditUserGroupInfo\n");
	char        *editUserGroup = NULL;
	char        tmp[16] = {};
	int         row = 0, nBytes = 1;
	int         portAccess, userManager;
	int         diviceSetting, securityManager, systemMaintenance;
	PeerHdr_t   pHdr_editGrpInfo = {};
	MsgHdr_t    mHdr_editGrpInfo = {};
	UserGrp_t   editGrpInfo = {};
	int         quit_flag = 0;
		
	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, pHdr_editGrpInfo.cWho, 
				sizeof(pHdr_editGrpInfo.cWho), &quit_flag))
	{
#ifdef FINISH
		initPeerHdr(&pHdr_editGrpInfo, requestUser, wp->ipaddr, PEER_GET);

		initMsgHdr(&mHdr_editGrpInfo, CFG_USER_GRP);

		editGrpInfo.cCmd = USER_GRP_GET;
		strncpy(editGrpInfo.sID, );
#else			
		editUserGroup = websGetVar (wp, T("userG"), T(""));
		row = umSearchStr("groups", "name", editUserGroup);
		userManager = umReadInt("groups", "userManager", row);
		portAccess = umReadInt("groups", "portAccess", row);
		diviceSetting = umReadInt("groups", "diviceSetting", row);
		securityManager = umReadInt("groups", "securityManager", row);
		systemMaintenance = umReadInt("groups",
				"systemMaintenance", row);

		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);

		websWrite(wp, T("\"userGroupName\":\"%s\","),editUserGroup);
		websWrite(wp, T("\"portAccess\":\"%d\","),portAccess);
		websWrite(wp, T("\"userManager\":\"%d\","),userManager);
		websWrite(wp, T("\"diviceSetting\":\"%d\","),diviceSetting);
		websWrite(wp, T("\"securityManager\":\"%d\","),securityManager);
		websWrite(wp, T("\"systemMaintenance\":\"%d\""),systemMaintenance);
		sendRspFooterObj(wp);
#endif			
	}
	else
	{
	    if (quit_flag) {
            Quit(pHdr_editGrpInfo.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *  test查询用户组 -->>改用formUserGroupList
 */

void formSearchUserGroup (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formSearchUserGroup\n");
	char       *userGroupName = NULL;
	char       keyGrp[8] = {};
	int        row;
	char       requestUser[MAX_USRN_LEN] = {};
	PeerHdr_t  pHdr_srchUserGrp = {};
	MsgHdr_t   mHdr_srchUserGrp = {};
	UserGrp_t  srchUserGrp = {};
	int        quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, requestUser, sizeof(requestUser), &quit_flag))
	{
		userGroupName = websGetVar (wp, T("userG"), T(""));
		printf("userGn:%s\n", userGroupName);
		row = umSearchStr("groups", "name", userGroupName);
		if(row >= 0)
		{
			sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
			websWrite(wp, T("\"userGroupName\":\"%s\""),
					userGroupName);
		}
		else
		{
			sendRspHeadObj(wp, SRCH_GRP_NOFND);
		}
		sendRspFooterObj(wp);
	}
	else
	{
	    if (quit_flag) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************/
/*
 *  test查询用户 
 */

void formSearchUser (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formSearchUser\n");
	char       *userName = NULL, *getUserGroup = NULL;
	char       keyUsr[8] = {};
	int        row;
	char       requestUser[MAX_USRN_LEN] = {};
	PeerHdr_t  pHdr_srchUser = {};
	MsgHdr_t   mHdr_srchUser = {};
	int        quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if(!authenLogin(wp, requestUser, sizeof(requestUser), &quit_flag))
	{
		userName = websGetVar (wp, T("userN"), T(""));
		printf("userN:%s\n", userName);
		row = umSearchStr("users", "name", userName);
		if(row >= 0)
		{
			umReadStr("users", "group", row, &getUserGroup);
			sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
			websWrite(wp, T("\"userName\":\"%s\","), userName);
			websWrite(wp, T("\"userStatus\":\"%s\","), "在线");
			websWrite(wp, T("\"userGroupName\":\"%s\""), getUserGroup);
		}
		else
		{
			sendRspHeadObj(wp, SRCH_USR_NOFND);		
		}
		sendRspFooterObj(wp);
	}
	else
	{
	    if (quit_flag) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}



