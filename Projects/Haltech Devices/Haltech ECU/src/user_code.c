/*
 *  	user_code.c - All User Code should be applied here unless specified otherwise.
 *  	Example Setup of Haltech ECU for Configuring
 * 		Notes :
 *
 *
 */

/* File Includes */
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"
#include "snprintf.h"
#include <string.h>
#include "stm32g4xx_hal.h"

/* End File Includes */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* File Define options */

#define HALTECH_CAN CAN_1 //
#define HALTECH_ECU 1

/* End File Defines */

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Variable Declarations */

uint32_t serialnumber;
CAN_ErrorCounts errors;

// ################ Generated Variable Declarations ################
//  Copy to Variable Declarations area in user_code.c

uint32_t Engine_Speed;
float Manifold_Pressure;
float Throttle_Position;
float Coolant_Pressure;
float Fuel_Pressure;
float Oil_Pressure;
float Engine_Demand;
float Wastegate_Pressure;
float Inj_Stg_1_DC;
float Inj_Stg_2_DC;
float Ignition_Angle;
float Wheel_Slip;
float Wheel_Diff;
uint32_t Launch_Control_End;
float Injection_Stage_1_Avg_Pulsewidth;
float Injection_Stage_2_Avg_Pulsewidth;
float Injection_Stage_3_Avg_Pulsewidth;
float Injection_Stage_4_Avg_Pulsewidth;
float Lambda_1;
float Lambda_2;
float Lambda_3;
float Lambda_4;
uint32_t Trigger_System_Error_Count;
uint32_t Trigger_Counter;
uint32_t Trigger_Sync_Level;
float Knock_Level_1;
float Knock_Level_2;
float Brake_Pressure;
float No2_Pressure_Sensor_1;
uint32_t Turbo_Speed_Sensor_1;
float Lateral_G;
float Wheel_Speed_FL;
float Wheel_Speed_FR;
float Wheel_Speed_RL;
float Wheel_Speed_RR;
float Exh_Cam_Angle_1;
float Exh_Cam_Angle_2;
uint32_t Engine_Limiting_Active;
float Launch_Control_Ign_Retard;
float Launch_Control_Fuel_Enrich;
float Longitudinal_G;
float Generic_Output_1_DC;
float Boost_Control_Output;
float Vehicle_Speed;
float Int_Cam_Angle_1;
float Int_Cam_Angle_2;
uint32_t Fuel_Flow;
uint32_t Fuel_Flow_Return;
float Battery_Voltage;
float Target_Boost_Level;
float Barometric_Pressure;
float EGT_1;
float EGT_2;
float EGT_3;
float EGT_4;
float EGT_5;
float EGT_6;
float EGT_7;
float EGT_8;
float EGT_9;
float EGT_10;
float EGT_11;
float EGT_12;
float Ambient_Air_Temperature;
float Relative_Humidity;
uint32_t Specific_Humidity;
float Absolute_Humidity;
float Coolant_Temperature;
float Air_Temperature;
float Fuel_Temperature;
float Oil_Temperature;
float Gearbox_Oil_Temperature;
float Diff_Oil_Temperature;
float Fuel_Composition;
float Fuel_Level;
float STFT_Bank_1;
float STFT_Bank_2;
float LTFT_Bank_1;
float LTFT_Bank_2;
uint32_t Oil_Pressure_Light;
uint32_t Clutch_Switch;
uint32_t Brake_Pedal_Switch;
uint32_t Transient_Throttle_Active;
uint32_t Decel_Cut_Active;
uint32_t Gear_Switch;
uint32_t Reverse_Switch;
uint32_t Neutral_Switch;
uint32_t Torque_Reduction_Active;
uint32_t Flat_Shift_Switch;
uint32_t Aux_RPM_Limiter_Active;
uint32_t Launch_Control_Switch;
uint32_t Launch_Control_Active;
uint32_t ThermoFan_1_On;
uint32_t ThermoFan_2_On;
uint32_t ThermoFan_3_On;
uint32_t ThermoFan_4_On;
uint32_t Aircon_Output;
uint32_t Aircon_Request;
uint32_t Traction_Control_Enabled;
uint32_t Traction_Control_Active;
int32_t Rotary_Trimpot_1;
int32_t Rotary_Trimpot_2;
int32_t Rotary_Trimpot_3;
uint32_t Traction_Control_Light;
uint32_t HandBrake_State;
uint32_t Battery_Light_Active;
uint32_t Check_Engine_Light;
uint32_t Ignition_Switch;
uint32_t Turbo_Timer_Sec_Remaining;
uint32_t Turbo_Timer_Eng_Sec_Remaining;
uint32_t ABS_Armed;
uint32_t ABS_Active;
uint32_t ABS_Error;
uint32_t Pit_Limiter_Switch_State;
uint32_t Pit_Limiter_Active;
uint32_t Pit_Limiter_Error;
float Steering_Wheel_Angle;
uint32_t Driveshaft_RPM;
float No2_Pressure_Sensor_2;
float No2_Pressure_Sensor_3;
float No2_Pressure_Sensor_4;
float Turbo_Speed_Sensor_2;
float Generic_Sensor_1;
float Generic_Sensor_2;
float Generic_Sensor_3;
float Generic_Sensor_4;
float Generic_Sensor_5;
float Generic_Sensor_6;
float Generic_Sensor_7;
float Generic_Sensor_8;
float Generic_Sensor_9;
float Generic_Sensor_10;
float Target_Lamnda;
uint32_t Nitrous_Stage_6_Output;
uint32_t Nitrous_Stage_5_Outout;
uint32_t Nitrous_Stage_4_Outout;
uint32_t Nitrous_Stage_3_Output;
uint32_t Nitrous_Stage_2_Outout;
uint32_t Nitrous_Stsge_1_Output;
int32_t TqMgmt_Knob;
float Gearbox_Oil_Pressure;
float Inj_Stage_3_DC;
float Inj_Stage_4_DC;
float Crankcase_Pressure;
uint32_t Race_Timer;
float Ignition_Angle_Bank_1;
float Ignition_Angle_Bank_2;
int32_t TqMgmt_DS_Target;
int32_t TqMgmt_DS_Error;
float TqMgmt_DS_Target_Err_Ign_Corr;
float TqMgmt_DS_Timed_Ign_Corr;
float TqMgmt_Combined_Ign_Corr;
float Lambda_5;
float Lambda_6;
float Lambda_7;
float Lambda_8;
float Lambda_9;
float Lambda_10;
float Lambda_11;
float Lambda_12;
float Damper_FL_Raw;
float Damper_FR_Raw;
float Damper_RL_Raw;
float Damper_RR_Raw;
float Damper_FL;
float Damper_FR;
float Damper_RL;
float Damper_RR;
float ECU_Temperature;
float Lambda_Overall;
float Lambda_Bank_1;
float Lambda_Bank_2;
int32_t Gear_Selector_Position;
int32_t Gear;
float Inj_Differential_Pressure;
float Accel_Pedal_Position;
float Exhuast_Manifold_Pressure;
float Cruise_Target;
float Cruise_Last_Target;
float Cruise_Error;
uint32_t Cruise_Input_State;
uint32_t Cruise_Controller_State;
uint32_t Total_Fuel_Used;
uint32_t Aux_3_Fuel_Pump_Output_State;
uint32_t Aux_2_Fuel_Pump_Output_State;
uint32_t Aux_1_Fuel_Pump_Output_State;
uint32_t Primary_Fuel_Pump_Output_State;
uint32_t Traction_Control_Switch_State;
uint32_t Antilag_Output_State;
uint32_t Antilag_Switch_State;
uint32_t Rolling_Antilag_Switch_State;
uint32_t Nitrous_Enable_4_Output_State;
uint32_t Nitrous_Enable_4_Switch_State;
uint32_t Nitrous_Enable_3_Output_State;
uint32_t Nitrous_Enable_3_Switch_State;
uint32_t Nitrous_Enable_2_Output_State;
uint32_t Nitrous_Enable_2_Switch_State;
uint32_t Nitrous_Enable_1_Output_State;
uint32_t Nitrous_Enable_1_Switch_State;
uint32_t Nitrous_Override_4_Output_State;
uint32_t Nitrous_Override_4_Switch_State;
uint32_t Nitrous_Override_3_Output_State;
uint32_t Nitrous_Override_3_Switch_State;
uint32_t Nitrous_Override_2_Output_State;
uint32_t Nitrous_Override_2_Switch_State;
uint32_t Nitrous_Override_1_Output_State;
uint32_t Nitrous_Override_1_Switch_State;
uint32_t Cut_Percentage_Method;
uint32_t Water_Inj_Adv_Override_Out_State;
uint32_t Water_Inj_Adv_Override_Sw_State;
uint32_t Water_Inj_Adv_Enable_Out_State;
uint32_t Water_Inj_Adv_Enable_Sw_State;
float Vertical_G;
float Pitch_Rate;
float Roll_Rate;
float Yaw_Rate;
float Primary_Fuel_Pump_Duty;
float Aux_1_Fuel_Pump_Duty;
float Aux_2_Fuel_Pump_Duty;
float Aux_3_Fuel_Pump_Duty;
float Brake_Pressure_Rear;
float Brake_Pressure_Front_Ratio;
float Brake_Pressure_Rear_Ratio;
uint32_t Brake_Pressure_Difference;
uint32_t Engine_Limiter_Max_RPM;
float Cut_Percentage;
uint32_t Engine_Limiter_Function;
uint32_t RPM_Limiter_Function;
uint32_t Cut_Percentage_Function;
uint32_t RPM_Limiter_Method;
uint32_t Engine_Limiter_Method;
float FL_Tire_Pressure;
float FR_Tire_Pressure;
float RL_Tire_Pressure;
float RR_Tire_Pressure;
uint32_t FL_Tire_Temp;
uint32_t FR_Tire_Temp;
uint32_t RL_Tire_Temp;
uint32_t RR_Tire_Temp;
float FL_TPMS_Voltage;
float FR_TPMS_Voltage;
float RL_TPMS_Voltage;
float RR_TPMS_Voltage;
float Front_Tire_Pres_Target;
float Rear_Tire_Pres_Target;
uint32_t FL_Tire_Leaking;
uint32_t FR_Tire_Leaking;
uint32_t RL_Tire_Leaking;
uint32_t RR_Tire_Leaking;
uint32_t Engine_Protection_Level;
uint32_t Engine_Protection_DTC;
uint32_t Engine_Protection_DTC_Class;
uint32_t Park_Light_State;
uint32_t Head_Light_State;
uint32_t High_Beam_Light_State;
uint32_t Left_Indicator_State;
uint32_t Right_Indicator_state;
int32_t Fuel_Used_Since_Trip1_Reset;
int32_t Trip_Meter_1;
uint32_t Generic_Output_17_State;
uint32_t Generic_Output_18_State;
uint32_t Generic_Output_19_State;
uint32_t Generic_Output_20_State;
uint32_t Generic_Output_9_State;
uint32_t Generic_Output_10_State;
uint32_t Generic_Output_11_State;
uint32_t Generic_Output_12_State;
uint32_t Generic_Output_13_State;
uint32_t Generic_Output_14_State;
uint32_t Generic_Output_15_State;
uint32_t Generic_Output_16_State;
uint32_t Generic_Output_1_State;
uint32_t Generic_Output_2_State;
uint32_t Generic_Output_3_State;
uint32_t Generic_Output_4_State;
uint32_t Generic_Output_5_State;
uint32_t Generic_Output_6_State;
uint32_t Generic_Output_7_State;
uint32_t Generic_Output_8_State;
float Calculated_Air_Temp;
float Water_Inj_Adv_Solenoid_Duty;
int32_t Exhaust_Cutout_State;
int32_t Nitrous_Bottle_Opener_State;
int32_t Generic_Open_Loop_Motor_1_State;
int32_t Generic_Open_Loop_Motor_2_State;
int32_t Generic_Open_Loop_Motor_3_State;
// ################ End Generated Variable Declarations ################

//-----------------------------//
//-----------------------------//
//-----------------------------//

/* Startup Functions */

void events_Startup()
{
	setupCANbus(CAN_1, 1000000, NORMAL_MODE); // Set up as Haltech CAN Bus
	setupCANbus(CAN_2, 1000000, NORMAL_MODE);
	setupCANbus(CAN_3, 1000000, NORMAL_MODE);
	setCAN_Termination(CAN_1, true);
	setCAN_Termination(CAN_2, true);
	setCAN_Termination(CAN_3, true);
	startCANbus(CAN_1);
	startCANbus(CAN_2);
	startCANbus(CAN_3);
}

/* End Startup Functions */

//-----------------------------//
//-----------------------------//
//-----------------------------//

void onSerialReceive(uint8_t *serialMessage)
{
	// What do you want to do when you receive a UART message.. ?
	// printf("%07.4f message received...\r\n",getTimestamp());
}

void onReceive(CAN_Message Message)
{
	// What do you want to do when you receive a CAN message.. ?
	if (Message.Bus == CAN_1)
	{
		if (HALTECH_CAN == CAN_1)
		{
			if (HALTECH_ECU == 1)
			{
				// ################ Generated CAN Code ################
				// Copy Code Below to appropriate Message.bus statement in user_code.c

				if (Message.arbitration_id == 0x360)
				{
					// Signal: Engine_Speed
					// Start bit: 7, Length: 16, Byte Order: big
					Engine_Speed = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

					// Signal: Manifold_Pressure
					// Start bit: 23, Length: 16, Byte Order: big
					Manifold_Pressure = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Throttle_Position
					// Start bit: 39, Length: 16, Byte Order: big
					Throttle_Position = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Coolant_Pressure
					// Start bit: 55, Length: 16, Byte Order: big
					Coolant_Pressure = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, -101.3, 3);
				}

				else if (Message.arbitration_id == 0x361)
				{
					// Signal: Fuel_Pressure
					// Start bit: 7, Length: 16, Byte Order: big
					Fuel_Pressure = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: Oil_Pressure
					// Start bit: 23, Length: 16, Byte Order: big
					Oil_Pressure = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: Engine_Demand
					// Start bit: 39, Length: 16, Byte Order: big
					Engine_Demand = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Wastegate_Pressure
					// Start bit: 55, Length: 16, Byte Order: big
					Wastegate_Pressure = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, -101.3, 3);
				}

				else if (Message.arbitration_id == 0x362)
				{
					// Signal: Inj_Stg_1_DC
					// Start bit: 7, Length: 16, Byte Order: big
					Inj_Stg_1_DC = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Inj_Stg_2_DC
					// Start bit: 23, Length: 16, Byte Order: big
					Inj_Stg_2_DC = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Ignition_Angle
					// Start bit: 39, Length: 16, Byte Order: big
					Ignition_Angle = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x363)
				{
					// Signal: Wheel_Slip
					// Start bit: 7, Length: 16, Byte Order: big
					Wheel_Slip = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Wheel_Diff
					// Start bit: 23, Length: 16, Byte Order: big
					Wheel_Diff = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Launch_Control_End
					// Start bit: 55, Length: 16, Byte Order: big
					Launch_Control_End = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);
				}

				else if (Message.arbitration_id == 0x364)
				{
					// Signal: Injection_Stage_1_Avg_Pulsewidth
					// Start bit: 7, Length: 16, Byte Order: big
					Injection_Stage_1_Avg_Pulsewidth = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Injection_Stage_2_Avg_Pulsewidth
					// Start bit: 23, Length: 16, Byte Order: big
					Injection_Stage_2_Avg_Pulsewidth = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Injection_Stage_3_Avg_Pulsewidth
					// Start bit: 39, Length: 16, Byte Order: big
					Injection_Stage_3_Avg_Pulsewidth = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Injection_Stage_4_Avg_Pulsewidth
					// Start bit: 55, Length: 16, Byte Order: big
					Injection_Stage_4_Avg_Pulsewidth = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.001, 0, 3);
				}

				else if (Message.arbitration_id == 0x368)
				{
					// Signal: Lambda_1
					// Start bit: 7, Length: 16, Byte Order: big
					Lambda_1 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_2
					// Start bit: 23, Length: 16, Byte Order: big
					Lambda_2 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_3
					// Start bit: 39, Length: 16, Byte Order: big
					Lambda_3 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_4
					// Start bit: 55, Length: 16, Byte Order: big
					Lambda_4 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.001, 0, 3);
				}

				else if (Message.arbitration_id == 0x369)
				{
					// Signal: Trigger_System_Error_Count
					// Start bit: 7, Length: 16, Byte Order: big
					Trigger_System_Error_Count = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

					// Signal: Trigger_Counter
					// Start bit: 23, Length: 16, Byte Order: big
					Trigger_Counter = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

					// Signal: Trigger_Sync_Level
					// Start bit: 55, Length: 16, Byte Order: big
					Trigger_Sync_Level = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);
				}

				else if (Message.arbitration_id == 0x36A)
				{
					// Signal: Knock_Level_1
					// Start bit: 7, Length: 16, Byte Order: big
					Knock_Level_1 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.01, 0, 3);

					// Signal: Knock_Level_2
					// Start bit: 23, Length: 16, Byte Order: big
					Knock_Level_2 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.01, 0, 3);
				}

				else if (Message.arbitration_id == 0x36B)
				{
					// Signal: Brake_Pressure
					// Start bit: 7, Length: 16, Byte Order: big
					Brake_Pressure = process_int_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 1, -101);

					// Signal: No2_Pressure_Sensor_1
					// Start bit: 23, Length: 16, Byte Order: big
					No2_Pressure_Sensor_1 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.22, -101.3, 3);

					// Signal: Turbo_Speed_Sensor_1
					// Start bit: 39, Length: 16, Byte Order: big
					Turbo_Speed_Sensor_1 = process_unsigned_int_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, 10, 0);

					// Signal: Lateral_G
					// Start bit: 55, Length: 16, Byte Order: big
					Lateral_G = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.0101972, 0, 3);
				}

				else if (Message.arbitration_id == 0x36C)
				{
					// Signal: Wheel_Speed_FL
					// Start bit: 7, Length: 16, Byte Order: big
					Wheel_Speed_FL = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Wheel_Speed_FR
					// Start bit: 23, Length: 16, Byte Order: big
					Wheel_Speed_FR = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Wheel_Speed_RL
					// Start bit: 39, Length: 16, Byte Order: big
					Wheel_Speed_RL = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Wheel_Speed_RR
					// Start bit: 55, Length: 16, Byte Order: big
					Wheel_Speed_RR = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x36D)
				{
					// Signal: Exh_Cam_Angle_1
					// Start bit: 39, Length: 16, Byte Order: big
					Exh_Cam_Angle_1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Exh_Cam_Angle_2
					// Start bit: 55, Length: 16, Byte Order: big
					Exh_Cam_Angle_2 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x36E)
				{
					// Signal: Engine_Limiting_Active
					// Start bit: 7, Length: 16, Byte Order: big
					Engine_Limiting_Active = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

					// Signal: Launch_Control_Ign_Retard
					// Start bit: 23, Length: 16, Byte Order: big
					Launch_Control_Ign_Retard = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Launch_Control_Fuel_Enrich
					// Start bit: 39, Length: 16, Byte Order: big
					Launch_Control_Fuel_Enrich = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Longitudinal_G
					// Start bit: 55, Length: 16, Byte Order: big
					Longitudinal_G = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.0101972, 0, 3);
				}

				else if (Message.arbitration_id == 0x36F)
				{
					// Signal: Generic_Output_1_DC
					// Start bit: 7, Length: 16, Byte Order: big
					Generic_Output_1_DC = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Boost_Control_Output
					// Start bit: 23, Length: 16, Byte Order: big
					Boost_Control_Output = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x370)
				{
					// Signal: Vehicle_Speed
					// Start bit: 7, Length: 16, Byte Order: big
					Vehicle_Speed = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Int_Cam_Angle_1
					// Start bit: 39, Length: 16, Byte Order: big
					Int_Cam_Angle_1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Int_Cam_Angle_2
					// Start bit: 55, Length: 16, Byte Order: big
					Int_Cam_Angle_2 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x371)
				{
					// Signal: Fuel_Flow
					// Start bit: 7, Length: 16, Byte Order: big
					Fuel_Flow = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

					// Signal: Fuel_Flow_Return
					// Start bit: 23, Length: 16, Byte Order: big
					Fuel_Flow_Return = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);
				}

				else if (Message.arbitration_id == 0x372)
				{
					// Signal: Battery_Voltage
					// Start bit: 7, Length: 16, Byte Order: big
					Battery_Voltage = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Target_Boost_Level
					// Start bit: 39, Length: 16, Byte Order: big
					Target_Boost_Level = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Barometric_Pressure
					// Start bit: 55, Length: 16, Byte Order: big
					Barometric_Pressure = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x373)
				{
					// Signal: EGT_1
					// Start bit: 7, Length: 16, Byte Order: big
					EGT_1 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_2
					// Start bit: 23, Length: 16, Byte Order: big
					EGT_2 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_3
					// Start bit: 39, Length: 16, Byte Order: big
					EGT_3 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_4
					// Start bit: 55, Length: 16, Byte Order: big
					EGT_4 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x374)
				{
					// Signal: EGT_5
					// Start bit: 7, Length: 16, Byte Order: big
					EGT_5 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_6
					// Start bit: 23, Length: 16, Byte Order: big
					EGT_6 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_7
					// Start bit: 39, Length: 16, Byte Order: big
					EGT_7 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_8
					// Start bit: 55, Length: 16, Byte Order: big
					EGT_8 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x375)
				{
					// Signal: EGT_9
					// Start bit: 7, Length: 16, Byte Order: big
					EGT_9 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_10
					// Start bit: 23, Length: 16, Byte Order: big
					EGT_10 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_11
					// Start bit: 39, Length: 16, Byte Order: big
					EGT_11 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: EGT_12
					// Start bit: 55, Length: 16, Byte Order: big
					EGT_12 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x376)
				{
					// Signal: Ambient_Air_Temperature
					// Start bit: 7, Length: 16, Byte Order: big
					Ambient_Air_Temperature = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Relative_Humidity
					// Start bit: 23, Length: 16, Byte Order: big
					Relative_Humidity = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Specific_Humidity
					// Start bit: 39, Length: 16, Byte Order: big
					Specific_Humidity = process_unsigned_int_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, 100, 0);

					// Signal: Absolute_Humidity
					// Start bit: 55, Length: 16, Byte Order: big
					Absolute_Humidity = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E0)
				{
					// Signal: Coolant_Temperature
					// Start bit: 7, Length: 16, Byte Order: big
					Coolant_Temperature = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Air_Temperature
					// Start bit: 23, Length: 16, Byte Order: big
					Air_Temperature = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Fuel_Temperature
					// Start bit: 39, Length: 16, Byte Order: big
					Fuel_Temperature = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Oil_Temperature
					// Start bit: 55, Length: 16, Byte Order: big
					Oil_Temperature = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E1)
				{
					// Signal: Gearbox_Oil_Temperature
					// Start bit: 7, Length: 16, Byte Order: big
					Gearbox_Oil_Temperature = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Diff_Oil_Temperature
					// Start bit: 23, Length: 16, Byte Order: big
					Diff_Oil_Temperature = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Fuel_Composition
					// Start bit: 39, Length: 16, Byte Order: big
					Fuel_Composition = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E2)
				{
					// Signal: Fuel_Level
					// Start bit: 7, Length: 16, Byte Order: big
					Fuel_Level = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E3)
				{
					// Signal: STFT_Bank_1
					// Start bit: 7, Length: 16, Byte Order: big
					STFT_Bank_1 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, true, 0.1, 0, 3);

					// Signal: STFT_Bank_2
					// Start bit: 23, Length: 16, Byte Order: big
					STFT_Bank_2 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, true, 0.1, 0, 3);

					// Signal: LTFT_Bank_1
					// Start bit: 39, Length: 16, Byte Order: big
					LTFT_Bank_1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: LTFT_Bank_2
					// Start bit: 55, Length: 16, Byte Order: big
					LTFT_Bank_2 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E4)
				{
					// Signal: Oil_Pressure_Light
					// Start bit: 8, Length: 1, Byte Order: big
					Oil_Pressure_Light = process_raw_value((uint32_t)Message.data[1], 0x1);

					// Signal: Clutch_Switch
					// Start bit: 9, Length: 1, Byte Order: big
					Clutch_Switch = process_raw_value((uint32_t)Message.data[1], 0x2);

					// Signal: Brake_Pedal_Switch
					// Start bit: 10, Length: 1, Byte Order: big
					Brake_Pedal_Switch = process_raw_value((uint32_t)Message.data[1], 0x4);

					// Signal: Transient_Throttle_Active
					// Start bit: 11, Length: 1, Byte Order: big
					Transient_Throttle_Active = process_raw_value((uint32_t)Message.data[1], 0x8);

					// Signal: Decel_Cut_Active
					// Start bit: 12, Length: 1, Byte Order: big
					Decel_Cut_Active = process_raw_value((uint32_t)Message.data[1], 0x10);

					// Signal: Gear_Switch
					// Start bit: 13, Length: 1, Byte Order: big
					Gear_Switch = process_raw_value((uint32_t)Message.data[1], 0x20);

					// Signal: Reverse_Switch
					// Start bit: 14, Length: 1, Byte Order: big
					Reverse_Switch = process_raw_value((uint32_t)Message.data[1], 0x40);

					// Signal: Neutral_Switch
					// Start bit: 15, Length: 1, Byte Order: big
					Neutral_Switch = process_raw_value((uint32_t)Message.data[1], 0x80);

					// Signal: Torque_Reduction_Active
					// Start bit: 17, Length: 1, Byte Order: big
					Torque_Reduction_Active = process_raw_value((uint32_t)Message.data[2], 0x2);

					// Signal: Flat_Shift_Switch
					// Start bit: 19, Length: 1, Byte Order: big
					Flat_Shift_Switch = process_raw_value((uint32_t)Message.data[2], 0x8);

					// Signal: Aux_RPM_Limiter_Active
					// Start bit: 21, Length: 1, Byte Order: big
					Aux_RPM_Limiter_Active = process_raw_value((uint32_t)Message.data[2], 0x20);

					// Signal: Launch_Control_Switch
					// Start bit: 22, Length: 1, Byte Order: big
					Launch_Control_Switch = process_raw_value((uint32_t)Message.data[2], 0x40);

					// Signal: Launch_Control_Active
					// Start bit: 23, Length: 1, Byte Order: big
					Launch_Control_Active = process_raw_value((uint32_t)Message.data[2], 0x80);

					// Signal: ThermoFan_1_On
					// Start bit: 24, Length: 1, Byte Order: big
					ThermoFan_1_On = process_raw_value((uint32_t)Message.data[3], 0x1);

					// Signal: ThermoFan_2_On
					// Start bit: 25, Length: 1, Byte Order: big
					ThermoFan_2_On = process_raw_value((uint32_t)Message.data[3], 0x2);

					// Signal: ThermoFan_3_On
					// Start bit: 26, Length: 1, Byte Order: big
					ThermoFan_3_On = process_raw_value((uint32_t)Message.data[3], 0x4);

					// Signal: ThermoFan_4_On
					// Start bit: 27, Length: 1, Byte Order: big
					ThermoFan_4_On = process_raw_value((uint32_t)Message.data[3], 0x8);

					// Signal: Aircon_Output
					// Start bit: 28, Length: 1, Byte Order: big
					Aircon_Output = process_raw_value((uint32_t)Message.data[3], 0x10);

					// Signal: Aircon_Request
					// Start bit: 29, Length: 1, Byte Order: big
					Aircon_Request = process_raw_value((uint32_t)Message.data[3], 0x20);

					// Signal: Traction_Control_Enabled
					// Start bit: 30, Length: 1, Byte Order: big
					Traction_Control_Enabled = process_raw_value((uint32_t)Message.data[3], 0x40);

					// Signal: Traction_Control_Active
					// Start bit: 31, Length: 1, Byte Order: big
					Traction_Control_Active = process_raw_value((uint32_t)Message.data[3], 0x80);

					// Signal: Rotary_Trimpot_1
					// Start bit: 39, Length: 8, Byte Order: big
					Rotary_Trimpot_1 = process_int_value((uint32_t)Message.data[4], 0xFF, true, 1, 0);

					// Signal: Rotary_Trimpot_2
					// Start bit: 47, Length: 8, Byte Order: big
					Rotary_Trimpot_2 = process_int_value((uint32_t)Message.data[5], 0xFF, true, 1, 0);

					// Signal: Rotary_Trimpot_3
					// Start bit: 55, Length: 8, Byte Order: big
					Rotary_Trimpot_3 = process_int_value((uint32_t)Message.data[6], 0xFF, true, 1, 0);

					// Signal: Traction_Control_Light
					// Start bit: 56, Length: 1, Byte Order: big
					Traction_Control_Light = process_raw_value((uint32_t)Message.data[7], 0x1);

					// Signal: HandBrake_State
					// Start bit: 57, Length: 1, Byte Order: big
					HandBrake_State = process_raw_value((uint32_t)Message.data[7], 0x2);

					// Signal: Battery_Light_Active
					// Start bit: 62, Length: 1, Byte Order: big
					Battery_Light_Active = process_raw_value((uint32_t)Message.data[7], 0x40);

					// Signal: Check_Engine_Light
					// Start bit: 63, Length: 1, Byte Order: big
					Check_Engine_Light = process_raw_value((uint32_t)Message.data[7], 0x80);
				}

				else if (Message.arbitration_id == 0x3E5)
				{
					// Signal: Ignition_Switch
					// Start bit: 0, Length: 1, Byte Order: big
					Ignition_Switch = process_raw_value((uint32_t)Message.data[0], 0x1);

					// Signal: Turbo_Timer_Sec_Remaining
					// Start bit: 15, Length: 8, Byte Order: big
					Turbo_Timer_Sec_Remaining = process_raw_value((uint32_t)Message.data[1], 0xFF);

					// Signal: Turbo_Timer_Eng_Sec_Remaining
					// Start bit: 23, Length: 8, Byte Order: big
					Turbo_Timer_Eng_Sec_Remaining = process_raw_value((uint32_t)Message.data[2], 0xFF);

					// Signal: ABS_Armed
					// Start bit: 24, Length: 1, Byte Order: big
					ABS_Armed = process_raw_value((uint32_t)Message.data[3], 0x1);

					// Signal: ABS_Active
					// Start bit: 25, Length: 1, Byte Order: big
					ABS_Active = process_raw_value((uint32_t)Message.data[3], 0x2);

					// Signal: ABS_Error
					// Start bit: 26, Length: 1, Byte Order: big
					ABS_Error = process_raw_value((uint32_t)Message.data[3], 0x4);

					// Signal: Pit_Limiter_Switch_State
					// Start bit: 28, Length: 1, Byte Order: big
					Pit_Limiter_Switch_State = process_raw_value((uint32_t)Message.data[3], 0x10);

					// Signal: Pit_Limiter_Active
					// Start bit: 29, Length: 1, Byte Order: big
					Pit_Limiter_Active = process_raw_value((uint32_t)Message.data[3], 0x20);

					// Signal: Pit_Limiter_Error
					// Start bit: 30, Length: 1, Byte Order: big
					Pit_Limiter_Error = process_raw_value((uint32_t)Message.data[3], 0x40);

					// Signal: Steering_Wheel_Angle
					// Start bit: 39, Length: 16, Byte Order: big
					Steering_Wheel_Angle = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Driveshaft_RPM
					// Start bit: 55, Length: 16, Byte Order: big
					Driveshaft_RPM = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);
				}

				else if (Message.arbitration_id == 0x3E6)
				{
					// Signal: No2_Pressure_Sensor_2
					// Start bit: 7, Length: 16, Byte Order: big
					No2_Pressure_Sensor_2 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.22, -101.3, 3);

					// Signal: No2_Pressure_Sensor_3
					// Start bit: 23, Length: 16, Byte Order: big
					No2_Pressure_Sensor_3 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.22, -101.3, 3);

					// Signal: No2_Pressure_Sensor_4
					// Start bit: 39, Length: 16, Byte Order: big
					No2_Pressure_Sensor_4 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.22, -101.3, 3);

					// Signal: Turbo_Speed_Sensor_2
					// Start bit: 55, Length: 16, Byte Order: big
					Turbo_Speed_Sensor_2 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E7)
				{
					// Signal: Generic_Sensor_1
					// Start bit: 7, Length: 16, Byte Order: big
					Generic_Sensor_1 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_2
					// Start bit: 23, Length: 16, Byte Order: big
					Generic_Sensor_2 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_3
					// Start bit: 39, Length: 16, Byte Order: big
					Generic_Sensor_3 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_4
					// Start bit: 55, Length: 16, Byte Order: big
					Generic_Sensor_4 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E8)
				{
					// Signal: Generic_Sensor_5
					// Start bit: 7, Length: 16, Byte Order: big
					Generic_Sensor_5 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_6
					// Start bit: 23, Length: 16, Byte Order: big
					Generic_Sensor_6 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_7
					// Start bit: 39, Length: 16, Byte Order: big
					Generic_Sensor_7 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_8
					// Start bit: 55, Length: 16, Byte Order: big
					Generic_Sensor_8 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3E9)
				{
					// Signal: Generic_Sensor_9
					// Start bit: 7, Length: 16, Byte Order: big
					Generic_Sensor_9 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Generic_Sensor_10
					// Start bit: 23, Length: 16, Byte Order: big
					Generic_Sensor_10 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Target_Lamnda
					// Start bit: 39, Length: 16, Byte Order: big
					Target_Lamnda = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Nitrous_Stage_6_Output
					// Start bit: 50, Length: 1, Byte Order: big
					Nitrous_Stage_6_Output = process_raw_value((uint32_t)Message.data[6], 0x4);

					// Signal: Nitrous_Stage_5_Outout
					// Start bit: 51, Length: 1, Byte Order: big
					Nitrous_Stage_5_Outout = process_raw_value((uint32_t)Message.data[6], 0x8);

					// Signal: Nitrous_Stage_4_Outout
					// Start bit: 52, Length: 1, Byte Order: big
					Nitrous_Stage_4_Outout = process_raw_value((uint32_t)Message.data[6], 0x10);

					// Signal: Nitrous_Stage_3_Output
					// Start bit: 53, Length: 1, Byte Order: big
					Nitrous_Stage_3_Output = process_raw_value((uint32_t)Message.data[6], 0x20);

					// Signal: Nitrous_Stage_2_Outout
					// Start bit: 54, Length: 1, Byte Order: big
					Nitrous_Stage_2_Outout = process_raw_value((uint32_t)Message.data[6], 0x40);

					// Signal: Nitrous_Stsge_1_Output
					// Start bit: 55, Length: 1, Byte Order: big
					Nitrous_Stsge_1_Output = process_raw_value((uint32_t)Message.data[6], 0x80);

					// Signal: TqMgmt_Knob
					// Start bit: 63, Length: 8, Byte Order: big
					TqMgmt_Knob = process_int_value((uint32_t)Message.data[7], 0xFF, true, 1, 0);
				}

				else if (Message.arbitration_id == 0x3EA)
				{
					// Signal: Gearbox_Oil_Pressure
					// Start bit: 7, Length: 16, Byte Order: big
					Gearbox_Oil_Pressure = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: Inj_Stage_3_DC
					// Start bit: 23, Length: 16, Byte Order: big
					Inj_Stage_3_DC = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Inj_Stage_4_DC
					// Start bit: 39, Length: 16, Byte Order: big
					Inj_Stage_4_DC = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Crankcase_Pressure
					// Start bit: 55, Length: 16, Byte Order: big
					Crankcase_Pressure = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, -101.3, 3);
				}

				else if (Message.arbitration_id == 0x3EB)
				{
					// Signal: Race_Timer
					// Start bit: 7, Length: 32, Byte Order: big
					Race_Timer = process_raw_value(((uint32_t)Message.data[0] << 24) | ((uint32_t)Message.data[1] << 16) | ((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFFFFFF);

					// Signal: Ignition_Angle_Bank_1
					// Start bit: 39, Length: 16, Byte Order: big
					Ignition_Angle_Bank_1 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Ignition_Angle_Bank_2
					// Start bit: 55, Length: 16, Byte Order: big
					Ignition_Angle_Bank_2 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3EC)
				{
					// Signal: TqMgmt_DS_Target
					// Start bit: 7, Length: 16, Byte Order: big
					TqMgmt_DS_Target = process_int_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, true, 1, 0);

					// Signal: TqMgmt_DS_Error
					// Start bit: 23, Length: 16, Byte Order: big
					TqMgmt_DS_Error = process_int_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, true, 1, 0);

					// Signal: TqMgmt_DS_Target_Err_Ign_Corr
					// Start bit: 39, Length: 16, Byte Order: big
					TqMgmt_DS_Target_Err_Ign_Corr = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: TqMgmt_DS_Timed_Ign_Corr
					// Start bit: 55, Length: 16, Byte Order: big
					TqMgmt_DS_Timed_Ign_Corr = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3ED)
				{
					// Signal: TqMgmt_Combined_Ign_Corr
					// Start bit: 7, Length: 16, Byte Order: big
					TqMgmt_Combined_Ign_Corr = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3EE)
				{
					// Signal: Lambda_5
					// Start bit: 7, Length: 16, Byte Order: big
					Lambda_5 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_6
					// Start bit: 23, Length: 16, Byte Order: big
					Lambda_6 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_7
					// Start bit: 39, Length: 16, Byte Order: big
					Lambda_7 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_8
					// Start bit: 55, Length: 16, Byte Order: big
					Lambda_8 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.001, 0, 3);
				}

				else if (Message.arbitration_id == 0x3EF)
				{
					// Signal: Lambda_9
					// Start bit: 7, Length: 16, Byte Order: big
					Lambda_9 = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_10
					// Start bit: 23, Length: 16, Byte Order: big
					Lambda_10 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_11
					// Start bit: 39, Length: 16, Byte Order: big
					Lambda_11 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_12
					// Start bit: 55, Length: 16, Byte Order: big
					Lambda_12 = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.001, 0, 3);
				}

				else if (Message.arbitration_id == 0x3F0)
				{
					// Signal: Damper_FL_Raw
					// Start bit: 7, Length: 16, Byte Order: big
					Damper_FL_Raw = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Damper_FR_Raw
					// Start bit: 23, Length: 16, Byte Order: big
					Damper_FR_Raw = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Damper_RL_Raw
					// Start bit: 39, Length: 16, Byte Order: big
					Damper_RL_Raw = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Damper_RR_Raw
					// Start bit: 55, Length: 16, Byte Order: big
					Damper_RR_Raw = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x3F1)
				{
					// Signal: Damper_FL
					// Start bit: 7, Length: 16, Byte Order: big
					Damper_FL = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Damper_FR
					// Start bit: 23, Length: 16, Byte Order: big
					Damper_FR = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Damper_RL
					// Start bit: 39, Length: 16, Byte Order: big
					Damper_RL = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Damper_RR
					// Start bit: 55, Length: 16, Byte Order: big
					Damper_RR = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x469)
				{
					// Signal: ECU_Temperature
					// Start bit: 7, Length: 16, Byte Order: big
					ECU_Temperature = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x470)
				{
					// Signal: Lambda_Overall
					// Start bit: 7, Length: 16, Byte Order: big
					Lambda_Overall = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_Bank_1
					// Start bit: 23, Length: 16, Byte Order: big
					Lambda_Bank_1 = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Lambda_Bank_2
					// Start bit: 39, Length: 16, Byte Order: big
					Lambda_Bank_2 = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: Gear_Selector_Position
					// Start bit: 55, Length: 8, Byte Order: big
					Gear_Selector_Position = process_int_value((uint32_t)Message.data[6], 0xFF, true, 1, 0);

					// Signal: Gear
					// Start bit: 63, Length: 8, Byte Order: big
					Gear = process_int_value((uint32_t)Message.data[7], 0xFF, true, 1, 0);
				}

				else if (Message.arbitration_id == 0x471)
				{
					// Signal: Inj_Differential_Pressure
					// Start bit: 7, Length: 16, Byte Order: big
					Inj_Differential_Pressure = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Accel_Pedal_Position
					// Start bit: 23, Length: 16, Byte Order: big
					Accel_Pedal_Position = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Exhuast_Manifold_Pressure
					// Start bit: 39, Length: 16, Byte Order: big
					Exhuast_Manifold_Pressure = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x472)
				{
					// Signal: Cruise_Target
					// Start bit: 7, Length: 16, Byte Order: big
					Cruise_Target = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Cruise_Last_Target
					// Start bit: 23, Length: 16, Byte Order: big
					Cruise_Last_Target = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Cruise_Error
					// Start bit: 39, Length: 16, Byte Order: big
					Cruise_Error = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Cruise_Input_State
					// Start bit: 51, Length: 12, Byte Order: big
					Cruise_Input_State = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFF);

					// Signal: Cruise_Controller_State
					// Start bit: 55, Length: 4, Byte Order: big
					Cruise_Controller_State = process_raw_value((uint32_t)Message.data[6], 0xF0);
				}

				else if (Message.arbitration_id == 0x473)
				{
					// Signal: Total_Fuel_Used
					// Start bit: 7, Length: 32, Byte Order: big
					Total_Fuel_Used = process_raw_value(((uint32_t)Message.data[0] << 24) | ((uint32_t)Message.data[1] << 16) | ((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFFFFFF);

					// Signal: Aux_3_Fuel_Pump_Output_State
					// Start bit: 32, Length: 1, Byte Order: big
					Aux_3_Fuel_Pump_Output_State = process_raw_value((uint32_t)Message.data[4], 0x1);

					// Signal: Aux_2_Fuel_Pump_Output_State
					// Start bit: 33, Length: 1, Byte Order: big
					Aux_2_Fuel_Pump_Output_State = process_raw_value((uint32_t)Message.data[4], 0x2);

					// Signal: Aux_1_Fuel_Pump_Output_State
					// Start bit: 34, Length: 1, Byte Order: big
					Aux_1_Fuel_Pump_Output_State = process_raw_value((uint32_t)Message.data[4], 0x4);

					// Signal: Primary_Fuel_Pump_Output_State
					// Start bit: 35, Length: 1, Byte Order: big
					Primary_Fuel_Pump_Output_State = process_raw_value((uint32_t)Message.data[4], 0x8);

					// Signal: Traction_Control_Switch_State
					// Start bit: 36, Length: 1, Byte Order: big
					Traction_Control_Switch_State = process_raw_value((uint32_t)Message.data[4], 0x10);

					// Signal: Antilag_Output_State
					// Start bit: 37, Length: 1, Byte Order: big
					Antilag_Output_State = process_raw_value((uint32_t)Message.data[4], 0x20);

					// Signal: Antilag_Switch_State
					// Start bit: 38, Length: 1, Byte Order: big
					Antilag_Switch_State = process_raw_value((uint32_t)Message.data[4], 0x40);

					// Signal: Rolling_Antilag_Switch_State
					// Start bit: 39, Length: 1, Byte Order: big
					Rolling_Antilag_Switch_State = process_raw_value((uint32_t)Message.data[4], 0x80);

					// Signal: Nitrous_Enable_4_Output_State
					// Start bit: 40, Length: 1, Byte Order: big
					Nitrous_Enable_4_Output_State = process_raw_value((uint32_t)Message.data[5], 0x1);

					// Signal: Nitrous_Enable_4_Switch_State
					// Start bit: 41, Length: 1, Byte Order: big
					Nitrous_Enable_4_Switch_State = process_raw_value((uint32_t)Message.data[5], 0x2);

					// Signal: Nitrous_Enable_3_Output_State
					// Start bit: 42, Length: 1, Byte Order: big
					Nitrous_Enable_3_Output_State = process_raw_value((uint32_t)Message.data[5], 0x4);

					// Signal: Nitrous_Enable_3_Switch_State
					// Start bit: 43, Length: 1, Byte Order: big
					Nitrous_Enable_3_Switch_State = process_raw_value((uint32_t)Message.data[5], 0x8);

					// Signal: Nitrous_Enable_2_Output_State
					// Start bit: 44, Length: 1, Byte Order: big
					Nitrous_Enable_2_Output_State = process_raw_value((uint32_t)Message.data[5], 0x10);

					// Signal: Nitrous_Enable_2_Switch_State
					// Start bit: 45, Length: 1, Byte Order: big
					Nitrous_Enable_2_Switch_State = process_raw_value((uint32_t)Message.data[5], 0x20);

					// Signal: Nitrous_Enable_1_Output_State
					// Start bit: 46, Length: 1, Byte Order: big
					Nitrous_Enable_1_Output_State = process_raw_value((uint32_t)Message.data[5], 0x40);

					// Signal: Nitrous_Enable_1_Switch_State
					// Start bit: 47, Length: 1, Byte Order: big
					Nitrous_Enable_1_Switch_State = process_raw_value((uint32_t)Message.data[5], 0x80);

					// Signal: Nitrous_Override_4_Output_State
					// Start bit: 48, Length: 1, Byte Order: big
					Nitrous_Override_4_Output_State = process_raw_value((uint32_t)Message.data[6], 0x1);

					// Signal: Nitrous_Override_4_Switch_State
					// Start bit: 49, Length: 1, Byte Order: big
					Nitrous_Override_4_Switch_State = process_raw_value((uint32_t)Message.data[6], 0x2);

					// Signal: Nitrous_Override_3_Output_State
					// Start bit: 50, Length: 1, Byte Order: big
					Nitrous_Override_3_Output_State = process_raw_value((uint32_t)Message.data[6], 0x4);

					// Signal: Nitrous_Override_3_Switch_State
					// Start bit: 51, Length: 1, Byte Order: big
					Nitrous_Override_3_Switch_State = process_raw_value((uint32_t)Message.data[6], 0x8);

					// Signal: Nitrous_Override_2_Output_State
					// Start bit: 52, Length: 1, Byte Order: big
					Nitrous_Override_2_Output_State = process_raw_value((uint32_t)Message.data[6], 0x10);

					// Signal: Nitrous_Override_2_Switch_State
					// Start bit: 53, Length: 1, Byte Order: big
					Nitrous_Override_2_Switch_State = process_raw_value((uint32_t)Message.data[6], 0x20);

					// Signal: Nitrous_Override_1_Output_State
					// Start bit: 54, Length: 1, Byte Order: big
					Nitrous_Override_1_Output_State = process_raw_value((uint32_t)Message.data[6], 0x40);

					// Signal: Nitrous_Override_1_Switch_State
					// Start bit: 55, Length: 1, Byte Order: big
					Nitrous_Override_1_Switch_State = process_raw_value((uint32_t)Message.data[6], 0x80);

					// Signal: Cut_Percentage_Method
					// Start bit: 59, Length: 4, Byte Order: big
					Cut_Percentage_Method = process_raw_value((uint32_t)Message.data[7], 0xF);

					// Signal: Water_Inj_Adv_Override_Out_State
					// Start bit: 60, Length: 1, Byte Order: big
					Water_Inj_Adv_Override_Out_State = process_raw_value((uint32_t)Message.data[7], 0x10);

					// Signal: Water_Inj_Adv_Override_Sw_State
					// Start bit: 61, Length: 1, Byte Order: big
					Water_Inj_Adv_Override_Sw_State = process_raw_value((uint32_t)Message.data[7], 0x20);

					// Signal: Water_Inj_Adv_Enable_Out_State
					// Start bit: 62, Length: 1, Byte Order: big
					Water_Inj_Adv_Enable_Out_State = process_raw_value((uint32_t)Message.data[7], 0x40);

					// Signal: Water_Inj_Adv_Enable_Sw_State
					// Start bit: 63, Length: 1, Byte Order: big
					Water_Inj_Adv_Enable_Sw_State = process_raw_value((uint32_t)Message.data[7], 0x80);
				}

				else if (Message.arbitration_id == 0x474)
				{
					// Signal: Vertical_G
					// Start bit: 7, Length: 16, Byte Order: big
					Vertical_G = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Pitch_Rate
					// Start bit: 23, Length: 16, Byte Order: big
					Pitch_Rate = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Roll_Rate
					// Start bit: 39, Length: 16, Byte Order: big
					Roll_Rate = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, true, 0.1, 0, 3);

					// Signal: Yaw_Rate
					// Start bit: 55, Length: 16, Byte Order: big
					Yaw_Rate = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, true, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x475)
				{
					// Signal: Primary_Fuel_Pump_Duty
					// Start bit: 7, Length: 16, Byte Order: big
					Primary_Fuel_Pump_Duty = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Aux_1_Fuel_Pump_Duty
					// Start bit: 23, Length: 16, Byte Order: big
					Aux_1_Fuel_Pump_Duty = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Aux_2_Fuel_Pump_Duty
					// Start bit: 39, Length: 16, Byte Order: big
					Aux_2_Fuel_Pump_Duty = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Aux_3_Fuel_Pump_Duty
					// Start bit: 55, Length: 16, Byte Order: big
					Aux_3_Fuel_Pump_Duty = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x476)
				{
					// Signal: Brake_Pressure_Rear
					// Start bit: 7, Length: 16, Byte Order: big
					Brake_Pressure_Rear = process_int_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 1, -101);

					// Signal: Brake_Pressure_Front_Ratio
					// Start bit: 23, Length: 16, Byte Order: big
					Brake_Pressure_Front_Ratio = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Brake_Pressure_Rear_Ratio
					// Start bit: 39, Length: 16, Byte Order: big
					Brake_Pressure_Rear_Ratio = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Brake_Pressure_Difference
					// Start bit: 55, Length: 16, Byte Order: big
					Brake_Pressure_Difference = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);
				}

				else if (Message.arbitration_id == 0x477)
				{
					// Signal: Engine_Limiter_Max_RPM
					// Start bit: 7, Length: 16, Byte Order: big
					Engine_Limiter_Max_RPM = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

					// Signal: Cut_Percentage
					// Start bit: 23, Length: 16, Byte Order: big
					Cut_Percentage = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Engine_Limiter_Function
					// Start bit: 39, Length: 8, Byte Order: big
					Engine_Limiter_Function = process_raw_value((uint32_t)Message.data[4], 0xFF);

					// Signal: RPM_Limiter_Function
					// Start bit: 47, Length: 8, Byte Order: big
					RPM_Limiter_Function = process_raw_value((uint32_t)Message.data[5], 0xFF);

					// Signal: Cut_Percentage_Function
					// Start bit: 55, Length: 8, Byte Order: big
					Cut_Percentage_Function = process_raw_value((uint32_t)Message.data[6], 0xFF);

					// Signal: RPM_Limiter_Method
					// Start bit: 59, Length: 4, Byte Order: big
					RPM_Limiter_Method = process_raw_value((uint32_t)Message.data[7], 0xF);

					// Signal: Engine_Limiter_Method
					// Start bit: 63, Length: 4, Byte Order: big
					Engine_Limiter_Method = process_raw_value((uint32_t)Message.data[7], 0xF0);
				}

				else if (Message.arbitration_id == 0x6F0)
				{
					// Signal: FL_Tire_Pressure
					// Start bit: 7, Length: 16, Byte Order: big
					FL_Tire_Pressure = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: FR_Tire_Pressure
					// Start bit: 23, Length: 16, Byte Order: big
					FR_Tire_Pressure = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: RL_Tire_Pressure
					// Start bit: 39, Length: 16, Byte Order: big
					RL_Tire_Pressure = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: RR_Tire_Pressure
					// Start bit: 55, Length: 16, Byte Order: big
					RR_Tire_Pressure = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, -101.3, 3);
				}

				else if (Message.arbitration_id == 0x6F1)
				{
					// Signal: FL_Tire_Temp
					// Start bit: 7, Length: 16, Byte Order: big
					FL_Tire_Temp = process_raw_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF);

					// Signal: FR_Tire_Temp
					// Start bit: 23, Length: 16, Byte Order: big
					FR_Tire_Temp = process_raw_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF);

					// Signal: RL_Tire_Temp
					// Start bit: 39, Length: 16, Byte Order: big
					RL_Tire_Temp = process_raw_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF);

					// Signal: RR_Tire_Temp
					// Start bit: 55, Length: 16, Byte Order: big
					RR_Tire_Temp = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF);
				}

				else if (Message.arbitration_id == 0x6F2)
				{
					// Signal: FL_TPMS_Voltage
					// Start bit: 7, Length: 16, Byte Order: big
					FL_TPMS_Voltage = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.001, 0, 3);

					// Signal: FR_TPMS_Voltage
					// Start bit: 23, Length: 16, Byte Order: big
					FR_TPMS_Voltage = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.001, 0, 3);

					// Signal: RL_TPMS_Voltage
					// Start bit: 39, Length: 16, Byte Order: big
					RL_TPMS_Voltage = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.001, 0, 3);

					// Signal: RR_TPMS_Voltage
					// Start bit: 55, Length: 16, Byte Order: big
					RR_TPMS_Voltage = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.001, 0, 3);
				}

				else if (Message.arbitration_id == 0x6F3)
				{
					// Signal: Front_Tire_Pres_Target
					// Start bit: 7, Length: 16, Byte Order: big
					Front_Tire_Pres_Target = process_float_value(((uint32_t)Message.data[0] << 8) | (uint32_t)Message.data[1], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: Rear_Tire_Pres_Target
					// Start bit: 23, Length: 16, Byte Order: big
					Rear_Tire_Pres_Target = process_float_value(((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFF, false, 0.1, -101.3, 3);

					// Signal: FL_Tire_Leaking
					// Start bit: 32, Length: 1, Byte Order: big
					FL_Tire_Leaking = process_raw_value((uint32_t)Message.data[4], 0x1);

					// Signal: FR_Tire_Leaking
					// Start bit: 33, Length: 1, Byte Order: big
					FR_Tire_Leaking = process_raw_value((uint32_t)Message.data[4], 0x2);

					// Signal: RL_Tire_Leaking
					// Start bit: 34, Length: 1, Byte Order: big
					RL_Tire_Leaking = process_raw_value((uint32_t)Message.data[4], 0x4);

					// Signal: RR_Tire_Leaking
					// Start bit: 35, Length: 1, Byte Order: big
					RR_Tire_Leaking = process_raw_value((uint32_t)Message.data[4], 0x8);

					// Signal: Engine_Protection_Level
					// Start bit: 47, Length: 8, Byte Order: big
					Engine_Protection_Level = process_raw_value((uint32_t)Message.data[5], 0xFF);

					// Signal: Engine_Protection_DTC
					// Start bit: 53, Length: 14, Byte Order: big
					Engine_Protection_DTC = process_raw_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0x3FFF);

					// Signal: Engine_Protection_DTC_Class
					// Start bit: 55, Length: 2, Byte Order: big
					Engine_Protection_DTC_Class = process_raw_value((uint32_t)Message.data[6], 0xC0);
				}

				else if (Message.arbitration_id == 0x6F4)
				{
					// Signal: Park_Light_State
					// Start bit: 0, Length: 1, Byte Order: big
					Park_Light_State = process_raw_value((uint32_t)Message.data[0], 0x1);

					// Signal: Head_Light_State
					// Start bit: 1, Length: 1, Byte Order: big
					Head_Light_State = process_raw_value((uint32_t)Message.data[0], 0x2);

					// Signal: High_Beam_Light_State
					// Start bit: 2, Length: 1, Byte Order: big
					High_Beam_Light_State = process_raw_value((uint32_t)Message.data[0], 0x4);

					// Signal: Left_Indicator_State
					// Start bit: 3, Length: 1, Byte Order: big
					Left_Indicator_State = process_raw_value((uint32_t)Message.data[0], 0x8);

					// Signal: Right_Indicator_state
					// Start bit: 4, Length: 1, Byte Order: big
					Right_Indicator_state = process_raw_value((uint32_t)Message.data[0], 0x10);
				}

				else if (Message.arbitration_id == 0x6F6)
				{
					// Signal: Fuel_Used_Since_Trip1_Reset
					// Start bit: 7, Length: 32, Byte Order: big
					Fuel_Used_Since_Trip1_Reset = process_int_value(((uint32_t)Message.data[0] << 24) | ((uint32_t)Message.data[1] << 16) | ((uint32_t)Message.data[2] << 8) | (uint32_t)Message.data[3], 0xFFFFFFFF, true, 1, 0);

					// Signal: Trip_Meter_1
					// Start bit: 39, Length: 32, Byte Order: big
					Trip_Meter_1 = process_int_value(((uint32_t)Message.data[4] << 24) | ((uint32_t)Message.data[5] << 16) | ((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFFFFFF, true, 1, 0);
				}

				else if (Message.arbitration_id == 0x6F7)
				{
					// Signal: Generic_Output_17_State
					// Start bit: 8, Length: 1, Byte Order: big
					Generic_Output_17_State = process_raw_value((uint32_t)Message.data[1], 0x1);

					// Signal: Generic_Output_18_State
					// Start bit: 9, Length: 1, Byte Order: big
					Generic_Output_18_State = process_raw_value((uint32_t)Message.data[1], 0x2);

					// Signal: Generic_Output_19_State
					// Start bit: 10, Length: 1, Byte Order: big
					Generic_Output_19_State = process_raw_value((uint32_t)Message.data[1], 0x4);

					// Signal: Generic_Output_20_State
					// Start bit: 11, Length: 1, Byte Order: big
					Generic_Output_20_State = process_raw_value((uint32_t)Message.data[1], 0x8);

					// Signal: Generic_Output_9_State
					// Start bit: 16, Length: 1, Byte Order: big
					Generic_Output_9_State = process_raw_value((uint32_t)Message.data[2], 0x1);

					// Signal: Generic_Output_10_State
					// Start bit: 17, Length: 1, Byte Order: big
					Generic_Output_10_State = process_raw_value((uint32_t)Message.data[2], 0x2);

					// Signal: Generic_Output_11_State
					// Start bit: 18, Length: 1, Byte Order: big
					Generic_Output_11_State = process_raw_value((uint32_t)Message.data[2], 0x4);

					// Signal: Generic_Output_12_State
					// Start bit: 19, Length: 1, Byte Order: big
					Generic_Output_12_State = process_raw_value((uint32_t)Message.data[2], 0x8);

					// Signal: Generic_Output_13_State
					// Start bit: 20, Length: 1, Byte Order: big
					Generic_Output_13_State = process_raw_value((uint32_t)Message.data[2], 0x10);

					// Signal: Generic_Output_14_State
					// Start bit: 21, Length: 1, Byte Order: big
					Generic_Output_14_State = process_raw_value((uint32_t)Message.data[2], 0x20);

					// Signal: Generic_Output_15_State
					// Start bit: 22, Length: 1, Byte Order: big
					Generic_Output_15_State = process_raw_value((uint32_t)Message.data[2], 0x40);

					// Signal: Generic_Output_16_State
					// Start bit: 23, Length: 1, Byte Order: big
					Generic_Output_16_State = process_raw_value((uint32_t)Message.data[2], 0x80);

					// Signal: Generic_Output_1_State
					// Start bit: 24, Length: 1, Byte Order: big
					Generic_Output_1_State = process_raw_value((uint32_t)Message.data[3], 0x1);

					// Signal: Generic_Output_2_State
					// Start bit: 25, Length: 1, Byte Order: big
					Generic_Output_2_State = process_raw_value((uint32_t)Message.data[3], 0x2);

					// Signal: Generic_Output_3_State
					// Start bit: 26, Length: 1, Byte Order: big
					Generic_Output_3_State = process_raw_value((uint32_t)Message.data[3], 0x4);

					// Signal: Generic_Output_4_State
					// Start bit: 27, Length: 1, Byte Order: big
					Generic_Output_4_State = process_raw_value((uint32_t)Message.data[3], 0x8);

					// Signal: Generic_Output_5_State
					// Start bit: 28, Length: 1, Byte Order: big
					Generic_Output_5_State = process_raw_value((uint32_t)Message.data[3], 0x10);

					// Signal: Generic_Output_6_State
					// Start bit: 29, Length: 1, Byte Order: big
					Generic_Output_6_State = process_raw_value((uint32_t)Message.data[3], 0x20);

					// Signal: Generic_Output_7_State
					// Start bit: 30, Length: 1, Byte Order: big
					Generic_Output_7_State = process_raw_value((uint32_t)Message.data[3], 0x40);

					// Signal: Generic_Output_8_State
					// Start bit: 31, Length: 1, Byte Order: big
					Generic_Output_8_State = process_raw_value((uint32_t)Message.data[3], 0x80);

					// Signal: Calculated_Air_Temp
					// Start bit: 39, Length: 16, Byte Order: big
					Calculated_Air_Temp = process_float_value(((uint32_t)Message.data[4] << 8) | (uint32_t)Message.data[5], 0xFFFF, false, 0.1, 0, 3);

					// Signal: Water_Inj_Adv_Solenoid_Duty
					// Start bit: 55, Length: 16, Byte Order: big
					Water_Inj_Adv_Solenoid_Duty = process_float_value(((uint32_t)Message.data[6] << 8) | (uint32_t)Message.data[7], 0xFFFF, false, 0.1, 0, 3);
				}

				else if (Message.arbitration_id == 0x6F8)
				{
					// Signal: Exhaust_Cutout_State
					// Start bit: 7, Length: 8, Byte Order: big
					Exhaust_Cutout_State = process_int_value((uint32_t)Message.data[0], 0xFF, true, 1, 0);

					// Signal: Nitrous_Bottle_Opener_State
					// Start bit: 15, Length: 8, Byte Order: big
					Nitrous_Bottle_Opener_State = process_int_value((uint32_t)Message.data[1], 0xFF, true, 1, 0);

					// Signal: Generic_Open_Loop_Motor_1_State
					// Start bit: 23, Length: 8, Byte Order: big
					Generic_Open_Loop_Motor_1_State = process_int_value((uint32_t)Message.data[2], 0xFF, true, 1, 0);

					// Signal: Generic_Open_Loop_Motor_2_State
					// Start bit: 31, Length: 8, Byte Order: big
					Generic_Open_Loop_Motor_2_State = process_int_value((uint32_t)Message.data[3], 0xFF, true, 1, 0);

					// Signal: Generic_Open_Loop_Motor_3_State
					// Start bit: 39, Length: 8, Byte Order: big
					Generic_Open_Loop_Motor_3_State = process_int_value((uint32_t)Message.data[4], 0xFF, true, 1, 0);
				}
				// ################ End Generated CAN Code ################
			}
		}
	}
	if (Message.Bus == CAN_2)
	{
	}
	if (Message.Bus == CAN_3)
	{
	}
}

/* Run 2000Hz Functions here */
void events_2000Hz()
{
}

/* Run 1000Hz Functions here */
void events_1000Hz()
{
}

/* Run 500Hz Functions here */
void events_500Hz()
{
}

/* Run 200Hz Functions here */
void events_200Hz()
{
}

/* Run 100Hz Functions here */
void events_100Hz()
{
}

/* Run 50Hz Functions here */
void events_50Hz()
{
}

/* Run 20Hz Functions here */
void events_20Hz()
{
}

/* Run 10Hz Functions here */
void events_10Hz()
{
}
/* Run 5Hz Functions here */
void events_5Hz()
{
	toggleLED(LED_1);
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}
