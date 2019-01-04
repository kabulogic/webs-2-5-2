/****************************************************************
*  Copyright (c) 2017-2021,Kinan 
*  All rights reserved. 
*  FILE: access.c
*  DES:show U how use the libSession.a
*  creator: Alex
*  date:2017
*****************************************************************/
#ifndef _ACCESS_C
#define _ACCESS_C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include "session.h"
#include "access.h"
#include <sys/time.h>
#include <assert.h>

static int SessionID = -1;
static void *Pdu = NULL;

/****************************************************************************
 * function name:  Inf_initDataAccess_API
 * arguments:
 * return:         0 or -1
 * description:    open a session to King proc
 * creator:
 * date:
 ***************************************************************************/
int Inf_initDataAccess_API( void )
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
				Inf_closeDataAccess_API();
				perror("get the buf for session");
				return -1;
            }
        }
    }
    //printf("\n-----Session ID:%d----\n",SessionID);
    return 0;
}

/****************************************************************************
 * function name:  Inf_closeDataAccess_API
 * arguments:
 * return:         
 * description:    close a session to King proc
 * creator:
 * date:
 ***************************************************************************/
void Inf_closeDataAccess_API( void )
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
     return;
}

/****************************************************************************
 * function name:  INF_ClientTalkToKing_API
 * arguments:
 * return:         0 or -1
 * creator:       
 * date:
 ***************************************************************************/
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
    Inf_closeDataAccess_API();
    Inf_initDataAccess_API();

    return -1;
}


#endif

