# CAN Triple 1.0 Documentation

The CAN Triple is designed to simplify the scope of interfacing multiple CAN Buses with a small form factor for Automotive Environments. Offers an Efficient and lightweight way to manage traffic among 3 CAN 2.0 Networks. Nearly all code should be written in the `*user_code.c*` file. Programming is completed by using a STlink V3 Debugger.

## Prerequisites
- Python [Download Link](https://www.python.org/downloads/)
- - *Make sure to Add python to PATH when installing Python...
- Visual Studio Code (VSCode) [Download Link](https://code.visualstudio.com/)
- PlatformIO extension for VSCode [Download Link](https://platformio.org/platformio-ide)

## Value Added Extensions within VS Code
- Teleplot : A plotting tool for UART messages
- Serial Monitor : Easy to use Serial Monitor

## Code Function Calls for user_code.c

### Setting CAN Bitrate : 
```C
uint8_t setupCANbus(uint8_t bus, uint32_t mainBitrate, enum mode)
Sets CANbus Bitrate and Mode.

Parameters:
bus – CAN_1, CAN_2, and/or CAN_3.
mainBitrate – Bitrate of CANbus in bits per second.
mode - NORMAL_MODE for normal mode, LISTEN_ONLY for listen only (silent) mode.

Returns:
0 if no errors.
```
---
### Setting internal 120Ω Termination Resistor for CAN Bus(es) : 
```C
uint8_t setCAN_Termination(uint8_t bus, bool activated)
Enable or Disable CAN Termination across CANbuses

Parameters:
bus – CAN_1, CAN_2, and/or CAN_3.

Returns:
0 if no errors
```
---
### Starting CAN Bus(es) :
```C
uint8_t startCANbus(uint8_t bus)
Starts CANbus

Parameters:
bus – CAN_1, CAN_2, and/or CAN_3.

Returns:
0 if no errors.
```
---
### Stopping CAN Bus(es) : 
```C
uint8_t stopCANbus(uint8_t bus)
Stops CANbus Bitrate

Parameters:
bus – CAN_1, CAN_2, and/or CAN_3.

Returns:
0 if no errors.
```
---
### Sending a CAN Message : 
```C
uint8_t send_message(uint8_t bus, bool is_extended_id, uint32_t arbitration_id, uint8_t dlc, uint8_t *data)
Sends message to Queue to be pushed to the CANbus

Parameters:
bus – CAN_1, CAN_2, and/or CAN_3.
is_extended_id – True or False.
arbitration_id – Message ID.
dlc – Data Length.
data – Message data (8 Bytes).

Returns:
0 if no errors.
```
---
### Turning GPIO LED on/off : 
```C
void writeLED(uint8_t led_enum, bool high)
Writes OnBoard LED

Parameters:
led_enum – LED_1.
high – Boolean.

Returns:
0 if no errors.
```
---
### Toggling GPIO LED : 
```C
void toggleLED(uint8_t led_enum)
Toggles OnBoard LED

Parameters:
led_enum – LED_1.

Returns:
0 if no errors.
```
---
### Managing Received CAN Messages : 
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
// eg, for which bus the message came from, use Message.Bus 
```
---

### Processing Received CAN Data.. 

There's a few functions to help process incoming CAN Message data to convert it to it's apppropriate data type. There's a few things to consider though.
Floats are 4 bytes of memory, can hold roughly 6 decimal places of precision and can be signed(negative) values or unsigned(positive values).
Integers are 1 to 4 bytes of memory, and can only hold whole numbers, and numbers can be Negative or Positive.
Unsigned Integers are 1 to to 4 bytes of memory, and can only hold whole numbers, and only Positive values.

## **Minimum and Maximum Values for Fixed-Width Integer Types in C**

### **Signed Integer Types (`int8_t`, `int16_t`, `int32_t`)**
| Type      | Size (bits) | Minimum Value (`2’s Complement`) | Maximum Value |
|-----------|------------|---------------------------------|--------------|
| `int8_t`  | 8          | -128 (`-2^7`)                 | 127 (`2^7 - 1`) |
| `int16_t` | 16         | -32,768 (`-2^15`)             | 32,767 (`2^15 - 1`) |
| `int32_t` | 32         | -2,147,483,648 (`-2^31`)      | 2,147,483,647 (`2^31 - 1`) |

### **Unsigned Integer Types (`uint8_t`, `uint16_t`, `uint32_t`)**
| Type       | Size (bits) | Minimum Value | Maximum Value |
|------------|------------|--------------|--------------|
| `uint8_t`  | 8          | 0            | 255 (`2^8 - 1`) |
| `uint16_t` | 16         | 0            | 65,535 (`2^16 - 1`) |
| `uint32_t` | 32         | 0            | 4,294,967,295 (`2^32 - 1`) |

---

### Storing signals as a float
```C
float process_float_value(uint32_t value, uint32_t bitmask, bool is_signed, float factor, float offset, uint8_t decimal_places);

Parameters:
value           – the byte(s) of information to be processed.
bitmask         – the bitmask to be applied to the bytes.
is_signed       – false if unsigned, true if signed.
factor          – the factor used in the DBC file.
offset          – the offset used in the DBC file.
decimal_places  – how many decimal placed you would like to round to.

Returns:
Scaled value as a float.
```
Lets assume the Engine speed is an unsigned 16 bit or 2 byte Big Endian CAN Signal on Bus 1 and Message ID 0x123 and is the first 2 bytes(indexes 0 and 1) of the Data field. It has a factor of 0.125 and an offset of 0 and we want to constrain to 3 decimal places. The code could be setup the following way. 

```C
float engine_Speed = 0.0f;
onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
        if (Message.arbitration_id == 0x123){
            // generic variable to hold the data bytes needed for the process
            uint32_t message_info = (Message.data[0]<< 8)| (Message.data[1]);
            engine_speed = process_float_value(message_info, 0xFFFF,false,0.125,0,3);
        }
    }
}
```
---
### Storing signals an integer
```C
int32_t process_int_value(uint32_t value, uint32_t bitmask, bool is_signed, int32_t factor, int32_t offset);

Parameters:
value           – the byte(s) of information to be processed.
bitmask         – the bitmask to be applied to the bytes.
is_signed       – false if unsigned, true if signed.
factor          – the factor used in the DBC file.
offset          – the offset used in the DBC file.

Returns:
Scaled value as a int32_t.
```
Lets assume the Engine Coolant Temp is an unsigned 10 bit Little Endian CAN Signal on Bus 1 and Message ID 0x124 and is the all 8 bits of the 3rd byte(index 2), and 2 bits of the 4th byte(index 3) of the Data field. It has a factor of 1 and an offset of -40. The code could be setup the following way. 

```C
int32_t engine_coolant_temp = 0;
onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
        if (Message.arbitration_id == 0x124){
            // generic variable to hold the data bytes needed for the process
            uint32_t message_info = (Message.data[3]<< 8)| (Message.data[2]);
            engine_coolant_temp = process_int_value(message_info, 0x03FF,false,1,-40);
        }
    }
}
```
---
### Storing signals an unsigned integer
```C
uint32_t process_unsigned_int_value(uint32_t value, uint32_t bitmask, uint32_t factor, uint32_t offset);

Parameters:
value           – the byte(s) of information to be processed.
bitmask         – the bitmask to be applied to the bytes.
factor          – the factor used in the DBC file.
offset          – the offset used in the DBC file.

Returns:
Scaled value as a float.
```
Lets assume the Engine Oil Pressure is an unsigned 10 bit Big Endian CAN Signal on Bus 1 and Message ID 0x125 and is the all 8 bits of the 6th byte(index 5), and 2 bits of the 5th byte(index 4) of the Data field. It has a factor of 1 and an offset of 0. The code could be setup the following way. 

```C
int32_t engine_oil_pressure = 0;
onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
        if (Message.arbitration_id == 0x125){
            // generic variable to hold the data bytes needed for the process
            uint32_t message_info = (Message.data[4]<< 8)| (Message.data[5]);
            engine_oil_pressure = process_int_value(message_info, 0x03FF,1,-40);
        }
    }
}
```
---
### Simple Bitmasking and bit shifting right (if needed)
```C
uint32_t process_raw_value(uint32_t value, uint32_t bitmask);

Parameters:
value   – the byte(s) of information to be processed.
bitmask – the bitmask to be applied to the bytes.

Returns:
Scaled value as a uint32_t.
```
Lets assume you are wanting to extract a bit field for an AC switch found on CAN Bus 2 and Message ID 0x126. first byte, 5th bit [00010000]. The code could be setup the following way.
```C
uint32_t ac_Switch = 0;
onReceive(CAN_Message Message){
	if (Message.Bus == CAN_2){
        if (Message.arbitration_id == 0x126){
            ac_switch = process_raw_value(Message.data[0], 0x10);
        }
    }
}
```
---
### Rounding floats
```C
float roundfloat(float num, uint8_t decimal_places);

Parameters:
value           – the input value.
decimal_places  – how many decimal placed you would like to round to.

Returns:
rounded value as a float.
```
---
### Converting Floats to Decimal values with *10 factor for decimal places.
```C
int32_t roundfloat_to_int32(float num, uint8_t decimal_places);

Parameters:
num             – input value.
decimal_places  – how many decimal placed you would like to round to.

Returns:
Scaled signal value as a int32_t.
```
Value will be an integer value decimal shifted by the decimal places.
```C
float startingvalue =  3.14159267;
int32_t endingvalue = roundfloat_to_int32(startingvalue, 4);
// endingvalue would == 31416
```
---
### Preparing Signals for CAN Transmission.
Preparing a CAN signal to be sent over CAN is somewhat complicated and confusing when you are dealing with signals that are not 8,16,or 32 bits in length. this function allows you to prepare a single signal to what the output should be, based on the attributes the output signal should have. 
```C
uint32_t prepare_output_signal(float value, uint8_t bitlength, bool is_signed, float dbcFactor, float dbcOffset);

Parameters:
value       - signal actual value.
bitlength   - bitlength of output signal.
is_signed   - false if unsigned, true if signed.
dbcFactor   - the scaling factor that would be used in the DBC file to read the signal appropriately.
dbcOffset   - the scaling offset that would be used in the DBC file to read the signal appropriately.

Returns:
0 if bitlength > 32, else returns scaled output signal value.
```
---



### Debugging with print statements
Debugging using print statements is offered in a few ways. This example uses a character array, snprintf, and alternatively printf.

```C
float engine_Speed = 1234.567;
float vehicle_speed = 55.2;
int32_t engine_coolant_temp = 98;
char test = "Test_Message";
char debug_buffer[100];
snprintf(debug_buffer, sizeof(debug_buffer), "Engine Speed: %5.1f, Vehicle Speed:%2.1f,Coolant Temp = %i,  %s", engine_Speed, vehicle_speed,engine_coolant_temp,  test);
printf("%s\r\n",debug_buffer);
// "Engine Speed: 1234.6, Vehicle Speed:55.2,Coolant Temp = 98,  Test_Message" would be printed to terminal..
