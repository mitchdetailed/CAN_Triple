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
// activated will be true or false..
// Return value = 0 if successful, else -1..
```
---
