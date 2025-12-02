/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech TC2 Box B for configuration
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
#define HALTECH_TC4B 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech TC4B Variables

float TC4B_TCI1_Temp_C; // 0 - 1500 C, 1 C Table Resolution
float TC4B_TCI2_Temp_C; // 0 - 1500 C, 1 C Table Resolution
float TC4B_TCI3_Temp_C; // 0 - 1500 C, 1 C Table Resolution
float TC4B_TCI4_Temp_C; // 0 - 1500 C, 1 C Table Resolution

bool TC4B_ID_Conflict = 0;
uint8_t TC4B_Status = 1;
uint8_t TC4B_FW_Major_Version = 3;
uint8_t TC4B_Bootcode_Version = 0;
uint8_t TC4B_FW_Minor_Version = 255;
uint8_t TC4B_Firmware_Bugfix_Version = 1;
uint8_t TC4B_FW_Release_Type = 0;

uint8_t msg_HT_TC4B_0x2CD[8];
uint8_t msg_HT_TC4B_0x2CF[8];

// End Haltech TC4B variables

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
		}
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

	if (HALTECH_TC4B == 1)
	{
		uint16_t tc4b_tc1_output = (uint16_t)((TC4B_TCI1_Temp_C + 250) * 2.4571835761849767);
		uint16_t tc4b_tc2_output = (uint16_t)((TC4B_TCI2_Temp_C + 250) * 2.4571835761849767);
		uint16_t tc4b_tc3_output = (uint16_t)((TC4B_TCI2_Temp_C + 250) * 2.4571835761849767);
		uint16_t tc4b_tc4_output = (uint16_t)((TC4B_TCI2_Temp_C + 250) * 2.4571835761849767);

		msg_HT_TC4B_0x2CD[0] = (uint8_t)(tc4b_tc1_output >> 8);
		msg_HT_TC4B_0x2CD[1] = (uint8_t)(tc4b_tc1_output);
		msg_HT_TC4B_0x2CD[2] = (uint8_t)(tc4b_tc2_output >> 8);
		msg_HT_TC4B_0x2CD[3] = (uint8_t)(tc4b_tc2_output);
		msg_HT_TC4B_0x2CD[4] = (uint8_t)(tc4b_tc3_output >> 8);
		msg_HT_TC4B_0x2CD[5] = (uint8_t)(tc4b_tc3_output);
		msg_HT_TC4B_0x2CD[6] = (uint8_t)(tc4b_tc4_output >> 8);
		msg_HT_TC4B_0x2CD[7] = (uint8_t)(tc4b_tc4_output);

		send_message(HALTECH_CAN, 0, 0x2CD, 8, msg_HT_TC4B_0x2CD);
	}
}

/* Run 20Hz Functions here */
void events_20Hz()
{
}

/* Run 10Hz Functions here */
void events_10Hz()
{
	msg_HT_TC4B_0x2CF[0] = (uint8_t)((TC4B_Status << 4) + TC4B_ID_Conflict);
	msg_HT_TC4B_0x2CF[1] = (uint8_t)((TC4B_Bootcode_Version << 2) + TC4B_FW_Major_Version);
	msg_HT_TC4B_0x2CF[2] = TC4B_FW_Minor_Version;
	msg_HT_TC4B_0x2CF[3] = TC4B_Firmware_Bugfix_Version;
	msg_HT_TC4B_0x2CF[4] = TC4B_FW_Release_Type;
	msg_HT_TC4B_0x2CF[5] = 0;
	msg_HT_TC4B_0x2CF[6] = 0;
	msg_HT_TC4B_0x2CF[7] = 0;
	send_message(HALTECH_CAN, 0, 0x2CF, 8, msg_HT_TC4B_0x2CF);
}

/* Run 5Hz Functions here */
void events_5Hz()
{
	toggleLED(LED_1);

	// DEMONSTRATION FUNCTIONS //
	TC4B_TCI1_Temp_C = TC4B_TCI1_Temp_C + 5;
	if (TC4B_TCI1_Temp_C > 1500)
	{
		TC4B_TCI1_Temp_C = 0;
	}

	TC4B_TCI2_Temp_C = TC4B_TCI2_Temp_C + 5;
	if (TC4B_TCI2_Temp_C > 1500)
	{
		TC4B_TCI2_Temp_C = 0;
	}

	TC4B_TCI3_Temp_C = TC4B_TCI3_Temp_C + 5;
	if (TC4B_TCI3_Temp_C > 1500)
	{
		TC4B_TCI3_Temp_C = 0;
	}

	TC4B_TCI4_Temp_C = TC4B_TCI4_Temp_C + 5;
	if (TC4B_TCI4_Temp_C > 1500)
	{
		TC4B_TCI4_Temp_C = 0;
	}

	// END DEMONSTRATION FUNCTIONS //
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}
