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

#define HALTECH_CAN CAN_1
#define HALTECH_TMS4
#define HALTECH_TMS4_DEMO

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//
/* Variable Prototypes */
/**
 * @brief Data structure for Haltech TMS-4 Tire Monitoring System.
 * 
 * This structure holds tire pressure, temperature, voltage, 
 * and status information for each tire, supporting real-time monitoring
 * and CAN message formatting.
 */
typedef struct {
    /**
     * @brief Enum representing tire positions.
     * 
     * FL: Front Left, FR: Front Right, RL: Rear Left, RR: Rear Right.
     */
    enum { FL = 0, FR = 1, RL = 2, RR = 3 } Tms4Position_t;

    /** @brief Tire pressure values (in kPa). Range: 0-800 kPa, 1 kPa resolution. */
    uint16_t Tire_Pressure_kPa[4];

    /** @brief Tire temperature values (in Celsius). Range: -40 to 124°C, 1°C resolution. */
    int8_t   Tire_Temperature_C[4];

    /** @brief TPMS voltage readings (in volts). Range: 0-4V, 0.1V resolution. */
    float    TPMS_Voltage[4];

    /** @brief Absolute tire temperature values. */
    uint8_t  Tire_Temperature_Absolute[4];

    /** @brief Tire leaking status. True = leaking, False = normal. */
    bool     Tire_Leaking[4];

    /** @brief Indicates if the temperature value is negative. */
    bool     Tire_Temperature_Negative[4];

    /** @brief Raw CAN message data buffer (8 bytes). */
    uint8_t  CanMsg[8];

} Tms4Data_t;


/* End Variable Prototypes */

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

/*  Haltech TMS-4  */
#ifdef HALTECH_TMS4
/**
 * @brief Haltech TMS-4 sensor data instance.
 * 
 * This instance of Tms4Data_t represents the real-time sensor values
 * for tire pressure, temperature, and status flags. It is initialized
 * with default values for testing and operation.
 */
Tms4Data_t haltech_tms4 = {
    /** @brief Initial tire pressure values (kPa). */
    .Tire_Pressure_kPa = {227, 227, 227, 227},

    /** @brief Initial tire temperature values (°C). */
    .Tire_Temperature_C = {40, 40, 40, 40},

    /** @brief Initial TPMS voltage values (V). */
    .TPMS_Voltage = {3.3, 3.3, 3.3, 3.3},

    /** @brief Initial absolute tire temperature values. */
    .Tire_Temperature_Absolute = {40, 40, 40, 40},

    /** @brief Initial tire leak status. False = no leak. */
    .Tire_Leaking = {false, false, false, false},

    /** @brief Initial negative temperature status. False = positive temperatures. */
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

	#ifdef HALTECH_TMS4
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
	
	
	/** Demo functions for testing operation with Haltech ECU */
	#if defined(HALTECH_TMS4) && defined(HALTECH_TMS4_DEMO)
	
	for (int i = 0; i < 4; i++) {
		// Increment tire pressure and wrap around at 800 kPa
		haltech_tms4.Tire_Pressure_kPa[i] = (haltech_tms4.Tire_Pressure_kPa[i] + 1) % 800;
	
		// Increment temperature, reset if exceeding 125°C
		haltech_tms4.Tire_Temperature_C[i]++;
		if (haltech_tms4.Tire_Temperature_C[i] >= 125) {
			haltech_tms4.Tire_Temperature_C[i] = -40;
		}
	
		// Increment TPMS voltage, reset if exceeding 4V
		haltech_tms4.TPMS_Voltage[i] += 0.1f;
		if (haltech_tms4.TPMS_Voltage[i] >= 4.0f) {
			haltech_tms4.TPMS_Voltage[i] = 0.0f;
		}
	}
	#endif
	/** End of Demo functions for testing operation with Haltech ECU */
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}
