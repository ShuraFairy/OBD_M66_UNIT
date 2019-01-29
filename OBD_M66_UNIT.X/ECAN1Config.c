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
*
* ADDITIONAL NOTES:
* This code is tested on Explorer-16 board with ECAN PICTail Card.
* The device used is dsPIC33FJ256GP710 controller 
*************************************************************************************************/


#if defined(__dsPIC33F__)
#include "p33fxxxx.h"
#elif defined(__dsPIC33E__)
#include "p33exxxx.h"
#elif defined(__PIC24H__)
#include "p24hxxxx.h"
#endif

#include "ECAN1Config.h"
//#include "cancommon.h"

volatile word rxmsg1;
volatile unsigned int CAN1AUX_R_ptr, CAN1AUX_W_ptr;
unsigned long ID;
volatile unsigned int CAN1_fault;

unsigned char __attribute__ ((far)) CAN1_DATA_buf [8];
unsigned char __attribute__ ((far)) CANOBD_DATA_buf1 [8];
unsigned char __attribute__ ((far)) CANOBD_DATA_buf2 [8];
unsigned char __attribute__ ((far)) CANOBD_DATA_buf3 [8];
volatile unsigned char __attribute__ ((fa)) CAN1AUX_DATA_buf[25][8];
volatile unsigned long __attribute__ ((far)) CAN1AUX_ID_buf[25][1];
    

unsigned char BRPVAL1;
unsigned int bitrate1, Fp1;


union __attribute__ ((far))  {
    unsigned int CAN1SETTINGS;
   struct 
    {
		unsigned char on:1;
        unsigned char ide:1;
        unsigned int  bitrate:10;
        unsigned int :4;
    };
} CAN1SETTINGSbits;
union __attribute__ ((far))  {
    unsigned long CAN1CFG;
   struct 
    {
		unsigned char   sjw:2;
        unsigned char  seg1:3;
        unsigned char  seg2:3;
        unsigned char prseg:3;
        unsigned char   sam:1;
        unsigned char      :4;
        
		unsigned char   sjw_slp:2;
        unsigned char  seg1_slp:3;
        unsigned char  seg2_slp:3;
        unsigned char prseg_slp:3;
        unsigned char   sam_slp:1;
        unsigned char      :4;        
    };
} CAN1CFGbits;

/* Dma Initialization for ECAN1 Transmission */
void dma3init(void){
     #if defined(__dsPIC33E__)
	 DMAPWC=0; DMARQC=0;
     #else
     DMACS0=0;
     #endif
     DMA3CON=0x2020;
	 DMA3PAD=0x0442;	/* ECAN 1 (C1TXD) */
 	 DMA3CNT=0x0007;
	 DMA3REQ=0x0046;	/* ECAN 1 Transmit */
     #if defined(__dsPIC33E__)
     DMA3STAH=  __builtin_dmapage(ecan1msgBuf);	
	 DMA3STAL=  __builtin_dmaoffset(ecan1msgBuf);	
     #else
	 DMA3STA=  __builtin_dmaoffset(ecan1msgBuf);	
     #endif
	 DMA3CONbits.CHEN=1;
}


/* Dma Initialization for ECAN1 Reception */
void dma2init(void){

	 #if defined(__dsPIC33E__)
	 DMAPWC=0; DMARQC=0;
     #else
     DMACS0=0;
     #endif
     DMA2CON=0x0020;
	 DMA2PAD=0x0440;	/* ECAN 1 (C1RXD) */
 	 DMA2CNT=0x0007;
	 DMA2REQ=0x0022;	/* ECAN 1 Receive */
     #if defined(__dsPIC33E__)
     DMA2STAH=  __builtin_dmapage(ecan1msgBuf);	
	 DMA2STAL=  __builtin_dmaoffset(ecan1msgBuf);	
     #else
	 DMA2STA=  __builtin_dmaoffset(ecan1msgBuf);	
     #endif
	 DMA2CONbits.CHEN=1;	 
}



void ecan1ClkInit(void){

/* FCAN is selected to be FCY*/
/* FCAN = FCY = 40MHz */
	C1CTRL1bits.CANCKS = CANCKSVAL;

    if (CAN1SETTINGSbits.bitrate == 500) C1CFG1bits.BRP = 0;
    if (CAN1SETTINGSbits.bitrate == 250) C1CFG1bits.BRP = 1;
    if (CAN1SETTINGSbits.bitrate == 125) C1CFG1bits.BRP = 3;
    if (CAN1SETTINGSbits.bitrate == 100) C1CFG1bits.BRP = 4;
    if (CAN1SETTINGSbits.bitrate == 83)  C1CFG1bits.BRP = 5;
    if (CAN1SETTINGSbits.bitrate == 62)  C1CFG1bits.BRP = 7;
    if (CAN1SETTINGSbits.bitrate == 50)  C1CFG1bits.BRP = 9; 
    if (CAN1SETTINGSbits.bitrate == 33)  C1CFG1bits.BRP = 14;    
/*
Bit Time = (Sync Segment + Propagation Delay + Phase Segment 1 + Phase Segment 2)=20*TQ
Phase Segment 1 = 8TQ
Phase Segment 2 = 6Tq
Propagation Delay = 5Tq
Sync Segment = 1TQ
CiCFG1<BRP> =(FCAN /(2 ×N×FBAUD))– 1
*/


	/* Baud Rate Prescaler */
//	C1CFG1bits.BRP = BRP_VAL;
    
// Äëÿ òàêòîâîé 10 ÌÃö
    if (Fp1 == 10) {
        /* Synchronization Jump Width set to 4 TQ */
        C1CFG1bits.SJW    = CAN1CFGbits.sjw_slp; //0x3;        
        /* Phase Segment 1 time is 4 TQ */
        C1CFG2bits.SEG1PH = CAN1CFGbits.seg1_slp;// 0x3;                                        // 4 TQ
        /* Phase Segment 2 time is set to be programmable */
        C1CFG2bits.SEG2PHTS = 0x1; // freely programmable
        /* Phase Segment 2 time is 3 TQ */
        C1CFG2bits.SEG2PH = CAN1CFGbits.seg2_slp; //0x2;                                      // 3 TQ
        /* Propagation Segment time is 3 TQ */
        C1CFG2bits.PRSEG  = CAN1CFGbits.prseg_slp; //0x1;                                       // 2 TQ
        /* Bus line is sampled three times at the sample point */
        C1CFG2bits.SAM    = CAN1CFGbits.sam_slp; // 0x1;	
    }
    else { // Äëÿ òàêòîâîé 20 ÌÃö
        /* Synchronization Jump Width set to 4 TQ */
        C1CFG1bits.SJW = CAN1CFGbits.sjw;       //0x3;  // 4 TQ     
        /* Phase Segment 1 time is 8 TQ */
        C1CFG2bits.SEG1PH = CAN1CFGbits.seg1;   //0x7;  // 8 TQ
        /* Phase Segment 2 time is set to be programmable */
        C1CFG2bits.SEG2PHTS = 0x1; // freely programmable
        /* Phase Segment 2 time is 6 TQ */
        C1CFG2bits.SEG2PH = CAN1CFGbits.seg2;   //0x5;  // 6 TQ
        /* Propagation Segment time is 5 TQ */
        C1CFG2bits.PRSEG = CAN1CFGbits.prseg;   //0x4;  // 5 TQ
        /* Bus line is sampled three times at the sample point */
        C1CFG2bits.SAM = CAN1CFGbits.sam;       //0x1;        
    }
}



void ecan1Init(void){

/* Request Configuration Mode */
	C1CTRL1bits.REQOP=4;
	while(C1CTRL1bits.OPMODE!=4);

	ecan1ClkInit();	

	C1FCTRLbits.FSA=0b01000;		/* 0b01000 FIFO Starts at Message Buffer 8 */
	C1FCTRLbits.DMABS=0b110;		/* 0b110 32 CAN Message Buffers in DMA RAM */
	
/*	Filter Configuration

	ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide,unsigned int bufPnt,unsigned int maskSel)

	n = 0 to 15 -> Filter number/

	identifier -> SID <10:0> : EID <17:0> 

	exide = 0 -> Match messages with standard identifier addresses 
	exide = 1 -> Match messages with extended identifier addresses 

	bufPnt = 0 to 14  -> RX Buffer 0 to 14
	bufPnt = 15 -> RX FIFO Buffer

	maskSel = 0	->	Acceptance Mask 0 register contains mask
	maskSel = 1	->	Acceptance Mask 1 register contains mask
	maskSel = 2	->	Acceptance Mask 2 register contains mask
	maskSel = 3	->	No Mask Selection
	
*/
Nop();Nop();Nop();
  
//	ecan1WriteRxAcptFilter(1,(long)0x000004F0,0,8,3);
//	ecan1WriteRxAcptFilter(2,(long)0x00000080,0,9,3); 
    
   

/*	Mask Configuration

	ecan1WriteRxAcptMask(int m, long identifierMask, unsigned int mide, unsigned int exide)

	m = 0 to 2 -> Mask Number

	identifier -> SID <10:0> : EID <17:0> 

	mide = 0 -> Match either standard or extended address message if filters match 
	mide = 1 -> Match only message types that correpond to 'exide' bit in filter

	exide = 0 -> Match messages with standard identifier addresses 
	exide = 1 -> Match messages with extended identifier addresses 
	
*/
Nop();Nop();Nop();
//	ecan1WriteRxAcptMask(1,0x1FFFFFFF,1,1);
//	ecan1WriteRxAcptMask(0,(long)0x7f8,1,0);	// mask 0, 

/* Enter Normal Mode */
	C1CTRL1bits.REQOP=0;
	while(C1CTRL1bits.OPMODE!=0);
	
/* ECAN transmit/receive message control */

	C1RXFUL1=C1RXFUL2=C1RXOVF1=C1RXOVF2=0x0000;
	C1TR01CONbits.TXEN0=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR01CONbits.TXEN1=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR23CONbits.TXEN2=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR23CONbits.TXEN3=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR45CONbits.TXEN4=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR45CONbits.TXEN5=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR67CONbits.TXEN6=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */
//	C1TR67CONbits.TXEN7=1;			/* ECAN1, Buffer 0 is a Transmit Buffer */

	C1TR01CONbits.TX0PRI=0b00; 		/* Message Buffer 0 Priority Level */
	C1TR01CONbits.TX1PRI=0b00; 		/* Message Buffer 0 Priority Level */
	C1TR23CONbits.TX2PRI=0b01; 		/* Message Buffer 0 Priority Level */
	C1TR23CONbits.TX3PRI=0b01; 		/* Message Buffer 0 Priority Level */
	C1TR45CONbits.TX4PRI=0b10; 		/* Message Buffer 0 Priority Level */
//	C1TR45CONbits.TX5PRI=0b10; 		/* Message Buffer 0 Priority Level */
//	C1TR67CONbits.TX6PRI=0b11; 		/* Message Buffer 0 Priority Level */
//	C1TR67CONbits.TX7PRI=0b11; 		/* Message Buffer 0 Priority Level */

	C1TR45CONbits.TXEN5=0;
	C1TR67CONbits.TXEN6=0;
	C1TR67CONbits.TXEN7=0; 
    
	C1TR45CONbits.RTREN5 = 0;
	C1TR67CONbits.RTREN6=0;
	C1TR67CONbits.RTREN7=0;     

	C1TR45CONbits.TXREQ5=0;
	C1TR67CONbits.TXREQ6=0;
	C1TR67CONbits.TXREQ7=0; 
    
}

extern void can1start(void)
{
//ìîå    
    C1FEN1 = 0;
    
    C1INTEbits.RBIE = 0;
    rxmsg1 = 0;
    
	ecan1Init();
	dma3init();	
	dma2init();
    MSTRPR = 0x0020;
	IEC2bits.C1IE = 1;
    
    C1INTF = 0;
	C1INTEbits.TBIE = 1;	
	C1INTEbits.RBIE = 1;
    
//    C1INTEbits.IVRIE  = 1;
//    C1INTEbits.FIFOIE = 1;
//    C1INTEbits.RBOVIE = 1;

} 
