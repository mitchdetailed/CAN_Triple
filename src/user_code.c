/*
 * user_code.c - All User Code should be applied here unless specified otherwise.
 * 
 */

/* File Includes */
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"
#include "snprintf.h"
#include <string.h>

/* End File Includes */


/* Variable Declarations */
uint8_t example_data_1Hz[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint32_t serialnumber = 0;
uint16_t test_rpm = 500;
char test_rpm_unit[8] = "§RPM";
bool increment_rpm = true;
float testvalue;
//################ Generated Variable Declarations ################
// Copy to Variable Declarations area in user_code.c 

float Steering_Wheel;
uint32_t Steering_Angle_ROC;
uint32_t throttle_related;
uint32_t unknown0x160_B23;
uint32_t shift_tq_reduction;
uint32_t trans_related2;
uint32_t timer_0x174;
uint32_t unknown0x176_B12;
uint32_t unknown0x176_B34;
uint32_t unknown0x176_B7;
uint32_t Gear;
uint32_t Gear_Bit;
uint32_t unknown_Gear0x177;
uint32_t shifttiming_retard_maybe;
uint32_t yaw_related;
uint32_t TPS_Based;
uint32_t TPS_Based_1;
uint32_t Engine_Speed;
uint32_t hex22A_B01;
uint32_t hex22A_B23;
uint32_t hex22A_B4;
uint32_t hex22A_B5;
uint32_t hex22A_B6;
uint32_t hex22A_B7;
uint32_t hex22B_B01;
uint32_t hex22B_B23;
uint32_t hex22B_B4;
uint32_t hex22B_B5;
uint32_t hex22B_B6;
uint32_t hex22B_B7;
uint32_t hex22C_B0;
uint32_t hex22C_B1;
uint32_t hex22C_B2;
uint32_t hex22C_B3;
uint32_t hex22C_B4;
uint32_t hex22C_B5;
uint32_t hex22C_B6;
uint32_t hex22C_B7;
uint32_t hex22D_B0;
uint32_t hex22D_B1;
uint32_t hex22D_B2;
uint32_t hex230_B0;
uint32_t hex230_B1;
uint32_t hex230_B2;
uint32_t hex230_B3;
uint32_t hex230_B4;
uint32_t hex230_B5;
uint32_t hex230_B67;
uint32_t hex231_B0;
uint32_t hex231_B12;
uint32_t hex232_B0;
uint32_t hex232_B1;
uint32_t hex232_B2;
uint32_t hex233_B0;
uint32_t hex233_B1;
uint32_t hex233_B2;
uint32_t hex233_B3;
uint32_t hex233_B4;
uint32_t hex233_B5;
uint32_t hex233_B6;
uint32_t hex233_B7;
uint32_t hex234_B0;
uint32_t hex234_B1;
uint32_t hex234_B2;
uint32_t hex234_B3;
float Accel_Pedal;
float TPS_Inverted;
uint32_t Cruise_Enabled;
uint32_t DCA_Pressed;
uint32_t no_steering_buttons_pressed;
uint32_t Cruise_Accel_Res;
uint32_t Cruise_Decel_Set;
uint32_t DCA_Distance_Pressed;
uint32_t cruise_cancel_pressed;
uint32_t Cruise_Button_Pressed;
uint32_t brake_pedal_depressed;
uint32_t Traction_Control_Disable_Bit_1;
uint32_t Counter_0x245;
uint32_t Doorlock_engagements;
uint32_t VSS_Based_1;
uint32_t TQ_Converter_Pres;
float WS_1;
float WS_2;
uint32_t WS_related;
uint32_t Counter_0x284;
uint32_t Odd_Signal_0x284B8;
float WS_3;
float WS_4;
uint32_t Vehicle_Speed_or_ws;
uint32_t Counter_0x285;
uint32_t Odd_Signal_0x285B8;
uint32_t something_tq_related;
uint32_t odd_tps_or_speed_0x286B2;
uint32_t odd_tps_or_speed_0x286B3;
uint32_t unknown0x286_B5;
uint32_t odd_tps_or_speed_0x286B4;
float Pitch;
float Yaw;
float Roll;
uint32_t TPS_overrun;
uint32_t Brake_Pres;
float Steering_Wheel_360;
uint32_t Traction_Control_Disable_Bit;
uint32_t tow_mode_button_engaged;
uint32_t hex330_B01;
uint32_t hex330_B23;
uint32_t hex330_B45;
uint32_t hex330_B67;
uint32_t hex340_B01;
uint32_t hex340_B23;
uint32_t hex340_B45;
uint32_t hex340_B67;
uint32_t hex350_B0;
uint32_t hex350_B1;
uint32_t hex350_B2;
uint32_t hex350_B3;
uint32_t hex350_B4;
uint32_t hex350_B5;
uint32_t hex350_B6;
uint32_t hex350_B7;
uint32_t VSS_Based_2;
uint32_t VSS_Based;
uint32_t Vss_Based_3;
uint32_t Rear__Defrost;
uint32_t hex360_B0;
uint32_t hex360_B1;
uint32_t hex360_B2;
uint32_t hex360_B3;
uint32_t hex360_B4;
uint32_t hex360_B5;
uint32_t hex360_B6;
uint32_t hex360_B7;
uint32_t hex370_B01;
uint32_t hex370_B23;
uint32_t hex370_B45;
uint32_t hex370_B67;
float tpms_FR;
float tpms_FL;
float tpms_RR;
float tpms_RL;
uint32_t RL_TPMS_Activated;
uint32_t RR_TPMS_Activated;
uint32_t FL_TPMS_Activated;
uint32_t FR_TPMS_Activated;
uint32_t hex3FF_B0;
uint32_t hex3FF_B1;
uint32_t hex3FF_B2;
uint32_t hex3FF_B3;
uint32_t hex3FF_B4;
uint32_t hex3FF_B5;
uint32_t hex3FF_B6;
uint32_t hex3FF_B7;
uint32_t Shifter_Position;
uint32_t Tow_Mode;
uint32_t Front_Defrost_Inverted_Active;
uint32_t HVAC_Overhead_Inverted_Bit;
uint32_t HVAC_R_Defrost_Buttonpress;
uint32_t HVAC_Recirc_Press_Changestate;
uint32_t HVAC_Freshair_Press_Changestate;
uint32_t HVAC_Off_Buttonpress_Changestate;
uint32_t HVAC_AC_Enabled_Bit;
uint32_t RH_HVAC__Knobpress_Changestate;
uint32_t HVAC_Fan_Decel_Changestate;
uint32_t HVAC_Fan_Accel_Changestate;
uint32_t LH_HVAC_Knobpress_Changestate;
uint32_t HVAC_Rear_Press_ChangeState;
uint32_t LH_AC_Temp;
uint32_t RH_AC_temp;
uint32_t unknoen0x551_B12;
uint32_t TPS_Target;
uint32_t Throttle_Based;
uint32_t Snow_Mode_Enabled;
uint32_t Left_Turnsignal;
uint32_t Right_Turnsignal;
uint32_t Door_Lock_switch;
uint32_t Door_Lock_State;
uint32_t Frame_Type;
uint32_t Single_Frame_length;
uint32_t Service_ID;
uint32_t Brake_Switch;
uint32_t AC_Signal;
uint32_t VVEL_Timing_B2_unscaled;
uint32_t VVEL_Timing_B1_unscaled;
float VVEL_Sensor_B2;
float VVEL_Sensor_B1;
float VTC_Exh_B2_Duty_Cycle;
float VTC_Exh_B1_Duty_Cycle;
float Vehicle_Speed;
float Throttle_Pos_S1_B2;
float Throttle_Pos_S1_B1;
uint32_t EVAP_Purge_Control_Valve_DC;
float MAF;
float MAF_Sensor;
float Intake_Valve_Timing_B2;
float Intake_Valve_Solenoid_B1_Duty;
int32_t Intake_Air_Temp;
int32_t Ingition_Timing;
uint32_t IP_Pulley_Speed;
float Ho2_S2_B2;
float Ho2_S2_B1;
float Intake_Valve_Timing_B1;
float Hi_pres_Fuel_Pump;
uint32_t Fuel_Temp;
uint32_t Fuel_Pump_Relay;
uint32_t Fuel_Pump_Duty_Cycle;
uint32_t Fuel_Pressure_Sensor;
float Fuel_Pressure;
float Fuel_Level_Sensor;
float Fuel_Injector_Pulse_Width_B2;
float Fuel_Injector_Pulse_Width_B1;
int32_t Fuel_Injection_Timing;
uint32_t Fan_Duty_Cycle;
float EXH_Valve_Timing_B2;
float EXH_Valve_Timing_B1;
float EVAP_System_Pressure_Sensor;
uint32_t Engine_Oil_Pressure_Sensor;
int32_t Engine_Oil_Temp;
float Cooling_Fan_Speed;
int32_t Engine_Coolant_Temp;
float Calculated_Load;
float Battery_Voltage;
float Battery_Temp_Sensor;
uint32_t Battery_Current_Sensor;
float Base_Fuel_Schedule;
float Alternator_Duty_Cycle;
uint32_t AC_Relay;
float Accel_Sensor_2;
float Accel_Sensor_1;
float AC_Pressure_Sensor;
float AC_Evap_Temp;
float AC_Evap_Target;
float Air_Fuel_S1_B2;
float Air_Fuel_S1_B1;
float Air_Fuel_S1_Heater_B2;
float Air_Fuel_S1_Heater_B1;
uint32_t Air_Fuel_Alpha_B2;
uint32_t Air_Fuel_Alpha_B1;
uint32_t Mode22_DID;
//################ End Generated Variable Declarations ################


/* Startup Functions */
void events_Startup(){
	setCANBitrate(CAN_1, 1000000);
	setCANBitrate(CAN_2, 1000000);
	setCANBitrate(CAN_3, 1000000);
	setCAN_Termination(CAN_1,true);
	setCAN_Termination(CAN_2, true);
	setCAN_Termination(CAN_3, true);
	startCANbus(CAN_1);
	startCANbus(CAN_2);
	startCANbus(CAN_3);
	serialnumber = getSerialNumber();

}
/* End Startup Functions */


void onReceive(CAN_Message Message){
	if (Message.Bus == CAN_1){
//################ Generated CAN Code ################
//Copy Code Below to appropriate Message.bus statement in user_code.c

		if (Message.arbitration_id == 0x2) {
		// Signal: Steering_Wheel
		// Start bit: 0, Length: 16, Byte Order: little
		Steering_Wheel = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, true, 0.1, 0, 3);

		// Signal: Steering_Angle_ROC
		// Start bit: 23, Length: 8, Byte Order: big
		Steering_Angle_ROC = process_raw_value((uint32_t)Message.data[2], 0xFF);

		}

		if (Message.arbitration_id == 0x160) {
		// Signal: throttle_related
		// Start bit: 7, Length: 12, Byte Order: big
		throttle_related = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFF0);

		// Signal: unknown0x160_B23
		// Start bit: 11, Length: 12, Byte Order: big
		unknown0x160_B23 = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[2], 0xFFF);

		}

		if (Message.arbitration_id == 0x174) {
		// Signal: shift_tq_reduction
		// Start bit: 7, Length: 12, Byte Order: big
		shift_tq_reduction = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFF0);

		// Signal: trans_related2
		// Start bit: 11, Length: 12, Byte Order: big
		trans_related2 = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[2], 0xFFF);

		// Signal: timer_0x174
		// Start bit: 35, Length: 4, Byte Order: big
		timer_0x174 = process_raw_value((uint32_t)Message.data[4], 0xF);

		}

		if (Message.arbitration_id == 0x176) {
		// Signal: unknown0x176_B12
		// Start bit: 7, Length: 16, Byte Order: big
		unknown0x176_B12 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: unknown0x176_B34
		// Start bit: 19, Length: 12, Byte Order: big
		unknown0x176_B34 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFF);

		// Signal: unknown0x176_B7
		// Start bit: 55, Length: 8, Byte Order: big
		unknown0x176_B7 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		}

		if (Message.arbitration_id == 0x177) {
		// Signal: Gear
		// Start bit: 18, Length: 3, Byte Order: big
		Gear = process_unsigned_int_value((uint32_t)Message.data[2], 0x7, 1, 1);

		// Signal: Gear_Bit
		// Start bit: 19, Length: 1, Byte Order: big
		Gear_Bit = process_raw_value((uint32_t)Message.data[2], 0x8);

		// Signal: unknown_Gear0x177
		// Start bit: 39, Length: 8, Byte Order: big
		unknown_Gear0x177 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: shifttiming_retard_maybe
		// Start bit: 63, Length: 8, Byte Order: big
		shifttiming_retard_maybe = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x180) {
		// Signal: yaw_related
		// Start bit: 6, Length: 10, Byte Order: big
		yaw_related = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0x7FE0);

		// Signal: TPS_Based
		// Start bit: 23, Length: 12, Byte Order: big
		TPS_Based = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFF0);

		// Signal: TPS_Based_1
		// Start bit: 27, Length: 12, Byte Order: big
		TPS_Based_1 = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[4], 0xFFF);

		}

		if (Message.arbitration_id == 0x1F9) {
		// Signal: Engine_Speed
		// Start bit: 23, Length: 13, Byte Order: big
		Engine_Speed = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFF8);

		}

		if (Message.arbitration_id == 0x22A) {
		// Signal: hex22A_B01
		// Start bit: 7, Length: 16, Byte Order: big
		hex22A_B01 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: hex22A_B23
		// Start bit: 23, Length: 16, Byte Order: big
		hex22A_B23 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		// Signal: hex22A_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex22A_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex22A_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex22A_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex22A_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex22A_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex22A_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex22A_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x22B) {
		// Signal: hex22B_B01
		// Start bit: 7, Length: 16, Byte Order: big
		hex22B_B01 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: hex22B_B23
		// Start bit: 23, Length: 16, Byte Order: big
		hex22B_B23 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		// Signal: hex22B_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex22B_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex22B_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex22B_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex22B_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex22B_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex22B_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex22B_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x22C) {
		// Signal: hex22C_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex22C_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex22C_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex22C_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex22C_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex22C_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex22C_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex22C_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		// Signal: hex22C_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex22C_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex22C_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex22C_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex22C_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex22C_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex22C_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex22C_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x22D) {
		// Signal: hex22D_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex22D_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex22D_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex22D_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex22D_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex22D_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		}

		if (Message.arbitration_id == 0x230) {
		// Signal: hex230_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex230_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex230_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex230_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex230_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex230_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex230_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex230_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		// Signal: hex230_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex230_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex230_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex230_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex230_B67
		// Start bit: 55, Length: 16, Byte Order: big
		hex230_B67 = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);

		}

		if (Message.arbitration_id == 0x231) {
		// Signal: hex231_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex231_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex231_B12
		// Start bit: 15, Length: 16, Byte Order: big
		hex231_B12 = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[2], 0xFFFF);

		}

		if (Message.arbitration_id == 0x232) {
		// Signal: hex232_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex232_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex232_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex232_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex232_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex232_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		}

		if (Message.arbitration_id == 0x233) {
		// Signal: hex233_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex233_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex233_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex233_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex233_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex233_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex233_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex233_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		// Signal: hex233_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex233_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex233_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex233_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex233_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex233_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex233_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex233_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x234) {
		// Signal: hex234_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex234_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex234_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex234_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex234_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex234_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex234_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex234_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		}

		if (Message.arbitration_id == 0x239) {
		// Signal: Accel_Pedal
		// Start bit: 7, Length: 8, Byte Order: big
		Accel_Pedal = process_float_value((uint32_t)Message.data[0], 0xFF, false, 0.39215686275, 0, 3);

		// Signal: TPS_Inverted
		// Start bit: 15, Length: 8, Byte Order: big
		TPS_Inverted = process_float_value((uint32_t)Message.data[1], 0xFF, false, 0.39215686275, 0, 3);

		// Signal: Cruise_Enabled
		// Start bit: 22, Length: 1, Byte Order: big
		Cruise_Enabled = process_raw_value((uint32_t)Message.data[2], 0x40);

		// Signal: DCA_Pressed
		// Start bit: 25, Length: 1, Byte Order: big
		DCA_Pressed = process_raw_value((uint32_t)Message.data[3], 0x2);

		// Signal: no_steering_buttons_pressed
		// Start bit: 26, Length: 1, Byte Order: big
		no_steering_buttons_pressed = process_raw_value((uint32_t)Message.data[3], 0x4);

		// Signal: Cruise_Accel_Res
		// Start bit: 27, Length: 1, Byte Order: big
		Cruise_Accel_Res = process_raw_value((uint32_t)Message.data[3], 0x8);

		// Signal: Cruise_Decel_Set
		// Start bit: 28, Length: 1, Byte Order: big
		Cruise_Decel_Set = process_raw_value((uint32_t)Message.data[3], 0x10);

		// Signal: DCA_Distance_Pressed
		// Start bit: 29, Length: 1, Byte Order: big
		DCA_Distance_Pressed = process_raw_value((uint32_t)Message.data[3], 0x20);

		// Signal: cruise_cancel_pressed
		// Start bit: 30, Length: 1, Byte Order: big
		cruise_cancel_pressed = process_raw_value((uint32_t)Message.data[3], 0x40);

		// Signal: Cruise_Button_Pressed
		// Start bit: 31, Length: 1, Byte Order: big
		Cruise_Button_Pressed = process_raw_value((uint32_t)Message.data[3], 0x80);

		// Signal: brake_pedal_depressed
		// Start bit: 33, Length: 1, Byte Order: big
		brake_pedal_depressed = process_raw_value((uint32_t)Message.data[4], 0x2);

		}

		if (Message.arbitration_id == 0x245) {
		// Signal: Traction_Control_Disable_Bit_1
		// Start bit: 24, Length: 1, Byte Order: big
		Traction_Control_Disable_Bit_1 = process_raw_value((uint32_t)Message.data[3], 0x1);

		// Signal: Counter_0x245
		// Start bit: 39, Length: 8, Byte Order: big
		Counter_0x245 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		}

		if (Message.arbitration_id == 0x280) {
		// Signal: Doorlock_engagements
		// Start bit: 7, Length: 8, Byte Order: big
		Doorlock_engagements = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: VSS_Based_1
		// Start bit: 37, Length: 14, Byte Order: big
		VSS_Based_1 = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0x3FFF);

		// Signal: TQ_Converter_Pres
		// Start bit: 55, Length: 8, Byte Order: big
		TQ_Converter_Pres = process_raw_value((uint32_t)Message.data[6], 0xFF);

		}

		if (Message.arbitration_id == 0x284) {
		// Signal: WS_1
		// Start bit: 7, Length: 16, Byte Order: big
		WS_1 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.0041, 0, 3);

		// Signal: WS_2
		// Start bit: 23, Length: 16, Byte Order: big
		WS_2 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.0041, 0, 3);

		// Signal: WS_related
		// Start bit: 39, Length: 16, Byte Order: big
		WS_related = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

		// Signal: Counter_0x284
		// Start bit: 55, Length: 8, Byte Order: big
		Counter_0x284 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: Odd_Signal_0x284B8
		// Start bit: 63, Length: 8, Byte Order: big
		Odd_Signal_0x284B8 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x285) {
		// Signal: WS_3
		// Start bit: 7, Length: 16, Byte Order: big
		WS_3 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.0041, 0, 3);

		// Signal: WS_4
		// Start bit: 23, Length: 16, Byte Order: big
		WS_4 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.0041, 0, 3);

		// Signal: Vehicle_Speed_or_ws
		// Start bit: 39, Length: 8, Byte Order: big
		Vehicle_Speed_or_ws = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: Counter_0x285
		// Start bit: 55, Length: 8, Byte Order: big
		Counter_0x285 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: Odd_Signal_0x285B8
		// Start bit: 63, Length: 8, Byte Order: big
		Odd_Signal_0x285B8 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x286) {
		// Signal: something_tq_related
		// Start bit: 7, Length: 8, Byte Order: big
		something_tq_related = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: odd_tps_or_speed_0x286B2
		// Start bit: 13, Length: 7, Byte Order: big
		odd_tps_or_speed_0x286B2 = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[2], 0x3F80);

		// Signal: odd_tps_or_speed_0x286B3
		// Start bit: 22, Length: 7, Byte Order: big
		odd_tps_or_speed_0x286B3 = process_raw_value((uint32_t)Message.data[2], 0x7F);

		// Signal: unknown0x286_B5
		// Start bit: 24, Length: 7, Byte Order: big
		unknown0x286_B5 = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[4], 0x1FC);

		// Signal: odd_tps_or_speed_0x286B4
		// Start bit: 31, Length: 7, Byte Order: big
		odd_tps_or_speed_0x286B4 = process_raw_value((uint32_t)Message.data[3], 0xFE);

		}

		if (Message.arbitration_id == 0x292) {
		// Signal: Pitch
		// Start bit: 7, Length: 12, Byte Order: big
		Pitch = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFF0, false, 0.1, -204.8, 3);

		// Signal: Yaw
		// Start bit: 11, Length: 12, Byte Order: big
		Yaw = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[2], 0xFFF, false, 0.75, -153.6, 3);

		// Signal: Roll
		// Start bit: 31, Length: 11, Byte Order: big
		Roll = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[4], 0xFFE0, false, 0.1, -102.4, 3);

		// Signal: TPS_overrun
		// Start bit: 55, Length: 8, Byte Order: big
		TPS_overrun = process_raw_value((uint32_t)Message.data[6], 0xFF);

		}

		if (Message.arbitration_id == 0x2AA) {
		// Signal: Brake_Pres
		// Start bit: 47, Length: 16, Byte Order: big
		Brake_Pres = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[6], 0xFFFF);

		}

		if (Message.arbitration_id == 0x2AB) {
		// Signal: Steering_Wheel_360
		// Start bit: 17, Length: 13, Byte Order: big
		Steering_Wheel_360 = process_float_value(((uint32_t)Message.data[2] << 16) | ((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[4], 0x3FFE0, true, 0.1, 0, 3);

		}

		if (Message.arbitration_id == 0x2B3) {
		// Signal: Traction_Control_Disable_Bit
		// Start bit: 25, Length: 1, Byte Order: big
		Traction_Control_Disable_Bit = process_raw_value((uint32_t)Message.data[3], 0x2);

		}

		if (Message.arbitration_id == 0x2DE) {
		// Signal: tow_mode_button_engaged
		// Start bit: 15, Length: 1, Byte Order: big
		tow_mode_button_engaged = process_raw_value((uint32_t)Message.data[1], 0x80);

		}

		if (Message.arbitration_id == 0x330) {
		// Signal: hex330_B01
		// Start bit: 7, Length: 16, Byte Order: big
		hex330_B01 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: hex330_B23
		// Start bit: 23, Length: 16, Byte Order: big
		hex330_B23 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		// Signal: hex330_B45
		// Start bit: 39, Length: 16, Byte Order: big
		hex330_B45 = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

		// Signal: hex330_B67
		// Start bit: 55, Length: 16, Byte Order: big
		hex330_B67 = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);

		}

		if (Message.arbitration_id == 0x340) {
		// Signal: hex340_B01
		// Start bit: 7, Length: 16, Byte Order: big
		hex340_B01 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: hex340_B23
		// Start bit: 23, Length: 16, Byte Order: big
		hex340_B23 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		// Signal: hex340_B45
		// Start bit: 39, Length: 16, Byte Order: big
		hex340_B45 = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

		// Signal: hex340_B67
		// Start bit: 55, Length: 16, Byte Order: big
		hex340_B67 = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);

		}

		if (Message.arbitration_id == 0x350) {
		// Signal: hex350_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex350_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex350_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex350_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex350_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex350_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex350_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex350_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		// Signal: hex350_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex350_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex350_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex350_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex350_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex350_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex350_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex350_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x354) {
		// Signal: VSS_Based_2
		// Start bit: 7, Length: 16, Byte Order: big
		VSS_Based_2 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		}

		if (Message.arbitration_id == 0x355) {
		// Signal: VSS_Based
		// Start bit: 7, Length: 16, Byte Order: big
		VSS_Based = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: Vss_Based_3
		// Start bit: 23, Length: 16, Byte Order: big
		Vss_Based_3 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		}

		if (Message.arbitration_id == 0x35D) {
		// Signal: Rear__Defrost
		// Start bit: 2, Length: 2, Byte Order: big
		Rear__Defrost = process_raw_value((uint32_t)Message.data[0], 0x6);

		}

		if (Message.arbitration_id == 0x360) {
		// Signal: hex360_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex360_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex360_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex360_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex360_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex360_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex360_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex360_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		// Signal: hex360_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex360_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex360_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex360_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex360_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex360_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex360_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex360_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x370) {
		// Signal: hex370_B01
		// Start bit: 7, Length: 16, Byte Order: big
		hex370_B01 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: hex370_B23
		// Start bit: 23, Length: 16, Byte Order: big
		hex370_B23 = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		// Signal: hex370_B45
		// Start bit: 39, Length: 16, Byte Order: big
		hex370_B45 = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

		// Signal: hex370_B67
		// Start bit: 55, Length: 16, Byte Order: big
		hex370_B67 = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);

		}

		if (Message.arbitration_id == 0x385) {
		// Signal: tpms_FR
		// Start bit: 23, Length: 8, Byte Order: big
		tpms_FR = process_float_value((uint32_t)Message.data[2], 0xFF, false, 1.7325, 0, 3);

		// Signal: tpms_FL
		// Start bit: 31, Length: 8, Byte Order: big
		tpms_FL = process_float_value((uint32_t)Message.data[3], 0xFF, false, 1.7325, 0, 3);

		// Signal: tpms_RR
		// Start bit: 39, Length: 8, Byte Order: big
		tpms_RR = process_float_value((uint32_t)Message.data[4], 0xFF, false, 1.7325, 0, 3);

		// Signal: tpms_RL
		// Start bit: 47, Length: 8, Byte Order: big
		tpms_RL = process_float_value((uint32_t)Message.data[5], 0xFF, false, 1.7325, 0, 3);

		// Signal: RL_TPMS_Activated
		// Start bit: 52, Length: 1, Byte Order: big
		RL_TPMS_Activated = process_raw_value((uint32_t)Message.data[6], 0x10);

		// Signal: RR_TPMS_Activated
		// Start bit: 53, Length: 1, Byte Order: big
		RR_TPMS_Activated = process_raw_value((uint32_t)Message.data[6], 0x20);

		// Signal: FL_TPMS_Activated
		// Start bit: 54, Length: 1, Byte Order: big
		FL_TPMS_Activated = process_raw_value((uint32_t)Message.data[6], 0x40);

		// Signal: FR_TPMS_Activated
		// Start bit: 55, Length: 1, Byte Order: big
		FR_TPMS_Activated = process_raw_value((uint32_t)Message.data[6], 0x80);

		}

		if (Message.arbitration_id == 0x3FF) {
		// Signal: hex3FF_B0
		// Start bit: 7, Length: 8, Byte Order: big
		hex3FF_B0 = process_raw_value((uint32_t)Message.data[0], 0xFF);

		// Signal: hex3FF_B1
		// Start bit: 15, Length: 8, Byte Order: big
		hex3FF_B1 = process_raw_value((uint32_t)Message.data[1], 0xFF);

		// Signal: hex3FF_B2
		// Start bit: 23, Length: 8, Byte Order: big
		hex3FF_B2 = process_raw_value((uint32_t)Message.data[2], 0xFF);

		// Signal: hex3FF_B3
		// Start bit: 31, Length: 8, Byte Order: big
		hex3FF_B3 = process_raw_value((uint32_t)Message.data[3], 0xFF);

		// Signal: hex3FF_B4
		// Start bit: 39, Length: 8, Byte Order: big
		hex3FF_B4 = process_raw_value((uint32_t)Message.data[4], 0xFF);

		// Signal: hex3FF_B5
		// Start bit: 47, Length: 8, Byte Order: big
		hex3FF_B5 = process_raw_value((uint32_t)Message.data[5], 0xFF);

		// Signal: hex3FF_B6
		// Start bit: 55, Length: 8, Byte Order: big
		hex3FF_B6 = process_raw_value((uint32_t)Message.data[6], 0xFF);

		// Signal: hex3FF_B7
		// Start bit: 63, Length: 8, Byte Order: big
		hex3FF_B7 = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x421) {
		// Signal: Shifter_Position
		// Start bit: 7, Length: 5, Byte Order: big
		Shifter_Position = process_raw_value((uint32_t)Message.data[0], 0xF8);

		// Signal: Tow_Mode
		// Start bit: 19, Length: 1, Byte Order: big
		Tow_Mode = process_raw_value((uint32_t)Message.data[2], 0x8);

		}

		if (Message.arbitration_id == 0x541) {
		// Signal: Front_Defrost_Inverted_Active
		// Start bit: 0, Length: 1, Byte Order: big
		Front_Defrost_Inverted_Active = process_raw_value((uint32_t)Message.data[0], 0x1);

		// Signal: HVAC_Overhead_Inverted_Bit
		// Start bit: 5, Length: 1, Byte Order: big
		HVAC_Overhead_Inverted_Bit = process_raw_value((uint32_t)Message.data[0], 0x20);

		// Signal: HVAC_R_Defrost_Buttonpress
		// Start bit: 8, Length: 1, Byte Order: big
		HVAC_R_Defrost_Buttonpress = process_raw_value((uint32_t)Message.data[1], 0x1);

		// Signal: HVAC_Recirc_Press_Changestate
		// Start bit: 9, Length: 1, Byte Order: big
		HVAC_Recirc_Press_Changestate = process_raw_value((uint32_t)Message.data[1], 0x2);

		// Signal: HVAC_Freshair_Press_Changestate
		// Start bit: 11, Length: 1, Byte Order: big
		HVAC_Freshair_Press_Changestate = process_raw_value((uint32_t)Message.data[1], 0x8);

		// Signal: HVAC_Off_Buttonpress_Changestate
		// Start bit: 16, Length: 1, Byte Order: big
		HVAC_Off_Buttonpress_Changestate = process_raw_value((uint32_t)Message.data[2], 0x1);

		// Signal: HVAC_AC_Enabled_Bit
		// Start bit: 18, Length: 1, Byte Order: big
		HVAC_AC_Enabled_Bit = process_raw_value((uint32_t)Message.data[2], 0x4);

		// Signal: RH_HVAC__Knobpress_Changestate
		// Start bit: 19, Length: 1, Byte Order: big
		RH_HVAC__Knobpress_Changestate = process_raw_value((uint32_t)Message.data[2], 0x8);

		// Signal: HVAC_Fan_Decel_Changestate
		// Start bit: 27, Length: 1, Byte Order: big
		HVAC_Fan_Decel_Changestate = process_raw_value((uint32_t)Message.data[3], 0x8);

		// Signal: HVAC_Fan_Accel_Changestate
		// Start bit: 28, Length: 1, Byte Order: big
		HVAC_Fan_Accel_Changestate = process_raw_value((uint32_t)Message.data[3], 0x10);

		// Signal: LH_HVAC_Knobpress_Changestate
		// Start bit: 31, Length: 1, Byte Order: big
		LH_HVAC_Knobpress_Changestate = process_raw_value((uint32_t)Message.data[3], 0x80);

		// Signal: HVAC_Rear_Press_ChangeState
		// Start bit: 36, Length: 1, Byte Order: big
		HVAC_Rear_Press_ChangeState = process_raw_value((uint32_t)Message.data[4], 0x10);

		}

		if (Message.arbitration_id == 0x54A) {
		// Signal: LH_AC_Temp
		// Start bit: 38, Length: 7, Byte Order: big
		LH_AC_Temp = process_raw_value((uint32_t)Message.data[4], 0x7F);

		// Signal: RH_AC_temp
		// Start bit: 46, Length: 7, Byte Order: big
		RH_AC_temp = process_raw_value((uint32_t)Message.data[5], 0x7F);

		}

		if (Message.arbitration_id == 0x551) {
		// Signal: unknoen0x551_B12
		// Start bit: 7, Length: 16, Byte Order: big
		unknoen0x551_B12 = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		}

		if (Message.arbitration_id == 0x580) {
		// Signal: TPS_Target
		// Start bit: 7, Length: 16, Byte Order: big
		TPS_Target = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

		// Signal: Throttle_Based
		// Start bit: 63, Length: 8, Byte Order: big
		Throttle_Based = process_raw_value((uint32_t)Message.data[7], 0xFF);

		}

		if (Message.arbitration_id == 0x5C5) {
		// Signal: Snow_Mode_Enabled
		// Start bit: 55, Length: 1, Byte Order: big
		Snow_Mode_Enabled = process_raw_value((uint32_t)Message.data[6], 0x80);

		}

		if (Message.arbitration_id == 0x60D) {
		// Signal: Left_Turnsignal
		// Start bit: 13, Length: 1, Byte Order: big
		Left_Turnsignal = process_raw_value((uint32_t)Message.data[1], 0x20);

		// Signal: Right_Turnsignal
		// Start bit: 14, Length: 1, Byte Order: big
		Right_Turnsignal = process_raw_value((uint32_t)Message.data[1], 0x40);

		// Signal: Door_Lock_switch
		// Start bit: 19, Length: 1, Byte Order: big
		Door_Lock_switch = process_raw_value((uint32_t)Message.data[2], 0x8);

		// Signal: Door_Lock_State
		// Start bit: 20, Length: 1, Byte Order: big
		Door_Lock_State = process_raw_value((uint32_t)Message.data[2], 0x10);

		}

		if (Message.arbitration_id == 0x7E8) {
		// Signal: Frame_Type
		// Start bit: 7, Length: 4, Byte Order: big
		Frame_Type = process_raw_value((uint32_t)Message.data[0], 0xF0);

			if (Frame_Type == 0) {
			// Signal: Single_Frame_length
			// Start bit: 3, Length: 4, Byte Order: big
			Single_Frame_length = process_raw_value((uint32_t)Message.data[0], 0xF);

			// Signal: Service_ID
			// Start bit: 15, Length: 8, Byte Order: big
			Service_ID = process_raw_value((uint32_t)Message.data[1], 0xFF);

			}
			if (Mode22_DID == 4869) {
			// Signal: Brake_Switch
			// Start bit: 34, Length: 1, Byte Order: big
			Brake_Switch = process_raw_value((uint32_t)Message.data[4], 0x4);

			// Signal: AC_Signal
			// Start bit: 36, Length: 1, Byte Order: big
			AC_Signal = process_raw_value((uint32_t)Message.data[4], 0x10);

			// Signal: VVEL_Timing_B2_unscaled
			// Start bit: 39, Length: 16, Byte Order: big
			VVEL_Timing_B2_unscaled = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

			// Signal: VVEL_Timing_B1_unscaled
			// Start bit: 39, Length: 16, Byte Order: big
			VVEL_Timing_B1_unscaled = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

			// Signal: VVEL_Sensor_B2
			// Start bit: 39, Length: 16, Byte Order: big
			VVEL_Sensor_B2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.01, -0.06, 3);

			// Signal: VVEL_Sensor_B1
			// Start bit: 39, Length: 16, Byte Order: big
			VVEL_Sensor_B1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.01, -0.06, 3);

			// Signal: VTC_Exh_B2_Duty_Cycle
			// Start bit: 39, Length: 16, Byte Order: big
			VTC_Exh_B2_Duty_Cycle = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

			// Signal: VTC_Exh_B1_Duty_Cycle
			// Start bit: 39, Length: 16, Byte Order: big
			VTC_Exh_B1_Duty_Cycle = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

			// Signal: Vehicle_Speed
			// Start bit: 39, Length: 16, Byte Order: big
			Vehicle_Speed = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

			// Signal: Throttle_Pos_S1_B2
			// Start bit: 39, Length: 16, Byte Order: big
			Throttle_Pos_S1_B2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: Throttle_Pos_S1_B1
			// Start bit: 39, Length: 16, Byte Order: big
			Throttle_Pos_S1_B1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: EVAP_Purge_Control_Valve_DC
			// Start bit: 39, Length: 8, Byte Order: big
			EVAP_Purge_Control_Valve_DC = process_raw_value((uint32_t)Message.data[4], 0xFF);

			// Signal: MAF
			// Start bit: 39, Length: 16, Byte Order: big
			MAF = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.01, 0, 3);

			// Signal: MAF_Sensor
			// Start bit: 39, Length: 16, Byte Order: big
			MAF_Sensor = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: Intake_Valve_Timing_B2
			// Start bit: 39, Length: 16, Byte Order: big
			Intake_Valve_Timing_B2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.5, -16384, 3);

			// Signal: Intake_Valve_Solenoid_B1_Duty
			// Start bit: 39, Length: 8, Byte Order: big
			Intake_Valve_Solenoid_B1_Duty = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.39215686275, 0, 3);

			// Signal: Intake_Air_Temp
			// Start bit: 39, Length: 8, Byte Order: big
			Intake_Air_Temp = process_int_value((uint32_t)Message.data[4], 0xFF, false, 1, -50);

			// Signal: Ingition_Timing
			// Start bit: 39, Length: 8, Byte Order: big
			Ingition_Timing = process_int_value((uint32_t)Message.data[4], 0xFF, false, -1, 80);

			// Signal: IP_Pulley_Speed
			// Start bit: 39, Length: 16, Byte Order: big
			IP_Pulley_Speed = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

			// Signal: Ho2_S2_B2
			// Start bit: 39, Length: 8, Byte Order: big
			Ho2_S2_B2 = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.01, 0, 3);

			// Signal: Ho2_S2_B1
			// Start bit: 39, Length: 8, Byte Order: big
			Ho2_S2_B1 = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.01, 0, 3);

			// Signal: Intake_Valve_Timing_B1
			// Start bit: 39, Length: 16, Byte Order: big
			Intake_Valve_Timing_B1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.5, -16384, 3);

			// Signal: Hi_pres_Fuel_Pump
			// Start bit: 39, Length: 16, Byte Order: big
			Hi_pres_Fuel_Pump = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

			// Signal: Fuel_Temp
			// Start bit: 39, Length: 8, Byte Order: big
			Fuel_Temp = process_raw_value((uint32_t)Message.data[4], 0xFF);

			// Signal: Fuel_Pump_Relay
			// Start bit: 39, Length: 16, Byte Order: big
			Fuel_Pump_Relay = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

			// Signal: Fuel_Pump_Duty_Cycle
			// Start bit: 39, Length: 8, Byte Order: big
			Fuel_Pump_Duty_Cycle = process_raw_value((uint32_t)Message.data[4], 0xFF);

			// Signal: Fuel_Pressure_Sensor
			// Start bit: 39, Length: 16, Byte Order: big
			Fuel_Pressure_Sensor = process_unsigned_int_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, 5, 0);

			// Signal: Fuel_Pressure
			// Start bit: 39, Length: 16, Byte Order: big
			Fuel_Pressure = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.33333333333, 0, 3);

			// Signal: Fuel_Level_Sensor
			// Start bit: 39, Length: 8, Byte Order: big
			Fuel_Level_Sensor = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.04, 0, 3);

			// Signal: Fuel_Injector_Pulse_Width_B2
			// Start bit: 39, Length: 16, Byte Order: big
			Fuel_Injector_Pulse_Width_B2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.01, 0.34, 3);

			// Signal: Fuel_Injector_Pulse_Width_B1
			// Start bit: 39, Length: 16, Byte Order: big
			Fuel_Injector_Pulse_Width_B1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.01, 0.34, 3);

			// Signal: Fuel_Injection_Timing
			// Start bit: 39, Length: 8, Byte Order: big
			Fuel_Injection_Timing = process_int_value((uint32_t)Message.data[4], 0xFF, true, 1, 26);

			// Signal: Fan_Duty_Cycle
			// Start bit: 39, Length: 8, Byte Order: big
			Fan_Duty_Cycle = process_raw_value((uint32_t)Message.data[4], 0xFF);

			// Signal: EXH_Valve_Timing_B2
			// Start bit: 39, Length: 8, Byte Order: big
			EXH_Valve_Timing_B2 = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.5, -64, 3);

			// Signal: EXH_Valve_Timing_B1
			// Start bit: 39, Length: 8, Byte Order: big
			EXH_Valve_Timing_B1 = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.5, -64, 3);

			// Signal: EVAP_System_Pressure_Sensor
			// Start bit: 39, Length: 8, Byte Order: big
			EVAP_System_Pressure_Sensor = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.02, 0, 3);

			// Signal: Engine_Oil_Pressure_Sensor
			// Start bit: 39, Length: 16, Byte Order: big
			Engine_Oil_Pressure_Sensor = process_unsigned_int_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, 5, 0);

			// Signal: Engine_Oil_Temp
			// Start bit: 39, Length: 8, Byte Order: big
			Engine_Oil_Temp = process_int_value((uint32_t)Message.data[4], 0xFF, false, 1, -50);

			// Signal: Cooling_Fan_Speed
			// Start bit: 39, Length: 16, Byte Order: big
			Cooling_Fan_Speed = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.0625, 0, 3);

			// Signal: Engine_Coolant_Temp
			// Start bit: 39, Length: 8, Byte Order: big
			Engine_Coolant_Temp = process_int_value((uint32_t)Message.data[4], 0xFF, false, 1, -50);

			// Signal: Calculated_Load
			// Start bit: 39, Length: 8, Byte Order: big
			Calculated_Load = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.39215686275, 0, 3);

			// Signal: Battery_Voltage
			// Start bit: 39, Length: 8, Byte Order: big
			Battery_Voltage = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.08, 0, 3);

			// Signal: Battery_Temp_Sensor
			// Start bit: 39, Length: 8, Byte Order: big
			Battery_Temp_Sensor = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.02, 0, 3);

			// Signal: Battery_Current_Sensor
			// Start bit: 39, Length: 16, Byte Order: big
			Battery_Current_Sensor = process_unsigned_int_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, 5, 0);

			// Signal: Base_Fuel_Schedule
			// Start bit: 39, Length: 16, Byte Order: big
			Base_Fuel_Schedule = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.0005, 0, 3);

			// Signal: Alternator_Duty_Cycle
			// Start bit: 39, Length: 16, Byte Order: big
			Alternator_Duty_Cycle = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.5, 0, 3);

			// Signal: AC_Relay
			// Start bit: 39, Length: 1, Byte Order: big
			AC_Relay = process_raw_value((uint32_t)Message.data[4], 0x80);

			// Signal: Accel_Sensor_2
			// Start bit: 39, Length: 16, Byte Order: big
			Accel_Sensor_2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: Accel_Sensor_1
			// Start bit: 39, Length: 16, Byte Order: big
			Accel_Sensor_1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: AC_Pressure_Sensor
			// Start bit: 39, Length: 16, Byte Order: big
			AC_Pressure_Sensor = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: AC_Evap_Temp
			// Start bit: 39, Length: 8, Byte Order: big
			AC_Evap_Temp = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.33333333333, -30, 3);

			// Signal: AC_Evap_Target
			// Start bit: 39, Length: 8, Byte Order: big
			AC_Evap_Target = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.33333333333, -30, 3);

			// Signal: Air_Fuel_S1_B2
			// Start bit: 39, Length: 16, Byte Order: big
			Air_Fuel_S1_B2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: Air_Fuel_S1_B1
			// Start bit: 39, Length: 16, Byte Order: big
			Air_Fuel_S1_B1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.005, 0, 3);

			// Signal: Air_Fuel_S1_Heater_B2
			// Start bit: 39, Length: 8, Byte Order: big
			Air_Fuel_S1_Heater_B2 = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.4, 0, 3);

			// Signal: Air_Fuel_S1_Heater_B1
			// Start bit: 39, Length: 8, Byte Order: big
			Air_Fuel_S1_Heater_B1 = process_float_value((uint32_t)Message.data[4], 0xFF, false, 0.4, 0, 3);

			// Signal: Air_Fuel_Alpha_B2
			// Start bit: 39, Length: 8, Byte Order: big
			Air_Fuel_Alpha_B2 = process_raw_value((uint32_t)Message.data[4], 0xFF);

			// Signal: Air_Fuel_Alpha_B1
			// Start bit: 39, Length: 8, Byte Order: big
			Air_Fuel_Alpha_B1 = process_raw_value((uint32_t)Message.data[4], 0xFF);

			}
			if (Service_ID == 98) {
			// Signal: Mode22_DID
			// Start bit: 23, Length: 16, Byte Order: big
			Mode22_DID = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

		}

			}

//################ End Generated CAN Code ################

		//send_message(CAN_2, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_2){
		//send_message(CAN_3, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_3){
		//send_message(CAN_1, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
				
	}
}

/* Run 2000Hz Functions here */
void events_2000Hz(){

}

/* Run 1000Hz Functions here */
void events_1000Hz(){
	for (uint8_t i = 0; i< 15; i++){
		//char buffer1[100];
		//snprintf(buffer1, 100,"(123.456789) can0 12345678#%02x34567890123456\r\n",i);
		//serialPrint(buffer1);
	}

}

/* Run 500Hz Functions here */
void events_500Hz(){

}

/* Run 200Hz Functions here */
void events_200Hz(){

}

/* Run 100Hz Functions here */
void events_100Hz(){

}

/* Run 50Hz Functions here */
void events_50Hz(){
	if (increment_rpm == true){
		test_rpm+=5;
		if (test_rpm > 9900){
			increment_rpm = false;
		}
	}
	else{
		test_rpm-=5;
		if(test_rpm < 500){
			increment_rpm = true;
		}
	}
	
	
}

/* Run 20Hz Functions here */
void events_20Hz(){
	//printf(">Engine Speed:%04d %s\r\n", test_rpm, test_rpm_unit);

}

/* Run 10Hz Functions here */
void events_10Hz(){
	toggleLED(LED_1);
	//serialPrint("LED Toggled...\r\n");
	//serialPrint("Testing pushing 2 strings\r\n");

}

/* Run 5Hz Functions here */
void events_5Hz(){

}

/* Run 2Hz Functions here */
void events_2Hz(){
	
}

/* Run 1Hz Functions here */
void events_1Hz(){
	send_message(CAN_1, false, 0x001, 8, example_data_1Hz);
	send_message(CAN_2, false, 0x002, 8, example_data_1Hz);
	send_message(CAN_3, false, 0x003, 8, example_data_1Hz);
	for (uint8_t i=0; i<8; i++){
		example_data_1Hz[i]++;
	}
	float testfloat = 1.234567;
	char buffer[16];
    snprintf(buffer, sizeof(buffer), "%3.6f\r\n", testfloat);
	//sprintf(buffer, "%3.9f\r\n", testfloat);
	//serialPrint(buffer);
	//printf("Hello World..\r\n");
	//uint8_t u8Decimal = 123 ;
    //float floatval = 3.141592 ;
	//uint8_t hw[13] = "Hello World!"; // Make sure there's 1 + total length of string for the buffer to NULL Terminate.
	//printf("This is my float: %2.6f , this is my u8 %u , %s\r\n", floatval, u8Decimal, hw);
	//HAL_UART_Transmit_DMA(&huart1, )
	//serialPrint("Hello World\r\n");
}
