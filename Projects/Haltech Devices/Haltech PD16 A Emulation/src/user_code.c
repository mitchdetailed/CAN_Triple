/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech PD16 A for configuration
 * 		Notes :
 *
 *
 */

/* File Includes */
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"
#include "snprintf.h"
#include <string.h>
#include "stm32g4xx_hal.h"

/* End File Includes */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* File Define options */

#define HALTECH_CAN CAN_1 //
#define HALTECH_PD16_A 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech PD16 A Variables

typedef enum RETRY_COUNT
{
	RETRY_NEVER = 0,
	RETRY_1X = 1,
	RETRY_2X = 2,
	RETRY_5X = 3,
	RETRY_10X = 4,
	RETRY_20X = 5,
	RETRY_30X = 6,
	RETRY_ALWAYS = 7
} RETRY_COUNT;

typedef enum DRIVE_TYPE
{
	UNDEFINED = 0,
	HIGH_SIDE = 1,
	LOW_SIDE = 2,
	BOTH_SIDES = 3
} DRIVE_TYPE;

typedef enum SAFE_STATE
{
	SAFE_STATE_INACTIVE = 0,
	SAFE_STATE_ACTIVE = 1,
	SAFE_STATE_OPEN_CIRCUIT = 2
} SAFE_STATE;

typedef enum ACTIVE_STATE
{
	ACTIVE_STATE_LOW = 0,
	ACTIVE_STATE_HIGH = 1
} ACTIVE_STATE;

typedef enum HBO_CONTROL_METHOD
{
	DUTY_CYCLE = 0,
	CURRENT = 1
} HBO_CONTROL_METHOD;

typedef enum SPI_PINMODE
{
	RELUCTOR = 0,
	HALL_EFFECT = 1,
	CUSTOM = 2
} SPI_PINMODE;

typedef enum INPUT_STARTUP_STATE
{
	INPUT_STARTUP_STATE_OFF = 0,
	INPUT_STARTUP_STATE_ON = 1,
	INPUT_STARTUP_STATE_LAST_STATE = 2
} INPUT_STARTUP_STATE;

typedef enum INPUT_MODE
{
	LATCHING = 0,
	MOMENTARY = 1
} INPUT_MODE;

typedef enum INPUT_PULLUP
{
	DISABLED = 0,
	ENABLED_1K = 1,
	ENABLED_240 = 2
} INPUT_PULLUP;

typedef enum SPI_EDGE_SELECT
{
	FALLING = 0,
	RISING = 1
} SPI_EDGE_SELECT;

typedef enum INPUT_STATE
{
	INPUT_STATE_OFF = 0,
	INPUT_STATE_ON = 1
} INPUT_STATE;

typedef enum HCO_8A_PIN_STATE
{
	OPERATIONAL = 0,
	HIGH_CURRENT = 1,
	OVER_CURRENT = 2,
	SHORT_CIRCUIT = 3,
	OPEN_CIRCUIT = 4
} HCO_8A_PIN_STATE;

typedef enum HCO_TEMP_ENUM
{
	TEMP_OK = 0,
	TEMP_WARNING_OVER_115 = 1,
	TEMP_SHUTDOWN_OVER_145 = 2
} HCO_TEMP_ENUM;

bool PD16_A_ID_Conflict = 0;
uint8_t PD16_A_Status = 1;
uint8_t PD16_A_FW_Major_Version = 3;
uint8_t PD16_A_Bootcode_Version = 0;
uint8_t PD16_A_FW_Minor_Version = 255;
uint8_t PD16_A_Firmware_Bugfix_Version = 0;
uint8_t PD16_A_FW_Release_Type = 0;
uint8_t PD16_A_IgnitionSwitchStatus = 1;
uint16_t PD16_A_Main_Rail_Voltage_mV = 12000;
uint16_t PD16_A_Protected_Rail_Voltage_mV = 12000;
uint16_t PD16_A_ECR_Plug_Voltage_mV = 12000;
uint16_t PD16_A_Boost_Voltage_mV = 22000;
uint16_t PD16_A_SEPIC_Voltage_mV = 12000;
uint16_t PD16_A_ECR_Plug_Current_mA = 12000;
uint16_t PD16_A_UVLO_Voltage_mV = 3300;
uint16_t PD16_A_SensorGround_Voltage_mV = 12000;
uint16_t PD16_A_VDD_Voltage_mV = 12000;
uint8_t PD16_A_Main_Rail_Temp_C = 20;
uint8_t PD16_A_Thermistor1_Temp_C = 20;
uint8_t PD16_A_Thermistor2_Temp_C = 20;
uint8_t PD16_A_Thermistor3_Temp_C = 20;
uint8_t PD16_A_CPU_Temp_C = 20;
float PD16_A_Total_Current_Amps = 0;
uint16_t PD16_A_Battery_Voltage_mV = 12000;
uint16_t PD16_A_OnTime = 0;
HCO_TEMP_ENUM HCO3_HCO4_Temp_enum = TEMP_OK;
HCO_TEMP_ENUM HCO1_HCO2_Temp_enum = TEMP_OK;
HCO_TEMP_ENUM TVS_Temp_enum = TEMP_OK;
HCO_TEMP_ENUM Main_Rail_Temp_enum = TEMP_OK;
uint8_t PD16_A_SerialNumber[12] = {0, 1, 2, 8, 1, 3, 3, 0, 8, 0, 0, 4}; // Hit Mike Jones up on the low cause Mike Jones about to blow...

// 25a HCO 1-4
float PD16_A_25a_HCO1_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_25a_HCO1_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_25a_HCO1_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_25a_HCO1_DriveType = UNDEFINED;
SAFE_STATE PD16_A_25a_HCO1_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_25a_HCO1_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_25a_HCO1_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_25a_HCO1_FuseCurrent = 0.0f;
float PD16_A_25a_HCO1_SoftStartCurrent = 0.0f;
float PD16_A_25a_HCO1_SoftStartDuration = 0.0f;	  // 0 - 2.5 seconds
uint8_t PD16_A_25a_HCO1_Load = 0;				  // 0 - 100 %
uint16_t PD16_A_25a_HCO1_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO1_LowSide_Current_mA = 0;  // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO1_HighSide_Current_mA = 0; // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //

float PD16_A_25a_HCO2_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_25a_HCO2_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_25a_HCO2_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_25a_HCO2_DriveType = UNDEFINED;
SAFE_STATE PD16_A_25a_HCO2_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_25a_HCO2_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_25a_HCO2_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_25a_HCO2_FuseCurrent = 0.0f;
float PD16_A_25a_HCO2_SoftStartCurrent = 0.0f;
float PD16_A_25a_HCO2_SoftStartDuration = 0.0f;	  // 0 - 2.5 seconds
uint8_t PD16_A_25a_HCO2_Load = 0;				  // 0 - 100 %
uint16_t PD16_A_25a_HCO2_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO2_LowSide_Current_mA = 0;  // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO2_HighSide_Current_mA = 0; // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //

float PD16_A_25a_HCO3_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_25a_HCO3_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_25a_HCO3_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_25a_HCO3_DriveType = UNDEFINED;
SAFE_STATE PD16_A_25a_HCO3_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_25a_HCO3_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_25a_HCO3_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_25a_HCO3_FuseCurrent = 0.0f;
float PD16_A_25a_HCO3_SoftStartCurrent = 0.0f;
float PD16_A_25a_HCO3_SoftStartDuration = 0.0f;	  // 0 - 2.5 seconds
uint8_t PD16_A_25a_HCO3_Load = 0;				  // 0 - 100 %
uint16_t PD16_A_25a_HCO3_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO3_LowSide_Current_mA = 0;  // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO3_HighSide_Current_mA = 0; // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //

float PD16_A_25a_HCO4_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_25a_HCO4_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_25a_HCO4_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_25a_HCO4_DriveType = UNDEFINED;
SAFE_STATE PD16_A_25a_HCO4_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_25a_HCO4_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_25a_HCO4_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_25a_HCO4_FuseCurrent = 0.0f;
float PD16_A_25a_HCO4_SoftStartCurrent = 0.0f;
float PD16_A_25a_HCO4_SoftStartDuration = 0.0f;	  // 0 - 2.5 seconds
uint8_t PD16_A_25a_HCO4_Load = 0;				  // 0 - 100 %
uint16_t PD16_A_25a_HCO4_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO4_LowSide_Current_mA = 0;  // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //
uint16_t PD16_A_25a_HCO4_HighSide_Current_mA = 0; // 0 - 50000 mA, 100mA Resolution, 10Hz CAN Tx //

// 8a HCO 1-10
float PD16_A_8a_HCO1_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO1_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO1_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO1_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO1_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO1_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO1_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO1_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO1_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO1_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO1_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx // // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO1_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO1_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO2_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO2_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO2_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO2_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO2_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO2_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO2_RetryDelay = 0;	 // 0 - 240 Seconds
float PD16_A_8a_HCO2_FuseCurrent = 0.0f; // 0 - 30000 mV, 10mV resolution, 5Hz CAN Tx //
uint8_t PD16_A_8a_HCO2_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO2_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO2_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO2_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO2_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO3_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO3_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO3_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO3_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO3_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO3_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO3_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO3_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO3_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO3_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO3_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO3_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO3_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO4_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO4_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO4_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO4_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO4_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO4_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO4_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO4_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO4_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO4_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO4_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO4_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO4_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO5_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO5_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO5_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO5_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO5_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO5_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO5_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO5_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO5_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO5_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO5_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO5_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO5_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO6_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO6_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO6_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO6_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO6_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO6_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO6_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO6_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO6_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO6_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO6_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO6_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO6_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO7_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO7_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO7_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO7_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO7_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO7_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO7_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO7_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO7_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO7_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO7_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO7_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO7_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO8_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO8_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO8_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO8_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO8_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO8_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO8_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO8_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO8_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO8_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO8_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO8_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO8_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO9_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO9_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO9_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO9_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO9_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO9_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO9_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO9_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO9_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO9_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO9_Voltage_mV = 0;			 // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO9_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO9_Load = 0;				 // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

float PD16_A_8a_HCO10_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_8a_HCO10_FrequencyHz_cmd = 0;
RETRY_COUNT PD16_A_8a_HCO10_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_8a_HCO10_DriveType = UNDEFINED;
SAFE_STATE PD16_A_8a_HCO10_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_8a_HCO10_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_8a_HCO10_RetryDelay = 0; // 0 - 240 Seconds
float PD16_A_8a_HCO10_FuseCurrent = 0.0f;
uint8_t PD16_A_8a_HCO10_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_8a_HCO10_PinState = OPERATIONAL;
uint16_t PD16_A_8a_HCO10_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_8a_HCO10_HighSide_Current_mA = 0; // 0 - 20000 mA, 100mA Resolution, 10Hz CAN Tx //
uint8_t PD16_A_8a_HCO10_Load = 0;				  // 0 - 100 %, 1% resolution, 10Hz CAN Tx //

// HBO 1-2
float PD16_A_HBO1_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_HBO1_FrequencyHz_cmd = 0;
uint16_t PD16_A_HBO1_TargetCurrent_mA = 0;
RETRY_COUNT PD16_A_HBO1_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_HBO1_DriveType = UNDEFINED;
SAFE_STATE PD16_A_HBO1_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_HBO1_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_HBO1_RetryDelay = 0; // 0 - 240 Seconds
HBO_CONTROL_METHOD PD16_A_HBO1_ControlMethod = CURRENT;
float PD16_A_HBO1_FuseCurrent = 0.0f;
uint8_t PD16_A_HBO1_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_HBO1_PinState = OPERATIONAL;
uint16_t PD16_A_HBO1_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_HBO1_LowSide_Current_mA = 0;  // 0 - 50000 mA, 1mA Resolution, 10Hz CAN Tx //
uint16_t PD16_A_HBO1_HighSide_Current_mA = 0; // 0 - 50000 mA, 1mA Resolution, 10Hz CAN Tx //

float PD16_A_HBO2_DutyCycle_cmd = 0.0f; // 0 - 100 %, 0.1% resolution,  10Hz Rx max //
uint16_t PD16_A_HBO2_FrequencyHz_cmd = 0;
uint16_t PD16_A_HBO2_TargetCurrent_mA = 0;
RETRY_COUNT PD16_A_HBO2_RetryCount = RETRY_NEVER;
DRIVE_TYPE PD16_A_HBO2_DriveType = UNDEFINED;
SAFE_STATE PD16_A_HBO2_SafeState = SAFE_STATE_INACTIVE;
ACTIVE_STATE PD16_A_HBO2_ActiveState = ACTIVE_STATE_HIGH;
uint8_t PD16_A_HBO2_RetryDelay = 0; // 0 - 240 Seconds
HBO_CONTROL_METHOD PD16_A_HBO2_ControlMethod = CURRENT;
float PD16_A_HBO2_FuseCurrent = 0.0f;
uint8_t PD16_A_HBO2_Total_Retries = 0;
HCO_8A_PIN_STATE PD16_A_HBO2_PinState = OPERATIONAL;
uint16_t PD16_A_HBO2_Voltage_mV = 0;		  // 0 - 30000 mV, 10mV resolution, 10Hz CAN Tx //
uint16_t PD16_A_HBO2_LowSide_Current_mA = 0;  // 0 - 50000 mA, 1mA Resolution, 10Hz CAN Tx //
uint16_t PD16_A_HBO2_HighSide_Current_mA = 0; // 0 - 50000 mA, 1mA Resolution, 10Hz CAN Tx //

// SPI 1-4
SPI_PINMODE PD16_A_SPI1_PinMode = RELUCTOR;								// Receive only, 2Hz//
INPUT_STARTUP_STATE PD16_A_SPI1_StartupState = INPUT_STARTUP_STATE_OFF; // Receive only, 2Hz//
INPUT_MODE PD16_A_SPI1_PinState = LATCHING;								// Receive only, 2Hz//
INPUT_PULLUP PD16_A_SPI1_Pullup = DISABLED;								// Receive only, 2Hz//
SPI_EDGE_SELECT PD16_A_SPI1_EdgeSelect = FALLING;						// Receive only, 2Hz//
uint16_t PD16_A_SPI1_UpperThreshold_mV = 2500;							// Receive only, 2Hz//
uint16_t PD16_A_SPI1_GlitchFilter_uS = 12;								// Receive only, 2Hz//
INPUT_STATE PD16_A_SPI1_State = INPUT_STATE_ON;							// 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_SPI1_mV = 0;											// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI1_DutyCycle = 0.0f;										// 0.0 to 100.0%, 0.1 resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI1_Frequency = 0.0f;										// 0 to 16000 Hz, 1Hz resolution 100Hz Tx Rate//

SPI_PINMODE PD16_A_SPI2_PinMode = RELUCTOR;								// Receive only, 2Hz//
INPUT_STARTUP_STATE PD16_A_SPI2_StartupState = INPUT_STARTUP_STATE_OFF; // Receive only, 2Hz//
INPUT_MODE PD16_A_SPI2_PinState = LATCHING;								// Receive only, 2Hz//
INPUT_PULLUP PD16_A_SPI2_Pullup = DISABLED;								// Receive only, 2Hz//
SPI_EDGE_SELECT PD16_A_SPI2_EdgeSelect = FALLING;						// Receive only, 2Hz//
uint16_t PD16_A_SPI2_UpperThreshold_mV = 2500;							// Receive only, 2Hz//
uint16_t PD16_A_SPI2_GlitchFilter_uS = 12;								// Receive only, 2Hz//
INPUT_STATE PD16_A_SPI2_State = INPUT_STATE_ON;							// 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_SPI2_mV = 0;											// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI2_DutyCycle = 0.0f;										// 0.0 to 100.0%, 0.1 resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI2_Frequency = 0.0f;										// 0 to 16000 Hz, 1Hz resolution 100Hz Tx Rate//

SPI_PINMODE PD16_A_SPI3_PinMode = RELUCTOR;								// Receive only, 2Hz//
INPUT_STARTUP_STATE PD16_A_SPI3_StartupState = INPUT_STARTUP_STATE_OFF; // Receive only, 2Hz//
INPUT_MODE PD16_A_SPI3_PinState = LATCHING;								// Receive only, 2Hz//
INPUT_PULLUP PD16_A_SPI3_Pullup = DISABLED;								// Receive only, 2Hz//
SPI_EDGE_SELECT PD16_A_SPI3_EdgeSelect = FALLING;						// Receive only, 2Hz//
uint16_t PD16_A_SPI3_UpperThreshold_mV = 2500;							// Receive only, 2Hz//
uint16_t PD16_A_SPI3_GlitchFilter_uS = 12;								// Receive only, 2Hz//
INPUT_STATE PD16_A_SPI3_State = INPUT_STATE_ON;							// 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_SPI3_mV = 0;											// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI3_DutyCycle = 0.0f;										// 0.0 to 100.0%, 0.1 resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI3_Frequency = 0.0f;										// 0 to 16000 Hz, 1Hz resolution 100Hz Tx Rate//

SPI_PINMODE PD16_A_SPI4_PinMode = RELUCTOR;								// Receive only, 2Hz//
INPUT_STARTUP_STATE PD16_A_SPI4_StartupState = INPUT_STARTUP_STATE_OFF; // Receive only, 2Hz//
INPUT_MODE PD16_A_SPI4_PinState = LATCHING;								// Receive only, 2Hz//
INPUT_PULLUP PD16_A_SPI4_Pullup = DISABLED;								// Receive only, 2Hz//
SPI_EDGE_SELECT PD16_A_SPI4_EdgeSelect = FALLING;						// Receive only, 2Hz//
uint16_t PD16_A_SPI4_UpperThreshold_mV = 2500;							// Receive only, 2Hz//
uint16_t PD16_A_SPI4_GlitchFilter_uS = 12;								// Receive only, 2Hz//
INPUT_STATE PD16_A_SPI4_State = INPUT_STATE_ON;							// 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_SPI4_mV = 0;											// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI4_DutyCycle = 0.0f;										// 0.0 to 100.0%, 0.1 resolution, 100Hz CAN Tx Rate//
float PD16_A_SPI4_Frequency = 0.0f;										// 0 to 16000 Hz, 1Hz resolution 100Hz Tx Rate//

// AVI 1-4
INPUT_PULLUP PD16_A_AVI1_Pullup = DISABLED;		// Receive only, 2Hz//
uint16_t PD16_A_AVI1_OnThreshold_mV = 2000;		// Receive only, 2Hz//
uint16_t PD16_A_AVI1_OffThreshold_mV = 1000;	// Receive only, 2Hz//
INPUT_STATE PD16_A_AVI1_State = INPUT_STATE_ON; // 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_AVI1_mV = 0;					// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//

INPUT_PULLUP PD16_A_AVI2_Pullup = DISABLED;		// Receive only, 2Hz//
uint16_t PD16_A_AVI2_OnThreshold_mV = 2000;		// Receive only, 2Hz//
uint16_t PD16_A_AVI2_OffThreshold_mV = 1000;	// Receive only, 2Hz//
INPUT_STATE PD16_A_AVI2_State = INPUT_STATE_ON; // 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_AVI2_mV = 0;					// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//

INPUT_PULLUP PD16_A_AVI3_Pullup = DISABLED;		// Receive only, 2Hz//
uint16_t PD16_A_AVI3_OnThreshold_mV = 2000;		// Receive only, 2Hz//
uint16_t PD16_A_AVI3_OffThreshold_mV = 1000;	// Receive only, 2Hz//
INPUT_STATE PD16_A_AVI3_State = INPUT_STATE_ON; // 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_AVI3_mV = 0;					// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//

INPUT_PULLUP PD16_A_AVI4_Pullup = DISABLED;		// Receive only, 2Hz//
uint16_t PD16_A_AVI4_OnThreshold_mV = 2000;		// Receive only, 2Hz//
uint16_t PD16_A_AVI4_OffThreshold_mV = 1000;	// Receive only, 2Hz//
INPUT_STATE PD16_A_AVI4_State = INPUT_STATE_ON; // 0 - 1, 100Hz CAN Tx Rate//
uint16_t PD16_A_AVI4_mV = 0;					// 0 - 5000 mV, 10mV resolution, 100Hz CAN Tx Rate//

uint8_t PD16_A_ECR_Status = 0;
uint8_t PD16_A_CAN_Power = 0;
uint8_t PD16_A_CAN_Termination = 0;

// Haltech PD16 A Multiplezer Declarations //
uint8_t multiplexer_0x6D0 = 0;
uint8_t multiplexer_0x6D1 = 0;

// Message declarations //
// PD16_A Base Address 0x6D0 //

uint8_t msg_HT_PD16_A_0x6D3[8];
uint8_t msg_HT_PD16_A_0x6D4[8];
uint8_t msg_HT_PD16_A_0x6D5[8];
uint8_t msg_HT_PD16_A_0x6D6[8];

// High Speed CAN Output Messages //
uint8_t msg_HT_PD16_A_0x320[8];
uint8_t msg_HT_PD16_A_0x324[8];
uint8_t msg_HT_PD16_A_0x328[8];

uint16_t dutycycleoutput;
uint8_t total_retries;

// End Haltech PD16 A variables

/* End Variable Declarations */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Startup Functions */

void events_Startup()
{
	setupCANbus(CAN_1, 1000000, NORMAL_MODE); // Set up as Haltech CAN Bus
	setupCANbus(CAN_2, 1000000, NORMAL_MODE);
	setupCANbus(CAN_3, 1000000, NORMAL_MODE);
	setCAN_Termination(CAN_1, true);
	setCAN_Termination(CAN_2, true);
	setCAN_Termination(CAN_3, true);
	startCANbus(CAN_1);
	startCANbus(CAN_2);
	startCANbus(CAN_3);
}

/* End Startup Functions */

//-----------------------------//
//-----------------------------//
//-----------------------------//

void onSerialReceive(uint8_t *serialMessage)
{
	// What do you want to do when you receive a UART message.. ?
	// printf("%07.4f message received...\r\n",getTimestamp());
}

void onReceive(CAN_Message Message)
{
	// What do you want to do when you receive a CAN message.. ?
	if (Message.Bus == CAN_1)
	{
		if (HALTECH_CAN == CAN_1)
		{
			if (Message.arbitration_id == 0x6D0)
			{
				multiplexer_0x6D0 = Message.data[0];
				if (multiplexer_0x6D0 == 0x00)
				{
					PD16_A_25a_HCO1_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_25a_HCO1_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x01)
				{
					PD16_A_25a_HCO2_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_25a_HCO2_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x02)
				{
					PD16_A_25a_HCO3_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_25a_HCO3_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x03)
				{
					PD16_A_25a_HCO4_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_25a_HCO4_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x20)
				{
					PD16_A_8a_HCO1_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO1_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
					printf("PD16_A_8a_HCO1_DutyCycle_cmd: %1.1f\r\n", PD16_A_8a_HCO1_DutyCycle_cmd);
				}
				else if (multiplexer_0x6D0 == 0x21)
				{
					PD16_A_8a_HCO2_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO2_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x22)
				{
					PD16_A_8a_HCO3_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO3_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x23)
				{
					PD16_A_8a_HCO4_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO4_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x24)
				{
					PD16_A_8a_HCO5_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO5_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x25)
				{
					PD16_A_8a_HCO6_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO6_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x26)
				{
					PD16_A_8a_HCO7_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO7_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x27)
				{
					PD16_A_8a_HCO8_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO8_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x28)
				{
					PD16_A_8a_HCO9_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO9_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x29)
				{
					PD16_A_8a_HCO10_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_8a_HCO10_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
				else if (multiplexer_0x6D0 == 0x40)
				{
					PD16_A_HBO1_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_HBO1_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
					printf("PD16_A_HBO1_DutyCycle_cmd: %1.1f\r\n", PD16_A_HBO1_DutyCycle_cmd);
				}
				else if (multiplexer_0x6D0 == 0x41)
				{
					PD16_A_HBO2_DutyCycle_cmd = (float)(((Message.data[1] << 8) + Message.data[2]) * 0.1);
					PD16_A_HBO2_FrequencyHz_cmd = ((Message.data[3] << 8) + Message.data[4]);
				}
			}
			else if (Message.arbitration_id == 0x6D1)
			{
				multiplexer_0x6D1 = Message.data[0];
				if (multiplexer_0x6D1 == 0x00)
				{
					PD16_A_25a_HCO1_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_25a_HCO1_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_25a_HCO1_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_25a_HCO1_ActiveState = (Message.data[1] & 0x01);
					PD16_A_25a_HCO1_RetryDelay = Message.data[2];
					PD16_A_25a_HCO1_FuseCurrent = (float)((Message.data[3]) * 0.2);
					PD16_A_25a_HCO1_SoftStartCurrent = (float)((Message.data[4]) * 0.2);
					PD16_A_25a_HCO1_SoftStartDuration = (float)((Message.data[5]) * 0.1);
				}
				else if (multiplexer_0x6D1 == 0x01)
				{
					PD16_A_25a_HCO2_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_25a_HCO2_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_25a_HCO2_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_25a_HCO2_ActiveState = (Message.data[1] & 0x01);
					PD16_A_25a_HCO2_RetryDelay = Message.data[2];
					PD16_A_25a_HCO2_FuseCurrent = (float)((Message.data[3]) * 0.2);
					PD16_A_25a_HCO2_SoftStartCurrent = (float)((Message.data[4]) * 0.2);
					PD16_A_25a_HCO2_SoftStartDuration = (float)((Message.data[5]) * 0.1);
				}
				else if (multiplexer_0x6D1 == 0x02)
				{
					PD16_A_25a_HCO3_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_25a_HCO3_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_25a_HCO3_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_25a_HCO3_ActiveState = (Message.data[1] & 0x01);
					PD16_A_25a_HCO3_RetryDelay = Message.data[2];
					PD16_A_25a_HCO3_FuseCurrent = (float)((Message.data[3]) * 0.2);
					PD16_A_25a_HCO3_SoftStartCurrent = (float)((Message.data[4]) * 0.2);
					PD16_A_25a_HCO3_SoftStartDuration = (float)((Message.data[5]) * 0.1);
				}
				else if (multiplexer_0x6D1 == 0x03)
				{
					PD16_A_25a_HCO4_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_25a_HCO4_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_25a_HCO4_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_25a_HCO4_ActiveState = (Message.data[1] & 0x01);
					PD16_A_25a_HCO4_RetryDelay = Message.data[2];
					PD16_A_25a_HCO4_FuseCurrent = (float)((Message.data[3]) * 0.2);
					PD16_A_25a_HCO4_SoftStartCurrent = (float)((Message.data[4]) * 0.2);
					PD16_A_25a_HCO4_SoftStartDuration = (float)((Message.data[5]) * 0.1);
				}
				else if (multiplexer_0x6D1 == 0x20)
				{
					PD16_A_8a_HCO1_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO1_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO1_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO1_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO1_RetryDelay = Message.data[2];
					PD16_A_8a_HCO1_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x21)
				{
					PD16_A_8a_HCO2_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO2_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO2_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO2_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO2_RetryDelay = Message.data[2];
					PD16_A_8a_HCO2_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x22)
				{
					PD16_A_8a_HCO3_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO3_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO3_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO3_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO3_RetryDelay = Message.data[2];
					PD16_A_8a_HCO3_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x23)
				{
					PD16_A_8a_HCO4_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO4_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO4_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO4_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO4_RetryDelay = Message.data[2];
					PD16_A_8a_HCO4_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x24)
				{
					PD16_A_8a_HCO5_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO5_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO5_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO5_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO5_RetryDelay = Message.data[2];
					PD16_A_8a_HCO5_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x25)
				{
					PD16_A_8a_HCO6_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO6_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO6_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO6_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO6_RetryDelay = Message.data[2];
					PD16_A_8a_HCO6_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x26)
				{
					PD16_A_8a_HCO7_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO7_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO7_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO7_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO7_RetryDelay = Message.data[2];
					PD16_A_8a_HCO7_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x27)
				{
					PD16_A_8a_HCO8_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO8_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO8_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO8_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO8_RetryDelay = Message.data[2];
					PD16_A_8a_HCO8_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x28)
				{
					PD16_A_8a_HCO9_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO9_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO9_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO9_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO9_RetryDelay = Message.data[2];
					PD16_A_8a_HCO9_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x29)
				{
					PD16_A_8a_HCO10_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_8a_HCO10_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_8a_HCO10_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_8a_HCO10_ActiveState = (Message.data[1] & 0x01);
					PD16_A_8a_HCO10_RetryDelay = Message.data[2];
					PD16_A_8a_HCO10_FuseCurrent = (float)((Message.data[3]) * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x40)
				{
					PD16_A_HBO1_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_HBO1_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_HBO1_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_HBO1_ActiveState = (Message.data[1] & 0x01);
					PD16_A_HBO1_RetryDelay = Message.data[2];
					PD16_A_HBO1_ControlMethod = (Message.data[3] & 0x01);
					PD16_A_HBO1_FuseCurrent = (Message.data[4] * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x41)
				{
					PD16_A_HBO2_RetryCount = ((Message.data[1] & 0xE0) >> 5);
					PD16_A_HBO2_DriveType = ((Message.data[1] & 0x18) >> 3);
					PD16_A_HBO2_SafeState = ((Message.data[1] & 0x06) >> 1);
					PD16_A_HBO2_ActiveState = (Message.data[1] & 0x01);
					PD16_A_HBO2_RetryDelay = Message.data[2];
					PD16_A_HBO2_ControlMethod = (Message.data[3] & 0x01);
					PD16_A_HBO2_FuseCurrent = (Message.data[4] * 0.2);
				}
				else if (multiplexer_0x6D1 == 0x60)
				{
					PD16_A_SPI1_PinMode = ((Message.data[1] & 0xC0) >> 6);
					PD16_A_SPI1_Pullup = ((Message.data[1] & 0x02) >> 1);
					PD16_A_SPI1_EdgeSelect = (Message.data[1] & 0x01);
					PD16_A_SPI1_UpperThreshold_mV = (uint16_t)((Message.data[4] << 8) + Message.data[5]);
					PD16_A_SPI1_GlitchFilter_uS = (uint16_t)((Message.data[6] << 8) + Message.data[7]);
				}
				else if (multiplexer_0x6D1 == 0x61)
				{
					PD16_A_SPI2_PinMode = ((Message.data[1] & 0xC0) >> 6);
					PD16_A_SPI2_Pullup = ((Message.data[1] & 0x02) >> 1);
					PD16_A_SPI2_EdgeSelect = (Message.data[1] & 0x01);
					PD16_A_SPI2_UpperThreshold_mV = (uint16_t)((Message.data[4] << 8) + Message.data[5]);
					PD16_A_SPI2_GlitchFilter_uS = (uint16_t)((Message.data[6] << 8) + Message.data[7]);
				}
				else if (multiplexer_0x6D1 == 0x62)
				{
					PD16_A_SPI3_PinMode = ((Message.data[1] & 0xC0) >> 6);
					PD16_A_SPI3_Pullup = ((Message.data[1] & 0x02) >> 1);
					PD16_A_SPI3_EdgeSelect = (Message.data[1] & 0x01);
					PD16_A_SPI3_UpperThreshold_mV = (uint16_t)((Message.data[4] << 8) + Message.data[5]);
					PD16_A_SPI3_GlitchFilter_uS = (uint16_t)((Message.data[6] << 8) + Message.data[7]);
				}
				else if (multiplexer_0x6D1 == 0x63)
				{
					PD16_A_SPI4_PinMode = ((Message.data[1] & 0xC0) >> 6);
					PD16_A_SPI4_Pullup = ((Message.data[1] & 0x02) >> 1);
					PD16_A_SPI4_EdgeSelect = (Message.data[1] & 0x01);
					PD16_A_SPI4_UpperThreshold_mV = (uint16_t)((Message.data[4] << 8) + Message.data[5]);
					PD16_A_SPI4_GlitchFilter_uS = (uint16_t)((Message.data[6] << 8) + Message.data[7]);
				}
				else if (multiplexer_0x6D1 == 0x80)
				{
					PD16_A_AVI1_Pullup = (Message.data[1] & 0x07);
					PD16_A_AVI1_OnThreshold_mV = (uint16_t)(Message.data[2] << 8) + (Message.data[3]);
					PD16_A_AVI1_OffThreshold_mV = (uint16_t)(Message.data[4] << 8) + (Message.data[5]);
				}
				else if (multiplexer_0x6D1 == 0x81)
				{
					PD16_A_AVI2_Pullup = (Message.data[1] & 0x07);
					PD16_A_AVI2_OnThreshold_mV = (uint16_t)(Message.data[2] << 8) + (Message.data[3]);
					PD16_A_AVI2_OffThreshold_mV = (uint16_t)(Message.data[4] << 8) + (Message.data[5]);
				}
				else if (multiplexer_0x6D1 == 0x82)
				{
					PD16_A_AVI3_Pullup = (Message.data[1] & 0x07);
					PD16_A_AVI3_OnThreshold_mV = (uint16_t)(Message.data[2] << 8) + (Message.data[3]);
					PD16_A_AVI3_OffThreshold_mV = (uint16_t)(Message.data[4] << 8) + (Message.data[5]);
				}
				else if (multiplexer_0x6D1 == 0x83)
				{
					PD16_A_AVI4_Pullup = (Message.data[1] & 0x07);
					PD16_A_AVI4_OnThreshold_mV = (uint16_t)(Message.data[2] << 8) + (Message.data[3]);
					PD16_A_AVI4_OffThreshold_mV = (uint16_t)(Message.data[4] << 8) + (Message.data[5]);
				}
			}
			else if (Message.arbitration_id == 0x6D2)
			{
				PD16_A_ECR_Status = ((Message.data[0] & 0x10) >> 4);
				PD16_A_CAN_Power = ((Message.data[0] & 0x08) >> 3);
				PD16_A_CAN_Termination = ((Message.data[0] & 0x02) >> 1);
			}
		}
	}
	else if (Message.Bus == CAN_2)
	{
	}
	else if (Message.Bus == CAN_3)
	{
	}
}

/* Run 2000Hz Functions here */
void events_2000Hz()
{
}

/* Run 1000Hz Functions here */
void events_1000Hz()
{
}

/* Run 500Hz Functions here */
void events_500Hz()
{
}

/* Run 200Hz Functions here */
void events_200Hz()
{
}

/* Run 100Hz Functions here */
void events_100Hz()
{
	if (HALTECH_PD16_A == 1)
	{
		// setup AVI1 Message at 0x320 arb id
		msg_HT_PD16_A_0x320[0] = (uint8_t)((PD16_A_AVI1_State << 7) | (uint8_t)(PD16_A_AVI1_mV >> 8));
		msg_HT_PD16_A_0x320[1] = (uint8_t)(PD16_A_AVI1_mV);
		msg_HT_PD16_A_0x320[2] = (uint8_t)((PD16_A_AVI2_State << 7) | (uint8_t)(PD16_A_AVI2_mV >> 8));
		msg_HT_PD16_A_0x320[3] = (uint8_t)(PD16_A_AVI2_mV);
		msg_HT_PD16_A_0x320[4] = (uint8_t)((PD16_A_AVI3_State << 7) | (uint8_t)(PD16_A_AVI3_mV >> 8));
		msg_HT_PD16_A_0x320[5] = (uint8_t)(PD16_A_AVI3_mV);
		msg_HT_PD16_A_0x320[6] = (uint8_t)((PD16_A_AVI4_State << 7) | (uint8_t)(PD16_A_AVI4_mV >> 8));
		msg_HT_PD16_A_0x320[7] = (uint8_t)(PD16_A_AVI4_mV);
		send_message(HALTECH_CAN, false, 0x320, 8, msg_HT_PD16_A_0x320);

		// setup SPI1 Message at 0x324 arb id
		msg_HT_PD16_A_0x324[0] = (uint8_t)((PD16_A_SPI1_State << 7) | (uint8_t)(PD16_A_SPI1_mV >> 8));
		msg_HT_PD16_A_0x324[1] = (uint8_t)(PD16_A_SPI1_mV);
		msg_HT_PD16_A_0x324[2] = (uint8_t)((PD16_A_SPI2_State << 7) | (uint8_t)(PD16_A_SPI2_mV >> 8));
		msg_HT_PD16_A_0x324[3] = (uint8_t)(PD16_A_SPI2_mV);
		msg_HT_PD16_A_0x324[4] = (uint8_t)((PD16_A_SPI3_State << 7) | (uint8_t)(PD16_A_SPI3_mV >> 8));
		msg_HT_PD16_A_0x324[5] = (uint8_t)(PD16_A_SPI3_mV);
		msg_HT_PD16_A_0x324[6] = (uint8_t)((PD16_A_SPI4_State << 7) | (uint8_t)(PD16_A_SPI4_mV >> 8));
		msg_HT_PD16_A_0x324[7] = (uint8_t)(PD16_A_SPI4_mV);
		send_message(HALTECH_CAN, false, 0x324, 8, msg_HT_PD16_A_0x324);

		// setup SPI Frequencies Message at 0x328 arb id
		msg_HT_PD16_A_0x328[0] = (uint8_t)((uint16_t)(PD16_A_SPI1_Frequency * 4) >> 8);
		msg_HT_PD16_A_0x328[1] = (uint8_t)((uint16_t)(PD16_A_SPI1_Frequency * 4));
		msg_HT_PD16_A_0x328[2] = (uint8_t)((uint16_t)(PD16_A_SPI2_Frequency * 4) >> 8);
		msg_HT_PD16_A_0x328[3] = (uint8_t)((uint16_t)(PD16_A_SPI2_Frequency * 4));
		msg_HT_PD16_A_0x328[4] = (uint8_t)((uint16_t)(PD16_A_SPI3_Frequency * 4) >> 8);
		msg_HT_PD16_A_0x328[5] = (uint8_t)((uint16_t)(PD16_A_SPI3_Frequency * 4));
		msg_HT_PD16_A_0x328[6] = (uint8_t)((uint16_t)(PD16_A_SPI4_Frequency * 4) >> 8);
		msg_HT_PD16_A_0x328[7] = (uint8_t)((uint16_t)(PD16_A_SPI4_Frequency * 4));
		send_message(HALTECH_CAN, false, 0x328, 8, msg_HT_PD16_A_0x328);
	}
}

/* Run 50Hz Functions here */
void events_50Hz()
{
	// demo functions

	PD16_A_SPI1_mV += 10;
	if (PD16_A_SPI1_mV > 5000)
	{
		PD16_A_SPI1_mV = 0;
	}

	PD16_A_SPI2_mV += 10;
	if (PD16_A_SPI2_mV > 5000)
	{
		PD16_A_SPI2_mV = 0;
	}

	PD16_A_SPI3_mV += 10;
	if (PD16_A_SPI3_mV > 5000)
	{
		PD16_A_SPI3_mV = 0;
	}

	PD16_A_SPI4_mV += 10;
	if (PD16_A_SPI4_mV > 5000)
	{
		PD16_A_SPI4_mV = 0;
	}
	PD16_A_SPI1_DutyCycle += 0.1f;
	if (PD16_A_SPI1_DutyCycle > 100.0f)
	{
		PD16_A_SPI1_DutyCycle = 0.0f;
	}

	PD16_A_SPI2_DutyCycle += 0.1f;
	if (PD16_A_SPI2_DutyCycle > 100.0f)
	{
		PD16_A_SPI2_DutyCycle = 0.0f;
	}

	PD16_A_SPI3_DutyCycle += 0.1f;
	if (PD16_A_SPI3_DutyCycle > 100.0f)
	{
		PD16_A_SPI3_DutyCycle = 0.0f;
	}

	PD16_A_SPI4_DutyCycle += 0.1f;
	if (PD16_A_SPI4_DutyCycle > 100.0f)
	{
		PD16_A_SPI4_DutyCycle = 0.0f;
	}

	PD16_A_SPI1_Frequency += 5;
	if (PD16_A_SPI1_Frequency > 16000)
	{
		PD16_A_SPI1_Frequency = 0;
	}

	PD16_A_SPI2_Frequency += 5;
	if (PD16_A_SPI2_Frequency > 16000)
	{
		PD16_A_SPI2_Frequency = 0;
	}

	PD16_A_SPI3_Frequency += 5;
	if (PD16_A_SPI3_Frequency > 16000)
	{
		PD16_A_SPI3_Frequency = 0;
	}

	PD16_A_SPI4_Frequency += 5;
	if (PD16_A_SPI4_Frequency > 16000)
	{
		PD16_A_SPI4_Frequency = 0;
	}

	PD16_A_AVI1_mV += 1;
	if (PD16_A_AVI1_mV > 5000)
	{
		PD16_A_AVI1_mV = 0;
	}

	PD16_A_AVI2_mV += 1;
	if (PD16_A_AVI2_mV > 5000)
	{
		PD16_A_AVI2_mV = 0;
	}

	PD16_A_AVI3_mV += 1;
	if (PD16_A_AVI3_mV > 5000)
	{
		PD16_A_AVI3_mV = 0;
	}

	PD16_A_AVI4_mV += 1;
	if (PD16_A_AVI4_mV > 5000)
	{
		PD16_A_AVI4_mV = 0;
	}
	// END DEMO FUNCTIONS
}

/* Run 20Hz Functions here */
void events_20Hz()
{
	if (HALTECH_PD16_A == 1)
	{
		// setup SPI1 Message
		msg_HT_PD16_A_0x6D3[0] = 0x60;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_SPI1_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_SPI1_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_SPI1_mV);
		dutycycleoutput = (uint16_t)(PD16_A_SPI1_DutyCycle * 10);
		msg_HT_PD16_A_0x6D3[4] = (uint8_t)(dutycycleoutput >> 8);
		msg_HT_PD16_A_0x6D3[5] = (uint8_t)(dutycycleoutput);
		msg_HT_PD16_A_0x6D3[6] = (uint8_t)((uint16_t)(PD16_A_SPI1_Frequency) >> 8);
		msg_HT_PD16_A_0x6D3[7] = (uint8_t)(PD16_A_SPI1_Frequency);
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup SPI2 Message
		msg_HT_PD16_A_0x6D3[0] = 0x61;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_SPI2_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_SPI2_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_SPI2_mV);
		dutycycleoutput = (uint16_t)(PD16_A_SPI2_DutyCycle * 10);
		msg_HT_PD16_A_0x6D3[4] = (uint8_t)(dutycycleoutput >> 8);
		msg_HT_PD16_A_0x6D3[5] = (uint8_t)(dutycycleoutput);
		msg_HT_PD16_A_0x6D3[6] = (uint8_t)((uint16_t)(PD16_A_SPI2_Frequency) >> 8);
		msg_HT_PD16_A_0x6D3[7] = (uint8_t)(PD16_A_SPI2_Frequency);
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup SPI3 Message
		msg_HT_PD16_A_0x6D3[0] = 0x62;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_SPI3_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_SPI3_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_SPI3_mV);
		dutycycleoutput = (uint16_t)(PD16_A_SPI3_DutyCycle * 10);
		msg_HT_PD16_A_0x6D3[4] = (uint8_t)(dutycycleoutput >> 8);
		msg_HT_PD16_A_0x6D3[5] = (uint8_t)(dutycycleoutput);
		msg_HT_PD16_A_0x6D3[6] = (uint8_t)((uint16_t)(PD16_A_SPI3_Frequency) >> 8);
		msg_HT_PD16_A_0x6D3[7] = (uint8_t)(PD16_A_SPI3_Frequency);
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup SPI4 Message
		msg_HT_PD16_A_0x6D3[0] = 0x63;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_SPI4_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_SPI4_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_SPI4_mV);
		dutycycleoutput = (uint16_t)(PD16_A_SPI4_DutyCycle * 10);
		msg_HT_PD16_A_0x6D3[4] = (uint8_t)(dutycycleoutput >> 8);
		msg_HT_PD16_A_0x6D3[5] = (uint8_t)(dutycycleoutput);
		msg_HT_PD16_A_0x6D3[6] = (uint8_t)((uint16_t)(PD16_A_SPI4_Frequency) >> 8);
		msg_HT_PD16_A_0x6D3[7] = (uint8_t)(PD16_A_SPI4_Frequency);
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup AVI1 Message
		msg_HT_PD16_A_0x6D3[0] = 0x80;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_AVI1_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_AVI1_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_AVI1_mV);
		msg_HT_PD16_A_0x6D3[4] = 0;
		msg_HT_PD16_A_0x6D3[5] = 0;
		msg_HT_PD16_A_0x6D3[6] = 0;
		msg_HT_PD16_A_0x6D3[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup AVI2 Message
		msg_HT_PD16_A_0x6D3[0] = 0x81;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_AVI2_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_AVI2_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_AVI2_mV);
		msg_HT_PD16_A_0x6D3[4] = 0;
		msg_HT_PD16_A_0x6D3[5] = 0;
		msg_HT_PD16_A_0x6D3[6] = 0;
		msg_HT_PD16_A_0x6D3[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup AVI3 Message
		msg_HT_PD16_A_0x6D3[0] = 0x82;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_AVI3_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_AVI3_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_AVI3_mV);
		msg_HT_PD16_A_0x6D3[4] = 0;
		msg_HT_PD16_A_0x6D3[5] = 0;
		msg_HT_PD16_A_0x6D3[6] = 0;
		msg_HT_PD16_A_0x6D3[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);

		// setup AVI4 Message
		msg_HT_PD16_A_0x6D3[0] = 0x83;
		msg_HT_PD16_A_0x6D3[1] = PD16_A_AVI4_State;
		msg_HT_PD16_A_0x6D3[2] = (uint8_t)(PD16_A_AVI4_mV >> 8);
		msg_HT_PD16_A_0x6D3[3] = (uint8_t)(PD16_A_AVI4_mV);
		msg_HT_PD16_A_0x6D3[4] = 0;
		msg_HT_PD16_A_0x6D3[5] = 0;
		msg_HT_PD16_A_0x6D3[6] = 0;
		msg_HT_PD16_A_0x6D3[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D3, 8, msg_HT_PD16_A_0x6D3);
	}
}

/* Run 10Hz Functions here */
void events_10Hz()
{
	if (HALTECH_PD16_A == 1)
	{
		// 25a HCO1 Message
		msg_HT_PD16_A_0x6D4[0] = 0x00;
		msg_HT_PD16_A_0x6D4[1] = PD16_A_25a_HCO1_Load;
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_25a_HCO1_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_25a_HCO1_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_25a_HCO1_LowSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_25a_HCO1_LowSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_25a_HCO1_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[7] = (uint8_t)(PD16_A_25a_HCO1_HighSide_Current_mA);
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 25a HCO2 Message
		msg_HT_PD16_A_0x6D4[0] = 0x01;
		msg_HT_PD16_A_0x6D4[1] = PD16_A_25a_HCO2_Load;
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_25a_HCO2_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_25a_HCO2_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_25a_HCO2_LowSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_25a_HCO2_LowSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_25a_HCO2_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[7] = (uint8_t)(PD16_A_25a_HCO2_HighSide_Current_mA);
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 25a HCO3 Message
		msg_HT_PD16_A_0x6D4[0] = 0x02;
		msg_HT_PD16_A_0x6D4[1] = PD16_A_25a_HCO3_Load;
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_25a_HCO3_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_25a_HCO3_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_25a_HCO3_LowSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_25a_HCO3_LowSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_25a_HCO3_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[7] = (uint8_t)(PD16_A_25a_HCO3_HighSide_Current_mA);
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 25a HCO4 Message
		msg_HT_PD16_A_0x6D4[0] = 0x03;
		msg_HT_PD16_A_0x6D4[1] = PD16_A_25a_HCO4_Load;
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_25a_HCO4_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_25a_HCO4_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_25a_HCO4_LowSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_25a_HCO4_LowSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_25a_HCO4_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[7] = (uint8_t)(PD16_A_25a_HCO4_HighSide_Current_mA);
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO1 Message
		if (PD16_A_8a_HCO1_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO1_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x20;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO1_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO1_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO1_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO1_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO1_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO1_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO2 Message
		if (PD16_A_8a_HCO2_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO2_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x21;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO2_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO2_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO2_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO2_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO2_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO2_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO3 Message
		if (PD16_A_8a_HCO3_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO3_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x22;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO3_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO3_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO3_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO3_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO3_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO3_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO4 Message
		if (PD16_A_8a_HCO4_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO4_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x23;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO4_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO4_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO4_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO4_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO4_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO4_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO5 Message
		if (PD16_A_8a_HCO5_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO5_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x24;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO5_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO5_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO5_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO5_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO5_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO5_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO6 Message
		if (PD16_A_8a_HCO6_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO6_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x25;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO6_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO6_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO6_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO6_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO6_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO6_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO7 Message
		if (PD16_A_8a_HCO7_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO7_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x26;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO7_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO7_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO7_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO7_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO7_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO7_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO8 Message
		if (PD16_A_8a_HCO8_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO8_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x27;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO8_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO8_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO8_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO8_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO8_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO8_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO9 Message
		if (PD16_A_8a_HCO9_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO9_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x28;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO9_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO9_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO9_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO9_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO9_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO9_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// 8a HCO10 Message
		if (PD16_A_8a_HCO10_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_8a_HCO10_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x29;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_8a_HCO10_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_8a_HCO10_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_8a_HCO10_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_8a_HCO10_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_8a_HCO10_HighSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_8a_HCO10_Load);
		msg_HT_PD16_A_0x6D4[7] = 0;
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// HBO1 Message
		if (PD16_A_HBO1_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_HBO1_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x40;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_HBO1_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_HBO1_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_HBO1_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_HBO1_LowSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_HBO1_LowSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_HBO1_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[7] = (uint8_t)(PD16_A_HBO1_HighSide_Current_mA);
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);

		// HBO2 Message
		if (PD16_A_HBO2_Total_Retries >= 31)
		{
			total_retries = 31;
		}
		else
		{
			total_retries = PD16_A_HBO2_Total_Retries;
		}
		msg_HT_PD16_A_0x6D4[0] = 0x41;
		msg_HT_PD16_A_0x6D4[1] = ((total_retries << 3) + PD16_A_HBO2_PinState);
		msg_HT_PD16_A_0x6D4[2] = (uint8_t)(PD16_A_HBO2_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D4[3] = (uint8_t)(PD16_A_HBO2_Voltage_mV);
		msg_HT_PD16_A_0x6D4[4] = (uint8_t)(PD16_A_HBO2_LowSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[5] = (uint8_t)(PD16_A_HBO2_LowSide_Current_mA);
		msg_HT_PD16_A_0x6D4[6] = (uint8_t)(PD16_A_HBO2_HighSide_Current_mA >> 8);
		msg_HT_PD16_A_0x6D4[7] = (uint8_t)(PD16_A_HBO2_HighSide_Current_mA);
		send_message(HALTECH_CAN, false, 0x6D4, 8, msg_HT_PD16_A_0x6D4);
	}

	// DEMONSTRATION FUNCTIONS //
	PD16_A_25a_HCO1_Voltage_mV += 10;
	if (PD16_A_25a_HCO1_Voltage_mV > 30000)
	{
		PD16_A_25a_HCO1_Voltage_mV = 0;
	}
	PD16_A_25a_HCO1_HighSide_Current_mA += 100;
	if (PD16_A_25a_HCO1_HighSide_Current_mA > 50000)
	{
		PD16_A_25a_HCO1_HighSide_Current_mA = 0;
	}
	PD16_A_25a_HCO1_Load += 1;
	if (PD16_A_25a_HCO1_Load > 100)
	{
		PD16_A_25a_HCO1_Load = 0;
	}
	PD16_A_25a_HCO1_LowSide_Current_mA = 50000 - PD16_A_25a_HCO1_HighSide_Current_mA;

	PD16_A_HBO1_Voltage_mV += 10;
	if (PD16_A_HBO1_Voltage_mV > 30000)
	{
		PD16_A_HBO1_Voltage_mV = 0;
	}
	PD16_A_HBO1_HighSide_Current_mA += 100;
	if (PD16_A_HBO1_HighSide_Current_mA > 50000)
	{
		PD16_A_HBO1_HighSide_Current_mA = 0;
	}
	PD16_A_HBO1_LowSide_Current_mA = 50000 - PD16_A_HBO1_HighSide_Current_mA;
	// END DEMONSTRATION FUNCTIONS //
}

/* Run 5Hz Functions here */
void events_5Hz()
{
	toggleLED(LED_1);
}

/* Run 2Hz Functions here */
void events_2Hz()
{
	if (HALTECH_PD16_A == 1)
	{
		msg_HT_PD16_A_0x6D5[0] = (uint8_t)((PD16_A_Status << 4) + PD16_A_ID_Conflict);
		msg_HT_PD16_A_0x6D5[1] = (uint8_t)((PD16_A_Bootcode_Version << 2) + PD16_A_FW_Major_Version);
		msg_HT_PD16_A_0x6D5[2] = PD16_A_FW_Minor_Version;
		msg_HT_PD16_A_0x6D5[3] = PD16_A_Firmware_Bugfix_Version;
		msg_HT_PD16_A_0x6D5[4] = PD16_A_FW_Release_Type;
		msg_HT_PD16_A_0x6D5[5] = 0;
		msg_HT_PD16_A_0x6D5[6] = 0;
		msg_HT_PD16_A_0x6D5[7] = 0;
		send_message(HALTECH_CAN, 0, 0x6D5, 8, msg_HT_PD16_A_0x6D5);

		msg_HT_PD16_A_0x6D6[0] = 0x00;
		msg_HT_PD16_A_0x6D6[1] = PD16_A_IgnitionSwitchStatus;
		msg_HT_PD16_A_0x6D6[2] = (uint8_t)(PD16_A_Main_Rail_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[3] = (uint8_t)(PD16_A_Main_Rail_Voltage_mV);
		msg_HT_PD16_A_0x6D6[4] = (uint8_t)(PD16_A_Protected_Rail_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[5] = (uint8_t)(PD16_A_Protected_Rail_Voltage_mV);
		msg_HT_PD16_A_0x6D6[6] = (uint8_t)(PD16_A_ECR_Plug_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[7] = (uint8_t)(PD16_A_ECR_Plug_Voltage_mV);
		send_message(HALTECH_CAN, 0, 0x6D6, 8, msg_HT_PD16_A_0x6D6);

		msg_HT_PD16_A_0x6D6[0] = 0x01;
		msg_HT_PD16_A_0x6D6[1] = 0;
		msg_HT_PD16_A_0x6D6[2] = (uint8_t)(PD16_A_Boost_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[3] = (uint8_t)(PD16_A_Boost_Voltage_mV);
		msg_HT_PD16_A_0x6D6[4] = (uint8_t)(PD16_A_SEPIC_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[5] = (uint8_t)(PD16_A_SEPIC_Voltage_mV);
		msg_HT_PD16_A_0x6D6[6] = (uint8_t)(PD16_A_ECR_Plug_Current_mA >> 8);
		msg_HT_PD16_A_0x6D6[7] = (uint8_t)(PD16_A_ECR_Plug_Current_mA);
		send_message(HALTECH_CAN, 0, 0x6D6, 8, msg_HT_PD16_A_0x6D6);

		msg_HT_PD16_A_0x6D6[0] = 0x02;
		msg_HT_PD16_A_0x6D6[1] = 0;
		msg_HT_PD16_A_0x6D6[2] = (uint8_t)(PD16_A_UVLO_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[3] = (uint8_t)(PD16_A_UVLO_Voltage_mV);
		msg_HT_PD16_A_0x6D6[4] = (uint8_t)(PD16_A_SensorGround_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[5] = (uint8_t)(PD16_A_SensorGround_Voltage_mV);
		msg_HT_PD16_A_0x6D6[6] = (uint8_t)(PD16_A_VDD_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[7] = (uint8_t)(PD16_A_VDD_Voltage_mV);
		send_message(HALTECH_CAN, 0, 0x6D6, 8, msg_HT_PD16_A_0x6D6);

		msg_HT_PD16_A_0x6D6[0] = 0x03;
		msg_HT_PD16_A_0x6D6[1] = PD16_A_Main_Rail_Temp_C;
		msg_HT_PD16_A_0x6D6[2] = PD16_A_Thermistor1_Temp_C;
		msg_HT_PD16_A_0x6D6[3] = PD16_A_Thermistor2_Temp_C;
		msg_HT_PD16_A_0x6D6[4] = PD16_A_Thermistor3_Temp_C;
		msg_HT_PD16_A_0x6D6[5] = PD16_A_CPU_Temp_C;
		msg_HT_PD16_A_0x6D6[6] = (uint8_t)((uint16_t)(PD16_A_Total_Current_Amps * 10) >> 8);
		msg_HT_PD16_A_0x6D6[7] = (uint8_t)(PD16_A_Total_Current_Amps * 10);
		send_message(HALTECH_CAN, 0, 0x6D6, 8, msg_HT_PD16_A_0x6D6);

		msg_HT_PD16_A_0x6D6[0] = 0x04;
		msg_HT_PD16_A_0x6D6[1] = 0;
		msg_HT_PD16_A_0x6D6[2] = (uint8_t)(PD16_A_Battery_Voltage_mV >> 8);
		msg_HT_PD16_A_0x6D6[3] = (uint8_t)(PD16_A_Battery_Voltage_mV);
		msg_HT_PD16_A_0x6D6[4] = (uint8_t)(PD16_A_OnTime >> 8);
		msg_HT_PD16_A_0x6D6[5] = (uint8_t)(PD16_A_OnTime);
		msg_HT_PD16_A_0x6D6[6] = ((HCO3_HCO4_Temp_enum << 6) + (HCO1_HCO2_Temp_enum << 4) + (TVS_Temp_enum << 2) + Main_Rail_Temp_enum);
		msg_HT_PD16_A_0x6D6[7] = 0;
		send_message(HALTECH_CAN, 0, 0x6D6, 8, msg_HT_PD16_A_0x6D6);

		msg_HT_PD16_A_0x6D6[0] = 0x05;
		msg_HT_PD16_A_0x6D6[1] = 0;
		msg_HT_PD16_A_0x6D6[2] = ((PD16_A_SerialNumber[0] << 4) + PD16_A_SerialNumber[1]);
		msg_HT_PD16_A_0x6D6[3] = ((PD16_A_SerialNumber[2] << 4) + PD16_A_SerialNumber[3]);
		msg_HT_PD16_A_0x6D6[4] = ((PD16_A_SerialNumber[4] << 4) + PD16_A_SerialNumber[5]);
		msg_HT_PD16_A_0x6D6[5] = ((PD16_A_SerialNumber[6] << 4) + PD16_A_SerialNumber[7]);
		msg_HT_PD16_A_0x6D6[6] = ((PD16_A_SerialNumber[8] << 4) + PD16_A_SerialNumber[9]);
		msg_HT_PD16_A_0x6D6[7] = ((PD16_A_SerialNumber[10] << 4) + PD16_A_SerialNumber[11]);
		send_message(HALTECH_CAN, 0, 0x6D6, 8, msg_HT_PD16_A_0x6D6);

		// Demonstration Functions
		if (PD16_A_SPI1_State == INPUT_STATE_ON)
		{
			PD16_A_SPI1_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_SPI1_State = INPUT_STATE_ON;
		}

		if (PD16_A_SPI2_State == INPUT_STATE_ON)
		{
			PD16_A_SPI2_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_SPI2_State = INPUT_STATE_ON;
		}

		if (PD16_A_SPI3_State == INPUT_STATE_ON)
		{
			PD16_A_SPI3_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_SPI3_State = INPUT_STATE_ON;
		}

		if (PD16_A_SPI4_State == INPUT_STATE_ON)
		{
			PD16_A_SPI4_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_SPI4_State = INPUT_STATE_ON;
		}

		if (PD16_A_AVI1_State == INPUT_STATE_ON)
		{
			PD16_A_AVI1_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_AVI1_State = INPUT_STATE_ON;
		}

		if (PD16_A_AVI2_State == INPUT_STATE_ON)
		{
			PD16_A_AVI2_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_AVI2_State = INPUT_STATE_ON;
		}

		if (PD16_A_AVI3_State == INPUT_STATE_ON)
		{
			PD16_A_AVI3_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_AVI3_State = INPUT_STATE_ON;
		}

		if (PD16_A_AVI4_State == INPUT_STATE_ON)
		{
			PD16_A_AVI4_State = INPUT_STATE_OFF;
		}
		else
		{
			PD16_A_AVI4_State = INPUT_STATE_ON;
		}
		PD16_A_HBO1_Total_Retries++;
		if (PD16_A_HBO1_Total_Retries > 30)
		{
			PD16_A_HBO1_Total_Retries = 0;
		}
		PD16_A_HBO2_Total_Retries++;
		if (PD16_A_HBO2_Total_Retries > 30)
		{
			PD16_A_HBO2_Total_Retries = 0;
		}
		// End Demonstration Functions
	}
}

/* Run 1Hz Functions here */
void events_1Hz()
{
	PD16_A_OnTime++;
}
