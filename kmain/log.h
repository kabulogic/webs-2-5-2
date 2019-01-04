/*****************************************************************************
* Name: log.h
* Copyright(C): 2017-2021 @ R&D of Kinan Comp.
*
* Description: 
*
* Creator: Alex
* Date: 2017-08-20
******************************************************************************/

#ifndef _LOG_H
#define _LOG_H

//#include "includes.h"

#ifdef _cplusplus
extern "c" {
#endif

//#define DEBUG_LOG

#define LOG_FILE_SIZE    (256*1024*1024)

#define MAX_LOG_NUM      (250*10000) //能存储的日志个数

#define MAX_LOG_CACHE    (16) //能缓存的日志个数

#define LOG_INDEX_LOFF   sizeof(LogFileHead_t) //第一条日志索引在日志文件中的偏移
/*第一条日志在日志文件中的偏移*/
#define LOG_LOFF         ( LOG_INDEX_LOFF + MAX_LOG_NUM * sizeof(LogIndex_t) )
/*搜索日志时，一次读取4K的日志索引, 4K=512条日志*/
#define MAX_READ_NUM     (u_32)( (4*1024)/sizeof(LogIndex_t) )

//日志文件的存储示意图:
/*____________________________________
*|                                    |
*|     日志头log_file_head_t          |
*|------------------------------------|---LOG_INDEX_LOFF
*|     日志索引log_index_0            |
*|             log_index_1            |
*|             log_index_2            |
*|                  .                 |
*|                  .                 |
*|                  .                 |
*|                                    |
*|------------------------------------|---LOG_LOFF
*|            日志log_t 0             |
*|            日志log_t 1             |
*|            日志log_t 2             |
*|               .                    |
*|               .                    |
*|               .                    |
*|                                    |
*|                                    |
*|                                    |
*|____________________________________|
*/

typedef struct log {
    time_t t;

    u_16   sMajorType;
    u_16   sMinorType;

    Name_t cUser;
    IP_t   IP;  

    s_8    cDes[36];
} log_t;

#define MAC_LEN                         6
typedef struct Log_File_Head {
    u_8     cMac[MAC_LEN];//KVM的MAC地址，用于表示此日志是哪台KVM的
    u_8     cRev[2];
    u_32    WritedNum; //已写入的日志个数
    u_32    WritedIndex; //上次记录的索引号
}LogFileHead_t;

typedef struct LogIndex {
    time_t     t;//日志时间
    u_16       sMajorType;
    u_16       sMinorType;
}LogIndex_t;

typedef struct log_Res_head {
    u_32    fileCnt;//搜索结果总文件的个数
    u_8     flag;//此搜索结果文件0:空闲，1:被占用
    u_8     rev[27];
}log_res_head_t;

typedef struct log_queue {
	void * start;
	u_32 data_len;
	u_32 data_num;
	u_32 head;
	u_32 tail;
	u_32 exist_data_num;
}log_queue_t;


#define LOG_MIN_SIZE           4
#define LOG_MAJOR_TYPE( i )    ( i & 0xFF00 )
#define LOG_MINOR_TYPE( i )    ( i & 0x00FF )

/* log major type */
#define LOG_ALM               ( 1 << 8 )  /*告警*/
#define LOG_EXP               ( 2 << 8 )  /*异常*/
#define LOG_CFG               ( 3 << 8 )  /*配置*/
#define LOG_OPS               ( 4 << 8 )  /*操作*/
#define LOG_VIW               ( 5 << 8 )  /*预览*/
#define LOG_REC               ( 6 << 8 )  /*录像*/

/* log minor type */
/*----------------------------------------------------------*/
/*告警*/
#define LOG_ALM_MOT_START   ( LOG_ALM | 1 )
#define LOG_ALM_MOT_STOP    ( LOG_ALM | 2 )
#define LOG_ALM_OBS_START   ( LOG_ALM | 3 )
#define LOG_ALM_OBS_STOP    ( LOG_ALM | 4 )
#define LOG_ALM_IN          ( LOG_ALM | 5 )
#define LOG_ALM_OUT         ( LOG_ALM | 6 )

/*----------------------------------------------------------*/
/*异常*/
#define LOG_EXP_LOST           ( LOG_EXP | 1 )//视频丢失
#define LOG_EXP_NET_BROKEN     ( LOG_EXP | 2 )//网络断开
#define LOG_EXP_NET_FAIL       ( LOG_EXP | 3 )//网络链接失败
#define LOG_EXP_ACCESS         ( LOG_EXP | 4 )//异常访问
#define LOG_EXP_HD_FULL        ( LOG_EXP | 5 )//硬盘满
#define LOG_EXP_HD_ERROR       ( LOG_EXP | 6 )//硬盘错误
#define LOG_EXP_ILG_POWER_OFF  ( LOG_EXP | 7 )//非法关机
#define LOG_EXP_IP             ( LOG_EXP | 8 )//ip冲突

/*----------------------------------------------------------*/
/*配置*/
#define LOG_CFG_RECORD    ( LOG_CFG | 1 )//录像配置
#define LOG_CFG_PORT      ( LOG_CFG | 2 )//端口配置
#define LOG_CFG_NET       ( LOG_CFG | 3 )//网络配置
#define LOG_CFG_USER      ( LOG_CFG | 4 )//用户配置
#define LOG_CFG_HD        ( LOG_CFG | 5 )//硬盘配置
#define LOG_CFG_USER_GRP  ( LOG_CFG | 6 )//用户组配置

/*----------------------------------------------------------*/
/*预览*/
#define LOG_VIW_CFG        ( LOG_VIW | 1 )
#define LOG_VIW_PREV       ( LOG_VIW | 2 )
#define LOG_VIW_PLAY       ( LOG_VIW | 3 )
#define LOG_VIW_LOG        ( LOG_VIW | 4 )
// #define LOG_VIW_LOGIN      ( LOG_VIW | 5 )
// #define LOG_VIW_LOGOUT     ( LOG_VIW | 6 )

/*----------------------------------------------------------*/
 /*操作*/
#define LOG_OPS_BK_RECORD     ( LOG_OPS | 1 )// 备份录像操作
#define LOG_OPS_BK_CFG        ( LOG_OPS | 2 )// 备份配置操作
#define LOG_OPS_DEL_RECORD    ( LOG_OPS | 3 )// 删除录像
#define LOG_OPS_DEL_LOG       ( LOG_OPS | 4 )// 删除日志
#define LOG_OPS_UPDATE        ( LOG_OPS | 5 )// 系统升级
#define LOG_OPS_DEFAULT       ( LOG_OPS | 6 )// 恢复出厂默认
#define LOG_OPS_HD            ( LOG_OPS | 7 )// 硬盘操作
#define LOG_OPS_TIME          ( LOG_OPS | 8 )// 时间操作
#define LOG_OPS_BOOT          ( LOG_OPS | 9 )// 启动
#define LOG_OPS_REBOOT        ( LOG_OPS | 10 )//重启
#define LOG_OPS_POWEROFF      ( LOG_OPS | 11 )//关机
#define LOG_OPS_LOGIN         ( LOG_OPS | 12 )
#define LOG_OPS_LOGOUT        ( LOG_OPS | 13 )


/*----------------------------------------------------------*/
/*录像的子类型*/
#define LOG_REC_START_TIMER    ( LOG_REC | 1 )定时录像开始
#define LOG_REC_START_ALARM    ( LOG_REC | 2 )报警录像开始
#define LOG_REC_STOP_TIMER     ( LOG_REC | 3 )定时录像停止
#define LOG_REC_STOP_ALARM     ( LOG_REC | 4 )报警录像停止

#ifdef _LOG_C
#define LOG_API
#else
#define LOG_API    extern
#endif
LOG_API s_32 INF_InitLog_API(void);
LOG_API s_32 INF_log_API(u_16 sType, s_8 const *cDes, s_8 const *User, s_8 const *ip);
LOG_API s_8 *INF_GetLogStr_API(u_16 sType);
LOG_API s_32 INF_SearchLog_API(time_t t1, time_t t2, u_16 sType, s_8 *cPath);
LOG_API void INF_RemoveLogFile_API(s_8 *cPath);
LOG_API s_32 INF_InitLogFileHead_API(u_8 diskIdx);
LOG_API void INF_SetStopRecordLog_API(bool bstop);


#define logStr( i )       INF_GetLogStr_API( i )
#define LOG(x...)         INF_log_API(x)

#ifdef _cplusplus
}
#endif

#endif
/*
static s_8 *cLog_alm_Str[]   = { "alarm",
                                 "motion alarm start",   "motion alarm stop",
                                 "obstruct alarm start", "obstruct alarm stop", 
                                 "alarm in",             "alarm out"          };
static s_8 *cLog_exp_Str[]   = { "exceptional",
                                 "video lost",           "network broken",
                                 "network fail",         "illegal access",
                                 "hard disk full",       "hard disk error", 
                                 "illegal power off",    "ip confict"};

static s_8 *cLog_cfg_Str[]   = { "configure",
                                 "record param config",  "port config",
                                 "network config",       "user config",
                                 "hard disk config",     "user group config"
                               };

static s_8 *cLog_viw_Str[]   = { "view",
                                 "get config.",    "video preview",
                                 "video playback",       "get log"
                                     };

static s_8 *cLog_ops_Str[]  = {  "operations", 
                                 "backup video record",  
                                 "backup config.",       "delete video record",  
                                 "delete log",           "update firmware",    
                                 "default config.",      "foramt hard disk",   
                                 "change system time",   "system boot", 
                                 "reboot system",        "shut down system" ，
                                 "user login",           "user logout"  
                              };

static s_8 *cLog_rec_Str[]  = {  "record",
                                 "timer record start",  "alarm record start",   
                                 "timer record stop",   "alarm record stop",     };
                                 */
