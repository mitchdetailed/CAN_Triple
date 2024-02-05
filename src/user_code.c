/*
 * user_code.c
 */

#include "user_code.h"
#include "backend_functions.h"
#include "main.h"

uint32_t serialnumber;
uint8_t example_data_1hz[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint8_t rdp_Level = 0;
uint32_t flashbaseaddr = 0x0800F800; // Start Address of last page of memory

void xStartup_Function(){
// Run Startup Functions here
	setCANBitrate(1, 1000000);
	setCANBitrate(2, 1000000);
	setCANBitrate(3, 1000000);
	setCAN_Termination(1, true);
	setCAN_Termination(2, true);
	setCAN_Termination(3, true);
	startCANbus(1);
	startCANbus(2);
	startCANbus(3);
}

void onReceive(uint8_t busChannel, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t Data[8]){
	if (busChannel == 1){

				add_to_CAN_TX_Queue(0b0100, EXT_ID, ID, DLC, Data);
	}
	if (busChannel == 2){

	}
	if (busChannel == 3){
				add_to_CAN_TX_Queue(0b0001, EXT_ID, ID, DLC, Data);
	}
}


void x2000hz_Function(){
// Run 2000Hz Functions here

}

void x1000hz_Function(){
// Run 1000Hz Functions here

}

void x500hz_Function(){
// Run 500Hz Functions here

}

void x200hz_Function(){
// Run 200Hz Functions here

}

void x100hz_Function(){
// Run 100Hz Functions here

}

void x50hz_Function(){
// Run 50Hz Functions here

}

void x20hz_Function(){
// Run 20Hz Functions here
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	
}

void x10hz_Function(){
// Run 10Hz Functions here
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
}

void x5hz_Function(){
// Run 5Hz Functions here

}

void x2hz_Function(){
// Run 2Hz Functions here

}

void x1hz_Function(){
// Run 1Hz Functions here
	serialnumber = getSerialNumber();
	add_to_CAN_TX_Queue(0b111, false, 0x7FF, 8, example_data_1hz);
	for (uint8_t i=0; i<8; i++){
		example_data_1hz[i]++;
	}
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);

}

void xShutdown_Function(){
	//writeFlash(31, example_data_1hz, 8);
	//add2_CAN_TX_Queue(0b0001, false, 0x100, 8, example_data_1hz);
	
}