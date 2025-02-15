/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech I/O expander 12 Boxes for configuration
 * 		Notes :
 */

/* File Includes */
// C Standard Library Includes
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

// Project Specific Includes
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"
#include "snprintf.h"

/* End File Includes */

//-----------------------------//

/* File Define options */

#define HALTECH_CAN CAN_1 //
#define ENABLE_HALTECH_IO_BOX_A
#define ENABLE_HALTECH_IO_BOX_A_DEMO
#define ENABLE_HALTECH_IO_BOX_B
#define ENABLE_HALTECH_IO_BOX_B_DEMO
/* End File Defines */

//-----------------------------//

/* Enumerations and Typedefs*/

// Haltech I/O Expander 12 Box Structure Prototype
typedef struct
{
	float AVI_Voltage[4];
	bool AVI_Pullup[4];
	float DPI_Duty[4];
	uint16_t DPI_Freq[4];
	float DPO_Duty[4];
	uint16_t DPO_Freq[4];
	bool DPO_Error[4];
	bool DPO_Active[4]; // Fixed the typo in your request: `bool_DPO_Active` -> `bool DPO_Active`
	bool IDConflict;
	uint8_t Status;
	uint8_t BootcodeVersion;
	uint8_t FW_Major;
	uint8_t FW_Minor;
	uint8_t FW_Bugfix;
	uint8_t FW_Release;
	uint8_t CANMsg[8];
	uint16_t outAVI[4];
	uint16_t outDPI_DC[4];
	uint16_t outDPI_Period[4];
} HaltechIO12Expander;

// Haltech Ecosystem Structure prototype

typedef struct
{
#ifdef ENABLE_HALTECH_IO_BOX_A
	HaltechIO12Expander IO12ExpanderA;
#endif

#ifdef ENABLE_HALTECH_IO_BOX_B
	HaltechIO12Expander IO12ExpanderB;
#endif
} HaltechEcosystem;

/* End Enumerations and Typedefs */

//-----------------------------//

/* Variable Declarations */

HaltechEcosystem Haltech =
	{

#ifdef ENABLE_HALTECH_IO_BOX_A
		.IO12ExpanderA =
			{

				.Status = 1,		   // 0=In bootmode,1=In firmware,2=Hardware failure,3=Firmware erased,4=Watchdog timeout,5=Illegal op-code
				.BootcodeVersion = 31, // min 0, max 31, resolution 1, recommend highest value{31}
				.FW_Major = 3,		   // min 0, max 3, resolution 1, recommend highest value{3}
				.FW_Minor = 255,	   // Given value for FW_Minor
			},
#endif

#ifdef ENABLE_HALTECH_IO_BOX_B
		.IO12ExpanderB =
			{
				.Status = 1,		   // 0=In bootmode,1=In firmware,2=Hardware failure,3=Firmware erased,4=Watchdog timeout,5=Illegal op-code
				.BootcodeVersion = 31, // min 0, max 31, resolution 1, recommend highest value{31}
				.FW_Major = 3,		   // min 0, max 3, resolution 1, recommend highest value{3}
				.FW_Minor = 255,	   // Given value for FW_Minor
			}
#endif
};

/* End Variable Declarations */

//-----------------------------//

/* Functions */

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
	else if (Message.Bus == CAN_2)
	{
	}
	else if (Message.Bus == CAN_3)
	{
	}

	if (Message.Bus == HALTECH_CAN)
	{

#ifdef ENABLE_HALTECH_IO_BOX_A
		if (Message.arbitration_id == 0x2D0)
		{
			Haltech.IO12ExpanderA.DPO_Duty[0] = (float)((Message.data[0] << 2) + (Message.data[1] >> 6)) / 10;
			Haltech.IO12ExpanderA.DPO_Active[0] = (Message.data[1] & 0x20) >> 5;
			Haltech.IO12ExpanderA.DPO_Error[0] = (Message.data[1] & 0x10) >> 4;
			Haltech.IO12ExpanderA.AVI_Pullup[0] = (Message.data[1] & 0x08) >> 3;
			Haltech.IO12ExpanderA.DPO_Freq[0] = period_10uS_to_frequency_Hz(((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]);
			Haltech.IO12ExpanderA.DPO_Duty[1] = (float)((Message.data[4] << 2) + (Message.data[5] >> 6)) / 10;
			Haltech.IO12ExpanderA.DPO_Active[1] = (Message.data[5] & 0x20) >> 5;
			Haltech.IO12ExpanderA.DPO_Error[1] = (Message.data[5] & 0x10) >> 4;
			Haltech.IO12ExpanderA.AVI_Pullup[1] = (Message.data[5] & 0x08) >> 3;
			Haltech.IO12ExpanderA.DPO_Freq[1] = period_10uS_to_frequency_Hz(((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]);
		}
		else if (Message.arbitration_id == 0x2D2)
		{
			Haltech.IO12ExpanderA.DPO_Duty[2] = (float)((Message.data[0] << 2) + (Message.data[1] >> 6)) / 10;
			Haltech.IO12ExpanderA.DPO_Active[2] = (Message.data[1] & 0x20) >> 5;
			Haltech.IO12ExpanderA.DPO_Error[2] = (Message.data[1] & 0x10) >> 4;
			Haltech.IO12ExpanderA.AVI_Pullup[2] = (Message.data[1] & 0x08) >> 3;
			Haltech.IO12ExpanderA.DPO_Freq[2] = period_10uS_to_frequency_Hz(((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]);
			Haltech.IO12ExpanderA.DPO_Duty[3] = (float)((Message.data[4] << 2) + (Message.data[5] >> 6)) / 10;
			Haltech.IO12ExpanderA.DPO_Active[3] = (Message.data[5] & 0x20) >> 5;
			Haltech.IO12ExpanderA.DPO_Error[3] = (Message.data[5] & 0x10) >> 4;
			Haltech.IO12ExpanderA.AVI_Pullup[3] = (Message.data[5] & 0x08) >> 3;
			Haltech.IO12ExpanderA.DPO_Freq[3] = period_10uS_to_frequency_Hz(((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]);
		}
#endif

#ifdef ENABLE_HALTECH_IO_BOX_B
		if (Message.arbitration_id == 0x2D1)
		{
			Haltech.IO12ExpanderB.DPO_Duty[0] = (float)((Message.data[0] << 2) + (Message.data[1] >> 6)) / 10;
			Haltech.IO12ExpanderB.DPO_Active[0] = (Message.data[1] & 0x20) >> 5;
			Haltech.IO12ExpanderB.DPO_Error[0] = (Message.data[1] & 0x10) >> 4;
			Haltech.IO12ExpanderB.AVI_Pullup[0] = (Message.data[1] & 0x08) >> 3;
			Haltech.IO12ExpanderB.DPO_Freq[0] = period_10uS_to_frequency_Hz(((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]);
			Haltech.IO12ExpanderB.DPO_Duty[1] = (float)((Message.data[4] << 2) + (Message.data[5] >> 6)) / 10;
			Haltech.IO12ExpanderB.DPO_Active[1] = (Message.data[5] & 0x20) >> 5;
			Haltech.IO12ExpanderB.DPO_Error[1] = (Message.data[5] & 0x10) >> 4;
			Haltech.IO12ExpanderB.AVI_Pullup[1] = (Message.data[5] & 0x08) >> 3;
			Haltech.IO12ExpanderB.DPO_Freq[1] = period_10uS_to_frequency_Hz(((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]);
		}
		else if (Message.arbitration_id == 0x2D3)
		{
			Haltech.IO12ExpanderB.DPO_Duty[2] = (float)((Message.data[0] << 2) + (Message.data[1] >> 6)) / 10;
			Haltech.IO12ExpanderB.DPO_Active[2] = (Message.data[1] & 0x20) >> 5;
			Haltech.IO12ExpanderB.DPO_Error[2] = (Message.data[1] & 0x10) >> 4;
			Haltech.IO12ExpanderB.AVI_Pullup[2] = (Message.data[1] & 0x08) >> 3;
			Haltech.IO12ExpanderB.DPO_Freq[2] = period_10uS_to_frequency_Hz(((Message.data[1] & 0x01) << 9) + (Message.data[2] << 8) + Message.data[3]);
			Haltech.IO12ExpanderB.DPO_Duty[3] = (float)((Message.data[4] << 2) + (Message.data[5] >> 6)) / 10;
			Haltech.IO12ExpanderB.DPO_Active[3] = (Message.data[5] & 0x20) >> 5;
			Haltech.IO12ExpanderB.DPO_Error[3] = (Message.data[5] & 0x10) >> 4;
			Haltech.IO12ExpanderB.AVI_Pullup[3] = (Message.data[5] & 0x08) >> 3;
			Haltech.IO12ExpanderB.DPO_Freq[3] = period_10uS_to_frequency_Hz(((Message.data[5] & 0x01) << 9) + (Message.data[6] << 8) + Message.data[7]);
		}
#endif
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

#ifdef ENABLE_HALTECH_IO_BOX_A
	for (uint8_t i = 0; i < 4; i++)
	{
		Haltech.IO12ExpanderA.outAVI[i] = (uint16_t)(map_float(Haltech.IO12ExpanderA.AVI_Voltage[i], 0, 5, 0, 4095));
		Haltech.IO12ExpanderA.outDPI_DC[i] = (uint16_t)(Haltech.IO12ExpanderA.DPI_Duty[i] * 10);
		Haltech.IO12ExpanderA.outDPI_Period[i] = (uint32_t)frequency_Hz_to_period_10uS(Haltech.IO12ExpanderA.DPI_Freq[i]);
	}

	Haltech.IO12ExpanderA.CANMsg[0] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[0] >> 8);
	Haltech.IO12ExpanderA.CANMsg[1] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[0] & 0xFF);
	Haltech.IO12ExpanderA.CANMsg[2] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[1] >> 8);
	Haltech.IO12ExpanderA.CANMsg[3] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[1] & 0xFF);
	Haltech.IO12ExpanderA.CANMsg[4] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[2] >> 8);
	Haltech.IO12ExpanderA.CANMsg[5] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[2] & 0xFF);
	Haltech.IO12ExpanderA.CANMsg[6] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[3] >> 8);
	Haltech.IO12ExpanderA.CANMsg[7] = (uint8_t)(Haltech.IO12ExpanderA.outAVI[3] & 0xFF);
	send_message(HALTECH_CAN, false, 0x2C0, 8, Haltech.IO12ExpanderA.CANMsg);

	Haltech.IO12ExpanderA.CANMsg[0] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_DC[0] >> 2);
	Haltech.IO12ExpanderA.CANMsg[1] = (uint8_t)((Haltech.IO12ExpanderA.outDPI_DC[0] & 0x03) << 6);
	Haltech.IO12ExpanderA.CANMsg[2] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[0] >> 8);
	Haltech.IO12ExpanderA.CANMsg[3] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[0]);
	Haltech.IO12ExpanderA.CANMsg[4] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_DC[1] >> 2);
	Haltech.IO12ExpanderA.CANMsg[5] = (uint8_t)((Haltech.IO12ExpanderA.outDPI_DC[1] & 0x03) << 6);
	Haltech.IO12ExpanderA.CANMsg[6] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[1] >> 8);
	Haltech.IO12ExpanderA.CANMsg[7] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[1]);
	send_message(HALTECH_CAN, false, 0x2C2, 8, Haltech.IO12ExpanderA.CANMsg);

	Haltech.IO12ExpanderA.CANMsg[0] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_DC[2] >> 2);
	Haltech.IO12ExpanderA.CANMsg[1] = (uint8_t)((Haltech.IO12ExpanderA.outDPI_DC[2] & 0x03) << 6);
	Haltech.IO12ExpanderA.CANMsg[2] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[2] >> 8);
	Haltech.IO12ExpanderA.CANMsg[3] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[2]);
	Haltech.IO12ExpanderA.CANMsg[4] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_DC[3] >> 2);
	Haltech.IO12ExpanderA.CANMsg[5] = (uint8_t)((Haltech.IO12ExpanderA.outDPI_DC[3] & 0x03) << 6);
	Haltech.IO12ExpanderA.CANMsg[6] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[3] >> 8);
	Haltech.IO12ExpanderA.CANMsg[7] = (uint8_t)(Haltech.IO12ExpanderA.outDPI_Period[3]);
	send_message(HALTECH_CAN, false, 0x2C4, 8, Haltech.IO12ExpanderA.CANMsg);

	Haltech.IO12ExpanderA.CANMsg[0] = (uint8_t)((Haltech.IO12ExpanderA.Status << 4) + Haltech.IO12ExpanderA.IDConflict);
	Haltech.IO12ExpanderA.CANMsg[1] = (uint8_t)((Haltech.IO12ExpanderA.BootcodeVersion << 2) + Haltech.IO12ExpanderA.FW_Major);
	Haltech.IO12ExpanderA.CANMsg[2] = Haltech.IO12ExpanderA.FW_Minor;
	Haltech.IO12ExpanderA.CANMsg[3] = Haltech.IO12ExpanderA.FW_Bugfix;
	Haltech.IO12ExpanderA.CANMsg[4] = Haltech.IO12ExpanderA.FW_Release;
	Haltech.IO12ExpanderA.CANMsg[5] = 0;
	Haltech.IO12ExpanderA.CANMsg[6] = 0;
	Haltech.IO12ExpanderA.CANMsg[7] = 0;
	send_message(HALTECH_CAN, false, 0x2C6, 8, Haltech.IO12ExpanderA.CANMsg);
#endif

#ifdef ENABLE_HALTECH_IO_BOX_B

	for (uint8_t i = 0; i < 4; i++)
	{
		Haltech.IO12ExpanderB.outAVI[i] = (uint16_t)(map_float(Haltech.IO12ExpanderB.AVI_Voltage[i], 0, 5, 0, 4095));
		Haltech.IO12ExpanderB.outDPI_DC[i] = (uint16_t)(Haltech.IO12ExpanderB.DPI_Duty[i] * 10);
		Haltech.IO12ExpanderB.outDPI_Period[i] = (uint32_t)(frequency_Hz_to_period_10uS(Haltech.IO12ExpanderB.DPI_Freq[i]));
	}

	Haltech.IO12ExpanderB.CANMsg[0] = (uint8_t)(Haltech.IO12ExpanderB.outAVI[0] >> 8);
	Haltech.IO12ExpanderB.CANMsg[1] = (uint8_t)Haltech.IO12ExpanderB.outAVI[0];
	Haltech.IO12ExpanderB.CANMsg[2] = (uint8_t)(Haltech.IO12ExpanderB.outAVI[1] >> 8);
	Haltech.IO12ExpanderB.CANMsg[3] = (uint8_t)Haltech.IO12ExpanderB.outAVI[1];
	Haltech.IO12ExpanderB.CANMsg[4] = (uint8_t)(Haltech.IO12ExpanderB.outAVI[2] >> 8);
	Haltech.IO12ExpanderB.CANMsg[5] = (uint8_t)Haltech.IO12ExpanderB.outAVI[2];
	Haltech.IO12ExpanderB.CANMsg[6] = (uint8_t)(Haltech.IO12ExpanderB.outAVI[3] >> 8);
	Haltech.IO12ExpanderB.CANMsg[7] = (uint8_t)Haltech.IO12ExpanderB.outAVI[3];
	send_message(HALTECH_CAN, false, 0x2C1, 8, Haltech.IO12ExpanderB.CANMsg);

	Haltech.IO12ExpanderB.CANMsg[0] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_DC[0] >> 2);
	Haltech.IO12ExpanderB.CANMsg[1] = (uint8_t)((Haltech.IO12ExpanderB.outDPI_DC[0] & 0x03) << 6);
	Haltech.IO12ExpanderB.CANMsg[2] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[0] >> 8);
	Haltech.IO12ExpanderB.CANMsg[3] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[0]);
	Haltech.IO12ExpanderB.CANMsg[4] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_DC[1] >> 2);
	Haltech.IO12ExpanderB.CANMsg[5] = (uint8_t)((Haltech.IO12ExpanderB.outDPI_DC[1] & 0x03) << 6);
	Haltech.IO12ExpanderB.CANMsg[6] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[1] >> 8);
	Haltech.IO12ExpanderB.CANMsg[7] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[1]);
	send_message(HALTECH_CAN, false, 0x2C3, 8, Haltech.IO12ExpanderB.CANMsg);

	Haltech.IO12ExpanderB.CANMsg[0] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_DC[2] >> 2);
	Haltech.IO12ExpanderB.CANMsg[1] = (uint8_t)((Haltech.IO12ExpanderB.outDPI_DC[2] & 0x03) << 6);
	Haltech.IO12ExpanderB.CANMsg[2] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[2] >> 8);
	Haltech.IO12ExpanderB.CANMsg[3] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[2]);
	Haltech.IO12ExpanderB.CANMsg[4] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_DC[3] >> 2);
	Haltech.IO12ExpanderB.CANMsg[5] = (uint8_t)((Haltech.IO12ExpanderB.outDPI_DC[3] & 0x03) << 6);
	Haltech.IO12ExpanderB.CANMsg[6] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[3] >> 8);
	Haltech.IO12ExpanderB.CANMsg[7] = (uint8_t)(Haltech.IO12ExpanderB.outDPI_Period[3]);
	send_message(HALTECH_CAN, false, 0x2C5, 8, Haltech.IO12ExpanderB.CANMsg);

	Haltech.IO12ExpanderB.CANMsg[0] = (uint8_t)((Haltech.IO12ExpanderB.Status << 4) + Haltech.IO12ExpanderB.IDConflict);
	Haltech.IO12ExpanderB.CANMsg[1] = (uint8_t)((Haltech.IO12ExpanderB.BootcodeVersion << 2) + Haltech.IO12ExpanderB.FW_Major);
	Haltech.IO12ExpanderB.CANMsg[2] = Haltech.IO12ExpanderB.FW_Minor;
	Haltech.IO12ExpanderB.CANMsg[3] = Haltech.IO12ExpanderB.FW_Bugfix;
	Haltech.IO12ExpanderB.CANMsg[4] = Haltech.IO12ExpanderB.FW_Release;
	Haltech.IO12ExpanderB.CANMsg[5] = 0;
	Haltech.IO12ExpanderB.CANMsg[6] = 0;
	Haltech.IO12ExpanderB.CANMsg[7] = 0;
	send_message(HALTECH_CAN, false, 0x2C7, 8, Haltech.IO12ExpanderB.CANMsg);
#endif
}

/* Run 20Hz Functions here */
void events_20Hz()
{
}

/* Run 10Hz Functions here */
void events_10Hz()
{
	// functions to increment values for testing...

#if defined(ENABLE_HALTECH_IO_BOX_A) && defined(ENABLE_HALTECH_IO_BOX_A_DEMO)
	for (uint8_t i = 0; i < 4; i++)
	{
		Haltech.IO12ExpanderA.AVI_Voltage[i] = fmod(Haltech.IO12ExpanderA.AVI_Voltage[i] + 0.01f, 5.0f);
		Haltech.IO12ExpanderA.DPI_Freq[i] = fmod(Haltech.IO12ExpanderA.DPI_Freq[i] + 1, 300);
		Haltech.IO12ExpanderA.DPI_Duty[i] = fmod(Haltech.IO12ExpanderA.DPI_Duty[i] + 0.1, 100);
	}
#endif

#if defined(ENABLE_HALTECH_IO_BOX_B) && defined(ENABLE_HALTECH_IO_BOX_B_DEMO)
	for (uint8_t i = 0; i < 4; i++)
	{
		Haltech.IO12ExpanderB.AVI_Voltage[i] = fmod(Haltech.IO12ExpanderB.AVI_Voltage[i] + 0.1f, 5.0f);
		Haltech.IO12ExpanderB.DPI_Freq[i] = fmod(Haltech.IO12ExpanderB.DPI_Freq[i] + 1, 300);
		Haltech.IO12ExpanderB.DPI_Duty[i] = fmod(Haltech.IO12ExpanderB.DPI_Duty[i] + 0.1, 100);
	}
#endif
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
