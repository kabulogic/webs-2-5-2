/***************************************************************************************
* File Name: system.h;
* Description: Void;
* Creator: Alex
* Date: 2017-7-20.
***************************************************************************************/
#ifndef _SYSTEM_H
#define _SYSTEM_H

//#include "includes.h"
//#include "../../common/product.h"
#ifdef _cplusplus
extern "c" {
#endif

#ifndef _LINUX_
#define _LINUX_
#endif

/**************************************************************************************/

#define PRODUCT_SERIAL               "123456789"   //???
#if 0
#ifndef KVM_CH
#define KVM_CH      (16)    
#endif
#endif

#ifdef  HI3512
#define CHS_PER_EDSP                 2    
#endif

#ifdef HI_3520D
#define CHS_PER_EDSP                 1
#define KVM_CH                       1
#endif

#ifndef CHS_PER_EDSP
#define CHS_PER_EDSP                 KVM_CH
#endif



/*chip type*/
#ifdef HI3531_32
#ifndef KVM_CH
#define KVM_CH      (32)    
#endif

#define TOTAL_ALARM_O                    4

#define TOTAL_ALARM_MAX_O                4
#define PLAY_CH  16

#endif

#ifdef HI3531_16
#ifndef KVM_CH
#define KVM_CH      (16)    
#endif
#define TOTAL_ALARM_O                    4

#define TOTAL_ALARM_MAX_O                4
#define PLAY_CH  16


#endif

#ifdef HI3531_8
#ifndef KVM_CH
#define KVM_CH      (8)    
#endif 
#define TOTAL_ALARM_O                    4

#define TOTAL_ALARM_MAX_O                4
#define PLAY_CH  8

#endif




#if 0

#define TOTAL_LOCAL_CH_NUM           KVM_CH
#define TOTAL_EDSP_NUM               (KVM_CH/CHS_PER_EDSP)
#define TOTAL_DSP_NUM                (TOTAL_EDSP_NUM+1)
#define TOTAL_NET_CH_NUM             0UL
#define SYS_NAME                     "Kinan KVM"
#else 
#define TOTAL_DSP_NUM                1 
#define TOTAL_EDSP_NUM               1
#define TOTAL_LOCAL_CH_NUM          KVM_CH 
#define TOTAL_NET_CH_NUM            0UL
#define SYS_NAME                     "KVM"
#define MAX_LOCALPLAY_CH_NUM           KVM_CH
#endif

#define TOTAL_DDSP_NUM               ( TOTAL_DSP_NUM - TOTAL_EDSP_NUM )
//#define DDSP_ID                      ( TOTAL_DSP_NUM - 1)
#define DDSP_ID                      0

#define TOTAL_CH_MAX_NUM            KVM_CH

#define MAX_HD_NUM                  8
#define HD_TOTAL_NUM                MAX_HD_NUM
#define TOTAL_MONITOR_NUM           1

#ifndef MAX_PORT_ACCESS_NUM
#define MAX_PORT_ACCESS_NUM			64
#endif

#ifndef MAX_WORKSTATION_NUM
#define MAX_WORKSTATION_NUM			4
#endif

#ifndef MAX_BACKUP_TIME_RANGE
#define MAX_BACKUP_TIME_RANGE		4
#endif

#define ETH_NUM         2




#if(KVM_CH == 8)
#define MAX_PREV_MODE                9UL
#else
#define MAX_PREV_MODE                KVM_CH
#endif

#define TOTAL_ALARM_C                TOTAL_CH_NUM
#define TOTAL_ALARM_MAX_C            TOTAL_CH_MAX_NUM
 
#define TOTAL_LOCAL_ALARM_I 	        16
#define TOTAL_ALARM_MAX_I               TOTAL_LOCAL_ALARM_I

#define TOTAL_ALARM_I                (TOTAL_LOCAL_ALARM_I + TOTAL_NET_CH_NUM)

#define TOTAL_ALARM_E                10



#define MAX_TIMES_PER_DAY            4

#define MAX_IMAGE_NUM                7

#define MAX_AREA_NUM                 4

#define MAX_PRE_RECORD_SEC           10

#define RECORD_TIMES_PER_DAY         4

#define MONITOR_1                    0
#define MONITOR_2                    1

#define DIR_3060                     "/kvm/"
#define DIR_EXE                      "/kvm/bin/"

#define ROOT                         "admin"
#define LOCAL_IP                     "127.0.0.1"

#define PIC_WIDETH     640
#define PIC_HEIGTH     480

#ifdef _cplusplus
}
#endif

#endif

