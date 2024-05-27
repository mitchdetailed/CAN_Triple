/*
 * backend_functions.h
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "stm32g4xx_hal.h"

#ifndef INC_BACKEND_FUNCTIONS_H_
#define INC_BACKEND_FUNCTIONS_H_

#define CAN_1                   1
#define CAN_2                   2
#define CAN_3                   4

#define LED_1                   1

#define SERIALNUMBER_BASE_ADDRESS        (0x1FFF7590UL)    /*!< Unique device ID register base address */
#define UART_ARRAY_LEN               1024
/**
 * @brief Structure to represent a CAN network message.
 * 
 * This structure is used to hold all the necessary data for a CAN message,
 * including its identifier, whether it is using an extended identifier,
 * and the payload data.
 */
typedef struct {
    uint8_t Bus;             /**< ID of the CAN bus the message is associated with. */
    bool is_extended_id;     /**< True if using an extended ID, false if using a standard ID. */
    uint32_t arbitration_id; /**< The identifier for the message, either standard or extended based on is_extended_id. */
    uint8_t dlc;             /**< Data length code, the number of valid bytes in the data field. */
    uint8_t data[8];         /**< Data payload of the CAN message. */
} CAN_Message;

typedef struct {
    char array[UART_ARRAY_LEN];
    uint16_t length;
} StringArray;

extern StringArray array0;
extern StringArray array1;
extern uint8_t uart_array;

UART_HandleTypeDef huart1;

/*Function Prototypes*/
uint8_t setCANBitrate(uint8_t enum_bus, uint32_t mainBitrate);
//uint8_t setCANFDBitrate(uint8_t enum_bus, uint32_t mainBitrate, uint32_t dataBitrate, bool bitrateSwitch);
uint8_t startCANbus(uint8_t enum_bus);
uint8_t stopCANbus(uint8_t enum_bus);
uint8_t setCAN_Termination(uint8_t enum_bus, bool activated);

uint8_t add_to_CAN_RX_Queue(uint8_t enum_bus, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t rxData[8]);
uint8_t send_message(uint8_t enum_bus, bool is_extended_id, uint32_t arbitration_id, uint8_t dlc, uint8_t data[8]);
void trigger_CAN_RX(void);
void trigger_CAN_TX(void);

/**
 * \brief Handles the receipt of a CAN message.
 * This function is called when a new CAN message is received.
 *
 * \param Message The CAN message that was received.
 */
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

float roundFloat(float num, uint8_t places);
int32_t roundAndPrepare(float num, uint8_t decimal_places);

uint32_t getSerialNumber(void);
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
void serialPrint(const char* str);
void tx_Serial_Comms();
float process_numeric_value(uint32_t value, uint32_t bitmask, bool is_signed, float factor, float offset);
uint32_t process_raw_value(uint32_t value, uint32_t bitmask);

#endif // INC_BACKEND_FUNCTIONS_H_