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
//################ Generated Variable Declarations ################
// Copy to Variable Declarations area in user_code.c 

float Right_Turnsignal_value;
float Left_Turnsignal_value;
float Door_Lock_State_value;
float Door_Lock_switch_value;
float Snow_Mode_Enabled_value;
float TPS_Target_value;
float Throttle_Based_value;
float unknoen0x551_B12_value;
float LH_AC_Temp_value;
float RH_AC_temp_value;
float HVAC_Overhead_Inverted_Bit_value;
float Front_Defrost_Inverted_Active_value;
float HVAC_Freshair_Press_Changestate_value;
float HVAC_Recirc_Press_Changestate_value;
float HVAC_R_Defrost_Buttonpress_value;
float RH_HVAC__Knobpress_Changestate_value;
float HVAC_AC_Enabled_Bit_value;
float HVAC_Off_Buttonpress_Changestate_value;
float LH_HVAC_Knobpress_Changestate_value;
float HVAC_Fan_Accel_Changestate_value;
float HVAC_Fan_Decel_Changestate_value;
float HVAC_Rear_Press_ChangeState_value;
float Shifter_Position_value;
float Tow_Mode_value;
float tpms_FR_value;
float tpms_FL_value;
float tpms_RR_value;
float tpms_RL_value;
float FR_TPMS_Activated_value;
float FL_TPMS_Activated_value;
float RR_TPMS_Activated_value;
float RL_TPMS_Activated_value;
float Rear__Defrost_value;
float VSS_Based_value;
float Vss_Based_3_value;
float VSS_Based_2_value;
float tow_mode_button_engaged_value;
float Traction_Control_Disable_Bit_value;
float Steering_Wheel_360_value;
float Brake_Pres_value;
float Pitch_value;
float Yaw_value;
float Roll_value;
float TPS_overrun_value;
float something_tq_related_value;
float odd_tps_or_speed_0x286B2_value;
float odd_tps_or_speed_0x286B3_value;
float odd_tps_or_speed_0x286B4_value;
float unknown0x286_B5_value;
float WS_3_value;
float WS_4_value;
float Vehicle_Speed_or_ws_value;
float Counter_0x285_value;
float Odd_Signal_0x285B8_value;
float WS_1_value;
float WS_2_value;
float WS_related_value;
float Counter_0x284_value;
float Odd_Signal_0x284B8_value;
float Doorlock_engagements_value;
float VSS_Based_1_value;
float TQ_Converter_Pres_value;
float Traction_Control_Disable_Bit_1_value;
float Counter_0x245_value;
float Accel_Pedal_value;
float TPS_Inverted_value;
float Cruise_Enabled_value;
float Cruise_Button_Pressed_value;
float cruise_cancel_pressed_value;
float DCA_Distance_Pressed_value;
float Cruise_Decel_Set_value;
float Cruise_Accel_Res_value;
float no_steering_buttons_pressed_value;
float DCA_Pressed_value;
float brake_pedal_depressed_value;
float Engine_Speed_value;
float yaw_related_value;
float TPS_Based_value;
float TPS_Based_1_value;
float Gear_Bit_value;
float Gear_value;
float unknown_Gear0x177_value;
float shifttiming_retard_maybe_value;
float unknown0x176_B12_value;
float unknown0x176_B34_value;
float unknown0x176_B7_value;
float shift_tq_reduction_value;
float trans_related2_value;
float timer_0x174_value;
float throttle_related_value;
float unknown0x160_B23_value;
float Steering_Wheel_value;
float Steering_Angle_ROC_value;
float Frame_Type_value;
float Service_ID_value;
float Mode22_DID_value;
float Single_Frame_length_value;
float VVEL_Timing_B2_unscaled_value;
float VVEL_Timing_B1_unscaled_value;
float VVEL_Sensor_B2_value;
float VVEL_Sensor_B1_value;
float VTC_Exh_B2_Duty_Cycle_value;
float VTC_Exh_B1_Duty_Cycle_value;
float Vehicle_Speed_value;
float Throttle_Pos_S1_B2_value;
float Throttle_Pos_S1_B1_value;
float EVAP_Purge_Control_Valve_DC_value;
float MAF_value;
float MAF_Sensor_value;
float Intake_Valve_Timing_B2_value;
float Intake_Valve_Solenoid_B1_Duty_value;
float Intake_Air_Temp_value;
float Ingition_Timing_value;
float IP_Pulley_Speed_value;
float Ho2_S2_B2_value;
float Ho2_S2_B1_value;
float Intake_Valve_Timing_B1_value;
float Hi_pres_Fuel_Pump_value;
float Fuel_Temp_value;
float Fuel_Pump_Relay_value;
float Fuel_Pump_Duty_Cycle_value;
float Fuel_Pressure_Sensor_value;
float Fuel_Pressure_value;
float Fuel_Level_Sensor_value;
float Fuel_Injector_Pulse_Width_B2_value;
float Fuel_Injector_Pulse_Width_B1_value;
float Fuel_Injection_Timing_value;
float Fan_Duty_Cycle_value;
float EXH_Valve_Timing_B2_value;
float EXH_Valve_Timing_B1_value;
float EVAP_System_Pressure_Sensor_value;
float Engine_Oil_Pressure_Sensor_value;
float Engine_Oil_Temp_value;
float Cooling_Fan_Speed_value;
float Engine_Coolant_Temp_value;
float Calculated_Load_value;
float Battery_Voltage_value;
float Battery_Temp_Sensor_value;
float Battery_Current_Sensor_value;
float Base_Fuel_Schedule_value;
float Alternator_Duty_Cycle_value;
float AC_Relay_value;
float Accel_Sensor_2_value;
float Accel_Sensor_1_value;
float AC_Pressure_Sensor_value;
float AC_Evap_Temp_value;
float AC_Evap_Target_value;
float Air_Fuel_S1_B2_value;
float Air_Fuel_S1_B1_value;
float Air_Fuel_S1_Heater_B2_value;
float Air_Fuel_S1_Heater_B1_value;
float Air_Fuel_Alpha_B2_value;
float Air_Fuel_Alpha_B1_value;
float AC_Signal_value;
float Brake_Switch_value;
float hex22A_B01_value;
float hex22A_B23_value;
float hex22A_B4_value;
float hex22A_B5_value;
float hex22A_B6_value;
float hex22A_B7_value;
float hex22B_B01_value;
float hex22B_B23_value;
float hex22B_B4_value;
float hex22B_B5_value;
float hex22B_B6_value;
float hex22B_B7_value;
float hex22C_B0_value;
float hex22C_B1_value;
float hex22C_B2_value;
float hex22C_B3_value;
float hex22C_B4_value;
float hex22C_B5_value;
float hex22C_B6_value;
float hex22C_B7_value;
float hex22D_B0_value;
float hex22D_B1_value;
float hex22D_B2_value;
float hex230_B0_value;
float hex230_B1_value;
float hex230_B2_value;
float hex230_B3_value;
float hex230_B4_value;
float hex230_B5_value;
float hex230_B67_value;
float hex231_B0_value;
float hex231_B12_value;
float hex232_B0_value;
float hex232_B1_value;
float hex232_B2_value;
float hex233_B0_value;
float hex233_B1_value;
float hex233_B2_value;
float hex233_B3_value;
float hex233_B4_value;
float hex233_B5_value;
float hex233_B6_value;
float hex233_B7_value;
float hex234_B0_value;
float hex234_B1_value;
float hex234_B2_value;
float hex234_B3_value;
float hex330_B01_value;
float hex330_B23_value;
float hex330_B45_value;
float hex330_B67_value;
float hex340_B01_value;
float hex340_B23_value;
float hex340_B45_value;
float hex340_B67_value;
float hex350_B0_value;
float hex350_B1_value;
float hex350_B2_value;
float hex350_B3_value;
float hex350_B4_value;
float hex350_B5_value;
float hex350_B6_value;
float hex350_B7_value;
float hex360_B0_value;
float hex360_B1_value;
float hex360_B2_value;
float hex360_B3_value;
float hex360_B4_value;
float hex360_B5_value;
float hex360_B6_value;
float hex360_B7_value;
float hex370_B01_value;
float hex370_B23_value;
float hex370_B45_value;
float hex370_B67_value;
float hex3FF_B0_value;
float hex3FF_B1_value;
float hex3FF_B2_value;
float hex3FF_B3_value;
float hex3FF_B4_value;
float hex3FF_B5_value;
float hex3FF_B6_value;
float hex3FF_B7_value;
//################ End Generated Variable Declarations ################

/* End Variable Declarations */

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

		if (Message.arbitration_id == 0x60d) {
			// Signal: Right_Turnsignal
			// Start bit: 14, Length: 1, Byte Order: big
			uint32_t Right_Turnsignal_raw_value = 0;
			Right_Turnsignal_raw_value |= (uint32_t)Message.data[1];
			Right_Turnsignal_value = process_numeric_value(Right_Turnsignal_raw_value, 0x40, false, 1, 0);

			// Signal: Left_Turnsignal
			// Start bit: 13, Length: 1, Byte Order: big
			uint32_t Left_Turnsignal_raw_value = 0;
			Left_Turnsignal_raw_value |= (uint32_t)Message.data[1];
			Left_Turnsignal_value = process_numeric_value(Left_Turnsignal_raw_value, 0x20, false, 1, 0);

			// Signal: Door_Lock_State
			// Start bit: 20, Length: 1, Byte Order: big
			uint32_t Door_Lock_State_raw_value = 0;
			Door_Lock_State_raw_value |= (uint32_t)Message.data[2];
			Door_Lock_State_value = process_numeric_value(Door_Lock_State_raw_value, 0x10, false, 1, 0);

			// Signal: Door_Lock_switch
			// Start bit: 19, Length: 1, Byte Order: big
			uint32_t Door_Lock_switch_raw_value = 0;
			Door_Lock_switch_raw_value |= (uint32_t)Message.data[2];
			Door_Lock_switch_value = process_numeric_value(Door_Lock_switch_raw_value, 0x8, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x5c5) {
			// Signal: Snow_Mode_Enabled
			// Start bit: 55, Length: 1, Byte Order: big
			uint32_t Snow_Mode_Enabled_raw_value = 0;
			Snow_Mode_Enabled_raw_value |= (uint32_t)Message.data[6];
			Snow_Mode_Enabled_value = process_numeric_value(Snow_Mode_Enabled_raw_value, 0x80, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x580) {
			// Signal: TPS_Target
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t TPS_Target_raw_value = 0;
			TPS_Target_raw_value |= (uint32_t)Message.data[0] << 8;
			TPS_Target_raw_value |= (uint32_t)Message.data[1];
			TPS_Target_value = process_numeric_value(TPS_Target_raw_value, 0xFFFF, false, 1, 0);

			// Signal: Throttle_Based
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t Throttle_Based_raw_value = 0;
			Throttle_Based_raw_value |= (uint32_t)Message.data[7];
			Throttle_Based_value = process_numeric_value(Throttle_Based_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x551) {
			// Signal: unknoen0x551_B12
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t unknoen0x551_B12_raw_value = 0;
			unknoen0x551_B12_raw_value |= (uint32_t)Message.data[0] << 8;
			unknoen0x551_B12_raw_value |= (uint32_t)Message.data[1];
			unknoen0x551_B12_value = process_numeric_value(unknoen0x551_B12_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x54a) {
			// Signal: LH_AC_Temp
			// Start bit: 38, Length: 7, Byte Order: big
			uint32_t LH_AC_Temp_raw_value = 0;
			LH_AC_Temp_raw_value |= (uint32_t)Message.data[4];
			LH_AC_Temp_value = process_numeric_value(LH_AC_Temp_raw_value, 0x7F, false, 1, 0);

			// Signal: RH_AC_temp
			// Start bit: 46, Length: 7, Byte Order: big
			uint32_t RH_AC_temp_raw_value = 0;
			RH_AC_temp_raw_value |= (uint32_t)Message.data[5];
			RH_AC_temp_value = process_numeric_value(RH_AC_temp_raw_value, 0x7F, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x541) {
			// Signal: HVAC_Overhead_Inverted_Bit
			// Start bit: 5, Length: 1, Byte Order: big
			uint32_t HVAC_Overhead_Inverted_Bit_raw_value = 0;
			HVAC_Overhead_Inverted_Bit_raw_value |= (uint32_t)Message.data[0];
			HVAC_Overhead_Inverted_Bit_value = process_numeric_value(HVAC_Overhead_Inverted_Bit_raw_value, 0x20, false, 1, 0);

			// Signal: Front_Defrost_Inverted_Active
			// Start bit: 0, Length: 1, Byte Order: big
			uint32_t Front_Defrost_Inverted_Active_raw_value = 0;
			Front_Defrost_Inverted_Active_raw_value |= (uint32_t)Message.data[0];
			Front_Defrost_Inverted_Active_value = process_numeric_value(Front_Defrost_Inverted_Active_raw_value, 0x1, false, 1, 0);

			// Signal: HVAC_Freshair_Press_Changestate
			// Start bit: 11, Length: 1, Byte Order: big
			uint32_t HVAC_Freshair_Press_Changestate_raw_value = 0;
			HVAC_Freshair_Press_Changestate_raw_value |= (uint32_t)Message.data[1];
			HVAC_Freshair_Press_Changestate_value = process_numeric_value(HVAC_Freshair_Press_Changestate_raw_value, 0x8, false, 1, 0);

			// Signal: HVAC_Recirc_Press_Changestate
			// Start bit: 9, Length: 1, Byte Order: big
			uint32_t HVAC_Recirc_Press_Changestate_raw_value = 0;
			HVAC_Recirc_Press_Changestate_raw_value |= (uint32_t)Message.data[1];
			HVAC_Recirc_Press_Changestate_value = process_numeric_value(HVAC_Recirc_Press_Changestate_raw_value, 0x2, false, 1, 0);

			// Signal: HVAC_R_Defrost_Buttonpress
			// Start bit: 8, Length: 1, Byte Order: big
			uint32_t HVAC_R_Defrost_Buttonpress_raw_value = 0;
			HVAC_R_Defrost_Buttonpress_raw_value |= (uint32_t)Message.data[1];
			HVAC_R_Defrost_Buttonpress_value = process_numeric_value(HVAC_R_Defrost_Buttonpress_raw_value, 0x1, false, 1, 0);

			// Signal: RH_HVAC__Knobpress_Changestate
			// Start bit: 19, Length: 1, Byte Order: big
			uint32_t RH_HVAC__Knobpress_Changestate_raw_value = 0;
			RH_HVAC__Knobpress_Changestate_raw_value |= (uint32_t)Message.data[2];
			RH_HVAC__Knobpress_Changestate_value = process_numeric_value(RH_HVAC__Knobpress_Changestate_raw_value, 0x8, false, 1, 0);

			// Signal: HVAC_AC_Enabled_Bit
			// Start bit: 18, Length: 1, Byte Order: big
			uint32_t HVAC_AC_Enabled_Bit_raw_value = 0;
			HVAC_AC_Enabled_Bit_raw_value |= (uint32_t)Message.data[2];
			HVAC_AC_Enabled_Bit_value = process_numeric_value(HVAC_AC_Enabled_Bit_raw_value, 0x4, false, 1, 0);

			// Signal: HVAC_Off_Buttonpress_Changestate
			// Start bit: 16, Length: 1, Byte Order: big
			uint32_t HVAC_Off_Buttonpress_Changestate_raw_value = 0;
			HVAC_Off_Buttonpress_Changestate_raw_value |= (uint32_t)Message.data[2];
			HVAC_Off_Buttonpress_Changestate_value = process_numeric_value(HVAC_Off_Buttonpress_Changestate_raw_value, 0x1, false, 1, 0);

			// Signal: LH_HVAC_Knobpress_Changestate
			// Start bit: 31, Length: 1, Byte Order: big
			uint32_t LH_HVAC_Knobpress_Changestate_raw_value = 0;
			LH_HVAC_Knobpress_Changestate_raw_value |= (uint32_t)Message.data[3];
			LH_HVAC_Knobpress_Changestate_value = process_numeric_value(LH_HVAC_Knobpress_Changestate_raw_value, 0x80, false, 1, 0);

			// Signal: HVAC_Fan_Accel_Changestate
			// Start bit: 28, Length: 1, Byte Order: big
			uint32_t HVAC_Fan_Accel_Changestate_raw_value = 0;
			HVAC_Fan_Accel_Changestate_raw_value |= (uint32_t)Message.data[3];
			HVAC_Fan_Accel_Changestate_value = process_numeric_value(HVAC_Fan_Accel_Changestate_raw_value, 0x10, false, 1, 0);

			// Signal: HVAC_Fan_Decel_Changestate
			// Start bit: 27, Length: 1, Byte Order: big
			uint32_t HVAC_Fan_Decel_Changestate_raw_value = 0;
			HVAC_Fan_Decel_Changestate_raw_value |= (uint32_t)Message.data[3];
			HVAC_Fan_Decel_Changestate_value = process_numeric_value(HVAC_Fan_Decel_Changestate_raw_value, 0x8, false, 1, 0);

			// Signal: HVAC_Rear_Press_ChangeState
			// Start bit: 36, Length: 1, Byte Order: big
			uint32_t HVAC_Rear_Press_ChangeState_raw_value = 0;
			HVAC_Rear_Press_ChangeState_raw_value |= (uint32_t)Message.data[4];
			HVAC_Rear_Press_ChangeState_value = process_numeric_value(HVAC_Rear_Press_ChangeState_raw_value, 0x10, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x421) {
			// Signal: Shifter_Position
			// Start bit: 7, Length: 5, Byte Order: big
			uint32_t Shifter_Position_raw_value = 0;
			Shifter_Position_raw_value |= (uint32_t)Message.data[0];
			Shifter_Position_value = process_numeric_value(Shifter_Position_raw_value, 0xF8, false, 1, 0);

			// Signal: Tow_Mode
			// Start bit: 19, Length: 1, Byte Order: big
			uint32_t Tow_Mode_raw_value = 0;
			Tow_Mode_raw_value |= (uint32_t)Message.data[2];
			Tow_Mode_value = process_numeric_value(Tow_Mode_raw_value, 0x8, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x385) {
			// Signal: tpms_FR
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t tpms_FR_raw_value = 0;
			tpms_FR_raw_value |= (uint32_t)Message.data[2];
			tpms_FR_value = process_numeric_value(tpms_FR_raw_value, 0xFF, false, 1.7325, 0);

			// Signal: tpms_FL
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t tpms_FL_raw_value = 0;
			tpms_FL_raw_value |= (uint32_t)Message.data[3];
			tpms_FL_value = process_numeric_value(tpms_FL_raw_value, 0xFF, false, 1.7325, 0);

			// Signal: tpms_RR
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t tpms_RR_raw_value = 0;
			tpms_RR_raw_value |= (uint32_t)Message.data[4];
			tpms_RR_value = process_numeric_value(tpms_RR_raw_value, 0xFF, false, 1.7325, 0);

			// Signal: tpms_RL
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t tpms_RL_raw_value = 0;
			tpms_RL_raw_value |= (uint32_t)Message.data[5];
			tpms_RL_value = process_numeric_value(tpms_RL_raw_value, 0xFF, false, 1.7325, 0);

			// Signal: FR_TPMS_Activated
			// Start bit: 55, Length: 1, Byte Order: big
			uint32_t FR_TPMS_Activated_raw_value = 0;
			FR_TPMS_Activated_raw_value |= (uint32_t)Message.data[6];
			FR_TPMS_Activated_value = process_numeric_value(FR_TPMS_Activated_raw_value, 0x80, false, 1, 0);

			// Signal: FL_TPMS_Activated
			// Start bit: 54, Length: 1, Byte Order: big
			uint32_t FL_TPMS_Activated_raw_value = 0;
			FL_TPMS_Activated_raw_value |= (uint32_t)Message.data[6];
			FL_TPMS_Activated_value = process_numeric_value(FL_TPMS_Activated_raw_value, 0x40, false, 1, 0);

			// Signal: RR_TPMS_Activated
			// Start bit: 53, Length: 1, Byte Order: big
			uint32_t RR_TPMS_Activated_raw_value = 0;
			RR_TPMS_Activated_raw_value |= (uint32_t)Message.data[6];
			RR_TPMS_Activated_value = process_numeric_value(RR_TPMS_Activated_raw_value, 0x20, false, 1, 0);

			// Signal: RL_TPMS_Activated
			// Start bit: 52, Length: 1, Byte Order: big
			uint32_t RL_TPMS_Activated_raw_value = 0;
			RL_TPMS_Activated_raw_value |= (uint32_t)Message.data[6];
			RL_TPMS_Activated_value = process_numeric_value(RL_TPMS_Activated_raw_value, 0x10, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x35d) {
			// Signal: Rear__Defrost
			// Start bit: 2, Length: 2, Byte Order: big
			uint32_t Rear__Defrost_raw_value = 0;
			Rear__Defrost_raw_value |= (uint32_t)Message.data[0];
			Rear__Defrost_value = process_numeric_value(Rear__Defrost_raw_value, 0x6, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x355) {
			// Signal: VSS_Based
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t VSS_Based_raw_value = 0;
			VSS_Based_raw_value |= (uint32_t)Message.data[0] << 8;
			VSS_Based_raw_value |= (uint32_t)Message.data[1];
			VSS_Based_value = process_numeric_value(VSS_Based_raw_value, 0xFFFF, false, 1, 0);

			// Signal: Vss_Based_3
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t Vss_Based_3_raw_value = 0;
			Vss_Based_3_raw_value |= (uint32_t)Message.data[2] << 8;
			Vss_Based_3_raw_value |= (uint32_t)Message.data[3];
			Vss_Based_3_value = process_numeric_value(Vss_Based_3_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x354) {
			// Signal: VSS_Based_2
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t VSS_Based_2_raw_value = 0;
			VSS_Based_2_raw_value |= (uint32_t)Message.data[0] << 8;
			VSS_Based_2_raw_value |= (uint32_t)Message.data[1];
			VSS_Based_2_value = process_numeric_value(VSS_Based_2_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x2de) {
			// Signal: tow_mode_button_engaged
			// Start bit: 15, Length: 1, Byte Order: big
			uint32_t tow_mode_button_engaged_raw_value = 0;
			tow_mode_button_engaged_raw_value |= (uint32_t)Message.data[1];
			tow_mode_button_engaged_value = process_numeric_value(tow_mode_button_engaged_raw_value, 0x80, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x2b3) {
			// Signal: Traction_Control_Disable_Bit
			// Start bit: 25, Length: 1, Byte Order: big
			uint32_t Traction_Control_Disable_Bit_raw_value = 0;
			Traction_Control_Disable_Bit_raw_value |= (uint32_t)Message.data[3];
			Traction_Control_Disable_Bit_value = process_numeric_value(Traction_Control_Disable_Bit_raw_value, 0x2, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x2ab) {
			// Signal: Steering_Wheel_360
			// Start bit: 17, Length: 13, Byte Order: big
			uint32_t Steering_Wheel_360_raw_value = 0;
			Steering_Wheel_360_raw_value |= (uint32_t)Message.data[2] << 16;
			Steering_Wheel_360_raw_value |= (uint32_t)Message.data[3] << 8;
			Steering_Wheel_360_raw_value |= (uint32_t)Message.data[4];
			Steering_Wheel_360_value = process_numeric_value(Steering_Wheel_360_raw_value, 0x3FFE0, true, 0.1, 0);

		}

		else if (Message.arbitration_id == 0x2aa) {
			// Signal: Brake_Pres
			// Start bit: 47, Length: 16, Byte Order: big
			uint32_t Brake_Pres_raw_value = 0;
			Brake_Pres_raw_value |= (uint32_t)Message.data[5] << 8;
			Brake_Pres_raw_value |= (uint32_t)Message.data[6];
			Brake_Pres_value = process_numeric_value(Brake_Pres_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x292) {
			// Signal: Pitch
			// Start bit: 7, Length: 12, Byte Order: big
			uint32_t Pitch_raw_value = 0;
			Pitch_raw_value |= (uint32_t)Message.data[0] << 8;
			Pitch_raw_value |= (uint32_t)Message.data[1];
			Pitch_value = process_numeric_value(Pitch_raw_value, 0xFFF0, false, 0.1, -204.8);

			// Signal: Yaw
			// Start bit: 11, Length: 12, Byte Order: big
			uint32_t Yaw_raw_value = 0;
			Yaw_raw_value |= (uint32_t)Message.data[1] << 8;
			Yaw_raw_value |= (uint32_t)Message.data[2];
			Yaw_value = process_numeric_value(Yaw_raw_value, 0xFFF, false, 0.75, -153.6);

			// Signal: Roll
			// Start bit: 31, Length: 11, Byte Order: big
			uint32_t Roll_raw_value = 0;
			Roll_raw_value |= (uint32_t)Message.data[3] << 8;
			Roll_raw_value |= (uint32_t)Message.data[4];
			Roll_value = process_numeric_value(Roll_raw_value, 0xFFE0, false, 0.1, -102.4);

			// Signal: TPS_overrun
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t TPS_overrun_raw_value = 0;
			TPS_overrun_raw_value |= (uint32_t)Message.data[6];
			TPS_overrun_value = process_numeric_value(TPS_overrun_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x286) {
			// Signal: something_tq_related
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t something_tq_related_raw_value = 0;
			something_tq_related_raw_value |= (uint32_t)Message.data[0];
			something_tq_related_value = process_numeric_value(something_tq_related_raw_value, 0xFF, false, 1, 0);

			// Signal: odd_tps_or_speed_0x286B2
			// Start bit: 13, Length: 7, Byte Order: big
			uint32_t odd_tps_or_speed_0x286B2_raw_value = 0;
			odd_tps_or_speed_0x286B2_raw_value |= (uint32_t)Message.data[1] << 8;
			odd_tps_or_speed_0x286B2_raw_value |= (uint32_t)Message.data[2];
			odd_tps_or_speed_0x286B2_value = process_numeric_value(odd_tps_or_speed_0x286B2_raw_value, 0x3F80, false, 1, 0);

			// Signal: odd_tps_or_speed_0x286B3
			// Start bit: 22, Length: 7, Byte Order: big
			uint32_t odd_tps_or_speed_0x286B3_raw_value = 0;
			odd_tps_or_speed_0x286B3_raw_value |= (uint32_t)Message.data[2];
			odd_tps_or_speed_0x286B3_value = process_numeric_value(odd_tps_or_speed_0x286B3_raw_value, 0x7F, false, 1, 0);

			// Signal: odd_tps_or_speed_0x286B4
			// Start bit: 31, Length: 7, Byte Order: big
			uint32_t odd_tps_or_speed_0x286B4_raw_value = 0;
			odd_tps_or_speed_0x286B4_raw_value |= (uint32_t)Message.data[3];
			odd_tps_or_speed_0x286B4_value = process_numeric_value(odd_tps_or_speed_0x286B4_raw_value, 0xFE, false, 1, 0);

			// Signal: unknown0x286_B5
			// Start bit: 24, Length: 7, Byte Order: big
			uint32_t unknown0x286_B5_raw_value = 0;
			unknown0x286_B5_raw_value |= (uint32_t)Message.data[3] << 8;
			unknown0x286_B5_raw_value |= (uint32_t)Message.data[4];
			unknown0x286_B5_value = process_numeric_value(unknown0x286_B5_raw_value, 0x1FC, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x285) {
			// Signal: WS_3
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t WS_3_raw_value = 0;
			WS_3_raw_value |= (uint32_t)Message.data[0] << 8;
			WS_3_raw_value |= (uint32_t)Message.data[1];
			WS_3_value = process_numeric_value(WS_3_raw_value, 0xFFFF, false, 0.0041, 0);

			// Signal: WS_4
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t WS_4_raw_value = 0;
			WS_4_raw_value |= (uint32_t)Message.data[2] << 8;
			WS_4_raw_value |= (uint32_t)Message.data[3];
			WS_4_value = process_numeric_value(WS_4_raw_value, 0xFFFF, false, 0.0041, 0);

			// Signal: Vehicle_Speed_or_ws
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t Vehicle_Speed_or_ws_raw_value = 0;
			Vehicle_Speed_or_ws_raw_value |= (uint32_t)Message.data[4];
			Vehicle_Speed_or_ws_value = process_numeric_value(Vehicle_Speed_or_ws_raw_value, 0xFF, false, 1, 0);

			// Signal: Counter_0x285
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t Counter_0x285_raw_value = 0;
			Counter_0x285_raw_value |= (uint32_t)Message.data[6];
			Counter_0x285_value = process_numeric_value(Counter_0x285_raw_value, 0xFF, false, 1, 0);

			// Signal: Odd_Signal_0x285B8
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t Odd_Signal_0x285B8_raw_value = 0;
			Odd_Signal_0x285B8_raw_value |= (uint32_t)Message.data[7];
			Odd_Signal_0x285B8_value = process_numeric_value(Odd_Signal_0x285B8_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x284) {
			// Signal: WS_1
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t WS_1_raw_value = 0;
			WS_1_raw_value |= (uint32_t)Message.data[0] << 8;
			WS_1_raw_value |= (uint32_t)Message.data[1];
			WS_1_value = process_numeric_value(WS_1_raw_value, 0xFFFF, false, 0.0041, 0);

			// Signal: WS_2
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t WS_2_raw_value = 0;
			WS_2_raw_value |= (uint32_t)Message.data[2] << 8;
			WS_2_raw_value |= (uint32_t)Message.data[3];
			WS_2_value = process_numeric_value(WS_2_raw_value, 0xFFFF, false, 0.0041, 0);

			// Signal: WS_related
			// Start bit: 39, Length: 16, Byte Order: big
			uint32_t WS_related_raw_value = 0;
			WS_related_raw_value |= (uint32_t)Message.data[4] << 8;
			WS_related_raw_value |= (uint32_t)Message.data[5];
			WS_related_value = process_numeric_value(WS_related_raw_value, 0xFFFF, false, 1, 0);

			// Signal: Counter_0x284
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t Counter_0x284_raw_value = 0;
			Counter_0x284_raw_value |= (uint32_t)Message.data[6];
			Counter_0x284_value = process_numeric_value(Counter_0x284_raw_value, 0xFF, false, 1, 0);

			// Signal: Odd_Signal_0x284B8
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t Odd_Signal_0x284B8_raw_value = 0;
			Odd_Signal_0x284B8_raw_value |= (uint32_t)Message.data[7];
			Odd_Signal_0x284B8_value = process_numeric_value(Odd_Signal_0x284B8_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x280) {
			// Signal: Doorlock_engagements
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t Doorlock_engagements_raw_value = 0;
			Doorlock_engagements_raw_value |= (uint32_t)Message.data[0];
			Doorlock_engagements_value = process_numeric_value(Doorlock_engagements_raw_value, 0xFF, false, 1, 0);

			// Signal: VSS_Based_1
			// Start bit: 37, Length: 14, Byte Order: big
			uint32_t VSS_Based_1_raw_value = 0;
			VSS_Based_1_raw_value |= (uint32_t)Message.data[4] << 8;
			VSS_Based_1_raw_value |= (uint32_t)Message.data[5];
			VSS_Based_1_value = process_numeric_value(VSS_Based_1_raw_value, 0x3FFF, false, 1, 0);

			// Signal: TQ_Converter_Pres
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t TQ_Converter_Pres_raw_value = 0;
			TQ_Converter_Pres_raw_value |= (uint32_t)Message.data[6];
			TQ_Converter_Pres_value = process_numeric_value(TQ_Converter_Pres_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x245) {
			// Signal: Traction_Control_Disable_Bit_1
			// Start bit: 24, Length: 1, Byte Order: big
			uint32_t Traction_Control_Disable_Bit_1_raw_value = 0;
			Traction_Control_Disable_Bit_1_raw_value |= (uint32_t)Message.data[3];
			Traction_Control_Disable_Bit_1_value = process_numeric_value(Traction_Control_Disable_Bit_1_raw_value, 0x1, false, 1, 0);

			// Signal: Counter_0x245
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t Counter_0x245_raw_value = 0;
			Counter_0x245_raw_value |= (uint32_t)Message.data[4];
			Counter_0x245_value = process_numeric_value(Counter_0x245_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x239) {
			// Signal: Accel_Pedal
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t Accel_Pedal_raw_value = 0;
			Accel_Pedal_raw_value |= (uint32_t)Message.data[0];
			Accel_Pedal_value = process_numeric_value(Accel_Pedal_raw_value, 0xFF, false, 0.39215686275, 0);

			// Signal: TPS_Inverted
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t TPS_Inverted_raw_value = 0;
			TPS_Inverted_raw_value |= (uint32_t)Message.data[1];
			TPS_Inverted_value = process_numeric_value(TPS_Inverted_raw_value, 0xFF, false, 0.39215686275, 0);

			// Signal: Cruise_Enabled
			// Start bit: 22, Length: 1, Byte Order: big
			uint32_t Cruise_Enabled_raw_value = 0;
			Cruise_Enabled_raw_value |= (uint32_t)Message.data[2];
			Cruise_Enabled_value = process_numeric_value(Cruise_Enabled_raw_value, 0x40, false, 1, 0);

			// Signal: Cruise_Button_Pressed
			// Start bit: 31, Length: 1, Byte Order: big
			uint32_t Cruise_Button_Pressed_raw_value = 0;
			Cruise_Button_Pressed_raw_value |= (uint32_t)Message.data[3];
			Cruise_Button_Pressed_value = process_numeric_value(Cruise_Button_Pressed_raw_value, 0x80, false, 1, 0);

			// Signal: cruise_cancel_pressed
			// Start bit: 30, Length: 1, Byte Order: big
			uint32_t cruise_cancel_pressed_raw_value = 0;
			cruise_cancel_pressed_raw_value |= (uint32_t)Message.data[3];
			cruise_cancel_pressed_value = process_numeric_value(cruise_cancel_pressed_raw_value, 0x40, false, 1, 0);

			// Signal: DCA_Distance_Pressed
			// Start bit: 29, Length: 1, Byte Order: big
			uint32_t DCA_Distance_Pressed_raw_value = 0;
			DCA_Distance_Pressed_raw_value |= (uint32_t)Message.data[3];
			DCA_Distance_Pressed_value = process_numeric_value(DCA_Distance_Pressed_raw_value, 0x20, false, 1, 0);

			// Signal: Cruise_Decel_Set
			// Start bit: 28, Length: 1, Byte Order: big
			uint32_t Cruise_Decel_Set_raw_value = 0;
			Cruise_Decel_Set_raw_value |= (uint32_t)Message.data[3];
			Cruise_Decel_Set_value = process_numeric_value(Cruise_Decel_Set_raw_value, 0x10, false, 1, 0);

			// Signal: Cruise_Accel_Res
			// Start bit: 27, Length: 1, Byte Order: big
			uint32_t Cruise_Accel_Res_raw_value = 0;
			Cruise_Accel_Res_raw_value |= (uint32_t)Message.data[3];
			Cruise_Accel_Res_value = process_numeric_value(Cruise_Accel_Res_raw_value, 0x8, false, 1, 0);

			// Signal: no_steering_buttons_pressed
			// Start bit: 26, Length: 1, Byte Order: big
			uint32_t no_steering_buttons_pressed_raw_value = 0;
			no_steering_buttons_pressed_raw_value |= (uint32_t)Message.data[3];
			no_steering_buttons_pressed_value = process_numeric_value(no_steering_buttons_pressed_raw_value, 0x4, false, 1, 0);

			// Signal: DCA_Pressed
			// Start bit: 25, Length: 1, Byte Order: big
			uint32_t DCA_Pressed_raw_value = 0;
			DCA_Pressed_raw_value |= (uint32_t)Message.data[3];
			DCA_Pressed_value = process_numeric_value(DCA_Pressed_raw_value, 0x2, false, 1, 0);

			// Signal: brake_pedal_depressed
			// Start bit: 33, Length: 1, Byte Order: big
			uint32_t brake_pedal_depressed_raw_value = 0;
			brake_pedal_depressed_raw_value |= (uint32_t)Message.data[4];
			brake_pedal_depressed_value = process_numeric_value(brake_pedal_depressed_raw_value, 0x2, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x1f9) {
			// Signal: Engine_Speed
			// Start bit: 23, Length: 13, Byte Order: big
			uint32_t Engine_Speed_raw_value = 0;
			Engine_Speed_raw_value |= (uint32_t)Message.data[2] << 8;
			Engine_Speed_raw_value |= (uint32_t)Message.data[3];
			Engine_Speed_value = process_numeric_value(Engine_Speed_raw_value, 0xFFF8, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x180) {
			// Signal: yaw_related
			// Start bit: 6, Length: 10, Byte Order: big
			uint32_t yaw_related_raw_value = 0;
			yaw_related_raw_value |= (uint32_t)Message.data[0] << 8;
			yaw_related_raw_value |= (uint32_t)Message.data[1];
			yaw_related_value = process_numeric_value(yaw_related_raw_value, 0x7FE0, false, 1, 0);

			// Signal: TPS_Based
			// Start bit: 23, Length: 12, Byte Order: big
			uint32_t TPS_Based_raw_value = 0;
			TPS_Based_raw_value |= (uint32_t)Message.data[2] << 8;
			TPS_Based_raw_value |= (uint32_t)Message.data[3];
			TPS_Based_value = process_numeric_value(TPS_Based_raw_value, 0xFFF0, false, 1, 0);

			// Signal: TPS_Based_1
			// Start bit: 27, Length: 12, Byte Order: big
			uint32_t TPS_Based_1_raw_value = 0;
			TPS_Based_1_raw_value |= (uint32_t)Message.data[3] << 8;
			TPS_Based_1_raw_value |= (uint32_t)Message.data[4];
			TPS_Based_1_value = process_numeric_value(TPS_Based_1_raw_value, 0xFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x177) {
			// Signal: Gear_Bit
			// Start bit: 19, Length: 1, Byte Order: big
			uint32_t Gear_Bit_raw_value = 0;
			Gear_Bit_raw_value |= (uint32_t)Message.data[2];
			Gear_Bit_value = process_numeric_value(Gear_Bit_raw_value, 0x8, false, 1, 0);

			// Signal: Gear
			// Start bit: 18, Length: 3, Byte Order: big
			uint32_t Gear_raw_value = 0;
			Gear_raw_value |= (uint32_t)Message.data[2];
			Gear_value = process_numeric_value(Gear_raw_value, 0x7, false, 1, 1);

			// Signal: unknown_Gear0x177
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t unknown_Gear0x177_raw_value = 0;
			unknown_Gear0x177_raw_value |= (uint32_t)Message.data[4];
			unknown_Gear0x177_value = process_numeric_value(unknown_Gear0x177_raw_value, 0xFF, false, 1, 0);

			// Signal: shifttiming_retard_maybe
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t shifttiming_retard_maybe_raw_value = 0;
			shifttiming_retard_maybe_raw_value |= (uint32_t)Message.data[7];
			shifttiming_retard_maybe_value = process_numeric_value(shifttiming_retard_maybe_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x176) {
			// Signal: unknown0x176_B12
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t unknown0x176_B12_raw_value = 0;
			unknown0x176_B12_raw_value |= (uint32_t)Message.data[0] << 8;
			unknown0x176_B12_raw_value |= (uint32_t)Message.data[1];
			unknown0x176_B12_value = process_numeric_value(unknown0x176_B12_raw_value, 0xFFFF, false, 1, 0);

			// Signal: unknown0x176_B34
			// Start bit: 19, Length: 12, Byte Order: big
			uint32_t unknown0x176_B34_raw_value = 0;
			unknown0x176_B34_raw_value |= (uint32_t)Message.data[2] << 8;
			unknown0x176_B34_raw_value |= (uint32_t)Message.data[3];
			unknown0x176_B34_value = process_numeric_value(unknown0x176_B34_raw_value, 0xFFF, false, 1, 0);

			// Signal: unknown0x176_B7
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t unknown0x176_B7_raw_value = 0;
			unknown0x176_B7_raw_value |= (uint32_t)Message.data[6];
			unknown0x176_B7_value = process_numeric_value(unknown0x176_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x174) {
			// Signal: shift_tq_reduction
			// Start bit: 7, Length: 12, Byte Order: big
			uint32_t shift_tq_reduction_raw_value = 0;
			shift_tq_reduction_raw_value |= (uint32_t)Message.data[0] << 8;
			shift_tq_reduction_raw_value |= (uint32_t)Message.data[1];
			shift_tq_reduction_value = process_numeric_value(shift_tq_reduction_raw_value, 0xFFF0, false, 1, 0);

			// Signal: trans_related2
			// Start bit: 11, Length: 12, Byte Order: big
			uint32_t trans_related2_raw_value = 0;
			trans_related2_raw_value |= (uint32_t)Message.data[1] << 8;
			trans_related2_raw_value |= (uint32_t)Message.data[2];
			trans_related2_value = process_numeric_value(trans_related2_raw_value, 0xFFF, false, 1, 0);

			// Signal: timer_0x174
			// Start bit: 35, Length: 4, Byte Order: big
			uint32_t timer_0x174_raw_value = 0;
			timer_0x174_raw_value |= (uint32_t)Message.data[4];
			timer_0x174_value = process_numeric_value(timer_0x174_raw_value, 0xF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x160) {
			// Signal: throttle_related
			// Start bit: 7, Length: 12, Byte Order: big
			uint32_t throttle_related_raw_value = 0;
			throttle_related_raw_value |= (uint32_t)Message.data[0] << 8;
			throttle_related_raw_value |= (uint32_t)Message.data[1];
			throttle_related_value = process_numeric_value(throttle_related_raw_value, 0xFFF0, false, 1, 0);

			// Signal: unknown0x160_B23
			// Start bit: 11, Length: 12, Byte Order: big
			uint32_t unknown0x160_B23_raw_value = 0;
			unknown0x160_B23_raw_value |= (uint32_t)Message.data[1] << 8;
			unknown0x160_B23_raw_value |= (uint32_t)Message.data[2];
			unknown0x160_B23_value = process_numeric_value(unknown0x160_B23_raw_value, 0xFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x2) {
			// Signal: Steering_Wheel
			// Start bit: 0, Length: 16, Byte Order: little
			uint32_t Steering_Wheel_raw_value = 0;
			Steering_Wheel_raw_value |= (uint32_t)Message.data[1] << 8;
			Steering_Wheel_raw_value |= (uint32_t)Message.data[0];
			Steering_Wheel_value = process_numeric_value(Steering_Wheel_raw_value, 0xFFFF, true, 0.1, 0);

			// Signal: Steering_Angle_ROC
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t Steering_Angle_ROC_raw_value = 0;
			Steering_Angle_ROC_raw_value |= (uint32_t)Message.data[2];
			Steering_Angle_ROC_value = process_numeric_value(Steering_Angle_ROC_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x7e8) {
			// Signal: Frame_Type
			// Start bit: 7, Length: 4, Byte Order: big
			uint32_t Frame_Type_raw_value = 0;
			Frame_Type_raw_value |= (uint32_t)Message.data[0];
			Frame_Type_value = process_numeric_value(Frame_Type_raw_value, 0xF0, false, 1, 0);

			// Signal: Service_ID
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t Service_ID_raw_value = 0;
			Service_ID_raw_value |= (uint32_t)Message.data[1];
			Service_ID_value = process_numeric_value(Service_ID_raw_value, 0xFF, false, 1, 0);

			// Signal: Mode22_DID
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t Mode22_DID_raw_value = 0;
			Mode22_DID_raw_value |= (uint32_t)Message.data[2] << 8;
			Mode22_DID_raw_value |= (uint32_t)Message.data[3];
			Mode22_DID_value = process_numeric_value(Mode22_DID_raw_value, 0xFFFF, false, 1, 0);

			if (Frame_Type_value == 0) {
				// Signal: Single_Frame_length
				// Start bit: 3, Length: 4, Byte Order: big
				uint32_t Single_Frame_length_raw_value = 0;
				Single_Frame_length_raw_value |= (uint32_t)Message.data[0];
				Single_Frame_length_value = process_numeric_value(Single_Frame_length_raw_value, 0xF, false, 1, 0);
			}

			if (Mode22_DID_value == 4702) {
				// Signal: VVEL_Timing_B2_unscaled
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t VVEL_Timing_B2_unscaled_raw_value = 0;
				VVEL_Timing_B2_unscaled_raw_value |= (uint32_t)Message.data[4] << 8;
				VVEL_Timing_B2_unscaled_raw_value |= (uint32_t)Message.data[5];
				VVEL_Timing_B2_unscaled_value = process_numeric_value(VVEL_Timing_B2_unscaled_raw_value, 0xFFFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4701) {
				// Signal: VVEL_Timing_B1_unscaled
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t VVEL_Timing_B1_unscaled_raw_value = 0;
				VVEL_Timing_B1_unscaled_raw_value |= (uint32_t)Message.data[4] << 8;
				VVEL_Timing_B1_unscaled_raw_value |= (uint32_t)Message.data[5];
				VVEL_Timing_B1_unscaled_value = process_numeric_value(VVEL_Timing_B1_unscaled_raw_value, 0xFFFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4699) {
				// Signal: VVEL_Sensor_B2
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t VVEL_Sensor_B2_raw_value = 0;
				VVEL_Sensor_B2_raw_value |= (uint32_t)Message.data[4] << 8;
				VVEL_Sensor_B2_raw_value |= (uint32_t)Message.data[5];
				VVEL_Sensor_B2_value = process_numeric_value(VVEL_Sensor_B2_raw_value, 0xFFFF, false, 0.01, -0.06);
			}

			if (Mode22_DID_value == 4698) {
				// Signal: VVEL_Sensor_B1
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t VVEL_Sensor_B1_raw_value = 0;
				VVEL_Sensor_B1_raw_value |= (uint32_t)Message.data[4] << 8;
				VVEL_Sensor_B1_raw_value |= (uint32_t)Message.data[5];
				VVEL_Sensor_B1_value = process_numeric_value(VVEL_Sensor_B1_raw_value, 0xFFFF, false, 0.01, -0.06);
			}

			if (Mode22_DID_value == 4656) {
				// Signal: VTC_Exh_B2_Duty_Cycle
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t VTC_Exh_B2_Duty_Cycle_raw_value = 0;
				VTC_Exh_B2_Duty_Cycle_raw_value |= (uint32_t)Message.data[4] << 8;
				VTC_Exh_B2_Duty_Cycle_raw_value |= (uint32_t)Message.data[5];
				VTC_Exh_B2_Duty_Cycle_value = process_numeric_value(VTC_Exh_B2_Duty_Cycle_raw_value, 0xFFFF, false, 0.1, 0);
			}

			if (Mode22_DID_value == 4655) {
				// Signal: VTC_Exh_B1_Duty_Cycle
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t VTC_Exh_B1_Duty_Cycle_raw_value = 0;
				VTC_Exh_B1_Duty_Cycle_raw_value |= (uint32_t)Message.data[4] << 8;
				VTC_Exh_B1_Duty_Cycle_raw_value |= (uint32_t)Message.data[5];
				VTC_Exh_B1_Duty_Cycle_value = process_numeric_value(VTC_Exh_B1_Duty_Cycle_raw_value, 0xFFFF, false, 0.1, 0);
			}

			if (Mode22_DID_value == 4634) {
				// Signal: Vehicle_Speed
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Vehicle_Speed_raw_value = 0;
				Vehicle_Speed_raw_value |= (uint32_t)Message.data[4] << 8;
				Vehicle_Speed_raw_value |= (uint32_t)Message.data[5];
				Vehicle_Speed_value = process_numeric_value(Vehicle_Speed_raw_value, 0xFFFF, false, 0.1, 0);
			}

			if (Mode22_DID_value == 4624) {
				// Signal: Throttle_Pos_S1_B2
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Throttle_Pos_S1_B2_raw_value = 0;
				Throttle_Pos_S1_B2_raw_value |= (uint32_t)Message.data[4] << 8;
				Throttle_Pos_S1_B2_raw_value |= (uint32_t)Message.data[5];
				Throttle_Pos_S1_B2_value = process_numeric_value(Throttle_Pos_S1_B2_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4623) {
				// Signal: Throttle_Pos_S1_B1
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Throttle_Pos_S1_B1_raw_value = 0;
				Throttle_Pos_S1_B1_raw_value |= (uint32_t)Message.data[4] << 8;
				Throttle_Pos_S1_B1_raw_value |= (uint32_t)Message.data[5];
				Throttle_Pos_S1_B1_value = process_numeric_value(Throttle_Pos_S1_B1_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4368) {
				// Signal: EVAP_Purge_Control_Valve_DC
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t EVAP_Purge_Control_Valve_DC_raw_value = 0;
				EVAP_Purge_Control_Valve_DC_raw_value |= (uint32_t)Message.data[4];
				EVAP_Purge_Control_Valve_DC_value = process_numeric_value(EVAP_Purge_Control_Valve_DC_raw_value, 0xFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4617) {
				// Signal: MAF
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t MAF_raw_value = 0;
				MAF_raw_value |= (uint32_t)Message.data[4] << 8;
				MAF_raw_value |= (uint32_t)Message.data[5];
				MAF_value = process_numeric_value(MAF_raw_value, 0xFFFF, false, 0.01, 0);
			}

			if (Mode22_DID_value == 4612) {
				// Signal: MAF_Sensor
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t MAF_Sensor_raw_value = 0;
				MAF_Sensor_raw_value |= (uint32_t)Message.data[4] << 8;
				MAF_Sensor_raw_value |= (uint32_t)Message.data[5];
				MAF_Sensor_value = process_numeric_value(MAF_Sensor_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4686) {
				// Signal: Intake_Valve_Timing_B2
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Intake_Valve_Timing_B2_raw_value = 0;
				Intake_Valve_Timing_B2_raw_value |= (uint32_t)Message.data[4] << 8;
				Intake_Valve_Timing_B2_raw_value |= (uint32_t)Message.data[5];
				Intake_Valve_Timing_B2_value = process_numeric_value(Intake_Valve_Timing_B2_raw_value, 0xFFFF, false, 0.5, -16384);
			}

			if (Mode22_DID_value == 4408) {
				// Signal: Intake_Valve_Solenoid_B1_Duty
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Intake_Valve_Solenoid_B1_Duty_raw_value = 0;
				Intake_Valve_Solenoid_B1_Duty_raw_value |= (uint32_t)Message.data[4];
				Intake_Valve_Solenoid_B1_Duty_value = process_numeric_value(Intake_Valve_Solenoid_B1_Duty_raw_value, 0xFF, false, 0.39215686275, 0);
			}

			if (Mode22_DID_value == 4358) {
				// Signal: Intake_Air_Temp
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Intake_Air_Temp_raw_value = 0;
				Intake_Air_Temp_raw_value |= (uint32_t)Message.data[4];
				Intake_Air_Temp_value = process_numeric_value(Intake_Air_Temp_raw_value, 0xFF, false, 1, -50);
			}

			if (Mode22_DID_value == 4361) {
				// Signal: Ingition_Timing
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Ingition_Timing_raw_value = 0;
				Ingition_Timing_raw_value |= (uint32_t)Message.data[4];
				Ingition_Timing_value = process_numeric_value(Ingition_Timing_raw_value, 0xFF, false, -1, 80);
			}

			if (Mode22_DID_value == 4633) {
				// Signal: IP_Pulley_Speed
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t IP_Pulley_Speed_raw_value = 0;
				IP_Pulley_Speed_raw_value |= (uint32_t)Message.data[4] << 8;
				IP_Pulley_Speed_raw_value |= (uint32_t)Message.data[5];
				IP_Pulley_Speed_value = process_numeric_value(IP_Pulley_Speed_raw_value, 0xFFFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4379) {
				// Signal: Ho2_S2_B2
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Ho2_S2_B2_raw_value = 0;
				Ho2_S2_B2_raw_value |= (uint32_t)Message.data[4];
				Ho2_S2_B2_value = process_numeric_value(Ho2_S2_B2_raw_value, 0xFF, false, 0.01, 0);
			}

			if (Mode22_DID_value == 4378) {
				// Signal: Ho2_S2_B1
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Ho2_S2_B1_raw_value = 0;
				Ho2_S2_B1_raw_value |= (uint32_t)Message.data[4];
				Ho2_S2_B1_value = process_numeric_value(Ho2_S2_B1_raw_value, 0xFF, false, 0.01, 0);
			}

			if (Mode22_DID_value == 4685) {
				// Signal: Intake_Valve_Timing_B1
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Intake_Valve_Timing_B1_raw_value = 0;
				Intake_Valve_Timing_B1_raw_value |= (uint32_t)Message.data[4] << 8;
				Intake_Valve_Timing_B1_raw_value |= (uint32_t)Message.data[5];
				Intake_Valve_Timing_B1_value = process_numeric_value(Intake_Valve_Timing_B1_raw_value, 0xFFFF, false, 0.5, -16384);
			}

			if (Mode22_DID_value == 4714) {
				// Signal: Hi_pres_Fuel_Pump
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Hi_pres_Fuel_Pump_raw_value = 0;
				Hi_pres_Fuel_Pump_raw_value |= (uint32_t)Message.data[4] << 8;
				Hi_pres_Fuel_Pump_raw_value |= (uint32_t)Message.data[5];
				Hi_pres_Fuel_Pump_value = process_numeric_value(Hi_pres_Fuel_Pump_raw_value, 0xFFFF, false, 0.1, 0);
			}

			if (Mode22_DID_value == 4369) {
				// Signal: Fuel_Temp
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Fuel_Temp_raw_value = 0;
				Fuel_Temp_raw_value |= (uint32_t)Message.data[4];
				Fuel_Temp_value = process_numeric_value(Fuel_Temp_raw_value, 0xFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4872) {
				// Signal: Fuel_Pump_Relay
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Fuel_Pump_Relay_raw_value = 0;
				Fuel_Pump_Relay_raw_value |= (uint32_t)Message.data[4] << 8;
				Fuel_Pump_Relay_raw_value |= (uint32_t)Message.data[5];
				Fuel_Pump_Relay_value = process_numeric_value(Fuel_Pump_Relay_raw_value, 0xFFFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4479) {
				// Signal: Fuel_Pump_Duty_Cycle
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Fuel_Pump_Duty_Cycle_raw_value = 0;
				Fuel_Pump_Duty_Cycle_raw_value |= (uint32_t)Message.data[4];
				Fuel_Pump_Duty_Cycle_value = process_numeric_value(Fuel_Pump_Duty_Cycle_raw_value, 0xFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4727) {
				// Signal: Fuel_Pressure_Sensor
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Fuel_Pressure_Sensor_raw_value = 0;
				Fuel_Pressure_Sensor_raw_value |= (uint32_t)Message.data[4] << 8;
				Fuel_Pressure_Sensor_raw_value |= (uint32_t)Message.data[5];
				Fuel_Pressure_Sensor_value = process_numeric_value(Fuel_Pressure_Sensor_raw_value, 0xFFFF, false, 5, 0);
			}

			if (Mode22_DID_value == 4620) {
				// Signal: Fuel_Pressure
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Fuel_Pressure_raw_value = 0;
				Fuel_Pressure_raw_value |= (uint32_t)Message.data[4] << 8;
				Fuel_Pressure_raw_value |= (uint32_t)Message.data[5];
				Fuel_Pressure_value = process_numeric_value(Fuel_Pressure_raw_value, 0xFFFF, false, 0.33333333333, 0);
			}

			if (Mode22_DID_value == 4372) {
				// Signal: Fuel_Level_Sensor
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Fuel_Level_Sensor_raw_value = 0;
				Fuel_Level_Sensor_raw_value |= (uint32_t)Message.data[4];
				Fuel_Level_Sensor_value = process_numeric_value(Fuel_Level_Sensor_raw_value, 0xFF, false, 0.04, 0);
			}

			if (Mode22_DID_value == 4626) {
				// Signal: Fuel_Injector_Pulse_Width_B2
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Fuel_Injector_Pulse_Width_B2_raw_value = 0;
				Fuel_Injector_Pulse_Width_B2_raw_value |= (uint32_t)Message.data[4] << 8;
				Fuel_Injector_Pulse_Width_B2_raw_value |= (uint32_t)Message.data[5];
				Fuel_Injector_Pulse_Width_B2_value = process_numeric_value(Fuel_Injector_Pulse_Width_B2_raw_value, 0xFFFF, true, 0.01, 0.34);
			}

			if (Mode22_DID_value == 4625) {
				// Signal: Fuel_Injector_Pulse_Width_B1
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Fuel_Injector_Pulse_Width_B1_raw_value = 0;
				Fuel_Injector_Pulse_Width_B1_raw_value |= (uint32_t)Message.data[4] << 8;
				Fuel_Injector_Pulse_Width_B1_raw_value |= (uint32_t)Message.data[5];
				Fuel_Injector_Pulse_Width_B1_value = process_numeric_value(Fuel_Injector_Pulse_Width_B1_raw_value, 0xFFFF, true, 0.01, 0.34);
			}

			if (Mode22_DID_value == 4492) {
				// Signal: Fuel_Injection_Timing
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Fuel_Injection_Timing_raw_value = 0;
				Fuel_Injection_Timing_raw_value |= (uint32_t)Message.data[4];
				Fuel_Injection_Timing_value = process_numeric_value(Fuel_Injection_Timing_raw_value, 0xFF, true, 1, 26);
			}

			if (Mode22_DID_value == 4472) {
				// Signal: Fan_Duty_Cycle
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Fan_Duty_Cycle_raw_value = 0;
				Fan_Duty_Cycle_raw_value |= (uint32_t)Message.data[4];
				Fan_Duty_Cycle_value = process_numeric_value(Fan_Duty_Cycle_raw_value, 0xFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4453) {
				// Signal: EXH_Valve_Timing_B2
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t EXH_Valve_Timing_B2_raw_value = 0;
				EXH_Valve_Timing_B2_raw_value |= (uint32_t)Message.data[4];
				EXH_Valve_Timing_B2_value = process_numeric_value(EXH_Valve_Timing_B2_raw_value, 0xFF, false, 0.5, -64);
			}

			if (Mode22_DID_value == 4452) {
				// Signal: EXH_Valve_Timing_B1
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t EXH_Valve_Timing_B1_raw_value = 0;
				EXH_Valve_Timing_B1_raw_value |= (uint32_t)Message.data[4];
				EXH_Valve_Timing_B1_value = process_numeric_value(EXH_Valve_Timing_B1_raw_value, 0xFF, false, 0.5, -64);
			}

			if (Mode22_DID_value == 4373) {
				// Signal: EVAP_System_Pressure_Sensor
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t EVAP_System_Pressure_Sensor_raw_value = 0;
				EVAP_System_Pressure_Sensor_raw_value |= (uint32_t)Message.data[4];
				EVAP_System_Pressure_Sensor_value = process_numeric_value(EVAP_System_Pressure_Sensor_raw_value, 0xFF, false, 0.02, 0);
			}

			if (Mode22_DID_value == 4728) {
				// Signal: Engine_Oil_Pressure_Sensor
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Engine_Oil_Pressure_Sensor_raw_value = 0;
				Engine_Oil_Pressure_Sensor_raw_value |= (uint32_t)Message.data[4] << 8;
				Engine_Oil_Pressure_Sensor_raw_value |= (uint32_t)Message.data[5];
				Engine_Oil_Pressure_Sensor_value = process_numeric_value(Engine_Oil_Pressure_Sensor_raw_value, 0xFFFF, false, 5, 0);
			}

			if (Mode22_DID_value == 4383) {
				// Signal: Engine_Oil_Temp
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Engine_Oil_Temp_raw_value = 0;
				Engine_Oil_Temp_raw_value |= (uint32_t)Message.data[4];
				Engine_Oil_Temp_value = process_numeric_value(Engine_Oil_Temp_raw_value, 0xFF, false, 1, -50);
			}

			if (Mode22_DID_value == 4709) {
				// Signal: Cooling_Fan_Speed
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Cooling_Fan_Speed_raw_value = 0;
				Cooling_Fan_Speed_raw_value |= (uint32_t)Message.data[4] << 8;
				Cooling_Fan_Speed_raw_value |= (uint32_t)Message.data[5];
				Cooling_Fan_Speed_value = process_numeric_value(Cooling_Fan_Speed_raw_value, 0xFFFF, false, 0.0625, 0);
			}

			if (Mode22_DID_value == 4353) {
				// Signal: Engine_Coolant_Temp
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Engine_Coolant_Temp_raw_value = 0;
				Engine_Coolant_Temp_raw_value |= (uint32_t)Message.data[4];
				Engine_Coolant_Temp_value = process_numeric_value(Engine_Coolant_Temp_raw_value, 0xFF, false, 1, -50);
			}

			if (Mode22_DID_value == 4375) {
				// Signal: Calculated_Load
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Calculated_Load_raw_value = 0;
				Calculated_Load_raw_value |= (uint32_t)Message.data[4];
				Calculated_Load_value = process_numeric_value(Calculated_Load_raw_value, 0xFF, false, 0.39215686275, 0);
			}

			if (Mode22_DID_value == 4355) {
				// Signal: Battery_Voltage
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Battery_Voltage_raw_value = 0;
				Battery_Voltage_raw_value |= (uint32_t)Message.data[4];
				Battery_Voltage_value = process_numeric_value(Battery_Voltage_raw_value, 0xFF, false, 0.08, 0);
			}

			if (Mode22_DID_value == 4482) {
				// Signal: Battery_Temp_Sensor
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Battery_Temp_Sensor_raw_value = 0;
				Battery_Temp_Sensor_raw_value |= (uint32_t)Message.data[4];
				Battery_Temp_Sensor_value = process_numeric_value(Battery_Temp_Sensor_raw_value, 0xFF, false, 0.02, 0);
			}

			if (Mode22_DID_value == 4678) {
				// Signal: Battery_Current_Sensor
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Battery_Current_Sensor_raw_value = 0;
				Battery_Current_Sensor_raw_value |= (uint32_t)Message.data[4] << 8;
				Battery_Current_Sensor_raw_value |= (uint32_t)Message.data[5];
				Battery_Current_Sensor_value = process_numeric_value(Battery_Current_Sensor_raw_value, 0xFFFF, false, 5, 0);
			}

			if (Mode22_DID_value == 4616) {
				// Signal: Base_Fuel_Schedule
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Base_Fuel_Schedule_raw_value = 0;
				Base_Fuel_Schedule_raw_value |= (uint32_t)Message.data[4] << 8;
				Base_Fuel_Schedule_raw_value |= (uint32_t)Message.data[5];
				Base_Fuel_Schedule_value = process_numeric_value(Base_Fuel_Schedule_raw_value, 0xFFFF, false, 0.0005, 0);
			}

			if (Mode22_DID_value == 4475) {
				// Signal: Alternator_Duty_Cycle
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Alternator_Duty_Cycle_raw_value = 0;
				Alternator_Duty_Cycle_raw_value |= (uint32_t)Message.data[4] << 8;
				Alternator_Duty_Cycle_raw_value |= (uint32_t)Message.data[5];
				Alternator_Duty_Cycle_value = process_numeric_value(Alternator_Duty_Cycle_raw_value, 0xFFFF, false, 0.5, 0);
			}

			if (Mode22_DID_value == 4871) {
				// Signal: AC_Relay
				// Start bit: 39, Length: 1, Byte Order: big
				uint32_t AC_Relay_raw_value = 0;
				AC_Relay_raw_value |= (uint32_t)Message.data[4];
				AC_Relay_value = process_numeric_value(AC_Relay_raw_value, 0x80, false, 1, 0);
			}

			if (Mode22_DID_value == 4622) {
				// Signal: Accel_Sensor_2
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Accel_Sensor_2_raw_value = 0;
				Accel_Sensor_2_raw_value |= (uint32_t)Message.data[4] << 8;
				Accel_Sensor_2_raw_value |= (uint32_t)Message.data[5];
				Accel_Sensor_2_value = process_numeric_value(Accel_Sensor_2_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4621) {
				// Signal: Accel_Sensor_1
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Accel_Sensor_1_raw_value = 0;
				Accel_Sensor_1_raw_value |= (uint32_t)Message.data[4] << 8;
				Accel_Sensor_1_raw_value |= (uint32_t)Message.data[5];
				Accel_Sensor_1_value = process_numeric_value(Accel_Sensor_1_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4643) {
				// Signal: AC_Pressure_Sensor
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t AC_Pressure_Sensor_raw_value = 0;
				AC_Pressure_Sensor_raw_value |= (uint32_t)Message.data[4] << 8;
				AC_Pressure_Sensor_raw_value |= (uint32_t)Message.data[5];
				AC_Pressure_Sensor_value = process_numeric_value(AC_Pressure_Sensor_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4473) {
				// Signal: AC_Evap_Temp
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t AC_Evap_Temp_raw_value = 0;
				AC_Evap_Temp_raw_value |= (uint32_t)Message.data[4];
				AC_Evap_Temp_value = process_numeric_value(AC_Evap_Temp_raw_value, 0xFF, false, 0.33333333333, -30);
			}

			if (Mode22_DID_value == 4474) {
				// Signal: AC_Evap_Target
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t AC_Evap_Target_raw_value = 0;
				AC_Evap_Target_raw_value |= (uint32_t)Message.data[4];
				AC_Evap_Target_value = process_numeric_value(AC_Evap_Target_raw_value, 0xFF, false, 0.33333333333, -30);
			}

			if (Mode22_DID_value == 4646) {
				// Signal: Air_Fuel_S1_B2
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Air_Fuel_S1_B2_raw_value = 0;
				Air_Fuel_S1_B2_raw_value |= (uint32_t)Message.data[4] << 8;
				Air_Fuel_S1_B2_raw_value |= (uint32_t)Message.data[5];
				Air_Fuel_S1_B2_value = process_numeric_value(Air_Fuel_S1_B2_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4645) {
				// Signal: Air_Fuel_S1_B1
				// Start bit: 39, Length: 16, Byte Order: big
				uint32_t Air_Fuel_S1_B1_raw_value = 0;
				Air_Fuel_S1_B1_raw_value |= (uint32_t)Message.data[4] << 8;
				Air_Fuel_S1_B1_raw_value |= (uint32_t)Message.data[5];
				Air_Fuel_S1_B1_value = process_numeric_value(Air_Fuel_S1_B1_raw_value, 0xFFFF, false, 0.005, 0);
			}

			if (Mode22_DID_value == 4431) {
				// Signal: Air_Fuel_S1_Heater_B2
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Air_Fuel_S1_Heater_B2_raw_value = 0;
				Air_Fuel_S1_Heater_B2_raw_value |= (uint32_t)Message.data[4];
				Air_Fuel_S1_Heater_B2_value = process_numeric_value(Air_Fuel_S1_Heater_B2_raw_value, 0xFF, false, 0.4, 0);
			}

			if (Mode22_DID_value == 4430) {
				// Signal: Air_Fuel_S1_Heater_B1
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Air_Fuel_S1_Heater_B1_raw_value = 0;
				Air_Fuel_S1_Heater_B1_raw_value |= (uint32_t)Message.data[4];
				Air_Fuel_S1_Heater_B1_value = process_numeric_value(Air_Fuel_S1_Heater_B1_raw_value, 0xFF, false, 0.4, 0);
			}

			if (Mode22_DID_value == 4388) {
				// Signal: Air_Fuel_Alpha_B2
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Air_Fuel_Alpha_B2_raw_value = 0;
				Air_Fuel_Alpha_B2_raw_value |= (uint32_t)Message.data[4];
				Air_Fuel_Alpha_B2_value = process_numeric_value(Air_Fuel_Alpha_B2_raw_value, 0xFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4387) {
				// Signal: Air_Fuel_Alpha_B1
				// Start bit: 39, Length: 8, Byte Order: big
				uint32_t Air_Fuel_Alpha_B1_raw_value = 0;
				Air_Fuel_Alpha_B1_raw_value |= (uint32_t)Message.data[4];
				Air_Fuel_Alpha_B1_value = process_numeric_value(Air_Fuel_Alpha_B1_raw_value, 0xFF, false, 1, 0);
			}

			if (Mode22_DID_value == 4866) {
				// Signal: AC_Signal
				// Start bit: 36, Length: 1, Byte Order: big
				uint32_t AC_Signal_raw_value = 0;
				AC_Signal_raw_value |= (uint32_t)Message.data[4];
				AC_Signal_value = process_numeric_value(AC_Signal_raw_value, 0x10, false, 1, 0);
			}

			if (Mode22_DID_value == 4869) {
				// Signal: Brake_Switch
				// Start bit: 34, Length: 1, Byte Order: big
				uint32_t Brake_Switch_raw_value = 0;
				Brake_Switch_raw_value |= (uint32_t)Message.data[4];
				Brake_Switch_value = process_numeric_value(Brake_Switch_raw_value, 0x4, false, 1, 0);
			}

		}

		else if (Message.arbitration_id == 0x22a) {
			// Signal: hex22A_B01
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t hex22A_B01_raw_value = 0;
			hex22A_B01_raw_value |= (uint32_t)Message.data[0] << 8;
			hex22A_B01_raw_value |= (uint32_t)Message.data[1];
			hex22A_B01_value = process_numeric_value(hex22A_B01_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex22A_B23
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t hex22A_B23_raw_value = 0;
			hex22A_B23_raw_value |= (uint32_t)Message.data[2] << 8;
			hex22A_B23_raw_value |= (uint32_t)Message.data[3];
			hex22A_B23_value = process_numeric_value(hex22A_B23_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex22A_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex22A_B4_raw_value = 0;
			hex22A_B4_raw_value |= (uint32_t)Message.data[4];
			hex22A_B4_value = process_numeric_value(hex22A_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22A_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex22A_B5_raw_value = 0;
			hex22A_B5_raw_value |= (uint32_t)Message.data[5];
			hex22A_B5_value = process_numeric_value(hex22A_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22A_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex22A_B6_raw_value = 0;
			hex22A_B6_raw_value |= (uint32_t)Message.data[6];
			hex22A_B6_value = process_numeric_value(hex22A_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22A_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex22A_B7_raw_value = 0;
			hex22A_B7_raw_value |= (uint32_t)Message.data[7];
			hex22A_B7_value = process_numeric_value(hex22A_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x22b) {
			// Signal: hex22B_B01
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t hex22B_B01_raw_value = 0;
			hex22B_B01_raw_value |= (uint32_t)Message.data[0] << 8;
			hex22B_B01_raw_value |= (uint32_t)Message.data[1];
			hex22B_B01_value = process_numeric_value(hex22B_B01_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex22B_B23
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t hex22B_B23_raw_value = 0;
			hex22B_B23_raw_value |= (uint32_t)Message.data[2] << 8;
			hex22B_B23_raw_value |= (uint32_t)Message.data[3];
			hex22B_B23_value = process_numeric_value(hex22B_B23_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex22B_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex22B_B4_raw_value = 0;
			hex22B_B4_raw_value |= (uint32_t)Message.data[4];
			hex22B_B4_value = process_numeric_value(hex22B_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22B_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex22B_B5_raw_value = 0;
			hex22B_B5_raw_value |= (uint32_t)Message.data[5];
			hex22B_B5_value = process_numeric_value(hex22B_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22B_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex22B_B6_raw_value = 0;
			hex22B_B6_raw_value |= (uint32_t)Message.data[6];
			hex22B_B6_value = process_numeric_value(hex22B_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22B_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex22B_B7_raw_value = 0;
			hex22B_B7_raw_value |= (uint32_t)Message.data[7];
			hex22B_B7_value = process_numeric_value(hex22B_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x22c) {
			// Signal: hex22C_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex22C_B0_raw_value = 0;
			hex22C_B0_raw_value |= (uint32_t)Message.data[0];
			hex22C_B0_value = process_numeric_value(hex22C_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex22C_B1_raw_value = 0;
			hex22C_B1_raw_value |= (uint32_t)Message.data[1];
			hex22C_B1_value = process_numeric_value(hex22C_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex22C_B2_raw_value = 0;
			hex22C_B2_raw_value |= (uint32_t)Message.data[2];
			hex22C_B2_value = process_numeric_value(hex22C_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex22C_B3_raw_value = 0;
			hex22C_B3_raw_value |= (uint32_t)Message.data[3];
			hex22C_B3_value = process_numeric_value(hex22C_B3_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex22C_B4_raw_value = 0;
			hex22C_B4_raw_value |= (uint32_t)Message.data[4];
			hex22C_B4_value = process_numeric_value(hex22C_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex22C_B5_raw_value = 0;
			hex22C_B5_raw_value |= (uint32_t)Message.data[5];
			hex22C_B5_value = process_numeric_value(hex22C_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex22C_B6_raw_value = 0;
			hex22C_B6_raw_value |= (uint32_t)Message.data[6];
			hex22C_B6_value = process_numeric_value(hex22C_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22C_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex22C_B7_raw_value = 0;
			hex22C_B7_raw_value |= (uint32_t)Message.data[7];
			hex22C_B7_value = process_numeric_value(hex22C_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x22d) {
			// Signal: hex22D_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex22D_B0_raw_value = 0;
			hex22D_B0_raw_value |= (uint32_t)Message.data[0];
			hex22D_B0_value = process_numeric_value(hex22D_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22D_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex22D_B1_raw_value = 0;
			hex22D_B1_raw_value |= (uint32_t)Message.data[1];
			hex22D_B1_value = process_numeric_value(hex22D_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex22D_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex22D_B2_raw_value = 0;
			hex22D_B2_raw_value |= (uint32_t)Message.data[2];
			hex22D_B2_value = process_numeric_value(hex22D_B2_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x230) {
			// Signal: hex230_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex230_B0_raw_value = 0;
			hex230_B0_raw_value |= (uint32_t)Message.data[0];
			hex230_B0_value = process_numeric_value(hex230_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex230_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex230_B1_raw_value = 0;
			hex230_B1_raw_value |= (uint32_t)Message.data[1];
			hex230_B1_value = process_numeric_value(hex230_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex230_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex230_B2_raw_value = 0;
			hex230_B2_raw_value |= (uint32_t)Message.data[2];
			hex230_B2_value = process_numeric_value(hex230_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex230_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex230_B3_raw_value = 0;
			hex230_B3_raw_value |= (uint32_t)Message.data[3];
			hex230_B3_value = process_numeric_value(hex230_B3_raw_value, 0xFF, false, 1, 0);

			// Signal: hex230_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex230_B4_raw_value = 0;
			hex230_B4_raw_value |= (uint32_t)Message.data[4];
			hex230_B4_value = process_numeric_value(hex230_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex230_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex230_B5_raw_value = 0;
			hex230_B5_raw_value |= (uint32_t)Message.data[5];
			hex230_B5_value = process_numeric_value(hex230_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex230_B67
			// Start bit: 55, Length: 16, Byte Order: big
			uint32_t hex230_B67_raw_value = 0;
			hex230_B67_raw_value |= (uint32_t)Message.data[6] << 8;
			hex230_B67_raw_value |= (uint32_t)Message.data[7];
			hex230_B67_value = process_numeric_value(hex230_B67_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x231) {
			// Signal: hex231_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex231_B0_raw_value = 0;
			hex231_B0_raw_value |= (uint32_t)Message.data[0];
			hex231_B0_value = process_numeric_value(hex231_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex231_B12
			// Start bit: 15, Length: 16, Byte Order: big
			uint32_t hex231_B12_raw_value = 0;
			hex231_B12_raw_value |= (uint32_t)Message.data[1] << 8;
			hex231_B12_raw_value |= (uint32_t)Message.data[2];
			hex231_B12_value = process_numeric_value(hex231_B12_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x232) {
			// Signal: hex232_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex232_B0_raw_value = 0;
			hex232_B0_raw_value |= (uint32_t)Message.data[0];
			hex232_B0_value = process_numeric_value(hex232_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex232_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex232_B1_raw_value = 0;
			hex232_B1_raw_value |= (uint32_t)Message.data[1];
			hex232_B1_value = process_numeric_value(hex232_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex232_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex232_B2_raw_value = 0;
			hex232_B2_raw_value |= (uint32_t)Message.data[2];
			hex232_B2_value = process_numeric_value(hex232_B2_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x233) {
			// Signal: hex233_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex233_B0_raw_value = 0;
			hex233_B0_raw_value |= (uint32_t)Message.data[0];
			hex233_B0_value = process_numeric_value(hex233_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex233_B1_raw_value = 0;
			hex233_B1_raw_value |= (uint32_t)Message.data[1];
			hex233_B1_value = process_numeric_value(hex233_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex233_B2_raw_value = 0;
			hex233_B2_raw_value |= (uint32_t)Message.data[2];
			hex233_B2_value = process_numeric_value(hex233_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex233_B3_raw_value = 0;
			hex233_B3_raw_value |= (uint32_t)Message.data[3];
			hex233_B3_value = process_numeric_value(hex233_B3_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex233_B4_raw_value = 0;
			hex233_B4_raw_value |= (uint32_t)Message.data[4];
			hex233_B4_value = process_numeric_value(hex233_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex233_B5_raw_value = 0;
			hex233_B5_raw_value |= (uint32_t)Message.data[5];
			hex233_B5_value = process_numeric_value(hex233_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex233_B6_raw_value = 0;
			hex233_B6_raw_value |= (uint32_t)Message.data[6];
			hex233_B6_value = process_numeric_value(hex233_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex233_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex233_B7_raw_value = 0;
			hex233_B7_raw_value |= (uint32_t)Message.data[7];
			hex233_B7_value = process_numeric_value(hex233_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x234) {
			// Signal: hex234_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex234_B0_raw_value = 0;
			hex234_B0_raw_value |= (uint32_t)Message.data[0];
			hex234_B0_value = process_numeric_value(hex234_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex234_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex234_B1_raw_value = 0;
			hex234_B1_raw_value |= (uint32_t)Message.data[1];
			hex234_B1_value = process_numeric_value(hex234_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex234_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex234_B2_raw_value = 0;
			hex234_B2_raw_value |= (uint32_t)Message.data[2];
			hex234_B2_value = process_numeric_value(hex234_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex234_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex234_B3_raw_value = 0;
			hex234_B3_raw_value |= (uint32_t)Message.data[3];
			hex234_B3_value = process_numeric_value(hex234_B3_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x330) {
			// Signal: hex330_B01
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t hex330_B01_raw_value = 0;
			hex330_B01_raw_value |= (uint32_t)Message.data[0] << 8;
			hex330_B01_raw_value |= (uint32_t)Message.data[1];
			hex330_B01_value = process_numeric_value(hex330_B01_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex330_B23
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t hex330_B23_raw_value = 0;
			hex330_B23_raw_value |= (uint32_t)Message.data[2] << 8;
			hex330_B23_raw_value |= (uint32_t)Message.data[3];
			hex330_B23_value = process_numeric_value(hex330_B23_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex330_B45
			// Start bit: 39, Length: 16, Byte Order: big
			uint32_t hex330_B45_raw_value = 0;
			hex330_B45_raw_value |= (uint32_t)Message.data[4] << 8;
			hex330_B45_raw_value |= (uint32_t)Message.data[5];
			hex330_B45_value = process_numeric_value(hex330_B45_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex330_B67
			// Start bit: 55, Length: 16, Byte Order: big
			uint32_t hex330_B67_raw_value = 0;
			hex330_B67_raw_value |= (uint32_t)Message.data[6] << 8;
			hex330_B67_raw_value |= (uint32_t)Message.data[7];
			hex330_B67_value = process_numeric_value(hex330_B67_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x340) {
			// Signal: hex340_B01
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t hex340_B01_raw_value = 0;
			hex340_B01_raw_value |= (uint32_t)Message.data[0] << 8;
			hex340_B01_raw_value |= (uint32_t)Message.data[1];
			hex340_B01_value = process_numeric_value(hex340_B01_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex340_B23
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t hex340_B23_raw_value = 0;
			hex340_B23_raw_value |= (uint32_t)Message.data[2] << 8;
			hex340_B23_raw_value |= (uint32_t)Message.data[3];
			hex340_B23_value = process_numeric_value(hex340_B23_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex340_B45
			// Start bit: 39, Length: 16, Byte Order: big
			uint32_t hex340_B45_raw_value = 0;
			hex340_B45_raw_value |= (uint32_t)Message.data[4] << 8;
			hex340_B45_raw_value |= (uint32_t)Message.data[5];
			hex340_B45_value = process_numeric_value(hex340_B45_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex340_B67
			// Start bit: 55, Length: 16, Byte Order: big
			uint32_t hex340_B67_raw_value = 0;
			hex340_B67_raw_value |= (uint32_t)Message.data[6] << 8;
			hex340_B67_raw_value |= (uint32_t)Message.data[7];
			hex340_B67_value = process_numeric_value(hex340_B67_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x350) {
			// Signal: hex350_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex350_B0_raw_value = 0;
			hex350_B0_raw_value |= (uint32_t)Message.data[0];
			hex350_B0_value = process_numeric_value(hex350_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex350_B1_raw_value = 0;
			hex350_B1_raw_value |= (uint32_t)Message.data[1];
			hex350_B1_value = process_numeric_value(hex350_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex350_B2_raw_value = 0;
			hex350_B2_raw_value |= (uint32_t)Message.data[2];
			hex350_B2_value = process_numeric_value(hex350_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex350_B3_raw_value = 0;
			hex350_B3_raw_value |= (uint32_t)Message.data[3];
			hex350_B3_value = process_numeric_value(hex350_B3_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex350_B4_raw_value = 0;
			hex350_B4_raw_value |= (uint32_t)Message.data[4];
			hex350_B4_value = process_numeric_value(hex350_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex350_B5_raw_value = 0;
			hex350_B5_raw_value |= (uint32_t)Message.data[5];
			hex350_B5_value = process_numeric_value(hex350_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex350_B6_raw_value = 0;
			hex350_B6_raw_value |= (uint32_t)Message.data[6];
			hex350_B6_value = process_numeric_value(hex350_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex350_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex350_B7_raw_value = 0;
			hex350_B7_raw_value |= (uint32_t)Message.data[7];
			hex350_B7_value = process_numeric_value(hex350_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x360) {
			// Signal: hex360_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex360_B0_raw_value = 0;
			hex360_B0_raw_value |= (uint32_t)Message.data[0];
			hex360_B0_value = process_numeric_value(hex360_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex360_B1_raw_value = 0;
			hex360_B1_raw_value |= (uint32_t)Message.data[1];
			hex360_B1_value = process_numeric_value(hex360_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex360_B2_raw_value = 0;
			hex360_B2_raw_value |= (uint32_t)Message.data[2];
			hex360_B2_value = process_numeric_value(hex360_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex360_B3_raw_value = 0;
			hex360_B3_raw_value |= (uint32_t)Message.data[3];
			hex360_B3_value = process_numeric_value(hex360_B3_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex360_B4_raw_value = 0;
			hex360_B4_raw_value |= (uint32_t)Message.data[4];
			hex360_B4_value = process_numeric_value(hex360_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex360_B5_raw_value = 0;
			hex360_B5_raw_value |= (uint32_t)Message.data[5];
			hex360_B5_value = process_numeric_value(hex360_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex360_B6_raw_value = 0;
			hex360_B6_raw_value |= (uint32_t)Message.data[6];
			hex360_B6_value = process_numeric_value(hex360_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex360_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex360_B7_raw_value = 0;
			hex360_B7_raw_value |= (uint32_t)Message.data[7];
			hex360_B7_value = process_numeric_value(hex360_B7_raw_value, 0xFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x370) {
			// Signal: hex370_B01
			// Start bit: 7, Length: 16, Byte Order: big
			uint32_t hex370_B01_raw_value = 0;
			hex370_B01_raw_value |= (uint32_t)Message.data[0] << 8;
			hex370_B01_raw_value |= (uint32_t)Message.data[1];
			hex370_B01_value = process_numeric_value(hex370_B01_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex370_B23
			// Start bit: 23, Length: 16, Byte Order: big
			uint32_t hex370_B23_raw_value = 0;
			hex370_B23_raw_value |= (uint32_t)Message.data[2] << 8;
			hex370_B23_raw_value |= (uint32_t)Message.data[3];
			hex370_B23_value = process_numeric_value(hex370_B23_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex370_B45
			// Start bit: 39, Length: 16, Byte Order: big
			uint32_t hex370_B45_raw_value = 0;
			hex370_B45_raw_value |= (uint32_t)Message.data[4] << 8;
			hex370_B45_raw_value |= (uint32_t)Message.data[5];
			hex370_B45_value = process_numeric_value(hex370_B45_raw_value, 0xFFFF, false, 1, 0);

			// Signal: hex370_B67
			// Start bit: 55, Length: 16, Byte Order: big
			uint32_t hex370_B67_raw_value = 0;
			hex370_B67_raw_value |= (uint32_t)Message.data[6] << 8;
			hex370_B67_raw_value |= (uint32_t)Message.data[7];
			hex370_B67_value = process_numeric_value(hex370_B67_raw_value, 0xFFFF, false, 1, 0);

		}

		else if (Message.arbitration_id == 0x3ff) {
			// Signal: hex3FF_B0
			// Start bit: 7, Length: 8, Byte Order: big
			uint32_t hex3FF_B0_raw_value = 0;
			hex3FF_B0_raw_value |= (uint32_t)Message.data[0];
			hex3FF_B0_value = process_numeric_value(hex3FF_B0_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B1
			// Start bit: 15, Length: 8, Byte Order: big
			uint32_t hex3FF_B1_raw_value = 0;
			hex3FF_B1_raw_value |= (uint32_t)Message.data[1];
			hex3FF_B1_value = process_numeric_value(hex3FF_B1_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B2
			// Start bit: 23, Length: 8, Byte Order: big
			uint32_t hex3FF_B2_raw_value = 0;
			hex3FF_B2_raw_value |= (uint32_t)Message.data[2];
			hex3FF_B2_value = process_numeric_value(hex3FF_B2_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B3
			// Start bit: 31, Length: 8, Byte Order: big
			uint32_t hex3FF_B3_raw_value = 0;
			hex3FF_B3_raw_value |= (uint32_t)Message.data[3];
			hex3FF_B3_value = process_numeric_value(hex3FF_B3_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B4
			// Start bit: 39, Length: 8, Byte Order: big
			uint32_t hex3FF_B4_raw_value = 0;
			hex3FF_B4_raw_value |= (uint32_t)Message.data[4];
			hex3FF_B4_value = process_numeric_value(hex3FF_B4_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B5
			// Start bit: 47, Length: 8, Byte Order: big
			uint32_t hex3FF_B5_raw_value = 0;
			hex3FF_B5_raw_value |= (uint32_t)Message.data[5];
			hex3FF_B5_value = process_numeric_value(hex3FF_B5_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B6
			// Start bit: 55, Length: 8, Byte Order: big
			uint32_t hex3FF_B6_raw_value = 0;
			hex3FF_B6_raw_value |= (uint32_t)Message.data[6];
			hex3FF_B6_value = process_numeric_value(hex3FF_B6_raw_value, 0xFF, false, 1, 0);

			// Signal: hex3FF_B7
			// Start bit: 63, Length: 8, Byte Order: big
			uint32_t hex3FF_B7_raw_value = 0;
			hex3FF_B7_raw_value |= (uint32_t)Message.data[7];
			hex3FF_B7_value = process_numeric_value(hex3FF_B7_raw_value, 0xFF, false, 1, 0);

		}


//################ End Generated CAN Code ################

	}
	if (Message.Bus == CAN_2){
		send_message(CAN_3, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
	}
	if (Message.Bus == CAN_3){
		send_message(CAN_1, Message.is_extended_id, Message.arbitration_id, Message.dlc, Message.data);
				
	}
}

/* Run 2000Hz Functions here */
void events_2000Hz(){

}

/* Run 1000Hz Functions here */
void events_1000Hz(){
	for (uint8_t i = 0; i< 15; i++){
		char buffer1[100];
		snprintf(buffer1, 100,"(123.456789) can0 12345678#%02x34567890123456\r\n",i);
		serialPrint(buffer1);
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
