/* 
 * File:   Variables.h
 * Author: petrov
 *
 * Created on 13 декабря 2018 г., 11:31
 */

#ifndef VARIABLES_H
#define	VARIABLES_H

#include <stdint.h>
//********************************* Variables **********************************
////////////////////////////////////////////////////////////////////////////////
// FMS-Stantard description - Service Information: SERV
// ID - 0x18FEC027
// spn914 - Service Distance - The distance which can be traveled by the vehicle before the next service inspection is required.
// A negative distance is transmitted if the service inspection has been passed. The component that requires service is identified by the
// service component identification (see SPN 911-913, 1379, and 1584).
// Data Length:                     2 bytes
// Resolution:                      5 km/bit , -160,635 km offset
// Data Range:                      -160,635 to 160,640 km
// Type:                            Measured
// Suspect Parameter Number:        914
// Parameter Group Number (PGN):    0x00FEC0 (65216)
// Rep. Rate:                       1000 ms
union __attribute__ ((far))  {
    uint64_t SERVICEDISTANCE;
    struct 
    {
        uint8_t  can_number  : 2;
        uint8_t  filt_number : 4;		
        uint16_t             : 10;
        uint32_t id          : 29;
        uint8_t              : 3;
        uint8_t  value1      : 8;
        uint8_t  value2      : 8;
    };
} SERVICEDISTANCEbits;
////////////////////////////////////////////////////////////////////////////////
// FMS-Stantard description - Engine Temperature 1: ET1
// ID - 0x18FEEE00
// spn110 - Engine Coolant Temperature - Temperature of liquid found in engine cooling system.
// Data Length:                     1 byte
// Resolution:                      1 deg C/bit , -40 deg C offset
// Data Range:                      -40 to 210 deg C
// Type:                            Measured
// Suspect Parameter Number:        110
// Parameter Group Number (PGN):    0x00FEEE (65262)
// Rep. Rate:                       1000 ms
union __attribute__ ((far))  {
    uint64_t EGINECOOLANTTEMPERATURE;
    struct 
    {
        uint8_t  can_number  : 2;
        uint8_t  filt_number : 4;
		uint8_t  value       : 8;
        uint8_t              : 2;
        uint32_t id          : 29;
        uint8_t              : 3;
        uint16_t             : 16;              
    };
} EGINECOOLANTTEMPERATUREbits;
////////////////////////////////////////////////////////////////////////////////
// FMS-Stantard description - Engine Hours, Revolutions: HOURS
// ID - 0x18FEE527
// spn247 - Total Engine Hours - Accumulated time of operation of engine.
// Data Length:                     4 bytes
// Resolution:                      0.05 hr/bit , 0 offset
// Data Range:                      0 to 210,554,060.75 hr
// Type:                            Measured
// Suspect Parameter Number:        247
// Parameter Group Number (PGN):    0x00FEE5 (65253)
// Rep. Rate:                       1000 ms
union __attribute__ ((far))  {
    uint64_t ENGINETOTALHOURSCONF;
    struct 
    {
        uint8_t  can_number  : 2;
        uint8_t  filt_number : 4;
        uint16_t             : 10;
        uint32_t id          : 29;
        uint8_t              : 3;
        uint16_t             : 16;              
    };
} ENGINETOTALHOURSCONFbits;
union __attribute__ ((far))  {
    uint32_t ENGINETOTALHOURS;
    struct 
    {        
		uint8_t  value1      : 8;
        uint8_t  value2      : 8;
        uint8_t  value3      : 8;
        uint8_t  value4      : 8;                    
    };
} ENGINETOTALHOURSbits;
////////////////////////////////////////////////////////////////////////////////
// FMS-Stantard description - High Resolution Vehicle Distance: VHDR
// ID - 0x18FEC1EE
// spn917 - High Resolution Total Vehicle Distance - Accumulated distance traveled by the vehicle during its
// operation. NOTE - See SPN 245 for alternate resolution.
// Data Length:                     4 bytes
// Resolution:                      5 m/bit , 0 offset
// Data Range:                      0 to 21,055,406 km
// Type:                            Measured
// Suspect Parameter Number:        917
// Parameter Group Number (PGN):    0x00FEC1 (65217)
// Rep. Rate:                       1000 ms
union __attribute__ ((far))  {
    uint64_t TOTALVEHICLEDISTANCECONF;
    struct 
    {
        uint8_t  can_number  : 2;
        uint8_t  filt_number : 4;
        uint16_t             : 10;
        uint32_t id          : 29;
        uint8_t              : 3;
        uint16_t             : 16;              
    };
} TOTALVEHICLEDISTANCECONFbits;
union __attribute__ ((far))  {
    uint32_t TOTALVEHICLEDISTANCE;
    struct 
    {        
		uint8_t  value1      : 8;
        uint8_t  value2      : 8;
        uint8_t  value3      : 8;
        uint8_t  value4      : 8;                    
    };
} TOTALVEHICLEDISTANCEbits;
////////////////////////////////////////////////////////////////////////////////
// FMS-Stantard description - Fuel Consumption: LFC
// ID - 0x18FEE927
// spn250 - Total Fuel Used - Accumulated amount of fuel used during vehicle operation.
// Data Length:                     4 bytes
// Resolution:                      0.5 L/bit , 0 offset
// Data Range:                      0 to 2,105,540,607.5 L
// Type:                            Measured
// Suspect Parameter Number:        250
// Parameter Group Number (PGN):    0x00FEE9(65257)
// Rep. Rate:                       1000 ms
union __attribute__ ((far))  {
    uint64_t TOTALFUELUSEDCONF;
    struct 
    {
        uint8_t  can_number  : 2;
        uint8_t  filt_number : 4;
        uint16_t             : 10;
        uint32_t id          : 29;
        uint8_t              : 3;
        uint16_t             : 16;              
    };
} TOTALFUELUSEDCONFbits;
union __attribute__ ((far))  {
    uint32_t TOTALFUELUSED;
    struct 
    {        
		uint8_t  value1      : 8;
        uint8_t  value2      : 8;
        uint8_t  value3      : 8;
        uint8_t  value4      : 8;                    
    };
} TOTALFUELUSEDbits;
////////////////////////////////////////////////////////////////////////////////
// FMS-Stantard description - Dash Display: DD
// ID - 0x18FEFC21
// spn96 - Fuel Level - Ratio of volume of fuel to the total volume of fuel storage container.
// Data Length:                     1 byte
// Resolution:                      0.4 %/bit , 0 offset
// Data Range:                      0 to 100 %
// Type:                            Measured
// Suspect Parameter Number:        96
// Parameter Group Number (PGN):    0x00FEFC (65276)
// Rep. Rate:                       1000 ms
union __attribute__ ((far))  {
    uint64_t FUELLEVEL;
    struct 
    {
        uint8_t  can_number  : 2;
        uint8_t  filt_number : 4;
		uint8_t  value       : 8;
        uint8_t              : 2;
        uint32_t id          : 29;
        uint8_t              : 3;
        uint16_t             : 16;              
    };
} FUELLEVELbits;
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
union __attribute__ ((far))  {
    uint32_t Data;   
    struct 
    {
		uint8_t can_number  : 2;
        uint8_t filt_number : 4;
        uint8_t bit_mask    : 8; 
        uint8_t             : 2;    
        uint16_t id         : 11;
        uint8_t             : 5;
    } Bits;
} DIAGNOSTICSConfig;  
////////////////////////////////////////////////////////////////////////////////
union __attribute__ ((far))  {
    uint64_t Data;   
    struct 
    {	
        uint8_t data0       : 8;
        uint8_t data1       : 8;
        uint8_t data2       : 8;
        uint8_t data3       : 8;
        uint8_t data4       : 8;
        uint8_t data5       : 8; 
        uint8_t data6       : 8;
        uint8_t data7       : 8;
    } Bits;
} DIAGNOSTICSData;

// ID - 0x0001, Description for inputStatesRecord
union __attribute__ ((far))  {
    uint16_t Data; 
    struct
    {
        uint8_t Input_ACC       : 2;    // 1-0 bits      // 0 - low, 1 - high, 2 - undefined, 3 - not used 
        uint8_t Input_KL15      : 2;    // 3-2 bits      // 0 - low, 1 - high, 2 - undefined, 3 - not used
        uint8_t Input_Service   : 2;    // 5-4 bits      // 0 - low, 1 - high, 2 - undefined, 3 - not used
        uint8_t Input_SOS       : 2;    // 7-6 bits      // 0 - low, 1 - high, 2 - undefined, 3 - not used
        uint8_t                 : 4;
        uint8_t Input_3         : 2;    // 13-12 bits    // 0 - low, 1 - high, 2 - undefined, 3 - not used
        uint8_t Input_2         : 2;    // 15-14 bits    // 0 - low, 1 - high, 2 - undefined, 3 - not used
    } Bits;
} inputStatesRecord;

// ID - 0x0002, Description for outputStatesRecord
union __attribute__ ((far))  {
    uint32_t Data;  
    struct
    {
        uint8_t Output_KL15A        : 2;    // 1-0 bits     // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_SOS_LED      : 2;    // 3-2 bits     // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_SERVICE_LED  : 2;    // 5-4 bits     // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_LockDoor     : 2;    // 7-6 bits     // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_Backlight    : 2;    // 9-8 bits     // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_AS_Button    : 2;    // 11-10 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_Klakson      : 2;    // 13-12 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_Preheater    : 2;    // 15-14 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_ON_OFF_Mode  : 2;    // 17-16 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_ON_Charge    : 2;    // 19-18 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_RED_LED      : 2;    // 21-20 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t Output_GREEN_LED    : 2;    // 23-22 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
        uint8_t                     : 2;    //
        uint8_t                     : 2;    //
        uint8_t                     : 2;    //
        uint8_t Output_Mute         : 2;    // 31-30 bits   // 0 - off, 1 - on, 2 - undefined, 3 - not used
    } Bits;
} outputStatesRecord;

// ID - 0x0003, Description for boardVoltage
// Invalid Value = 0xFF, Min = 0, Max = 24.021, Formula - N = 0.0942 * E, Unit - V
uint8_t  boardVoltage;

// ID - 0x0004, Description for reserveBatteryCharge
// Invalid Value = 0xFF, Min = 0, Max = 100, Formula - N = 0.3922 * E, Unit - %
uint8_t  reserveBatteryCharge;

// ID - 0x0005, Description for reserveBatteryTemperature
// Invalid Value = 0xFF, Min = -40, Max = 87, Formula - N = 0.3922 * E, Unit - °C
uint8_t reserveBatteryTemperature;

// ID - 0x0006, Description for SystemState
union __attribute__ ((far))  {
    uint32_t Data;  
    struct
    {
        uint8_t Comfort_State           : 2;    // 0 - ACC off
                                                // 1 - ACC on
                                                // 2 - not used
                                                // 3 - undefined
        uint8_t Airbag_State            : 3;    // 0 - idle
                                                // 1 - ENS act
                                                // 2 - Network act
                                                // 3 - Indirect act
                                                // 4 - error
                                                // 5,6 - not used
                                                // 7 - undefined
        uint8_t TCM_State               : 3;    // 0 - work
                                                // 1 - initializing
                                                // 2 - prework
                                                // 3 - sleep
                                                // 4 - reset
                                                // 5 - testing
                                                // 6 - boot
                                                // 7 - send at
        uint8_t                         : 3;
        uint8_t Battery_State           : 3;    // 0 - no charging
                                                // 1 - trickle charging
                                                // 2 - fast charging
                                                // 3 - care charging
                                                // 4 - check old
                                                // 5 - check absence
                                                // 6 - stabilization
                                                // 7 - undefined
        uint8_t Motion_State            : 2;    // 0 - ignition off
                                                // 1 - ignition on
                                                // 2 - not used
                                                // 3 - undefined
        uint8_t                         : 2;
        uint8_t Rollover_agngle_status  : 2;    // 1 - tilt exceeded
                                                // 0 - tilt in tolerance
        uint8_t GSM_State               : 5;    // 0 - initializing;
                                                // 1 - idle
                                                // 2 - sleep
                                                // 3 - testing_w1
                                                // 4 - testing_w2
                                                // 5 - testing_w3
                                                // 6 - testing_other
                                                // 7 - testing_sound_condition
                                                // 8 - SOS comm
                                                // 9 - SERV comm
                                                // 10 - registration
                                                // 11 - call_preparation
                                                // 12 - dial
                                                // 13 - enable_sleep
                                                // 14 - sleep_pin
                                                // 15 - MSD_sends
                                                // 16 - incoming_call
                                                // 17 - not initialized
                                                // 18-30 - not used
                                                // 31 - undefined
    } Bits;
} SystemState;

// ID - 0x0007, Description for vehicleCoordinates
__attribute__ ((far)) struct VehicleCoordinates
{
    uint32_t vehicleLattitude;  // Invalid value - 0xFFFFFFFF, Min = -90, Max = 90
                                // Formula - N = (E / 3600000) - 90;
    uint32_t vehicleLongitude;  // Invalid value - 0xFFFFFFFF, Min = -180, Max = 180
                                // Formula - N = (E / 3600000) - 180;
} vehicleCoordinates;

// ID - 0x0008, vehicleCoordinatesReliability - Current value of vehicle coordinates reliability
uint8_t vehicleCoordinatesReliability;      // 0 - false, 1 - true, 2 - undefined, 3 - not used

// ID - 0x0009, MDS_FormatVersion - Current format version of Minimum Data Set
uint8_t MDS_FormatVersion;                  // uint8 (0 - 255)

// ID - 0x000A, Description for vehicleFuelType
union __attribute__ ((far))  {
    uint8_t Data; 
    struct
    {
        uint8_t                         : 1;
        uint8_t hydrogen                : 1;    // 0 - not hydrogen, 1 - hydrogen
        uint8_t electricEnergy          : 1;    // 0 - not electric energy, 1 - electric energy
        uint8_t liquidPropaneGas        : 1;    // 0 - not liquid propane gas, 1 - liquid propane gas
        uint8_t compressedNaturalGas    : 1;    // 0 - not compressed natural gas, 1 - compressed natural gas
        uint8_t diesel                  : 1;    // 0 - not diesel, 1 - diesel
        uint8_t gasoline                : 1;    // 0 - not gasoline, 1 - gasoline
    } Bits;
} vehicleFuelType;

// ID - 0x000B, timeStamp - Current value of seconds from 0:00 am 01/01/1970, Invalid valuex - 0xFFFFFFFF
uint32_t timeStapm;     

// ID - 0x000C, passengersNumber - Current value of passenger number
// uint8, min = 0, max = 254, 0xFF - undefined
uint8_t passengersNumber;

// ID - 0x000D, TCM_working_mode - The working of TCM
// 0x5A - working mode, 0xA5 - factory mode
uint8_t TCM_working_mode;

// ID - 0x000E, TCM_activation_source - The way of the TCM activation
// 0 - non-activated, 1 - auto-activated, 2 - manually activated, 3 - undefined
uint8_t TCM_activation_source;

// ID - 0x000F, TCM_time_calculation - The source of the TIMESTAMP
// uint8(0 bit), 0 - GPS/GLONASS, 1 - internal RTC
uint8_t TCM_time_calculation;

// ID - 0x0010, ECALLManualCanCancel - Current state the ecall_manual_can_cancel
// 0xC7 - active, 0x7C - inactive
uint8_t ECALLManualCanCancel;

// ID - 0x0011, GLONASS_and_GLONASS_GPS_groups - The switching between the sattelites groups
// uint8(0 bit), 0 - GPS/GLONASS, 1 - GLONASS
uint8_t GLONASS_and_GLONASS_GPS_groups;

// ID -0x0012, GsmRegistrationState - The state of the BEG registration in the GSM network
// 0-1 bits, 0 - not registered, 1 - registered in the HomeGSM network
// 2 - registered in the Roaming GSM network, 3 - not used
uint8_t GsmRegistrationState;

// ID - 0x0013, GsmInnerError - if an error presents in the GSM module
// 0-1 bits, 0 - undefined, 1 - no errors, 2 - the inner error, 3 - not used
uint8_t GsmInnerError;

// ID - 0x0014, VehicleCoordinatesReliabilityMem - Current value of vehicle coordinates reliability in memory
// 0-1 bits, 0 - false, 1 - true, 2 - undefined, 3 - not used
uint8_t VehicleCoordinatesReliabilityMem;

// ID - 0x0015, GsmRegistrationStateMem - The state of the BEG registration in the GSM network in memory
// 0-1 bits, 0 - not registered, 1 - registered in the Home GSM network,
// 2 - registered in the Roaming GSM network, 3 - not used
uint8_t GsmRegistrationStateMem;

// ID - 0x0016, GsmRegistrationError - The parameter shows whether the module failed to register successfully or not
// 0-1 bits, 0 - undefined, 1 - no errors, 2 - error, 3 - not used
uint8_t GsmRegistrationError;

// ID - 0x0017, EcallOn - This parameter specifies whether the emergency call is allowed or not
// 0x3B - emergency call is active, 0xB3 - emergency call inactive
uint8_t EcallOn;

// ID - 0x0018, CrashSignalExternal - This parameter specifies if external crash signal is active or not
// 0x8D - signal is active, 0xD8 - signal is inactive
uint8_t CrashSignalExternal;

// ID - 0x0019, TestModeEndDistance - The distance radius in which allowed to carry selt-test, meters
// uint16, min = 0, max = 0xFFFF
uint16_t TestModeEndDistance;

// ID - 0x001A, GnssPowerOffTime - The switching off time of the GLONASS module after the ignition is off
// uint16, min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t GnssPowerOffTime;

// ID - 0x001B, AutomationActivationProhibition - The prohibition of the automatic activation process
// uint8(0 bit), 0 - activation allowed, 1 - activation prhibited
uint8_t AutomationActivationProhibition;

// ID - 0x001C, VehicleType - The vehicle type
// 0-2 bits, 0 - M1 Passenger vehicle, 1 - M2 Autobus (<= 5 tonn), 2 - M3 Autobus (> 5 tonn),
// 3 - N1 Truck (<= 3.5 tonn), 4 - N2 Truck (> 3.5 and <= 12 tonn),
// 5 - N3 Truck (> 12 tonn), 6,7 - not used
uint8_t VehicleType;

// ID - 0x001D, SimIdentifier - The ICCID number of the sim-chip, ASCII
char SimIdentifier [19]; 

// ID - 0x0301, CallAutoAnswerTime - The duration of the auto answer after the call from the TCM, minutes
// min = 0, max = 480, 0xFFFF - undefined
uint16_t CallAutoAnswerTime;

// ID - 0x0302, ECALLTestNumber - The ECALL test number
// Null terminated string, Unused characters fill with 0x00
char ECALLTestNumber [20];

// ID - 0x0303, ECALLToTest - Whether the ECALL is the test number of the 112 emergency number
// 0 - ECALL is the 112 emergency number, 1 - ECALL is the test number,
// 2 - ECALL is the debug number
uint8_t ECALLToTest;

// ID - 0x0304, NadRegistrationTimer - The time of the deregistration from the network, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t NadRegistrationTimer;

// ID - 0x0305, NadRegistrationAtStartup - The time, when the TCM will be registered in the network
// uint8(0 bit), 0 - registration by call, 1 - registration at startup
uint8_t NadRegistrationAtStartup;

// ID - 0x0306, SMSCenterNumber - The SMS center number
// Null terminated string, Unused characters fill with 0x00
char SMSCenterNumber [20];

// ID - 0x0307, SMSFallbackNumber - The SMS fallback number
// Null terminated string, Unused characters fill with 0x00
char SMSFallbackNumber [20];

// ID - 0x030E, TestRegitrationPeriod - The time in minutes between next registration and end of the
// PostRegistrationTime, if "Service functions" (test call, etc.) were initialized, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t TestRegitrationPeriod;

// ID - 0x030F, EcallManualDialAttempts - The number of manual eCall attempts
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t EcallManualDialAttempts;

// ID - 0x0310, IntMemTransmitInterval - The time between tries to transmit MSD, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t IntMemTransmitInterval;

// ID - 0x0311, IntMemTransmitAttempts - The number of attempts to transmit MSD
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t IntMemTransmitAttempts;

// ID - 0x0312, GSMSoftwareVersionNumber - GSM Software version number
// Null terminated string, Unused characters fill with 0x00
char GSMSoftwareVersionNumber [10];

// ID - 0x0316, SmsFallbackTestNumber - The SMS test fallback number
// Null terminated string, Unused characters fill with 0x00
char SmsFallbackTestNumber [20];

// ID - 0x0319, EcallAutoDialAttempts - The number of auto eCall attempts
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t EcallAutoDialAttempts;

// ID - 0x031A, EcallDialDuration - The duration of ecall dial attempt, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t EcallDialDuration = 0;

// ID - 0x031B, PostTestRegistrationTime - The time in seconds of registration after the end of the
// "Service functions" (test call, etc.), minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t PostTestRegistrationTime = 0;

// ID - 0x031C, SimProfileAmount - The number of SIM profiles
// min = 0, max = 0xFE, 0xFF - undefined
uint8_t SimProfileAmount = 0;

// ID - 0x031D, Description for SimProfile - The current SIM profile and manufacturer
union __attribute__ ((far))  {
    uint8_t Data; 
    struct
    {        
        uint8_t SimManufacturer : 4;    // 0 - oberthur
                                        // 2 - gemalto
                                        // 3 - morpho
                                        // Other not used
        uint8_t SimProfile      : 4;    // 0 - ERA 
                                        // 1-14 - commercial
    } Bits;
} SimProfile;

// ID - 0x0323, AudioProfile - The current audio profile
// min = 0, max = 250, 251-254 - not used, 0xFF - undefined
uint8_t AudioProfile;

// ID - 0x0401, Description for AccelerometerRawData - Raw data from accelerometer
__attribute__ ((far)) struct AccelerometerRawData
{
    uint16_t X_axis_data;                           // Invalid value - 0xFFFF, Min = -32768, Max = 32767
                                                    // g, Raw data from accelerometer, N = E / 120
    uint16_t Y_axis_data;                           // Invalid value - 0xFFFF, Min = -32768, Max = 32767
                                                    // g, Raw data from accelerometer, N = E / 120
    uint16_t Z_axis_data;                           // Invalid value - 0xFFFF, Min = -32768, Max = 32767
                                                    // g, Raw data from accelerometer, N = E / 120
    uint16_t Tilt_angle_relative_to_the_horizon;    // Invalid value - 0xFFFF, Min = 0, Max = 180
                                                    // angle, N = E
} accelerometerRawData;

// ID - 0x0402, RolloverAngle - Calibration angle for rollover detection, degree
// min = 0, max = 180, 0xFF - undefined
uint8_t RolloverAngle;

// ID - 0x0403, olloverTime - Calibration Time for rollover detection
// Invalid Value - 0xFF, min = 0, max = 0xFE, Formule - N = E * 10
uint8_t RolloverTime;

// ID - 0x0404, AccelCalibrationX - Accelerometer axis data, g
// Invalid Value - 0xFFFF, min = -32768, max = 32767, Formula - N = E / 1200
uint16_t AccelCalibrationX;

// ID - 0x0405, AccelCalibrationY - Accelerometer axis data, g
// Invalid Value - 0xFFFF, min = -32768, max = 32767, Formula - N = E / 1200
uint16_t AccelCalibrationY;

// ID - 0x0406, AccelCalibrationZ - Accelerometer axis data, g
// Invalid Value - 0xFFFF, min = -32768, max = 32767, Formula - N = E / 1200
uint16_t AccelCalibrationZ;

// ID - 0x0407, EcallNoAutomaticTriggering
// 0x29 - prohibited, 0x92 - allowed
uint8_t EcallNoAutomaticTriggering;

// ID - 0x0408, MiddletState - State of GSM middlet
// 0 - not activated, 1 - wait activation, 2 - activated
uint8_t MiddletState;

// ID - 0x0409, SW_Version
// ASCII
char SW_Version [27];

// ID - 0x040A, Vehicle_SW_Version
// ASCII
char Vehicle_SW_Version [24];

// ID - 0x040B, Middlet_SW_Version
// ASCII (only 0x30 - 0x39 char)
char Middlet_SW_Version [24];

// ID - 0x01FF, SavedMSDAmount - The total number of saved MSDs, which were unsent
// through the inband or SMS channel
// min = 0, max = 100, 0xFF - undefined
uint8_t SavedMSDAmount;

// ID - 0x02FF, SentMSDAmount - The total number of saved MSDs, which were are in the
// order to be sent
// min = 0, max = 100, 0xFF - undefined
uint8_t SentMSDAmount;

// ID - 0xF187, vehicleManufacturerSparePartNumber - Order part number reference
// ASCII
char vehicleManufacturerSparePartNumber [10];

// ID - 0xF188, ConfigurationFileReferenceLink - Corresponding PDX file name (combination of
// 0xF1A0, 0xF194, 0xF195, 0xF18A). Equal to reference to a physical part, consisting
// from PCB + Boot + Application + Calibration
// ASCII
char ConfigurationFileReferenceLink [10];

// ID - 0xF18A, systemSupplierIdentifier - The number identifies TCM supplier
// ASCII
char systemSupplierIdentifier [3];

// ID - 0xF18C, ECUSerialNumber - Serial number of TCM, placed on sticker
char ECUSerialNumber [20];

// ID - 0xF190, vehicleIdentificationNumber - Vehicle identification number
// ASCII
char vehicleIdentificationNumber[17]; 

// ID - 0xF191, vehicleManufacturerECUHardwareNumber - This number identifies TCM hardware and bootloader
// ASCII
char vehicleManufacturerECUHardwareNumber [10];

// ID - 0xF194, systemSupplierECUSoftwareNumber - Software Number of TCM
// ASCII
char systemSupplierECUSoftwareNumber [2];

// ID - 0xF195, systemSupplierECUSoftwareVersionNumber - Software Version Number
// ASCII
char systemSupplierECUSoftwareVersionNumber [2];

// ID - 0xF1A0, VDIAG - Diag Version
// min = 0, max = 0xFE, 0xFF - undefined
uint8_t VersionDIAG = 0;


uint16_t IDParameter;
uint16_t __temp;

//****************************** Functions prototype ***************************
void initTruckVariables(void);

#endif	/* VARIABLES_H */

