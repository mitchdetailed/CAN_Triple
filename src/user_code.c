/*
 * user_code.c
 */

/* File Includes */
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"

/* End File Includes */


/* Variable Declarations */
uint32_t serialnumber;
uint8_t example_data_1Hz[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint8_t rdp_Level = 0;
uint32_t flashbaseaddr = 0x0800F800; // Start Address of last page of memory

/* End Variable Declarations */

/* Startup Functions */
void events_Startup(){
	setCANBitrate(CAN_1,  500000);
	setCANBitrate(CAN_2,  250000);
	setCANBitrate(CAN_3, 1000000);
	//setCAN_Termination(CAN_1, false);
	setCAN_Termination(CAN_1,true);
	setCAN_Termination(CAN_2, true);
	setCAN_Termination(CAN_3, false);
	startCANbus(CAN_1);
	startCANbus(CAN_2);
	//startCANbus(CAN_3);
}

/* When a CAN Message is Received.... */
void onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
		add_to_CAN_TX_Queue(CAN_2, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_2){
		//add_to_CAN_TX_Queue(CAN_Channel_1, EXT_ID, ID, DLC, Data);
		// do nothing
	}
	if (Message.Bus == CAN_3){
		// Do Nothing...
				

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
	toggleLED(LED_1);
}

/* Run 20Hz Functions here */
void events_20Hz(){
	
}

/* Run 10Hz Functions here */
void events_10Hz(){
	
}

/* Run 5Hz Functions here */
void events_5Hz(){

}

/* Run 2Hz Functions here */
void events_2Hz(){

}

/* Run 1Hz Functions here */
void events_1Hz(){
	//serialnumber = getSerialNumber();
	//add_to_CAN_TX_Queue(0b111, false, 0x7FF, 8, example_data_1Hz);
	//for (uint8_t i=0; i<8; i++){
	//	example_data_1Hz[i]++;
	//}

}
