/*
 * user_code.h
 */

/* Includes Declarations */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Defines Declarations */
#ifndef INC_USER_CODE_H_
#define INC_USER_CODE_H_



/* Message queues are circular byte buffers holding variable-length records
 * (6-byte header + actual payload), so short frames pack tightly.
 * CANx_.._MSG_BUFFER_SIZE = number of maximum-size (CANx_DATALENGTH) messages
 * guaranteed to fit; any value >= 1 is allowed (no power-of-two requirement).
 * Smaller frames consume less space, so many more of them fit. */
#define CAN1_RX_MSG_BUFFER_SIZE 32     /* < Guaranteed max-size message capacity of the RX queue */
#define CAN1_TX_MSG_BUFFER_SIZE 32     /* < Guaranteed max-size message capacity of the TX queue */
#define CAN1_DATALENGTH         64     /* Max data length (bytes, 1..64) queued per message */

#define CAN2_RX_MSG_BUFFER_SIZE 32      /* < Guaranteed max-size message capacity of the RX queue */
#define CAN2_TX_MSG_BUFFER_SIZE 32      /* < Guaranteed max-size message capacity of the TX queue */
#define CAN2_DATALENGTH         64     /* Max data length (bytes, 1..64) queued per message */

#define CAN3_RX_MSG_BUFFER_SIZE 32      /* < Guaranteed max-size message capacity of the RX queue */
#define CAN3_TX_MSG_BUFFER_SIZE 32      /* < Guaranteed max-size message capacity of the TX queue */
#define CAN3_DATALENGTH        8       /* Max data length (bytes, 1..64) queued per message */

#define CANFD_LOOP_DELAY_NS     100     /* Assumed transceiver+path loop delay in ns */

#define UART_MSG_BUFFER_SIZE 1024 /* UART String Buffer Size*/
// #define UART_DEBUG_BAUDRATE       115200      /* Default UART Debug Baudrate*/
// #define UART_DEBUG_BAUDRATE       921600      /* Teleplot Max UART Debug Baudrate?*/
#define UART_DEBUG_BAUDRATE 7372800 /* Maximum UART Debug Baudrate*/

/* Function Prototypes */

void events_Startup(void);
void events_2000Hz(void);
void events_1000Hz(void);
void events_500Hz(void);
void events_200Hz(void);
void events_100Hz(void);
void events_50Hz(void);
void events_20Hz(void);
void events_10Hz(void);
void events_5Hz(void);
void events_2Hz(void);
void events_1Hz(void);
void events_Shutdown(void);

#endif /* INC_USER_CODE_H_ */
