/***************************************************************************************
* file name:   cfg.h
* description:
* creator:     Alex
* date:        2017-06-12
***************************************************************************************/

#ifndef __CFG_H__
#define __CFG_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef unsigned char  u_8;
typedef unsigned short u_16;
typedef unsigned int   u_32;
typedef unsigned long long   u_64;

typedef char  s_8;
typedef short s_16;
typedef int   s_32;

////typedef u_8   bool;

typedef s_32 fd_t;
typedef void callback_t;
typedef u_32 arg_t;

typedef enum 
{
/**/    False = 0,
		True  = 1,
}BOOL_E;

#endif /* _INF_TYPES */

/*最后值有待商议*/
#define NAME_LEN    20
#define IP_LEN      16
#define MAX_ETH_NUM 32
#define MAX_HD_NUM  64
#define DOMAIN_NAME_LEN1 16
#define MAX_PORT_ACCESS_NUM  64
#define MAC_LEN     32
#define PSWD_LEN    16

typedef u_8 cfg_t;

typedef s_8 IP_t[16];
typedef s_8 MAC_t[20];
typedef s_8 Name_t[20];
typedef s_8 PPPOEName_t[32];
typedef s_8 Pswd_t[20];
typedef s_8 OSD_Name_t[64];
typedef s_8 Alarm_Name_t[64];

typedef struct kLoginInfo{

    struct tm t; //tm系统时间结构体

	u_8    sIp[32];

}kLoginInfo_t;


typedef struct KvmSystemInfo{

	u_8    loginUser[NAME_LEN];
	
    kLoginInfo_t curLogin;
	
    kLoginInfo_t lastLogin;

	u_8    cKvmName[NAME_LEN];

	u_8    cKvmIp[IP_LEN];

	u_8    cFirmware[NAME_LEN];

	u_8    cKvmModel[NAME_LEN];

	u_8    cLogServerIp[IP_LEN];

////netWorkType net;
    
	u_8    cPowerIn;//on = 1; off  = 0 

}KvmSystemInfo_t;

typedef struct eth {
    u_8   cCardType;    /* 0: 100M/1000M auto 1: 1000M, 2: 100M, 3: 10M */
    MAC_t MAC;

    u_8  cUnsPort[2]; /*for net pre,cfg,snmp... default 5000*/

    u_8 cType;   /* 0x00: static no   3PoE, 0x01: DHCP no 3PoE, 
                    0x10: static with 3PoE, 0x11: DHCP with 3PoE */
    u_8 bAutoDNS;

    IP_t  IP, Mask, Gateway;
    u_16  sPort;  /* rt date server port */

////P3oE_t P3oE;

    IP_t DNS, BCast, MCast;
}eth_t;


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

typedef struct CfgNTP {
////bool  bNTP;
    u_8   IP[16];
    u_16  sPtz  : 6;    //time zone: -12 ~ +13
    u_16  bDayLight : 1;  //daylight saving time enable
}CfgNTP_t;

typedef struct DiskCfg
{
    u_8     IsRecordDisk[MAX_HD_NUM];/*是否录像盘,0-磁盘不存在，1-录像盘，2-备份盘*/
    u_8     WorkDisk;                   /*工作磁盘，0~(HD_MAJOR_NUM-1)*/
    u_8     BackupDisk;                 /*备份盘，0~HD_MAJOR_NUM，默认为HD_MAJOR_NUM，即U盘*/
    u_8     IsOverWrite;                /*是否可以覆盖，0-可以覆盖，1-不可覆盖，默认为可以覆盖*/
    u_8     rev;
}DiskCfg_t;

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
	u_8  cPortName[NAME_LEN];
	u_8  cPortType;

}PortAccessCfg_t;

typedef struct Workstation{
    u_8   cWorkstationName[NAME_LEN];
	u_8   cPortName[NAME_LEN];
	
	u_8   cNum;
	u_8   cStatus;
	u_8   cRes[2];
	
	u_32  lPort;

}Workstation_t;


typedef struct {
    u_8    cType;         /* 0; root, 1: administrator, 2: normal user */
    u_8    cPriority;  /* 0 ~ 255, root has the highest priority of 255 */

    u_16   sID;
    u_16   sGroup;

    s_8   Name[20];
    s_8  Pswd[20];

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

    s_8   Name[NAME_LEN];
    s_16  userNum;
	s_16  ID;
	
	struct {
		
        u_32 view[MAX_PORT_ACCESS_NUM];
        u_32 ctrl[MAX_PORT_ACCESS_NUM];
        u_32 reject[MAX_PORT_ACCESS_NUM];

        u_8   allPortView;
        u_8   allPortCtrl;
        u_8   allPortReject;
		u_8   allPortPri;  
		
	}portPriv;

	struct {
		
        u_32 RdOnly[MAX_PORT_ACCESS_NUM];
        u_32 RdWr[MAX_PORT_ACCESS_NUM];
        u_32 reject[MAX_PORT_ACCESS_NUM];

        u_8   allVirMediaRdOnly;
        u_8   allVirMediaRdWr;
        u_8   allVirMediaReject;
		u_8   allVirMediaPri;
		
	}virMediaPriv;

}UserGrp_t;


typedef struct HD_Info {

    s_8     cHD_Ver[32];/*此硬盘的数据库程序的版本号*/
    u_8     cRes[20];
    time_t  STime;    /*硬盘最早录像时间*/
    time_t  OTime;   /*硬盘覆盖开始时间*/
    time_t  ETime;    /*硬盘最晚录像时间*/
    u_8     cHD_Loc;    /*硬盘位置：0-本地盘，1-nfs盘，2-iscsi盘*/
    u_8     cHD_Type;   /*硬盘类型：0-录像盘，1-冗余盘，2-备份盘*/
    u_8     cHD_Attr;   /*硬盘属性：0-可读写， 1-只读，2-不可读写*/
    u_8     cHD_Grp;    /*硬盘所属组0-8*/

    /*硬盘大小(/proc/partitions记录的大小),k为单位,1T为10亿K*/
    u_32    Blocks;   
    
    /*整个硬盘的大小,不包含块的头部索引大小，以k为单位, 将四个分区的Size相加*/
    u_32    Size;      
    u_32    Used;      /*已写入硬盘的大小，以k为单位 将四个分区Used相加*/    
    u_32    Free;      /*硬盘剩余空间，k为单位,1T为10亿K,将四个分区Free相加*/

   /*覆盖的次数，0的话为还没开始覆盖即格盘后第一次使用，
     1的话为第一次正在覆盖，以此类推
   */
    u_32    RcvrNum;     

    /*硬盘格式化状态: 0-未格式化  1-正在格式化   2-已格式化 3-格式化出错*/
    u_8     cFmtStat;
    
    /* 硬盘工作状态: 0-空闲,可以录像  1-硬盘满 2-硬盘录像时出错 */
    u_8     cWkStat;    

    u_16    sMaxVch;   /*曾经在此硬盘上录像的最大虚拟通道数*/

    u_8     cPts;      /*实际分区数*/
    u_8     cLogHDTag; /*是否是日志盘*/
    u_8     cMac[MAC_LEN];/*设备的MAC地址，用于表示此日志是哪台设备的*/

    time_t  SftTime;    /*该磁盘的慢速格式化时间*/
    time_t  QftTime;    /*最后一次快速格式化时间*/

    u_8     cExtTag;   /*是否有扩展信息*/
    u_8     cRev[3]; 
    u_32    ExtLen;    /*扩展信息长度*/

}HD_Info_t; 

#if 1
/* peer action define */
#define PEER_GET    0x0  //获取系统参数
#define PEER_SET    0x1  //设置系统参数
#define PEER_CTR    0x2  //系统控制
#define PEER_STA    0x3  //系统状态
#define PEER_RET    0x4  //回复

//cfg
#define CFG_CHANNEL    0x00
#define CFG_PREVIEW    0x01
#define CFG_RECORD     0x02
#define CFG_ALARM      0x03
#define CFG_USER       0x04
#define CFG_COM        0x05
#define CFG_NET        0x06
#define CFG_PTZ        0x07
#define CFG_GUI        0x08
#define CFG_NTP        0x09
#define CFG_DDNS       0x0A
#define DEV_SYSINFO    0xA0
#define CFG_LOGIN      0xB0
#define CFG_SYSTEM_INFO         0xC0
#define CFG_SG_INFO             0xD0
#define CFG_WIFI_INFO	        0xE0
#define CFG_3G_INFO             0xF0
#define CFG_ONEKEY		        0x0B
#define CFG_PORT_ACCESS         0x10
#define CFG_PORT_ACCESS_STATUS  0X11
#define CFG_WORKSTATION         0x12
#define CFG_SECURE              0x13
#define CFG_VERIFY              0x14
#define CFG_BACKUP              0x15

//stat
#define SYS_STAT( x ) ( x >> 8 )
#define STAT_DISK     ( 0x0 )
#define STAT_DVR      ( 0x1 )
#define STAT_VIDEO    ( 0x2 )
#define STAT_ALARM    ( 0x3 )
#define STAT_DVDRW    ( 0x4 ) //dvdrw
#define STAT_PREV     ( 0x5 )
#define STAT_REC      ( 0x6 )
#define STAT_SYSTIME  ( 0x8 )
#define STAT_KVM_LOGIN_CMS   ( 0x7 )

#define STAT_RECORD_START    ( ( STAT_VIDEO << 8 ) | 0x00 )
#define STAT_RECORD_STOP     ( ( STAT_VIDEO << 8 ) | 0x01 )
#define STAT_NETPREV_START   ( ( STAT_VIDEO << 8 ) | 0x02 )
#define STAT_NETPREV_STOP    ( ( STAT_VIDEO << 8 ) | 0x03 )
#define STAT_VIDEO_LOST      ( ( STAT_VIDEO << 8 ) | 0x04 )
#define STAT_VIDEO_GOOD      ( ( STAT_VIDEO << 8 ) | 0x05 )

#define STAT_KVM_BOOT        ( ( STAT_DVR << 8 ) | 0x00 )
#define STAT_KVM_READY       ( ( STAT_DVR << 8 ) | 0x01 )
#define STAT_KVM_CLOSE       ( ( STAT_DVR << 8 ) | 0x02 )
#define STAT_PTT_START       ( ( STAT_DVR << 8 ) | 0x03 )
#define STAT_PTT_STOP        ( ( STAT_DVR << 8 ) | 0x04 )

#define STAT_ALARM_START     ( ( STAT_ALARM << 8 ) | 0 )
#define STAT_ALARM_STOP      ( ( STAT_ALARM << 8 ) | 1 )

//ctrl

#define CTRL_PTZ        0x01
#define CTRL_RECORD     0x02
#define CTRL_PLAY       0x03
#define CTRL_SEARCH     0x04
#define CTRL_CP         0x05
#define CTRL_RM         0x06
#define CTRL_HD         0x07
#define CTRL_ALARM      0x08
#define CTRL_RUN        0x09
#define CTRL_TIME       0x0A
#define CTRL_LOG        0x0B
#define CTRL_UPDATE     0x0C
#define CTRL_BACKUP     0x0D
#define CTRL_LOGIN      0x0E
#define CTRL_CFG        0x0F
#define CTRL_GUI		0x10
#define CTRL_DVDRW		0x11
#define CTRL_VO_ZOOM    0x12
#define CTRL_DISCOVERY  0x13
#define CTRL_MANAGE     0x14
#define CTRL_GET_CAM_NET		0x15
#define CTRL_SET_CAM_NET		0x16
#define CTRL_ONEKEY		        0x17

#define CTRL_OPEN_PTT    0xF1
#define CTRL_CLOSE_PTT   0xF0

#endif
