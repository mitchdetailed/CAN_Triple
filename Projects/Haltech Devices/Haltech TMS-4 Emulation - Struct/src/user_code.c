/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech TMS-4 for configuration
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
#include <stdlib.h>
#include "stm32g4xx_hal.h"

/* End File Includes */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* File Define options */

#define HALTECH_CAN CAN_1 //
#define ENABLE_TMS4

#ifdef ENABLE_TMS4 
	#define FL 0
	#define FR 1
	#define RL 2
	#define RR 3
#endif

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//
/* Variable Prototypes */
typedef struct {
    uint16_t 	Tire_Pressure_kPa[4];  // 0-800 kPa, 1 kPa resolution
    int8_t   	Tire_Temperature_C[4]; // -40 to 125 °C, 1°C resolution
    float    	TPMS_Voltage[4];       // 0-4V, 0.1V resolution
    uint8_t  	Tire_Temperature_Absolute[4]; // Absolute temperature
	bool 		Tire_Leaking[4];		// Tire Leaking Status
	bool 		Tire_Temperature_Negative[4]; // Negative Temperature Status
	uint8_t 	CanMsg[8]; // CAN Message
} Tms4Data_t;

/* End Variable Prototypes */

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

/*  Haltech TMS-4  */
#ifdef ENABLE_TMS4
Tms4Data_t haltech_tms4 = {
    .Tire_Pressure_kPa = {250, 255, 260, 265},
    .Tire_Temperature_C = {30, 32, 28, 29},
    .TPMS_Voltage = {3.5, 3.4, 3.6, 3.3},
    .Tire_Temperature_Absolute = {30, 32, 28, 29},
	.Tire_Leaking = {false, false, false, false},
	.Tire_Temperature_Negative = {false, false, false, false}
	
};
#endif

/*  End Haltech TMS-4 */

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
	}
	if (Message.Bus == CAN_2)
	{
	}
	if (Message.Bus == CAN_3)
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
}

/* Run 50Hz Functions here */
void events_50Hz()
{

#ifdef ENABLE_TMS4
	for (int i = 0; i < 4; i++) {
		haltech_tms4.Tire_Temperature_Negative[i] = (haltech_tms4.Tire_Temperature_C[i] < 0);
		haltech_tms4.Tire_Temperature_Absolute[i] = abs(haltech_tms4.Tire_Temperature_C[i]);
		haltech_tms4.CanMsg[0] = i+1;
		haltech_tms4.CanMsg[1] = (uint8_t)(haltech_tms4.Tire_Pressure_kPa[i] >> 8);
		haltech_tms4.CanMsg[2] = (uint8_t)(haltech_tms4.Tire_Pressure_kPa[i]);
		haltech_tms4.CanMsg[3] = haltech_tms4.Tire_Temperature_Absolute[i];
		haltech_tms4.CanMsg[4] = (uint8_t)(haltech_tms4.TPMS_Voltage[i] * 10);
		haltech_tms4.CanMsg[5] = (uint8_t)((haltech_tms4.Tire_Temperature_Negative[i] << 4) + haltech_tms4.Tire_Leaking[i]);
		haltech_tms4.CanMsg[6] = 0;
		haltech_tms4.CanMsg[7] = 0;
		send_message(HALTECH_CAN, 0, 0x77E, 8, haltech_tms4.CanMsg);
	}
#endif
}

/* Run 20Hz Functions here */
void events_20Hz()
{
}

/* Run 10Hz Functions here */
void events_10Hz()
{
}

/* Run 5Hz Functions here */
void events_5Hz()
{
	toggleLED(LED_1);
	#ifdef ENABLE_TMS4
	for (int i = 0; i < 4; i++) {
		// Increment tire pressure and wrap around at 800 kPa
		haltech_tms4.Tire_Pressure_kPa[i] = (haltech_tms4.Tire_Pressure_kPa[i] + 1) % 800;
	
		// Increment temperature, reset if exceeding 125°C
		haltech_tms4.Tire_Temperature_C[i]++;
		if (haltech_tms4.Tire_Temperature_C[i] > 125) {
			haltech_tms4.Tire_Temperature_C[i] = -40;
		}
	
		// Increment TPMS voltage, reset if exceeding 4V
		haltech_tms4.TPMS_Voltage[i] += 0.1f;
		if (haltech_tms4.TPMS_Voltage[i] > 4.0f) {
			haltech_tms4.TPMS_Voltage[i] = 0.0f;
		}
	}
	#endif
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}
