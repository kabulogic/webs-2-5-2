/***************************************************************************************
* file name:   sysstat.h
* description: 
* creator:     Alex
* date:        2017-05-30
***************************************************************************************/
#ifndef _SYSSTAT_H
#define _SYSSTAT_H

//#include "includes.h"

#ifdef _cplusplus
extern "c" {
#endif

#define SYS_STAT( x ) ( x >> 8 )
#define STAT_DISK     ( 0x0 )
#define STAT_KVM      ( 0x1 )
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

#define STAT_KVM_BOOT        ( ( STAT_KVM << 8 ) | 0x00 )
#define STAT_KVM_READY       ( ( STAT_KVM << 8 ) | 0x01 )
#define STAT_KVM_CLOSE       ( ( STAT_KVM << 8 ) | 0x02 )
#define STAT_PTT_START       ( ( STAT_KVM << 8 ) | 0x03 )
#define STAT_PTT_STOP        ( ( STAT_KVM << 8 ) | 0x04 )

#define STAT_ALARM_START     ( ( STAT_ALARM << 8 ) | 0 )
#define STAT_ALARM_STOP      ( ( STAT_ALARM << 8 ) | 1 )

///////////////////////////////
#define TOTAL_ALARM_MAX_C  64
#define TOTAL_ALARM_I  32
#define TOTAL_ALARM_E 32
#define KVM_CH 1
//////////////////////////////
typedef struct videoStat {
    u_16  sCh;
    bool bLost;
    u_8  cRecordType;  /* 0: no record, 1: man, 2: time, 3: alarm */

    u_8  cNetPrev;
    u_8  cPtz;
    u_8  manualstart;/*是否启动了手动录像*/
    u_8  rev;
    
    u_32 motion;
    u_32 obstruct;
} videoStat_t;

typedef struct diskStat {
    u_8  id;
    u_8  stat;     /* 0: idle, 1: work, 2: full, 3: error, 4: no */
    u_8  method;   /* 0: loop, 1: not loop */
    u_8  format;  /*0- 未格式化，1-正在格式化 2-格式化录像盘，3-格式化为备份盘 4-此盘正在录像*/
    u_32 capacity;
    u_32 free;
} diskStat_t;

typedef struct alarmStat {
    u_32 alarms;

    u_8  cAC[TOTAL_ALARM_MAX_C];  /* 0: no alarm, 1: lost, 2: motion, 4: obstruct ,    8: input*/
    bool bAI[TOTAL_ALARM_I];
    bool bAE[TOTAL_ALARM_E]; 
} alarmStat_t;

typedef struct kvmStat  {
    s_8    name[64];
    s_8    id[64];
    s_8    SN[64];

    s_8    de_ver[64], en_ver[64];
    s_8    hw_ver[64], sw_ver[64];
    
    u_16   sChs;
    u_8    cDisks;
	u_8    cRes;

    time_t tBoot;
    u_32   boots;

    u_8    cPTT;
    //u_8    cRes[3];
    u_8 cAIs;
    u_8 cAOs;
    u_8 res;

} kvmStat_t;


typedef struct netStat {

} netStat_t;

typedef struct recStat {
    u_8 cRecordType[TOTAL_CH_NUM];
} recStat_t;

typedef struct{

    u_32 IP, lPort,lID;

    bool bLogin;    

}KVMLoginStat_t;

//typedef struct dvdrwCtrl
//{
//	u_8 cCmd;	/* 0x00:发送查询命令; (mount to /mnt/sr)
//				0x01: 发送fileinfo 0x02:烧写光盘
//				0x03:获取进度; 0x04:弹出光驱; 0x05:关闭光驱;
//				0x06:擦除光盘; */
//
//	u_32 uPackNo;			/*包序号*/
//	u_32 uPackTotal;		/*包总数(fileinfo)*/
//	u_32 uErrCode;			/*错误码*/
//	union 
//	{
//	struct status			/*查询命令回应*/
//	{
//	u_32 uDiscType;			/*光盘类型*/
//	u_32 uDriveStatus;		/*光驱状态 */	
//	u_32 uDiscSpace;		/*光盘容量*/
//	u_32 uUsedSpace;		/*已用空间*/
//	}status;
//	u_32 uProcess;			/*进度 0 ~ 100*/	
//	fileInfo_t stFileInfo;	/*刻录对象文件信息*/
//	}data;
//}dvdrwCtrl_t;

typedef struct sysstat {
    u_8   cType;
    u_8   cRes[3];
    union {
        videoStat_t video;
        diskStat_t  disk;    
        alarmStat_t alarm;
        kvmStat_t   dvr;
        PrevStat_t  prevStat[TOTAL_MONITOR_NUM];
        //dvdrwCtrl_t stDvdrw;        
        recStat_t   record;
        KVMLoginStat_t KVMLogin;
    }of;    
} sysstat_t, SysStat_t;

#ifdef _SYSSTAT_C
#define SYSSTAT_API
#else
#define SYSSTAT_API    extern
#endif

SYSSTAT_API s_32 INF_GetSysStat_API( sysstat_t *p );
SYSSTAT_API s_32 INF_SetSysStat_API( u_16 sType, u_32 arg );
SYSSTAT_API bool INF_KVMIsRecording_API(u_8 ch);
SYSSTAT_API void INF_SetVideoManualStat_API(u_8 sCh ,u_8 start);
SYSSTAT_API s_32 INF_GetSnFromFile_FUN( s_8* cSn, const s_8* cDefault );
SYSSTAT_API void HH_SetKVMCfg_API( char cType, void *pCfg );
//SYSSTAT_API BOOL_E HH_GetChVideoLost( u_16 sCh );


#ifdef _cplusplus
}
#endif

#endif

