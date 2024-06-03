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
	setCAN_Termination(CAN_1, false);
	setCAN_Termination(CAN_2, false);
	setCAN_Termination(CAN_3, false);
	startCANbus(CAN_1);
	startCANbus(CAN_2);
	startCANbus(CAN_3);
	serialnumber = getSerialNumber();

}
/* End Startup Functions */


void onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
		//send_message(CAN_2, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
		float test = getTimestamp();
		printf(" Timestamp = %11.4f\r\n",test);
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
	for (uint8_t i = 0; i< 15; i++){
		//char buffer1[100];
		//snprintf(buffer1, 100, "(123.456789) can0 12345678#%02x34567890123456\r\n", i);
		//serialPrint(buffer1);
	}

}

/* Run 500Hz Functions here */
void events_500Hz(){
	send_message(CAN_1, false, 0x061, 8, example_data_1Hz);
}

/* Run 200Hz Functions here */
void events_200Hz(){

}

/* Run 100Hz Functions here */
void events_100Hz(){

}

/* Run 50Hz Functions here */
void events_50Hz(){
	if (increment_rpm == true){
		test_rpm+=5;
		if (test_rpm > 9900){
			increment_rpm = false;
		}
	}
	else{
		test_rpm-=5;
		if(test_rpm < 500){
			increment_rpm = true;
		}
	}

	
}

/* Run 20Hz Functions here */
void events_20Hz(){
	//printf(">Engine Speed:%04d %s\r\n", test_rpm, test_rpm_unit);

	
}

/* Run 10Hz Functions here */
void events_10Hz(){
	toggleLED(LED_1);
	//serialPrint("LED Toggled...\r\n");
	//serialPrint("Testing pushing 2 strings\r\n");

}

/* Run 5Hz Functions here */
void events_5Hz(){

	errors = getCANErrorCounts(CAN_1);
	char buffer1[200];
	float ts = getTimestamp();
	//snprintf(buffer1, sizeof(buffer1), "CAN1 Resets: %3u, CAN 1 Rx err : %3u, Tx err : %3u\r\n", errors.BusResetCounter, errors.RxErrorCounter, errors.TxErrorCounter);
	//serialPrint(buffer1);
	//uint32_t counter_value = __HAL_TIM_GET_COUNTER(&htim2); // Direct register access
	//uint32_t counter_value = ((&htim2)->Instance->CNT); // Direct register access
	snprintf(buffer1, sizeof(buffer1), "Counter value = %.4f\r\n",ts);
	serialPrint(buffer1);
}

/* Run 2Hz Functions here */
void events_2Hz(){

}

/* Run 1Hz Functions here */
void events_1Hz(){
	send_message(CAN_1, false, 0x001, 8, example_data_1Hz);
	send_message(CAN_1, false, 0x021, 8, example_data_1Hz);
	send_message(CAN_1, false, 0x041, 8, example_data_1Hz);

	//send_message(CAN_2, false, 0x002, 8, example_data_1Hz);
	//send_message(CAN_3, false, 0x003, 8, example_data_1Hz);
	for (uint8_t i=0; i<8; i++){
		example_data_1Hz[i]++;
	}
	float testfloat = 1.234567;
	char buffer[16];
    snprintf(buffer, sizeof(buffer), "%3.6f\r\n", testfloat);
	//sprintf(buffer, "%3.9f\r\n", testfloat);
	//serialPrint(buffer);
	//printf("Hello World..\r\n");
	//uint8_t u8Decimal = 123 ;
    //float floatval = 3.141592 ;
	//uint8_t hw[13] = "Hello World!"; // Make sure there's 1 + total length of string for the buffer to NULL Terminate.
	//printf("This is my float: %2.6f, this is my u8 %u, %s\r\n", floatval, u8Decimal, hw);
	//HAL_UART_Transmit_DMA(&huart1, )
	//serialPrint("Hello World\r\n");
}
