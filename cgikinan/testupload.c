#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)

{
	int i = 0;
	int offset = 0;
	int filesize = 0;
	int res = 0;
	char *content_type = getenv("CONTENT_TYPE");
	fprintf(stderr, "1.testupload::ct->>%s\n", content_type);
	
	char *boundary = strchr(content_type, '=')+1;
	fprintf(stderr, "2.testupload::boundary->>%s\n", boundary);
	
	int content_len = atoi(getenv("CONTENT_LENGTH"));
	fprintf(stderr, "3.testupload::cl->>%d\n", content_len);

	char *word_f_stdin = (char*)malloc(content_len*sizeof(char));
//	fcntl(stdin,F_SETFL,fcntl(stdin,F_GETFL)|O_BLOCK);
	fprintf(stderr, "fseek::%d\n", fseek(stdin, 0, SEEK_CUR));
	while(content_len) {
		res = fread(word_f_stdin+offset, 1, content_len, stdin);
		if(res > 0) {
			content_len -= res ;
			offset += res;
			fprintf(stderr, "offset : %d\n", offset);
			continue;
		} else {
			fprintf(stderr, "res : %d\n", res);
			break;
		}
	}
	fprintf(stderr, "6.=== testupload::word_f_stdin ===\n");
	for(i=0; i<1024; i++) {
		fprintf(stderr, "%c", word_f_stdin[i]);
	}
	fprintf(stderr,"\n");
	fprintf(stderr, "5.1.testupload::fread num->>%d\n", res);
	
	

	//找到数据中第一次出现\r\n\r\n的地方
	char *file_dsrp_head = NULL;
	file_dsrp_head = word_f_stdin;
	char *filecontent1 = strstr(word_f_stdin, "\r\n\r\n");
	*filecontent1 = '\0';

	filecontent1 = filecontent1 + 4; //此时指向文件的起始位置
	int fileindex = filecontent1 - file_dsrp_head;
	fprintf(stderr, "7.testupload::fileindex->>%d\n", fileindex);
	filesize = content_len - fileindex;
	fprintf(stderr, "8.=== testupload::file_dsrp_head ===\n");
	for(i=0; i<fileindex; i++) {
		fprintf(stderr, "%c", file_dsrp_head[i]);
	}
		
	//找到boundary出现的地方 向前移动4个
	char n_b[128] = {};
	sprintf(n_b, "--%s", boundary);
	char *tmp = strstr(filecontent1, n_b);
	tmp = tmp - 2;
	*tmp = '\0';
	filesize = tmp - filecontent1;
	fprintf(stderr, "9.testupload::filesize->>%d\n", filesize);
	fprintf(stderr, "10.=== testupload::file_content_1 ===\n");
	for(i=0; i<filesize; i++) {
		fprintf(stderr, "%c", filecontent1[i]);
	}

	free(word_f_stdin);
	word_f_stdin = NULL;
	fprintf(stderr, "done\n");
	return 0;
}
