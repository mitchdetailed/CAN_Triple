/*
 * backend_functions.c
 *
 */







#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"

extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;

struct q_CAN_Msg
{
	bool EXT_ID;
	uint32_t arb_id;
	uint8_t dlc;
	uint8_t data[8];
};

// CAN RX Queue
uint8_t can1_Rx_qHead = 0;
uint8_t can1_Rx_qTail = 0;
struct q_CAN_Msg can1_Rx_qData[BUFFER_SIZE];
uint8_t can1_Rx_qNextHead = 0;
uint8_t can1_Rx_qElements = 0;

// CAN 1 TX Queue
uint8_t can1_Tx_qHead = 0;
uint8_t can1_Tx_qTail = 0;
struct q_CAN_Msg can1_Tx_qData[BUFFER_SIZE];
uint8_t can1_Tx_qNextHead = 0;
uint8_t can1_Tx_qElements = 0;

// CAN 2 RX Queue
uint8_t can2_Rx_qHead = 0;
uint8_t can2_Rx_qTail = 0;
struct q_CAN_Msg can2_Rx_qData[BUFFER_SIZE];
uint8_t can2_Rx_qNextHead = 0;
uint8_t can2_Rx_qElements = 0;

// CAN 2 TX Queue
uint8_t can2_Tx_qHead = 0;
uint8_t can2_Tx_qTail = 0;
struct q_CAN_Msg can2_Tx_qData[BUFFER_SIZE];
uint8_t can2_Tx_qNextHead = 0;
uint8_t can2_Tx_qElements = 0;

// CAN 3 RX Queue
uint8_t can3_Rx_qHead = 0;
uint8_t can3_Rx_qTail = 0;
struct q_CAN_Msg can3_Rx_qData[BUFFER_SIZE];
uint8_t can3_Rx_qNextHead = 0;
uint8_t can3_Rx_qElements = 0;

// CAN 3 TX Queue
uint8_t can3_Tx_qHead = 0;
uint8_t can3_Tx_qTail = 0;
struct q_CAN_Msg can3_Tx_qData[BUFFER_SIZE];
uint8_t can3_Tx_qNextHead = 0;
uint8_t can3_Tx_qElements = 0;

bool Can1_RxMsgEXT_ID;
uint32_t Can1_RxMsgID;
uint8_t Can1_RxMsgDLC;
uint8_t Can1_RxMsgData[8];

bool Can2_RxMsgEXT_ID;
uint32_t Can2_RxMsgID;
uint8_t Can2_RxMsgDLC;
uint8_t Can2_RxMsgData[8];

bool Can3_RxMsgEXT_ID;
uint32_t Can3_RxMsgID;
uint8_t Can3_RxMsgDLC;
uint8_t Can3_RxMsgData[8];

FDCAN_RxHeaderTypeDef CAN1_RxHeader;
uint8_t CAN1_RxData[8];
FDCAN_TxHeaderTypeDef CAN1_TxHeader;
uint8_t CAN1_TxData[8];

FDCAN_RxHeaderTypeDef CAN2_RxHeader;
uint8_t CAN2_RxData[8];
FDCAN_TxHeaderTypeDef CAN2_TxHeader;
uint8_t CAN2_TxData[8];

FDCAN_RxHeaderTypeDef CAN3_RxHeader;
uint8_t CAN3_RxData[8];
FDCAN_TxHeaderTypeDef CAN3_TxHeader;
uint8_t CAN3_TxData[8];

bool storecompleted = false;



/* Sets CANbus Bitrate. 1M,500k,250k,125k validated */
uint8_t setCANBitrate(uint8_t busChannel, uint32_t mainBitrate){
	uint32_t apb1clock = HAL_RCC_GetPCLK1Freq();
	uint32_t prescaler = apb1clock/(mainBitrate*17);

	if (busChannel == 1){
		hfdcan1.Instance = FDCAN1;
		hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
		hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
		hfdcan1.Init.AutoRetransmission = ENABLE;
		hfdcan1.Init.TransmitPause = ENABLE;
		hfdcan1.Init.ProtocolException = DISABLE;
		hfdcan1.Init.NominalPrescaler = prescaler;
		hfdcan1.Init.NominalSyncJumpWidth = 1;
		hfdcan1.Init.NominalTimeSeg1 = 14;
		hfdcan1.Init.NominalTimeSeg2 = 2;
		hfdcan1.Init.DataPrescaler = 10;
		hfdcan1.Init.DataSyncJumpWidth = 1;
		hfdcan1.Init.DataTimeSeg1 = 13;
		hfdcan1.Init.DataTimeSeg2 = 2;
		hfdcan1.Init.StdFiltersNbr = 0;
		hfdcan1.Init.ExtFiltersNbr = 0;
		hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK){
		    Error_Handler();
		}
		return 0;
	}
	else if (busChannel == 2){
		hfdcan2.Instance = FDCAN2;
		hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
		hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
		hfdcan2.Init.AutoRetransmission = ENABLE;
		hfdcan2.Init.TransmitPause = ENABLE;
		hfdcan2.Init.ProtocolException = DISABLE;
		hfdcan2.Init.NominalPrescaler = prescaler;
		hfdcan2.Init.NominalSyncJumpWidth = 1;
		hfdcan2.Init.NominalTimeSeg1 = 14;
		hfdcan2.Init.NominalTimeSeg2 = 2;
		hfdcan2.Init.DataPrescaler = 10;
		hfdcan2.Init.DataSyncJumpWidth = 1;
		hfdcan2.Init.DataTimeSeg1 = 13;
		hfdcan2.Init.DataTimeSeg2 = 2;
		hfdcan2.Init.StdFiltersNbr = 0;
		hfdcan2.Init.ExtFiltersNbr = 0;
		hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK){
		    Error_Handler();
		}
		return 0;
	}
	else if (busChannel == 3){
		hfdcan3.Instance = FDCAN3;
		hfdcan3.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan3.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
		hfdcan3.Init.Mode = FDCAN_MODE_NORMAL;
		hfdcan3.Init.AutoRetransmission = ENABLE;
		hfdcan3.Init.TransmitPause = ENABLE;
		hfdcan3.Init.ProtocolException = DISABLE;
		hfdcan3.Init.NominalPrescaler = prescaler;
		hfdcan3.Init.NominalSyncJumpWidth = 1;
		hfdcan3.Init.NominalTimeSeg1 = 14;
		hfdcan3.Init.NominalTimeSeg2 = 2;
		hfdcan3.Init.DataPrescaler = 10;
		hfdcan3.Init.DataSyncJumpWidth = 1;
		hfdcan3.Init.DataTimeSeg1 = 13;
		hfdcan3.Init.DataTimeSeg2 = 2;
		hfdcan3.Init.StdFiltersNbr = 0;
		hfdcan3.Init.ExtFiltersNbr = 0;
		hfdcan3.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan3) != HAL_OK){
		    Error_Handler();
		}
		return 0;
	}
return -1;
}

/* Start CAN Bus */
uint8_t startCANbus(uint8_t busChannel){

		// Unused filter //

		/*  FDCAN_FilterTypeDef sFilterConfig;
		**  sFilterConfig.IdType = FDCAN_STANDARD_ID;
		**  sFilterConfig.FilterIndex = 0;
		**  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
		**  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
		**  sFilterConfig.FilterID1 = 0x321;
		**  sFilterConfig.FilterID2 = 0x7FF;
		**  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
		**  {
		**    Error_Handler();
		**  }
		*/
	if (busChannel == 1){
		if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK){
			Error_Handler();
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_ERROR_PASSIVE | FDCAN_IT_ERROR_LOGGING_OVERFLOW | FDCAN_IT_DATA_PROTOCOL_ERROR | FDCAN_IT_ARB_PROTOCOL_ERROR | FDCAN_IT_BUS_OFF | FDCAN_IT_ERROR_WARNING | FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2) != HAL_OK){
			Error_Handler();
		}
		/* Start the FDCAN module */
		if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK){
			Error_Handler();
		}
		return 0;
	}
	else if (busChannel == 2){
		if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK){
			Error_Handler();
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_ERROR_PASSIVE | FDCAN_IT_ERROR_LOGGING_OVERFLOW | FDCAN_IT_DATA_PROTOCOL_ERROR | FDCAN_IT_ARB_PROTOCOL_ERROR | FDCAN_IT_BUS_OFF | FDCAN_IT_ERROR_WARNING | FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2) != HAL_OK){
			Error_Handler();
		}
		/* Start the FDCAN module */
		if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK){
			Error_Handler();
		}
		return 0;
	}
	else if (busChannel == 3){
		if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK){
			Error_Handler();
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_ERROR_PASSIVE | FDCAN_IT_ERROR_LOGGING_OVERFLOW | FDCAN_IT_DATA_PROTOCOL_ERROR | FDCAN_IT_ARB_PROTOCOL_ERROR | FDCAN_IT_BUS_OFF | FDCAN_IT_ERROR_WARNING | FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2) != HAL_OK){
			Error_Handler();
		}
		/* Start the FDCAN module */
		if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK){
			Error_Handler();
		}
		return 0;
	}
	return -1;
}


/* Stop CAN Bus */
uint8_t stopCANbus(uint8_t busChannel){

		// Unused filter //

		/*  FDCAN_FilterTypeDef sFilterConfig;
		**  sFilterConfig.IdType = FDCAN_STANDARD_ID;
		**  sFilterConfig.FilterIndex = 0;
		**  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
		**  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
		**  sFilterConfig.FilterID1 = 0x321;
		**  sFilterConfig.FilterID2 = 0x7FF;
		**  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
		**  {
		**    Error_Handler();
		**  }
		*/
	if (busChannel == 1){
		if (HAL_FDCAN_Stop(&hfdcan1) != HAL_OK){
			Error_Handler();
		}
		return 0;
	}
	else if (busChannel == 2){
		if (HAL_FDCAN_Stop(&hfdcan2) != HAL_OK){
			Error_Handler();
		}
		return 0;
	}
	else if (busChannel == 3){
		if (HAL_FDCAN_Stop(&hfdcan3) != HAL_OK){
			Error_Handler();
		}
		return 0;
	}
	return -1;
}

/* Set/Reset CAN Termination */
uint8_t setCAN_Termination(uint8_t busChannel, bool activated){
	if (busChannel == 1){
		if (activated == true){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
		}
		return 0;
	}
	else if (busChannel == 2){
		if (activated == true){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);
		}
		return 0;
	}
	else if (busChannel == 3){
		if (activated == true){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
		}
		else{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
		}
		return 0;
	}
	return -1;
}

/* Interrupt Service Routine for Rx Messages */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs){
	if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0){
		/* Retrieve Rx messages from RX FIFO0 */
		if (hfdcan->Instance == FDCAN1){
			if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &CAN1_RxHeader, CAN1_RxData) != HAL_OK){
				Error_Handler();
			}

			bool Callback_Rx_ID_Type;
			uint32_t Callback_Rx_ID;
			uint8_t Callback_Rx_DLC;

			if (CAN1_RxHeader.IdType == FDCAN_EXTENDED_ID){
				Callback_Rx_ID_Type = true;
			}
			else{
				Callback_Rx_ID_Type = false;
			}
			Callback_Rx_ID = CAN1_RxHeader.Identifier;
			Callback_Rx_DLC = (CAN1_RxHeader.DataLength >> 16 & 0x0F);
			if (Callback_Rx_DLC > 8){
				Callback_Rx_DLC = 8;
			}
			add_to_CAN_RX_Queue(1, Callback_Rx_ID_Type, Callback_Rx_ID, Callback_Rx_DLC, CAN1_RxData);

		}
		if (hfdcan->Instance == FDCAN2){
			if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO0, &CAN2_RxHeader, CAN2_RxData) != HAL_OK){
				Error_Handler();
			}

			bool Callback_Rx_ID_Type;
			uint32_t Callback_Rx_ID;
			uint8_t Callback_Rx_DLC;

			if (CAN2_RxHeader.IdType == FDCAN_EXTENDED_ID){
				Callback_Rx_ID_Type = true;
			}
			else{
				Callback_Rx_ID_Type = false;
			}
			Callback_Rx_ID = CAN2_RxHeader.Identifier;
			Callback_Rx_DLC = (CAN2_RxHeader.DataLength >> 16 & 0x0F);
			if (Callback_Rx_DLC > 8){
				Callback_Rx_DLC = 8;
			}
			add_to_CAN_RX_Queue(2, Callback_Rx_ID_Type, Callback_Rx_ID, Callback_Rx_DLC, CAN2_RxData);
		}
		if (hfdcan->Instance == FDCAN3){
			if (HAL_FDCAN_GetRxMessage(&hfdcan3, FDCAN_RX_FIFO0, &CAN3_RxHeader, CAN3_RxData) != HAL_OK){
				Error_Handler();
			}

			bool Callback_Rx_ID_Type;
			uint32_t Callback_Rx_ID;
			uint8_t Callback_Rx_DLC;

			if (CAN3_RxHeader.IdType == FDCAN_EXTENDED_ID){
				Callback_Rx_ID_Type = true;
			}
			else{
				Callback_Rx_ID_Type = false;
			}
			Callback_Rx_ID = CAN3_RxHeader.Identifier;
			Callback_Rx_DLC = (CAN3_RxHeader.DataLength >> 16 & 0x0F);
			if (Callback_Rx_DLC > 8){
				Callback_Rx_DLC = 8;
			}
			add_to_CAN_RX_Queue(3, Callback_Rx_ID_Type, Callback_Rx_ID, Callback_Rx_DLC, CAN3_RxData);
		}
	}
}

/* Interrupt Service Routine for Successfully Transmitting Messages.. */
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes){
	if (hfdcan->Instance == FDCAN1){

	}
	if (hfdcan->Instance == FDCAN2){

	}
	if (hfdcan->Instance == FDCAN3){

	}
}

/* Add to CAN Receive Queue*/
uint8_t add_to_CAN_RX_Queue(uint8_t enum_busChannel, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t rxData[8]){
	uint8_t return_val = 0;
	if((enum_busChannel & 0x01) == 0x01){
		can1_Rx_qNextHead = (can1_Rx_qHead + 1) & 0xFF;
		/*  if there is room */
		if (can1_Rx_qNextHead != can1_Rx_qTail){
			can1_Rx_qData[can1_Rx_qHead].EXT_ID = EXT_ID;
			can1_Rx_qData[can1_Rx_qHead].arb_id = ID;
			can1_Rx_qData[can1_Rx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++){
				can1_Rx_qData[can1_Rx_qHead].data[i] = rxData[i];
			}
			can1_Rx_qHead = can1_Rx_qNextHead;
			can1_Rx_qElements ++;
		return_val += 0;
		}
		else{
		/* no room left in the buffer */
			return_val -= 1;
		}
	}
	if ((enum_busChannel & 0x02) == 0x02){
		can2_Rx_qNextHead = (can2_Rx_qHead + 1) & 0xFF;
		/*  if there is room */
		if (can2_Rx_qNextHead != can2_Rx_qTail){
			can2_Rx_qData[can2_Rx_qHead].EXT_ID = EXT_ID;
			can2_Rx_qData[can2_Rx_qHead].arb_id = ID;
			can2_Rx_qData[can2_Rx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++){
				can2_Rx_qData[can2_Rx_qHead].data[i] = rxData[i];
			}
			can2_Rx_qHead = can2_Rx_qNextHead;
			can2_Rx_qElements ++;
			return_val += 0;
		}
		else{
			/* no room left in the buffer */
		return_val -= 2;
		}
	}
	if ((enum_busChannel & 0x04) == 0x04){
		can3_Rx_qNextHead = (can3_Rx_qHead + 1) & 0xFF;
		/*  if there is room */
		if (can3_Rx_qNextHead != can3_Rx_qTail){
			can3_Rx_qData[can3_Rx_qHead].EXT_ID = EXT_ID;
			can3_Rx_qData[can3_Rx_qHead].arb_id = ID;
			can3_Rx_qData[can3_Rx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++){
				can3_Rx_qData[can3_Rx_qHead].data[i] = rxData[i];
			}
			can3_Rx_qHead = can3_Rx_qNextHead;
			can3_Rx_qElements ++;
			return_val += 0;
		}
		else{
			/* no room left in the buffer */
		return_val -= 4;
		}
	}
	return return_val;
}

/* Add to CAN Transmit Queue*/
uint8_t add_to_CAN_TX_Queue(uint8_t enum_busChannel, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t Data[8]){
	uint8_t return_val = 0;
	if((enum_busChannel & 0x01) == 0x01){
		can1_Tx_qNextHead = (can1_Tx_qHead + 1) & 0xFF;
		/*  if there is room */
		if (can1_Tx_qNextHead != can1_Tx_qTail){
			can1_Tx_qData[can1_Tx_qHead].EXT_ID = EXT_ID;
			can1_Tx_qData[can1_Tx_qHead].arb_id = ID;
			can1_Tx_qData[can1_Tx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++){
				can1_Tx_qData[can1_Tx_qHead].data[i] = Data[i];
			}
			can1_Tx_qHead = can1_Tx_qNextHead;
			can1_Tx_qElements ++;
		return_val += 0;
		}
		else{
		/* no room left in the buffer */
			return_val -= 1;
		}
	}
	if ((enum_busChannel & 0x02) == 0x02){
		can2_Tx_qNextHead = (can2_Tx_qHead + 1) & 0xFF;
		/*  if there is room */
		if (can2_Tx_qNextHead != can2_Tx_qTail){
			can2_Tx_qData[can2_Tx_qHead].EXT_ID = EXT_ID;
			can2_Tx_qData[can2_Tx_qHead].arb_id = ID;
			can2_Tx_qData[can2_Tx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++){
				can2_Tx_qData[can2_Tx_qHead].data[i] = Data[i];
			}
			can2_Tx_qHead = can2_Tx_qNextHead;
			can2_Tx_qElements ++;
			return_val += 0;
		}
		else{
			/* no room left in the buffer */
		return_val -= 2;
		}
	}
	if ((enum_busChannel & 0x04) == 0x04){
		can3_Tx_qNextHead = (can3_Tx_qHead + 1) & 0xFF;
		/*  if there is room */
		if (can3_Tx_qNextHead != can3_Tx_qTail){
			can3_Tx_qData[can3_Tx_qHead].EXT_ID = EXT_ID;
			can3_Tx_qData[can3_Tx_qHead].arb_id = ID;
			can3_Tx_qData[can3_Tx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++){
				can3_Tx_qData[can3_Tx_qHead].data[i] = Data[i];
			}
			can3_Tx_qHead = can3_Tx_qNextHead;
			can3_Tx_qElements ++;
			return_val += 0;
		}
		else{
			/* no room left in the buffer */
		return_val -= 4;
		}
	}
	return return_val;
}

/* Callback for Received Messages for OnReceive Function*/
void trigger_CAN_RX(){
	while (can1_Rx_qElements > 0){
		if (can1_Rx_qData[can1_Rx_qTail].EXT_ID == true){
			Can1_RxMsgEXT_ID = true;
		}
		else{
			Can1_RxMsgEXT_ID = false;
		}
		Can1_RxMsgID = can1_Rx_qData[can1_Rx_qTail].arb_id;
		Can1_RxMsgDLC = can1_Rx_qData[can1_Rx_qTail].dlc;
		for (uint8_t i = 0; i < 8; i++){
			Can1_RxMsgData[i] = can1_Rx_qData[can1_Rx_qTail].data[i];
		}
		can1_Rx_qTail = (can1_Rx_qTail + 1) & 0xFF;
		can1_Rx_qElements--;
		/* */ // Do things with the  Can 1 Messages here....
		onReceive(1,Can1_RxMsgEXT_ID,Can1_RxMsgID,Can1_RxMsgDLC,Can1_RxMsgData );

	}
	while (can2_Rx_qElements > 0){
		if (can2_Rx_qData[can2_Rx_qTail].EXT_ID == true){
			Can2_RxMsgEXT_ID = true;
		}
		else{
			Can2_RxMsgEXT_ID = false;
		}
		Can2_RxMsgID = can2_Rx_qData[can2_Rx_qTail].arb_id;
		Can2_RxMsgDLC = can2_Rx_qData[can2_Rx_qTail].dlc;
		for (uint8_t i = 0; i < 8; i++){
			Can2_RxMsgData[i] = can2_Rx_qData[can2_Rx_qTail].data[i];
		}
		can2_Rx_qTail = (can2_Rx_qTail + 1) & 0xFF;
		can2_Rx_qElements--;
		/* */ // Do things with the  Can 2 Messages here....
		onReceive(2,Can2_RxMsgEXT_ID,Can2_RxMsgID,Can2_RxMsgDLC,Can2_RxMsgData );
	}
	while (can3_Rx_qElements > 0){
		if (can3_Rx_qData[can3_Rx_qTail].EXT_ID == true){
			Can3_RxMsgEXT_ID = true;
		}
		else{
			Can3_RxMsgEXT_ID = false;
		}
		Can3_RxMsgID = can3_Rx_qData[can3_Rx_qTail].arb_id;
		Can3_RxMsgDLC = can3_Rx_qData[can3_Rx_qTail].dlc;
		for (uint8_t i = 0; i < 8; i++){
			Can3_RxMsgData[i] = can3_Rx_qData[can3_Rx_qTail].data[i];
		}
		can3_Rx_qTail = (can3_Rx_qTail + 1) & 0xFF;
		can3_Rx_qElements--;
		/* */ // Do things with the  Can 3 Messages here....
		onReceive(3,Can3_RxMsgEXT_ID,Can3_RxMsgID,Can3_RxMsgDLC,Can3_RxMsgData);
	}
}

/* Callback to Transmit Messages to CANBuses*/
void trigger_CAN_TX(){
	if (HAL_FDCAN_GetState(&hfdcan1) == HAL_FDCAN_STATE_BUSY){
		uint8_t can1_freelevel = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1);
		while ((can1_freelevel > 0) & (can1_Tx_qElements > 0)){
			if (can1_Tx_qData[can1_Tx_qTail].EXT_ID == true){
				CAN1_TxHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else{
				CAN1_TxHeader.IdType = FDCAN_STANDARD_ID;
			}

			CAN1_TxHeader.Identifier = can1_Tx_qData[can1_Tx_qTail].arb_id;
			if (can1_Tx_qData[can1_Tx_qTail].dlc <= 8){
				CAN1_TxHeader.DataLength = (can1_Tx_qData[can1_Tx_qTail].dlc) << 16;
			}
			else{
				CAN1_TxHeader.DataLength = (8 << 16);
			}
			CAN1_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
			CAN1_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			CAN1_TxHeader.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
			CAN1_TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
			CAN1_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			CAN1_TxHeader.MessageMarker = 0;
			for (uint8_t i = 0; i < 8; i++){
				CAN1_TxData[i] = can1_Tx_qData[can1_Tx_qTail].data[i];
			}
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &CAN1_TxHeader, CAN1_TxData);
			can1_Tx_qTail = (can1_Tx_qTail + 1) & 0xFF;
			can1_Tx_qElements--;
			can1_freelevel--;
		}
	}

	if (HAL_FDCAN_GetState(&hfdcan2) == HAL_FDCAN_STATE_BUSY){
		uint8_t can2_freelevel = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2);
		while ((can2_freelevel > 0) && (can2_Tx_qElements > 0)){
			if (can2_Tx_qData[can2_Tx_qTail].EXT_ID == true){
				CAN2_TxHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else{
				CAN2_TxHeader.IdType = FDCAN_STANDARD_ID;
			}
			CAN2_TxHeader.Identifier = can2_Tx_qData[can2_Tx_qTail].arb_id;
			if (can2_Tx_qData[can2_Tx_qTail].dlc <= 8){
				CAN2_TxHeader.DataLength = (can2_Tx_qData[can2_Tx_qTail].dlc) << 16;
			}
			else{
				CAN2_TxHeader.DataLength = (8 << 16);
			}
			CAN2_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
			CAN2_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			CAN2_TxHeader.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
			CAN2_TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
			CAN2_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			CAN2_TxHeader.MessageMarker = 0;
			for (uint8_t i = 0; i < 8; i++){
				CAN2_TxData[i] = can2_Tx_qData[can2_Tx_qTail].data[i];
			}
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &CAN2_TxHeader, CAN2_TxData);
			can2_Tx_qTail = (can2_Tx_qTail + 1) & 0xFF;
			can2_Tx_qElements--;
			can2_freelevel--;
		}
	}

	if (HAL_FDCAN_GetState(&hfdcan3) == HAL_FDCAN_STATE_BUSY){
		uint8_t can3_freelevel = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan3);
		while ((can3_freelevel > 0) && (can3_Tx_qElements > 0)){
			if (can3_Tx_qData[can3_Tx_qTail].EXT_ID == true){
				CAN3_TxHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else{
				CAN3_TxHeader.IdType = FDCAN_STANDARD_ID;
			}

			CAN3_TxHeader.Identifier = can3_Tx_qData[can3_Tx_qTail].arb_id;
			if (can3_Tx_qData[can3_Tx_qTail].dlc <= 8){
				CAN3_TxHeader.DataLength = (can3_Tx_qData[can3_Tx_qTail].dlc) << 16;
			}
			else{
				CAN3_TxHeader.DataLength = (8 << 16);
			}
			CAN3_TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
			CAN3_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			CAN3_TxHeader.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
			CAN3_TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
			CAN3_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			CAN3_TxHeader.MessageMarker = 0;
			for (uint8_t i = 0; i < 8; i++){
				CAN3_TxData[i] = can3_Tx_qData[can3_Tx_qTail].data[i];
			}
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &CAN3_TxHeader, CAN3_TxData);
			can3_Tx_qTail = (can3_Tx_qTail + 1) & 0xFF;
			can3_Tx_qElements--;
			can3_freelevel--;
		}
	}
}

/* Callback for Errors occurred on CAN buses */
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs){
	uint16_t canTxErrorCount;
	uint16_t canRxErrorCount;
	if (hfdcan->Instance == FDCAN1){
		canTxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
		if (canTxErrorCount > 240){
			resetCAN(1);
		}
		canRxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
		if (canRxErrorCount > 120){
			resetCAN(1);
		}
	}
	if (hfdcan->Instance == FDCAN2){
		canTxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
		if (canTxErrorCount > 240){
			resetCAN(2);
		}
		canRxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
		if (canRxErrorCount > 120){
			resetCAN(2);
		}
	}
	if (hfdcan->Instance == FDCAN3){
		canTxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
		if (canTxErrorCount > 240){
			resetCAN(3);
		}
		canRxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
		if (canRxErrorCount > 120){
			resetCAN(3);
		}
	}
}

/* Resets CAN network(s) */
void resetCAN(uint8_t busChannel){
	if (busChannel == 1){
		if (HAL_FDCAN_Stop(&hfdcan1) != HAL_OK){
			Error_Handler();
		}
				/* Start the FDCAN module */
		if (hfdcan1.State == HAL_FDCAN_STATE_READY){
			if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK){
				Error_Handler();
			}
		}
	}
	if (busChannel == 2){
		if (HAL_FDCAN_Stop(&hfdcan2) != HAL_OK){
			Error_Handler();
		}
				/* Start the FDCAN module */
		if (hfdcan2.State == HAL_FDCAN_STATE_READY){
			if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK){
				Error_Handler();
			}
		}
	}
	if (busChannel == 3){
		if (HAL_FDCAN_Stop(&hfdcan3) != HAL_OK){
			Error_Handler();
		}
				/* Start the FDCAN module */
		if (hfdcan3.State == HAL_FDCAN_STATE_READY){
			if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK){
				Error_Handler();
			}
		}
	}
}


/* reflect8 function */
uint8_t reflect8(uint8_t data){
    uint8_t reflection = 0;
    for (uint8_t i = 0; i < 8; ++i){
        if (data & (1 << i)){
            reflection |= (1 << (7 - i));
        }
    }
    return reflection;
}

/* calculate CRC8 function */
uint8_t calculateCRC8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t crcInit, uint8_t finalXor, bool reflectInput, bool reflectOutput){
    uint8_t crc = crcInit;
    for (size_t i = 0; i < length; ++i){
        uint8_t byte = data[i];
        if (reflectInput){
            byte = reflect8(byte);
        }
        crc ^= byte;
        for (uint8_t j = 0; j < 8; ++j){
            if (crc & 0x80){
                crc = (crc << 1) ^ polynomial;
            } else{
                crc <<= 1;
            }
        }
    }

    if (reflectOutput){
        crc = reflect8(crc);
    }
    return crc ^ finalXor;
}

/* reflect16 function */
uint16_t reflect16(uint16_t data){
    uint16_t reflection = 0;
    for (uint16_t i = 0; i < 16; ++i){
        if (data & (1 << i)){
            reflection |= (1 << (15 - i));
        }
    }
    return reflection;
}

/* calculate CRC16 function */
uint16_t calculateCRC16(uint8_t *data, size_t length, uint16_t polynomial, uint16_t crcInit, uint16_t finalXor, bool reflectInput, bool reflectOutput){
    uint16_t crc = crcInit;
    for (size_t i = 0; i < length; ++i){
        uint16_t byte = data[i];
        if (reflectInput){
            byte = reflect8((uint8_t)byte);  // Using reflect8 since each byte is reflected individually
        }
        crc ^= (byte << 8);  // Shift byte to the high bits of the 16-bit CRC
        for (uint8_t j = 0; j < 8; ++j){
            if (crc & 0x8000){
                crc = (crc << 1) ^ polynomial;
            } else{
                crc <<= 1;
            }
        }
    }

    if (reflectOutput){
        crc = reflect16(crc);
    }
    return crc ^ finalXor;
}

/* reflect32 function */
uint32_t reflect32(uint32_t data){
    uint32_t reflection = 0;
    for (uint32_t i = 0; i < 32; ++i){
        if (data & (1u << i)){
            reflection |= (1u << (31 - i));
        }
    }
    return reflection;
}

/* calculate CRC32 function */
uint32_t calculateCRC32(uint8_t *data, size_t length, uint32_t polynomial, uint32_t crcInit, uint32_t finalXor, bool reflectInput, bool reflectOutput){
    uint32_t crc = crcInit;
    for (size_t i = 0; i < length; ++i){
        uint32_t byte = data[i];
        if (reflectInput){
            byte = reflect8((uint8_t)byte);  // Reflect each byte individually
        }
        crc ^= (byte << 24);  // Shift the byte to the high bits of the 32-bit CRC
        for (uint8_t j = 0; j < 8; ++j){
            if (crc & 0x80000000){
                crc = (crc << 1) ^ polynomial;
            } else{
                crc <<= 1;
            }
        }
    }

    if (reflectOutput){
        crc = reflect32(crc);
    }
    return crc ^ finalXor;
}


/* retrieve MCU Serial Number */
uint32_t getSerialNumber(void){
    uint8_t *serialnumberbase = (uint8_t *)0x1FFF7594;
    uint32_t serialnumber = 0;

    for (uint8_t i = 0; i < 4; i++){
        serialnumber |= (uint32_t)serialnumberbase[i] << (8 * i);
    }

    return serialnumber;
}

/* Get Readout Protection Level */
uint8_t getRDP(void){
	uint32_t optionbytes = 0xFBFFFCAA;
	uint8_t rdp_val = 0;
	uint8_t rdplevel = 0;
	rdp_val = (uint8_t)((optionbytes & FLASH_OPTR_RDP_Msk) >> FLASH_OPTR_RDP_Pos);
	if (rdp_val == 0xAA){
		rdplevel = 0;
	}
	else if (rdp_val == 0xCC){
		rdplevel = 2;
	}
	else {
		rdplevel = 1;
	}
	return rdplevel;
}
/* Set Readout Protection - !Disables debugging! */
void setRDP(bool on){
	uint8_t level = getRDP();
	if ((level == 0) & (on = true)){
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		FLASH_OBProgramInitTypeDef obConfig;
		obConfig.OptionType = OPTIONBYTE_RDP;
		obConfig.RDPLevel = 0xBB;
		HAL_FLASHEx_OBProgram(&obConfig);
		HAL_FLASH_OB_Launch();
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
	}
	else if ((level != 0) & (on = false)){
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		FLASH_OBProgramInitTypeDef obConfig;
		obConfig.OptionType = OPTIONBYTE_RDP;
		obConfig.RDPLevel = 0xAA;
		HAL_FLASHEx_OBProgram(&obConfig);
		HAL_FLASH_OB_Launch();
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
	}
}

void init_PVD(){
	PWR_PVDTypeDef sconfigPVD;
	sconfigPVD.PVDLevel = PWR_CR2_PLS_LEV6; //2.9 Volt Threshold Level 6
	sconfigPVD.Mode = PWR_PVD_MODE_IT_RISING_FALLING;
	HAL_PWR_ConfigPVD(&sconfigPVD);
	HAL_PWR_EnablePVD();
}

//void HAL_PWR_PVDCallback(){
//	xShutdown_Function();
//}

uint8_t read_uint8_t_from_address(void* address) {
    return *(uint8_t*)address;
}

int8_t read_int8_t_from_address(void* address) {
    return *(int8_t*)address;
}

uint16_t read_uint16_t_from_address(void* address) {
    return *(uint16_t*)address;
}

int16_t read_int16_t_from_address(void* address) {
    return *(int16_t*)address;
}

uint32_t read_uint32_t_from_address(void* address) {
    return *(uint32_t*)address;
}

int32_t read_int32_t_from_address(void* address) {
    return *(uint32_t*)address;
}

float read_float_from_address(void* address) {
    return *(float*)address;
}

char* read_char_array_from_address(const void* source, size_t length) {
    char* dest = malloc(length * sizeof(char));
    if (dest == NULL) {
        perror("Failed to allocate memory");
        return NULL; // Allocation failed
    }

    const char* charSource = (const char*)source;
    memcpy(dest, charSource, length);
    return dest;
}



/* Flash Back Data to the last Page in FLASH Memory */
void writeFlash(uint32_t page, uint8_t *Data, uint16_t dataSize){
	if ((storecompleted == false) & (page > 30)){
		static FLASH_EraseInitTypeDef EraseInitStruct;
		uint32_t PAGEError;

		/* Unlock the Flash to enable the flash control register access *************/
		HAL_FLASH_Unlock();
		/* Erase the user Flash area*/
		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.Banks = FLASH_BANK_1;
		EraseInitStruct.Page = 31;
		EraseInitStruct.NbPages = 1;

		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK){
			/*Error occurred while page erase.*/
			HAL_FLASH_GetError();
		}
		/* Program the user Flash area word by word*/
		uint32_t pageaddress = 2048 * page + 0x08000000;
		uint16_t j = 0;
		HAL_StatusTypeDef status;
		for (uint32_t i = 0; i < dataSize; i += 8) {
			uint64_t writeValue = 0;

			// Construct the double word from the data array
			for (int k = 0; k < 8; ++k) {
				if (i + k < dataSize) {
					writeValue |= ((uint64_t)Data[j + k]) << (k * 8);
				}
			}

			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, pageaddress, writeValue);
			if (status == HAL_OK) {
				pageaddress += 8;
				j += 8;
			} else {
				// Handle error
				break;
			}
		}
		HAL_FLASH_Lock();
		storecompleted = true;
	}
}
