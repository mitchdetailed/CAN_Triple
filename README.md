# CAN Triple 1.0 Documentation

The CAN Triple is designed to simplify the scope of interfacing multiple CAN Buses with a small form factor for Automotive Environments. Offers an Efficient and lightweight way to manage traffic among 3 CAN 2.0 Networks. Nearly all code should be written in the *user_code.c* file.

## Code Function Calls

Setting CAN Bitrate : 
```C
uint8_t setCANBitrate(uint8_t enum_bus, uint32_t mainBitrate)
Sets CANbus Bitrate

Parameters:
enum_bus – CAN_1, CAN_2, and/or CAN_3.
mainBitrate – Bitrate of CANbus in bits per second.

Returns:
CAN_1, CAN_2, and/or CAN_3.
```
---
Setting internal 120 Ω Termination Resistor for CAN Bus(es) : 
```C
uint8_t setCAN_Termination(uint8_t enum_bus, bool activated)
Enable or Disable CAN Termination across CANbuses

Parameters:
enum_bus – CAN_1, CAN_2, and/or CAN_3.

Returns:
CAN_1, CAN_2, and/or CAN_3 only if termination enabled.
```
---
Starting CAN Bus(es) :
```C
uint8_t startCANbus(uint8_t enum_bus)
Starts CANbus

Parameters:
enum_bus – CAN_1, CAN_2, and/or CAN_3.

Returns:
CAN_1, CAN_2, and/or CAN_3.
```
---
Stopping CAN Bus(es) : 
```C
uint8_t stopCANbus(uint8_t enum_bus)
Stops CANbus Bitrate

Parameters:
enum_bus – CAN_1, CAN_2, and/or CAN_3.

Returns:
CAN_1, CAN_2, and/or CAN_3.
```
---
Adding a CAN bus message to the Transmit Queue : 
```C
uint8_t send_message(uint8_t enum_bus, bool is_extended_id, uint32_t arbitration_id, uint8_t dlc, uint8_t *data)
Sends message to Queue

Parameters:
enum_bus – CAN_1, CAN_2, and/or CAN_3.
is_extended_id – True or False.
arbitration_id – Message ID.
dlc – Data Length.
data – Message data (8 Bytes).

Returns:
CAN_1, CAN_2, and/or CAN_3
```
---
Turning GPIO LED on/off : 
```C
void writeLED(uint8_t led_enum, bool high)
Writes OnBoard LED

Parameters:
led_enum – LED_1.
high – Boolean.
```
---
Toggling GPIO LED : 
```C
void toggleLED(uint8_t led_enum)
Toggles OnBoard LED

Parameters:
led_enum – LED_1.
```
---
Managing Received CAN Messages : 
```C
void onReceive(CAN_Message)
Handles the receipt of a CAN message. This function is called when a new CAN message is received.

Parameters:
Message – The CAN message that was received.
typedef struct {
    uint8_t Bus;             /**< ID of the CAN bus the message is associated with. */
    bool is_extended_id;     /**< True if using an extended ID, false if using a standard ID. */
    uint32_t arbitration_id; /**< The identifier for the message, either standard or extended based on is_extended_id. */
    uint8_t dlc;             /**< Data length code, the number of valid bytes in the data field. */
    uint8_t data[8];         /**< Data payload of the CAN message. */
} CAN_Message;

// we'll define the CAN_Message and call each field using the [dot] operator.

