/* 
 * File:   cancommon.h
 * Author: user
 *
 * Created on 26 апреля 2016 г., 8:40
 */

#ifndef CANCOMMON_H
#define	CANCOMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

extern union __attribute__ ((far))  {
    unsigned long long CANIGNPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANIGNPRMSbits;
extern union __attribute__ ((far))  {
    unsigned long long CANDDPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANDDPRMSbits;  // Дверь водителя
extern union __attribute__ ((far))  {
    unsigned long long CANFPDPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANFPDPRMSbits; // Передняя пассажирская дверь 
extern union __attribute__ ((far))  {
    unsigned long long CANRLDPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANRLDPRMSbits; // Левая задняя дверь
extern union __attribute__ ((far))  {
    unsigned long long CANRRDPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANRRDPRMSbits; // Правая задняя дверь
extern union __attribute__ ((far))  {
    unsigned long long CANBNPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANBNPRMSbits;// Багажник
extern union __attribute__ ((far))  {
    unsigned long long CANBTPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANBTPRMSbits;// Капот
extern union __attribute__ ((far))  {
    unsigned long long CANODOPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char filt_number:4;
        unsigned int :2;
        unsigned char byte0:8;
        unsigned char byte1:8;
        unsigned char byte2:8;
        unsigned long id:29;        
        unsigned int :3;
    };
} CANODOPRMSbits;//
extern union __attribute__ ((far))  {
    unsigned long long CANFLPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char filt_number:4;
        unsigned long :2;
        unsigned char byte0:8;
        unsigned long id:29;        
        unsigned long :19;

    };
} CANFLPRMSbits;//
extern union __attribute__ ((far))  {
    unsigned long long CANBELTPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} CANBELTPRMSbits;//
extern union __attribute__ ((far))  {
    unsigned long long LOCKSTATPRMS;
   struct 
    {
		unsigned char can_number:2;
        unsigned char inv:1;
        unsigned char :5;        
        unsigned char filt_number:4;
        unsigned char byte:4;
        unsigned char bit_mask:8;
        unsigned long id:29;        
        unsigned int :11;
    };
} LOCKSTATPRMSbits;//



#ifdef	__cplusplus
}
#endif

#endif	/* CANCOMMON_H */

