
#ifndef _INF_PUBLIC_H_
#define _INF_PUBLIC_H_

#ifdef _cplusplus
extern "c" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include <signal.h>
#include <linux/reboot.h>
#include <sys/reboot.h>
#include <linux/rtc.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <fcntl.h>
#include <pthread.h>
//#include <linux/sockios.h>
//#include <linux/ethtool.h>
//#include <linux/sockios.h>

#include <linux/unistd.h>

typedef pthread_mutex_t     mutex_t;
typedef pthread_mutexattr_t mutex_attr_t;
typedef pthread_cond_t      cond_t;
typedef pthread_condattr_t  cond_attr_t;
typedef pthread_t           thread_t;

typedef struct timeval  timeval_t;
typedef struct timezone timezone_t;
typedef struct tm       tm_t;
typedef struct timespec timespec_t;


#ifndef _INF_TYPES
#define _INF_TYPES
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

/*
typedef enum 
{
    FALSE = 0,
    TRUE  = 1,
}BOOL_E;
*/

#endif /* _INF_TYPES */



#define OSD_TEXT_LEN        (64)
#define OSD_NUM_PER_CHN     (4)
#define AREA_NUM_PER_CHN    (4)
#define LOCALPLAY_MAX_CH   (16)

#define CPU_LITTLE_ENDIA

#ifdef CPU_LITTLE_ENDIA
#define MAIN_BYTE_TO_INT( byte )  ( byte[0]  | byte[1] << 8 | byte[2] << 16 | byte[3]<<24 )
#define MAIN_INT_TO_BYTE( byte, u32DataLen )\
        do{\
            byte[3] = (u_8)(((u32DataLen) & 0xFF000000 ) >> 24);\
            byte[2] = (u_8)(((u32DataLen) & 0xFF0000 ) >> 16);\
            byte[1] = (u_8)(((u32DataLen) & 0xFF00 ) >> 8);\
            byte[0] = (u_8)( (u32DataLen) & 0xFF );\
        }while(0)
#define MAIN_SECT_BYTE_TO_INT( byteH,byteM,byteL)  ((byteH)|((byteM)<<8)|((byteL)<<16))
#define MAIN_SECT_INT_TO_BYTE( byteH,byteM,byteL, dataLen )\
        do{\
            byteH = ( (dataLen) & 0xFF);\
            byteM = (( (dataLen) >> 8  ) & 0xFF);\
            byteL = (( (dataLen) >> 16  ) & 0xFF);\
        }while(0)
#else
#define MAIN_BYTE_TO_INT( byte )  ( byte[0] << 24 | byte[1] << 16 | byte[2] << 8 | byte[3])
#define MAIN_INT_TO_BYTE( byte, u32DataLen )\
        do{\
            byte[0] = (u_8)(((u32DataLen) & 0xFF000000 ) >> 24);\
            byte[1] = (u_8)(((u32DataLen) & 0xFF0000 ) >> 16);\
            byte[2] = (u_8)(((u32DataLen) & 0xFF00 ) >> 8);\
            byte[3] = (u_8)( (u32DataLen) & 0xFF );\
        }while(0)
#define MAIN_SECT_BYTE_TO_INT( byteH,byteM,byteL)  ((byteH<<16)|((byteM)<<8)|((byteL)))
#define MAIN_SECT_INT_TO_BYTE( byteH,byteM,byteL, dataLen )\
        do{\
            byteL = ( (dataLen) & 0xFF);\
            byteM = (( (dataLen) >> 8  ) & 0xFF);\
            byteH = (( (dataLen) >> 16  ) & 0xFF);\
        }while(0)
#endif

#define GET_FILE_INDEX( index ) \
        do{\
            index.KeyOffset  = ntohl( index.KeyOffset );\
            index.KeySN      = ntohl( index.KeySN );\
		    index.KeyTimeSec = ntohl( index.KeyTimeSec );\
        }while(0)

#define CHECK_RET( express, name )\
    do{\
        if( SUCCESS != express )\
        {\
            printf("%s failed at %s: LINE: %d !, express = 0x%x\n", name, __FUNCTION__, __LINE__, express );\
            return -1;\
        }\
    }while(0)

#define CHECK_MIN_MAX( min, max, value )\
    do{\
        s_32 tmp = value; \
        if( tmp < min || tmp > max )\
        {\
            printf("range error at  %s: LINE: %d, value = %d !\n", __FUNCTION__, __LINE__, value );\
            return -1;\
        }\
    }while(0)

#define CHECK_NULL( value )\
    do{\
        if( NULL == value )\
        {\
            printf(" NULL == value at  %s: LINE: %d !\n", __FUNCTION__, __LINE__);\
            return -1;\
        }\
    }while(0)
#define X_SETBIT( x , i )       ( (x) |= ( 0x1 << (i) ))
#define X_CLRBIT( x , i )       ( (x) &= ( ~( 0x01 << (i) )))
#define X_CHKBIT( x , i )       ( ((x) >> (i) ) & 0x01 )

#define  V1080P_WIDTH    (1920)
#define  V720P_WIDTH     (1280)
#define  CIF4_WIDTH     (704)
#define  CIF_WIDTH      (352)
#define  QCIF_WIDTH     (176)

#define V1080P_HEIGHT    (1080)
#define V720P_HEIGHT    (720)
#define CIF4_P_HEIGHT   (576)
#define CIF4_N_HEIGHT    (480)
#define CIF_P_HEIGHT   (288)
#define CIF_N_HEIGHT    (240)
#define QCIF_P_HEIGHT   (144)
#define QCIF_N_HEIGHT    (120)

#ifndef DVR_CH
#define DVR_CH 1
#endif

typedef enum{
    VIDEO_RES_QCIF,
    VIDEO_RES_CIF,
    VIDEO_RES_2CIF,
    VIDEO_RES_4CIF,
    VIDEO_RES_D1,
    VIDEO_RES_720P,
    VIDEO_RES_1080P,
    VIDEO_RES_3MP,
    VIDEO_RES_5MP,
    VIDEO_RES_MAX
}video_res_t;

typedef enum
{
    OSD_ID_NAME = 0,
    OSD_ID_TIME,    
    OSD_ID_TEXT1,  
    OSD_ID_TEXT2
}OSD_Id_t;

typedef enum{
    VIDEO_MODE_PAL,
    VIDEO_MODE_NTSC,
    VIDEO_MODE_MAX
}video_mode_t;

typedef enum{
    FRAME_TYPE_VIDEO_VOL,
    FRAME_TYPE_VIDEO_I,
    FRAME_TYPE_VIDEO_BP,   
    FRAME_TYPE_AUDIO,
    FRAME_TYPE_MAX
}video_frame_type_t;

typedef enum{
    VO_VGA_BNC       = 0,
    
    VO_VGA_800X600_60 ,
    VO_VGA_1024X768_60,
    VO_VGA_1280x1024_60,
    VO_VGA_1366x768_60,
    VO_VGA_1440x900_60,
    
    //VO_VGA_800x600_75,
    //VO_VGA_1024x768_75,

    //VO_HDMI_720P_60,
    //VO_HDMI_1080I_50,
    VO_HDMI_1080I_60,
    VO_HDMI_1080P_25,
    VO_HDMI_1080P_30,
    
    VO_VGA_MAX
}vo_vga_t;

typedef enum{
    VIDEO_STREAM_MAIN,
    VIDEO_STREAM_SUB,
    VIDEO_STREAM_BOTH,
    VIDEO_STREAM_MAX
}video_stream_type_t;

typedef enum{
    PIC_QUALITY_LOWEST,
    PIC_QUALITY_LOWER,        
    PIC_QUALITY_NORMAL,
    PIC_QUALITY_HIGHER,
    PIC_QUALITY_HIGHEST,
    PIC_QUALITY_MAX
}pic_quality_t;

typedef enum{
    STREAM_TYPE_VIDEO,
    STREAM_TYPE_AUDIO,        
    STREAM_TYPE_BOTH,
    STREAM_TYPE_MAX
}stream_type_t;

typedef enum{
    DEV_ENC_TYPE_DSP,
    DEV_ENC_TYPE_ASIC,
    DEV_ENC_TYPE_MAX
}dev_enc_type_t;

typedef enum{
    BITRATE_TYPE_VBR,
    BITRATE_TYPE_CBR,
    BITRATE_TYPE_MAX
}bitrate_type_t;

typedef enum{
    PCI_CFG_TYPE_SLVWORK,
    PCI_CFG_TYPE_MAJORVENC,
    PCI_CFG_TYPE_MINORVENC,
    PCI_CFG_TYPE_IMAGE,
    PCI_CFG_TYPE_OSD,
    PCI_CFG_TYPE_PREVIEW,
    PCI_CFG_TYPE_PLAY,
    PCI_CFG_TYPE_PRIAREA,
    PCI_CFG_TYPE_MD,
    PCI_CFG_TYPE_OBS,
    PCI_CFG_TYPE_TIME,
    PCI_CFG_TYPE_MAX
}pci_cfg_type_t;

typedef enum{
    PCI_CTL_TYPE_PLAY_START,
    PCI_CTL_TYPE_PLAY_PAUSE,
    PCI_CTL_TYPE_PLAY_RESUME,
    PCI_CTL_TYPE_PLAY_STOP,
    PCI_CTL_TYPE_PLAY_END,
    PCI_CTL_TYPE_PLAY_FRAME,
    PCI_CTL_TYPE_PLAY_FF,    
    PCI_CTL_TYPE_PLAY_FB, 
    PCI_CTL_TYPE_PLAY_CLEAR_BUF,
    PCI_CTL_TYPE_PLAY_AUDIO,
    PCI_CTL_TYPE_PIC_ZOOM,
    PCI_CTL_TYPE_CH_FULL,
    PCI_CTL_TYPE_CH_FULL_EXIT,
    PCI_CTL_TYPE_MAX
}pci_ctl_type_t;

typedef enum{
    PCI_DATA_ENC_VIDEO = 0x10,
    PCI_DATA_ENC_AUDIO,
    PCI_DATA_REPLAY_VIDEO,
    PCI_DATA_REPLAY_AUDIO,
    PCI_DATA_PREW_VIDEO,
    PCI_DATA_PREW_AUDIO,
    PCI_DATA_ALARM,
    PCI_DATA_TALK,
    PCI_DATA_REV_TALK,/*反向音频*/
    PCI_DATA_GET_CH_STATUS,
    PCI_DATA_MAX
}pci_data_type_t;

typedef enum{
    PCI_CMD_TYPE_CFG,
    PCI_CMD_TYPE_CTL,
    PCI_CMD_TYPE_DATA,    
    PCI_CMD_TYPE_MAX
}pci_cmd_type_t;


#define CH_SIG   0x0000
#define CH_OBS   0x0001
#define CH_MOT   0x0002
#define CH_ALARM_IN   0x0003


typedef enum{
    ALARM_TYPE_LOSS,
    ALARM_TYPE_OBS,
    ALARM_TYPE_MOTION,
    ALARM_TYPE_MAX
}alarm_type_t;


typedef struct DSPtoCPUHead
{
    u_32 u32PackId:24;
    u_32 cPackets:8;
}DCHead_t;

typedef enum{
    CMD_MAIN_REQ_DSP = 0,
    CMD_DSP_RSP_MAIN,
    CMD_DSP_REQ_MAIN,
    CMD_MAIN_RSP_DSP,
    CMD_TYPE_MAX,
}CMD_type_t;

/* 1.2 Head of a Data Packet */
typedef struct PacketHead
{
    u_8 u8Type;
    u_8 u8Subtype;
    u_8 u8CMDMode;/*0-主控请求，1-DSP应答,2-DSP请求，3-主控应答*/
    u_8 u8rev;
    u_32 u32len;    
    u_32 u32SN;
    s_32 ret;/*返回值*/
}PtHead_t;


typedef struct {    
    u_8 u8ChNum;        /*0~15*/
    u_8 u8StreamType;   /*0 = main 1 = sub*/
    u_8 bMixStream;     /* 0: video stream, 1: V & A stream */   
    u_8 u8Enable;     /* 0: disable, 1: enable */
 
    u_8 u8FrameType;    
    u_8 u8IFrameInterval;       /*IP rate*/ 
    u_8 u8FrameRate;        /*1~25*/
    u_8 u8ImageQuality;     /*0~4*/
    
    u_8 u8Resolution; 
    u_8 u8BitRateType;        /*0-varible,1-constant*/
    u_8 u8MaxBitRate;    /* Max bit rate >> 4*/ 
    u_8 mode;
}Compress_Param_S;

typedef struct {
 
   u_8 u8ChNum;
   u_8 u8Res[3]; 
 
   u_8 u8Brightness;
   u_8 u8Contrast; 
   u_8 u8Color; 
   u_8 u8Saturation;

}Image_Param_S;

typedef struct  area
{
    u_16 u16X,u16Y;
    u_16 u16Width,u16Height;
}AREA_S;

typedef struct Motion_Obstruct_Cfg 
{
    u_8 u8ChNum;
    u_8 u8On;
    u_8 u8Sensitivity; //for privacy area invalid
    u_8 u8res;

    AREA_S area[AREA_NUM_PER_CHN];

}PRI_AREA_Param_S,MD_Param_S,OBS_Param_S;

typedef enum ZoomType {
    VO_SRC_VI  = 0x00,
    VO_SRC_VDEC,
    VO_SRC_MAX
}ZoomType_e;

typedef struct VideoZoom {
    u_8 u8Ch;
    u_8 u8On; 
    u_8 u8Res[2];
    ZoomType_e eType;
    u_32 u32x; 
    u_32 u32y; 
    u_32 u32W; 
    u_32 u32H; 
}Ele_Enlarge_t;

typedef struct 
{
    u_8 u8Monitor;                      /*0~2*/
    u_8 u8Enable;                       
    u_8 u8VGARes;                       /*VGA分辨率，仅对vga输出设置有效*/
    u_8 u8DisplayMode;                  /* 0, 1, 2, 4, 6, 8, 9 ,13, 16 */    
    
    u_8 u8Place[DVR_CH];       /*各个画面通道的位置*/
    //u_8 u8Place[1];       /*各个画面通道的位置*/
    u_8 u8Aduio;                        /*通道音频,0~16，0xff为不输出音频*/
    u_8 u8Vga;               /*vga是否为主监视器*/
    u_8 bPlay;
    u_8 rev;
}Preview_S;


typedef struct 
{
    u_8 u8Monitor;                      /*0~2*/
    u_8 u8DisplayMode;                  /* 0, 1, 2, 4, 6, 8, 9 ,13, 16 */   
    u_8 u8Rate;
    u_8 u8Aduio;                        /*通道音频,0~16，0xff为不输出音频*/
    u_8 u8Place[16];       /*各个画面通道的位置*/
    u_8 u8VideoRes[16];    /*回放各个通道分辨率*/ 
    u_8 rev[4];
}Play_S;
typedef struct ALARM_INFO
{
      u_8 u8AlarmType;// 0:video lossed; 1:moving detected; 2:shelter detectd
      u_8 u8Chan;
      u_8 u8Status;// 1:no alarm to alarm; 0:alarm to no alarm
      u_8 u8Res;
}ALARM_INFO_S;


typedef struct PacketOSD
{
    u_8 cCh;
    u_8 cID; 
    u_8 cAttribute;
    u_8 cEnable;    

    u_8 u8Week;
    u_8 u8Format;
    u_8 u8lang;
    u_8 u8rev;
      
    u_8 cX_H[2], cX_L[2], cY_H[2], cY_L[2];      

}PtOSD_t;


typedef struct{
    u_8 slave_no;    
    u_8 dvr_num;         /*该设备是多少路机器*/     
    u_8 u8IsUp;          /*是否已经启动成功*/    
    u_8 video_mode;      /*0-pal ,1-ntsc*/   
    
    u_8 venc_res_max;   /*该dsp具有最大分辨率*/
    u_8 video_enc_num;  /*该dsp具有多少路编码能力*/    
    u_8 play_num;        /*该dsp具有多少路解码能力*/     
    u_8 vo_num;          /*该dsp具有多少路VO输出能力*/  
    
    u_8 prew_mode;      /*最大预览分辨率模式*/    
    u_8 audio_enc_num;  /*该dsp具有多少路音频编码能力(不包括对讲)*/
    u_8 talk_num;        /*该dsp具有多少路语音对讲能力*/    
    u_8 osdlang;         /*OSD语言，中英文*/    
}slv_work_t;


typedef struct
{
    u_8  u8ch;
    u_8  u8Init;      /*是否启动完成*/
    u_8  u8ViStatus;
    u_8  u8VencStatus;
    
    u_8  u8AudioStatus;     
    u_8  MainStatus;/*主码流*/
    u_8  subStatus;/*子码流*/
    u_8  AudioEncStatus;

        
    u_8  u8Loss;     /*视频丢失状态*/
    u_8  u8Motion;   /*移动侦测状态*/
    u_8  u8Cover;    /*视频遮挡状态*/
    u_8  u8PriArea;  /*隐私区域设置状态*/
    
    
    time_t curTime;     /*当前时间*/
    time_t runtime;  /*运行时间*/

    Compress_Param_S stMainPress;
    Compress_Param_S stMoirPress;

    Image_Param_S stImage;
    
}dsp_ch_status;

typedef struct
{
    u_8  u8ch;
    u_8  u8dspId;
    u_8  u8resettime;/*重启次数*/    

    dsp_ch_status dsp_chstatus;
    
    
    u_32 u32VMainframeNo;
    u_32 u32VMainLostframeNum;
    u_32 u32VMainTransNum;
    u_32 u32VMainTransLostNum;
    
    u_32 u32VSubframeNo;
    u_32 u32VSubLostframeNum;
    u_32 u32VSubTransNum;
    u_32 u32VSubTransLostNum;
    
    u_32 u32AframeNo;
    u_32 u32ALostframeNum;
    u_32 u32ATransNum;
    u_32 u32ATransLostNum;    
}ch_status;

/* define video or audio encoded data head */
typedef struct 
{
    u_8  u8Mon;
    u_8  u8ChnNum;
    u_8  u8Resolution;
    u_8  u8FrameType;// 0:I; 1:p
    
    u_8  u8FrameRate;
    u_8  u8FrameLen_H;
    u_8  u8FrameLen_M;
    u_8  u8FrameLen_L;
    
    u_8  u8Mode;// 0:PAL; 1:NTSC
    u_8  u8StreamType;// 0:main; 1:sub	
    u_8  DevNo[2];/*在主控端填写*/
    
    u_32 timestamp;
    u_32 FrameNO;
    u_32 ticks;/*纳秒为单位*/
}PtVOP_t,VIDEO_ENCODED_DATA_HEAD_S, HEAD_S;

typedef struct
{
    u_8 u8Mon;
    u_8 u8Ch;
    u_8 bStart;
    u_8 u8Res;
    Ele_Enlarge_t Zoom;
}dsp_play_ctrl_t;

typedef struct 
{
    u_8    cCh;
    u_8    cBitWidth;
    u_8    cSampleRate[2];
    
    u_32   SN;    
    u_32   ticks;/*音频时标,只记录低位32位，高32位不记录*/
    u_32   DataLen;
}audioHdr_t;

extern void INF_Process_Msg_FromDSP_API(u_8 *pData,u_32 u32Datalen);
extern int start_3520Main(slv_work_t *pstSlvWork);
#ifdef _cplusplus
}
#endif

#endif

