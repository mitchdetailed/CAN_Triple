/*
 * backend_functions.h
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef INC_BACKEND_FUNCTIONS_H_
#define INC_BACKEND_FUNCTIONS_H_

#define CAN_1 1
#define CAN_2 2
#define CAN_3 4

#define LED_1 1

typedef struct {
    uint8_t Bus;
    bool is_extended_id;
    uint32_t arbitration_id;
    uint8_t dlc;
    uint8_t data[8];
} CAN_Message;

uint8_t setCANBitrate(uint8_t enum_bus, uint32_t mainBitrate);
uint8_t setCANFDBitrate(uint8_t enum_bus, uint32_t mainBitrate, uint32_t dataBitrate, bool bitrateSwitch);
uint8_t startCANbus(uint8_t enum_bus);
uint8_t stopCANbus(uint8_t enum_bus);
uint8_t setCAN_Termination(uint8_t enum_bus, bool activated);

uint8_t add_to_CAN_RX_Queue(uint8_t enum_bus, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t rxData[8]);
uint8_t send_message(uint8_t enum_bus, bool is_extended_id, uint32_t arbitration_id, uint8_t dlc, uint8_t data[8]);
void trigger_CAN_RX(void);
void trigger_CAN_TX(void);
void onReceive(CAN_Message);
void writeLED(uint8_t LED_int, bool high);
void toggleLED(uint8_t LED_int);

uint8_t resetCAN(uint8_t enum_bus);

uint8_t reflect8(uint8_t data);
uint16_t reflect16(uint16_t data);
uint32_t reflect32(uint32_t data);
uint8_t calculateCRC8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t crcInit, uint8_t finalXor, bool reflectInput, bool reflectOutput);
uint16_t calculateCRC16(uint8_t *data, size_t length, uint16_t polynomial, uint16_t crcInit, uint16_t finalXor, bool reflectInput, bool reflectOutput);
uint32_t calculateCRC32(uint8_t *data, size_t length, uint32_t polynomial, uint32_t crcInit, uint32_t finalXor, bool reflectInput, bool reflectOutput);

uint32_t getSerialNumber1of3(void);
uint32_t getSerialNumber2of3(void);
uint32_t getSerialNumber3of3(void);
uint8_t getRDP(void);
uint8_t setRDP(bool on);
uint8_t read_uint8_t_from_address(void* address);
int8_t read_int8_t_from_address(void* address);
uint16_t read_uint16_t_from_address(void* address);
int16_t read_int16_t_from_address(void* address);
uint32_t read_uint32_t_from_address(void* address);
int32_t read_int32_t_from_address(void* address);
float read_float_from_address(void* address);
char* read_char_array_from_address(const void* source, size_t length);

#endif // INC_BACKEND_FUNCTIONS_H_