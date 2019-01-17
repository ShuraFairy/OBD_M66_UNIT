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

#ifndef __ECAN1_DRV_H__
#define __ECAN1_DRV_H__ 

//typedef unsigned int word;    // 16-bit unsigned

extern volatile word rxmsg1;
extern volatile unsigned int CAN1AUX_R_ptr, CAN1AUX_W_ptr;

extern unsigned long ID;
extern volatile unsigned int CAN1_fault;
extern unsigned char __attribute__ ((far)) CAN1_DATA_buf [8];
extern unsigned char __attribute__ ((far)) CANOBD_DATA_buf1 [8];
extern unsigned char __attribute__ ((far)) CANOBD_DATA_buf2 [8];
extern unsigned char __attribute__ ((far)) CANOBD_DATA_buf3 [8];
extern volatile unsigned char __attribute__ ((far)) CAN1AUX_DATA_buf[25][8];
extern volatile unsigned long __attribute__ ((far)) CAN1AUX_ID_buf[25][1];

extern union __attribute__ ((far))  {
    unsigned int CAN1SETTINGS;
   struct 
    {
		unsigned char on:1;
        unsigned char ide:1;
        unsigned int  bitrate:10;
        unsigned int :4;
    };
} CAN1SETTINGSbits;

//extern union __attribute__ ((far))  {
//    unsigned int CANODOEXIST;
//   struct 
//    {
//		unsigned char exist_mes1:1;
//        unsigned char exist_mes2:1;
//        unsigned char exist_mes3:1;
//        unsigned char      :5;
//    };
//} CANODOEXISTbits;


extern void ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide,unsigned int bufPnt,unsigned int maskSel);
extern void ecan1WriteRxAcptMask(int m, long identifierMask, unsigned int mide,unsigned int exide);

extern void ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit);
extern void ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 );

extern void ecan1DisableRXFilter(int n);


extern word isfreetx(word buf);
extern void settxtransmit(word buf);
extern word sendnormalmsg(word prio, long txidentifier,unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 );

extern void rxECAN1(word message);
void Can1Tasks(void);
#endif
