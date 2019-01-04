/*************************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.	
 *	Version		:	km1.0
 *	Filename	:	websAPI.c
 *	Description	:	该模块为KM01系列网页API
 * 					包括各个API的注册和实现
 *	Creator		:	Zeed
 *	Date		:	2017-7-21
 *	History		:	
 *	<author>    <time>    <version >    <desc>
 *	Zeed	    17/07/31  1.0			build this moudle  
 *
 *************************************************************/
/************************ Includes ***************************/
#include    "websAPI.h"     

/******************** Forward Declarations *******************/
static void formSideBar  (webs_t wp, char_t *path, char_t *query);
static void formPortInfo (webs_t wp, char_t *path, char_t *query);

/***************************Code******************************
 *
 *	km01 各模块接口
 */
void formDefineKinan(void)
{
	websFormDefine (T("SideBar"), formSideBar);
	websFormDefine (T("PortInfo"), formPortInfo);

	websFormDefine (T("Login"), formLogin);
	websFormDefine (T("Quit"), formQuit);

	websFormDefine (T("AddUserGroup"), formAddUserGroup);
	websFormDefine (T("AddUser"), formAddUser);
	websFormDefine (T("AddUserInfo"), formAddUserInfo);

    websFormDefine (T("UserList"), formUserList);
	websFormDefine (T("UserGroupList"), formUserGroupList);
	
	websFormDefine (T("DeleteUserGroup"), formDelUserGroup);
	websFormDefine (T("DelUser"), formDelUser);
	
	websFormDefine (T("EditUserGroup"), formEditUserGroup);
	websFormDefine (T("EditUser"), formEditUser);
	websFormDefine (T("EditUserInfo"), formEditUserInfo);
	websFormDefine (T("EditUserGroupInfo"), formEditUserGroupInfo);
	
	websFormDefine (T("ChangePasswd"), formChaPasswd);
	websFormDefine (T("SearchUser"), formSearchUser);
	websFormDefine (T("SearchUserGroup"), formSearchUserGroup);

	websFormDefine (T("NetSetting"), formNetSetting);
	websFormDefine (T("NetDefaultInfo"), formNetDefaultInfo);
	websFormDefine (T("DateTimeInfo"), formDateTimeInfo);
	websFormDefine (T("DateTime"), formDateTime);
	websFormDefine (T("ModifyPort"), formModifyPort);
	websFormDefine (T("ConfigPortInfo"), formConfigPortInfo);
	websFormDefine (T("LocalPortInfo"), formLocalPortInfo);
	websFormDefine (T("SetLocalPort"), formSetLocalPort);
	websFormDefine (T("DeviceConfig"), formDeviceConfig);
	websFormDefine (T("EventManage"), formEventManage);

    websFormDefine (T("SafeSet"), formSafeSetting);
	websFormDefine (T("SafeSetInfo"), formSafeSetInfo);
	websFormDefine (T("ConfirmSetInfo"), formConfirmSetInfo);
	websFormDefine (T("ConfirmSet"), formConfirmSet);
	websFormDefine (T("AuditLog"), formAuditLog);

	websFormDefine (T("SystemCtrl"), formSystemCtrl);
	websFormDefine (T("Backup"), formBackup);
	websFormDefine (T("BackupInfo"), formBackupInfo);
	websFormDefine (T("PingHost"), formPingHost);
	websFormDefine (T("PingHostv3"), formPingHostv3);
	websFormDefine (T("RemoteUpgrade"), formRemoteUpgrade);
}

/*************************************************************
 *
 *	初始化webs需要用的sessionid  
 */
 int  websApiOpen ()
{
	return sessionOpen();
}

/*************************************************************
 *
 *  关闭webs需要用的sessionid  
 */
  int  websApiClose ()
 {
	 return sessionClose();
 }

/*************************************************************
 *
 *	页面侧边栏
 *  请求系统信息 和 用户的访问权限  
 */
void formSideBar (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formSideBar ---\n");
	KvmSystemInfo_t  system_info = {};	 
	PeerHdr_t        phdr_system_info = {};		
	MsgHdr_t         mhdr_system_info = {};		
	int              quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, phdr_system_info.cWho, sizeof(phdr_system_info.cWho), &quit_flag)) {
		
#ifdef PROJECT_KM01_FINISHED
        // 获取主控程序中的系统信息
		initPeerHdr(&phdr_system_info, NULL, wp->ipaddr, PEER_GET);	

		initMsgHdr(&mhdr_system_info, CFG_SYSTEM_INFO);

		INF_ClientTalkToKing_API(
		    &phdr_system_info, 
		    &mhdr_system_info,
		    (void*)system_info, 
		    sizeof(system_info));
		
		// 获取用户的访问权限 (待完成)
#else			
		getKvmSystemInfo(&system_info);
#endif
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
        // 发送用户的访问权限
        websWrite(wp, T("\"portPrivilege\":\"%d\","), 1);
		websWrite(wp, T("\"userMngPrivilege\":\"%d\","), 1);
		websWrite(wp, T("\"sysSetPrivilege\":\"%d\","), 1);
		websWrite(wp, T("\"securePrivilege\":\"%d\","), 1);
		websWrite(wp, T("\"sysMntPrivilege\":\"%d\","), 1);

		// 将系统数据发送给前端
		websWrite(wp, T("\"loginUser\":\"%s\","), 
		    system_info.loginUser);

		websWrite(wp, T("\"curLogin_time\":\"%d-%d-%d %d:%d:%d\","),
			system_info.curLogin.t.tm_year+1900,
			system_info.curLogin.t.tm_mon+1,
			system_info.curLogin.t.tm_mday,
			system_info.curLogin.t.tm_hour,
			system_info.curLogin.t.tm_min,
			system_info.curLogin.t.tm_sec);

		websWrite(wp, T("\"curLogin_ip\":\"%s\","),
			wp->ipaddr/*rcvSystemInfo.curLogin.sIp*/);
/*		
				websWrite(wp, T("\"lastLogin_ip\":\"%s\","),
				rcvSystemInfo.lastLogin.sIp);

				websWrite(wp,T("\"lastLogin_time\":\"%d-%d-%d %d:%d:%d\","),
				rcvSystemInfo.lastLogin.t.tm_year+1900,
				rcvSystemInfo.lastLogin.t.tm_mon+1,
				rcvSystemInfo.lastLogin.t.tm_mday,
				rcvSystemInfo.lastLogin.t.tm_hour,
				rcvSystemInfo.lastLogin.t.tm_min,
				rcvSystemInfo.lastLogin.t.tm_sec);
*/
		websWrite(wp ,T("\"cKvmName\":\"%s\","), 
			system_info.cKvmName);

		websWrite(wp ,T("\"cFirmware\":\"%s\","), 
			system_info.cFirmware);

		websWrite(wp ,T("\"cKvmModel\":\"%s\","), 
			system_info.cKvmModel);

		websWrite(wp, T("\"cPowerIn\":\"%s\","), 
			system_info.cPowerIn? "开": "关");
		
		// 新加的选项：硬件型号 网口地址
		websWrite (wp, T("\"cHardware\":\"KVM100GF1\","));

		websWrite (wp, T("\"cNetWork1\":\"%s\","), 
			"192.168.2.111");
		websWrite (wp, T("\"cNetWork2\":\"%s\""),
			"192.168.2.222");

		sendRspFooterObj(wp);
	} else {
		if (quit_flag == 1) {
		    Quit(phdr_system_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	页面端口信息
 *  请求端口数据 提交最大的存储空间 
 *  通过返回的数据大小 发送对应大小的数据
 */
void formPortInfo(webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formPortInfo ---\n");
	PeerHdr_t           phdr_port_info;
	MsgHdr_t            mhdr_port_info;
	// 最多显示端口 (数组)
	PortAccessStatus_t  port_info[MAX_PORT_ACCESS_NUM] = {}; 
	int                 nGroup, i, j;
	int                 quit_flag;

	printf("formPortInfo::ip-->>%s\n", wp->ipaddr);
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_port_info.cWho, 
		    sizeof(phdr_port_info.cWho), 
		    &quit_flag)) {
		
#ifdef PROJECT_KM01_FINISHED
        // 从后台获取主控程序中的端口信息
		initPeerHdr(&phdr_port_info, NULL, wp->ipaddr, PEER_GET);

		initMsgHdr(&mhdr_port_info, CFG_PORT_ACCESS_STATUS);

		INF_ClientTalkToKing_API(
			phdr_port_info, 
			mhdr_port_info, 
			(void*)port_info, 
			64*sizeof(PortAccessStatus_t)
			);

		nGroup = (phdr_port_info->sLen - sizeof(MsgHdr_t))/(sizeof(PortAccessStatus_t));
#else
		getPortInfo(port_info);
#endif			
		sendRspHeadArray(wp, AUTHEN_SUCCESS_MSG);
		for (i=0; i<MAX_PORT_ACCESS_NUM; i++)
		{
			websWrite(wp, T("{\"sNum\":\"%hd\","),
				port_info[i].sNum);

			websWrite(wp, T("\"cName\":\"%s\","),
				port_info[i].cName);

			websWrite(wp, T("\"AccessType\":\"%s\","),
				port_info[i].AccessType?"访问":"无法访问");

			websWrite(wp, T("\"cStatus\":\"%c\","),
				port_info[i].cStatus);

			websWrite(wp, T("\"availability\":\"%c\","),
				port_info[i].availability);

			websWrite(wp, T("\"broadcast\":\"ky\"}"));

			if (i < MAX_PORT_ACCESS_NUM-1) {
				websWrite(wp, T(","));
			}
		}
		sendRspFooterArray(wp);
    } else {
		if (quit_flag == 1) {
            Quit(phdr_port_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}


