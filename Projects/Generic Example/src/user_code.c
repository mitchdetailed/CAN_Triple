/*
 * user_code.c - All User Code should be applied here unless specified otherwise.
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

/* Variable Declarations */
uint32_t serialnumber;
CAN_ErrorCounts errors;
double testval = 0.0f;
/* Startup Functions */
void events_Startup()
{
	setupCANbus(CAN_1, 1000000, NORMAL_MODE);
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
		if( Message.arbitration_id == 0x123)
		{	
			// Message.data = {0x03,0xE8,0x00,0x00,0x00,0x00,0x00,0x00};
			testval = dbc_decode(Message.data, DBC_SIGNED,true,24,8,0.1,0,3);
			printf("testval = %6.3f\r\n", testval);
			uint8_t newmessage[8] = {0}; // MAKE SURE YOU DECLARE THE ARRAY AS 0's prior..
			dbc_encode(newmessage,8, DBC_SIGNED,true,24,8,0.1,0,3);
			printf("newmessage = ");
			for (int i = 0; i < 8; i++)
			{
				printf("%02X ", newmessage[i]);
			}
			printf("\r\n");
		}
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
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}
