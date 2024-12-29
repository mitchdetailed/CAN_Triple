/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech 3x5 Keypad A for configuration
 * 		Notes :
 * 			*** Will require defining CAN Inputs as button press states. ***
 *			*** When a Keypad Button State is changed, you will want to send
 *			*** a message of the Keypad Button States
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
#define HALTECH_KEYPAD_3X5_A 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech Keypad 3x5 A Variables

enum State
{
	OFF = 0, // Representing false
	ON = 1	 // Representing true
};

enum ButtonState
{
	NOT_PRESSED = 0, // Representing false
	PRESSED = 1		 // Representing true
};

bool HT_3x5A_Button_1_State = NOT_PRESSED;
bool HT_3x5A_Button_2_State = NOT_PRESSED;
bool HT_3x5A_Button_3_State = NOT_PRESSED;
bool HT_3x5A_Button_4_State = NOT_PRESSED;
bool HT_3x5A_Button_5_State = NOT_PRESSED;
bool HT_3x5A_Button_6_State = NOT_PRESSED;
bool HT_3x5A_Button_7_State = NOT_PRESSED;
bool HT_3x5A_Button_8_State = NOT_PRESSED;
bool HT_3x5A_Button_9_State = NOT_PRESSED;
bool HT_3x5A_Button_10_State = NOT_PRESSED;
bool HT_3x5A_Button_11_State = NOT_PRESSED;
bool HT_3x5A_Button_12_State = NOT_PRESSED;
bool HT_3x5A_Button_13_State = NOT_PRESSED;
bool HT_3x5A_Button_14_State = NOT_PRESSED;
bool HT_3x5A_Button_15_State = NOT_PRESSED;

bool HT_3x5A_Button_1_LED_Green = OFF;
bool HT_3x5A_Button_1_LED_Yellow = OFF;
bool HT_3x5A_Button_1_LED_Red = OFF;
bool HT_3x5A_Button_2_LED_Green = OFF;
bool HT_3x5A_Button_2_LED_Yellow = OFF;
bool HT_3x5A_Button_2_LED_Red = OFF;
bool HT_3x5A_Button_3_LED_Green = OFF;
bool HT_3x5A_Button_3_LED_Yellow = OFF;

bool HT_3x5A_Button_3_LED_Red = OFF;
bool HT_3x5A_Button_4_LED_Green = OFF;
bool HT_3x5A_Button_4_LED_Yellow = OFF;
bool HT_3x5A_Button_4_LED_Red = OFF;
bool HT_3x5A_Button_5_LED_Green = OFF;
bool HT_3x5A_Button_5_LED_Yellow = OFF;
bool HT_3x5A_Button_5_LED_Red = OFF;
bool HT_3x5A_Button_6_LED_Green = OFF;

bool HT_3x5A_Button_6_LED_Yellow = OFF;
bool HT_3x5A_Button_6_LED_Red = OFF;
bool HT_3x5A_Button_7_LED_Green = OFF;
bool HT_3x5A_Button_7_LED_Yellow = OFF;
bool HT_3x5A_Button_7_LED_Red = OFF;
bool HT_3x5A_Button_8_LED_Green = OFF;
bool HT_3x5A_Button_8_LED_Yellow = OFF;
bool HT_3x5A_Button_8_LED_Red = OFF;

bool HT_3x5A_Button_9_LED_Green = OFF;
bool HT_3x5A_Button_9_LED_Yellow = OFF;
bool HT_3x5A_Button_9_LED_Red = OFF;
bool HT_3x5A_Button_10_LED_Green = OFF;
bool HT_3x5A_Button_10_LED_Yellow = OFF;
bool HT_3x5A_Button_10_LED_Red = OFF;
bool HT_3x5A_Button_11_LED_Green = OFF;
bool HT_3x5A_Button_11_LED_Yellow = OFF;

bool HT_3x5A_Button_11_LED_Red = OFF;
bool HT_3x5A_Button_12_LED_Green = OFF;
bool HT_3x5A_Button_12_LED_Yellow = OFF;
bool HT_3x5A_Button_12_LED_Red = OFF;
bool HT_3x5A_Button_13_LED_Green = OFF;
bool HT_3x5A_Button_13_LED_Yellow = OFF;
bool HT_3x5A_Button_13_LED_Red = OFF;
bool HT_3x5A_Button_14_LED_Green = OFF;

bool HT_3x5A_Button_14_LED_Yellow = OFF;
bool HT_3x5A_Button_14_LED_Red = OFF;
bool HT_3x5A_Button_15_LED_Green = OFF;
bool HT_3x5A_Button_15_LED_Yellow = OFF;
bool HT_3x5A_Button_15_LED_Red = OFF;

uint8_t HT_3x5A_Button_Backlight_Brightness = 0x7F; // Initial 50%
uint8_t HT_3x5A_Button_LED_Brightness = 0x7F;		// Initial 50%

uint8_t msg_0x18C_data[3] = {0, 0, 0};
uint8_t msg_0x70C_data[1] = {0x05};
uint8_t msg_0x58C_data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

uint16_t Service_Data_Object = 0;
uint8_t sdo_sub_index = 0;

uint8_t HT_3x5A_Node_ID = 0x0C;
uint32_t HT_3x5A_Button_Vendor_ID = 0x0307;
uint32_t HT_3x5A_Button_Product_Code = 0x334B;
uint32_t HT_3x5A_Button_Revision_Number = 0x0000;
uint32_t HT_3x5A_Button_Serial_Number = 0xFFFFFFFE;
uint16_t HT_3x5A_Button_COB_ID = 0x18C;
uint16_t HT_3x5A_Button_Broadcast_timeMs = 200;
uint16_t HT_3x5A_Button_Broadcast_counter = 0;
uint16_t HT_3x5A_NMT_Broadcast_timeMs = 150;
uint16_t HT_3x5A_NMT_counter = 0;

// for demonstration purposes //
uint8_t msg_0x18C_data_demo[3] = {0, 0, 0};
uint8_t demo_counter = 0;
// end for demonstration purposes //

// End Haltech Keypad 3x5 A variables

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
			if (HALTECH_KEYPAD_3X5_A == 1)
			{
				if (Message.arbitration_id == (0x600 + HT_3x5A_Node_ID))
				{
					Service_Data_Object = ((Message.data[2] << 8) + Message.data[1]);
					sdo_sub_index = Message.data[3];
					if ((Message.data[0] & 0xF0) == 0x20) // Requesting Write Data...
					{
						if (Service_Data_Object == 0x1017)
						{
							if (sdo_sub_index == 0)
							{
								HT_3x5A_NMT_Broadcast_timeMs = ((Message.data[5] << 8) + Message.data[4]);
								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = 0x00;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
						}
						else if (Service_Data_Object == 0x1800)
						{
							if (sdo_sub_index == 0x05)
							{
								HT_3x5A_Button_Broadcast_timeMs = ((Message.data[5] << 8) + Message.data[4]);
								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
						}
						else if (Service_Data_Object == 0x6200)
						{
							if (sdo_sub_index == 0x01)
							{
								HT_3x5A_Button_1_LED_Green = (Message.data[4] & 0x01);
								HT_3x5A_Button_1_LED_Yellow = ((Message.data[4] & 0x02) >> 1);
								HT_3x5A_Button_1_LED_Red = ((Message.data[4] & 0x04) >> 2);
								HT_3x5A_Button_2_LED_Green = ((Message.data[4] & 0x08) >> 3);
								HT_3x5A_Button_2_LED_Yellow = ((Message.data[4] & 0x10) >> 4);
								HT_3x5A_Button_2_LED_Red = ((Message.data[4] & 0x20) >> 5);
								HT_3x5A_Button_3_LED_Green = ((Message.data[4] & 0x40) >> 6);
								HT_3x5A_Button_3_LED_Yellow = ((Message.data[4] & 0x80) >> 7);

								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x02)
							{
								HT_3x5A_Button_3_LED_Red = (Message.data[4] & 0x01);
								HT_3x5A_Button_4_LED_Green = ((Message.data[4] & 0x02) >> 1);
								HT_3x5A_Button_4_LED_Yellow = ((Message.data[4] & 0x04) >> 2);
								HT_3x5A_Button_4_LED_Red = ((Message.data[4] & 0x08) >> 3);
								HT_3x5A_Button_5_LED_Green = ((Message.data[4] & 0x10) >> 4);
								HT_3x5A_Button_5_LED_Yellow = ((Message.data[4] & 0x20) >> 5);
								HT_3x5A_Button_5_LED_Red = ((Message.data[4] & 0x40) >> 6);
								HT_3x5A_Button_6_LED_Green = ((Message.data[4] & 0x80) >> 7);

								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x03)
							{
								HT_3x5A_Button_6_LED_Yellow = (Message.data[4] & 0x01);
								HT_3x5A_Button_6_LED_Red = ((Message.data[4] & 0x02) >> 1);
								HT_3x5A_Button_7_LED_Green = ((Message.data[4] & 0x04) >> 2);
								HT_3x5A_Button_7_LED_Yellow = ((Message.data[4] & 0x08) >> 3);
								HT_3x5A_Button_7_LED_Red = ((Message.data[4] & 0x10) >> 4);
								HT_3x5A_Button_8_LED_Green = ((Message.data[4] & 0x20) >> 5);
								HT_3x5A_Button_8_LED_Yellow = ((Message.data[4] & 0x40) >> 6);
								HT_3x5A_Button_8_LED_Red = ((Message.data[4] & 0x80) >> 7);

								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x04)
							{
								HT_3x5A_Button_9_LED_Green = (Message.data[4] & 0x01);
								HT_3x5A_Button_9_LED_Yellow = ((Message.data[4] & 0x02) >> 1);
								HT_3x5A_Button_9_LED_Red = ((Message.data[4] & 0x04) >> 2);
								HT_3x5A_Button_10_LED_Green = ((Message.data[4] & 0x08) >> 3);
								HT_3x5A_Button_10_LED_Yellow = ((Message.data[4] & 0x10) >> 4);
								HT_3x5A_Button_10_LED_Red = ((Message.data[4] & 0x20) >> 5);
								HT_3x5A_Button_11_LED_Green = ((Message.data[4] & 0x40) >> 6);
								HT_3x5A_Button_11_LED_Yellow = ((Message.data[4] & 0x80) >> 7);

								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x05)
							{
								HT_3x5A_Button_11_LED_Red = (Message.data[4] & 0x01);
								HT_3x5A_Button_12_LED_Green = ((Message.data[4] & 0x02) >> 1);
								HT_3x5A_Button_12_LED_Yellow = ((Message.data[4] & 0x04) >> 2);
								HT_3x5A_Button_12_LED_Red = ((Message.data[4] & 0x08) >> 3);
								HT_3x5A_Button_13_LED_Green = ((Message.data[4] & 0x10) >> 4);
								HT_3x5A_Button_13_LED_Yellow = ((Message.data[4] & 0x20) >> 5);
								HT_3x5A_Button_13_LED_Red = ((Message.data[4] & 0x40) >> 6);
								HT_3x5A_Button_14_LED_Green = ((Message.data[4] & 0x80) >> 7);

								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x06)
							{
								HT_3x5A_Button_14_LED_Yellow = (Message.data[4] & 0x01);
								HT_3x5A_Button_14_LED_Red = ((Message.data[4] & 0x02) >> 1);
								HT_3x5A_Button_15_LED_Green = ((Message.data[4] & 0x04) >> 2);
								HT_3x5A_Button_15_LED_Yellow = ((Message.data[4] & 0x08) >> 3);
								HT_3x5A_Button_15_LED_Red = ((Message.data[4] & 0x10) >> 4);

								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x07)
							{
								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x08)
							{
								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
						}

						else if (Service_Data_Object == 0x6411)
						{
							if (sdo_sub_index == 0x01) // LED Brightness
							{
								HT_3x5A_Button_LED_Brightness = Message.data[4];
								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 0x02) // Backlight Brightness
							{
								HT_3x5A_Button_Backlight_Brightness = Message.data[4];
								msg_0x58C_data[0] = 0x60;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = 0x00;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
						}
					}
					else if ((Message.data[0] & 0xF0) == 0x40) // Requesting Read Data...
					{
						if (Service_Data_Object == 0x1018)
						{
							if (sdo_sub_index == 0)
							{
								msg_0x58C_data[0] = 0x4F;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = 0x00;
								msg_0x58C_data[4] = 0x04;
								msg_0x58C_data[5] = 0x00;
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x00;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 1) // Requesting Vendor ID
							{
								msg_0x58C_data[0] = 0x43;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = (uint8_t)(HT_3x5A_Button_Vendor_ID);
								msg_0x58C_data[5] = (uint8_t)(HT_3x5A_Button_Vendor_ID >> 8);
								msg_0x58C_data[6] = (uint8_t)(HT_3x5A_Button_Vendor_ID >> 16);
								msg_0x58C_data[7] = (uint8_t)(HT_3x5A_Button_Vendor_ID >> 24);
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 2) // Requesting Product Code
							{
								msg_0x58C_data[0] = 0x43;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = (uint8_t)(HT_3x5A_Button_Product_Code);
								msg_0x58C_data[5] = (uint8_t)(HT_3x5A_Button_Product_Code >> 8);
								msg_0x58C_data[6] = (uint8_t)(HT_3x5A_Button_Product_Code >> 16);
								msg_0x58C_data[7] = (uint8_t)(HT_3x5A_Button_Product_Code >> 24);
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 3) // Requesting Revision Number
							{
								msg_0x58C_data[0] = 0x43;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = (uint8_t)(HT_3x5A_Button_Revision_Number);
								msg_0x58C_data[5] = (uint8_t)(HT_3x5A_Button_Revision_Number >> 8);
								msg_0x58C_data[6] = (uint8_t)(HT_3x5A_Button_Revision_Number >> 16);
								msg_0x58C_data[7] = (uint8_t)(HT_3x5A_Button_Revision_Number >> 24);
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
							else if (sdo_sub_index == 4) // Requesting Serial Number
							{
								msg_0x58C_data[0] = 0x43;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = (uint8_t)(HT_3x5A_Button_Serial_Number);
								msg_0x58C_data[5] = (uint8_t)(HT_3x5A_Button_Serial_Number >> 8);
								msg_0x58C_data[6] = (uint8_t)(HT_3x5A_Button_Serial_Number >> 16);
								msg_0x58C_data[7] = (uint8_t)(HT_3x5A_Button_Serial_Number >> 24);
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
						}
						else if (Service_Data_Object == 0x1800) // Requesting COB ID (for button presses)
						{
							if (sdo_sub_index == 1)
							{
								msg_0x58C_data[0] = 0x43;
								msg_0x58C_data[1] = (uint8_t)(Service_Data_Object);
								msg_0x58C_data[2] = (uint8_t)(Service_Data_Object >> 8);
								msg_0x58C_data[3] = sdo_sub_index;
								msg_0x58C_data[4] = (uint8_t)(HT_3x5A_Button_COB_ID);
								msg_0x58C_data[5] = (uint8_t)(HT_3x5A_Button_COB_ID >> 8);
								msg_0x58C_data[6] = 0x00;
								msg_0x58C_data[7] = 0x40;
								send_message(HALTECH_CAN, 0, (0x580 + HT_3x5A_Node_ID), 8, msg_0x58C_data);
							}
						}
					}
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
	HT_3x5A_Button_Broadcast_counter++;
	if (HT_3x5A_Button_Broadcast_counter >= HT_3x5A_Button_Broadcast_timeMs)
	{
		HT_3x5A_Button_Broadcast_counter = 0;
		msg_0x18C_data[0] = ((HT_3x5A_Button_1_State) + ((HT_3x5A_Button_2_State) << 1) + ((HT_3x5A_Button_3_State) << 2) + ((HT_3x5A_Button_4_State) << 3) + ((HT_3x5A_Button_5_State) << 4) + ((HT_3x5A_Button_6_State) << 5) + ((HT_3x5A_Button_7_State) << 6) + ((HT_3x5A_Button_8_State) << 7));
		msg_0x18C_data[1] = ((HT_3x5A_Button_9_State) + ((HT_3x5A_Button_10_State) << 1) + ((HT_3x5A_Button_11_State) << 2) + ((HT_3x5A_Button_12_State) << 3) + ((HT_3x5A_Button_13_State) << 4) + ((HT_3x5A_Button_14_State) << 5) + ((HT_3x5A_Button_15_State) << 6));
		msg_0x18C_data[2] = 0;
		// send_message(HALTECH_CAN, 0, (0x180 + HT_3x5A_Node_ID), 3, msg_0x18C_data);
		send_message(HALTECH_CAN, 0, (0x180 + HT_3x5A_Node_ID), 3, msg_0x18C_data_demo);
	}

	HT_3x5A_NMT_counter++;
	if (HT_3x5A_NMT_counter >= HT_3x5A_NMT_Broadcast_timeMs)
	{
		HT_3x5A_NMT_counter = 0;
		msg_0x70C_data[0] = 0x05;
		send_message(HALTECH_CAN, 0, (0x700 + HT_3x5A_Node_ID), 1, msg_0x70C_data);
	}
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
	uint16_t demo = 1 << demo_counter;
	msg_0x18C_data_demo[0] = (uint8_t)(demo);
	msg_0x18C_data_demo[1] = (uint8_t)((demo) >> 8);
	send_message(HALTECH_CAN, 0, (0x180 + HT_3x5A_Node_ID), 3, msg_0x18C_data_demo);
	demo_counter++;
	if (demo_counter >= 15)
	{
		demo_counter = 0;
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
