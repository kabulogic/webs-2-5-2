#include "../kinan/websSession.h"
#include "cgic.h"
#include "authenBySessionid.h"
#include <time.h>

#define  PING_RESULT_FALSE     "100% packet loss"

int cgiMain()
{
	char    pingIP[17] = {};
	char    pingCmd[128] = {};       
	char    tempFile[32] = {};
	char    pingResult[32] = {};
	time_t  curtime;
	int     tempFd, res;
	struct stat tbuf;
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

	if(cgiFormString("ping", pingIP, sizeof(pingIP)) == cgiFormSuccess) {
		time(&curtime);
		sprintf(tempFile, "%lu.tmp",  curtime);
		fprintf(stderr, "cgiping::tempFile:%s\n", tempFile);
		sprintf(pingCmd, "ping %s -c 1 | egrep -o \"[0-100]+%% packet loss\">%s",
		    pingIP, tempFile);
		fprintf(stderr, "cgiping::pingCmd:%s\n", pingCmd);
		res = system(pingCmd);
		if(stat(tempFile, &tbuf)<0) {
			fprintf(stderr, "cgiping::stat temp file\n");
			goto FAIL;
		}
		if((tempFd = open(tempFile, O_RDONLY))<0) {
			fprintf(stderr, "cgiping::open temp file\n");
			goto FAIL;
		}
		res = read(tempFd, pingResult, tbuf.st_size);
		pingResult[tbuf.st_size-1] = '\0';    //除去字符串后面带的\n 
		if(!strcmp(pingResult, PING_RESULT_FALSE)){
			printf("{\"status\":\"true\",");
			printf("\"msg\":\"%s\",", pingIP);
			printf("\"data\":\"no response from %s\"}", pingIP);
		}
		else{
			printf("{\"status\":\"true\",");
			printf("\"msg\":\"%s\",",pingIP);
			printf("\"data\":\"%s is active\"}", pingIP);
		}
		close(tempFd);
		unlink(tempFile);
		return 0;
	} else {
		fprintf(stderr, "cgiping::get ping argument failed\n");
		goto FAIL;
	}
	
FAIL:
	fprintf(stderr, "cgiping::fail to ping\n");
	printf("{\"status\":\"false\",\"msg\":\"fail to ping\"}");
	return 1;
}

