/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech I/O expander 12 Box A for configuration
 * 		Notes :
 * 			*** DPO Ouput only responds to Duty cycle from Haltech ECU,
 * 			*** USE DUTY for DPO's WHEN CONFIGURING HALTECH ECU!!!!***
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
#define HALTECH_IO_BOX_A 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech IO Box Variables
float haltech_IO_Box_A_AVI1 = 0.0f;				 // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
float haltech_IO_Box_A_AVI2 = 0.0f;				 // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
float haltech_IO_Box_A_AVI3 = 0.0f;				 // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
float haltech_IO_Box_A_AVI4 = 0.0f;				 // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
float haltech_IO_Box_A_DPI1_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPI2_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPI3_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPI4_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
uint32_t haltech_IO_Box_A_DPI1_Hz = 0;			 // min 0 Hz, max 20000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint32_t haltech_IO_Box_A_DPI2_Hz = 0;			 // min 0 Hz, max 20000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint32_t haltech_IO_Box_A_DPI3_Hz = 0;			 // min 0 Hz, max 20000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint32_t haltech_IO_Box_A_DPI4_Hz = 0;			 // min 0 Hz, max 20000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
float haltech_IO_Box_A_DPO1_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPO2_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPO3_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPO4_Duty = 0.0f;		 // min 0.0%, max 100.0%, resolution 0.1% //
float haltech_IO_Box_A_DPO1_Period = 0.0f;		 // min 0.00ms, max 50.00ms, resolution 0.01ms //
float haltech_IO_Box_A_DPO2_Period = 0.0f;		 // min 0.00ms, max 50.00ms, resolution 0.01ms //
float haltech_IO_Box_A_DPO3_Period = 0.0f;		 // min 0.00ms, max 50.00ms, resolution 0.01ms //
float haltech_IO_Box_A_DPO4_Period = 0.0f;		 // min 0.00ms, max 50.00ms, resolution 0.01ms //
uint32_t haltech_IO_Box_A_DPO1_Hz = 0;			 // min 0 Hz, max 1000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint32_t haltech_IO_Box_A_DPO2_Hz = 0;			 // min 0 Hz, max 1000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint32_t haltech_IO_Box_A_DPO3_Hz = 0;			 // min 0 Hz, max 1000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint32_t haltech_IO_Box_A_DPO4_Hz = 0;			 // min 0 Hz, max 1000 Hz, resolution Variable based on Pulse Width, min 1 Hz after 300 hz, resolution will start reducing.. //
uint8_t haltech_IO_Box_A_Status = 1;			 // 0=In bootmode,1=In firmware,2=Hardware failure,3=Firmware erased,4=Watchdog timeout,5=Illegal op-code //
uint8_t haltech_IO_Box_A_ID_Conflict = 0;		 // 0=No Conflict, 1=Conflict //
uint8_t haltech_IO_Box_A_Bootcode_Version = 31;	 // min 0, max 31, resolution 1, recommend highest value{31} //
uint8_t haltech_IO_Box_A_FW_Major_Version = 3;	 // min 0, max 3, resolution 1, recommend highest value{3} //
uint8_t haltech_IO_Box_A_FW_Minor_Version = 255; // min 0, max 255, resolution 1, recommend highest value{255} //
uint8_t haltech_IO_Box_A_FW_Bugfix_Version = 0;	 // min 0, max 255, resolution 1, currently unaffected by value //
uint8_t haltech_IO_Box_A_FW_Release_Type = 0;	 // min 0, max 255, resolution 1, currently unaffected by value //
uint8_t haltech_IO_Box_A_AVI1_Pullup = 0;		 // 0=off, 1=on
uint8_t haltech_IO_Box_A_DPO1_Error = 0;		 // 0=Inactive, 1=Active
uint8_t haltech_IO_Box_A_DPO1_Active = 0;		 // 0=Low, 1=High
uint8_t haltech_IO_Box_A_AVI2_Pullup = 0;		 // 0=off, 1=on
uint8_t haltech_IO_Box_A_DPO2_Error = 0;		 // 0=Inactive, 1=Active
uint8_t haltech_IO_Box_A_DPO2_Active = 0;		 // 0=Low, 1=High
uint8_t haltech_IO_Box_A_AVI3_Pullup = 0;		 // 0=off, 1=on
uint8_t haltech_IO_Box_A_DPO3_Error = 0;		 // 0=Inactive, 1=Active
uint8_t haltech_IO_Box_A_DPO3_Active = 0;		 // 0=Low, 1=High
uint8_t haltech_IO_Box_A_AVI4_Pullup = 0;		 // 0=off, 1=on
uint8_t haltech_IO_Box_A_DPO4_Error = 0;		 // 0=Inactive, 1=Active
uint8_t haltech_IO_Box_A_DPO4_Active = 0;		 // 0=Low, 1=High
// End HALTECH_IO_BOX_A variables

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
			if (HALTECH_IO_BOX_A == 1)
			{
				if (Message.arbitration_id == 0x2D0)
				{
					haltech_IO_Box_A_DPO1_Duty = (float)((Message.data[0] << 2) + (Message.data[1] >> 6)) / 10;
					haltech_IO_Box_A_DPO1_Active = (Message.data[1] & 0x20) >> 5;
					haltech_IO_Box_A_DPO1_Error = (Message.data[1] & 0x10) >> 4;
					haltech_IO_Box_A_AVI1_Pullup = (Message.data[1] & 0x08) >> 3;
					haltech_IO_Box_A_DPO1_Hz = period_10uS_to_frequency_Hz(((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]);
					haltech_IO_Box_A_DPO1_Period = (float)((((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]) / 10);
					haltech_IO_Box_A_DPO2_Duty = (float)((Message.data[4] << 2) + (Message.data[5] >> 6)) / 10;
					haltech_IO_Box_A_DPO2_Active = (Message.data[5] & 0x20) >> 5;
					haltech_IO_Box_A_DPO2_Error = (Message.data[5] & 0x10) >> 4;
					haltech_IO_Box_A_AVI2_Pullup = (Message.data[5] & 0x08) >> 3;
					haltech_IO_Box_A_DPO2_Hz = period_10uS_to_frequency_Hz(((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]);
					haltech_IO_Box_A_DPO2_Period = (float)((((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]) / 10);

					// functions for testing DPO1
					// printf("DPO1 Period = %02.3f ms\t\t DPO1 Freq = %5i Hz\t\t DPO1 Duty = %03.1f\r\n",haltech_IO_Box_A_DPO1_Period,haltech_IO_Box_A_DPO1_Hz,haltech_IO_Box_A_DPO1_Duty);
					// printf("Byte 0 : %02x\tByte 1 : %02x\tByte 2 %02x\tByte 3 %02x\r\n", Message.data[0],Message.data[1], Message.data[2], Message.data[3]);
				}
				else if (Message.arbitration_id == 0x2D2)
				{
					haltech_IO_Box_A_DPO3_Duty = (float)((Message.data[0] << 2) + (Message.data[1] >> 6)) / 10;
					haltech_IO_Box_A_DPO3_Active = (Message.data[1] & 0x20) >> 5;
					haltech_IO_Box_A_DPO3_Error = (Message.data[1] & 0x10) >> 4;
					haltech_IO_Box_A_AVI3_Pullup = (Message.data[1] & 0x08) >> 3;
					haltech_IO_Box_A_DPO3_Hz = period_10uS_to_frequency_Hz(((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]);
					haltech_IO_Box_A_DPO3_Period = (float)((((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]) / 10);
					haltech_IO_Box_A_DPO4_Duty = (float)((Message.data[4] << 2) + (Message.data[5] >> 6)) / 10;
					haltech_IO_Box_A_DPO4_Active = (Message.data[5] & 0x20) >> 5;
					haltech_IO_Box_A_DPO4_Error = (Message.data[5] & 0x10) >> 4;
					haltech_IO_Box_A_AVI4_Pullup = (Message.data[5] & 0x08) >> 3;
					haltech_IO_Box_A_DPO4_Hz = period_10uS_to_frequency_Hz(((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]);
					haltech_IO_Box_A_DPO4_Period = (float)((((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]) / 10);
				}
			}
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

	if (HALTECH_IO_BOX_A == 1)
	{
		uint16_t ioBA_AVI1 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_A_AVI1 * 5 / 4095, 0);
		uint16_t ioBA_AVI2 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_A_AVI2 * 5 / 4095, 0);
		uint16_t ioBA_AVI3 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_A_AVI1 * 5 / 4095, 0);
		uint16_t ioBA_AVI4 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_A_AVI1 * 5 / 4095, 0);
		uint8_t msgIOBA_1[8] = {(uint8_t)(ioBA_AVI1 >> 8), (uint8_t)ioBA_AVI1, (uint8_t)(ioBA_AVI2 >> 8), (uint8_t)ioBA_AVI2, (uint8_t)(ioBA_AVI3 >> 8), (uint8_t)ioBA_AVI3, (uint8_t)(ioBA_AVI4 >> 8), (uint8_t)ioBA_AVI4};
		send_message(HALTECH_CAN, false, 0x2C0, 8, msgIOBA_1);

		uint16_t ioBA_DPI1_DC = (uint16_t)(haltech_IO_Box_A_DPI1_Duty * 10);
		uint16_t ioBA_DPI1_Period = (uint32_t)frequency_Hz_to_period_10uS(haltech_IO_Box_A_DPI1_Hz); // Can be edited to take in a general 10uS resolution value instead of frequency conversion function
		uint16_t ioBA_DPI2_DC = (uint16_t)(haltech_IO_Box_A_DPI2_Duty * 10);
		uint16_t ioBA_DPI2_Period = (uint32_t)frequency_Hz_to_period_10uS(haltech_IO_Box_A_DPI2_Hz); // Can be edited to take in a general 10uS resolution value instead of frequency conversion function
		uint8_t msgIOBA_2[8] = {(uint8_t)(ioBA_DPI1_DC >> 2), (uint8_t)((ioBA_DPI1_DC & 0x03) << 6), (uint8_t)(ioBA_DPI1_Period >> 8), (uint8_t)(ioBA_DPI1_Period), (uint8_t)(ioBA_DPI2_DC >> 2), (uint8_t)((ioBA_DPI2_DC & 0x03) << 6), (uint8_t)(ioBA_DPI2_Period >> 8), (uint8_t)(ioBA_DPI2_Period)};
		send_message(HALTECH_CAN, false, 0x2C2, 8, msgIOBA_2);

		uint16_t ioBA_DPI3_DC = (uint16_t)(haltech_IO_Box_A_DPI3_Duty * 10);
		uint16_t ioBA_DPI3_Period = (uint32_t)frequency_Hz_to_period_10uS(haltech_IO_Box_A_DPI3_Hz); // Can be edited to take in a general 10uS resolution value instead of frequency conversion function
		uint16_t ioBA_DPI4_DC = (uint16_t)(haltech_IO_Box_A_DPI4_Duty * 10);
		uint16_t ioBA_DPI4_Period = (uint32_t)frequency_Hz_to_period_10uS(haltech_IO_Box_A_DPI4_Hz); // Can be edited to take in a general 10uS resolution value instead of frequency conversion function
		uint8_t msgIOBA_3[8] = {(uint8_t)(ioBA_DPI3_DC >> 2), (uint8_t)((ioBA_DPI3_DC & 0x03) << 6), (uint8_t)(ioBA_DPI3_Period >> 8), (uint8_t)(ioBA_DPI3_Period), (uint8_t)(ioBA_DPI4_DC >> 2), (uint8_t)((ioBA_DPI4_DC & 0x03) << 6), (uint8_t)(ioBA_DPI4_Period >> 8), (uint8_t)(ioBA_DPI4_Period)};
		send_message(HALTECH_CAN, false, 0x2C4, 8, msgIOBA_3);

		uint8_t msgIOBA_4[8] = {(uint8_t)((haltech_IO_Box_A_Status << 4) + haltech_IO_Box_A_ID_Conflict), (uint8_t)((haltech_IO_Box_A_Bootcode_Version << 2) + haltech_IO_Box_A_FW_Major_Version), haltech_IO_Box_A_FW_Minor_Version, haltech_IO_Box_A_FW_Bugfix_Version, haltech_IO_Box_A_FW_Release_Type, 0, 0, 0};
		send_message(HALTECH_CAN, false, 0x2C6, 8, msgIOBA_4);
	}
}

/* Run 20Hz Functions here */
void events_20Hz()
{
}

/* Run 10Hz Functions here */
void events_10Hz()
{

	// functions to increment DPI values for testing...
	haltech_IO_Box_A_DPI1_Hz += 1;
	haltech_IO_Box_A_DPI2_Hz += 1;
	haltech_IO_Box_A_DPI3_Hz += 1;
	haltech_IO_Box_A_DPI4_Hz += 1;
	haltech_IO_Box_A_DPI1_Duty += 0.1;
	haltech_IO_Box_A_DPI2_Duty += 0.1;
	haltech_IO_Box_A_DPI3_Duty += 0.1;
	haltech_IO_Box_A_DPI4_Duty += 0.1;
	if (haltech_IO_Box_A_DPI1_Hz > 300)
	{
		haltech_IO_Box_A_DPI1_Hz = 0;
	}
	if (haltech_IO_Box_A_DPI2_Hz > 300)
	{
		haltech_IO_Box_A_DPI2_Hz = 0;
	}
	if (haltech_IO_Box_A_DPI3_Hz > 300)
	{
		haltech_IO_Box_A_DPI3_Hz = 0;
	}
	if (haltech_IO_Box_A_DPI4_Hz > 300)
	{
		haltech_IO_Box_A_DPI4_Hz = 0;
	}
	if (haltech_IO_Box_A_DPI1_Duty > 100)
	{
		haltech_IO_Box_A_DPI1_Duty = 0;
	}
	if (haltech_IO_Box_A_DPI2_Duty > 100)
	{
		haltech_IO_Box_A_DPI2_Duty = 0;
	}
	if (haltech_IO_Box_A_DPI3_Duty > 100)
	{
		haltech_IO_Box_A_DPI3_Duty = 0;
	}
	if (haltech_IO_Box_A_DPI4_Duty > 100)
	{
		haltech_IO_Box_A_DPI4_Duty = 0;
	}
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
