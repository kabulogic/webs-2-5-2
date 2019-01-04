/*****************************************************************************
* Name: types.h
* Copyright(C): 2017-2021 @ R&D of Kinan Comp.
*
* Description:
*
* Creator: Alex
* Date: 2017-06-26
******************************************************************************/


#ifndef _TYPES_H
#define _TYPES_H

#include "inf_public.h"
#include <time.h>
#include "macro.h"

//#include "../des/tables.h"

#ifdef _cplusplus
extern "c" {
#endif

#ifndef TOTAL_CH_NUM
#define TOTAL_CH_NUM    KVM_CH
#endif

#define DOMAIN_NAME_LEN1 48

#ifndef IP_LEN
#define IP_LEN      32
#endif

#ifndef DEV_NAME_LEN
#define DEV_NAME_LEN    32
#endif

#ifndef NAME_LEN
#define NAME_LEN    20
#endif

#ifndef NAME_LEN_CN
#define NAME_LEN_CN     60
#endif

#if 0
#ifndef CMS_NAME_LEN
#define CMS_NAME_LEN                     32
#endif
#endif

#ifndef PSWD_LEN
#define PSWD_LEN    16
#endif

#ifndef MAC_LEN
#define MAC_LEN                            6
#endif

#ifndef LNAME_LEN
#define LNAME_LEN                          128
#endif
#ifndef MAX_OSD_NUM
#define MAX_OSD_NUM    4
#endif

#ifndef MAX_AREA_NUM
#define MAX_AREA_NUM      4
#endif

#define BYTE_TO_INT( byte )  ( (byte[0] << 24) | (byte[1] << 16) | (byte[2] << 8) | byte[3])
#define BYTE_TO_SHORT( byte )  ( (byte[0] << 8) | (byte[1] << 0) )

#ifndef ONE_DAY_SEC
#define ONE_DAY_SEC      (24*60*60)
#endif

#ifndef ONE_DAY_MSEC
#define ONE_DAY_MSEC      (ONE_DAY_SEC*1000)
#endif

#ifndef ONE_HOUR_MSEC
#define ONE_HOUR_MSEC      (60*60*1000)
#endif

#ifndef INT_DATA_TYPE
#define INT_DATA_TYPE    sizeof( int )
#endif

#ifndef SHORT_DATA_TYPE
#define SHORT_DATA_TYPE       sizeof( short )
#endif


#define MAX_USER_GROUP_NUM     16
#define MAX_USER_NUM_EACH_GRP  8


#define ALARN_LINK_SECT (( TOTAL_CH_MAX_NUM/8 ) + (TOTAL_CH_MAX_NUM%8)?1:0)

#define BIG_LITTLE_SWAP( swap, type )\
            {\
                u_32 data = *(swap);\
                *(swap) = ( type == INT_DATA_TYPE ) ?\
                ((data & 0xFF000000) >> 24) | ((data & 0x000000FF) << 24) |\
                ((data & 0x00FF0000) >> 8)  | ((data & 0x0000FF00) << 8 ):\
                ((data & 0xFF00) >> 8)  | ((data & 0x00FF) << 8);\
            }


#define __PRIVILEGE_DETAIL__

////#ifndef _INF_TYPES
#define _INF_TYPES
typedef unsigned char  u_8;
typedef unsigned short u_16;
typedef unsigned int   u_32;
typedef unsigned long long   u_64;

typedef char  s_8;
typedef short s_16;
typedef int   s_32;
#ifndef bool
typedef u_8   bool;
#endif
typedef s_32 fd_t;
typedef void callback_t;
typedef u_32 arg_t;
/*
typedef enum 
{
    FALSE = 0,
    TRUE  = 1,
}BOOL_E;
*/
////#endif /* _INF_TYPES */

typedef u_8 cfg_t;

typedef s_8 IP_t[16];
typedef s_8 MAC_t[20];
typedef s_8 Name_t[20];
typedef s_8 PPPOEName_t[32];
typedef s_8 Pswd_t[20];
typedef s_8 OSD_Name_t[64];
typedef s_8 Alarm_Name_t[64];


typedef struct {
 
    u_8 cX,cY,cHig,cWid;   
  
}area_t;

//typedef u_8 area_t[18][4]; /* Divided the screen into 18X22 squares */
#define SET_AREA( area, i, j )   ( area[i][j >> 3] |= ( 0x80 >> (j & 7)  ) )
#define CLR_AREA( area, i, j )   ( area[i][j >> 3] &= ~( 0x80 >> (j & 7)  ) ) 
#define CHECK_AREA( area, i, j ) ( area[i][j >> 3] & ( 0x80 >> (j & 7)  ) )

typedef enum{
    DEV_SUB_TYPE_KVM_HD,
    DEV_SUB_TYPE_KVM_MUL,
}dev_sub_type_t;

typedef struct {
    u_32 type_mode;/*KVM型号，如3061等*/
    u_8 sub_type;/*0-kvm,1-延长线*/
    u_8 enc_type;/*编码器最高支持编码类型，0-qcif，1-cif ，2-2cif，3-4cif*/
    u_8 total_ch;/*当前所有通道*/
    u_8 local_ch;/*当前本地通道*/
    u_8 edsp_num;   /*编码从CPU个数*/    
    u_8 net_ch;     /*网络通道数*/ 
    u_8 talk_in;    /*支持语音对讲数*/
    u_8 disk_num;   /*支持最大磁盘数*/    
    u_8 alarmIn_num;    /*支持最大报警输入数*/
    u_8 local_almIn;    /*支持本地最大报警输入数*/
    u_8 alarmOut_num;   /*支持本地最大报警输出数*/
    u_8 monitor_num;    /*支持同时监视器数*/
    u_8 prew_mode;      /*最大预览模式*/    
    u_8 net_num;        /*网口数*/
    u_8 usb_num;        /*USB数*/
    u_8 uart_num;       /*串口数*/
    u_8 res[12];
}dvrsys_t;
typedef struct {
    u_8    cType;          /* 0: local channel, 1: network channel */
    OSD_Name_t Name;
    IP_t   IP;             /* Only for network channel */
    u_32   lPort;
    Name_t User;           /* Only for network channel */
    Pswd_t Pswd;           /* Only for network channel */
}chinfo_t;

typedef struct {
    u_8 cStream;       /* 0; major stream, 1: minor stream */
    u_8 bMixStream;    /* 0: video stream, 1: V & A stream */
    u_8 cVOPType;      /* 0: BBP, 1: P */ 
    u_8 cVOPRate;      /* 10 ~~ 30 */
    u_8 cIPRate;       /* 10 ~~ 255 */
    u_8 cQuality;      /* 0: lowest, 1: low, 2: middle, 3: high, 4: highest*/
    u_8 cResolution;   /* 0: QCIF, 1: CIF, 2: 2CIF, 3: 4CIF */
    u_8 cBitRate;      /* 0: variable, other: ( 1 ~~  255) kbps */
    u_32 lMaxBitRate;  /* unit: kbps */
}video_t;

typedef struct {
    u_8 cColor;       /* 0 ~~ 255 */
    u_8 cSaturation;  /* 0 ~~ 255 */
    u_8 cContrast;    /* 0 ~~ 255 */
    u_8 cBrightness;  /* 0 ~~ 255 */
}image_t;

typedef struct {
    u_8  cTrans;
    u_16 sX, sY;
    u_16 sW, sH;
    s_8  *pcYUV;
}pic_t;

#ifndef WEEK
#define WEEK    7
#endif
#ifndef TIMES
#define TIMES    4
#endif
/*报警触发方式*/
typedef struct {
    u_8 bMonitor:    1;       /*监视器预览*/
    u_8 bVoice:      1;       /*声音报警*/
    u_8 bCenter:     1;       /*控制中心*/
    u_8 bTrigger1:   1;       /*触发输出1*/
    u_8 bTrigger2:   1;       /*触发输出2*/
    u_8 bTrigger3:   1;       /*触发输出3*/
    u_8 bTrigger4:   1;       /*触发输出4*/
}AlarmHnd_t;

#if 0
typedef struct {
    u_8  bOn[TIMES];
    u_32 sTime[TIMES][2];/* unit: minute, e.g. 12:30:15 => sTime = 12 * 60 + 30
                            sTime[i][0]: start time, sTime[i][1]: end time     */ 
}defend_t;
#endif
typedef struct {
    u_8 cTime[6];/* unit: minute, e.g. 12:30:15 => sTime = 12 * 60 + 30
                            sTime[i][0]: start time, sTime[i][1]: end time     */ 
}defend_t;


typedef struct {
    bool     bOn;
    /* defend */
    defend_t Defend[WEEK];
                     
    /* handle   */
    AlarmHnd_t OutTo;                     
    /* link cfg */
    u_8  bRecord[TOTAL_CH_MAX_NUM];  /* set bRecord[i] 1 to record channel i, else 0 */
    u_16 sPTZ[TOTAL_CH_MAX_NUM];     /*   method   points
                                  0x    F       FFF  
                                  method: 0: no ptz, 1 - preset, 2 - auto pan, 3 - pattern */
}alarm_t;


#ifndef OSD_TEXT_LEN
#define OSD_TEXT_LEN    64
#endif

typedef struct {
    u_8  bOn;           /* 1: turn on, 0: turn off */
    u_8  cAttribute;    /* 0: transparent and flashing, 1: transmparent and steadly 
                           2: opaque and flashing       3: opaque and steadly */
    u_8  bOnWeek;       /* Only for time OSD, 0: turn off week, 1: turn on week */ 
    u_8  cFormat;       /* Only for time OSD, 0: xxxx-xx-xx, 1: xxxx xx xx
                                              2: xxxx/xx/xx, 3: xx/xx/xxxx */
    u_8  cText[OSD_TEXT_LEN];
    u_16 sX0, sY0;
}OSD_t;
typedef struct {
    u_8  bOn;           /* 1: turn on, 0: turn off */
    u_8  cPosionType;      /*0 upper left,1 upper right, 2 lower left, 3 lower right*/
    u_8  cText[OSD_TEXT_LEN];
    u_16 sX0, sY0;
}OSD_LOCAL_t;



typedef struct {
    u_8 bCheck;       /* need password to manage */
    u_8 cLanguage;
    u_8 cMode;        /* 1: PAL, 2: NTSC */
    u_8 cTransparent; /* 56 ~~ 255 */

    u_8 cBrightness;
    u_8 cContrast;
    u_8 cColor;
    u_8 cSaturation;

    bool bCRT; 
    u_8  cVORes;        /*0-~{7G~}VGA    1-800*600_60   2-1024x768_60 3-1280x1024_60 
                               4-1366x768_60 5-1440x900_60   6-800x600_75   7-1024x768_75 
                               8-720P60 ,9-1080I50 10-1080I60,11-1080P25,12-1080P30*/
    bool bVga;			/*true:use vga , false : use bnc*/
    u_8 wRev;
                               
    u_32 t;                 /* screen protect time */
    
    s_8 sysID[64];
    s_8 sysName[64];
    u_16 sTotalChs;/*nvr total channels*/ 
}gui_t;

typedef struct {
    u_8  bEnglish;      
    u_8  bPrev:   1;      /* 1 used for tour ( loop preview ), 0 else  */
    u_8  bAlarm:  1;      /* 1 used for display alarm video, 0 else */
    u_8  bPlay:   1;      /* 1 used for playback, 0 else */
    u_8  bGUI:    1;      /* 1 used for GUI, 0 else */
    u_8  bNet:    1;       /*used for net */
    u_8  bRev:    3;
    
    u_8  cMatrix;         /* 1, 4, 6,8,9,10,13,16 */
    u_16 sCycleTime;     
    u_16 sCycleAlarmTime;
    u_16 sSequence[TOTAL_CH_MAX_NUM]; /* e.g. if cMaxtrix = 9, and preview channel 1 
                                     on the 8 matrix, then sSequence[8-1] = 1 */
}monitor_t;


typedef struct {
    u_8    cType;         /* 0; root, 1: administrator, 2: normal user */
    u_8    cPriority;  /* 0 ~ 255, root has the highest priority of 255 */

    u_16   sID;
    u_8    cGroup[NAME_LEN];

    s_8   Name[NAME_LEN];
    s_8   Pswd[NAME_LEN];
	s_8   newPswd[NAME_LEN];

    s_8  IP[16];
    s_8  MAC[20];

    struct {
        /* view */
        u_32 bNetPrev:    1;
        u_32 bNetPlay:    1;
        u_32 bLocalPlay:  1;
        u_32 bLogView:    1;

        /* control */
        u_32 bPTZ:        1;
        u_32 bAlarm:      1;
        u_32 bTalk:       1;
        u_32 bRecord:     1;

        /* manage */
        u_32 bCfg:        1;
        u_32 bSysMan:     1;
        u_32 bUserMan:    1;
        u_32 bDataMan:    1;


		
		u_32 bPort: 	   1;//端口访问总体权限
		u_32 bUserMng:		1;//用户管理总体权限
		u_32 bSecure:		1;//安全设置总体权限
		u_32 bSysMaintenance:	  1;//系统维护总体权限

		//权限细化
		//u_32 bNetPrev:	  1;//实时预览权限
		//u_32 bNetPlay:	  1;//网络回放权限
		//u_32 bLocalPlay:  1;//本地回放权限
		//u_32 bLogView:	  1;//日志预览权限
		
		/*detail*/
		u_32 bAddUser:		  1;//增加用户权限
		u_32 bAddGroup: 	1;//增加用户组权限
		u_32 bDelUser:	  1;//删除用户权限
		u_32 NetCfg:	  1;//网络配置权限
		
		u_32 SysTime:	  1;//设置系统时间权限
		u_32 PortCfg:	   1;//配置端口权限
		u_32 backupAndRecover:1;//备份和覆盖权限
		u_32 factoryReset:	   1;//恢复出厂设置权限
		
		u_32 rebootSys: 	   1; //重启系统权限
		u_32 RemoteUpdate:	  1;//远程升级功能

		struct {
				u_32 Mouse_left:	1;//鼠标左键
				u_32 Mouse_right:	1;//鼠标右键
		}privilege_hotkey;
		
    }privilege;
}UserCfg_t;

typedef struct UserInfo {
    UserCfg_t Cfg;

    u_16      sStatus; /* 0: off line */
    u_16      sFrom;   /* 0x01: localhost gui login,  0x10:remote guest login*/

    u_32      lIP;
    u_32      lTimes;
    time_t    tOn, tOff;
}UserInfo_t;



typedef struct {
	
    s_8   cCmd;
    s_8   Name[NAME_LEN];
    s_16  userNum;
	s_16  sID;

    #ifndef __PRIVILEGE_DETAIL__
	
    struct {

		u_32    PortMng:    1;   
		u_32    UserMng:    1;
		u_32    SysMng:     1;
		u_32    Security:   1;

		u_32    SysMaintain:1;

	}privilege;

	#else

    struct {
        /* view */
        u_32 bNetPrev:    1;
        u_32 bNetPlay:    1;
        u_32 bLocalPlay:  1;
        u_32 bLogView:    1;

        u_32 bAlarm:      1;
        u_32 bRecord:     1;
        u_32 bCfg:        1;
        u_32 bSysMan:     1;

		u_32 bPort: 	    1;//端口访问总体权限
		u_32 bUserMng:		1;//用户管理总体权限
		u_32 bSecure:		1;//安全设置总体权限
		u_32 bSysMaintenance:	  1;//系统维护总体权限

		/*detail*/
		u_32 bAddUser:		  1;//增加用户权限
		u_32 bAddGroup: 	1;//增加用户组权限
		u_32 bDelUser:	  1;//删除用户权限
		u_32 NetCfg:	  1;//网络配置权限
		
		u_32 SysTime:	  1;//设置系统时间权限
		u_32 PortCfg:	   1;//配置端口权限
		u_32 backupAndRecover:1;//备份和覆盖权限
		u_32 factoryReset:	   1;//恢复出厂设置权限
		
		u_32 rebootSys: 	   1; //重启系统权限
		u_32 RemoteUpdate:	  1;//远程升级功能
		//struct {
		u_32 Mouse_left:	1;//鼠标左键
		u_32 Mouse_right:	1;//鼠标右键
		//}privilege_hotkey;
		
    }privilege;

    #endif
	
	struct {
		
        //u_32 view[MAX_PORT_ACCESS_NUM];
        //u_32 ctrl[MAX_PORT_ACCESS_NUM];
        //u_32 reject[MAX_PORT_ACCESS_NUM];
		
		u_8  cPri[MAX_PORT_ACCESS_NUM];//0x01--view 0x02--ctrl 0x03--reject

        u_8   allPortView;
        u_8   allPortCtrl;
        u_8   allPortReject;
		u_8   allPortPri;  
		
	}portPriv;

	struct {
		
        //u_32 RdOnly[MAX_PORT_ACCESS_NUM];
        //u_32 RdWr[MAX_PORT_ACCESS_NUM];
        //u_32 reject[MAX_PORT_ACCESS_NUM];

		u_8   cPri[MAX_PORT_ACCESS_NUM];//0x01--reject 0x02--rd 0x03--wr

        u_8   allVirMediaRdOnly;
        u_8   allVirMediaRdWr;
        u_8   allVirMediaReject;
		u_8   allVirMediaPri;
		
	}virMediaPriv;

}UserGrp_t;


typedef struct AllUserGrpPrew{

    s_8     cCmd;
	s_8     cNum;
    s_8     Name[MAX_USER_GROUP_NUM][NAME_LEN];
	u_16    sID[MAX_USER_GROUP_NUM];

}AllUserGrpPrew_t;

typedef struct AllUserPrew{

	u_8    cCmd;
    u_8    cNum;

    u_8    cStatus[MAX_USER_GROUP_NUM<<3];
	u_8    cUserName[MAX_USER_GROUP_NUM<<3][NAME_LEN];
	u_8    cGrpName[MAX_USER_GROUP_NUM<<3][NAME_LEN];
	u_16   sGrpId[MAX_USER_GROUP_NUM<<3];

}AllUserPrew_t;

#if 0

typedef struct {
    u_8    cType;         /* 0; root, 1: administrator, 2: normal user */
    u_8    cPriority;  /* 0 ~~ 255, root has the highest priority of 255 */

    u_16   sID;
    u_16   sGroup;

    Name_t Name;
    Pswd_t Pswd;

    IP_t  IP;
    MAC_t MAC;
    u_8  res[2];

    struct {
        /* view */
        u_32 bNetPrev:    1;
        u_32 bNetPlay:    1;
        u_32 bLocalPlay:  1;
        u_32 bLogView:    1;

        /* control */
        u_32 bPTZ:        1;
        u_32 bAlarm:      1;
        u_32 bTalk:       1;
        u_32 bRecord:     1;

        /* manage */
        u_32 bCfg:        1;
        u_32 bSysMan:     1;
        u_32 bUserMan:    1;
        u_32 bDataMan:    1;
    }privilege;
}UserCfg_t;

typedef struct UserInfo {
    UserCfg_t Cfg;

    u_16      sStatus; /* 0: off line */
    u_16      sFrom;   /* 0x01: localhost gui login,  0x10:remote guest login*/

    u_32      lIP;
    u_32      lTimes;
    time_t    tOn, tOff;
}UserInfo_t;

#endif

typedef struct loginReq{

    u_32    lID;

    s_8    cUserName[DEV_NAME_LEN];

    s_8    cPassword[DEV_NAME_LEN];

}loginReq_t;

typedef struct loginCms{
   
    u_16 sLogin;
     
    u_32 lCMSIP;

    loginReq_t loginCMS;

}loginCms_t;

typedef struct loginCmsStatus{

    u_8  cStatus;

    loginCms_t loginInfo;  

}loginCmsStatus_t;
typedef struct {
    u_32 lBaudRate; /*  0 ~~ 14:  B50, B75, B110, B150, B300, B600, B1200, B2400, 
                                 B4800, B9600, B19200, B38400, B57600, B76800, B115200 */
    u_8  cDataBit;   /* 5, 6, 7, 8                        */
    u_8  cStopBit;   /* 1, 2                              */
    u_8  cParity;    /* 0: no,   1: odd,      2: even     */
    u_8  cFlowCtrl;  /* 0: none, 1: software, 2: hardware */
}COM_t;

typedef struct {
    u_16  sCh;

    COM_t COM422;
 
    u_8   cAddr,     /* Decode address */
          cProtocol; /* 0: Kinan, 1: Kalatel-312, 2: Panasonic,
                        3: Peloc-D,  4: Peloc-Di,    5: Samsung,   6: VCOM */ 
}PTZ_t;

typedef struct P3oE {
    IP_t   IP;
    PPPOEName_t User;
    Pswd_t Pswd;
}P3oE_t;    
typedef struct eth {
    u_8   cCardType;    /* 0: 100M/1000M auto 1: 1000M, 2: 100M, 3: 10M */
    MAC_t MAC;

    u_8  cUnsPort[2]; /*for net pre,cfg,snmp... default 5000*/

    u_8 cType;   /* 0x00: static no   3PoE, 0x01: DHCP no 3PoE, 
                    0x10: static with 3PoE, 0x11: DHCP with 3PoE */
    u_8 bAutoDNS;

    IP_t  IP, Mask, Gateway;
    u_16  sPort;  /* rt date server port */

    P3oE_t P3oE;

    IP_t DNS, BCast, MCast;
}eth_t;
#define GET_UNS_PORT( __pNetCfg )  \
    ( ((__pNetCfg)->eth[0].cUnsPort[1] << 8) | (__pNetCfg)->eth[0].cUnsPort[0] )

typedef struct ddns_struct {
	/* switch variable of DDNS service. 1: turn on; 0: turn off */
	u_8 ddns_switch;
	u_8 ddns_type;
	u_8 res[2];    /* reservd for alignning */
	s_8 serv_ip[IP_LEN];
	s_8 domain_name[DOMAIN_NAME_LEN1];
	s_8 usr_name[NAME_LEN];
	s_8 passwd[PSWD_LEN];
}ddns_t;

typedef struct {
    eth_t eth[MAX_ETH_NUM];

    struct {
        IP_t IP;
        u_8  cPath[24];
    }NFS;

    u_16 sWebPort, sSNMPPort,sSMTPort;

    /* remote host */
    struct {
        IP_t IP;
        u_16 sPort;
    }RHost;

}net_t;

typedef struct {
    u_8     cSTT;       /* sensitivity */
    area_t  Area[MAX_AREA_NUM];
    alarm_t AlarmCfg;
}IQD_t;
typedef struct {
  
    u_8 cAllVoice;
    u_8 cAllCenter;

    u_8 cVoice[TOTAL_CH_MAX_NUM/8];

    u_8 cCenter[TOTAL_CH_MAX_NUM/8];

}AlarmLink_t;


typedef struct {
    //AlarmHnd_t SigLost;   /* Video lost alarm configure */
    //AlarmHnd_t Motion;    /* Motion sense alarm configure*/
    u_8 cType;
    u_8 bRecord;
    alarm_t   SigLost,Motion,AlarmIn;
}AC_t;

typedef struct {
    u_8     cType;         /* 0: open, 1: close */
    Alarm_Name_t  Name;

    alarm_t AlarmCfg;
}AI_t;

typedef struct {
   u_16     sDelayTime;   /* 0: manual, other: 1 ~~ 0xFFFF second  */
   defend_t Defend[WEEK];
}AO_t;

typedef struct {
    AlarmHnd_t OutTo;
}AE_t;

typedef struct fileInfo {
    u_32   IP; 
    u_16   sCh;
    u_8    cType;      /* 'a': alarm record, 't': time record, 'm': manual record */
    u_8    cNum;
    time_t tStart,tEnd;          /* create time */

    s_8    cPath[128];  /* save path */
    u_32   lLen; 

    u_32   lOffset;
    bool   bSelect;
} fileInfo_t;

typedef struct condition {
    u_32 IP;
    u_16 sCh;
    u_8  cType;
    u_8  cRes;

    time_t t1, t2;
    s_8 cPath[128];
}search_t;

//KVM录像 摄像机列表
typedef struct  NvrCameraInfo
{
    u_32    lNvrID;                         //KVM ID
    u_32    lCamID;                         //CameraID
    s_8     cCameraName[DEV_NAME_LEN];          //Camera名称
    u_8     cDevIP[IP_LEN];                  //设备IP
    u_8     cDevMac[MAC_LEN];                //设备Mac
    u_16    sDevChan;                       //设备通道号,从0开始
    u_32    lDevType;                       //设备类型
    u_8     cDevUserName[DEV_NAME_LEN];          //设备用户名
    u_8     cDevPassword[DEV_NAME_LEN];          //设备密码
    u_16    sExtLength;                     //扩展长度
    u_8     cReserved[2];                    //保留	
}NvrCameraInfo_t;


typedef struct SysCfgFromCms{

    u_32   lNvrID;

    u_8    cNvrName[DEV_NAME_LEN];

    u_8    cDomainName[LNAME_LEN];               //kvm 域名
    u_8    cKvmIP[IP_LEN];

    u_32   lMinDiskFreeSpace;                    //min space allow
    u_32   lDelFileNums;                         //the file num will be del  when lNoDiskDispose = DISPOSE_DEL_FILES

    u_8    lDiskFullHnd;                         //hd full ? handle = del file:stop record

    u_8	   cRecPrevT;			//表示报警预录像时长，
    u_8    cRecDelayT;                     //表示报警延迟停止录像时长
    u_8    cRes;
    u_16   sChNum;
    u_16   lExtLen;
 
    u_8    SMTListIP[160];

    u_32   SMTListID[10];

}SysCfgFromCms_t;


typedef struct ChSchemeFromCms{

    u_32    lCamID;
    u_8     cRecPlan[WEEK][180];            //rec plan 

    u_8     cSchemeEnable;
    u_8     cRes[3];
    
}ChSchemeFromCms_t;

typedef struct{
    bool                bSchemeEnable;
    u_8                 cDevCh;

    u_32                lCamID;

    s_8                 cDevName[DEV_NAME_LEN];

    s_8                 IP[IP_LEN];

    MAC_t               MAC;
    u_8                 cVirCh;                        //0-NUL(链路断开), 1-CAM, 2-SMT
    u_8                 cLinkType;                      /*0:onvif  1-* private*/
    u_8                 cLinkPro;						/*0:tcp  1-* rtp*/
    u_8                 bCreate;
    u_32                lMajorSpeed;                         /*主码流传输速度*/
    u_32                lMinorSpeed;                         /*次码流传输速度*/
    u_32                lPort;
    u_32                lDevType;                       //设备类型0"IPC",1,"DVS",2"Encoder",3"Others"
    s_8                 cDevUserName[DEV_NAME_LEN];          //设备用户名
    s_8                 cDevPassword[DEV_NAME_LEN];          //设备密码
}NetChBasic_t;



typedef struct  RecCmdFromCms{

    u_32    lDevID;

    u_8     cRecordType;
    u_8     cReserved[3];

}RecordCmdFromCms_t;

typedef struct SmtOnline_t{

    s_8    cDevId[DEV_NAME_LEN];

    u_8    cDevIP[IP_LEN];

    u_32    cDevType;  //1=SMT

    u_8    bOnline;
    u_8    cRes[3];               //

}SmtOnline_t;

typedef enum{

    PORT_SNMP         = 161,
    PORT_RTP          = 202,
    PORT_HTTP         = 80,
    PORT_KVM_PTZ      = 8000,
    PORT_KVM_PLAYBACK = 9000,
    PORT_AUDIO_TALK   = 3060,
    PORT_SCAN         = 9981,
    PORT_UPDATE       = 251,
    PORT_NET_ALARM    = 6791,
    PORT_VMPLANE      = 8686,
    PORT_PUB_PTZ      = 90,
    PORT_PUB_PLAYBACK = 8111,
    PORT_SMT            =5000

}KVMPorts_t;


typedef  struct RecFileIndex {

    time_t   t1;      //录像开始时间
    time_t   t2;      //录像停止时间
    u_8     cType;    //文件类型，为0xFF时表示所有类型，用于搜索
    u_8     cStatus;  //文件状态
    u_16    sBlkRecIdx;  /*此录像片段在块文件中属于第几个录像片段, 从0开始计*/
    u_8     cMac[6];  //设备MAC地址，全为0xFF时表示所有设备，用于搜索
    u_16    sCh;      //设备通道，从0开始，0xFF时表示所有通道，用于搜索
    u_32    IP1;
    u_32    IP2;
    u_32    IP3;
    u_32    IP4;
    u_32    lOffset; //文件大小，用于文件索引信息，用于搜索返回
    /*返回给2216此录像片段所在的块BlkName: xx xxx xxxxx 硬盘号 分区号 块序号 
     * 以十进制表示  如0200100036 第3个硬盘第2分区的36号块*/
    u_32   BlkName;  
} RecFileIndex_t;


typedef  enum {
           ACCESS_LOCAL=0,
		   ACCESS_NETWORK,
		   ACCESS_NULL
	}AccessVideo;



typedef struct portAccessStatus{
    u_16  sNum;
	
	u_8   cName[NAME_LEN];

	AccessVideo AccessType;

	u_8   cStatus; //0 close 1 connected
	u_8   availability;
	
}PortAccessStatus_t;


typedef struct AccessPortCfg{
    s_16 sNum;
	u_8  cPortName[NAME_LEN_CN];
	u_8  cPortType;
	u_16 cResolution[2];//1920x1080
	u_8  cRefresh;//50,60HZ

}PortAccessCfg_t;

typedef struct Workstation{
    u_8   cWorkstationName[NAME_LEN];
	u_8   cPortName[NAME_LEN];
	
	u_8   cNum;
	u_8   cStatus;
	u_8   cRes[2];
	
	u_32  lPort;

}Workstation_t;

typedef enum{
	NO_ENCRYP=0,
	ENCRYP_DES,
	ENCRYP_AES128,
	ENCRYP_AES256
}encrypType;

typedef struct SecureCfg{
    //login limit
    u_8    cSSO;  //SINGLE SION ON 
	u_8    cPsswdAging;
	u_16   cPsswdAgingDays;

    u_8    cLogoutIdleUser;
	u_16   cLogoutIdleUserMin;
	u_8    cRes;

	//strong psswd
	u_8    cPsswdStrongRule;//bit 0 = start psswd strong rule bit 1 = at least one minuscules 
	u_16   sPsswdDepth;
	u_8    sPsswdLenMin;
	u_8    sPsswdLenMax;

	//login lock
	u_8    cEnableLock;
	u_8    cLockAccount;
	u_8    cTryUnlockTime;
	u_8    cLockAccountTimeing;
	
	u_16   sLockTime;
	u_8    cEncrypKvm;
	u_8    localReset;//?

	encrypType encryp;
	
}SecureCfg_t;

typedef enum{
	
    VERIFY_WAY_LOCAL=0,
	VERIFY_WAY_LDAP,
	VERIFY_WAY_RADIUS
	
}verifyWay;

typedef struct ldapCfg{

    u_8  cLdapServer[IP_LEN];
	
	u_32  cPort; 

	u_8   cLadpServerType;
	u_8   cScanDNS[IP_LEN];
    u_8   cTestUserName[NAME_LEN];
	u_8   cTestPsswd[PSWD_LEN];
	
}ldapCfg_t;

typedef struct radiusCfg{

    u_8    cServer[IP_LEN];
	u_8    cShareCode[PSWD_LEN];
	
	u_32   lPort;

	u_16   sTimeOut;
	u_16   sRetry;
	
}radiusCfg_t;

typedef struct verifyCfg{

    verifyWay   verify;
	ldapCfg_t    ldap;
	radiusCfg_t  radius;
	
}VerifyCft_t;

 typedef struct backupCfg{

    u_8 cMethod;

	u_16 backTime[4];

}BackupCfg_t;

typedef struct systemCtrl{

    u_8 cCmd;

	u_8 pingHost[IP_LEN];
     
}systemCtrl_t;



#ifdef _cplusplus
}
#endif

#endif

