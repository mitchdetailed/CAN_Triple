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
uint8_t example_data_1Hz[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint32_t serialnumber = 0;
uint16_t test_rpm = 500;
char test_rpm_unit[8] = "§RPM";
bool increment_rpm = true;
float testvalue;
CAN_ErrorCounts errors;



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
	serialnumber = getSerialNumber();

}
/* End Startup Functions */


void onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
		char bufferCAN1[32];
		//send_message(CAN_2, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
		float test = getTimestamp();
		snprintf(bufferCAN1,sizeof(bufferCAN1),"Timestamp = %.4f\r\n",test);
		serialPrint(bufferCAN1);
	}
	if (Message.Bus == CAN_2){
		//send_message(CAN_3, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_3){
		//send_message(CAN_1, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
				
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
	
}

/* Run 20Hz Functions here */
void events_20Hz(){
	
}

/* Run 10Hz Functions here */
void events_10Hz(){
	toggleLED(LED_1);
	//serialPrint("LED Toggled...\r\n");
}

/* Run 5Hz Functions here */
void events_5Hz(){

	//errors = getCANErrorCounts(CAN_1);
	//char buffer1[200];
	//snprintf(buffer1, sizeof(buffer1), "CAN1 Resets: %3u, CAN 1 Rx err : %3u, Tx err : %3u\r\n", errors.BusResetCounter, errors.RxErrorCounter, errors.TxErrorCounter);
	//serialPrint(buffer1);

	//float ts = getTimestamp();
	//snprintf(buffer1, sizeof(buffer1), "Counter value = %.4f\r\n",ts);
	//serialPrint(buffer1);
}

/* Run 2Hz Functions here */
void events_2Hz(){

}

/* Run 1Hz Functions here */
void events_1Hz(){
	send_message(CAN_1, false, 0x001, 8, example_data_1Hz);
	//send_message(CAN_2, false, 0x002, 8, example_data_1Hz);
	//send_message(CAN_3, false, 0x003, 8, example_data_1Hz);
}
