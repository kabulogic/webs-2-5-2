/*****************************************************************************
* Name: syscfg.h
* Copyright(C): 2017-2021 @ R&D of Kinan Comp.
*
* Description:
*
* Creator: Alex
* Date: 2017-05-25
******************************************************************************/

#ifndef _SYSCFG_H
#define _SYSCFG_H

//#include "includes.h"
#include "types.h"

#ifdef _cplusplus
extern "c" {
#endif


/***************************************************************************************
* types for do system config 
***************************************************************************************/
typedef struct PrivacyArea {
    bool bOn;
    area_t area[MAX_AREA_NUM];
}PArea_t;

typedef struct CfgCh
{
    u_8  cType; /* 0: channel basic info, 1: major video compress,  2: minor video compress
                   3: image parameter,    4: OSD,                   5: privacy area
                   6: motion detection,   7: view obsstruct,        8: signal lost 
                   9: voice volume */
    u_16 sCh;
    union 
    {
        chinfo_t BasicInfo;         /* cType = 0  */
        video_t  MajorVideo,        /* cType = 1  */
                 MinorVideo;        /* cType = 2  */
        image_t  Image;             /* cType = 3  */
        OSD_t    OSD[MAX_OSD_NUM];  /* cType = 4  */
        PArea_t  PArea;             /* cType = 5  */ 

        IQD_t    Motion,            /* cType = 6  */
                 Obstruct;          /* cType = 7  */
        alarm_t  SigLost;           /* cType = 8  */
        u_8      cVolume;           /* cType = 9  */
    }Cfg;
}CfgCh_t, CfgChn_t;
typedef struct CfgPreview
{
    u_8       cNum;
    monitor_t MonitorCfg;
}CfgPreview_t;
#if 0
typedef struct record
{
    u_8  bOn;                 /* 0: on, 1: off */ 
    u_8  to;                  /* 0x1 local, 0x2: net, 0x3; local & net */
    u_16 sPRT;                /* prev record time */
    u_16 sDRT;                /* delay record time*/
    struct {
        u_8  bOn[TIMES];
        u_8  cType[TIMES];    /* record type, 0: auto, 1: alarm */
        u_16 sRT[TIMES][2];   /* sRT[i][0]: begin time, sRT[i][1]: stop time 
                                 unit:      minute  */
    }plan[WEEK];
}record_t;
#endif
#define FOR_RECORD_SECT        6
#define ONE_CHAR_RECORD_SECT   8
#define TOTAL_RECORD_SECT      48
#define HALF_HOUR_FOR_MIN      30
#define FOUR_HOUR_FOR_MIN      4*60

typedef struct record
{
    u_8  bOn;                 /* 0: on, 1: off */ 
    u_8  to;                  /* 0x1 local, 0x2: net, 0x3; local & net */
    u_8  bMix;              /*0 video 1 mix*/
    u_8  cRes;

    u_16 sPRT;                /* prev record time */
    u_16 sDRT;                /* delay record time*/
   
    struct { 
        u_8  cRT[ FOR_RECORD_SECT ];
        u_8  cType[ TOTAL_RECORD_SECT ];     
    }plan[WEEK];
    /*48 bit every bit express the record status and the record type,there are 48 sect can select */
}record_t;

typedef struct CfgRecord {
    u_16 sCh;                 /* channel number */

    record_t Record;
}CfgRecord_t, CfgRec_t;

typedef struct CfgAlarm 
{
    u_8 cType;         /* 0: alarm input, 1: alarm output, 2: exception alarm */
    u_8 cNum;          /* for alarm input: 0 ~ 15 
                          for alarm output: 0 ~ 3 
                          for exception alarm: 0 -- disk full      1 -- disk error 
                                               2 -- net broken     3 -- IP conflict
                                               4 -- illegal access 5 -- mode ill-matched */
    union {   
        AC_t AC;
        AI_t AI;
        AO_t AO;
        AE_t AE;
    }Cfg;
}CfgAlarm_t, CfgAlm_t;

typedef struct CfgUser
{
   u_8        cType;   /* 0: add, 1: modify, 2: del, 3: rt one user info, 
                          4: rt next one user info */

   UserInfo_t UserInfo;
}CfgUser_t, CfgUsr_t;

typedef struct CfgCOM
{
    u_8 cType; /* 0: 232 COM, 1: 422 COM */
   
    union {
        COM_t COM232;
        PTZ_t PTZ;
    }Cfg;   
}CfgCOM_t;

typedef struct KVMWanInfo{

    u_32 lChannelNumber;			//???
    u_32 lDiskNumber;				//???
    u_8 cDevMac[6];			//KVM  Mac???????KVM

    u_8 cSnmpPort[2];			//KVM ????,snmp????
    u_8 cRtpPort[2];			//KVM ????,rtp????

    u_8 cHttpPort[2];			//KVM ????,http????
    u_8 cKVMPtzPort[2];			//KVM ????,????????

    u_8 cKVMPlayBackPort[2];			//KVM ????,?????????    u_8 cAudioTalkPort[2];			//KVM ????,??????
    u_8 cAudioTalkPort[2];			//KVM ????,??????

    u_8 cScanPort[2];			//KVM ????,??????
    u_8 cUpdatePort[2];			//KVM ????,????

    u_8 cNetAlarmPort[2];			//KVM ????,????
    u_8 cVMPlanePort[2];			//KVM ????,??????

    u_8 cPubPTZPort[2];			//KVM ????,??2216????
    u_8 cPubPlayBackPort[2];			//KVM ????,??2216????

    u_8 cResvered[2];				//??

}KVMWanInfo_t;
typedef struct CfgNet {
    net_t net;
}CfgNet_t;

typedef struct CfgPTZ {
    PTZ_t PTZ;
}CfgPTZ_t;

typedef struct CfgGUI {
    gui_t gui;
} CfgGUI_t;

typedef struct CfgNTP {
    bool  bNTP;
    u_8   IP[16];
    u_16  sPtz  : 6;    //time zone: -12 ~ +13
    u_16  bDayLight : 1;  //daylight saving time enable
}CfgNTP_t;
typedef struct{
    
    u_8                 cCfgType;
    u_8                 cStat;
    u_16                sCh;
    OSD_LOCAL_t         LocalOsd;
    NetChBasic_t        ChBasicInfo;
    record_t            Record;
}NetChInfo_t;

typedef struct{

    u_32   lNvrID;

    u_8    cNvrName[DEV_NAME_LEN];

    u_8    cDomainName[LNAME_LEN];               //KVMóò??

    u_16   sMaxCh;

}KvmSysInfo_t;

typedef struct{

    u_32  lPreTime;

    u_32  lDelayTime;    

}RecordTimeCtl_t;

//sg
typedef struct{
	bool 			bSgOpen;
	bool 			bAll;
	bool			cSnapOpen;
    u_8             cSnapType;
	s_8  			cSgName[16];
	u_32			snapTime[6];
    u_32      		interval;       /*播放间隔时间*/
	u_32 	  		lChannel[16];

}CfgSG_t;

typedef struct _LI_WF_NET_CONFIG
{
	unsigned char		wfOpen;
	char		ipAddress[32];
	char		subMask[32];
	char		gateWay[32];
	char		ssidName[34];
	char		pswText[34];	
	u_8		wfAuthType;					
} LI_WF_NET_CONFIG;
//3G
typedef struct _3G_WEB_INTERAC
{
	u_8     	n3gOpen;//3g 开关1open;0 close
	u_8			sigal;//取值0-5，对应无信号，差，一般，好，强，非常强
	u_8      	n3gType;//3g 类型 0 evdo 1 wcdma 2 td
	u_8			needApn;// 0 no;1 need
	char        sz3gApn[32];				//3g apn 
	u_8	  		c3gstatus	   ;//0: 没开启  1: 拨号成功 -1: 拨号失败；-3没有sim卡
	u_8     	simExits;      //   1       umi exits  else 0
	u_8     	serviceStatus; //srv status 
							 // 0 no srv status
							 // 1 a restrict srv status
							 // 2 a good srv
							 // 3 a restrict district srv
							 // 4 sleep status
	u_8     	networkType ;  // 0 not service
							 // 1 AMPS
							 // 2 CDMA
							 // 3 GSM/GPRS
							 // 4 HDR
							 // 5 WCDMA
							 // 6 GPS
							 // 7 GSM/WCDMA
							 // 8 CDMA/HDR HYBIRD
	char      softWareVer[128];   //software version
	char      hardWareVer[128];   //hardware version

} T3G_WEB_INTERAC;//200字节

typedef  enum {
           LAN1=0,
		   LAN2,
		   WAN
	}netWorkType;


#if 0
   struct tm {
                int tm_sec;         /* seconds */
                int tm_min;         /* minutes */
                int tm_hour;        /* hours */
                int tm_mday;        /* day of the month */
                int tm_mon;         /* month */
                int tm_year;        /* year */
                int tm_wday;        /* day of the week */
                int tm_yday;        /* day in the year */
                int tm_isdst;       /* daylight saving time */
            };        
int tm_sec 代表目前秒数，正常范围为0-59，但允许至61秒
int tm_min 代表目前分数，范围0-59
int tm_hour 从午夜算起的时数，范围为0-23
int tm_mday 目前月份的日数，范围01-31
int tm_mon 代表目前月份，从一月算起，范围从0-11
int tm_year 从1900 年算起至今的年数
int tm_wday 一星期的日数，从星期一算起，范围为0-6
int tm_yday 从今年1月1日算起至今的天数，范围为0-365
int tm_isdst 日光节约时间的旗标
#endif

typedef struct kLoginInfo{

    struct tm t;

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

    netWorkType net;
    
	u_8    cPowerIn;//on = 1; off  = 0 

}KvmSystemInfo_t;






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
#define DEV_SYSINFO   0xA0
#define CFG_LOGIN      0xB0
#define CFG_SYSTEM_INFO  0xC0
#define CFG_SG_INFO    0xD0
#define CFG_WIFI_INFO	   0xE0
#define CFG_3G_INFO  0xF0
#define CFG_ONEKEY		0x0B
#define CFG_PORT_ACCESS         0x10
#define CFG_PORT_ACCESS_STATUS  0X11
#define CFG_WORKSTATION         0x12
#define CFG_SECURE              0x13
#define CFG_VERIFY              0x14
#define CFG_BACKUP              0x15
#define CFG_USER_GRP            0x16
#define CFG_USER_PREW           0x17
#define CFG_USER_GRP_PREW       0x18



#define CH_BASIC_INFO    0x00
#define CH_MAJOR_VIDEO   0x01
#define CH_MINOR_VIDEO   0x02
#define CH_IMAGE         0x03
#define CH_OSD           0x04
#define CH_PRIVACY       0x05
#define CH_MOTION        0x06
#define CH_OBSTRUCT      0x07
#define CH_LOST          0x08
#define CH_RECORD_SCHEME 0x09



#define CFG_AI         0x00   /*ê?è?±¨?ˉ*/
#define CFG_AO         0x01   /*ê?3?±¨?ˉ*/
#define CFG_AE         0x02   /*òì3￡±¨?ˉ*/
#define CFG_AC         0x03   /*í¨μà±¨?ˉ*/

extern dvrsys_t g_sysInfo;
extern s_32 INF_SetSystemCfg_API( cfg_t TYPE, void *pCfg, s_8 *User, s_8 *ip );
extern s_32 INF_GetSystemCfg_API( cfg_t TYPE, void *pCfg, s_8 *User, s_8 *ip );

#ifdef _cplusplus
}
#endif

#endif


