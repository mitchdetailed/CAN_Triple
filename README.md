# CAN Triple 1.0 Documentation

The CAN Triple is designed to simplify the scope of interfacing multiple CAN Buses with a small form factor for Automotive Environments. Offers an Efficient and lightweight way to manage traffic among 3 CAN 2.0 Networks. Nearly all code should be written in the *user_code.c* file.

## Code Function Calls

Setting CAN Bitrate : 
```C
uint8_t setCANBitrate(uint8_t enum_bus, uint32_t mainBitrate);
// enum_bus will be the Bus Enumeration(s)..
// mainBitrate will be the bitrate value in bits per second..
// Return value = 0 if successful, else -1..
```
---
Starting CAN Bus(es) :
```C
uint8_t startCANbus(uint8_t enum_bus);
// enum_bus will be the Bus Enumeration(s)..
// Return value = 0 if successful, else -1..
```
---
Stopping CAN Bus(es) : 
```C
uint8_t stopCANbus(uint8_t enum_bus);
// enum_bus will be the Bus Enumeration(s)..
// Return value = 0 if successful, else -1..
```
---
Setting internal 120 Ω Termination Resistor for CAN Bus(es) : 
```C
uint8_t setCAN_Termination(uint8_t enum_bus, bool activated);
// enum_bus will be the Bus Enumeration(s)..
// activated will be true or false value based on if you want termination enabled..
// Return value = 0 if successful, else -1..
```
---
Adding a CAN bus message to the Transmit Queue : 
```C
uint8_t add_to_CAN_TX_Queue(uint8_t enum_bus, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t Data[8]);
// enum_bus will be the Bus Enumeration(s)..
// EXT_ID will be a true or false value based on if your message ID is extended addressing or not..
// ID will be the arbitration ID 0x0 - 0x7ff for Standard addressing, 0x0 - 0x 1FFFFFFF for Extended Addressing..
// DLC will be the data length, 0-8..
// Data[8] will be an 8 byte array of data for transmitting..
```
---
Turning GPIO LED on/off : 
```C
void writeLED(uint8_t LED_int, bool high);
// led_enum will be the LED Enumeration(s)..
// high will be a true or false value for setting on or off..
```
---
Toggling GPIO LED : 
```C
void writeLED(uint8_t LED_int);
// led_enum will be the LED Enumeration(s)..
```
---
Managing Received CAN Messages : 
```C
void onReceive(CAN_Message);
// the CAN_Message struct will contain the following items :
---    uint8_t Bus; // will be the Bus Enumeration.
---    bool is_extended_id; // will be 
---    uint32_t arbitration_id;
---    uint8_t dlc;
---    uint8_t data[8];
// we'll define the CAN_Message and call each field usint the [dot] operator.

