/*
 * user_code.h
 *
 */

#ifndef INC_USER_CODE_H_
#define INC_USER_CODE_H_
#define BUFFER_SIZE 256                 /**< Must Be incremented by a factor of 2. eg.(4,8,16,32,64,..,256) */
//#define UART_DEBUG_BAUDRATE 115200    /** Default UART Debug Speed*/
#define UART_DEBUG_BAUDRATE 921600      /** Maximum Teleplot Plugin UART Debug Speed*/
//#define UART_DEBUG_BAUDRATE 10000000  /** Maximum UART Debug Speed*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


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
