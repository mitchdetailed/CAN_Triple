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
double testval = 0.0f;
/* Startup Functions */
void events_Startup()
{
	setupCANbus(CAN_1, 1000000, NORMAL_MODE);
	setupCAN_FDbus(CAN_2, 125000,500000, true, NORMAL_MODE);
	setupCANbus(CAN_3, 1000000, NORMAL_MODE);
	setCAN_Termination(CAN_1, true);
	setCAN_Termination(CAN_2, true);
	setCAN_Termination(CAN_3, true);
	//startCANbus(CAN_1);
	startCANbus(CAN_2);
	//startCANbus(CAN_3);
}
/* End Startup Functions */

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
		static char formatted_message[400];  // Static to avoid large stack allocation in ISR-context
		format_CAN_message(&Message, formatted_message, sizeof(formatted_message));
		printf("%s\r\n", formatted_message);
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
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Helper: human-readable names for the CAN bus state and last-error-code. */
static const char *can_state_name(CAN_ErrorState s)
{
	switch (s)
	{
	case CAN_ERR_ACTIVE:  return "ACTIVE";
	case CAN_ERR_WARNING: return "WARNING";
	case CAN_ERR_PASSIVE: return "PASSIVE";
	case CAN_ERR_BUSOFF:  return "BUS-OFF";
	default:              return "?";
	}
}

static const char *can_lec_name(CAN_LastErrorCode l)
{
	switch (l)
	{
	case CAN_LEC_NONE:      return "none";
	case CAN_LEC_STUFF:     return "stuff";
	case CAN_LEC_FORM:      return "form";
	case CAN_LEC_ACK:       return "ack";
	case CAN_LEC_BIT1:      return "bit1";
	case CAN_LEC_BIT0:      return "bit0";
	case CAN_LEC_CRC:       return "crc";
	default:                return "nochg";
	}
}

/* Optional hook: fires (from the main loop) the moment a CAN fault is detected. */
void onCANError(CAN_Bus bus, const CAN_ErrorStatus *status)
{
	printf("!! CAN%u fault: state=%s lastErr=%s busOff=%lu passive=%lu\r\n",
		   (bus == CAN_1) ? 1u : (bus == CAN_2) ? 2u : 3u,
		   can_state_name(status->state),
		   can_lec_name(status->lastArbLEC),
		   (unsigned long)status->busOffCount,
		   (unsigned long)status->passiveCount);
}

/* Run 1Hz Functions here */
void events_1Hz()
{
	uint8_t test123[16] = {1,2,3,4,5,6,7,8,5,5,5,5,5,5,5,5};
	send_message(CAN_2,true,0x12345678,16,test123);
	send_message(CAN_2,true,0x10504030,16,test123);

	/* Legacy accessor still works unchanged. */
	CAN_ErrorCounts errors = getCANErrorCounts(CAN_2);
	printf("CAN2 Errors - TX: %u, RX: %u, Resets: %u\r\n",
		   errors.TxErrorCounter, errors.RxErrorCounter, errors.BusResetCounter);

	/* Rich health snapshot: state, last error type, and dropped-frame counters. */
	CAN_ErrorStatus st = getCANErrorStatus(CAN_2);
	printf("CAN2 Health - state=%s lastArb=%s lastData=%s | busOff=%lu warn=%lu passive=%lu proto=%lu\r\n",
		   can_state_name(st.state), can_lec_name(st.lastArbLEC), can_lec_name(st.lastDataLEC),
		   (unsigned long)st.busOffCount, (unsigned long)st.warningCount,
		   (unsigned long)st.passiveCount, (unsigned long)st.protocolErrCount);
	printf("CAN2 Drops - rxFifoLost=%lu rxQ=%lu txQ=%lu txFifo=%lu\r\n",
		   (unsigned long)st.rxFifoLostCount, (unsigned long)st.rxQueueOverflowCount,
		   (unsigned long)st.txQueueOverflowCount, (unsigned long)st.txFifoFullCount);
}
