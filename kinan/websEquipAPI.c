/*************************************************************
 *  Copyright (C), 2017-2021, Kinan Tech. Co., Ltd. 
 *  Version     :   km1.0
 *  Filename    :   websEquipAPI.c
 *  Description :   此模块为网页设备设置的API
 *  Creator     :   Zeed
 *  Date        :   2017-7-31
 *  History     :   
 *  <author>    <time>    <version >    <desc>
 *  Zeed        17/07/31  1.0           build this moudle  
 *
 *************************************************************/
/************************* Includes **************************/
#include    "websEquipAPI.h"

/***************************Code******************************
 *
 *	页面网络设置
 *  获取页面网络设置数据 并存于主控程序
 */
void formNetSetting (webs_t wp, char_t* path, char_t* query)
{
	printf("--- kinan-formNetSetting ---\n");
	char_t     *network = NULL;
	int        net_index;   //选择设置的网口
	char_t     *ipv4_addr = NULL;
	char_t     *subnetmask = NULL;
	char_t     *dft_gateway = NULL;
	PeerHdr_t  phdr_netset = {};
	MsgHdr_t   mhdr_netset = {};
	CfgNet_t   netset = {};
	int        quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_netset.cWho, 
		    sizeof(phdr_netset.cWho), 
		    &quit_flag)) {
		network = websGetVar(wp, T("netCard"), T(""));
		if (network == NULL || *network == '\0') {
			printf("formNetSetting::worry network choose!\n");
			goto FAIL;
		} else {
			net_index = atoi (network);
		}
		ipv4_addr = websGetVar(wp, T("deviceIpv4"), T(""));
		if (ipv4_addr == NULL || *ipv4_addr == '\0') {
            goto FAIL;
		} else {
            strncpy(netset.net.eth[net_index].IP, 
			        ipv4_addr, 
			        sizeof(netset.net.eth[net_index].IP));
		}
		subnetmask = websGetVar(wp, T("subnetmask"), T(""));
		if (subnetmask == NULL || *subnetmask == '\0') {
		    goto FAIL;
		} else {
           	strncpy(netset.net.eth[net_index].Mask,
			        subnetmask,
			        sizeof(netset.net.eth[net_index].Mask));
		}
		dft_gateway = websGetVar(wp, T("defaultGateway"), T(""));
		if (dft_gateway == NULL || *dft_gateway == '\0') {
			goto FAIL;
		} else {
            strncpy(netset.net.eth[net_index].Gateway,
			        dft_gateway,
			        sizeof(netset.net.eth[net_index].Gateway));
		}
		printf("formNetSetting::NetWork:%d\n", net_index);
		printf("formNetSetting::cIp:%s\n", netset.net.eth[net_index].IP);
		printf("formNetSetting::cMask:%s\n", netset.net.eth[net_index].Mask);
		printf("formNetSetting::cGateWay:%s\n", netset.net.eth[net_index].Gateway);

#ifdef PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_netset, NULL, wp->ipaddr, PEER_SET);

		initMsgHdr(&mhdr_netset, CFG_NET);

		INF_ClientTalkToKing_API(&phdr_netset, &mhdr_netset, 
			(void*)&netset, sizeof(netset));
#endif
		sendRspHeadObj(wp, SET_SUCCESS_MSG);
		sendRspFooterObj(wp);
	} else {
		if (quit_flag == 1) {
            Quit(phdr_netset.cWho, wp->ipaddr);
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

/*************************************************************
 *
 *	网络设置页面
 *  显示默认的网口1的信息
 *  根据参数 返回对应的网口信息
 */
void formNetDefaultInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formNetDefaultInfo ---\n");
	PeerHdr_t  phdr_net_info = {};
	MsgHdr_t   mhdr_net_info = {};
	net_t      net_info = {};
	int        net_index;
	char_t     *network_choose = NULL;
    int        quit_flag;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_net_info.cWho, 
		    sizeof(phdr_net_info.cWho), 
		    &quit_flag)) {
		
#ifdef PROJECT_KM01_FINISHED
        // 获取网口的信息
		initPeerHdr(&phdr_net_info, NULL, wp->ipaddr, PEER_GET);

		// unknown
		initMsgHdr(&mhdr_net_info, );

		INF_ClientTalkToKing_API(&phdr_net_info, 
			&mhdr_net_info, 
			(void*)&net_info, 
			sizeof(net_info)
		);
#else
		getNetWorkInfo(net_info.eth);
#endif	

		// 如果没有传递参数则默认发送网口1的信息
		network_choose = websGetVar(wp, T("network"), T(""));
        if (network_choose == NULL || *network_choose == '\0') {
            net_index = 0;
		} else {
			net_index = atoi(network_choose);
			if (net_index < 0 || net_index >= 2) {
                sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
			    websDone(wp, 200);
				return ;
			}
		}
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
		websWrite(wp, T("\"network\":\"%d\","), net_index);
		websWrite(wp, T("\"deviceIpv4\":\"%s\","), 
				net_info.eth[net_index].IP);
		websWrite(wp, T("\"subnetmask\":\"%s\","), 
				net_info.eth[net_index].Mask);
		websWrite(wp, T("\"cMac\":\"%s\","), 
				net_info.eth[net_index].MAC);
		websWrite(wp, T("\"defaultGateway\":\"%s\""),
				net_info.eth[net_index].Gateway);
		sendRspFooterObj(wp);
	} else {
		if (quit_flag == 1) {
            Quit(phdr_net_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	时间设置 用户自定义/配置NTP服务器
 */
void formDateTime (webs_t wp, char_t* path, char_t* query)
{
	printf("--- kinan-formDateTime ---\n");
	PeerHdr_t  phdr_datetime_set = {};
	MsgHdr_t   mhdr_datetime_set = {};
	sysCtrl_t  datetime_set = {};
	CfgNTP_t   NTPcfg = {};
	char_t     *host_time_sever = NULL;
	char_t     *date_ptr = NULL, *time_ptr = NULL;
	char_t     *parse_time1 = NULL, *parse_time2 = NULL;
	char_t     *time_set_way = NULL;	//时间设置方式 用户/NTP服务器
	int        time_set_way_i;
	struct tm  gt;
	int        quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_datetime_set.cWho, 
		    sizeof(phdr_datetime_set.cWho), 
		    &quit_flag)) {
		time_set_way = websGetVar(wp, T("timeSetway"), T(""));
		printf("formDateTime::timesway:%s\n", time_set_way);

		if (time_set_way == NULL || *time_set_way == '\0') {
			sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return ;
		} else {
			time_set_way_i = atoi(time_set_way);
			if (time_set_way_i < 0 || time_set_way_i > 1) {
          		sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
				websDone(wp, 200);
				return ;
			} else {
                NTPcfg.bNTP = time_set_way_i;
			}
			printf("formDateTime::setway:%d\n", NTPcfg.bNTP);
			if (!NTPcfg.bNTP) {
				date_ptr = websGetVar(wp, T("currentDate"), T("")); //2017-11-19
				time_ptr = websGetVar(wp, T("currentTime"), T("")); //20:10
				
				if (date_ptr == NULL || *date_ptr == '\0') {
					sendRspHeadObj(wp, ARG_ERROR_MSG);
					sendRspFooterObj(wp);
					websDone(wp, 200);
					return ;
				} else {
					printf("formDateTime::1date_ptr-->%s\n", date_ptr);
					if (!parseKeyValue(date_ptr, &parse_time1, &parse_time2, "-")) { //2017 09-23
						printf("formDateTime::1ptt1-->%s\n", parse_time1);
					    printf("formDateTime::1ptt2-->%s\n", parse_time2);
						gt.tm_year = atoi(parse_time1) - 1900;
					} else {
                        sendRspHeadObj(wp, ARG_ERROR_MSG);
						sendRspFooterObj(wp);
						websDone(wp, 200);
						return ;
					}
					date_ptr = parse_time2;
					parse_time1 = NULL;
					parse_time2 = NULL;
					printf("formDateTime::2date_ptr-->%s\n", date_ptr);
					if (!parseKeyValue(date_ptr, &parse_time1, &parse_time2, "-")) { // 13 28
						printf("formDateTime::2ptt1-->%s\n", parse_time1);
						printf("formDateTime::2ptt2-->%s\n", parse_time2);
						gt.tm_mon = atoi(parse_time1)-1;
						gt.tm_mday = atoi(parse_time2);
					} else {
                        sendRspHeadObj(wp, ARG_ERROR_MSG);
						sendRspFooterObj(wp);
						websDone(wp, 200);
						return ;
					}
				}
				if (time_ptr == NULL || *time_ptr == '\0') {
					sendRspHeadObj(wp, ARG_ERROR_MSG);
					sendRspFooterObj(wp);
					websDone(wp, 200);
					return ;
				} else {
					parseKeyValue(time_ptr, &parse_time1, &parse_time2, ":"); //20:10
					gt.tm_hour = atoi(parse_time1);
					printf("formDateTime::hour-->%d\n",gt.tm_hour);
					gt.tm_min = atoi(parse_time2);
					printf("formDateTime::min-->%d\n",gt.tm_min);
					gt.tm_sec = 0;
				}
				datetime_set.ctrl.time.t = mktime(&gt);
				if (datetime_set.ctrl.time.t == -1) {
                    sendRspHeadObj(wp, ARG_ERROR_MSG);
					sendRspFooterObj(wp);
					websDone(wp, 200);
					return ;
				}
				printf("formDateTime::time-->%ld\n", datetime_set.ctrl.time.t);
				datetime_set.ctrl.time.bNet = 0;
				
#ifdef PROJECT_KM01_FINISHED	

                // 选择用户自定义时间 
				// 获取时间字符串 转换成time_t 类型
				initPeerHdr(&phdr_datetime_set, NULL, wp->ipaddr, PEER_CTR);
				initMsgHdr(&mhdr_datetime_set, CTRL_TIME);

				INF_ClientTalkToKing_API(&phdr_datetime_set,
					&mhdr_datetime_set, 
					(void *)&datetime_set, 
					sizeof(datetime_set)
				);
#endif
			} else {
     			host_time_sever = websGetVar(wp, T("hostTimeServer"), T(""));
				if (host_time_sever == NULL || *host_time_sever == '\0') {
				    sendRspHeadObj(wp, ARG_ERROR_MSG);
					sendRspFooterObj(wp);
					websDone(wp, 200);
					return ;
				} else {
				    strncpy(NTPcfg.IP, host_time_sever, sizeof(NTPcfg.IP));
				    printf("formDateTime::ipadr:%s\n", NTPcfg.IP);
					              	
#ifdef PROJECT_KM01_FINISHED  

				// 配置NTP服务器
				initPeerHdr(&phdr_datetime_set, NULL, wp->ipaddr, PEER_SET);
				// cfg_system_info??
				initMsgHdr(&mhdr_datetime_set, CFG_SYSTEM_INFO);

				INF_ClientTalkToKing_API(&phdr_datetime_set, 
					&mhdr_datetime_set, 
				   	(void *)&NTPcfg, 
				   	sizeof(NTPcfg)
				);
#endif
				}
			}
		}
		sendRspHeadObj(wp, SET_SUCCESS_MSG);
		sendRspFooterObj(wp);
	} else {
		if (quit_flag == 1) {
            Quit(phdr_datetime_set.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *  页面日期时间
 *	发送默认日期设置信息
 */
void formDateTimeInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formDateTimeInfo ---\n");
	PeerHdr_t    phdr_time_info = {};
	MsgHdr_t     mhdr_time_info = {};
	CfgNTP_t     ntp_info = {};
	int          quit_flag;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_time_info.cWho, 
		    sizeof(phdr_time_info.cWho), 
		    &quit_flag)) {
		    
#ifdef  PROJECT_KM01_FINISHED

        //获取CfgNTP_t 根据其中的bNTP 判断是否设置了ntp服务器
        //如果设置了        则发送ntp服务器的ip地址
        //如果没有设置 则获取网页PC上的时间显示
		initPeerHdr(&phdr_time_info, NULL, wp->ipaddr, PEER_GET);

		initMsgHdr(&mhdr_time_info, CFG_NTP);

		INF_ClientTalkToKing_API(&phdr_time_info, 
			&mhdr_time_info, 
			(void *)&ntp_info, 
			sizeof(ntp_info)
		);
#else
		getNTPserver(&ntp_info);
#endif
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
		websWrite(wp, T("\"timeSetWay\":\"%d\""),
			      ntp_info.bNTP);
 		if (ntp_info.bNTP) {
			//发送ntp服务器地址
			websWrite(wp, T(",\"hostTimeServer\":\"%s\""),
				      ntp_info.IP);
		}
		sendRspFooterObj(wp);
	} else {
	    if (quit_flag == 1) {
            Quit(phdr_time_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	设备设置
 */
void formDeviceConfig (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formDeviceConfig ---\n");
	PeerHdr_t        phdr_device_cfg = {};
	MsgHdr_t         mhdr_device_cfg = {};
	KvmSystemInfo_t  device_cfg = {};
	char             *device_name = NULL;
    int              quit_flag;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_device_cfg.cWho, 
		    sizeof(phdr_device_cfg.cWho), 
		    &quit_flag)) {
		device_name = websGetVar(wp, T("deviceName"), T(""));
		if(device_name == NULL || *device_name == '\0'){
			sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
			// 从主控程序中获取设备名称
			websWrite(wp, T("\"devicename\":\"%s\""), "kvm01");
			sendRspFooterObj(wp);
		    websDone(wp, 200);
			return ;
		} else {
			
#ifdef  PROJECT_KM01_FINISHED
			initPeerHdr(&phdr_device_cfg, NULL, wp->ipaddr, PEER_SET);

			initMsgHdr(&mhdr_device_cfg, CFG_SYSTEM_INFO);
			//需要判断设备名的长度
			//...
			strncpy(device_cfg.cKvmName, device_name, sizeof(device_cfg.cKvmName));
#endif
			sendRspHeadObj(wp, SET_SUCCESS_MSG);
			sendRspFooterObj(wp);
		}
		
	} else {
	    if (quit_flag == 1) {
            Quit(phdr_device_cfg.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	事件管理
 */
void formEventManage (webs_t wp, char_t *path, char_t *query)
{
    printf("--- kinan-formEventManage ---\n");
	char  request_user[MAX_USRN_LEN] = {};
	char  *enableSysLogFoward = NULL;
	char  *foward_ipaddr = NULL;
	int   quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    request_user, 
		    sizeof(request_user), 
		    &quit_flag)) {
		    
#ifdef PROJECT_KM01_FINISHED

#endif
		enableSysLogFoward = websGetVar(wp, T("enableSysLogFoward"),
				                        T(""));	
		foward_ipaddr = websGetVar(wp, T("fowardIpAddress"),
				                   T(""));
		if (foward_ipaddr == NULL || *foward_ipaddr == '\0') {
            sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
		    websDone(wp, 200);
			return ;
		} else {
		    printf("en:%s\n", enableSysLogFoward);
		    printf("fo:%s\n", foward_ipaddr);
		    sendRspHeadObj(wp, SET_SUCCESS_MSG);
		    sendRspFooterObj(wp);
		}
	}
	else {
	    if (quit_flag == 1) {
            Quit(request_user, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	配置端口信息
 *  根据前端的请求 从主控程序中获取对应的端口信息
 */
void formConfigPortInfo (webs_t wp, char_t *path, char_t *query)
{
    printf("--- kinan-formConfigPortInfo ---\n");
	char requestUser[MAX_USRN_LEN] = {};
	char *valuePortId = NULL;
	char *keyPortId = NULL, *portType = NULL; 
	int  portId;
	int  quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    requestUser, 
		    sizeof(requestUser), 
		    &quit_flag)) {
		    
#ifdef PROJECT_KM01_FINISHED
		
#endif
		valuePortId = websGetVar (wp, T("portNum"), T(""));
		if(valuePortId == NULL || *valuePortId == '\0')
		{
			printf("worry argment!\n");
			return ;
		}
		else
		{
			portType = "USB";
			printf("vp:%s\n", valuePortId);
			if((valuePortId != NULL) && (*valuePortId != '\0'))
			{
				portId = atoi (valuePortId);

				sendRspHeadObj (wp, AUTHEN_SUCCESS_MSG);
				websWrite (wp, T("\"portNumber\":\"配置端口_%d\","),
						portId);
				websWrite (wp, T("\"portType\":\"%s\","),
						portType);
				websWrite (wp, T("\"portName\":\"port%d\","),
						portId);
				websWrite (wp, T("\"resolution\":\"1920X1080\","));
				websWrite (wp, T("\"refresh\":\"60\""));
				sendRspFooterObj (wp);
			}
			else
			{
				sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj (wp);
			}
		}			
	}
	else
	{
	    if (quit_flag == 1) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	发送本地端口快捷键设置信息
 */
void formLocalPortInfo (webs_t wp, char_t *path, char_t *query)
{
    printf("--- kinan-formLocalPortInfo ---\n");
	char requestUser[MAX_USRN_LEN] = {};
	int  quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    requestUser, 
		    sizeof(requestUser), 
		    &quit_flag)) {

#ifdef PROJECT_KM01_FINISHED

#endif
		websWrite (wp, T("{\"status\":\"true\","));
		websWrite (wp, T("\"msg\":{\"hotKey\":["));
		websWrite (wp, T("{\"opt\":\"双击Scroll Lock\"},"));
		websWrite (wp, T("{\"opt\":\"双击Num Lock\"},"));
		websWrite (wp, T("{\"opt\":\"双击Caps Lock\"},"));
		websWrite (wp, T("{\"opt\":\"双击左Alt键\"},"));
		websWrite (wp, T("{\"opt\":\"双击左Shift键\"},"));
		websWrite (wp, T("{\"opt\":\"双击左Ctrl键\"}"));
		websWrite (wp, T("],\"linkKey\":["));
		websWrite (wp, T("{\"opt\":\"左Alt键\"},"));
		websWrite (wp, T("{\"opt\":\"左Shift键\"},"));
		websWrite (wp, T("{\"opt\":\"左Ctrl键\"},"));
		websWrite (wp, T("{\"opt\":\"禁用\"}]},"));
		websWrite (wp, T("\"data\":{"));
		websWrite (wp, T("\"portHotKey\":\"双击左Shift键\","));
		websWrite (wp, T("\"portLinkKey\":\"左Alt键\""));
		sendRspFooterObj (wp);
	} else {
	    if (quit_flag == 1) {
            Quit(requestUser, wp->ipaddr);
		} 
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);

}

/*************************************************************
 *
 *	更改端口信息
 */
void formModifyPort (webs_t wp, char_t *path, char_t *query)
{
    printf("--- kinan-formModefyPort ---\n");
	PeerHdr_t        pHdr_modifyPort = {};
	MsgHdr_t         mHdr_modifyPort = {};
	PortAccessCfg_t  modifyPort = {};  
	char_t           *portNum = NULL, *portName = NULL, *portType = NULL;
	char_t           *portResolution = NULL, *portRefresh = NULL;
	int              quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    pHdr_modifyPort.cWho, 
		    sizeof(pHdr_modifyPort.cWho), 
		    &quit_flag)) {
		portNum = websGetVar (wp, T("portCount"), T(""));
		portName = websGetVar (wp, T("portName"), T(""));
		//portType = websGetVar (wp, T(""), T(""));
		portResolution = websGetVar (wp, T("refreshRate"), T(""));
		portRefresh = websGetVar (wp, T("resolution"), T(""));
		printf("formModifyPort::portNum:%s\n", portNum);
		printf("formModifyPort::portName:%s\n", portName);
		printf("formModifyPort::portType:%s\n", portType);
		printf("formModifyPort::portResolution:%s\n", portResolution);
		printf("formModifyPort::portRefresh:%s\n", portRefresh);

#ifdef PROJECT_KM01_FINISHED

		initPeerHdr(&pHdr_modifyPort, NULL, wp->ipaddr, PEER_SET);

		initMsgHdr(&mHdr_modifyPort, CFG_PORT_ACCESS);

		// 传递给主控程序
#endif		
		sendRspHeadObj (wp, AUTHEN_SUCCESS_MSG);
		sendRspFooterObj (wp);			
	} else {
	    if (quit_flag == 1) {
            Quit(pHdr_modifyPort.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	设置本地端口快捷键
 */
void formSetLocalPort (webs_t wp, char_t *path, char_t *query)
{
    printf("--- kinan-formSetLocalPort ---\n");
	char requestUser[MAX_USRN_LEN] = {};
	char *portHotKey = NULL, *portLinkKey = NULL;
	int  quit_flag;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    requestUser, 
		    sizeof(requestUser), 
		    &quit_flag)) {
		portHotKey = websGetVar (wp, T("portHotKey"), T(""));
		portLinkKey = websGetVar (wp, T("portLinkKey"), T(""));
		printf("portHotKey:%s\n", portHotKey);
		printf("portLinkKey:%s\n", portLinkKey);

#ifdef PROJECT_KM01_FINISHED

#endif		
		sendRspHeadObj (wp, AUTHEN_SUCCESS_MSG);
		sendRspFooterObj (wp);
	} else {
	    if (quit_flag == 1) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}


