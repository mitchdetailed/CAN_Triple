/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech Dyno Dynamics integration for configuration
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
#define HALTECH_DYNODYNAMICS 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech Dyno Dynamics Variables

float Dyno_Ambient_Pressure_kPa;  // 0 to 200 kPa, 1kPa resolution
float Dyno_Ambient_Temperature_C; // -40 to 100 C, 1C resolution
uint8_t Dyno_Humidity_Percent;	  // 0.0 - 100.0 %, 1% resolution
float Dyno_Lambda1 = 1;			  // 0.48 - 1.36 lambda, 0.01 resolution
float Dyno_Lambda2 = 1;			  // 0.48 - 1.36 lambda, 0.01 resolution
int16_t Dyno_Power_kW;			  // -100 to 1000 kW, 1kW resolution
uint16_t Dyno_Road_Speed_kph;	  // 0 to 400 kph, 1kph resolution
int16_t Dyno_Torque_Nm;			  // -500 to 3000 Nm, 1Nm resolution
int16_t Dyno_Tractive_Effort_N;	  // -5000 to 32767 N, 1N resolution

uint8_t msg_HT_DynoDynamics_0x100[8];
uint8_t msg_HT_DynoDynamics_0x101[8];
uint8_t msg_HT_DynoDynamics_0x102[8];
uint8_t msg_HT_DynoDynamics_0x103[8];

// End Haltech Dyno Dynamics variables

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

	if (HALTECH_DYNODYNAMICS == 1)
	{
		msg_HT_DynoDynamics_0x100[0] = 0;
		msg_HT_DynoDynamics_0x100[1] = 0;
		msg_HT_DynoDynamics_0x100[2] = (uint8_t)((uint16_t)(Dyno_Road_Speed_kph) * 100);
		msg_HT_DynoDynamics_0x100[3] = (uint8_t)(((uint16_t)(Dyno_Road_Speed_kph) * 100) >> 8);
		msg_HT_DynoDynamics_0x100[4] = (uint8_t)((int16_t)(Dyno_Power_kW) * 10);
		msg_HT_DynoDynamics_0x100[5] = (uint8_t)(((int16_t)(Dyno_Power_kW) * 10) >> 8);
		msg_HT_DynoDynamics_0x100[6] = (uint8_t)((int16_t)(Dyno_Torque_Nm) * 5);
		msg_HT_DynoDynamics_0x100[7] = (uint8_t)(((int16_t)(Dyno_Torque_Nm) * 5) >> 8);
		send_message(HALTECH_CAN, false, 0x100, 8, msg_HT_DynoDynamics_0x100);

		msg_HT_DynoDynamics_0x101[0] = (uint8_t)(Dyno_Tractive_Effort_N);
		msg_HT_DynoDynamics_0x101[1] = (uint8_t)(Dyno_Tractive_Effort_N >> 8);
		msg_HT_DynoDynamics_0x101[2] = 0;
		msg_HT_DynoDynamics_0x101[3] = 0;
		msg_HT_DynoDynamics_0x101[4] = 0;
		msg_HT_DynoDynamics_0x101[5] = 0;
		msg_HT_DynoDynamics_0x101[6] = 0;
		msg_HT_DynoDynamics_0x101[7] = 0;
		send_message(HALTECH_CAN, false, 0x101, 8, msg_HT_DynoDynamics_0x101);

		msg_HT_DynoDynamics_0x102[0] = 0;
		msg_HT_DynoDynamics_0x102[1] = 0;
		msg_HT_DynoDynamics_0x102[2] = (uint8_t)((int16_t)(Dyno_Ambient_Temperature_C) * 10);
		msg_HT_DynoDynamics_0x102[3] = (uint8_t)((int16_t)((Dyno_Ambient_Temperature_C) * 10) >> 8);
		msg_HT_DynoDynamics_0x102[4] = (uint8_t)((uint16_t)(Dyno_Ambient_Pressure_kPa) * 10);
		msg_HT_DynoDynamics_0x102[5] = (uint8_t)(((uint16_t)(Dyno_Ambient_Pressure_kPa) * 10) >> 8);
		msg_HT_DynoDynamics_0x102[6] = (uint8_t)((uint16_t)(Dyno_Humidity_Percent) * 100);
		msg_HT_DynoDynamics_0x102[7] = (uint8_t)(((uint16_t)(Dyno_Humidity_Percent) * 100) >> 8);
		send_message(HALTECH_CAN, false, 0x102, 8, msg_HT_DynoDynamics_0x102);

		msg_HT_DynoDynamics_0x103[0] = (uint8_t)((uint16_t)(Dyno_Lambda1 * 100));
		msg_HT_DynoDynamics_0x103[1] = (uint8_t)((uint16_t)(Dyno_Lambda1 * 100) >> 8);
		msg_HT_DynoDynamics_0x103[2] = (uint8_t)((uint16_t)(Dyno_Lambda2 * 100));
		msg_HT_DynoDynamics_0x103[3] = (uint8_t)((uint16_t)(Dyno_Lambda2 * 100) >> 8);
		msg_HT_DynoDynamics_0x103[4] = 0;
		msg_HT_DynoDynamics_0x103[5] = 0;
		msg_HT_DynoDynamics_0x103[6] = 0;
		msg_HT_DynoDynamics_0x103[7] = 0;
		send_message(HALTECH_CAN, false, 0x103, 8, msg_HT_DynoDynamics_0x103);
	}
}

/* Run 20Hz Functions here */
void events_20Hz()
{
}

/* Run 10Hz Functions here */
void events_10Hz()
{
	// Increment the Haltech Dyno Dynamics variables
	Dyno_Ambient_Pressure_kPa += 1;
	if (Dyno_Ambient_Pressure_kPa > 200)
		Dyno_Ambient_Pressure_kPa = 0;
	Dyno_Ambient_Temperature_C += 1;
	if (Dyno_Ambient_Temperature_C > 100)
		Dyno_Ambient_Temperature_C = -40;
	Dyno_Humidity_Percent += 1;
	if (Dyno_Humidity_Percent > 100)
		Dyno_Humidity_Percent = 0;
	Dyno_Lambda1 += 0.01;
	if (Dyno_Lambda1 > 1.36)
		Dyno_Lambda1 = 0.48;
	Dyno_Lambda2 += 0.01;
	if (Dyno_Lambda2 > 1.36)
		Dyno_Lambda2 = 0.48;
	Dyno_Power_kW += 1;
	if (Dyno_Power_kW > 1000)
		Dyno_Power_kW = -100;
	Dyno_Road_Speed_kph += 1;
	if (Dyno_Road_Speed_kph > 400)
		Dyno_Road_Speed_kph = 0;
	Dyno_Torque_Nm += 1;
	if (Dyno_Torque_Nm > 3000)
		Dyno_Torque_Nm = -500;
	Dyno_Tractive_Effort_N += 1;
	if (Dyno_Tractive_Effort_N > 32767)
		Dyno_Tractive_Effort_N = -5000;
	// End Haltech Dyno Dynamics variables increments
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
