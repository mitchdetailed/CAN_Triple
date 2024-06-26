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
#define UART_MSG_BUFFER_SIZE        1024        /* UART String Buffer Size*/
#define CAN_MSG_BUFFER_SIZE         256         /* < Must Be incremented by a factor of 2. eg.(4,8,16,32,64,..,256) */
//#define UART_DEBUG_BAUDRATE       115200      /* Default UART Debug Baudrate*/
//#define UART_DEBUG_BAUDRATE       921600      /* Teleplot Max UART Debug Baudrate?*/
#define UART_DEBUG_BAUDRATE         7372800     /* Maximum UART Debug Baudrate*/

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
