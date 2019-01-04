/***************************************************************************************
* file name:  websMacro.h
* description:
* creator:    Zeed
* date:       2017-12-20
***************************************************************************************/
#ifndef _WEBSMACRO_H
#define _WEBSMACRO_H

#ifdef _cplusplus
extern "c" {
#endif
// 各数组的长度
#define MAX_OG_SESSIONID_LEN    32
#define MAX_PSWD_LEN     16
#define MAX_USRN_LEN     20
#define MAX_GRPN_LEN     20
#define MAX_GRP_NUM    16
#define MAX_SESSIONID_LEN    64

// 验证结果	
#define    AUTHEN_ERRO       -1
#define    AUTHEN_SUCCESS    0

// 消息头
#define    SRCH_USR_NOFND      "false", "未找到该用户"
#define	   SRCH_GRP_NOFND      "false", "未找到该用户组"
#define    DEL_GRP_FAIL        "false", "删除用户组失败"
#define    DEL_GRP_SUCCESS     "true",  "删除用户组成功"
#define    DEL_USR_SUCCESS     "true",  "删除用户成功"
#define	   AUTHEN_ERRO_MSG     "false", "登录已过期"
#define    AUTHEN_SUCCESS_MSG  "true",  "验证通过"
#define    LOGIN_ERRO_MSG      "false", "用户名或密码错误" 
#define    LOGIN_SUCCESS_MSG   "true",  "登录成功" 
#define    LOGOUT_SUCCESS_MSG  "true",  "登出成功"	
#define    PASSWD_ERRO_MSG     "false", "密码错误"
#define    SET_SUCCESS_MSG     "true",  "设置成功"
#define    SET_FAIL_MSG        "false", "设置失败"
#define    ARG_ERROR_MSG	   "false", "参数错误"
#define    LOG_EMPTY           "false", "该内容不存在"

#ifdef _cplusplus
}
#endif

#endif //_WEBSMACRO_H 

