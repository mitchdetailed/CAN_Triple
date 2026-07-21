/*
 * backend_functions.h
 */

/* Includes Declarations */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "stm32g4xx_hal.h"
#include "user_code.h"

/* Defines Declarations */
#ifndef INC_BACKEND_FUNCTIONS_H_
#define INC_BACKEND_FUNCTIONS_H_

extern uint32_t timestamp;
/* Variable Declarations */

extern uint16_t can1Reset_counter;
extern uint16_t can2Reset_counter;
extern uint16_t can3Reset_counter;

typedef enum
{
    CAN_1 = 1 << 0,
    CAN_2 = 1 << 1,
    CAN_3 = 1 << 2
} CAN_Bus;

typedef enum
{
    LED_1
} gpio_LED;

typedef struct
{
    uint8_t TxErrorCounter;
    uint8_t RxErrorCounter;
    uint8_t BusResetCounter;
} CAN_ErrorCounts;

/**
 * @brief Overall protocol state of a CAN bus (from the FDCAN PSR register).
 */
typedef enum
{
    CAN_ERR_ACTIVE  = 0, /**< Normal operation.                       */
    CAN_ERR_WARNING = 1, /**< Error-warning: an error counter >= 96.  */
    CAN_ERR_PASSIVE = 2, /**< Error-passive: an error counter >= 128. */
    CAN_ERR_BUSOFF  = 3  /**< Bus-off: TEC >= 256, bus disconnected.  */
} CAN_ErrorState;

/**
 * @brief Last protocol error type. Values match the FDCAN PSR.LEC / PSR.DLEC field encoding.
 */
typedef enum
{
    CAN_LEC_NONE      = 0, /**< No error since the last check.        */
    CAN_LEC_STUFF     = 1, /**< Bit-stuffing error.                   */
    CAN_LEC_FORM      = 2, /**< Form (fixed-format) error.            */
    CAN_LEC_ACK       = 3, /**< Acknowledge error (no receiver ACK).  */
    CAN_LEC_BIT1      = 4, /**< Sent recessive but monitored dominant.*/
    CAN_LEC_BIT0      = 5, /**< Sent dominant but monitored recessive.*/
    CAN_LEC_CRC       = 6, /**< CRC error.                            */
    CAN_LEC_NO_CHANGE = 7  /**< No bus event since PSR was last read. */
} CAN_LastErrorCode;

/**
 * @brief Rich CAN health/error snapshot for a single bus.
 *
 * Live fields (TxErrorCounter/RxErrorCounter/state/lastArb/DataLEC) are read from
 * hardware at call time; the cumulative counters are maintained by the CAN error
 * interrupt callbacks. Retrieve with getCANErrorStatus(bus).
 */
typedef struct
{
    uint8_t           TxErrorCounter;   /**< Live transmit error counter (ECR.TEC). */
    uint8_t           RxErrorCounter;   /**< Live receive error counter (ECR.REC).  */
    CAN_ErrorState    state;            /**< Live bus state (PSR BO/EP/EW).          */
    CAN_LastErrorCode lastArbLEC;       /**< Last arbitration-phase error type.      */
    CAN_LastErrorCode lastDataLEC;      /**< Last FD data-phase error type.          */

    uint32_t busOffCount;               /**< Number of bus-off events.               */
    uint32_t warningCount;              /**< Number of error-warning events.         */
    uint32_t passiveCount;              /**< Number of error-passive events.         */
    uint32_t protocolErrCount;          /**< Number of arb/data protocol errors.     */

    uint32_t rxFifoLostCount;           /**< Hardware RX FIFO0 dropped frames.       */
    uint32_t rxQueueOverflowCount;      /**< Software RX ring-buffer dropped frames. */
    uint32_t txQueueOverflowCount;      /**< Software TX ring-buffer dropped frames. */
    uint32_t txFifoFullCount;           /**< HAL TX FIFO add failures.               */

    uint32_t busResetCount;             /**< Automatic bus resets performed.         */
    float    lastResetTimestamp;        /**< getTimestamp() at the last reset.       */

    uint16_t lecCount[8];               /**< Arbitration-phase errors by CAN_LastErrorCode (1..6). */
    uint16_t dlecCount[8];              /**< FD data-phase errors by CAN_LastErrorCode (1..6).     */
} CAN_ErrorStatus;

// Define datatype_t enum
typedef enum
{
    DBC_UNSIGNED = 0,
    DBC_SIGNED = 1,
    DBC_FLOAT = 2,
    DBC_DOUBLE = 4
} datatype_t;

// Union for IEEE-754 float representation
typedef union
{
    uint8_t bytes[4];
    float f32;
} FloatUnion_t;

// Union for IEEE-754 double representation
typedef union
{
    uint8_t bytes[8];
    double f64;
} DoubleUnion_t;

/* Maximum data payload size across all three CAN buses */
#define CAN_MSG_MAX_DLC  ((CAN1_DATALENGTH > CAN2_DATALENGTH) ? ((CAN1_DATALENGTH > CAN3_DATALENGTH) ? CAN1_DATALENGTH : CAN3_DATALENGTH) \
                                                 : ((CAN2_DATALENGTH > CAN3_DATALENGTH) ? CAN2_DATALENGTH : CAN3_DATALENGTH))

/**
 * @brief Structure to represent a CAN network message.
 * \param Bus : ID of the CAN bus the message is associated with.
 * \param is_extended_id : True if using an extended ID, false if using a standard ID.
 * \param arbitration_id : The identifier for the message, either standard or extended based on is_extended_id.
 * \param dlc : the Data Length in bytes (1-64)
 * \param data : the Data array, sized to the largest configured bus DLC
 * \return uint32_t Value
 */
typedef struct
{
    uint8_t Bus;             /**< ID of the CAN bus the message is associated with. */
    bool is_extended_id;     /**< True if using an extended ID, false if using a standard ID. */
    uint32_t arbitration_id; /**< The identifier for the message, either standard or extended based on is_extended_id. */
    uint8_t dlc;             /**< Data length in bytes, the number of valid bytes in the data field. */
    uint8_t data[CAN_MSG_MAX_DLC]; /**< Data payload of the CAN message. */
} CAN_Message;

typedef enum
{
    NORMAL_MODE,
    LISTEN_ONLY
} CAN_Mode;

typedef struct
{
    char array[UART_MSG_BUFFER_SIZE];
    uint16_t length;
} StringArray;

extern StringArray array0;
extern StringArray array1;
extern uint8_t uart_array;

/* Function Prototypes */

// CAN Physical Layer Function Prototypes //
uint8_t setupCANbus(CAN_Bus bus, uint32_t mainBitrate, CAN_Mode mode);
uint8_t setupCAN_FDbus(CAN_Bus bus, uint32_t mainBitrate, uint32_t dataBitrate, bool bitrateSwitch, CAN_Mode mode);
uint8_t startCANbus(CAN_Bus bus);
uint8_t stopCANbus(CAN_Bus bus);
uint8_t resetCAN(CAN_Bus bus);
uint8_t setCAN_Termination(CAN_Bus bus, bool activated);
CAN_ErrorCounts getCANErrorCounts(CAN_Bus bus);
CAN_ErrorStatus getCANErrorStatus(CAN_Bus bus);

// CAN Communication Layer Fuction Prototypes //
/* `data` must hold at least `dlc` bytes; only that many are read. */
uint8_t send_message(CAN_Bus bus, bool is_extended_id, uint32_t arbitration_id, uint8_t dlc, const uint8_t data[]);
void onReceive(CAN_Message);

/**
 * @brief Optional user hook, called (from the main loop) when a CAN fault is detected.
 * The backend provides a weak no-op default; override it in user_code.c to react.
 * @param bus The bus the fault occurred on.
 * @param status Snapshot of that bus's error status at the time of the fault.
 */
void onCANError(CAN_Bus bus, const CAN_ErrorStatus *status);

void trigger_CAN_RX(void);
void trigger_CAN_TX(void);
uint8_t add_to_CAN_RX_Queue(CAN_Bus bus, bool EXT_ID, uint32_t ID, uint8_t DLC, const uint8_t rxData[]);

// Arithmatic Functions related to CAN Reception and Transmission //
double dbc_decode(const uint8_t *data, datatype_t datatype, bool is_big_endian, uint8_t dbc_start_bit, uint8_t dbc_bit_length, float factor, float offset, uint8_t decimal_places);
int dbc_encode(uint8_t *data, size_t msg_data_length, datatype_t datatype, bool is_big_endian, double scaled_value, uint8_t dbc_start_bit, uint8_t dbc_bit_length, float factor, float offset);
float process_float_value(uint32_t value, uint32_t bitmask, bool is_signed, float factor, float offset, int8_t decimal_places);
float process_ieee754(uint32_t value, uint32_t bitmask, float factor, float offset, uint8_t decimal_places);
int32_t process_int_value(uint32_t value, uint32_t bitmask, bool is_signed, int32_t factor, int32_t offset);
uint32_t process_unsigned_int_value(uint32_t value, uint32_t bitmask, uint32_t factor, uint32_t offset);
uint32_t process_raw_value(uint32_t value, uint32_t bitmask);
uint32_t prepare_output_signal(float value, uint8_t bitlength, bool is_signed, float dbcFactor, float dbcOffset);
float roundfloat(float num, uint8_t decimal_places);
int32_t roundfloat_to_int32(float num, uint8_t decimal_places);
int32_t map_int(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);
float map_float(float x, float in_min, float in_max, float out_min, float out_max);
int32_t clamped_map_int(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);
float clamped_map_float(float x, float in_min, float in_max, float out_min, float out_max);
uint32_t frequency_Hz_to_period_10uS(uint32_t frequency_value);
uint32_t period_10uS_to_frequency_Hz(uint32_t period_value);

float getTimestamp();
// GPIO LED Function Prototypes //
void writeLED(gpio_LED led, bool high);
void toggleLED(gpio_LED led);

// CRC Checksum Calculation Function Prototypes //
uint8_t reflect8(uint8_t data);
uint16_t reflect16(uint16_t data);
uint32_t reflect32(uint32_t data);
uint8_t calculateCRC8(const uint8_t *data, size_t length, uint8_t polynomial, uint8_t crcInit, uint8_t finalXor, bool reflectInput, bool reflectOutput);
uint16_t calculateCRC16(const uint8_t *data, size_t length, uint16_t polynomial, uint16_t crcInit, uint16_t finalXor, bool reflectInput, bool reflectOutput);
uint32_t calculateCRC32(const uint8_t *data, size_t length, uint32_t polynomial, uint32_t crcInit, uint32_t finalXor, bool reflectInput, bool reflectOutput);

// Security and Readout Protection Function Prototypes //
uint32_t getSerialNumber(void);
uint8_t getRDP(void);
uint8_t setRDP(bool on);

// Reading from Flash Function Prototypes //
uint8_t read_uint8_t_from_address(void *address);
int8_t read_int8_t_from_address(void *address);
uint16_t read_uint16_t_from_address(void *address);
int16_t read_int16_t_from_address(void *address);
uint32_t read_uint32_t_from_address(void *address);
int32_t read_int32_t_from_address(void *address);
float read_float_from_address(void *address);
char *read_char_array_from_address(const void *source, size_t length);
void writeFlash(uint32_t page, uint8_t *Data, uint16_t dataSize);

// filtering functions //
float lowpass_filter_by_frequency(float basevalue, float newvalue, float time_constant, float frequency);
float lowpass_filter_by_timedelta(float basevalue, float newvalue,  float time_constant, float last_timestamp, float current_timestamp);

// UART Debugger Function Prototypes //
void serialPrint(const char *str);
void serialWrite(const uint8_t *data, uint16_t length);
void tx_Serial_Comms();
void onSerialReceive(uint8_t *serialMessage);

char *format_CAN_message(const CAN_Message *msg, char *buffer, size_t buf_size);

#endif
