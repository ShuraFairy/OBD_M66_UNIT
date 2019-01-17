/* 
 * File:   Variables.h
 * Author: petrov
 *
 * Created on 13 декабря 2018 г., 11:31
 */

#ifndef VARIABLES_H
#define	VARIABLES_H

union __attribute__ ((far))  {
    unsigned long long CANTESTPRMS;
    struct 
    {
		unsigned char can_number    : 2;
        unsigned char               : 2;
        unsigned char filt_number   : 4;
        unsigned char bit_mask      : 8;        
        unsigned char value1        : 8;
        unsigned char value2        : 8;
        unsigned long id            : 29;
        unsigned char byte          : 3;        
    };
} CANTESTPRMSbits;    
    


#endif	/* VARIABLES_H */

