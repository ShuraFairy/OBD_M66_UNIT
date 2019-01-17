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
#include "ECAN1Drv.h"



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
void ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide, unsigned int bufPnt,unsigned int maskSel) {
//   ecan1WriteRxAcptFilter(    1,      0x1FFEFFFF,                  1,                  15,                   0);
unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
unsigned int *sidRegAddr,*bufPntRegAddr,*maskSelRegAddr, *fltEnRegAddr;


	C1CTRL1bits.WIN=1;

	// Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN register for a given filter number "n"
	sidRegAddr     = (unsigned int *)(&C1RXF0SID  + (n << 1));
	bufPntRegAddr  = (unsigned int *)(&C1BUFPNT1  + (n >> 2));
	maskSelRegAddr = (unsigned int *)(&C1FMSKSEL1 + (n >> 3));
	fltEnRegAddr   = (unsigned int *)(&C1FEN1);


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

   C1CTRL1bits.WIN=0;


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
void ecan1WriteRxAcptMask(int m, long identifier, unsigned int mide, unsigned int exide){
//   ecan1WriteRxAcptMask(    1,      0x1FFFFFFF,                 1,                  1);
unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
unsigned int *maskRegAddr;


	C1CTRL1bits.WIN=1;

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


	C1CTRL1bits.WIN=0;	

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

void ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit){

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
	ecan1msgBuf[buf][0] = (word0 | 0x0002);
else
	ecan1msgBuf[buf][0] = word0;

	ecan1msgBuf[buf][1] = word1;
	ecan1msgBuf[buf][2] = word2;
}


/* ECAN Transmit Data

Inputs :
buf -> Transmit Buffer Number

dataLength -> Length of Data in Bytes to be transmitted

data1/data2/data3/data4 ->  Transmit Data Bytes 

*/

void ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 )
{

	ecan1msgBuf[buf][2] = ((ecan1msgBuf[buf][2] & 0xFFF0) + dataLength) ;
	
	ecan1msgBuf[buf][3]  = data1;
	ecan1msgBuf[buf][4]  = data2;
	ecan1msgBuf[buf][5]  = data3;
	ecan1msgBuf[buf][6]  = data4;

}

/*------------------------------------------------------------------------------
/ Disable RX Acceptance Filter
/ void ecan1DisableRXFilter(int n)
/------------------------------------------------------------------------------
/
n -> Filter number [0-15]
*/

void ecan1DisableRXFilter(int n)
{
unsigned int *fltEnRegAddr;
   C1CTRL1bits.WIN=1;
   fltEnRegAddr = (unsigned int *)(&C1FEN1);
   *fltEnRegAddr = (*fltEnRegAddr) & (0xFFFF - (0x1 << n));
   C1CTRL1bits.WIN=0;

}


word isfreetx(word buf)
{
  switch (buf)
   {
   case 0 : return !C1TR01CONbits.TXREQ0;
   case 1 : return !C1TR01CONbits.TXREQ1;
   case 2 : return !C1TR23CONbits.TXREQ2;
   case 3 : return !C1TR23CONbits.TXREQ3;
   case 4 : return !C1TR45CONbits.TXREQ4;  
   case 5 : return !C1TR45CONbits.TXREQ5;
   case 6 : return !C1TR67CONbits.TXREQ6;
   case 7 : return !C1TR67CONbits.TXREQ7;
   }
 return 0;
}

void settxtransmit(word buf)
{
switch (buf)
   {
   case 0 : C1TR01CONbits.TXREQ0=1;	
			break;
   case 1 : C1TR01CONbits.TXREQ1=1;
			break;
   case 2 : C1TR23CONbits.TXREQ2=1;
 			break;
   case 3 : C1TR23CONbits.TXREQ3=1;
			break;
   case 4 : C1TR45CONbits.TXREQ4=1;
			break;
   case 5 : C1TR45CONbits.TXREQ5=1;
			break;
   case 6 : C1TR67CONbits.TXREQ6=1;
			break;
   case 7 : C1TR67CONbits.TXREQ7=1;
			break;
   }
}

 
word sendnormalmsg(word prio, long txidentifier,unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4 )
{ // assumes buffer 0..7 have increasing priority
  // prio to send is nr of buffer tried first, decrease by availability. 
//
  prio++; // 1..8 
  while (prio>0)
    {
      if (isfreetx(prio-1))
       {
         ecan1WriteTxMsgBufId(prio-1,txidentifier,1,0);
         ecan1WriteTxMsgBufData(prio-1,dataLength,data1,data2,data3,data4); 
         settxtransmit(prio-1);
         return prio; // 1..8 if succesful.
       }
     prio--;
    }
   return 0;
}

void processshorttxtdmsg(word id,
#if defined(__dsPIC33E__)
						__eds__  
#endif
                            word *msg, word msgval)
{
    Nop();Nop();Nop();
    ID = id;
    
    
    
}
void rxECAN1(word message)
{
	unsigned int ide=0;
	unsigned int srr=0;
	unsigned long id=0,d;
    int *can1buf_ptr;
			
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
	ide=ecan1msgBuf[message][0] & 0x0001;	
	srr=ecan1msgBuf[message][0] & 0x0002;	
	
	/* check to see what type of message it is */
	/* message is standard identifier */
	if(ide==0)
	{
          // count
        //return;
		id=(ecan1msgBuf[message][0] & 0x1FFC) >> 2;		
	//	frame_type=CAN_FRAME_STD;
	}
	/* mesage is extended identifier */
	else
	{ 
        d=(ecan1msgBuf[message][0] & 0x1FFC);		
		id=d << 16;
		d=ecan1msgBuf[message][1] & 0x0FFF;
		id=id+(d << 6);
		d=(ecan1msgBuf[message][2] & 0xFC00) >> 10;
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
        ID = id;
        can1buf_ptr = & ecan1msgBuf[message][3];
        CAN1_DATA_buf[0] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
        CAN1_DATA_buf[1] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
        CAN1_DATA_buf[2] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
        CAN1_DATA_buf[3] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
        CAN1_DATA_buf[4] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
        CAN1_DATA_buf[5] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
        CAN1_DATA_buf[6] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
        CAN1_DATA_buf[7] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);      
	}
	
}

void Can1Tasks(void){  
//   word fnrb,fbp,fnrbmask;       
//   fnrb=C1FIFObits.FNRB;
//   fbp=C1FIFObits.FBP;
//   if (fnrb<16)
//     {
//       fnrbmask=1<<fnrb;
//       if (C1RXFUL1&fnrbmask)
//         {
//           rxECAN1(fnrb);
//           C1RXFUL1&=~fnrbmask; 	    	
//         }
//     }
//   else
//     {
//       fnrbmask=1<<(fnrb-16);
//       if (C1RXFUL2&fnrbmask)
//         {
//  	       rxECAN1(fnrb);
//      	   C1RXFUL2&=~fnrbmask; 	    	    
//         }
//     }
    
word fnrb,fbp,fnrbmask;
word flag;
   // default way is in in order(FIFO) and simple (no loops)
   flag=0;       
   fnrb=C1FIFObits.FNRB;
   fbp=C1FIFObits.FBP;
   if (fnrb<16)
     {
       fnrbmask=1<<fnrb;
       if (C1RXFUL1&fnrbmask)
         {
           rxECAN1(fnrb);
           C1RXFUL1&=~fnrbmask;             
         }
       else 
       {flag++;}
     }
   else
     {
       fnrbmask=1<<(fnrb-16);
       if (C1RXFUL2&fnrbmask)
         {
             rxECAN1(fnrb);
             C1RXFUL2&=~fnrbmask;                 
         }
       else 
       {flag++;}
     }
 if (flag)
   {
     // after overflow fnrb pointer is corrupt.
     // and we must poll if flags are set.
    if ((C1RXFUL1&0xFF00)>0) 
      {
         fnrb=8; // skip 8 write buffers
         while ((fnrb<16) && (flag>0))
          { 
           fnrbmask=1<<fnrb;
           if (C1RXFUL1&fnrbmask)
             {
               rxECAN1(fnrb);
               C1RXFUL1&=~fnrbmask;             
               flag--;
             }  
            fnrb++; 
          }
       }
     if ((C1RXFUL2)>0) 
       {
         fnrb=0; 
         while ((fnrb<16) && (flag>0))
          { 
           fnrbmask=1<<fnrb;
           if (C1RXFUL2&fnrbmask)
             {
               rxECAN1(16+fnrb);
               C1RXFUL2&=~fnrbmask;             
               flag--;
             }  
            fnrb++; 
          } 
       } 
  // if flag>0 here then something weird is going on.
   } 
    
    
}

void __attribute__((interrupt, no_auto_psv))_C1Interrupt(void)  
{
word fnrb,fbp,fnrbmask;
unsigned int ide=0;
unsigned int srr=0;
unsigned long id=0,d;
int *can1buf_ptr;

           
	IFS2bits.C1IF = 0;        // clear interrupt flag
	if(C1INTFbits.TBIF) { 
    	C1INTFbits.TBIF = 0;
    } 
    
    if(C1INTFbits.RBIF) {  
//	   rxmsg1++;
//        Nop();Nop();Nop();
        while (C1FIFObits.FNRB != C1FIFObits.FBP ) {
            fnrb=C1FIFObits.FNRB;
            fbp=C1FIFObits.FBP;
               if (fnrb<16) {
                   fnrbmask=1<<fnrb;
                   if (C1RXFUL1&fnrbmask) {
                        ide=ecan1msgBuf[fnrb][0] & 0x0001;	
                        srr=ecan1msgBuf[fnrb][0] & 0x0002;	
                        /* check to see what type of message it is */
                        if(ide==0) {
                            id=(ecan1msgBuf[fnrb][0] & 0x1FFC) >> 2;		
                        }
                        /* mesage is extended identifier */
                        else { 
                            d=(ecan1msgBuf[fnrb][0] & 0x1FFC); id=d << 16;
                            d=ecan1msgBuf[fnrb][1] & 0x0FFF; id=id+(d << 6);
                            d=(ecan1msgBuf[fnrb][2] & 0xFC00) >> 10; id=id+d;		
                        }
                        /* check to see what type of message it is */
                        /* RTR message */
                        if(srr != 1) {/* normal message */
//                            ID = id;
                            CAN1AUX_ID_buf[CAN1AUX_W_ptr][0] = id;
                            can1buf_ptr = & ecan1msgBuf[fnrb][3];
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][0] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][1] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][2] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][3] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][4] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][5] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][6] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][7] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);      
                        }
                       C1RXFUL1&=~fnrbmask; 	    	
                     }
                 }
               else {
                   fnrbmask=1<<(fnrb-16);
                   if (C1RXFUL2&fnrbmask)
                     {
                        ide=ecan1msgBuf[fnrb][0] & 0x0001;	
                        srr=ecan1msgBuf[fnrb][0] & 0x0002;	
                        /* check to see what type of message it is */
                        if(ide==0) {
                            id=(ecan1msgBuf[fnrb][0] & 0x1FFC) >> 2;		
                        }
                        /* mesage is extended identifier */
                        else { 
                            d=(ecan1msgBuf[fnrb][0] & 0x1FFC); id=d << 16;
                            d=ecan1msgBuf[fnrb][1] & 0x0FFF; id=id+(d << 6);
                            d=(ecan1msgBuf[fnrb][2] & 0xFC00) >> 10; id=id+d;		
                        }
                        /* check to see what type of message it is */
                        /* RTR message */
                        if(srr != 1) {/* normal message */
//                            ID = id;
                            CAN1AUX_ID_buf[CAN1AUX_W_ptr][0] = id;
                            can1buf_ptr = & ecan1msgBuf[fnrb][3];
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][0] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][1] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][2] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][3] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][4] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][5] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][6] = (unsigned char)(*(can1buf_ptr) & 0x00FF);
                            CAN1AUX_DATA_buf[CAN1AUX_W_ptr][7] = (unsigned char)((*(can1buf_ptr++) & 0xFF00) >> 8);

                        }
                       C1RXFUL2&=~fnrbmask; 	    	    
                     }
                 }
            CAN1AUX_W_ptr ++; CAN1AUX_W_ptr %= 25;
            if (CAN1AUX_W_ptr == CAN1AUX_R_ptr) {CAN1AUX_R_ptr++; CAN1AUX_R_ptr %= 25;}
        }
  	   C1INTFbits.RBIF = 0;
	}
    
    if (C1INTFbits.IVRIF == 1) {
       C1INTFbits.IVRIF = 0;
       Nop();Nop();Nop();
       if (C1INTFbits.TXBO == 1) {
        Nop();Nop();Nop();
        C1INTFbits.TXBO = 0;
//        CAN1_fault = 1;
       }
       if (C1INTFbits.TXBP == 1) {
        Nop();Nop();Nop();
        C1INTFbits.TXBP = 0;
       }
      
    }
       if (C1INTFbits.FIFOIF == 1) {
        Nop();Nop();Nop();
        C1INTFbits.FIFOIF = 0;
       }
       if (C1INTFbits.RBOVIF == 1) {
        Nop();Nop();Nop();
        C1INTEbits.RBOVIE = 0;
        C1INTFbits.RBOVIF = 0;
//        CAN1_fault = 1;
       }  
    
}

