/*****************************************************************************
* Name: usercfg.h
* Copyright(C): 2017-2021 @ R&D of Kinan Comp.
*
* Description:
*
* Creator: Alex
* Date: 2017-06-28
******************************************************************************/

#ifndef _USERCFG_H
#define _USERCFG_H

//#include "includes.h"

#ifdef _cplusplus
extern "c" {
#endif

#define USER_STATUS_OFF       0x0000
#define USER_STATUS_ON        0x0001
#define USER_STATUS_ABNORMAL  0xFFFF

#define USER_LOGIN_NONE         0x00
#define USER_LOGIN_LOCAL        0x01
#define USER_LOGIN_REMOTE       0x10
#define LOCALHOST_ADDR          "127.0.0.1"

#define _FILE_USER_INFO    "/var/kvm/user-info"
#define _FILE_USER_GROUP   "/var/kvm/user-group"

#define MAX_USER_TO_BUF        20
#define SUPER_USER_ID          0x1000
#define SUPER_USER_GRP         "SUPER_USER"



#define USER_ADD           0x00
#define USER_MOD           0x01
#define USER_DEL           0x02
#define USER_GET           0x03
#define USER_NEXT          0x04
#define USER_ON            0x05
#define USER_OFF           0x06
#define USER_PRE           0x07
#define USER_ONLINE        0x08
#define USER_GET_ALL       0x09


#define USER_GRP_ADD       0x00
#define USER_GRP_MOD       0x01
#define USER_GRP_DEL       0x02
#define USER_GRP_GET       0x03
#define USER_GRP_GET_ALL   0x04



/* for privilage check */
#ifdef _BIG_ENDIAN
#define PRI_NETPREV      ( 1 << 31 )
#define PRI_NETPLAY      ( 1 << 30 )
#define PRI_LOCALPLAY    ( 1 << 29 )
#define PRI_LOGVIEW      ( 1 << 28 )

#define PRI_ALARM        ( 1 << 27 )
#define PRI_RECORD       ( 1 << 26 )
#define PRI_CFG          ( 1 << 25 )
#define PRI_SYSMAN       ( 1 << 24 ) //系统管理

#define PRI_PORT         ( 1 << 23 ) //端口
#define PRI_USERMAN      ( 1 << 22 ) //用户管理
#define PRI_SECURE       ( 1 << 21 ) //安全管理
#define PRI_DATAMAN      ( 1 << 20 ) //系统维护?

#define PRI_ADDUSER      ( 1 << 19 )
#define PRI_ADDGRP       ( 1 << 18 )
#define PRI_DELUSER      ( 1 << 17 )
#define PRI_NETCFG       ( 1 << 16 )

#define PRI_SYSTIME      ( 1 << 15 )
#define PRI_PORTCFG      ( 1 << 14 )
#define PRI_BKANDRECOVER ( 1 << 13 )
#define PRI_FACTORYRESET ( 1 << 12 )

#define PRI_REBOOT       ( 1 << 11 )
#define PRI_REMOTEUPDATE ( 1 << 10 )
#define PRI_MOUSELEFT    ( 1 << 9  )
#define PRI_MOUSERIGHT   ( 1 << 8  )

#else
#define PRI_NETPREV      ( 1 << 0 )
#define PRI_NETPLAY      ( 1 << 1 )
#define PRI_LOCALPLAY    ( 1 << 2 )
#define PRI_LOGVIEW      ( 1 << 3 )

#define PRI_ALARM        ( 1 << 4 )
#define PRI_RECORD       ( 1 << 5 )
#define PRI_CFG          ( 1 << 6 )
#define PRI_SYSMAN       ( 1 << 7 )

#define PRI_PORT         ( 1 << 8 )
#define PRI_USERMAN      ( 1 << 9 )
#define PRI_SECURE       ( 1 << 10 )
#define PRI_DATAMAN      ( 1 << 11 )

#define PRI_ADDUSER      ( 1 << 12 )
#define PRI_ADDGRP       ( 1 << 13 )
#define PRI_DELUSER      ( 1 << 14 )
#define PRI_NETCFG       ( 1 << 15 )

#define PRI_SYSTIME      ( 1 << 16 )
#define PRI_PORTCFG      ( 1 << 17 )
#define PRI_BKANDRECOVER ( 1 << 18 )
#define PRI_FACTORYRESET ( 1 << 19 )

#define PRI_REBOOT       ( 1 << 20 )
#define PRI_REMOTEUPDATE ( 1 << 21 )
#define PRI_MOUSELEFT    ( 1 << 22 )
#define PRI_MOUSERIGHT   ( 1 << 23 )

#endif

#define UNKNOW_USER      ( 0 - 1 )
#define UNKNOW_UID       ( 0 - 1)

#ifdef _USERCFG_C
#define USERCFG_API
#else
#define USERCFG_API    extern
#endif

#if 0
typedef struct login {
    u_8 cName;
    u_8 cPswd;
}login_t;
#endif

USERCFG_API s_32 INF_InitUser_API( void );
USERCFG_API s_32 INF_User_API( u_16 sCmd, UserInfo_t *pUserInfo );
USERCFG_API s_32 INF_PrivilageCheck_API( s_8 *who, u_32 what );
USERCFG_API s_32 INF_InitSnmpUser_API( void );
USERCFG_API s_32 INF_UserGrp_API( UserGrp_t *pGrp );
USERCFG_API s_32 INF_GetAllUserGrp_API( AllUserGrpPrew_t *pGrpBaseInfo,s_8 *pUser,s_8 *IP );
USERCFG_API s_32 INF_GetAllUser_API( AllUserPrew_t *pAllUser,s_8 *pUser, s_8 *IP );




#ifdef _cplusplus
}
#endif


#endif

