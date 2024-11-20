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

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* File Define options */


// Uncomment if using Haltech CAN..
#define HALTECH_CAN_ENABLED



#ifdef HALTECH_CAN_ENABLED

// Define which Physical bus HALTECH Devices are on, (Uncomment only 1...)
#define HALTECH_CAN (1 << 0) // Uncomment if you have Haltech devices on CAN 1
//	#define HALTECH_CAN (1 << 1) // Uncomment if you have Haltech devices on CAN 2
//	#define HALTECH_CAN (1 << 2) // Uncomment if you have Haltech devices on CAN 3

// Uncomment if wanting to Emulate Haltech IO Box A..
	#define HALTECH_IO_BOX_B 1






#endif
#ifndef HALTECH_IO_BOX_B
	#define HALTECH_IO_BOX_B 0
#endif

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// Haltech IO Box Variables
	float haltech_IO_Box_B_AVI1 = 0.0f; // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
	float haltech_IO_Box_B_AVI2 = 0.0f; // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
	float haltech_IO_Box_B_AVI3 = 0.0f; // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
	float haltech_IO_Box_B_AVI4 = 0.0f; // min 0.00v, max 5.00v, resolution 0.001221'ish volts (4095 Steps..) //
	float haltech_IO_Box_B_DPI1_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPI2_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPI3_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPI4_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPI1_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPI2_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPI3_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPI4_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPO1_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPO2_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPO3_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DPO4_Duty = 0.0f; // min 0.0%, max 100.0%, resolution 0.1% //
	float haltech_IO_Box_B_DP01_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPO2_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPO3_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	float haltech_IO_Box_B_DPO4_Period = 0.0f; // min 0.00ms, max 50.00ms, resolution 0.01ms //
	uint8_t haltech_IO_Box_B_Status = 1; // 0=In bootmode,1=In firmware,2=Hardware failure,3=Firmware erased,4=Watchdog timeout,5=Illegal op-code //
	uint8_t haltech_IO_Box_B_ID_Conflict = 0; // 0=No Conflict, 1=Conflict //
	uint8_t haltech_IO_Box_B_Bootcode_Version = 31; // min 0, max 31, resolution 1, recommend highest value{31} //
	uint8_t haltech_IO_Box_B_FW_Major_Version = 3; // min 0, max 3, resolution 1, recommend highest value{3} //
	uint8_t haltech_IO_Box_B_FW_Minor_Version = 255; // min 0, max 255, resolution 1, recommend highest value{255} //
	uint8_t haltech_IO_Box_B_FW_Bugfix_Version = 0; // min 0, max 255, resolution 1, currently unaffected by value //
	uint8_t haltech_IO_Box_B_FW_Release_Type = 0; // min 0, max 255, resolution 1, currently unaffected by value //
	uint8_t haltech_IO_Box_B_AVI1_Pullup = 0; // 0=off, 1=on
	uint8_t haltech_IO_Box_B_DPO1_Error = 0; // 0=Inactive, 1=Active
	uint8_t haltech_IO_Box_B_DPO1_Active = 0; // 0=Low, 1=High
	uint8_t haltech_IO_Box_B_AVI2_Pullup = 0; // 0=off, 1=on
	uint8_t haltech_IO_Box_B_DPO2_Error = 0; // 0=Inactive, 1=Active
	uint8_t haltech_IO_Box_B_DPO2_Active = 0; // 0=Low, 1=High
	uint8_t haltech_IO_Box_B_AVI3_Pullup = 0; // 0=off, 1=on
	uint8_t haltech_IO_Box_B_DPO3_Error = 0; // 0=Inactive, 1=Active
	uint8_t haltech_IO_Box_B_DPO3_Active = 0; // 0=Low, 1=High
	uint8_t haltech_IO_Box_B_AVI4_Pullup = 0; // 0=off, 1=on
	uint8_t haltech_IO_Box_B_DPO4_Error = 0; // 0=Inactive, 1=Active
	uint8_t haltech_IO_Box_B_DPO4_Active = 0; // 0=Low, 1=High
// End HALTECH_IO_BOX_B variables

/* End Variable Declarations */

//-----------------------------//
//-----------------------------//
//-----------------------------//


/* Startup Functions */

void events_Startup(){
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

//-----------------------------//
//-----------------------------//
//-----------------------------//

void onSerialReceive(uint8_t *serialMessage){
    // What do you want to do when you receive a UART message.. ?
	//printf("%07.4f message received...\r\n",getTimestamp());

  }

void onReceive(CAN_Message Message){
	// What do you want to do when you receive a CAN message.. ?	
	if (Message.Bus == CAN_1){
		if(HALTECH_CAN == CAN_1){
			if (HALTECH_IO_BOX_B == 1){
				if(Message.arbitration_id == 0x2D1){
					haltech_IO_Box_B_DPI1_Duty = (float)((Message.data[0]<<2) + (Message.data[1]>>6))/10;
					haltech_IO_Box_B_DPO1_Active = (Message.data[1] & 0x20)>>5;
					haltech_IO_Box_B_DPO1_Error = (Message.data[1] & 0x10)>>4;
					haltech_IO_Box_B_AVI1_Pullup = (Message.data[1] & 0x08)>>3;
					haltech_IO_Box_B_DP01_Period = (float)((Message.data[2]<<8)+Message.data[3])/10;
					haltech_IO_Box_B_DPI2_Duty = (float)((Message.data[4]<<2) + (Message.data[5]>>6))/10;
					haltech_IO_Box_B_DPO2_Active = (Message.data[5] & 0x20)>>5;
					haltech_IO_Box_B_DPO2_Error = (Message.data[5] & 0x10)>>4;
					haltech_IO_Box_B_AVI2_Pullup = (Message.data[5] & 0x08)>>3;
					haltech_IO_Box_B_DPO2_Period = (float)((Message.data[6]<<8)+Message.data[7])/10;
				}
				else if(Message.arbitration_id == 0x2D3){
					haltech_IO_Box_B_DPI3_Duty = (float)((Message.data[0]<<2) + (Message.data[1]>>6))/10;
					haltech_IO_Box_B_DPO3_Active = (Message.data[1] & 0x20)>>5;
					haltech_IO_Box_B_DPO3_Error = (Message.data[1] & 0x10)>>4;
					haltech_IO_Box_B_AVI3_Pullup = (Message.data[1] & 0x08)>>3;
					haltech_IO_Box_B_DPO3_Period = (float)((Message.data[2]<<8)+Message.data[3])/10;
					haltech_IO_Box_B_DPI4_Duty = (float)((Message.data[4]<<2) + (Message.data[5]>>6))/10;
					haltech_IO_Box_B_DPO4_Active = (Message.data[5] & 0x20)>>5;
					haltech_IO_Box_B_DPO4_Error = (Message.data[5] & 0x10)>>4;
					haltech_IO_Box_B_AVI4_Pullup = (Message.data[5] & 0x08)>>3;
					haltech_IO_Box_B_DPO4_Period = (float)((Message.data[6]<<8)+Message.data[7])/10;
				}
			}
		}
	}
	if (Message.Bus == CAN_2){
		if(HALTECH_CAN == CAN_2){
			if (HALTECH_IO_BOX_B == 1){
				if(Message.arbitration_id == 0x2D1){
					haltech_IO_Box_B_DPI1_Duty = (float)((Message.data[0]<<2) + (Message.data[1]>>6))/10;
					haltech_IO_Box_B_DPO1_Active = (Message.data[1] & 0x20)>>5;
					haltech_IO_Box_B_DPO1_Error = (Message.data[1] & 0x10)>>4;
					haltech_IO_Box_B_AVI1_Pullup = (Message.data[1] & 0x08)>>3;
					haltech_IO_Box_B_DP01_Period = (float)((Message.data[2]<<8)+Message.data[3])/10;
					haltech_IO_Box_B_DPI2_Duty = (float)((Message.data[4]<<2) + (Message.data[5]>>6))/10;
					haltech_IO_Box_B_DPO2_Active = (Message.data[5] & 0x20)>>5;
					haltech_IO_Box_B_DPO2_Error = (Message.data[5] & 0x10)>>4;
					haltech_IO_Box_B_AVI2_Pullup = (Message.data[5] & 0x08)>>3;
					haltech_IO_Box_B_DPO2_Period = (float)((Message.data[6]<<8)+Message.data[7])/10;
				}
				else if(Message.arbitration_id == 0x2D3){
					haltech_IO_Box_B_DPI3_Duty = (float)((Message.data[0]<<2) + (Message.data[1]>>6))/10;
					haltech_IO_Box_B_DPO3_Active = (Message.data[1] & 0x20)>>5;
					haltech_IO_Box_B_DPO3_Error = (Message.data[1] & 0x10)>>4;
					haltech_IO_Box_B_AVI3_Pullup = (Message.data[1] & 0x08)>>3;
					haltech_IO_Box_B_DPO3_Period = (float)((Message.data[2]<<8)+Message.data[3])/10;
					haltech_IO_Box_B_DPI4_Duty = (float)((Message.data[4]<<2) + (Message.data[5]>>6))/10;
					haltech_IO_Box_B_DPO4_Active = (Message.data[5] & 0x20)>>5;
					haltech_IO_Box_B_DPO4_Error = (Message.data[5] & 0x10)>>4;
					haltech_IO_Box_B_AVI4_Pullup = (Message.data[5] & 0x08)>>3;
					haltech_IO_Box_B_DPO4_Period = (float)((Message.data[6]<<8)+Message.data[7])/10;
				}
			}
		}
	}
	if (Message.Bus == CAN_3){
		if(HALTECH_CAN == CAN_3){
			if (HALTECH_IO_BOX_B == 1){
				if(Message.arbitration_id == 0x2D1){
					haltech_IO_Box_B_DPI1_Duty = (float)((Message.data[0]<<2) + (Message.data[1]>>6))/10;
					haltech_IO_Box_B_DPO1_Active = (Message.data[1] & 0x20)>>5;
					haltech_IO_Box_B_DPO1_Error = (Message.data[1] & 0x10)>>4;
					haltech_IO_Box_B_AVI1_Pullup = (Message.data[1] & 0x08)>>3;
					haltech_IO_Box_B_DP01_Period = (float)((Message.data[2]<<8)+Message.data[3])/10;
					haltech_IO_Box_B_DPI2_Duty = (float)((Message.data[4]<<2) + (Message.data[5]>>6))/10;
					haltech_IO_Box_B_DPO2_Active = (Message.data[5] & 0x20)>>5;
					haltech_IO_Box_B_DPO2_Error = (Message.data[5] & 0x10)>>4;
					haltech_IO_Box_B_AVI2_Pullup = (Message.data[5] & 0x08)>>3;
					haltech_IO_Box_B_DPO2_Period = (float)((Message.data[6]<<8)+Message.data[7])/10;
				}
				else if(Message.arbitration_id == 0x2D3){
					haltech_IO_Box_B_DPI3_Duty = (float)((Message.data[0]<<2) + (Message.data[1]>>6))/10;
					haltech_IO_Box_B_DPO3_Active = (Message.data[1] & 0x20)>>5;
					haltech_IO_Box_B_DPO3_Error = (Message.data[1] & 0x10)>>4;
					haltech_IO_Box_B_AVI3_Pullup = (Message.data[1] & 0x08)>>3;
					haltech_IO_Box_B_DPO3_Period = (float)((Message.data[2]<<8)+Message.data[3])/10;
					haltech_IO_Box_B_DPI4_Duty = (float)((Message.data[4]<<2) + (Message.data[5]>>6))/10;
					haltech_IO_Box_B_DPO4_Active = (Message.data[5] & 0x20)>>5;
					haltech_IO_Box_B_DPO4_Error = (Message.data[5] & 0x10)>>4;
					haltech_IO_Box_B_AVI4_Pullup = (Message.data[5] & 0x08)>>3;
					haltech_IO_Box_B_DPO4_Period = (float)((Message.data[6]<<8)+Message.data[7])/10;
				}
			}
		}
	}
}

/* Run 2000Hz Functions here */
void events_2000Hz(){
	
}

/* Run 1000Hz Functions here */
void events_1000Hz(){

}

/* Run 500Hz Functions here */
void events_500Hz(){

}

/* Run 200Hz Functions here */
void events_200Hz(){

}

/* Run 100Hz Functions here */
void events_100Hz(){

}

/* Run 50Hz Functions here */
void events_50Hz(){
	
	if(HALTECH_IO_BOX_B == 1){
		uint16_t ioBB_AVI1 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_B_AVI1*5/4095,0);
		uint16_t ioBB_AVI2 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_B_AVI2*5/4095,0);
		uint16_t ioBB_AVI3 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_B_AVI1*5/4095,0);
		uint16_t ioBB_AVI4 = (uint16_t)roundfloat_to_int32(haltech_IO_Box_B_AVI1*5/4095,0);
		uint8_t msgIOBB_1[8] = {(uint8_t) ioBB_AVI1 >> 8, (uint8_t) ioBB_AVI1, (uint8_t) ioBB_AVI2 >> 8, (uint8_t) ioBB_AVI2, (uint8_t) ioBB_AVI3 >> 8, (uint8_t) ioBB_AVI3, (uint8_t) ioBB_AVI4 >> 8, (uint8_t) ioBB_AVI4};
		send_message(HALTECH_CAN,false,0x2C0,8,msgIOBB_1);

		uint16_t ioBB_DPI1_DC = (uint16_t)roundfloat(haltech_IO_Box_B_DPI1_Duty,1);
		uint16_t ioBB_DPI1_Period = (uint16_t)roundfloat(haltech_IO_Box_B_DPI1_Period,2);
		uint16_t ioBB_DPI2_DC = (uint16_t)roundfloat(haltech_IO_Box_B_DPI2_Duty,1);
		uint16_t ioBB_DPI2_Period = (uint16_t)roundfloat(haltech_IO_Box_B_DPI2_Period,2);
		uint8_t msgIOBB_2[8] = {(uint8_t)(ioBB_DPI1_DC>>2), (uint8_t)((ioBB_DPI1_DC& 0x03)<<6),(uint8_t)(ioBB_DPI1_Period>>8),(uint8_t)(ioBB_DPI1_Period), (uint8_t)(ioBB_DPI2_DC>>2), (uint8_t)((ioBB_DPI2_DC& 0x03)<<6),(uint8_t)(ioBB_DPI2_Period>>8),(uint8_t)(ioBB_DPI2_Period)};
		send_message(HALTECH_CAN,false,0x2C2,8,msgIOBB_2);

		uint16_t ioBB_DPI3_DC = (uint16_t)roundfloat(haltech_IO_Box_B_DPI3_Duty,1);
		uint16_t ioBB_DPI3_Period = (uint16_t)roundfloat(haltech_IO_Box_B_DPI3_Period,2);
		uint16_t ioBB_DPI4_DC = (uint16_t)roundfloat(haltech_IO_Box_B_DPI4_Duty,1);
		uint16_t ioBB_DPI4_Period = (uint16_t)roundfloat(haltech_IO_Box_B_DPI4_Period,2);
		uint8_t msgIOBB_3[8] = {(uint8_t)(ioBB_DPI3_DC>>2), (uint8_t)((ioBB_DPI3_DC& 0x03)<<6),(uint8_t)(ioBB_DPI3_Period>>8),(uint8_t)(ioBB_DPI3_Period), (uint8_t)(ioBB_DPI4_DC>>2), (uint8_t)((ioBB_DPI4_DC& 0x03)<<6),(uint8_t)(ioBB_DPI4_Period>>8),(uint8_t)(ioBB_DPI4_Period)};
		send_message(HALTECH_CAN,false,0x2C4,8,msgIOBB_3);

		uint8_t msgIOBB_4[8] = {(uint8_t)((haltech_IO_Box_B_Status<<4) + haltech_IO_Box_B_ID_Conflict),(uint8_t)((haltech_IO_Box_B_Bootcode_Version<<2) + haltech_IO_Box_B_FW_Major_Version),haltech_IO_Box_B_FW_Minor_Version, haltech_IO_Box_B_FW_Bugfix_Version, haltech_IO_Box_B_FW_Release_Type,0,0,0};
		send_message(HALTECH_CAN,false,0x2C6,8,msgIOBB_4);
	}

}

/* Run 20Hz Functions here */
void events_20Hz(){
	
}

/* Run 10Hz Functions here */
void events_10Hz(){

}

/* Run 5Hz Functions here */
void events_5Hz(){
	toggleLED(LED_1);

}

/* Run 2Hz Functions here */
void events_2Hz(){

}

/* Run 1Hz Functions here */
void events_1Hz(){
	
}




// #defines Management

// Validation logic for HALTECH_CAN
#if defined(HALTECH_CAN_ENABLED)
    #if !defined(HALTECH_CAN)
        #error "HALTECH_CAN must be defined as 1 (CAN_1), 2 (CAN_2), or 4 (CAN_3)."
    #elif (HALTECH_CAN != 1 && HALTECH_CAN != 2 && HALTECH_CAN != 4)
        #error "HALTECH_CAN must be one of 1 (CAN_1), 2 (CAN_2), or 4 (CAN_3)."
    #endif
#endif