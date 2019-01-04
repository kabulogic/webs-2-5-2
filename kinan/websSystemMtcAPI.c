/*************************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.	
 *	Version		:	km1.0
 *	Filename	:	websSystemMtcAPI.c
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

#include "websSystemMtcAPI.h" 

/******************** Forward Declarations *******************/

#define  CONTENT_TYPE          "Content-Type"
#define  PING_RESULT_FALSE     "100% packet loss"

/* used for formPingHost2::Call
#define WAIT_TIME 3

char SendBuffer[SEND_BUFFER_SIZE];
char RecvBuffer[RECV_BUFFER_SIZE];
int nRecv = 0;	//实际接收到的报文数
struct timeval FirstSendTime;	//用以计算总的时间
struct timeval LastRecvTime;
double min = 0.0;
double avg = 0.0;
double max = 0.0;
double mdev = 0.0;

struct hostent * pHost = NULL;		//保存主机信息
int sock_icmp;				//icmp套接字
int nSend = 1;
char *IP = NULL;
*/
/***************** ping相关程序 ******************/
#if 0
int Call(char *pingIP)
{

	struct protoent *protocol;
	struct sockaddr_in dest_addr; 	//IPv4专用socket地址,保存目的地址

	in_addr_t inaddr;		//ip地址（网络字节序）

	if ((protocol = getprotobyname("icmp")) == NULL){
		perror("getprotobyname");
		return 0;
	}

	/* 创建ICMP套接字 */
	//AF_INET:IPv4, SOCK_RAW:IP协议数据报接口, IPPROTO_ICMP:ICMP协议
	if ((sock_icmp = socket(PF_INET, SOCK_RAW, protocol->p_proto/*IPPROTO_ICMP*/)) < 0)
	{
		perror("socket");
		return 0;
	}
	dest_addr.sin_family = AF_INET;

	/* 将点分十进制ip地址转换为网络字节序 */
	if ((inaddr = inet_addr(pingIP)) == INADDR_NONE)
	{
		/* 转换失败，表明是主机名,需通过主机名获取ip */
		if ((pHost = gethostbyname(pingIP)) == NULL)
		{
			herror("gethostbyname()");
			return 0;
		}
		memmove(&dest_addr.sin_addr, pHost->h_addr_list[0], pHost->h_length);
	}
	else
	{
		memmove(&dest_addr.sin_addr, &inaddr, sizeof(struct in_addr));
	}

	if (NULL != pHost)
		printf("PING %s", pHost->h_name);
	else
		printf("PING %s", pingIP);
	printf("(%s) %d bytes of data.\n", inet_ntoa(dest_addr.sin_addr), ICMP_LEN);

	IP = pingIP;
	signal(SIGINT, Statistics);
	while (nSend < SEND_NUM)
	{
		int unpack_ret;
		
		SendPacket(sock_icmp, &dest_addr, nSend);
		
		unpack_ret = RecvePacket(sock_icmp, &dest_addr);
		if (-1 == unpack_ret)	//（ping回环时）收到了自己发出的报文,重新等待接收
			RecvePacket(sock_icmp, &dest_addr);
		
		sleep(1);
		nSend++;
	}
	
	Statistics(0);	//输出信息，关闭套接字
	return 1;
}

u_int16_t Compute_cksum(struct icmp *pIcmp)
{
	u_int16_t *data = (u_int16_t *)pIcmp;
	int len = ICMP_LEN;
	u_int32_t sum = 0;
	
	while (len > 1)
	{
		sum += *data++;
		len -= 2;
	}
	if (1 == len)
	{
		u_int16_t tmp = *data;
		tmp &= 0xff00;
		sum += tmp;
	}

	//ICMP校验和带进位
	while (sum >> 16)
		sum = (sum >> 16) + (sum & 0x0000ffff);
	sum = ~sum;
	
	return sum;
}

void SetICMP(u_int16_t seq)
{
	struct icmp *pIcmp;
	struct timeval *pTime;

	pIcmp = (struct icmp*)SendBuffer;
	
	/* 类型和代码分别为ICMP_ECHO,0代表请求回送 */
	pIcmp->icmp_type = ICMP_ECHO;
	pIcmp->icmp_code = 0;
	pIcmp->icmp_cksum = 0;		//校验和
	pIcmp->icmp_seq = seq;		//序号
	pIcmp->icmp_id = getpid();	//取进程号作为标志
	pTime = (struct timeval *)pIcmp->icmp_data;
	gettimeofday(pTime, NULL);	//数据段存放发送时间
	pIcmp->icmp_cksum = Compute_cksum(pIcmp);
	
	if (1 == seq)
		FirstSendTime = *pTime;
}

void SendPacket(int sock_icmp, struct sockaddr_in *dest_addr, int nSend)
{
	SetICMP(nSend);
	if (sendto(sock_icmp, SendBuffer, ICMP_LEN, 0,
		(struct sockaddr *)dest_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("sendto");
		return;
	}
}

double GetRtt(struct timeval *RecvTime, struct timeval *SendTime)
{
	struct timeval sub = *RecvTime;

	if ((sub.tv_usec -= SendTime->tv_usec) < 0)
	{
		--(sub.tv_sec);
		sub.tv_usec += 1000000;
	}
	sub.tv_sec -= SendTime->tv_sec;
	
	return sub.tv_sec * 1000.0 + sub.tv_usec / 1000.0; //转换单位为毫秒
}

int unpack(struct timeval *RecvTime)
{
	struct ip *Ip = (struct ip *)RecvBuffer;
	struct icmp *Icmp;
	int ipHeadLen;
	double rtt;

	ipHeadLen = Ip->ip_hl << 2;	//ip_hl字段单位为4字节
	Icmp = (struct icmp *)(RecvBuffer + ipHeadLen);

	//判断接收到的报文是否是自己所发报文的响应
	if ((Icmp->icmp_type == ICMP_ECHOREPLY) && Icmp->icmp_id == getpid())
	{
		struct timeval *SendTime = (struct timeval *)Icmp->icmp_data;
		rtt = GetRtt(RecvTime, SendTime);
	
		printf("%u bytes from %s: icmp_seq=%u ttl=%u time=%.1f ms\n",
			ntohs(Ip->ip_len) - ipHeadLen,
			inet_ntoa(Ip->ip_src),
			Icmp->icmp_seq,
			Ip->ip_ttl,
			rtt);
		
		if (rtt < min || 0 == min)
			min = rtt;
		if (rtt > max)
			max = rtt;
		avg += rtt;
		mdev += rtt * rtt;
		
		return 0;
	}
		
	return -1;
}


void Statistics(int signo)
{
	double tmp;
	avg /= nRecv;
	tmp = mdev / nRecv - avg * avg;
	//mdev = sqrt(tmp);
	
	if (NULL != pHost)
		printf("--- %s  ping statistics ---\n", pHost->h_name);
	else
		printf("--- %s  ping statistics ---\n", IP);
		
	printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n"
		, nSend
		, nRecv
		, (nSend - nRecv) / nSend * 100
		, (int)GetRtt(&LastRecvTime, &FirstSendTime));
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f ms\n",
		min, avg, max);
	
	close(sock_icmp);
	//exit(0);
	return ;
}

int RecvePacket(int sock_icmp, struct sockaddr_in *dest_addr)
{
	int RecvBytes = 0;
	int addrlen = sizeof(struct sockaddr_in);
	int resttime;
	struct timeval RecvTime;
	
	signal(SIGALRM, Statistics);
	resttime = alarm(WAIT_TIME);
	printf("resttime:%d\n", resttime);
	if ((RecvBytes = recvfrom(sock_icmp, RecvBuffer, RECV_BUFFER_SIZE,
			0, (struct sockaddr *)dest_addr, &addrlen)) < 0)
	{
		perror("recvfrom");
		return 0;
	}
	//printf("nRecv=%d\n", RecvBytes);
	gettimeofday(&RecvTime, NULL);
	LastRecvTime = RecvTime;

	if (unpack(&RecvTime) == -1)
	{
		return -1; 
	}
	nRecv++;
}
#endif

/************************** Code *****************************
 *
 *	控制系统 
 *  重启/ 恢复出厂/ 恢复系统配置/ 关机
 *  通过获取网页数据 doflag 判断具体什么操作
 */
void formSystemCtrl (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formSystemCtrl ---\n");
	PeerHdr_t  phdr_system_ctrl = {};
	MsgHdr_t   mhdr_system_ctrl = {};
	runCtr_t   system_ctrl = {};
	char       *do_flag = NULL;
	int        quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_system_ctrl.cWho, 
			sizeof(phdr_system_ctrl.cWho), 
			&quit_flag)) {
		do_flag = websGetVar (wp, T("doFlag"), T(""));
		printf("formSystemCtrl::doflag:%s\n", do_flag);
		if (do_flag == NULL || *do_flag == '\0') {
			goto FAIL;
		} else {
			switch (atoi(do_flag))
			{
                case 4:
					system_ctrl.cCmd = 0x04;  //重启
					break;
				case 5:
					system_ctrl.cCmd = 0x05;  //关机
					break;
				case 6:
					system_ctrl.cCmd = 0x06;  //恢复出厂
					break;
				case 7:
					system_ctrl.cCmd = 0x07;  //恢复配置
					break;
				default:
				    goto FAIL;
					break;
			}
			printf("ctrlsys.ccmd:%d\n", system_ctrl.cCmd);
			
#ifdef  PROJECT_KM01_FINISHED
			initPeerHdr(&phdr_system_ctrl, NULL, wp->ipaddr, PEER_CTR);
			initMsgHdr(&mhdr_system_ctrl, CTRL_RUN);

			INF_ClientTalkToKing_API(
				&phdr_system_ctrl, 
				&mhdr_system_ctrl, 
				(void *)&system_ctrl, 
				sizeof(system_ctrl));
#endif
			sendRspHeadObj(wp, SET_SUCCESS_MSG);
			sendRspFooterObj(wp);
		}
	} else {
	    if (quit_flag) {
            Quit(phdr_system_ctrl.cWho, wp->ipaddr);
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
 *	备份恢复
 *  从网页上获取备份设置的数据
 *  如果获取到的备份设置模式为自动 那么将获取3个不同的时间段
 *  并将时间转换成按分钟为单位的u_16数据
 */
void formBackup (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formBackup ---\n");
	PeerHdr_t    phdr_backup = {};
	MsgHdr_t     mhdr_backup = {};
	BackupCfg_t  backup = {};
	char         *get_time_ptr = NULL, *backup_mode = NULL;
	char         *hour_ptr = NULL,  *min_ptr = NULL;
	char         *time_kyword_index[] = {"oneTime", "twoTime", "threeTime"}; 
	int          i;
    int          quit_flag = 0;

	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_backup.cWho, 
		    sizeof(phdr_backup.cWho), 
		    &quit_flag)) {
		backup_mode = websGetVar (wp, T("backMode"), T(""));
		if (backup_mode == NULL || *backup_mode == '\0') {
			goto FAIL;
		} else {
			switch (atoi(backup_mode)) {
				case 0:
					backup.cMethod = 0x00;
					break;
				case 1:
					backup.cMethod = 0x01;
					break;
				default:
					goto FAIL;
				    break;
			}
			printf("formBackup::cMethod-->>%d\n", backup.cMethod);
		}
		if (backup.cMethod) {
			for (i=0; i<3; i++) {
				get_time_ptr = websGetVar (wp, time_kyword_index[i], T(""));
				if(get_time_ptr == NULL || *get_time_ptr == '\0') {
					goto FAIL;
				} else {
					parseKeyValue(get_time_ptr, &hour_ptr, &min_ptr, ":");
					backup.backTime[i] = atoi(hour_ptr)*60;
					backup.backTime[i] += atoi(min_ptr);
					printf("formBackup::backtime-->>%d\n", backup.backTime[i]);
				}
			}
		}
		
#ifdef  PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_backup, NULL, wp->ipaddr, PEER_CTR);
		initMsgHdr(&mhdr_backup, CTRL_BACKUP);
		INF_ClientTalkToKing_API(&phdr_backup, 
			&mhdr_backup, 
			(void *)&backup, 
			sizeof(backup));
#endif		
		sendRspHeadObj(wp, SET_SUCCESS_MSG);
		sendRspFooterObj(wp);
	} else {
		if (quit_flag) {
            Quit(phdr_backup.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
	return;
FAIL:
	sendRspHeadObj(wp, ARG_ERROR_MSG);
	sendRspFooterObj(wp);
	websDone(wp, 200);
	return ;
}

/*************************************************************
 *
 *	备份恢复
 *  从主控程序中获取备份信息
 *  如果备份模式为自动 则有3组时间 以分钟为单位 存于u_16数组中
 */
void formBackupInfo (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formBackupInfo ---\n");
	PeerHdr_t    phdr_backup_info = {};
	MsgHdr_t     mhdr_backup_info = {};
	BackupCfg_t  backup_info = {};
    int          quit_flag = 0;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    phdr_backup_info.cWho, 
			sizeof(phdr_backup_info.cWho), 
			&quit_flag)) {
			
#ifdef  PROJECT_KM01_FINISHED
		initPeerHdr(&phdr_backup_info, NULL, wp->ipaddr, PEER_GET);
		initMsgHdr(&mhdr_backup_info, CFG_BACKUP);

		INF_ClientTalkToKing_API(&phdr_backup_info, &mhdr_backup_info, 
				(void *)backup_info, sizeof(backup_info));
#else
		getBackup(&backup_info);
#endif
		sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
		if (!backup_info.cMethod) {
			websWrite (wp, T("\"backModel\":\"%d\""), 
				backup_info.cMethod);
		} else {
			websWrite (wp, T("\"backModel\":\"%d\","),
					backup_info.cMethod);
			websWrite (wp, T("\"oneTime\":\"%02d:%02d\","),
					backup_info.backTime[0]/60, 
					backup_info.backTime[0]%60);
			websWrite (wp, T("\"twoTime\":\"%02d:%02d\","),
					backup_info.backTime[1]/60,
					backup_info.backTime[1]%60);
			websWrite (wp, T("\"threeTime\":\"%02d:%02d\""),
					backup_info.backTime[2]/60,
					backup_info.backTime[2]%60);
		}
		sendRspFooterObj(wp);
	} else {
	    if (quit_flag) {
            Quit(phdr_backup_info.cWho, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *	远程升级
 */
void formRemoteUpgrade (webs_t wp, char_t *path, char_t *query)
{
	printf("--- kinan-formRemoteUpgrade ---\n");
	FILE      *file_fd;
    char_t    *first_file_name = NULL;
    char_t    *final_file_name = NULL;
    int       locate_write;
    int       num_left;
    int       num_write;
	char      request_user[MAX_USRN_LEN] = {};
	int       quit_flag = 0;

    a_assert(websValid(wp));
	goformHead(wp);
    if (!authenLogin(wp, 
		    request_user, 
		    sizeof(request_user), 
		    &quit_flag)) {
    	first_file_name = websGetVar(wp, T("filename"), T(""));
    	if (first_file_name != NULL && *first_file_name != '\0') {
        	if ((int)(final_file_name = gstrrchr(first_file_name, '/') + 1) == 1) {
            	if ((int)(final_file_name = gstrrchr(first_file_name, '\\') + 1) == 1) {
                	final_file_name = first_file_name;
            	}
        	}
    	}
		printf("fromRemoteUpgrade::fn=%s, bn=%s \n", first_file_name, final_file_name);

		if ((file_fd = fopen((final_file_name == NULL ? "upldForm.bin" : final_file_name), "w+b")) == NULL) {
        	sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return ;
    	} else {
        	locate_write = 0;
        	num_left = wp->lenPostData;
        	while (num_left > 0) {
            	num_write = fwrite(&(wp->postData[locate_write]), sizeof(*(wp->postData)), num_left, file_fd);
            	if (num_write < num_left) {
                	printf("fromRemoteUpgrade::File write failed.locWrite=%d numLeft=%d numWrite=%d Size=%d bytes\n",
						locate_write, num_left, num_write, wp->lenPostData);
					break;
            	}
            	locate_write += num_write;
            	num_left -= num_write;
        	}

        	if (num_left == 0) {
            	if(fclose(file_fd) != 0) {
                	printf("fromRemoteUpgrade::File close failed. errno=%d locWrite=%d numLeft=%d numWrite=%d Size=%d\n", 
						errno, locate_write, num_left, num_write, wp->lenPostData);
            	} else {
                	/*sendRspHeadObj(wp, AUTHEN_SUCCESS_MSG);
					websWrite(wp, T("\"filename\":\"%s\""), bn);
					sendRspFooterObj(wp);*/
					websWrite (wp, T("{\"status\":\"true\"}"));
            	}
        	} else {
            	printf("fromRemoteUpgrade::numLeft=%d locWrite=%d Size=%d bytes\n", num_left, locate_write, wp->lenPostData);
				websWrite(wp, T("{\"status\":\"false\"}"));
        	}
    	}
    }else{
        if (quit_flag) {
            Quit(request_user, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
    websDone(wp, 200);
}

/*************************************************************
 *
 *  Ping主机	  效果不好！在延迟等待主机会话时无法进行其他操作
 *  -->> 改用CGI的方式
 */
void formPingHost (webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-formBackup\n");
	char_t    requestUser[MAX_USRN_LEN] = {};
	char_t    *pingIP = NULL;
	char_t    pingCmd[128] = {};       
	char_t    tempFile[32] = {};
	char_t    pingResult[32] = {};
	gstat_t   tbuf;
	time_t    curtime;
	int       tempFd, res;
	int       quit_flag = 0;
	  
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    requestUser, 
		    sizeof(requestUser), 
		    &quit_flag)) {
		pingIP = websGetVar (wp, T("ping"), T(""));
		printf("ping:%s\n", pingIP);
		if (pingIP == NULL || *pingIP == '\0') {
			sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return ;
		} else {
			curtime = time(NULL);
			gsprintf(tempFile, "%s%ld.tmp", requestUser, curtime);
			printf("tempFile:%s\n", tempFile);
			gsprintf(pingCmd, "ping %s -c 1 | egrep -o \"[0-100]+%% packet loss\">%s",
						pingIP, tempFile);
			printf("pingCmd:%s\n", pingCmd);
			res = system(pingCmd);
			if (gstat(tempFile, &tbuf)<0) {
				perror("stat temp file\n");
				sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
				websDone(wp, 200);
				return ;
			}
			if ((tempFd = open(tempFile, O_RDONLY))<0) {
				perror("open temp file\n");
				sendRspHeadObj(wp, ARG_ERROR_MSG);
				sendRspFooterObj(wp);
				websDone(wp, 200);
				return ;
			}
			res = read(tempFd, pingResult, tbuf.st_size);
			pingResult[tbuf.st_size-1] = '\0';    //除去字符串后面带的\n 
			printf("pingresult:%s\n",pingResult);
			if (!strcmp(pingResult, PING_RESULT_FALSE)) {
				sendRspHeadObj(wp, "true", NULL);
				websWrite(wp, T("\"pingresult\":\"no response from %s\""),
						pingIP);
				sendRspFooterObj(wp);
			} else {
				sendRspHeadObj(wp, "true", NULL);
				websWrite(wp, T("\"pingresult\":\"%s is active\""),
						pingIP);
				sendRspFooterObj(wp);
			}
			close(tempFd);
			unlink(tempFile);
		}
	} else {
	    if (quit_flag) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}

/*************************************************************
 *
 *  ping2
 */
#if 0
void formPingHost2(webs_t wp, char_t * path, char_t * query)
{
	int i = 0;
/*
	printf("----kinan-pinghost2\n");
	char_t    requestUser[MAX_USRN_LEN] = {};
	char_t    *pingIP = NULL;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, requestUser, sizeof(requestUser)))
	{
		pingIP = websGetVar (wp, T("ping"), T(""));
		printf("ping:%s\n", pingIP);
		if(pingIP == NULL || *pingIP == '\0'){
			sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return ;
		}
		else{
			if(!Call(pingIP)){
				printf("====== webs no =====\n");
			}
			else{
				printf("====== webs yes =====\n");
			}
		}
	}
	else
	{
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);*/
	while(1){
		printf("loop %d\n", i++);
		sleep(1);
	}
}
#endif

/*************************************************************
 *
 *  与formPingHost的效果差不多但是等待的时间会少一些 
 *  -->> 改用CGI的方式
 */
void formPingHostv3(webs_t wp, char_t *path, char_t *query)
{
	printf("----kinan-pinghost3\n");
    struct timeval      tv;
	struct timeval      *sendtime;
	struct timeval      recvtime;
	struct timeval      different;
	struct sockaddr_in  host;
	struct sockaddr_in  recvhost;
	struct hostent      *address;
	struct icmphdr      *sendhdr;
	struct icmphdr      *recvhdr;
	struct ip           *iphdr;
	int    quit_flag = 0;
	
	int		sock;
	int 	loop;
	int 	ret;
	int 	max_loop_time = 10;
	int 	addrlen = sizeof(struct sockaddr);
	int 	sendlen = sizeof(struct icmphdr) + sizeof(long);
	int 	ttl = 64;
	int 	hdrlen = sizeof(struct icmphdr) + sizeof(struct ip);
	int 	seq = 0;
		
	char 	*sendbuf[64];
	char 	*recvbuf[64];
		
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	
	char_t    requestUser[MAX_USRN_LEN] = {};
	char_t    *pingIP = NULL;
	
	a_assert(wp);
	goformHead(wp);
	if (!authenLogin(wp, 
		    requestUser, 
		    sizeof(requestUser), 
		    &quit_flag)) {
		pingIP = websGetVar (wp, T("ping"), T(""));
		printf("ping:%s\n", pingIP);
		if (pingIP == NULL || *pingIP == '\0') {
			sendRspHeadObj(wp, ARG_ERROR_MSG);
			sendRspFooterObj(wp);
			websDone(wp, 200);
			return ;
		}
		
		sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(struct timeval));
		setsockopt(sock, IPPROTO_IP, IP_TTL, (int *)&ttl, sizeof(int));

		host.sin_family = AF_INET;
		if ((host.sin_addr.s_addr = inet_addr(pingIP)) != 0xffff) {
			address = gethostbyname( pingIP );
			if (address) {
				memcpy(&host.sin_addr , address->h_addr, address->h_length);
			}
		}
			
		sendhdr = (struct icmphdr *)sendbuf;
		sendhdr -> type = ICMP_ECHO;
		sendhdr -> code = 0;
		sendhdr -> checksum = 0;
		(sendhdr -> un).echo.id = (unsigned short)getpid();
		(sendhdr -> un).echo.sequence = seq;
	
		for(loop = 0; loop < max_loop_time ; loop++ )
		{
			(sendhdr -> un).echo.sequence = seq++;
			sendtime = (struct timeval *)(sendbuf+sizeof(struct icmphdr));
			gettimeofday(sendtime, NULL);
			if(sendto(sock, sendbuf, sendlen, 0, (struct sockaddr*)&host, addrlen)<0)
			{
				printf("%d sendto error\n",loop);
				break;
			}
			ret = recvfrom(sock, recvbuf, 64, 0,  (struct sockaddr*)&recvhost, &addrlen);
			printf("recvfrom::ret:%d\n", ret);
			gettimeofday(&recvtime, NULL);
			if (ret < 0){
				printf("%d recvfrom error\n",loop);
				break;
			}
			different.tv_sec = recvtime.tv_sec - sendtime->tv_sec;
			different.tv_usec = recvtime.tv_usec - sendtime->tv_usec;
			
			iphdr = (struct ip*)recvbuf;
			recvhdr = (struct icmphdr*)(recvbuf + 20);
			printf("Reply from %s: ", inet_ntoa(recvhost.sin_addr));
			printf("%d bytes  ",ret);
			printf("ttl=%d  ",iphdr->ip_ttl);
			printf("time=%1.4fms\n",(different.tv_sec)*1000.0 + (different.tv_usec)/1000.0);
			if(different.tv_sec >= 3){
				break;
			}
		}
		if(loop != max_loop_time){
			sendRspHeadObj(wp, "true", NULL);
			websWrite(wp, T("\"pingresult\":\"no response from %s\""),
						pingIP);
			sendRspFooterObj(wp);
		}
		else{
			sendRspHeadObj(wp, "true", NULL);
			websWrite(wp, T("\"pingresult\":\"%s is active\""),
					pingIP);
			sendRspFooterObj(wp);
		}
		close(sock);
		
	}
	else{
		if (quit_flag) {
            Quit(requestUser, wp->ipaddr);
		}
		sendRspHeadObj(wp, AUTHEN_ERRO_MSG);
		sendRspFooterObj(wp);
	}
	websDone(wp, 200);
}


