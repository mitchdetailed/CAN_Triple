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
#include "stm32g4xx_hal.h"

/* End File Includes */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* File Define options */

#define HALTECH_CAN CAN_1 //
#define HALTECH_TMS4 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech TMS-4 Variables

uint8_t TMS_4_Multiplexer;
uint16_t RR_Tire_Pressure_kPa; // 0 to 800 kPa Table Range, 1kPa Resolution
uint16_t RL_Tire_Pressure_kPa; // 0 to 800 kPa Table Range, 1kPa Resolution
uint16_t FR_Tire_Pressure_kPa; // 0 to 800 kPa Table Range, 1kPa Resolution
uint16_t FL_Tire_Pressure_kPa; // 0 to 800 kPa Table Range, 1kPa Resolution
int16_t RR_Tire_Temperature_C; // -40 to 125 C Table Range, 1 C Resolution
int16_t RL_Tire_Temperature_C; // -40 to 125 C Table Range, 1 C Resolution
int16_t FR_Tire_Temperature_C; // -40 to 125 C Table Range, 1 C Resolution
int16_t FL_Tire_Temperature_C; // -40 to 125 C Table Range, 1 C Resolution
float RR_TPMS_Voltage;		   // 0 to 4 Volts Table Range, 0.1V Resolution
float RL_TPMS_Voltage;		   // 0 to 4 Volts Table Range, 0.1V Resolution
float FR_TPMS_Voltage;		   // 0 to 4 Volts Table Range, 0.1V Resolution
float FL_TPMS_Voltage;		   // 0 to 4 Volts Table Range, 0.1V Resolution
bool RR_Tire_Leaking;
bool RL_Tire_Leaking;
bool FR_Tire_Leaking;
bool FL_Tire_Leaking;
uint8_t RR_Tire_Temperature_Absolute;
uint8_t RL_Tire_Temperature_Absolute;
uint8_t FR_Tire_Temperature_Absolute;
uint8_t FL_Tire_Temperature_Absolute;
bool RR_Tire_Temperature_Negative;
bool RL_Tire_Temperature_Negative;
bool FR_Tire_Temperature_Negative;
bool FL_Tire_Temperature_Negative;
uint8_t msg_0x77E_FL[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // FL
uint8_t msg_0x77E_FR[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // FR
uint8_t msg_0x77E_RL[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // RL
uint8_t msg_0x77E_RR[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // RR

// End Haltech TMS-4 variables

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

	if (HALTECH_TMS4 == 1)
	{
		if (FL_Tire_Temperature_C < 0)
		{
			FL_Tire_Temperature_Negative = 1;
			FL_Tire_Temperature_Absolute = FL_Tire_Temperature_C * -1;
		}
		else
		{
			FL_Tire_Temperature_Negative = 0;
			FL_Tire_Temperature_Absolute = FL_Tire_Temperature_C;
		}

		if (FR_Tire_Temperature_C < 0)
		{
			FR_Tire_Temperature_Negative = 1;
			FR_Tire_Temperature_Absolute = FR_Tire_Temperature_C * -1;
		}
		else
		{
			FR_Tire_Temperature_Negative = 0;
			FR_Tire_Temperature_Absolute = FR_Tire_Temperature_C;
		}

		if (RL_Tire_Temperature_C < 0)
		{
			RL_Tire_Temperature_Negative = 1;
			RL_Tire_Temperature_Absolute = RL_Tire_Temperature_C * -1;
		}
		else
		{
			RL_Tire_Temperature_Negative = 0;
			RL_Tire_Temperature_Absolute = RL_Tire_Temperature_C;
		}

		if (RR_Tire_Temperature_C < 0)
		{
			RR_Tire_Temperature_Negative = 1;
			RR_Tire_Temperature_Absolute = RR_Tire_Temperature_C * -1;
		}
		else
		{
			RR_Tire_Temperature_Negative = 0;
			RR_Tire_Temperature_Absolute = RR_Tire_Temperature_C;
		}

		msg_0x77E_FL[0] = 0x01;
		msg_0x77E_FL[1] = (uint8_t)(FL_Tire_Pressure_kPa >> 8);
		msg_0x77E_FL[2] = (uint8_t)(FL_Tire_Pressure_kPa);
		msg_0x77E_FL[3] = FL_Tire_Temperature_Absolute;
		msg_0x77E_FL[4] = (uint8_t)(FL_TPMS_Voltage * 10);
		msg_0x77E_FL[5] = (uint8_t)((FL_Tire_Temperature_Negative << 4) + FL_Tire_Leaking);
		msg_0x77E_FL[6] = 0;
		msg_0x77E_FL[7] = 0;
		send_message(HALTECH_CAN, 0, 0x77E, 8, msg_0x77E_FL);

		msg_0x77E_FR[0] = 0x02;
		msg_0x77E_FR[1] = (uint8_t)(FR_Tire_Pressure_kPa >> 8);
		msg_0x77E_FR[2] = (uint8_t)(FR_Tire_Pressure_kPa);
		msg_0x77E_FR[3] = FR_Tire_Temperature_Absolute;
		msg_0x77E_FR[4] = (uint8_t)(FR_TPMS_Voltage * 10);
		msg_0x77E_FR[5] = (uint8_t)((FR_Tire_Temperature_Negative << 4) + FR_Tire_Leaking);
		msg_0x77E_FR[6] = 0;
		msg_0x77E_FR[7] = 0;
		send_message(HALTECH_CAN, 0, 0x77E, 8, msg_0x77E_FR);

		msg_0x77E_RL[0] = 0x03;
		msg_0x77E_RL[1] = (uint8_t)(RL_Tire_Pressure_kPa >> 8);
		msg_0x77E_RL[2] = (uint8_t)(RL_Tire_Pressure_kPa);
		msg_0x77E_RL[3] = RL_Tire_Temperature_Absolute;
		msg_0x77E_RL[4] = (uint8_t)(RL_TPMS_Voltage * 10);
		msg_0x77E_RL[5] = (uint8_t)((RL_Tire_Temperature_Negative << 4) + RL_Tire_Leaking);
		msg_0x77E_RL[6] = 0;
		msg_0x77E_RL[7] = 0;
		send_message(HALTECH_CAN, 0, 0x77E, 8, msg_0x77E_RL);

		msg_0x77E_RR[0] = 0x04;
		msg_0x77E_RR[1] = (uint8_t)(RR_Tire_Pressure_kPa >> 8);
		msg_0x77E_RR[2] = (uint8_t)(RR_Tire_Pressure_kPa);
		msg_0x77E_RR[3] = RR_Tire_Temperature_Absolute;
		msg_0x77E_RR[4] = (uint8_t)(RR_TPMS_Voltage * 10);
		msg_0x77E_RR[5] = (uint8_t)((RR_Tire_Temperature_Negative << 4) + RR_Tire_Leaking);
		msg_0x77E_RR[6] = 0;
		msg_0x77E_RR[7] = 0;
		send_message(HALTECH_CAN, 0, 0x77E, 8, msg_0x77E_RR);
	}
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
	RR_Tire_Pressure_kPa = ((RR_Tire_Pressure_kPa + 1) % 800);
	RL_Tire_Pressure_kPa = ((RL_Tire_Pressure_kPa + 1) % 800);
	FR_Tire_Pressure_kPa = ((FR_Tire_Pressure_kPa + 1) % 800);
	FL_Tire_Pressure_kPa = ((FL_Tire_Pressure_kPa + 1) % 800);
	RR_Tire_Temperature_C = (RR_Tire_Temperature_C + 1);
	if (RR_Tire_Temperature_C > 125)
	{
		RR_Tire_Temperature_C = -40;
	}
	RL_Tire_Temperature_C = (RL_Tire_Temperature_C + 1);
	if (RL_Tire_Temperature_C > 125)
	{
		RL_Tire_Temperature_C = -40;
	}
	FR_Tire_Temperature_C = (FR_Tire_Temperature_C + 1);
	if (FR_Tire_Temperature_C > 125)
	{
		FR_Tire_Temperature_C = -40;
	}
	FL_Tire_Temperature_C = (FL_Tire_Temperature_C + 1);
	if (FL_Tire_Temperature_C > 125)
	{
		FL_Tire_Temperature_C = -40;
	}
	RR_TPMS_Voltage = (RR_TPMS_Voltage + 0.1);
	RL_TPMS_Voltage = (RL_TPMS_Voltage + 0.1);
	FR_TPMS_Voltage = (FR_TPMS_Voltage + 0.1);
	FL_TPMS_Voltage = (FL_TPMS_Voltage + 0.1);
	if (RR_TPMS_Voltage > 4)
	{
		RR_TPMS_Voltage = 0;
	}
	if (RL_TPMS_Voltage > 4)
	{
		RL_TPMS_Voltage = 0;
	}
	if (FR_TPMS_Voltage > 4)
	{
		FR_TPMS_Voltage = 0;
	}
	if (FL_TPMS_Voltage > 4)
	{
		FL_TPMS_Voltage = 0;
	}
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}
