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
// for the realdash function
#include <stdlib.h>
#include <unistd.h>
// end includes for realdash function
#include "stm32g4xx_hal.h"

/* End File Includes */

/* Variable Declarations */
uint32_t serialnumber;
CAN_ErrorCounts errors;
uint8_t countervalue = 0;

/* Startup Functions */
void events_Startup()
{
	setupCANbus(CAN_1, 500000, NORMAL_MODE);
	setupCANbus(CAN_2, 1000000, NORMAL_MODE);
	setupCANbus(CAN_3, 1000000, NORMAL_MODE);
	setCAN_Termination(CAN_1, false);
	setCAN_Termination(CAN_2, false);
	setCAN_Termination(CAN_3, false);
	startCANbus(CAN_1);
	// startCANbus(CAN_2);
	// startCANbus(CAN_3);
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
	// char formatted_message[50];
	// format_CAN_message(&Message, formatted_message, sizeof(formatted_message));
	// printf("%s\r\n", formatted_message);
	if (Message.Bus == CAN_1)
	{

		uint8_t serialBlockTag[4] = {0x44, 0x33, 0x22, 0x11};
		serialWrite((const uint8_t *)&serialBlockTag, 4);

		// the CAN frame id number (as 32bit little endian value)
		serialWrite((const uint8_t *)&Message.arbitration_id, 4);

		// CAN frame payload
		serialWrite(Message.data, 8);

		// send_message(CAN_2,Message.is_extended_id,Message.arbitration_id,Message.dlc,Message.data);
	}
	if (Message.Bus == CAN_2)
	{
		// send_message(CAN_1,Message.is_extended_id,Message.arbitration_id,Message.dlc,Message.data);
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
	uint8_t msgdata1[8] = {countervalue, countervalue + 1 % 256, countervalue + 2 % 256, countervalue + 3 % 256, countervalue + 4 % 256, countervalue + 5 % 256, countervalue + 6 % 256, countervalue + 7 % 256};
	send_message(CAN_1, false, 0x123, 8, msgdata1);
	countervalue++;
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