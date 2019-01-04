/***************************************************************************************
 * file name:   sysctrl.h
 * description:
 * creator:     Alex
 * date:        2017-06-26
 **************************************************************************************/
#ifndef _SYSCTRL_H
#define _SYSCTRL_H

//#include "includes.h"
#include "inf_public.h"
//#include "cms_sdk.h"

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
#define CTRL_VO_ZOOM     0x12
#define CTRL_DISCOVERY     0x13
#define CTRL_MANAGE     0x14
#define CTRL_GET_CAM_NET		0x15
#define CTRL_SET_CAM_NET		0x16
#define CTRL_ONEKEY		0x17

#define CTRL_OPEN_PTT    0xF1
#define CTRL_CLOSE_PTT   0xF0

#ifndef KVM_LOGIN_CMS
#define KVM_LOGIN_CMS                           0x30
#endif

#ifndef KVM_LOGOUT_CMS
#define KVM_LOGOUT_CMS                          0x20
#endif
//////////////////////////////
#define PLAY_CH 64
#define TOTAL_MONITOR_NUM   64
//////////////////////////////
typedef struct login {
    bool bOn;

    UserInfo_t User;
} login_t;


typedef struct ptzCtr {
    u_16 sCh;
    u_8  cCmd;
    u_8  cData;
    s_8  cX;
    s_8  cY;
} ptzCtr_t;


typedef struct recordCtr {
    bool  bStart;/* 0: stop, 1: start */
    u_8  cCmd;   /*2 manual 3 alarm*/
    u_16 sCh;
    u_32 t;        
} recordCtr_t;

typedef struct diskCtr {
    u_8 cCmd;  /* 0: format harddisk */
    u_8 cNum;
    u_8 cMethod;
} diskCtr_t;

typedef struct logSearch {
    time_t t1, t2;
    u_16   sMajorType, sMinorType;
    s_8    cPath[128];
} logSearch_t;

typedef struct SearchFile {
    s_8    cPath[32];
}SearchFile_t;

typedef struct playCtr {
    u_8           cNum;      /*total play ch  range 1-16*/
    u_8           cCmd;      /* 0: stop, 1: start */
    u_8           cMonitor;
    u_8 	      bAudio;
    SearchFile_t  file[PLAY_CH];
    u_32	      cFrameRate;
    time_t        tStart, tCur, tEnd; 
    //Ele_Enlarge_t enlarge;
    u_32          ID;
} playCtr_t;

typedef struct timeCtr {
    time_t t;
    bool   bNet;
    u_16  sPtz;
} timeCtr_t;

#define REBOOT_KVM    0x01
#define REBOOT_SNMP   0x02
#define REBOOT_WEB    0x03   
#define REBOOT_SYS    0x04
#define HALT_SYS      0x05 
#define FACTORY_RESET 0x06
#define CFG_RECOVER   0x07

typedef  struct runCtr {
    u_8  cCmd;        /* 0x04: reboot 0x05:power off  0x06: reset 0x07:config recover*/
    u_32 data;
} runCtr_t;

typedef struct dataIndex
{
     RecFileIndex_t RecFileIdx;
     u_32  lOffset;/*文件索引*/
     u_32  lSize;
     fd_t   fd;
}dataIndex_t;
typedef struct dataCtr {
    u_8    cMdeia;    /* 0x00: local hd,  0x01: NAS, 0x02: usb, 0x03: dvd, 0x04: sdk */
    u_8    cMethod;   /* 0x01: by search, 0x02: by file */
    u_8    rev[2];
    union {
        search_t search;
        dataIndex_t dataIndex;
    }arg;
 } dataCtr_t;

typedef struct update {
    u_8 cType;        /* 0x01: v3060,     0x02: snmp,   0x03: webs, 0x13: watch dog 
                         0x10: ramdisk,   0x11: kernel, 0x12: uboot */
    u_8 cFrom;        /* 0x01: usb, 0x02: dvd, 0x03: sdk, 0x04: web, 0x05: remote */
    s_8 cPath[128];
} update_t, Update_t;

typedef struct cfgCtr {
    u_8 cType;      /* 0x00: backup user-info, 0x01: backup sys-cfg 
                       0x10: update user-info, 0x11: update sys-cfg, 0xE0: default cfg */
    u_8 cMedia;     /* 0x01: usb, 0x02: dvd, 0x03: sdk */
    u_8 cPath[128]; 
} cfgCtr_t;

typedef struct alarmCtr {
    u_8 cCmd;   /* 0x00: clear one,         0x01: clear all, 0x10: trigger one */
    u_8 cType;  /* 0x00: channel alarm,     0x01: motion alarm;
                   0x02: obstruct alarm;    0x03: signal lost alarm 
                   0x10: local input alarm  0x11: net input alarm */
    u_16 sNum;
    
}alarmCtr_t;

typedef struct PrevStatus
{
    bool bPrev;/*0-预览，1-回放*/
    u_8  cMode;/*画面状态,1,4,9,16*/
    bool bAlarm;
    bool bAuto;
    u_16 sCh[TOTAL_CH_MAX_NUM];/*对应画面状态的位置*/
}PrevStat_t;

typedef struct guiCtr{
    u_8 cCmd;	/* see gui.h */
    u_16 sCh;	
    PrevStat_t PrevStat[TOTAL_MONITOR_NUM];
    s_8 LoginName[20];
}guiCtr_t;

//typedef unsigned long long u_64;

typedef struct dvdrwCtrl
{
    u_8 cCmd;	/* 0x00:发送查询命令; (mount to /mnt/sr)
				0x01: 发送fileinfo 0x02:烧写光盘
				0x03:获取进度; 0x04:弹出光驱; 0x05:关闭光驱;
				0x06:擦除光盘; */

    u_32 uPackNo;			/*包序号*/
    u_32 uPackTotal;		/*包总数(fileinfo)*/
    u_32 uErrCode;			/*错误码*/
    union 
    {
        struct status			/*查询命令回应*/
	{
	    u_32 uDiscType;			/*光盘类型*/
	    u_32 uDriveStatus;		/*光驱状态 */	
	    u_64 uDiscSpace;		/*光盘容量*/
	    u_64 uUsedSpace;		/*已用空间*/
	}status;
	u_32 uProcess;			/*进度 0 ~ 100*/	
	s_8 cPath[128];	/*刻录对象文件信息*/
    }data;
}dvdrwCtrl_t;

#if 0 //mdf_Alex
typedef struct chManage{
    u_16 sCh;
    u_8  cCmd;  /*0 add, 1 del */
    u_8  cRes;
    KVM_CAMERA_INFO camerainfo;
}chManage_t;
#endif

typedef struct IpArea{
	char   cIpStart[IP_LEN]; 
	char   cIpEnd[IP_LEN]; 

}IpArea_t;
typedef struct sysCtrl {
    u_8 cType;

    s_8 cUser[16];
    s_8 cPswd[16];

    union {
        recordCtr_t record;
        diskCtr_t   hd;
        logSearch_t log;
        playCtr_t   play;
        timeCtr_t   time;
        runCtr_t    run;
        search_t    search;
        dataCtr_t   cp, rm;
        update_t    update;
        login_t     login;
        //loginCms_t  loginCms;
        cfgCtr_t    cfg;
        alarmCtr_t  alarm;
        guiCtr_t    gui;
        dsp_play_ctrl_t  dsplay;
        search_t  discovery;
    }ctrl;
}sysCtrl_t, SysCtr_t;

#ifdef _SYSCTRL_C
#define SYSCTRL_API
#else
#define SYSCTRL_API    extern
#endif

SYSCTRL_API s_32 INF_SysCtrl_API( sysCtrl_t *p, s_8 *User, s_8 *ip );
//SYSCTRL_API int HH_ManageStream_API( chManage_t *Man, s_8 *User , s_8 *IP );


#endif

