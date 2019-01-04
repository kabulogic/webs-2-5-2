/***************************************************************************************
* file name:  authenBySessionid.h
* description:
* creator:    Zeed
* date:       2017-12-20
***************************************************************************************/
#ifndef _AUTHENBYSESSIONID_H
#define _AUTHENBYSESSIONID_H

/********************* Includes ***********************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../kinan/websSession.h"
#include "../des/tables.h"

/*********************** Prototypes *********************/

extern int authenBySessionid (char *sessionid, char *username, int size, int *flag);
#endif //_AUTHENBYSESSIONID_H

