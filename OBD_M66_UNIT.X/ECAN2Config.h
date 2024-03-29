/**********************************************************************
* � 2005 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33Fxxxx
* Compiler:        MPLAB� C30 v3.00 or higher
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author          	Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Vinaya Skanda 	10/18/06  First release of source file
* Vinaya Skanda		07/25/07  Updates from Joe Supinsky and Jatinder Gharoo incorporated
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*************************************************************************************************/


#ifndef __ECAN2_CONFIG_H__
#define __ECAN2_CONFIG_H__ 
//#include "ECAN1Drv.h"

/* CAN Baud Rate Configuration 		*/
#if defined(__dsPIC33E__)
// FCAN = 2*FCY so that the division below is integer.
#define FCAN  	20000000 
#define CANCKSVAL 1
#else
// FCAN = FCY 
#define FCAN  	40000000
#define CANCKSVAL 1
#endif
#define BITRATE 500000
#define NTQ 	20		// 20 Time Quanta in a Bit Time
#define BRP_VAL		((FCAN/(2*NTQ*BITRATE))-1)

/* CAN Message Buffer Configuration */
#define  ECAN2_MSG_BUF_LENGTH 	32
typedef unsigned int ECAN2MSGBUF [ECAN2_MSG_BUF_LENGTH][8];	
#if defined(__dsPIC33E__)
extern __eds__ ECAN2MSGBUF  ecan2msgBuf __attribute__((eds,space(dma)));
#else
extern ECAN2MSGBUF  ecan2msgBuf __attribute__((space(dma)));
#endif

//typedef int int;    // 16-bit signed


/* Function Prototype 	*/
extern void ecan2Init(void);
extern void dma5init(void);
extern void dma4init(void);

extern void can2start(void);

#endif
