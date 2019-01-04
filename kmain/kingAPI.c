/****************************************************************
*  Copyright (c) 2017-2021,Kinan Tech. Co., Ltd.
*  Version     :    km1.0
*  Filename    :    kingApi.c
*  Description :    open and close the api of king
*  Creator     :    zeed
*  Date        :    2017-7-31
*  History     :
*  <author>    <time>    <version>    <desc>
*  zeed        17/07/31  1.0          build this moudle
*
*****************************************************************/

#include "./kingAPI.h"

static int SessionID = -1;
static void *Pdu = NULL;

/*****************************************************************
 * function name    :   Inf_initDataAccess_API
 * arguments        :    
 * return           :   0 or -1
 * description      :   open a session to King proc
 * creator          :
 * date             :   2017-8-2
 *****************************************************************/
int Inf_initDataAccess_API( int SessionID, void *Pdu )
{   
	if( SessionID < 0 )
	{
		SessionID = INF_OpenSession_API( DOMAIN_CLI );
		if( SessionID < 0 )
		{   
			perror("open session with king proc");
			return -1;
		}
		if( Pdu == NULL )
		{
			Pdu = malloc(MAX_PDU_LEN);
			if( Pdu == NULL )
			{
				Inf_closeDataAccess_API(SessionID, Pdu);
				perror("get the buf for session");
				return -1;
			}
		}
	}
	//printf("\n-----Session ID:%d----\n",SessionID);
	return 0;
}

/****************************************************************
 * function name:  Inf_closeDataAccess_API
 * arguments:
 * return:         
 * description:    close a session to King proc
 * creator:
 * date:
 ****************************************************************/
int Inf_closeDataAccess_API( int SessionID, void *Pdu )
{   
    if( SessionID > 0 )
    {
     	 INF_CloseSession_API(SessionID,DOMAIN_CLI);
	}
    if(Pdu)
    {
    	free(Pdu);
		Pdu = NULL;	
    }
    SessionID = -1;
    return 0;
}

/*******************************************************************
 * function name:  INF_ClientTalkToKing_API
 * arguments:
 * return:         0 or -1
 * creator:       
 * date:
 *******************************************************************/
int INF_ClientTalkToKing_API( PeerHdr_t *PeerHdr, MsgHdr_t *MsgHdr, void *buf, size_t size )
{  
    struct timeval sessTime;
    sessTime.tv_sec = 120;
    sessTime.tv_usec = 0 ;

    if( !Pdu || !PeerHdr || !MsgHdr || !buf )
    {
        printf( "pointer is null\n" );
        goto ERROR_HND;
    }
    PeerHdr->sLen = sizeof( MsgHdr_t ) + size;

    memcpy( Pdu, (void *)PeerHdr, sizeof(PeerHdr_t) );
    memcpy( Pdu + sizeof(PeerHdr_t), (void *)MsgHdr, sizeof(MsgHdr_t) );
    memcpy( Pdu + sizeof(PeerHdr_t) + sizeof(MsgHdr_t), (void *)buf, size );
	
    if(SessionID < 0)
    {
        goto ERROR_HND;
    }
    if( INF_SpeakToPeer_API( SessionID, Pdu, sizeof(PeerHdr_t) + sizeof(MsgHdr_t) + size, &sessTime ) < 0 )
    {
        perror("client send request about config error");
        goto ERROR_HND;
    }
     
    if( INF_ListenToPeer_API( SessionID, Pdu, MAX_PDU_LEN, &sessTime ) < 0 )
    {
        perror("client get config error");
         if( INF_ListenToPeer_API( SessionID, Pdu, MAX_PDU_LEN, &sessTime ) < 0 )
        {
            goto ERROR_HND;
        }
    }
    
    memcpy( PeerHdr, Pdu, sizeof(PeerHdr_t) ); 
    memcpy( MsgHdr, Pdu + sizeof(PeerHdr_t), sizeof(MsgHdr_t) );    
    memcpy( buf, Pdu + sizeof(PeerHdr_t) + sizeof(MsgHdr_t), size );
    return 0;
	
    ERROR_HND:;
    Inf_closeDataAccess_API(SessionID, Pdu);
    Inf_initDataAccess_API(SessionID, Pdu);

    return -1;
}

/*******************************************************************
 * function name:  initPeerHdr
 * arguments:
 * return:      
 * creator:       
 * date:
 *******************************************************************/

void initPeerHdr (PeerHdr_t *pHdr, char *cWho, char *cIP, char cAction)
{
	if(cWho != NULL)
	{
		strncpy(pHdr->cWho, cWho, sizeof(pHdr->cWho));
	}
	strncpy(pHdr->IP, cIP, sizeof(pHdr->IP));
	pHdr->cAction = cAction;
}

/*******************************************************************
 * function name:  initPeerHdr
 * arguments:
 * return:      
 * creator:       
 * date:
 *******************************************************************/

void initMsgHdr (MsgHdr_t *mHdr, char cType)
{
	mHdr->cType = cType;
}

