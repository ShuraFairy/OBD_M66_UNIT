/****************************************************/
/* (—) ŒŒŒ "À”¬", 2019                              */
/* ¿‚ÚÓ: œÂÚÓ‚ ¿ÎÂÍÒ‡Ì‰  						*/
/* ƒ‡Ú‡: 22.01.2019									*/
/* ŒÔËÒ‡ÌËÂ: ›–¿-√ÀŒÕ¿——							*/
/****************************************************/
#ifndef ERA_H
#define	ERA_H

#include <stdint.h>
//********************************** Defines ***********************************
// Identifiers ReadDataByIdentifier service
#define READ_DATA_BY_IDENTIFIER                     0x22

#define INPUT_STATES_RECORD                         0x0001
#define OUTPUT_STATES_RECORD                        0x0002
#define BOARD_VOLTAGE                               0x0003
#define RESERVE_BATTERY_CHARGE                      0x0004
#define RESERVE_BATTERY_TEMPERATURE                 0x0005
#define SYSTEM_STATE                                0x0006
#define VEHICLE_COORDINATES                         0x0007
#define VEHICLE_COORDINATES_RELIABILITY             0x0008
#define MDS_FORMAT_VERSION                          0x0009
#define VEHICLE_FUEL_TYPE                           0x000A
#define TIME_STAMP                                  0x000B
#define PASSENGERS_NUMBER                           0x000C
#define TCM_WORKING_MODE                            0x000D
#define TCM_ACTIVATION_SOURCE                       0x000E
#define TCM_TIME_CALCULATION                        0x000F
#define ECALL_MANUAL_CAN_CANCEL                     0x0010
#define GLONASS_GPS_GROUPS                          0x0011
#define GSM_REGISTRATION_STATE                      0x0012
#define GSM_INNER_ERROR                             0x0013
#define VEHICLE_COORDINATES_RELIABILITY_MEM         0x0014
#define GSM_REGISTRATION_STATE_MEM                  0x0015
#define GSM_REGISTRATION_ERROR                      0x0016
#define ECALL_ON                                    0x0017
#define CRASH_SIGNAL_EXTERNAL                       0x0018
#define TEST_MODE_END_DISTANCE                      0x0019
#define GNSS_POWER_OFF_TIME                         0x001A
#define AUTOMATION_ACTIVATION_PROHIBITION           0x001B
#define VEHICLE_TYPE                                0x001C
#define SIM_IDENTIFIER                              0x001D
#define CALL_AUTO_ANSWER_TIME                       0x0301
#define ECALL_TEST_NUMBER                           0x0302
#define ECALL_TO_TEST                               0x0303
#define NAD_DEREGISTRATION_TIMER                    0x0304
#define NAD_REGISTRATION_STARTUP                    0x0305
#define SMS_CENTER_NUMBER                           0x0306
#define SMS_FALLBACK_NUMBER                         0x0307
#define TEST_REGISTRATION_PERIOD                    0x030E
#define ECALL_MANUAL_DIAL_ATTEMPTS                  0x030F
#define INT_MEM_TRANSMIT_INTERVAL                   0x0310
#define INT_MEM_TRANSMIT_ATTEMPTS                   0x0311
#define GSM_SOFTWARE_VERSION_NUMBER                 0x0312
#define SMS_FALLBACK_TEST_NUMBER                    0x0316
#define ECALL_AUTO_DIAL_ATTEMPTS                    0x0319
#define ECALL_DIAL_DURATION                         0x031A
#define POST_TEST_REGISTRATION_TIME                 0x031B
#define SIM_PROFILE_AMOUNT                          0x031C
#define SIM_PROFILE                                 0x031D
#define AUDIO_PROFILE                               0x0323
#define ACCELEROMETER_RAW_DATA                      0x0401
#define ROLLOVER_ANGLE                              0x0402
#define ROLLOVER_TIME                               0x0403
#define ACCEL_CALIBRATION_X                         0x0404
#define ACCEL_CALIBRATION_Y                         0x0405
#define ACCEL_CALIBRATION_Z                         0x0406
#define ECALL_NO_AUTOMATIC_TRIGGERING               0x0407
#define MIDDLET_STATE                               0x0408
#define SW_VERSION                                  0x0409
#define VEHICLE_SW_VERSION                          0x040A
#define MIDDLET_SW_VERSION                          0x040B
#define SAVED_MSD_AMOUNT                            0x01FF
#define SENT_MSD_AMOUNT                             0x02FF
#define VEHICLE_MANUFACTURER_SPARE_PART_NUMBER      0xF187
#define CONFIGURATION_FILE_REFERENCE_LINK           0xF188
#define SYSTEM_SUPPLIER_IDENTIFIER                  0xF18A
#define ECU_SERIAL_NUMBER                           0xF18C
#define VEHICLE_IDENTIFICATION_NUMBER               0xF190
#define VEHICLE_MANUFACTURER_ECU_HARDWARE_NUMBER    0xF191
#define SYSTEM_SUPPLIER_ECU_SOFTWARE_NUMBER         0xF194
#define SYSTEM_SUPPLIER_ECU_SOFTWARE_VERSION_NUMBER 0xF195
#define VDIAG                                       0xF1A0
//********************************* —onstants **********************************
 const uint16_t request_inputStateRecord [] = {INPUT_STATES_RECORD};
//********************************* Variables **********************************
union __attribute__ ((far))  {
    unsigned long long Data;
    struct 
    {
		uint8_t can_number  : 2;
        uint8_t filt_number : 4;
        uint8_t bit_mask    : 8; 
        uint16_t id         : 11;
        uint8_t data0       : 8;
        uint8_t data1       : 8;
        uint8_t data2       : 8;
        uint8_t data3       : 8;
        uint8_t data4       : 8;
        uint8_t data5       : 8; 
        uint8_t data6       : 8;
        uint8_t data7       : 8;
    } Bits;
} DIAGNOSTICS;  

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
} inputStatesRecor;

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
// Invalid Value = 0xFF, Min = -40, Max = 87, Formula - N = 0.3922 * E, Unit - ∞C
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
__attribute__ ((far)) struct vehicleCoordinates
{
    uint32_t vehicleLattitude;  // Invalid value - 0xFFFFFFFF, Min = -90, Max = 90
                                // Formula - N = (E / 3600000) - 90;
    uint32_t vehicleLongitude;  // Invalid value - 0xFFFFFFFF, Min = -180, Max = 180
                                // Formula - N = (E / 3600000) - 180;
};

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

// AutomationActivationProhibition - The prohibition of the automatic activation process
// uint8(0 bit), 0 - activation allowed, 1 - activation prhibited
uint8_t AutomationActivationProhibition = 0;

// VehicleType - The vehicle type
// 0-2 bits, 0 - M1 Passenger vehicle, 1 - M2 Autobus (<= 5 tonn), 2 - M3 Autobus (> 5 tonn),
// 3 - N1 Truck (<= 3.5 tonn), 4 - N2 Truck (> 3.5 and <= 12 tonn),
// 5 - N3 Truck (> 12 tonn), 6,7 - not used
uint8_t VehicleType = 0;

// SimIdentifier - The ICCID number of the sim-chip, ASCII
char SimIdentifier [19]; 

// CallAutoAnswerTime - The duration of the auto answer after the call from the TCM, minutes
// min = 0, max = 480, 0xFFFF - undefined
uint16_t CallAutoAnswerTime = 0;

// ECALLTestNumber - The ECALL test number
// Null terminated string, Unused characters fill with 0x00
char ECALLTestNumber [20];

// ECALLToTest - Whether the ECALL is the test number of the 112 emergency number
// 0 - ECALL is the 112 emergency number, 1 - ECALL is the test number,
// 2 - ECALL is the debug number
uint8_t ECALLToTest = 0;

// NadRegistrationTimer - The time of the deregistration from the network, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t NadRegistrationTimer = 0;

// NadRegistrationAtStartup - The time, when the TCM will be registered in the network
// uint8(0 bit), 0 - registration by call, 1 - registration at startup
uint8_t NadRegistrationAtStartup = 0;

// SMSCenterNumber - The SMS center number
// Null terminated string, Unused characters fill with 0x00
char SMSCenterNumber [20];

// SMSFallbackNumber - The SMS fallback number
// Null terminated string, Unused characters fill with 0x00
char SMSFallbackNumber [20];

// TestRegitrationPeriod - The time in minutes between next registration and end of the
// PostRegistrationTime, if "Service functions" (test call, etc.) were initialized, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t TestRegitrationPeriod = 0;

// EcallManualDialAttempts - The number of manual eCall attempts
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t EcallManualDialAttempts = 0;

// IntMemTransmitInterval - The time between tries to transmit MSD, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t IntMemTransmitInterval = 0;

// IntMemTransmitAttempts - The number of attempts to transmit MSD
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t IntMemTransmitAttempts = 0;

// GSMSoftwareVersionNumber - GSM Software version number
// Null terminated string, Unused characters fill with 0x00
char GSMSoftwareVersionNumber [10];

// SmsFallbackTestNumber - The SMS test fallback number
// Null terminated string, Unused characters fill with 0x00
char SmsFallbackTestNumber [20];

// EcallAutoDialAttempts - The number of auto eCall attempts
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t EcallAutoDialAttempts = 0;

// EcallDialDuration - The duration of ecall dial attempt, minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t EcallDialDuration = 0;

// PostTestRegistrationTime - The time in seconds of registration after the end of the
// "Service functions" (test call, etc.), minutes
// min = 0, max = 0xFFFE, 0xFFFF - undefined
uint16_t PostTestRegistrationTime = 0;

// SimProfileAmount - The number of SIM profiles
// min = 0, max = 0xFE, 0xFF - undefined
uint8_t SimProfileAmount = 0;

// Description for SimProfile - The current SIM profile and manufacturer
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

// AudioProfile - The current audio profile
// min = 0, max = 250, 251-254 - not used, 0xFF - undefined
uint8_t AudioProfile = 0;

// Description for AccelerometerRawData - Raw data from accelerometer
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
};

// RolloverAngle - Calibration angle for rollover detection, degree
// min = 0, max = 180, 0xFF - undefined
uint8_t RolloverAngle = 0;

// RolloverTime - Calibration Time for rollover detection
// Invalid Value - 0xFF, min = 0, max = 0xFE, Formule - N = E * 10
uint8_t RolloverTime = 0;

// AccelCalibrationX - Accelerometer axis data, g
// Invalid Value - 0xFFFF, min = -32768, max = 32767, Formula - N = E / 1200
uint16_t AccelCalibrationX = 0;

// AccelCalibrationY - Accelerometer axis data, g
// Invalid Value - 0xFFFF, min = -32768, max = 32767, Formula - N = E / 1200
uint16_t AccelCalibrationY = 0;

// AccelCalibrationZ - Accelerometer axis data, g
// Invalid Value - 0xFFFF, min = -32768, max = 32767, Formula - N = E / 1200
uint16_t AccelCalibrationZ = 0;

// EcallNoAutomaticTriggering
// 0x29 - prohibited, 0x92 - allowed
uint8_t EcallNoAutomaticTriggering = 0;

// MiddletState - State of GSM middlet
// 0 - not activated, 1 - wait activation, 2 - activated
uint8_t MiddletState = 0;

// SW_Version
// ASCII
char SW_Version [27];

// Vehicle_SW_Version
// ASCII
char Vehicle_SW_Version [24];

// Middlet_SW_Version
// ASCII (only 0x30 - 0x39 char)
char Middlet_SW_Version [24];

// SavedMSDAmount - The total number of saved MSDs, which were unsent
// through the inband or SMS channel
// min = 0, max = 100, 0xFF - undefined
uint8_t SavedMSDAmount = 0;

// SentMSDAmount - The total number of saved MSDs, which were are in the
// order to be sent
// min = 0, max = 100, 0xFF - undefined
uint8_t SentMSDAmount = 0;

// vehicleManufacturerSparePartNumber - Order part number reference
// ASCII
char vehicleManufacturerSparePartNumber [10];

// ConfigurationFileReferenceLink - Corresponding PDX file name (combination of
// 0xF1A0, 0xF194, 0xF195, 0xF18A). Equal to reference to a physical part, consisting
// from PCB + Boot + Application + Calibration
// ASCII
char ConfigurationFileReferenceLink [10];

// systemSupplierIdentifier - The number identifies TCM supplier
// ASCII
char systemSupplierIdentifier [3];

// ECUSerialNumber - Serial number of TCM, placed on sticker
char ECUSerialNumber [20];

// vehicleIdentificationNumber - Vehicle identification number
// ASCII
char vehicleIdentificationNumber[17]; 

// vehicleManufacturerECUHardwareNumber - This number identifies TCM hardware and bootloader
// ASCII
char vehicleManufacturerECUHardwareNumber [10];

// systemSupplierECUSoftwareNumber - Software Number of TCM
// ASCII
char systemSupplierECUSoftwareNumber [2];

// systemSupplierECUSoftwareVersionNumber - Software Version Number
// ASCII
char systemSupplierECUSoftwareVersionNumber [2];

// VDIAG - Diag Version
// min = 0, max = 0xFE, 0xFF - undefined
uint8_t VDIAG = 0;
//****************************** Functions prototype ***************************
 

#endif	/* ERA_H */


