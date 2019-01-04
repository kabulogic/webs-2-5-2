/****************************************************************
*  Copyright (c) 2017-2021,Kinan Tech. Co., Ltd.
*  Version     :    km1.0
*  Filename    :    upload.c
*  Description :    upload file for remoteupgrade
*  Creator     :    zeed
*  Date        :    2017-09-20
*  History     :
*  <author>    <time>    <version>    <desc>
*  zeed        17/09/20   1.0          build this moudle
*
******************************************************************/

#include "../kinan/websSession.h"
#include "cgic.h"
#include "authenBySessionid.h"

#define BufferLen 1024
int cgiMain(void)
{
	cgiFilePtr file;
	int        targetFile;
	mode_t     mode;
	char       name[128];
	char       fileNameOnServer[64];
	char       contentType[1024];
	char       buffer[BufferLen];
	int        size;
	int        got;

	char       **arrayCookie, **arrayCookieStep;
	char       cookieValue[65];
	char       username[21] = {};
	char       *nameFromQuery = NULL;
	char       nameKey[16] = {};
	int        funcReturn;
/*
 *  获取cookie值
 */
 #if 0
 	if (cgiCookies(&arrayCookie) != cgiFormSuccess) {
		fprintf(stderr, "cgiupload::could not get cookies\n");
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
	fprintf(stderr, "upload::cookieValue:%s\n", cookieValue);
#endif

	cgiHeaderContentType("text/html");
	
	if(/*!authenBySessionid(cookieValue, username, sizeof(username))*/1) {
		fprintf(stderr, "cgiupload::username=%s\n", username);
		char *content_t = getenv("CONTENT_TYPE");
		fprintf(stderr, "cgiupload::content-type=%s\n", content_t);
		char *content_len = getenv("CONTENT_LENGTH");
		fprintf(stderr, "cgiupload::content-length=%s\n", content_len);
		int content_l = atoi(content_len);

		if(cgiFormFileName("file", name, sizeof(name)) != cgiFormSuccess){
			nameFromQuery = getenv("QUERY_STRING");
			if (nameFromQuery == NULL || *nameFromQuery == '\0') {
				fprintf(stderr,"upload::could not retrieve filename\n");
				goto FAIL;
			} else {
				sscanf(nameFromQuery, "%[^=]=%[^=]", nameKey, name);
				fprintf(stderr, "cgiupload::second way to get filename=%s\n", name);
			}
		}
		fprintf(stderr,"cgiupload::filename=%s\n", name);
		cgiFormFileSize("file", &size);
		cgiFormFileContentType("file", contentType, sizeof(contentType));
		if ((funcReturn=cgiFormFileOpen("file", &file)) != cgiFormSuccess) {
			fprintf(stderr, "cgiupload::could not open the file return-->%d\n", funcReturn);
				goto FAIL;
		}
		
		strcpy(fileNameOnServer, name);
		mode=S_IRWXU|S_IRGRP|S_IROTH;
		targetFile = open(fileNameOnServer, O_RDWR|O_CREAT|O_TRUNC|O_APPEND,mode);
		if(targetFile < 0){
			fprintf(stderr, "cgiupload::could not create the new file, %s\n", fileNameOnServer);
			goto FAIL;
		}
		while(cgiFormFileRead(file, buffer, BufferLen, &got) == cgiFormSuccess){
			if(got>0)
				write(targetFile, buffer, got);
		}
		cgiFormFileClose(file);
		close(targetFile);
		goto END;
	}
	else{
		fprintf(stderr, "cgiupload::authen failed\n");
		goto FAIL;
	}
			
FAIL:
	fprintf(stderr, "cgiupload::Failed to upload\n");
	printf("{\"status\":\"false\",\"msg\":\"failed to upload\"}");
	return 1;
END:
	printf("{\"status\":\"true\",\"msg\":\"%s has been uploaded\"}", fileNameOnServer);
	return 0;
}
