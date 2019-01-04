/*************************************************************
 *	Copyright (C), 2017-2021, Kinan Tech. Co., Ltd.	
 *	Version		:	km1.0
 *	Filename	:	websSession.c
 *	Description	:	因为goahead2.5没有session机制
 *					所以	给webservers添加session机制
 *					本模块包括sessionid的增删改查和保存加载
 *	Creator		:	Zeed
 *	Date		:	2017-8-14
 *	History		:	
 *	<author>    <time>    	<version >    	<desc>
 *	Zeed	    17/08/14  	1.0				build this moudle  
 *	Zeed 		17/11/06	1.0				Add extractKeyValue2()
 *************************************************************/
/************************** Includes *************************/
#include "websSession.h"    

/************************** Static   *************************/
static sessionList  sessions;  
static logoutTime_t  logout_s;  //注销登录

/************************** Code *****************************
 *
 *  获取sessions链表
 */ 
session_t get_sessions()
{
	return &sessions;
}

/*************************************************************
 *
 *  获取logout_s
 */ 
logoutTime_t* get_logout_s()
{
	return &logout_s;
}


/************************************************************* 
 *
 *  初始化sessions链表
 */ 
int sessionOpen()
{
    sessions.sessionHead = NULL;
	sessions.count = 0;

	logout_s.enable = 0;
	logout_s.times = 1;
	return 0;
}

/*************************************************************
 *
 *  关闭sessions链表
 */
int sessionClose ()
{
	clearSession(&sessions);
	logout_s.enable = 0;
	logout_s.times = 1;
	return 0;
}

/*************************************************************
 *
 *  创建一个session节点
 *  @param [in] username 根据username生成sessionid
 *  @return 新节点
 */
sessionNode* createSession (char *username)
{
    FILE          *session_fp;
	logoutTime_t  logout_opt;
	if (username == NULL || *username == '\0') {
		return NULL;
	}
	sessionNode* snp = (sessionNode* )malloc(sizeof(sessionNode));	
	memset (snp, 0, sizeof(sessionNode));
	
	strncpy(snp->username, username, sizeof(snp->username));
	snp->sessiontime = genSessionid (snp->username, snp->sessionid, 
			sizeof(snp->sessionid)); 
	snp->snpNext = NULL;

	session_fp = fopen(SESSIONID_SAVE_PATH, "r");
	if (session_fp == NULL) {
        perror("createSession::fopen");
		// 当前时间上加上默认过期时间
		snp->sessiontime += DEFAUTL_BEHIND_TIME;
	} else {
        fscanf(session_fp, "%1d%10lu", 
			&logout_opt.enable, &logout_opt.times);
		if (logout_opt.enable) {
            snp->sessiontime += logout_opt.times;
		} else {
            snp->sessiontime += DEFAUTL_BEHIND_TIME;
		}
	}
	return snp;
}

/*************************************************************
 *
 *  判断session列表是否为空
 *  @return 1-->>列表为空 	0-->>列表不为空
 */
int isEmpty (session_t spl)
{
	return NULL==spl->sessionHead;
}

/*************************************************************
 *
 *  判断session列表是否为满
 *  @return 1-->>列表为满 	0-->>列表不满
 */
int isFull (session_t spl)
{
	return MAX_SESSIONID_NUM==spl->count;
}

/*************************************************************
 *
 *  计算session列表节点个数
 *  @return 列表的节点个数
 */
int sizeSession (session_t spl)
{
	return spl->count;
}

/*************************************************************
 *
 *  向session列表具体某位置 插入session节点
 *  @param [in out] spl-->>session列表
 *  @param [in    ] pos-->>插入位置
 *  @param [in    ] username-->>用户名 节点根据username生成
 */
void insertSession (session_t spl, int pos, char *username)
{
    // 如果位置不符合标准则默认向链表的末尾插入
	if ((0 > pos) || ( sizeSession(spl) < pos))
	{
		pos = sizeSession(spl);
	}
	
	sessionNode* snp = createSession(username);
	// 当把新节点插入头节点位置时的处理
	if(0 == pos)
	{
		snp->snpNext = spl->sessionHead;
		spl->sessionHead = snp;
		// 元素个数加一
		spl->count++;
		return;
	}
	
	sessionNode* snp_new = spl->sessionHead;
	int i = 0;
	for(i = 1;i < pos; i++)
	{
		snp_new = snp_new->snpNext;
	}
	
	snp->snpNext = snp_new->snpNext;
	snp_new->snpNext = snp;
	
	spl->count++;
}

/*************************************************************
 *
 *  在session列表中寻找元素值为username的下标
 *  @param [in out] spl-->>session列表
 *  @param [in    ] username-->>被查询的用户名
 *  @return 成功返回下标，失败返回-1
 */
int findSession(session_t spl, char *username)
{
	int pos = 0;
	if (spl == NULL || spl->sessionHead == NULL) {
		return -1;
	}
	if (username == NULL || *username == '\0') {
		return -1;
	}
	sessionNode* snp = spl->sessionHead;
	while (snp != NULL) {
		if (!strncmp(snp->username,username, 
			        sizeof(snp->username))) {
			return pos;
		}
		pos++;
		snp = snp->snpNext;
	}
	if (pos == spl->count) {
		return -1;
	}
}

/*************************************************************
 *
 *  在session列表中寻找元素值为sessionid的下标
 *  @param [in out] spl-->>session列表
 *  @param [in    ] sessionid-->>被查询的sessionid
 *  @return 成功返回下标，失败返回-1
 */
int findSessionByid(session_t spl, char *sessionid)
{
	int pos = 0;
	if(spl == NULL || spl->sessionHead == NULL){
		return -1;
	}
	if (sessionid == NULL || *sessionid == '\0') {
		return -1;
	}
	sessionNode* snp = spl->sessionHead;
	while(snp != NULL)
	{
		if(!strncmp(snp->sessionid,sessionid,
		    sizeof(snp->sessionid))) {
			return pos;
		}
		pos++;
		snp = snp->snpNext;
	}
	if (pos == spl->count) {
		return -1;
	}
	
}

/*************************************************************
 *
 *  改变下标为pos的元素的值为username
 *  @param [in out] spl-->>session列表
 *  @param [in    ] pos-->>修改的位置
 *  @param [in    ] username-->>根据username生成新的节点
 *  @return 0 表示列表为空   
 *          1 表示修改成功
 *         -1 表示输入错误位置
 */
int modifySession(session_t spl, int pos, char *username)
{
	if (isEmpty(spl)) {
#ifdef PORJECT_KM01_DEBUG		
		printf("modifySession::empty!\n");
#endif
		return 0;
	}
	if ((pos < 0) || (pos > spl->count)) {
#ifdef PORJECT_KM01_DEBUG		
		printf("modifySession::you put wrong position! err!\n");
#endif
		return -1;
	}
	if (username == NULL || *username == '\0') {
		return -1;
	}
	sessionNode * snpt = spl->sessionHead;
	int i = 0;
	for (i = 0; i < pos; i++) {
		snpt = snpt->snpNext;
	}
	strncpy(snpt->username ,username, sizeof(snpt->username));
	snpt->sessiontime = genSessionid(username, snpt->sessionid, 
		sizeof(snpt->sessionid));
	return 1;	
}

/*************************************************************
 *
 *  读取pos下标的值 
 *  @param [in out] spl-->>session列表
 *  @param [in    ] pos-->>节点下标
 *  @return 下标对应的节点
 */
sessionNode *readSession (session_t spl, int pos)
{
	if (isEmpty(spl)) {
#ifdef PORJECT_KM01_DEBUG		
		printf("readSession::empty!\n");
#endif
		return NULL;
	}
	if ((pos < 0) || (pos > sizeSession(spl))) {
#ifdef PORJECT_KM01_DEBUG		
		printf("readSession::you put wrong position! err!\n");
#endif
		return NULL;
	}
	
	sessionNode *snpt = spl->sessionHead;
	int i = 0;
	for (i=0; i<pos; i++) {
		snpt = snpt->snpNext;
	}
	return snpt;		
}

/*************************************************************
 *
 *  删除pos下标的值
 *  @param [in out] spl-->>session列表
 *  @param [in    ] pos-->>节点下标
 *  @return 0: 列表为空 失败
 *         -1: pos参数错误
 *          1: 成功
 */
int delSession (session_t spl, int pos)
{
	if (isEmpty(spl)) {
#ifdef PORJECT_KM01_DEBUG		
		printf("delSession::empty!\n");
#endif
		return 0;
	}
	if ((pos < 0) || (pos > sizeSession(spl))) {
#ifdef PORJECT_KM01_DEBUG		
		printf("delSession::you put wrong position! err!\n");
#endif
		return -1;
	}
	// 删除头节点时的处理方式
	if (0 == pos) {
		sessionNode *snptr = spl->sessionHead;
		spl->sessionHead = spl->sessionHead->snpNext;
		free(snptr);
		snptr = NULL;
		// 节点元素个数减一
		spl->count--;
		return 1;
	}
	// 删除其他节点时的处理方式
	sessionNode *snpt = spl->sessionHead;
	int i = 0;
	for (i=1; i<pos; i++) {
		snpt = snpt->snpNext;
	}
	// 记录要删节点的地址
	sessionNode *snqt = snpt->snpNext;
	// 让删除节点的前一个节点连接删除节点的后一个节点
	snpt->snpNext = snqt->snpNext;
	free(snqt);
	snqt = NULL;
	spl->count--;
	return 1;
}

/*************************************************************
 *
 *  清除session列表 
 */
void clearSession(session_t spl)
{
	while (spl->sessionHead != NULL) {
		sessionNode *snp = spl->sessionHead;
		spl->sessionHead = spl->sessionHead->snpNext;
		free(snp);
		snp = NULL;
	}
	spl->count = 0;
}

/*************************************************************
 *
 *  遍历列表 并删除过期节点
 */
void travelDelSession (session_t spl)
{
	sessionNode* snpt = spl->sessionHead;
	int          pos, flag = 0;
	time_t       current_time;
	time(&current_time);

	while (snpt != NULL) {
		if (snpt->sessiontime < current_time) {
			flag = 1;
			pos = findSession(spl, snpt->username);
		} else {
#ifdef PORJECT_KM01_DEBUG			
			printf("travelDelSession::username-->>%s\n",
				   snpt->username);
#endif
		}
		// 指向下一个节点
		snpt = snpt->snpNext;
		if (1 == flag) {
			delSession(spl, pos);
			flag = 0;
		}
	}
}

/*************************************************************
 *
 *  往头部插入session节点 
 *  @param [in out] spl-->>session列表的地址
 *  @param [in    ] username-->>要插入的节点
 */
void pushHeadSession (session_t spl, char *username)
{
    if (username == NULL || *username == '\0') {
		return ;
	}
	insertSession(spl, 0, username);
}

/*************************************************************
 *
 *  往尾部插入session节点 
 *  @param [in out] spl-->>session列表的地址
 *  @param [in    ] username-->>要插入的节点
 */

void pushTailSession (session_t spl, char *username)
{
	if (username == NULL || *username == '\0') {
		return ;
	}
	insertSession (spl, sizeSession(spl), username);
}

/*************************************************************
 *
 *  产生sessionid 
 *  @param [in    ] username-->>要生成对应的username的sessionid
 *  @param [in out] sessionid-->>生成的sessionid
 *  @param [in    ] size-->>sessionid的大小
 *  @return 节点的时间
 */

time_t genSessionid (char *username, char *sessionid, int size)
{
	logoutTime_t *logout_times = NULL;
	time_t       cur_time;
	char         str_time[STR_TIME+1] = {};
	char         gen_sessionid[ORG_SESSIONID_LEN] = {}; //用户名+时间
	char         csessionid[C_SESSSIONID_LEN] = {};   //密文sessionid
	
    if (username == NULL || *username == '\0' || size <= 0) {
		return 0;
	}
	time(&cur_time);
	logout_times = get_logout_s();
#ifdef  PORJECT_KM01_DEBUG
	printf("genSessionid::cur_time=%ld\n",cur_time);
#endif
	if (logout_times->enable) {
	    cur_time += logout_times->times;
	}
	snprintf(str_time, sizeof(str_time), "%ld", cur_time);
	sprintf (gen_sessionid, "%-20s+%.10s", username, str_time);
	encString((const char *)gen_sessionid, csessionid, sizeof(csessionid));
	strncpy (sessionid, csessionid, size);
#ifdef  PORJECT_KM01_DEBUG	
	printf("genSessionid::cur_time=%ld\n",cur_time);
	printf("genSessionid::str_time=%s\n",str_time);
	printf("genSessionid::id=%s\n",gen_sessionid);
	printf("genSessionid::cSessionid=%s\n", csessionid);
#endif	
	return cur_time;
}

/*************************************************************
 *
 *  解密
 *  @param [in ] secrText-->>密文
 *  @param [out] clearText-->>解密后的明文(数组)
 *  @param [in ] size-->>明文大小
 */
void decString (const char *secrText, char *clearText, int size)
{
	int   iterator;
    int   i,j;
    char  Key[8] = "12345678";  //des key           
    char  part_secret_text[16] = {0};  
    char  part_clear_text[8] = {0};    
    char  *tmp_cleartext_ptr = clearText;   
    int    secret_len;
	if (secrText == NULL || *secrText == '\0') {
		return ;
	}
	secret_len = strlen(secrText);
    iterator = secret_len/16;
	// 密文必须是16的倍数
	if (secret_len%16 || size <= 0) {
        return ;   
	}
	if ((secret_len > 0) && (iterator<<3 <= size)) {
        for (i=0; i<iterator; i++) {
        	// 将密文按16长度分解
            for (j=0; j<16; j++) {
                part_secret_text[j] = (secrText)[(i<<4)+j];
            }
			// 生成子密钥
            SetKey(Key);  
			// 进行解密
            KickDes(part_clear_text, part_secret_text);         
            for (j=0; j<8; j++) {
                *tmp_cleartext_ptr++ = part_clear_text[j];
            }
        }
    }
}

/*************************************************************
 *
 *  加密 
 *  @param [in ] clearText-->>要加密的明文
 *  @param [out] secrText-->>加密后的密文
 *  @param [in ] size-->>加密后密文的大小
 */
void encString (const char *clearText, char *secrText, int size)
{
    char  Key[8] = "12345678";  //des key
    int   sessionid_len;        
    int   iterator;
    int   remainder;
    int   i,j;
    char  part_clear_text[8] = {};    //每次加密的明文
    char  part_encrypt_text[16] = {}; //每次加密后的密文
    char  *encrypt_ptr = secrText;

    if (clearText == NULL || *clearText == '\0' || size <= 0) {
        return ;
	}
    sessionid_len = strlen(clearText);
    iterator = sessionid_len/8;
    remainder = sessionid_len%8;

	// 设置加密密钥
    SetKey(Key);                        
    if (sessionid_len > 0) {
        if (remainder > 0 && (size >= (iterator+1)<<4)) {
            for (i=0; i<iterator+1; i++) {
                for (j=0; j<8; j++) {
                    part_clear_text[j] = (clearText)[(i<<3)+j];
                }
                PlayDes(part_encrypt_text,part_clear_text); //加密
                for (j=0; j<16; j++) {
                    *encrypt_ptr++ = part_encrypt_text[j];
                }
            }
        }
        else if (size >= iterator<<4) {
            for (i=0; i<iterator; i++) {
                for (j=0; j<8; j++) {
                    part_clear_text[j] = (clearText)[(i<<3)+j];
                }
                PlayDes(part_encrypt_text, part_clear_text);
                for (j=0; j<16; j++) {
                    *encrypt_ptr++ = part_encrypt_text[j];
                }
            }
        }
    }
}

/*************************************************************
 *
 *  分解键值 
 *  @param [in    ] buf-->>被分解的键值
 *  @param [in out] key-->>分解后的键
 *  @param [in out] value-->>分解后的值
 *  @param [in    ] d-->>分割符
 *  @return -1 分解失败 0 成功
 */
int parseKeyValue (char *buf, char **key, char **value, char *d)
{
	char *ptr = NULL;
	if ((buf==NULL) || (*buf == '\0')) {
		return -1;
	}

	if ((ptr = strrchr(buf, '\n'))!=NULL ||
	    (ptr = strrchr(buf, '\r'))!=NULL ) {
		*ptr = '\0';
	}

	if ((ptr = strstr(buf, d)) == NULL) {
		return -1;
	}
	
	*ptr++ = '\0';
	*key = buf;
	*value = ptr;

	return 0;
}

/*************************************************************
 *
 *  提取键值中的值 
 *  @param [in ] buf：原数据包含需要提取的键值 但不会保留原数据完整性
 *  @param [in ] key：键 [标识] 如果传入为NULL 那么只分解出由d分隔符后的数据
 *  @param [in ] d：键值间的分割符
 *  @param [out] value：提取出来的值
 *  @return -1 提取失败 0 成功
 */
int extractKeyValue2(char *buf, char *key, char *d, char **value)
{
    char  *ptr = NULL;
	char  keystr[32] = {};
	sprintf(keystr, "%s=", key);
    if ((buf == NULL) || (*buf == '\0')) {
        return -1;
    }

    if ((ptr = strrchr(buf, '\n')) != NULL || 
       (ptr = strrchr(buf, '\r')) != NULL) {
        *ptr = '\0';
    }

	if (key != NULL) { 
    	if ((ptr = strstr(buf, keystr)) == NULL) {
       	 	return -1;
    	}
		ptr += strlen(key) + 1;
    	*value = ptr;
    	while (*ptr) {
            if (*ptr == *d) {
                *ptr = '\0';
                break;
            }
			ptr++;
    	}
    } else {
		if ((ptr = strstr(buf, d)) == NULL) {
			return -1;
		}
		*ptr++ = '\0';
		*value = ptr;
	}
	return 0;
}

/*************************************************************
 *
 *  将sessions存入文件中 
 *  @param [in] slp：session列表
 *  @param [in] logoutPtr：注销用户信息
 *  @param [in] filename：文件路径 文件路径最好是绝对路径
 *  @return 0 成功 -1 失败
 */
int sessionSave(session_t slp, logoutTime_t *logoutPtr, char *filename)
{
	FILE   *fp_session;
	char   *tmp_file = "./sessions.tmp";
	sessionNode  *snpt = slp->sessionHead;

	if (filename == NULL || *filename == '\0' ||
		slp == NULL) {
         return -1;
	}
	fp_session = fopen(tmp_file, "w");
	if (fp_session == NULL) {
         return -1;
	}
	
	fprintf(fp_session, "%d%-10lu\n", logoutPtr->enable, logoutPtr->times);
	
	while (snpt != NULL) {
		fprintf(fp_session, "%-21s%-10lu%-65s\n", snpt->username,
			snpt->sessiontime, snpt->sessionid);
		// 指向下一个节点
		snpt = snpt->snpNext;
	}
	fclose(fp_session);

	// 删除之前存在的文件
	unlink(filename);
	// 重命名
	if (rename(tmp_file, filename) != 0) {
		perror("sessionSave::rename");
		return -1;
	}
	return 0;
}

/*************************************************************
 *
 *  将文件中的数据加载到链表中
 *  @param [out] logouts：注册用户信息
 *  @param [out] count：列表中节点数目
 *  @param [in ] filename：文件路径
 *  @return 新列表
 */
sessionNode* sessionLoad(logoutTime_t* logouts, int *count, char *filename)
{
	sessionNode  *session_node_head = (sessionNode*)malloc(sizeof(sessionNode));
	sessionNode  *session_node_ptr1;
	sessionNode  *session_node_ptr2;
	char         username[USRN_LEN+1];
	time_t       time;
	char         sessionid[C_SESSSIONID_LEN+1];
	FILE         *fp_session;

	session_node_ptr1 = session_node_ptr2 = session_node_head;

	if (filename == NULL || *filename == '\0') {
        return NULL;
	}
	fp_session = fopen (filename, "r");
	if (!fp_session) {
#ifdef  PORJECT_KM01_DEBUG
		printf("sessionLoad::fopen fail\n");
#endif
		return NULL;
	}
	
    fscanf(fp_session, "%1d%10lu", &logouts->enable, &logouts->times);
	
	*count = 0;
	while (fscanf(fp_session, "%21s%10ld%65s", username, &time, sessionid)!=EOF)
	{
		*count += 1;
		session_node_ptr2 = (sessionNode*)malloc(sizeof(sessionNode));
		strncpy(session_node_ptr2->username, username, 
			    sizeof(session_node_ptr2->username));
		strncpy(session_node_ptr2->sessionid, sessionid,
			    sizeof(session_node_ptr1->sessionid));
		session_node_ptr2->sessiontime = time;

		session_node_ptr1->snpNext = session_node_ptr2;
		session_node_ptr1 = session_node_ptr2;
	}
	session_node_ptr1->snpNext = NULL;
	fclose(fp_session);
	return session_node_head->snpNext;
}




