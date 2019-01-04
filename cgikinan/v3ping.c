#include "../kinan/websSession.h"
#include "cgic.h"
#include "authenBySessionid.h"
#include "ping.h"

struct hostent * pHost = NULL;		//保存主机信息
int sock_icmp;				//icmp套接字
int nSend = 1;
char *IP = NULL;

void Call(char *argip)
{
	struct protoent *protocol;
	struct sockaddr_in dest_addr; 	//IPv4专用socket地址,保存目的地址

	in_addr_t inaddr;		//ip地址（网络字节序）

	if ((protocol = getprotobyname("icmp")) == NULL)
	{
		fprintf(stderr, "v3ping::getprotobyname failed\n");
		return ;
	}

	/* 创建ICMP套接字 */
	//AF_INET:IPv4, SOCK_RAW:IP协议数据报接口, IPPROTO_ICMP:ICMP协议
	if ((sock_icmp = socket(PF_INET, SOCK_RAW, protocol->p_proto/*IPPROTO_ICMP*/)) < 0)
	{
		fprintf(stderr, "v3ping::open socket failed\n");
		return ;
	}
	dest_addr.sin_family = AF_INET;

	/* 将点分十进制ip地址转换为网络字节序 */
	if ((inaddr = inet_addr(argip)) == INADDR_NONE)
	{
		/* 转换失败，表明是主机名,需通过主机名获取ip */
		if ((pHost = gethostbyname(argip)) == NULL)
		{
			fprintf(stderr, "v3ping::gethostbyname failed\n");
			return ;
		}
		memmove(&dest_addr.sin_addr, pHost->h_addr_list[0], pHost->h_length);
	}
	else
	{
		memmove(&dest_addr.sin_addr, &inaddr, sizeof(struct in_addr));
	}

	IP = argip;
	signal(SIGINT, Statistics);
	while (nSend < 10)
	{
		int unpack_ret;
		
		SendPacket(sock_icmp, &dest_addr, nSend);
		fprintf(stderr, "v3ping::send over\n");	
		unpack_ret = RecvePacket(sock_icmp, &dest_addr);
		fprintf(stderr, "v3ping::first recve\n");
		if (-1 == unpack_ret)	//（ping回环时）收到了自己发出的报文,重新等待接收
		{
			RecvePacket(sock_icmp, &dest_addr);
		}	
		sleep(1);
		nSend++;
	}
	Statistics(0);	//输出信息，关闭套接字
}

int cgiMain()
{
	char    pingIP[17] = {};
	char	**arrayCookie, **arrayCookieStep;
	char	cookieValue[65];
	char	username[21] = {};
/*
 *	获取cookie值
 */
	if (cgiCookies(&arrayCookie) != cgiFormSuccess) {
		fprintf(stderr, "cgiping::could not get cookies\n");
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
	fprintf(stderr, "cgiping::cookieValue:%s\n", cookieValue);
	cgiHeaderContentType("text/html");

	if(!authenBySessionid(cookieValue, username, sizeof(username))) {
		if(cgiFormString("ping", pingIP, sizeof(pingIP)) == cgiFormSuccess) {
			Call(pingIP);	
		} else {
			fprintf(stderr, "cgiping::get ping argument failed\n");
			goto FAIL;
		}

	} else {
		fprintf(stderr, "cgiping::authen failed\n");
		goto FAIL;
	}
FAIL:
	fprintf(stderr, "cgiping::fail to ping\n");
	printf("{\"status\":\"false\",\"msg\":\"fail to ping\"}");
	return 1;
}


