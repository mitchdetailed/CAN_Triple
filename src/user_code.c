/*
 * user_code.c - All Code should be applied here unless specified otherwise.
 */

/* File Includes */
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"
#include <stdio.h>

/* End File Includes */
extern UART_HandleTypeDef huart1;

/* Variable Declarations */
uint8_t example_data_1Hz[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint32_t serial = 0;

/* End Variable Declarations */

/* Startup Functions */
void events_Startup(){
	setCANBitrate(CAN_1, 1000000);
	setCANBitrate(CAN_2, 1000000);
	setCANBitrate(CAN_3, 1000000);
	setCAN_Termination(CAN_1,true);
	setCAN_Termination(CAN_2, true);
	setCAN_Termination(CAN_3, true);
	startCANbus(CAN_1);
	startCANbus(CAN_2);
	startCANbus(CAN_3);
	serial = getSerialNumber();


}
/* End Startup Functions */


void onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
		send_message(CAN_2, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_2){
		send_message(CAN_3, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_3){
		send_message(CAN_1, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
				
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
}

/* Run 5Hz Functions here */
void events_5Hz(){

}

/* Run 2Hz Functions here */
void events_2Hz(){
	
}

/* Run 1Hz Functions here */
void events_1Hz(){
	send_message(CAN_1, false, 0x001, 8, example_data_1Hz);
	send_message(CAN_2, false, 0x002, 8, example_data_1Hz);
	send_message(CAN_3, false, 0x003, 8, example_data_1Hz);
	for (uint8_t i=0; i<8; i++){
		example_data_1Hz[i]++;
	}
    float string1 = 3.141592 ;

	printf("testing %2.6f !\r\n", string1);

}
