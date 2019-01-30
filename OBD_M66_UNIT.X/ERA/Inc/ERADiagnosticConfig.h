/****************************************************/
/* (—) ŒŒŒ "À”¬", 2019                              */
/* ¿‚ÚÓ: œÂÚÓ‚ ¿ÎÂÍÒ‡Ì‰  						*/
/* ƒ‡Ú‡: 22.01.2019									*/
/* ŒÔËÒ‡ÌËÂ: ›–¿-√ÀŒÕ¿——							*/
/****************************************************/

#ifndef ERADIAGNOSTICCONFIG_H
#define	ERADIAGNOSTICCONFIG_H

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

#endif	/* ERACONFIG_H */

