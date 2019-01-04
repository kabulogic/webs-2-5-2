/***************************************************************************************
* file name:  macro.h
* description:
* creator:    Alex
* date:       2017-12-20
***************************************************************************************/
#ifndef _MACRO_H
#define _MACRO_H

//#include "includes.h"

#ifdef _cplusplus
extern "c" {
#endif
/////////
#define MAX_USER_GROUP_NUM 16
#define TOTAL_CH_MAX_NUM 64
#define MAX_PORT_ACCESS_NUM 64
/////////

#define GET_1_BYTE(i)    (u_8)( ( (i) & 0xFF ) >> 0 )
#define GET_2_BYTE(i)    (u_8)( ( (i) & 0xFF00 ) >> 8 )
#define GET_3_BYTE(i)    (u_8)( ( (i) & 0xFF0000 ) >> 16 ) 
#define GET_4_BYTE(i)    (u_8)( ( (i) & 0xFF000000 ) >> 24 )

#ifndef false
#define false            0
#endif
#ifndef true
#define true             1
#endif

#define STOP             0x0
#define START            0x1
#define CLEAR            0x2

#define DIR_LEN          40

#define WEEK             7
#define MAKE_DAY_MIN( H, M )  ( H * 60 + M )
#define DAY_MIN          ( 24 * 60 )
#define DAY_SEC          ( 24 * 60 * 60 )

#define CH_TYPE_LOCAL    0
#define CH_TYPE_NET      1

#define _KVM_ 
#ifdef _KVM_
#define BE_ENCODE_DSP( i )  ( i < TOTAL_EDSP_NUM )
#define BE_LOCAL_CH(i)   ( i < TOTAL_LOCAL_CH_NUM )
#define BE_NET_CH(i)     ( i >= TOTAL_LOCAL_CH_NUM && i < TOTAL_CH_NUM )
#else
#define BE_ENCODE_DSP( i )  ( false )
#define BE_LOCAL_CH(i)      ( false )
#define BE_NET_CH(i)        ( !BE_LOCAL_CH(i) && i < TOTAL_CH_NUM )
#endif

#define VALID_IP( ip )  ( inet_addr( ip ) > 0 )

#define MAX_ETH_NUM      2
#define CUR_ETH_NUM      1

#define NET_CH_NUM(i)    ( i - TOTAL_LOCAL_CH_NUM )

#define MAJOR_STREAM     0
#define MINOR_STREAM     1

#define INVALID_CH_NUM   ( 0 - 1 )
#define ALL_CH           0xFFFF

#define UNKNOW_ID      (0 - 1)
#define UNKNOW_CH      (0 - 1)
#define UNKNOW_VOP     (0 - 1)

#define MAX_PATH_LEN     128
#define MAX_FILE_LEN     16

#ifndef IP_LEN
#define IP_LEN      32
#endif


#define OFFSET( type, a )    ( (u_32)&(*(type *)0).a )

#define COST_TIME( x, t2, t1 )  DEBUG( "%s: %d\n", x, (u_32)((t2.tv_sec - t1.tv_sec)*1000000 \
                                                         + (t2.tv_usec - t1.tv_usec) ) );

#define SHOW_MEM( s, p, num ) do{\
                               u_32 i;\
                               u_8  *addr = (u_8 *)p;\
                               printf("---%s %s addr: %p, size: %d ---\n", __func__, s, addr, num);\
                               for( i = 0; i < num; i++ ){\
                                   printf("%2x-", addr[i]);\
                                   if( 0 == (i + 1) % 32 && i )\
                                        printf("\n");\
                               }\
                               printf("\n");\
                           }while(0)

//}	add by Alex for debug
#define __KVM_DEBUG__	
//#define __NET_LOG__

#ifdef	__KVM_DEBUG__

#ifdef	__NET_LOG__
	#include <syslog.h>
	#define KVM_INFO(arg)		syslog(LOG_INFO,arg)

	#define KVM_DBG(fmt,arg...)	syslog(LOG_DEBUG,"[%s]%s: %s:(%d)-> "fmt,\
						SW_VERSION, __FILE__, __FUNCTION__, __LINE__, ##arg)

	#define KVM_ERR(fmt,arg...) 	syslog(LOG_ERR,"[%s]%s: %s:(%d)-> "fmt,\
					        SW_VERSION, __FILE__, __FUNCTION__, __LINE__, ##arg)
#else
	#define	KVM_INFO(arg...)	printf(arg)
	#define KVM_DBG(fmt,arg...)	printf("[DBG:%s]%s: %s:(%d)-> "fmt,\
						SW_VERSION, __FILE__, __FUNCTION__, __LINE__, ##arg)

	#define	KVM_ERR(fmt,arg...)	printf("[ERR:%s]%s: %s:(%d)-> "fmt,\
						SW_VERSION, __FILE__, __FUNCTION__, __LINE__, ##arg)
#endif	//__NET_LOG__

#else
	#define	KVM_INFO(arg...)			
	#define	KVM_DBG(fmt,arg...)		
	#define	KVM_ERR(fmt,arg...)				
#endif	//__KVM_DEBUG__

//}



#define PATH_SN_MAC    "/var/kvm/.mac"

typedef struct sn_mac
{
    unsigned char cSN[64];       //7->64, D¨°¨¢Do?
    unsigned char cMac1[12];     //MAC¦Ì??¡¤1
    unsigned char cMac2[12];     //MAC¦Ì??¡¤2
}SN_MAC_t;

#if 0
#define PrintHex(p, len)\
    u_32 i=0;\
    do\
    {\
        printf("%02x ", (u_8)*(p+i));\
        i++;\
    }while(len>i);\
    printf("\n");
#endif


#ifdef _cplusplus
}
#endif

#endif

