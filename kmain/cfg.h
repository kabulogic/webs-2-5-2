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

/*���ֵ�д�����*/
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

    struct tm t; //tmϵͳʱ��ṹ��

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
    u_8     IsRecordDisk[MAX_HD_NUM];/*�Ƿ�¼����,0-���̲����ڣ�1-¼���̣�2-������*/
    u_8     WorkDisk;                   /*�������̣�0~(HD_MAJOR_NUM-1)*/
    u_8     BackupDisk;                 /*�����̣�0~HD_MAJOR_NUM��Ĭ��ΪHD_MAJOR_NUM����U��*/
    u_8     IsOverWrite;                /*�Ƿ���Ը��ǣ�0-���Ը��ǣ�1-���ɸ��ǣ�Ĭ��Ϊ���Ը���*/
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


		
		u_32 bPort: 	   1;//�˿ڷ�������Ȩ��
		u_32 bUserMng:		1;//�û���������Ȩ��
		u_32 bSecure:		1;//��ȫ��������Ȩ��
		u_32 bSysMaintenance:	  1;//ϵͳά������Ȩ��

		//Ȩ��ϸ��
		//u_32 bNetPrev:	  1;//ʵʱԤ��Ȩ��
		//u_32 bNetPlay:	  1;//����ط�Ȩ��
		//u_32 bLocalPlay:  1;//���ػط�Ȩ��
		//u_32 bLogView:	  1;//��־Ԥ��Ȩ��
		
		/*detail*/
		u_32 bAddUser:		  1;//�����û�Ȩ��
		u_32 bAddGroup: 	1;//�����û���Ȩ��
		u_32 bDelUser:	  1;//ɾ���û�Ȩ��
		u_32 NetCfg:	  1;//��������Ȩ��
		
		u_32 SysTime:	  1;//����ϵͳʱ��Ȩ��
		u_32 PortCfg:	   1;//���ö˿�Ȩ��
		u_32 backupAndRecover:1;//���ݺ͸���Ȩ��
		u_32 factoryReset:	   1;//�ָ���������Ȩ��
		
		u_32 rebootSys: 	   1; //����ϵͳȨ��
		u_32 RemoteUpdate:	  1;//Զ����������

		struct {
				u_32 Mouse_left:	1;//������
				u_32 Mouse_right:	1;//����Ҽ�
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

    s_8     cHD_Ver[32];/*��Ӳ�̵����ݿ����İ汾��*/
    u_8     cRes[20];
    time_t  STime;    /*Ӳ������¼��ʱ��*/
    time_t  OTime;   /*Ӳ�̸��ǿ�ʼʱ��*/
    time_t  ETime;    /*Ӳ������¼��ʱ��*/
    u_8     cHD_Loc;    /*Ӳ��λ�ã�0-�����̣�1-nfs�̣�2-iscsi��*/
    u_8     cHD_Type;   /*Ӳ�����ͣ�0-¼���̣�1-�����̣�2-������*/
    u_8     cHD_Attr;   /*Ӳ�����ԣ�0-�ɶ�д�� 1-ֻ����2-���ɶ�д*/
    u_8     cHD_Grp;    /*Ӳ��������0-8*/

    /*Ӳ�̴�С(/proc/partitions��¼�Ĵ�С),kΪ��λ,1TΪ10��K*/
    u_32    Blocks;   
    
    /*����Ӳ�̵Ĵ�С,���������ͷ��������С����kΪ��λ, ���ĸ�������Size���*/
    u_32    Size;      
    u_32    Used;      /*��д��Ӳ�̵Ĵ�С����kΪ��λ ���ĸ�����Used���*/    
    u_32    Free;      /*Ӳ��ʣ��ռ䣬kΪ��λ,1TΪ10��K,���ĸ�����Free���*/

   /*���ǵĴ�����0�Ļ�Ϊ��û��ʼ���Ǽ����̺��һ��ʹ�ã�
     1�Ļ�Ϊ��һ�����ڸ��ǣ��Դ�����
   */
    u_32    RcvrNum;     

    /*Ӳ�̸�ʽ��״̬: 0-δ��ʽ��  1-���ڸ�ʽ��   2-�Ѹ�ʽ�� 3-��ʽ������*/
    u_8     cFmtStat;
    
    /* Ӳ�̹���״̬: 0-����,����¼��  1-Ӳ���� 2-Ӳ��¼��ʱ���� */
    u_8     cWkStat;    

    u_16    sMaxVch;   /*�����ڴ�Ӳ����¼����������ͨ����*/

    u_8     cPts;      /*ʵ�ʷ�����*/
    u_8     cLogHDTag; /*�Ƿ�����־��*/
    u_8     cMac[MAC_LEN];/*�豸��MAC��ַ�����ڱ�ʾ����־����̨�豸��*/

    time_t  SftTime;    /*�ô��̵����ٸ�ʽ��ʱ��*/
    time_t  QftTime;    /*���һ�ο��ٸ�ʽ��ʱ��*/

    u_8     cExtTag;   /*�Ƿ�����չ��Ϣ*/
    u_8     cRev[3]; 
    u_32    ExtLen;    /*��չ��Ϣ����*/

}HD_Info_t; 

#if 1
/* peer action define */
#define PEER_GET    0x0  //��ȡϵͳ����
#define PEER_SET    0x1  //����ϵͳ����
#define PEER_CTR    0x2  //ϵͳ����
#define PEER_STA    0x3  //ϵͳ״̬
#define PEER_RET    0x4  //�ظ�

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
