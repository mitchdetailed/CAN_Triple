/*
 * backend_functions.h
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef INC_BACKEND_FUNCTIONS_H_
#define INC_BACKEND_FUNCTIONS_H_



extern uint8_t setCANBitrate(uint8_t busChannel, uint32_t mainBitrate);
extern uint8_t setCANFDBitrate(uint8_t busChannel, uint32_t mainBitrate, uint32_t dataBitrate, bool bitrateSwitch);
extern uint8_t startCANbus(uint8_t busChannel);
extern uint8_t stopCANbus(uint8_t busChannel);
extern uint8_t setCAN_Termination(uint8_t busChannel, bool activated);

extern uint8_t add_to_CAN_RX_Queue(uint8_t enum_busChannel, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t rxData[8]);
extern uint8_t add_to_CAN_TX_Queue(uint8_t enum_busChannel, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t txData[8]);
void trigger_CAN_RX(void);
void trigger_CAN_TX(void);
extern void onReceive(uint8_t busChannel, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t Data[8]);

extern void resetCAN(uint8_t busChannel);

extern uint8_t reflect8(uint8_t data);
extern uint16_t reflect16(uint16_t data);
extern uint32_t reflect32(uint32_t data);
extern uint8_t calculateCRC8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t crcInit, uint8_t finalXor, bool reflectInput, bool reflectOutput);
extern uint16_t calculateCRC16(uint8_t *data, size_t length, uint16_t polynomial, uint16_t crcInit, uint16_t finalXor, bool reflectInput, bool reflectOutput);
extern uint32_t calculateCRC32(uint8_t *data, size_t length, uint32_t polynomial, uint32_t crcInit, uint32_t finalXor, bool reflectInput, bool reflectOutput);

uint32_t getSerialNumber(void);
uint8_t getRDP(void);
extern void setRDP(bool on);
extern uint8_t read_uint8_t_from_address(void* address);
extern int8_t read_int8_t_from_address(void* address);
extern uint16_t read_uint16_t_from_address(void* address);
extern int16_t read_int16_t_from_address(void* address);
extern uint32_t read_uint32_t_from_address(void* address);
extern int32_t read_int32_t_from_address(void* address);
extern float read_float_from_address(void* address);
extern char* read_char_array_from_address(const void* source, size_t length);

#endif // INC_BACKEND_FUNCTIONS_H_
