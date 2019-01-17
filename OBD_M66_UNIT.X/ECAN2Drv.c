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
///

#if defined(__dsPIC33F__)
#include "p33fxxxx.h"
#elif defined(__dsPIC33E__)
#include "p33exxxx.h"
#elif defined(__PIC24H__)
#include "p24hxxxx.h"
#endif


#include "ECAN2Config.h"
#include "ECAN2Drv.h"



/* 
This function configures Acceptance Filter "n" 

Inputs:
n-> Filter number [0-15]
identifier-> Bit ordering is given below
Filter Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
								   |____________|_____________________|
									  SID10:0           EID17:0


Filter Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
														  |___________|
															  SID10:0
exide -> "0" for standard identifier 
		 "1" for Extended identifier

bufPnt -> Message buffer to store filtered message [0-15]
maskSel -> Optinal Masking of identifier bits [0-3]
						
*/
void ecan2WriteRxAcptFilter(int n, long identifier, unsigned int exide, unsigned int bufPnt,unsigned int maskSel) {
//   ecan1WriteRxAcptFilter(    1,      0x1FFEFFFF,                  1,                  15,                   0);
unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
unsigned int *sidRegAddr,*bufPntRegAddr,*maskSelRegAddr, *fltEnRegAddr;


	C2CTRL1bits.WIN=1;

	// Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN register for a given filter number "n"
	sidRegAddr     = (unsigned int *)(&C2RXF0SID  + (n << 1));
	bufPntRegAddr  = (unsigned int *)(&C2BUFPNT1  + (n >> 2));
	maskSelRegAddr = (unsigned int *)(&C2FMSKSEL1 + (n >> 3));
	fltEnRegAddr   = (unsigned int *)(&C2FEN1);


	// Bit-filed manupulation to write to Filter identifier register
	if(exide==1) { 	// Filter Extended Identifier
		eid15_0 = (identifier & 0xFFFF);
		eid17_16= (identifier>>16) & 0x3;
		sid10_0 = (identifier>>18) & 0x7FF;

		*sidRegAddr=(((sid10_0)<<5) + 0x8) + eid17_16;	// Write to CiRXFnSID Register
	    *(sidRegAddr+1)= eid15_0;					// Write to CiRXFnEID Register

	}else{			// Filter Standard Identifier
		sid10_0 = (identifier & 0x7FF);			
		*sidRegAddr=(sid10_0)<<5;					// Write to CiRXFnSID Register
		*(sidRegAddr+1)=0;							// Write to CiRXFnEID Register
	}


   *bufPntRegAddr = (*bufPntRegAddr) & (0xFFFF - (0xF << (4 *(n & 3)))); // clear nibble
   *bufPntRegAddr = ((bufPnt << (4 *(n & 3))) | (*bufPntRegAddr));       // Write to C1BUFPNTn Register

   *maskSelRegAddr = (*maskSelRegAddr) & (0xFFFF - (0x3 << ((n & 7) * 2))); // clear 2 bits
   *maskSelRegAddr = ((maskSel << (2 * (n & 7))) | (*maskSelRegAddr));      // Write to C1FMSKSELn Register

   *fltEnRegAddr = ((0x1 << n) | (*fltEnRegAddr)); // Write to C1FEN1 Register

   C2CTRL1bits.WIN=0;


}


/* 
This function configures Acceptance Filter Mask "m" 

Inputs:
m-> Mask number [0-2]
identifier-> Bit ordering is given below
Filter Mask Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
								        |____________|_____________________|
									        SID10:0           EID17:0


Filter Mask Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
														       |___________|
															      SID10:0

mide ->  "0"  Match either standard or extended address message if filters match 
         "1"  Match only message types that correpond to 'exide' bit in filter
					
*/
void ecan2WriteRxAcptMask(int m, long identifier, unsigned int mide, unsigned int exide){
//   ecan1WriteRxAcptMask(    1,      0x1FFFFFFF,                 1,                  1);
unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
unsigned int *maskRegAddr;


	C2CTRL1bits.WIN=1;

	// Obtain the Address of CiRXMmSID register for given Mask number "m"
	maskRegAddr = (unsigned int *)(&C1RXM0SID + (m << 1));

	// Bit-filed manupulation to write to Filter Mask register
	if(exide==1) 
	{ 	// Filter Extended Identifier
		eid15_0 = (identifier & 0xFFFF);
		eid17_16= (identifier>>16) & 0x3;
		sid10_0 = (identifier>>18) & 0x7FF;

		if(mide==1)
			*maskRegAddr=((sid10_0)<<5) + 0x0008 + eid17_16;	// Write to CiRXMnSID Register
		else
			*maskRegAddr=((sid10_0)<<5) + eid17_16;	// Write to CiRXMnSID Register
	    *(maskRegAddr+1)= eid15_0;					// Write to CiRXMnEID Register

	}
	else
	{			// Filter Standard Identifier
		sid10_0 = (identifier & 0x7FF);			
		if(mide==1)
			*maskRegAddr=((sid10_0)<<5) + 0x0008;					// Write to CiRXMnSID Register
		else
			*maskRegAddr=(sid10_0)<<5;					// Write to CiRXMnSID Register	
		
		*(maskRegAddr+1)=0;							// Write to CiRXMnEID Register
	}


	C2CTRL1bits.WIN=0;	

}


/* ECAN Transmit Message Buffer Configuration

Inputs:
buf	-> Transmit Buffer Number

txIdentifier ->	

Extended Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
								     |____________|_____________________|
									        SID10:0           EID17:0



Standard Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
														    |___________|
															      SID10:0

Standard Message Format: 
											Word0 : 0b000f ffff ffff ffff
													     |____________|||___
 									        				SID10:0   SRR   IDE     

											Word1 : 0b0000 0000 0000 0000
														   |____________|
															  EID17:6

											Word2 : 0b0000 00f0 0000 ffff
													  |_____||	  	 |__|
													  EID5:0 RTR   	  DLC
										
																  
																	
Extended Message Format: 
											Word0 : 0b000f ffff ffff ffff
													     |____________|||___
 									        				SID10:0   SRR   IDE     

											Word1 : 0b0000 ffff ffff ffff
														   |____________|
															  EID17:6

											Word2 : 0bffff fff0 0000 ffff
													  |_____||	  	 |__|
													  EID5:0 RTR   	  DLC

ide -> "0"  Message will transmit standard identifier
	   "1"  Message will transmit extended identifier



remoteTransmit -> "0" Message transmitted is a normal message
				  "1" Message transmitted is a remote message

				Standard Message Format: 
											Word0 : 0b000f ffff ffff ff1f
													     |____________|||___
 									        				SID10:0   SRR   IDE     

											Word1 : 0b0000 0000 0000 0000
														   |____________|
															  EID17:6

											Word2 : 0b0000 0010 0000 ffff
													  |_____||	  	 |__|
													  EID5:0 RTR   	  DLC
										
																  
																	
				Extended Message Format: 
											Word0 : 0b000f ffff ffff ff1f
													     |____________|||___
 									        				SID10:0   SRR   IDE     

											Word1 : 0b0000 ffff ffff ffff
														   |____________|
															  EID17:6

											Word2 : 0bffff ff10 0000 ffff
													  |_____||	  	 |__|
													  EID5:0 RTR   	  DLC

*/

void ecan2WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit){

unsigned long word0=0, word1=0, word2=0;
unsigned long sid10_0=0, eid5_0=0, eid17_6=0;


if(ide)
	{
		eid5_0  = (txIdentifier & 0x3F);
		eid17_6 = (txIdentifier>>6) & 0xFFF;
		sid10_0 = (txIdentifier>>18) & 0x7FF;
		word1 = eid17_6;
	}
	else
	{
		sid10_0 = (txIdentifier & 0x7FF);
	}
	
	
	if(remoteTransmit==1) { 	// Transmit Remote Frame

		word0 = ((sid10_0 << 2) | ide | 0x2);
		word2 = ((eid5_0 << 10)| 0x0200);}

	else {
		
		word0 = ((sid10_0 << 2) | ide);
		word2 = (eid5_0 << 10);
	     }
			
// Obtain the Address of Transmit Buffer in DMA RAM for a given Transmit Buffer number

if(ide)
	ecan2msgBuf[buf][0] = (word0 | 0x0002);
else
	ecan2msgBuf[buf][0] = word0;

	ecan2msgBuf[buf][1] = word1;
	ecan2msgBuf[buf][2] = word2;
}


/* ECAN Transmit Data

Inputs :
buf -> Transmit Buffer Number

dataLength -> Length of Data in Bytes to be transmitted

data1/data2/data3/data4 ->  Transmit Data Bytes 

*/

void ecan2WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 )
{

	ecan2msgBuf[buf][2] = ((ecan2msgBuf[buf][2] & 0xFFF0) + dataLength) ;
	
	ecan2msgBuf[buf][3]  = data1;
	ecan2msgBuf[buf][4]  = data2;
	ecan2msgBuf[buf][5]  = data3;
	ecan2msgBuf[buf][6]  = data4;

}

/*------------------------------------------------------------------------------
/ Disable RX Acceptance Filter
/ void ecan1DisableRXFilter(int n)
/------------------------------------------------------------------------------
/
n -> Filter number [0-15]
*/

void ecan2DisableRXFilter(int n)
{
unsigned int *fltEnRegAddr;
   C2CTRL1bits.WIN=1;
   fltEnRegAddr = (unsigned int *)(&C2FEN1);
   *fltEnRegAddr = (*fltEnRegAddr) & (0xFFFF - (0x1 << n));
   C2CTRL1bits.WIN=0;

}


int isfreetx2(int buf)
{
  switch (buf)
   {
   case 0 : return !C2TR01CONbits.TXREQ0;
   case 1 : return !C2TR01CONbits.TXREQ1;
   case 2 : return !C2TR23CONbits.TXREQ2;
   case 3 : return !C2TR23CONbits.TXREQ3;
   case 4 : return !C2TR45CONbits.TXREQ4;  
   case 5 : return !C2TR45CONbits.TXREQ5;
   case 6 : return !C2TR67CONbits.TXREQ6;
   case 7 : return !C2TR67CONbits.TXREQ7;
   }
 return 0;
}

void settxtransmit2(int buf)
{
switch (buf)
   {
   case 0 : C2TR01CONbits.TXREQ0=1;	
			break;
   case 1 : C2TR01CONbits.TXREQ1=1;
			break;
   case 2 : C2TR23CONbits.TXREQ2=1;
 			break;
   case 3 : C2TR23CONbits.TXREQ3=1;
			break;
   case 4 : C2TR45CONbits.TXREQ4=1;
			break;
   case 5 : C2TR45CONbits.TXREQ5=1;
			break;
   case 6 : C2TR67CONbits.TXREQ6=1;
			break;
   case 7 : C2TR67CONbits.TXREQ7=1;
			break;
   }
}

 
int sendnormalmsg2(int prio, long txidentifier,unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 )
{ // assumes buffer 0..7 have increasing priority
  // prio to send is nr of buffer tried first, decrease by availability. 
//
  prio++; // 1..8 
  while (prio>0)
    {
      if (isfreetx(prio-1))
       {
         ecan2WriteTxMsgBufId(prio-1,txidentifier,1,0);
         ecan2WriteTxMsgBufData(prio-1,dataLength,data1,data2,data3,data4); 
         settxtransmit2(prio-1);
         return prio; // 1..8 if succesful.
       }
     prio--;
    }
   return 0;
}

void processshorttxtdmsg2(int id,
#if defined(__dsPIC33E__)
						__eds__  
#endif
                            int *msg, int msgval)
{
    Nop();Nop();Nop();
    ID2 = id;
    
    
    
}
void rxECAN2(int message)
{
	unsigned int ide=0;
	unsigned int srr=0;
	unsigned long id=0,d;
    int *can2buf_ptr;
			
	/*
	Standard Message Format: 
	Word0 : 0bUUUx xxxx xxxx xxxx
			     |____________|||
 					SID10:0   SRR IDE(bit 0)     
	Word1 : 0bUUUU xxxx xxxx xxxx
			   	   |____________|
						EID17:6
	Word2 : 0bxxxx xxx0 UUU0 xxxx
			  |_____||	     |__|
			  EID5:0 RTR   	  DLC
	word3-word6: data bytes
	word7: filter hit code bits
	
	Substitute Remote Request Bit
	SRR->	"0"	 Normal Message 
			"1"  Message will request remote transmission
	
	Extended  Identifier Bit			
	IDE-> 	"0"  Message will transmit standard identifier
	   		"1"  Message will transmit extended identifier
	
	Remote Transmission Request Bit
	RTR-> 	"0"  Message transmitted is a normal message
			"1"  Message transmitted is a remote message
	*/
	/* read word 0 to see the message type */
	ide=ecan2msgBuf[message][0] & 0x0001;	
	srr=ecan2msgBuf[message][0] & 0x0002;	
	
	/* check to see what type of message it is */
	/* message is standard identifier */
	if(ide==0)
	{
          // count
        //return;
		id=(ecan2msgBuf[message][0] & 0x1FFC) >> 2;		
	//	frame_type=CAN_FRAME_STD;
	}
	/* mesage is extended identifier */
	else
	{ 
        d=(ecan2msgBuf[message][0] & 0x1FFC);		
		id=d << 16;
		d=ecan2msgBuf[message][1] & 0x0FFF;
		id=id+(d << 6);
		d=(ecan2msgBuf[message][2] & 0xFC00) >> 10;
		id=id+d;		
		 
	}
    

	/* check to see what type of message it is */
	/* RTR message */
	if(srr==1)
	{
        // count
        return;
//		message->message_type=CAN_MSG_RTR;	
	}
	/* normal message */
	else
	{
//        processshorttxtdmsg(id&65535,&ecan1msgBuf[message][3],ecan1msgBuf[message][3]);
        ID2 = id;
        can2buf_ptr = & ecan2msgBuf[message][3];
        CAN2_DATA_buf[0] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
        CAN2_DATA_buf[1] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
        CAN2_DATA_buf[2] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
        CAN2_DATA_buf[3] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
        CAN2_DATA_buf[4] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
        CAN2_DATA_buf[5] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
        CAN2_DATA_buf[6] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
        CAN2_DATA_buf[7] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);      
	}
	
}

void Can2Tasks(void)
{  int fnrb,fbp,fnrbmask;       
   fnrb=C2FIFObits.FNRB;
   fbp=C2FIFObits.FBP;
   if (fnrb<16)
     {
       fnrbmask=1<<fnrb;
       if (C2RXFUL1&fnrbmask)
         {
           rxECAN2(fnrb);
           C2RXFUL1&=~fnrbmask; 	    	
         }
     }
   else
     {
       fnrbmask=1<<(fnrb-16);
       if (C2RXFUL2&fnrbmask)
         {
  	       rxECAN2(fnrb);
      	   C2RXFUL2&=~fnrbmask; 	    	    
         }
     }
}

void __attribute__((interrupt, no_auto_psv))_C2Interrupt(void)  
{
int fnrb,fbp,fnrbmask;
unsigned int ide=0;
unsigned int srr=0;
unsigned long id=0,d;
int *can2buf_ptr;    
    
    
	IFS3bits.C2IF = 0;        // clear interrupt flag
	if(C2INTFbits.TBIF) { 
    	C2INTFbits.TBIF = 0;
    }
    
    if(C2INTFbits.RBIF) {  
//	   rxmsg2++;
        while (C2FIFObits.FNRB != C2FIFObits.FBP ) {
            fnrb=C2FIFObits.FNRB;
            fbp=C2FIFObits.FBP;
               if (fnrb<16) {
                   fnrbmask=1<<fnrb;
                   if (C2RXFUL1&fnrbmask) {
                        ide=ecan2msgBuf[fnrb][0] & 0x0001;	
                        srr=ecan2msgBuf[fnrb][0] & 0x0002;	
                        /* check to see what type of message it is */
                        if(ide==0) {
                            id=(ecan2msgBuf[fnrb][0] & 0x1FFC) >> 2;		
                        }
                        /* mesage is extended identifier */
                        else { 
                            d=(ecan2msgBuf[fnrb][0] & 0x1FFC); id=d << 16;
                            d=ecan2msgBuf[fnrb][1] & 0x0FFF; id=id+(d << 6);
                            d=(ecan2msgBuf[fnrb][2] & 0xFC00) >> 10; id=id+d;		
                        }
                        /* check to see what type of message it is */
                        /* RTR message */
                        if(srr != 1) {/* normal message */
//                            ID = id;
                            CAN2AUX_ID_buf[CAN2AUX_W_ptr][0] = id;
                            can2buf_ptr = & ecan2msgBuf[fnrb][3];
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][0] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][1] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][2] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][3] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][4] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][5] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][6] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][7] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);      
                        }
                       C2RXFUL1&=~fnrbmask; 	    	
                     }
                 }
               else {
                   fnrbmask=1<<(fnrb-16);
                   if (C2RXFUL2&fnrbmask)
                     {
                        ide=ecan2msgBuf[fnrb][0] & 0x0001;	
                        srr=ecan2msgBuf[fnrb][0] & 0x0002;	
                        /* check to see what type of message it is */
                        if(ide==0) {
                            id=(ecan2msgBuf[fnrb][0] & 0x1FFC) >> 2;		
                        }
                        /* mesage is extended identifier */
                        else { 
                            d=(ecan2msgBuf[fnrb][0] & 0x1FFC); id=d << 16;
                            d=ecan2msgBuf[fnrb][1] & 0x0FFF; id=id+(d << 6);
                            d=(ecan2msgBuf[fnrb][2] & 0xFC00) >> 10; id=id+d;		
                        }
                        /* check to see what type of message it is */
                        /* RTR message */
                        if(srr != 1) {/* normal message */
//                            ID = id;
                            CAN2AUX_ID_buf[CAN2AUX_W_ptr][0] = id;
                            can2buf_ptr = & ecan2msgBuf[fnrb][3];
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][0] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][1] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][2] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][3] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][4] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][5] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][6] = (unsigned char)(*(can2buf_ptr) & 0x00FF);
                            CAN2AUX_DATA_buf[CAN2AUX_W_ptr][7] = (unsigned char)((*(can2buf_ptr++) & 0xFF00) >> 8);      
                        }
                       C2RXFUL2&=~fnrbmask; 	    	    
                     }
                 }
            CAN2AUX_W_ptr ++; CAN2AUX_W_ptr %= 25;
            if (CAN2AUX_W_ptr == CAN2AUX_R_ptr) {CAN2AUX_R_ptr++; CAN2AUX_R_ptr %= 25;}
        }       
  	   C2INTFbits.RBIF = 0;
	}
    
    if (C2INTFbits.IVRIF == 1) {
       C2INTFbits.IVRIF = 0;
       Nop();Nop();Nop();
       if (C2INTFbits.TXBO == 1) {
        Nop();Nop();Nop();
        C2INTFbits.TXBO = 0;
//        CAN2_fault = 1;
       }
       if (C2INTFbits.TXBP == 1) {
        Nop();Nop();Nop();
//        C2TR01CONbits.TXREQ0 = 0;
        C2INTFbits.TXBP = 0;
       }
      
    }
       if (C2INTFbits.FIFOIF == 1) {
        Nop();Nop();Nop();
        C2INTFbits.FIFOIF = 0;
       }
       if (C2INTFbits.RBOVIF == 1) {
        Nop();Nop();Nop();
        C2INTEbits.RBOVIE = 0;
        C2INTFbits.RBOVIF = 0;
//        CAN2_fault = 1;
       }     
    
}

