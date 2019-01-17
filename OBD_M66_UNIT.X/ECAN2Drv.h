/**********************************************************************
* © 2005 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author          	Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Vinaya Skanda 	10/18/06  First release of source file
* Vinaya Skanda		07/25/07  Updates from Joe Supinsky and Jatinder Gharoo incorporated
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*************************************************************************************************/

//#include "candcommon.h"

#ifndef __ECAN2_DRV_H__
#define __ECAN2_DRV_H__ 

//typedef unsigned int int;    // 16-bit unsigned

extern volatile int rxmsg2;
extern volatile unsigned int CAN2AUX_R_ptr, CAN2AUX_W_ptr;
extern unsigned long ID2;
extern volatile unsigned int CAN2_fault;
extern unsigned char __attribute__ ((far)) CAN2_DATA_buf [8];
extern volatile unsigned char __attribute__ ((far)) CAN2AUX_DATA_buf[25][8];
extern volatile unsigned long __attribute__ ((far)) CAN2AUX_ID_buf[25][1];

extern union __attribute__ ((far))  {
    unsigned int CAN2SETTINGS;
   struct 
    {
		unsigned char on:1;
        unsigned char ide:1;
        unsigned int  bitrate:10;
        unsigned int :4;
    };
} CAN2SETTINGSbits;


extern void ecan2WriteRxAcptFilter(int n, long identifier, unsigned int exide,unsigned int bufPnt,unsigned int maskSel);
extern void ecan2WriteRxAcptMask(int m, long identifierMask, unsigned int mide,unsigned int exide);

extern void ecan2WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit);
extern void ecan2WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 );

extern void ecan2DisableRXFilter(int n);


extern int isfreetx2(int buf);
extern void settxtransmit2(int buf);
extern int sendnormalmsg2(int prio, long txidentifier,unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 );

extern void rxECAN2(int message);
void Can2Tasks(void);
#endif
