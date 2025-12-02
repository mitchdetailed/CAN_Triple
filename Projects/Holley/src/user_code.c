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
#include "stm32g4xx_hal.h"

/* End File Includes */

/* Variable Declarations */

// ################ Generated Enum Definitions ################
typedef enum
{
	STATUS_OK = 0,
	STATUS_DISABLED = 1,
	STATUS_INITIALIZING = 2,
	STATUS_HEATING = 3,
	STATUS_WBACTIVE = 4,
	STATUS_TOOCOLD = 5,
	STATUS_TOOHOT = 6,
	STATUS_UNPLUGGED = 7,
	STATUS_SLOW = 8,
	STATUS_UNCALYELLOW = 9,
	STATUS_UNCALRED = 10,
	STATUS_REPLACE = 11,
	STATUS_DISABLED_ALT = 12,
	STATUS_SHORTED = 13,
	STATUS_OPEN = 14,
	STATUS_OVERRANGE = 15,
	STATUS_UNDERRANGE = 16,
	STATUS_UNDEFINED = 17,
	STATUS_ERROR = 18,
	STATUS_LOWERROR = 19,
	STATUS_HIGHERROR = 20,
	STATUS_NONCRITICALNOLED = 21,
	STATUS_CRITICALGREENLED = 27,
	STATUS_STALL = 32,
	STATUS_SYNCHRONIZED = 33,
	STATUS_SYNCING = 34,
	STATUS_ERROR_ALT = 35,
	STATUS_ERROR_ALT2 = 36,
	STATUS_UNCALIBRATED = 37,
	STATUS_OPENLOOP = 38,
	STATUS_CLOSEDLOOP = 39,
	STATUS_NOTLEARN = 40,
	STATUS_LEARNING = 41,
	STATUS_OFF = 42,
	STATUS_ON = 43,
	STATUS_NOTREVLIMITING = 44,
	STATUS_REVLIMIT = 45,
	STATUS_NOCUTOFF = 46,
	STATUS_CUTOFF = 47,
	STATUS_OFF_ALT = 48,
	STATUS_WARNING = 49,
	STATUS_CAUTION = 50,
	STATUS_NOTIMINGMODIFIER = 51,
	STATUS_TIMINGISBEINGMODIFIED = 52,
	STATUS_TIMINGVALUEISBEINGREPLACED = 53,
	STATUS_ACQSAT = 54,
	STATUS_NOGPS = 55,
	STATUS_NODATA = 56,
	STATUS_NONCRITICALGREENLED = 22,
	STATUS_NONCRITICALYELLOWLED = 23,
	STATUS_NONCRITICALREDLED = 24,
	STATUS_NONCRITICALBLUELED = 25,
	STATUS_NONCRITICALGREYLED = 26,
	STATUS_CRITICALYELLOWLED = 28,
	STATUS_CRITICALREDLED = 29,
	STATUS_CRITICALBLUELED = 30,
	STATUS_CRITICALGREYLED = 31,
} Status_t;

// ################ Generated Variable Declarations ################
typedef struct
{
	uint8_t Status;
	Status_t Status_enum;
	float Seconds;
	float RPM;
	float FUEL_INJ_PW;
	float FUEL_DUTY_CYCLE;
	float FUEL_CLOSED_LOOP_COMP;
	float FUEL_TARGET_AFR;
	float FUEL_AFR_LEFT;
	float FUEL_AFR_RIGHT;
	float FUEL_AFR_AVERAGE;
	float FUEL_AIR_TEMP_ENRICH;
	float FUEL_COOLANT_ENRICH;
	float FUEL_COOLANT_AFR_OFFSET;
	float FUEL_AFTERSTART_ENRICH;
	float FUEL_CURRENT_LEARN_PERCENT;
	float FUEL_CLOSED_LOOP_STATUS;
	float FUEL_LEARN_STATUS;
	float FUEL_ECONOMY;
	float FUEL_FLOW;
	float FUEL_MAP_ROC;
	float FUEL_TPS_ROC;
	float TUNING_CHANGE;
	float ESTIMATED_VE;
	float SPARK_IGNITION_TIMING;
	float SPARK_KNOCK_RETARD;
	float KNOCK_LEVEL;
	int32_t PADDING;
	float IDLE_IAC_POS;
	float IDLE_TARGET_IDLE_SPEED;
	float SENSOR_MAP;
	float SENSOR_TPS;
	float SENSOR_MAT;
	float SENSOR_CTS;
	float SENSOR_BARO;
	float SENSOR_BATT_VOLT;
	float SENSOR_OIL_PRESSURE;
	float SENSOR_FUEL_PRESSURE;
	float SENSOR_PEDAL_POSITION;
	float SYSTEM_REV_LIMIT_MAIN_STATUS;
	float SYSTEM_REV_LIMIT1_STATUS;
	float SYSTEM_REV_LIMIT2_STATUS;
	float SYSTEM_AC_KICK_STATUS;
	float SYSTEM_TIMING_RETARD1;
	float SYSTEM_TIMING_RETARD2;
	float SYSTEM_TIMING_RETARD3;
	float SYSTEM_FAN1_STATUS;
	float SYSTEM_FAN2_STATUS;
	float SYSTEM_FUEL_PUMP2_STATUS;
	float SYSTEM_AC_SHUTDOWN_STATUS;
	float SYSTEM_LOCKUP_STATUS;
	float SYSTEM_SENSOR_WARNING;
	float SYSTEM_SENSOR_CAUTION;
	float SYSTEM_BASE_FUEL_LB;
	float SYSTEM_BASE_FUEL_VE;
	float SYSTEM_BASE_TIMING;
	float SYSTEM_BASE_TAFR;
	float SYSTEM_BASE_IGN_DWELL;
	float SYSTEM_VOL_COMP_IGN_DWELL;
	float SYSTEM_INJ_END_ANGLE;
	float SYSTEM_ECU_LOG_TRIGGER;
	float SYSTEM_TIMING_AIR_TEMP;
	float SYSTEM_TIMING_COOLANT_TEMP;
	float SYSTEM_STATUS1;
	float SYSTEM_STATUS2;
	float SYSTEM_STATUS3;
	float SYSTEM_STATUS4;
	float SYSTEM_STATUS5;
	float SYSTEM_STATUS6;
	float SYSTEM_STATUS7;
	float SYSTEM_STATUS8;
	float SYSTEM_INJ_PPH1;
	float SYSTEM_INJ_PPH2;
	float SYSTEM_INJ_PPH3;
	float SYSTEM_INJ_PPH4;
	float SYSTEM_INJ_PPH5;
	float SYSTEM_INJ_PPH6;
	float SYSTEM_INJ_PPH7;
	float SYSTEM_INJ_PPH8;
	float SYSTEM_INJ_PPH9;
	float SYSTEM_INJ_PPH10;
	float SYSTEM_INJ_PPH11;
	float SYSTEM_INJ_PPH12;
	float SYSTEM_INJ_PW1;
	float SYSTEM_INJ_PW2;
	float SYSTEM_INJ_PW3;
	float SYSTEM_INJ_PW4;
	float SYSTEM_INJ_PW5;
	float SYSTEM_INJ_PW6;
	float SYSTEM_INJ_PW7;
	float SYSTEM_INJ_PW8;
	float SYSTEM_INJ_PW9;
	float SYSTEM_INJ_PW10;
	float SYSTEM_INJ_PW11;
	float SYSTEM_INJ_PW12;
	float SYSTEM_CYL_FUEL_CORR1;
	float SYSTEM_CYL_FUEL_CORR2;
	float SYSTEM_CYL_FUEL_CORR3;
	float SYSTEM_CYL_FUEL_CORR4;
	float SYSTEM_CYL_FUEL_CORR5;
	float SYSTEM_CYL_FUEL_CORR6;
	float SYSTEM_CYL_FUEL_CORR7;
	float SYSTEM_CYL_FUEL_CORR8;
	float SYSTEM_CYL_FUEL_CORR9;
	float SYSTEM_CYL_FUEL_CORR10;
	float SYSTEM_CYL_FUEL_CORR11;
	float SYSTEM_CYL_FUEL_CORR12;
	float SYSTEM_CYL_FUEL_CORR13;
	float SYSTEM_CYL_FUEL_CORR14;
	float SYSTEM_CYL_FUEL_CORR15;
	float SYSTEM_CYL_FUEL_CORR16;
	float SYSTEM_CYL_TIMING_CORR1;
	float SYSTEM_CYL_TIMING_CORR2;
	float SYSTEM_CYL_TIMING_CORR3;
	float SYSTEM_CYL_TIMING_CORR4;
	float SYSTEM_CYL_TIMING_CORR5;
	float SYSTEM_CYL_TIMING_CORR6;
	float SYSTEM_CYL_TIMING_CORR7;
	float SYSTEM_CYL_TIMING_CORR8;
	float SYSTEM_CYL_TIMING_CORR9;
	float SYSTEM_CYL_TIMING_CORR10;
	float SYSTEM_CYL_TIMING_CORR11;
	float SYSTEM_CYL_TIMING_CORR12;
	float SYSTEM_CYL_TIMING_CORR13;
	float SYSTEM_CYL_TIMING_CORR14;
	float SYSTEM_CYL_TIMING_CORR15;
	float SYSTEM_CYL_TIMING_CORR16;
	float SYSTEM_TARGET_FUEL_PRESSURE;
	float SYSTEM_BOOST_PSIG;
	float BOOST_GEAR;
	float BOOST_MANUAL_STAGE;
	float BOOST_PSIG;
	float BOOST_SPEED;
	float BOOST_TIME;
	float BOOST_TARGET_BOOST;
	float BOOST_TRANS_BRAKE_STATUS;
	float BOOST_SCRAMBLE_UP_STATUS;
	float BOOST_SCRAMBLE_DOWN_STATUS;
	float BOOST_MANUAL_BUILD_STATUS;
	float BOOST_MANUAL_RESET_STATUS;
	float BOOST_BUILD_STATUS;
	float BOOST_SOLENOID_DUTY;
	float BOOST_SAFETY;
	float BOOST_MASTER_ENABLE;
	float BOOST_MANUAL_SHIFT_INPUT;
	float BOOST_MANUAL_STAGE_INPUT;
	float BOOST_FILL_SOL_DC;
	float BOOST_VENT_SOL_DC;
	float WM_INJ_VALUE;
	float WM_MANUAL_ENABLE_STATUS;
	float WM_LOW_FLUID_STATUS;
	float WM_PUMP_STATUS;
	float WM_SOL_FLOW1;
	float WM_SOL_FLOW2;
	float WM_TOTAL_FLOW;
	float WM_SOL_DC1;
	float WM_SOL_DC2;
	float NOS_STAGE1;
	float NOS_STAGE2;
	float NOS_STAGE3;
	float NOS_STAGE4;
	float NOS_STAGE5;
	float NOS_STAGE6;
	float NOS_STAGE7;
	float NOS_STAGE8;
	float NOS_GPO1;
	float NOS_GPO2;
	float NOS_GPO3;
	float NOS_GPO4;
	float NOS_GPO5;
	float NOS_GPO6;
	float NOS_GPO7;
	float NOS_GPO8;
	float NOS_ENABLED_STATUS;
	float NOS_INPUT1_STATUS;
	float NOS_INPUT2_STATUS;
	float NOS_INPUT3_STATUS;
	float NOS_INPUT4_STATUS;
	float NOS_INPUT5_STATUS;
	float NOS_INPUT6_STATUS;
	float NOS_INPUT7_STATUS;
	float NOS_INPUT8_STATUS;
	float NOS_PURGE_STATUS;
	float NOS_LEAN_CUTOFF_STATUS;
	float NOS_RICH_CUTOFF_STATUS;
	float NOS_RPM_CUTOFF_STATUS;
	float NOS_MAP_CUTOFF_STATUS;
	float NOS_PURGE_OUTPUT;
	float NOS_DRY_FUEL1;
	float NOS_DRY_FUEL2;
	float NOS_DRY_FUEL3;
	float NOS_DRY_FUEL4;
	float NOS_DRY_FUEL5;
	float NOS_DRY_FUEL6;
	float NOS_DRY_FUEL7;
	float NOS_DRY_FUEL8;
	float NOS_TIMING_MOD1;
	float NOS_TIMING_MOD2;
	float NOS_TIMING_MOD3;
	float NOS_TIMING_MOD4;
	float NOS_TIMING_MOD5;
	float NOS_TIMING_MOD6;
	float NOS_TIMING_MOD7;
	float NOS_TIMING_MOD8;
	float NOS_TIMER1;
	float NOS_TIMER2;
	float NOS_TIMER3;
	float NOS_TIMER4;
	float NOS_TIMER5;
	float NOS_TIMER6;
	float NOS_TIMER7;
	float NOS_TIMER8;
	float TRANS_GEAR;
	float TRANS_SPEED;
	float TRANS_LINE_PRESSURE_PWM;
	float TRANS_INPUT_SHAFT_SPEED;
	float TRANS_ACCUM_PRESSURE_PWM;
	float TRANS_TCC_DUTY_CYCLE;
	float TRANS_LINE_TEMP;
	float TRANS_TORQUE_TIME;
	float TRANS_MAN_US_INPUT;
	float TRANS_MAN_DS_INPUT;
	float TRANS_AUTOMAN_INPUT;
	float TRANS_RANGE_SWITCH_POSITION;
	float DBW_TB_TPS_RISING;
	float DBW_TB_TPS_FALLING;
	float DBW_PEDAL_TPS_RISING;
	float DBW_PEDAL_TPS_FALLING;
	float DBW_TB2_TPS_RISING;
	float DBW_TB2_TPS_FALLING;
	float DBW_TB_POSITION;
	float DBW_TB2_POSITION;
	float DBW_BRAKE_PEDAL;
	float DIAGNOSTIC1;
	float DIAGNOSTIC2;
	float DIAGNOSTIC3;
	float DIAGNOSTIC4;
	float DIAGNOSTIC5;
	float DIAGNOSTIC6;
	float DIAGNOSTIC7;
	float DIAGNOSTIC8;
	float DIAGNOSTIC9;
	float DIAGNOSTIC10;
	float DIAGNOSTIC11;
	float DIAGNOSTIC12;
	float DIAGNOSTIC13;
	float DIAGNOSTIC14;
	float DIAGNOSTIC15;
	float DIAGNOSTIC16;
	float DIAGNOSTIC17;
	float DIAGNOSTIC18;
	float DIAGNOSTIC19;
	float DIAGNOSTIC20;
	float ADV_LAUNCH_INPUT;
	float ADV_SHIFT_INPUT;
	float ADV_MANUAL_INPUT;
	float ADV_GEAR;
	float ADV_AT_1D1;
	float ADV_AT_1D2;
	float ADV_AT_1D3;
	float ADV_AT_1D4;
	float ADV_AT_1D5;
	float ADV_AT_1D6;
	float ADV_AT_1D7;
	float ADV_AT_1D8;
	float ADV_AT_2D1;
	float ADV_AT_2D2;
	float ADV_AT_2D3;
	float ADV_AT_2D4;
	float ADV_AT_2D5;
	float ADV_AT_2D6;
	float ADV_AT_2D7;
	float ADV_AT_2D8;
	float ADV_AT_1D_GEAR1;
	float ADV_AT_1D_GEAR2;
	float ADV_AT_1D_GEAR3;
	float ADV_AT_1D_GEAR4;
	float ADV_AT_1D_GEAR5;
	float ADV_AT_1D_GEAR6;
	float ADV_AT_1D_GEAR7;
	float ADV_AT_1D_GEAR8;
	float ADV_AT_2D_GEAR1;
	float ADV_AT_2D_GEAR2;
	float ADV_AT_2D_GEAR3;
	float ADV_AT_2D_GEAR4;
	float ADV_AT_2D_GEAR5;
	float ADV_AT_2D_GEAR6;
	float ADV_AT_2D_GEAR7;
	float ADV_AT_2D_GEAR8;
	float IO_INPUT1;
	float IO_INPUT2;
	float IO_INPUT3;
	float IO_INPUT4;
	float IO_INPUT5;
	float IO_INPUT6;
	float IO_INPUT7;
	float IO_INPUT8;
	float IO_INPUT9;
	float IO_INPUT10;
	float IO_INPUT11;
	float IO_INPUT12;
	float IO_INPUT13;
	float IO_INPUT14;
	float IO_INPUT15;
	float IO_INPUT16;
	float IO_INPUT17;
	float IO_INPUT18;
	float IO_INPUT19;
	float IO_INPUT20;
	float IO_INPUT21;
	float IO_INPUT22;
	float IO_INPUT23;
	float IO_INPUT24;
	float IO_INPUT25;
	float IO_INPUT26;
	float IO_INPUT27;
	float IO_INPUT28;
	float IO_INPUT29;
	float IO_INPUT30;
	float IO_INPUT31;
	float IO_INPUT32;
	float IO_INPUT33;
	float IO_INPUT34;
	float IO_INPUT35;
	float IO_INPUT36;
	float IO_INPUT37;
	float IO_INPUT38;
	float IO_INPUT39;
	float IO_INPUT40;
	float IO_INPUT41;
	float IO_INPUT42;
	float IO_INPUT43;
	float IO_INPUT44;
	float IO_INPUT45;
	float IO_INPUT46;
	float IO_INPUT47;
	float IO_INPUT48;
	float IO_INPUT49;
	float IO_INPUT50;
	float IO_INPUT51;
	float IO_INPUT52;
	float IO_INPUT53;
	float IO_INPUT54;
	float IO_INPUT55;
	float IO_INPUT56;
	float IO_INPUT57;
	float IO_INPUT58;
	float IO_INPUT59;
	float IO_INPUT60;
	float IO_INPUT61;
	float IO_INPUT62;
	float IO_INPUT63;
	float IO_INPUT64;
	float IO_INPUT65;
	float IO_INPUT66;
	float IO_INPUT67;
	float IO_INPUT68;
	float IO_INPUT69;
	float IO_INPUT70;
	float IO_INPUT71;
	float IO_INPUT72;
	float IO_INPUT73;
	float IO_INPUT74;
	float IO_INPUT75;
	float IO_INPUT76;
	float IO_INPUT77;
	float IO_INPUT78;
	float IO_INPUT79;
	float IO_INPUT80;
	float IO_OUTPUT1;
	float IO_OUTPUT2;
	float IO_OUTPUT3;
	float IO_OUTPUT4;
	float IO_OUTPUT5;
	float IO_OUTPUT6;
	float IO_OUTPUT7;
	float IO_OUTPUT8;
	float IO_OUTPUT9;
	float IO_OUTPUT10;
	float IO_OUTPUT11;
	float IO_OUTPUT12;
	float IO_OUTPUT13;
	float IO_OUTPUT14;
	float IO_OUTPUT15;
	float IO_OUTPUT16;
	float IO_OUTPUT17;
	float IO_OUTPUT18;
	float IO_OUTPUT19;
	float IO_OUTPUT20;
	float IO_OUTPUT21;
	float IO_OUTPUT22;
	float IO_OUTPUT23;
	float IO_OUTPUT24;
	float IO_OUTPUT25;
	float IO_OUTPUT26;
	float IO_OUTPUT27;
	float IO_OUTPUT28;
	float IO_OUTPUT29;
	float IO_OUTPUT30;
	float IO_OUTPUT31;
	float IO_OUTPUT32;
	float IO_OUTPUT33;
	float IO_OUTPUT34;
	float IO_OUTPUT35;
	float IO_OUTPUT36;
	float IO_OUTPUT37;
	float IO_OUTPUT38;
	float IO_OUTPUT39;
	float IO_OUTPUT40;
	float IO_OUTPUT41;
	float IO_OUTPUT42;
	float IO_OUTPUT43;
	float IO_OUTPUT44;
	float IO_OUTPUT45;
	float IO_OUTPUT46;
	float IO_OUTPUT47;
	float IO_OUTPUT48;
	float IO_OUTPUT49;
	float IO_OUTPUT50;
	float IO_OUTPUT51;
	float IO_OUTPUT52;
	float IO_OUTPUT53;
	float IO_OUTPUT54;
	float IO_OUTPUT55;
	float IO_OUTPUT56;
	float IO_OUTPUT57;
	float IO_OUTPUT58;
	float IO_OUTPUT59;
	float IO_OUTPUT60;
	float IO_OUTPUT61;
	float IO_OUTPUT62;
	float FUEL_TABLE1_PERCENT;
	float FUEL_TABLE2_PERCENT;
	float FUEL_TABLE3_PERCENT;
	float SYSTEM_INJ_PPH13;
	float SYSTEM_INJ_PPH14;
	float SYSTEM_INJ_PPH15;
	float SYSTEM_INJ_PPH16;
	float SYSTEM_INJ_PPH17;
	float SYSTEM_INJ_PPH18;
	float SYSTEM_INJ_PPH19;
	float SYSTEM_INJ_PPH20;
	float SYSTEM_INJ_PPH21;
	float SYSTEM_INJ_PPH22;
	float SYSTEM_INJ_PPH23;
	float SYSTEM_INJ_PPH24;
	float SYSTEM_INJ_PPH25;
	float SYSTEM_INJ_PPH26;
	float SYSTEM_INJ_PPH27;
	float SYSTEM_INJ_PPH28;
	float SYSTEM_INJ_PW13;
	float SYSTEM_INJ_PW14;
	float SYSTEM_INJ_PW15;
	float SYSTEM_INJ_PW16;
	float SYSTEM_INJ_PW17;
	float SYSTEM_INJ_PW18;
	float SYSTEM_INJ_PW19;
	float SYSTEM_INJ_PW20;
	float SYSTEM_INJ_PW21;
	float SYSTEM_INJ_PW22;
	float SYSTEM_INJ_PW23;
	float SYSTEM_INJ_PW24;
	float SYSTEM_INJ_PW25;
	float SYSTEM_INJ_PW26;
	float SYSTEM_INJ_PW27;
	float SYSTEM_INJ_PW28;
	float SYSTEM_STAGING_INPUT1;
	float SYSTEM_STAGING_INPUT2;
	float SYSTEM_STAGING_OUTPUT;
	float TRACTION_SMARTDROP;
	float TRACTION_TIMINGRETARD;
	float TRACTION_N2ODECREASE;
	float TRACTION_BOOSTDECREASE;
	float TRACTION_DBWDECREASE;
	float TRACTION_DSTIMINGOFFSET;
	float TRACTION_CSTIMINGOFFSET;
	float TRACTION_DSREVLIMIT;
	float TRACTION_CSREVLIMIT;
	float TRACTION_TCTIME;
	float TRACTION_TCLAUNCHINPUT;
	float DIFUEL_GRAMSPERCYLINDER;
	float VVT_DESIREDINTAKECAMPOS;
	float VVT_ACTUALINTAKECAMPOS;
	float VVT_INTAKESOLDUTY;
	float VVT_DESIREDEXHAUSTCAMPOS;
	float VVT_ACTUALEXHAUSTCAMPOS;
	float VVT_EXHAUSTSOLDUTY;
	float TRANS_GOVERNORPRESSUREPSIACTUAL;
	float TRANS_GOVERNORPRESSUREPSITARGET;
	float TRANS_LINEPRESSUREPSIACTUAL;
	float RACE_LAUNCH_STATUS;
	float RACE_SPOOL_ASSIST_OUTPUT_STATUS2;
	float RACE_SHIFT_SINGLE_OUTPUT_STATUS;
	float RACE_SHIFT_1_2_OUTPUT_STATUS;
	float RACE_SHIFT_2_3_OUTPUT_STATUS;
	float RACE_SHIFT_3_4_OUTPUT_STATUS;
	float RACE_SHIFT_4_5_OUTPUT_STATUS;
	float RACE_SHIFT_5_6_OUTPUT_STATUS;
	float RACE_SHIFT_6_7_OUTPUT_STATUS;
	float RACE_SHIFT_7_8_OUTPUT_STATUS;
	float RACE_SHIFT_OVERRIDE_STATUS;
	float RACE_SHIFT_MASTER_ENABLE_STATUS;
	float RACE_SHIFT_IGNITION_CUT_STATUS;
	float RACE_SHIFT_TIMING_MODIFIER;
	float RACE_SHIFT_TIMER;
	float RACE_CONVERTER_LOCK1;
	float RACE_CONVERTER_LOCK2;
	float RACE_CONVERTER_LOCK3;
	float RACE_CONVERTER_LOCK4;
	float RACE_CONVERTER_LOCK_DISABLE_STAT;
	float RACE_SPOOL_ASSIST_OUTPUT_STATUS;
	float RACE_TRANS_DUMP_VALVE1;
	float RACE_TRANS_DUMP_VALVE2;
	float RACE_TRANS_DUMP_VALVE3;
	float RACE_TRANS_DUMP_VALVE4;
	float RACE_TRANS_DUMP_DISABLE_STATUS;
} Holley_ECU_t;

Holley_ECU_t Holley_ECU = {0};

// ################ End Generated Variable Declarations ################

/* Startup Functions */
void events_Startup()
{
	setupCANbus(CAN_1, 1000000, NORMAL_MODE);
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

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E001000)
		{
			// Signal: Seconds
			Holley_ECU.Seconds = (float)dbc_decode(Message.data, 56, 64, true, DBC_UNSIGNED, 0.001, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E005000)
		{
			// Signal: RPM
			Holley_ECU.RPM = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E009000)
		{
			// Signal: FUEL_INJ_PW
			Holley_ECU.FUEL_INJ_PW = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E00D000)
		{
			// Signal: FUEL_DUTY_CYCLE
			Holley_ECU.FUEL_DUTY_CYCLE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E011000)
		{
			// Signal: FUEL_CLOSED_LOOP_COMP
			Holley_ECU.FUEL_CLOSED_LOOP_COMP = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E015000)
		{
			// Signal: FUEL_TARGET_AFR
			Holley_ECU.FUEL_TARGET_AFR = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E019000)
		{
			// Signal: FUEL_AFR_LEFT
			Holley_ECU.FUEL_AFR_LEFT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E01D000)
		{
			// Signal: FUEL_AFR_RIGHT
			Holley_ECU.FUEL_AFR_RIGHT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E021000)
		{
			// Signal: FUEL_AFR_AVERAGE
			Holley_ECU.FUEL_AFR_AVERAGE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E025000)
		{
			// Signal: FUEL_AIR_TEMP_ENRICH
			Holley_ECU.FUEL_AIR_TEMP_ENRICH = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E029000)
		{
			// Signal: FUEL_COOLANT_ENRICH
			Holley_ECU.FUEL_COOLANT_ENRICH = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E02D000)
		{
			// Signal: FUEL_COOLANT_AFR_OFFSET
			Holley_ECU.FUEL_COOLANT_AFR_OFFSET = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E031000)
		{
			// Signal: FUEL_AFTERSTART_ENRICH
			Holley_ECU.FUEL_AFTERSTART_ENRICH = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E035000)
		{
			// Signal: FUEL_CURRENT_LEARN_PERCENT
			Holley_ECU.FUEL_CURRENT_LEARN_PERCENT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E039000)
		{
			// Signal: FUEL_CLOSED_LOOP_STATUS
			Holley_ECU.FUEL_CLOSED_LOOP_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E03D000)
		{
			// Signal: FUEL_LEARN_STATUS
			Holley_ECU.FUEL_LEARN_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E041000)
		{
			// Signal: FUEL_ECONOMY
			Holley_ECU.FUEL_ECONOMY = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E045000)
		{
			// Signal: FUEL_FLOW
			Holley_ECU.FUEL_FLOW = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E049000)
		{
			// Signal: FUEL_MAP_ROC
			Holley_ECU.FUEL_MAP_ROC = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E04D000)
		{
			// Signal: FUEL_TPS_ROC
			Holley_ECU.FUEL_TPS_ROC = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E051000)
		{
			// Signal: TUNING_CHANGE
			Holley_ECU.TUNING_CHANGE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E055000)
		{
			// Signal: ESTIMATED_VE
			Holley_ECU.ESTIMATED_VE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E059000)
		{
			// Signal: SPARK_IGNITION_TIMING
			Holley_ECU.SPARK_IGNITION_TIMING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E05D000)
		{
			// Signal: SPARK_KNOCK_RETARD
			Holley_ECU.SPARK_KNOCK_RETARD = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E061000)
		{
			// Signal: KNOCK_LEVEL
			Holley_ECU.KNOCK_LEVEL = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E065000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E069000)
		{
			// Signal: IDLE_IAC_POS
			Holley_ECU.IDLE_IAC_POS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E06D000)
		{
			// Signal: IDLE_TARGET_IDLE_SPEED
			Holley_ECU.IDLE_TARGET_IDLE_SPEED = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E071000)
		{
			// Signal: SENSOR_MAP
			Holley_ECU.SENSOR_MAP = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E075000)
		{
			// Signal: SENSOR_TPS
			Holley_ECU.SENSOR_TPS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E079000)
		{
			// Signal: SENSOR_MAT
			Holley_ECU.SENSOR_MAT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E07D000)
		{
			// Signal: SENSOR_CTS
			Holley_ECU.SENSOR_CTS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E081000)
		{
			// Signal: SENSOR_BARO
			Holley_ECU.SENSOR_BARO = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E085000)
		{
			// Signal: SENSOR_BATT_VOLT
			Holley_ECU.SENSOR_BATT_VOLT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E089000)
		{
			// Signal: SENSOR_OIL_PRESSURE
			Holley_ECU.SENSOR_OIL_PRESSURE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E08D000)
		{
			// Signal: SENSOR_FUEL_PRESSURE
			Holley_ECU.SENSOR_FUEL_PRESSURE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E091000)
		{
			// Signal: SENSOR_PEDAL_POSITION
			Holley_ECU.SENSOR_PEDAL_POSITION = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E095000)
		{
			// Signal: SYSTEM_REV_LIMIT_MAIN_STATUS
			Holley_ECU.SYSTEM_REV_LIMIT_MAIN_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E099000)
		{
			// Signal: SYSTEM_REV_LIMIT1_STATUS
			Holley_ECU.SYSTEM_REV_LIMIT1_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E09D000)
		{
			// Signal: SYSTEM_REV_LIMIT2_STATUS
			Holley_ECU.SYSTEM_REV_LIMIT2_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0A1000)
		{
			// Signal: SYSTEM_AC_KICK_STATUS
			Holley_ECU.SYSTEM_AC_KICK_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0A5000)
		{
			// Signal: SYSTEM_TIMING_RETARD1
			Holley_ECU.SYSTEM_TIMING_RETARD1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0A9000)
		{
			// Signal: SYSTEM_TIMING_RETARD2
			Holley_ECU.SYSTEM_TIMING_RETARD2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0AD000)
		{
			// Signal: SYSTEM_TIMING_RETARD3
			Holley_ECU.SYSTEM_TIMING_RETARD3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0B1000)
		{
			// Signal: SYSTEM_FAN1_STATUS
			Holley_ECU.SYSTEM_FAN1_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0B5000)
		{
			// Signal: SYSTEM_FAN2_STATUS
			Holley_ECU.SYSTEM_FAN2_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0B9000)
		{
			// Signal: SYSTEM_FUEL_PUMP2_STATUS
			Holley_ECU.SYSTEM_FUEL_PUMP2_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0BD000)
		{
			// Signal: SYSTEM_AC_SHUTDOWN_STATUS
			Holley_ECU.SYSTEM_AC_SHUTDOWN_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0C1000)
		{
			// Signal: SYSTEM_LOCKUP_STATUS
			Holley_ECU.SYSTEM_LOCKUP_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0C5000)
		{
			// Signal: SYSTEM_SENSOR_WARNING
			Holley_ECU.SYSTEM_SENSOR_WARNING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0C9000)
		{
			// Signal: SYSTEM_SENSOR_CAUTION
			Holley_ECU.SYSTEM_SENSOR_CAUTION = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0CD000)
		{
			// Signal: SYSTEM_BASE_FUEL_LB
			Holley_ECU.SYSTEM_BASE_FUEL_LB = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0D1000)
		{
			// Signal: SYSTEM_BASE_FUEL_VE
			Holley_ECU.SYSTEM_BASE_FUEL_VE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0D5000)
		{
			// Signal: SYSTEM_BASE_TIMING
			Holley_ECU.SYSTEM_BASE_TIMING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0D9000)
		{
			// Signal: SYSTEM_BASE_TAFR
			Holley_ECU.SYSTEM_BASE_TAFR = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0DD000)
		{
			// Signal: SYSTEM_BASE_IGN_DWELL
			Holley_ECU.SYSTEM_BASE_IGN_DWELL = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0E1000)
		{
			// Signal: SYSTEM_VOL_COMP_IGN_DWELL
			Holley_ECU.SYSTEM_VOL_COMP_IGN_DWELL = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0E5000)
		{
			// Signal: SYSTEM_INJ_END_ANGLE
			Holley_ECU.SYSTEM_INJ_END_ANGLE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0E9000)
		{
			// Signal: SYSTEM_ECU_LOG_TRIGGER
			Holley_ECU.SYSTEM_ECU_LOG_TRIGGER = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0ED000)
		{
			// Signal: SYSTEM_TIMING_AIR_TEMP
			Holley_ECU.SYSTEM_TIMING_AIR_TEMP = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0F1000)
		{
			// Signal: SYSTEM_TIMING_COOLANT_TEMP
			Holley_ECU.SYSTEM_TIMING_COOLANT_TEMP = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0F5000)
		{
			// Signal: SYSTEM_STATUS1
			Holley_ECU.SYSTEM_STATUS1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0F9000)
		{
			// Signal: SYSTEM_STATUS2
			Holley_ECU.SYSTEM_STATUS2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E0FD000)
		{
			// Signal: SYSTEM_STATUS3
			Holley_ECU.SYSTEM_STATUS3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E101000)
		{
			// Signal: SYSTEM_STATUS4
			Holley_ECU.SYSTEM_STATUS4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E105000)
		{
			// Signal: SYSTEM_STATUS5
			Holley_ECU.SYSTEM_STATUS5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E109000)
		{
			// Signal: SYSTEM_STATUS6
			Holley_ECU.SYSTEM_STATUS6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E10D000)
		{
			// Signal: SYSTEM_STATUS7
			Holley_ECU.SYSTEM_STATUS7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E111000)
		{
			// Signal: SYSTEM_STATUS8
			Holley_ECU.SYSTEM_STATUS8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E115000)
		{
			// Signal: SYSTEM_INJ_PPH1
			Holley_ECU.SYSTEM_INJ_PPH1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E119000)
		{
			// Signal: SYSTEM_INJ_PPH2
			Holley_ECU.SYSTEM_INJ_PPH2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E11D000)
		{
			// Signal: SYSTEM_INJ_PPH3
			Holley_ECU.SYSTEM_INJ_PPH3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E121000)
		{
			// Signal: SYSTEM_INJ_PPH4
			Holley_ECU.SYSTEM_INJ_PPH4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E125000)
		{
			// Signal: SYSTEM_INJ_PPH5
			Holley_ECU.SYSTEM_INJ_PPH5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E129000)
		{
			// Signal: SYSTEM_INJ_PPH6
			Holley_ECU.SYSTEM_INJ_PPH6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E12D000)
		{
			// Signal: SYSTEM_INJ_PPH7
			Holley_ECU.SYSTEM_INJ_PPH7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E131000)
		{
			// Signal: SYSTEM_INJ_PPH8
			Holley_ECU.SYSTEM_INJ_PPH8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E135000)
		{
			// Signal: SYSTEM_INJ_PPH9
			Holley_ECU.SYSTEM_INJ_PPH9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E139000)
		{
			// Signal: SYSTEM_INJ_PPH10
			Holley_ECU.SYSTEM_INJ_PPH10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E13D000)
		{
			// Signal: SYSTEM_INJ_PPH11
			Holley_ECU.SYSTEM_INJ_PPH11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E141000)
		{
			// Signal: SYSTEM_INJ_PPH12
			Holley_ECU.SYSTEM_INJ_PPH12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E145000)
		{
			// Signal: SYSTEM_INJ_PW1
			Holley_ECU.SYSTEM_INJ_PW1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E149000)
		{
			// Signal: SYSTEM_INJ_PW2
			Holley_ECU.SYSTEM_INJ_PW2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E14D000)
		{
			// Signal: SYSTEM_INJ_PW3
			Holley_ECU.SYSTEM_INJ_PW3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E151000)
		{
			// Signal: SYSTEM_INJ_PW4
			Holley_ECU.SYSTEM_INJ_PW4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E155000)
		{
			// Signal: SYSTEM_INJ_PW5
			Holley_ECU.SYSTEM_INJ_PW5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E159000)
		{
			// Signal: SYSTEM_INJ_PW6
			Holley_ECU.SYSTEM_INJ_PW6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E15D000)
		{
			// Signal: SYSTEM_INJ_PW7
			Holley_ECU.SYSTEM_INJ_PW7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E161000)
		{
			// Signal: SYSTEM_INJ_PW8
			Holley_ECU.SYSTEM_INJ_PW8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E165000)
		{
			// Signal: SYSTEM_INJ_PW9
			Holley_ECU.SYSTEM_INJ_PW9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E169000)
		{
			// Signal: SYSTEM_INJ_PW10
			Holley_ECU.SYSTEM_INJ_PW10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E16D000)
		{
			// Signal: SYSTEM_INJ_PW11
			Holley_ECU.SYSTEM_INJ_PW11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E171000)
		{
			// Signal: SYSTEM_INJ_PW12
			Holley_ECU.SYSTEM_INJ_PW12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E175000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR1
			Holley_ECU.SYSTEM_CYL_FUEL_CORR1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E179000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR2
			Holley_ECU.SYSTEM_CYL_FUEL_CORR2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E17D000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR3
			Holley_ECU.SYSTEM_CYL_FUEL_CORR3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E181000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR4
			Holley_ECU.SYSTEM_CYL_FUEL_CORR4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E185000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR5
			Holley_ECU.SYSTEM_CYL_FUEL_CORR5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E189000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR6
			Holley_ECU.SYSTEM_CYL_FUEL_CORR6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E18D000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR7
			Holley_ECU.SYSTEM_CYL_FUEL_CORR7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E191000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR8
			Holley_ECU.SYSTEM_CYL_FUEL_CORR8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E195000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR9
			Holley_ECU.SYSTEM_CYL_FUEL_CORR9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E199000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR10
			Holley_ECU.SYSTEM_CYL_FUEL_CORR10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E19D000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR11
			Holley_ECU.SYSTEM_CYL_FUEL_CORR11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1A1000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR12
			Holley_ECU.SYSTEM_CYL_FUEL_CORR12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1A5000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR13
			Holley_ECU.SYSTEM_CYL_FUEL_CORR13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1A9000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR14
			Holley_ECU.SYSTEM_CYL_FUEL_CORR14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1AD000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR15
			Holley_ECU.SYSTEM_CYL_FUEL_CORR15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1B1000)
		{
			// Signal: SYSTEM_CYL_FUEL_CORR16
			Holley_ECU.SYSTEM_CYL_FUEL_CORR16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1B5000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR1
			Holley_ECU.SYSTEM_CYL_TIMING_CORR1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1B9000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR2
			Holley_ECU.SYSTEM_CYL_TIMING_CORR2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1BD000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR3
			Holley_ECU.SYSTEM_CYL_TIMING_CORR3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1C1000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR4
			Holley_ECU.SYSTEM_CYL_TIMING_CORR4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1C5000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR5
			Holley_ECU.SYSTEM_CYL_TIMING_CORR5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1C9000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR6
			Holley_ECU.SYSTEM_CYL_TIMING_CORR6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1CD000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR7
			Holley_ECU.SYSTEM_CYL_TIMING_CORR7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1D1000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR8
			Holley_ECU.SYSTEM_CYL_TIMING_CORR8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1D5000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR9
			Holley_ECU.SYSTEM_CYL_TIMING_CORR9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1D9000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR10
			Holley_ECU.SYSTEM_CYL_TIMING_CORR10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1DD000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR11
			Holley_ECU.SYSTEM_CYL_TIMING_CORR11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1E1000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR12
			Holley_ECU.SYSTEM_CYL_TIMING_CORR12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1E5000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR13
			Holley_ECU.SYSTEM_CYL_TIMING_CORR13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1E9000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR14
			Holley_ECU.SYSTEM_CYL_TIMING_CORR14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1ED000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR15
			Holley_ECU.SYSTEM_CYL_TIMING_CORR15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1F1000)
		{
			// Signal: SYSTEM_CYL_TIMING_CORR16
			Holley_ECU.SYSTEM_CYL_TIMING_CORR16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1F5000)
		{
			// Signal: SYSTEM_TARGET_FUEL_PRESSURE
			Holley_ECU.SYSTEM_TARGET_FUEL_PRESSURE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1F9000)
		{
			// Signal: SYSTEM_BOOST_PSIG
			Holley_ECU.SYSTEM_BOOST_PSIG = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E1FD000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E201000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E205000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E209000)
		{
			// Signal: BOOST_GEAR
			Holley_ECU.BOOST_GEAR = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E20D000)
		{
			// Signal: BOOST_MANUAL_STAGE
			Holley_ECU.BOOST_MANUAL_STAGE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E211000)
		{
			// Signal: BOOST_PSIG
			Holley_ECU.BOOST_PSIG = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E215000)
		{
			// Signal: BOOST_SPEED
			Holley_ECU.BOOST_SPEED = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E219000)
		{
			// Signal: BOOST_TIME
			Holley_ECU.BOOST_TIME = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E21D000)
		{
			// Signal: BOOST_TARGET_BOOST
			Holley_ECU.BOOST_TARGET_BOOST = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E221000)
		{
			// Signal: BOOST_TRANS_BRAKE_STATUS
			Holley_ECU.BOOST_TRANS_BRAKE_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E225000)
		{
			// Signal: BOOST_SCRAMBLE_UP_STATUS
			Holley_ECU.BOOST_SCRAMBLE_UP_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E229000)
		{
			// Signal: BOOST_SCRAMBLE_DOWN_STATUS
			Holley_ECU.BOOST_SCRAMBLE_DOWN_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E22D000)
		{
			// Signal: BOOST_MANUAL_BUILD_STATUS
			Holley_ECU.BOOST_MANUAL_BUILD_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E231000)
		{
			// Signal: BOOST_MANUAL_RESET_STATUS
			Holley_ECU.BOOST_MANUAL_RESET_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E235000)
		{
			// Signal: BOOST_BUILD_STATUS
			Holley_ECU.BOOST_BUILD_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E239000)
		{
			// Signal: BOOST_SOLENOID_DUTY
			Holley_ECU.BOOST_SOLENOID_DUTY = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E23D000)
		{
			// Signal: BOOST_SAFETY
			Holley_ECU.BOOST_SAFETY = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E241000)
		{
			// Signal: BOOST_MASTER_ENABLE
			Holley_ECU.BOOST_MASTER_ENABLE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E245000)
		{
			// Signal: BOOST_MANUAL_SHIFT_INPUT
			Holley_ECU.BOOST_MANUAL_SHIFT_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E249000)
		{
			// Signal: BOOST_MANUAL_STAGE_INPUT
			Holley_ECU.BOOST_MANUAL_STAGE_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E24D000)
		{
			// Signal: BOOST_FILL_SOL_DC
			Holley_ECU.BOOST_FILL_SOL_DC = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E251000)
		{
			// Signal: BOOST_VENT_SOL_DC
			Holley_ECU.BOOST_VENT_SOL_DC = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E255000)
		{
			// Signal: WM_INJ_VALUE
			Holley_ECU.WM_INJ_VALUE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E259000)
		{
			// Signal: WM_MANUAL_ENABLE_STATUS
			Holley_ECU.WM_MANUAL_ENABLE_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E25D000)
		{
			// Signal: WM_LOW_FLUID_STATUS
			Holley_ECU.WM_LOW_FLUID_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E261000)
		{
			// Signal: WM_PUMP_STATUS
			Holley_ECU.WM_PUMP_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E265000)
		{
			// Signal: WM_SOL_FLOW1
			Holley_ECU.WM_SOL_FLOW1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E269000)
		{
			// Signal: WM_SOL_FLOW2
			Holley_ECU.WM_SOL_FLOW2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E26D000)
		{
			// Signal: WM_TOTAL_FLOW
			Holley_ECU.WM_TOTAL_FLOW = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E271000)
		{
			// Signal: WM_SOL_DC1
			Holley_ECU.WM_SOL_DC1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E275000)
		{
			// Signal: WM_SOL_DC2
			Holley_ECU.WM_SOL_DC2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E279000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E27D000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E281000)
		{
			// Signal: NOS_STAGE1
			Holley_ECU.NOS_STAGE1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E285000)
		{
			// Signal: NOS_STAGE2
			Holley_ECU.NOS_STAGE2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E289000)
		{
			// Signal: NOS_STAGE3
			Holley_ECU.NOS_STAGE3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E28D000)
		{
			// Signal: NOS_STAGE4
			Holley_ECU.NOS_STAGE4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E291000)
		{
			// Signal: NOS_STAGE5
			Holley_ECU.NOS_STAGE5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E295000)
		{
			// Signal: NOS_STAGE6
			Holley_ECU.NOS_STAGE6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E299000)
		{
			// Signal: NOS_STAGE7
			Holley_ECU.NOS_STAGE7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E29D000)
		{
			// Signal: NOS_STAGE8
			Holley_ECU.NOS_STAGE8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2A1000)
		{
			// Signal: NOS_GPO1
			Holley_ECU.NOS_GPO1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2A5000)
		{
			// Signal: NOS_GPO2
			Holley_ECU.NOS_GPO2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2A9000)
		{
			// Signal: NOS_GPO3
			Holley_ECU.NOS_GPO3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2AD000)
		{
			// Signal: NOS_GPO4
			Holley_ECU.NOS_GPO4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2B1000)
		{
			// Signal: NOS_GPO5
			Holley_ECU.NOS_GPO5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2B5000)
		{
			// Signal: NOS_GPO6
			Holley_ECU.NOS_GPO6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2B9000)
		{
			// Signal: NOS_GPO7
			Holley_ECU.NOS_GPO7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2BD000)
		{
			// Signal: NOS_GPO8
			Holley_ECU.NOS_GPO8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2C1000)
		{
			// Signal: NOS_ENABLED_STATUS
			Holley_ECU.NOS_ENABLED_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2C5000)
		{
			// Signal: NOS_INPUT1_STATUS
			Holley_ECU.NOS_INPUT1_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2C9000)
		{
			// Signal: NOS_INPUT2_STATUS
			Holley_ECU.NOS_INPUT2_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2CD000)
		{
			// Signal: NOS_INPUT3_STATUS
			Holley_ECU.NOS_INPUT3_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2D1000)
		{
			// Signal: NOS_INPUT4_STATUS
			Holley_ECU.NOS_INPUT4_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2D5000)
		{
			// Signal: NOS_INPUT5_STATUS
			Holley_ECU.NOS_INPUT5_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2D9000)
		{
			// Signal: NOS_INPUT6_STATUS
			Holley_ECU.NOS_INPUT6_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2DD000)
		{
			// Signal: NOS_INPUT7_STATUS
			Holley_ECU.NOS_INPUT7_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2E1000)
		{
			// Signal: NOS_INPUT8_STATUS
			Holley_ECU.NOS_INPUT8_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2E5000)
		{
			// Signal: NOS_PURGE_STATUS
			Holley_ECU.NOS_PURGE_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2E9000)
		{
			// Signal: NOS_LEAN_CUTOFF_STATUS
			Holley_ECU.NOS_LEAN_CUTOFF_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2ED000)
		{
			// Signal: NOS_RICH_CUTOFF_STATUS
			Holley_ECU.NOS_RICH_CUTOFF_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2F1000)
		{
			// Signal: NOS_RPM_CUTOFF_STATUS
			Holley_ECU.NOS_RPM_CUTOFF_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2F5000)
		{
			// Signal: NOS_MAP_CUTOFF_STATUS
			Holley_ECU.NOS_MAP_CUTOFF_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2F9000)
		{
			// Signal: NOS_PURGE_OUTPUT
			Holley_ECU.NOS_PURGE_OUTPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E2FD000)
		{
			// Signal: NOS_DRY_FUEL1
			Holley_ECU.NOS_DRY_FUEL1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E301000)
		{
			// Signal: NOS_DRY_FUEL2
			Holley_ECU.NOS_DRY_FUEL2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E305000)
		{
			// Signal: NOS_DRY_FUEL3
			Holley_ECU.NOS_DRY_FUEL3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E309000)
		{
			// Signal: NOS_DRY_FUEL4
			Holley_ECU.NOS_DRY_FUEL4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E30D000)
		{
			// Signal: NOS_DRY_FUEL5
			Holley_ECU.NOS_DRY_FUEL5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E311000)
		{
			// Signal: NOS_DRY_FUEL6
			Holley_ECU.NOS_DRY_FUEL6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E315000)
		{
			// Signal: NOS_DRY_FUEL7
			Holley_ECU.NOS_DRY_FUEL7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E319000)
		{
			// Signal: NOS_DRY_FUEL8
			Holley_ECU.NOS_DRY_FUEL8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E31D000)
		{
			// Signal: NOS_TIMING_MOD1
			Holley_ECU.NOS_TIMING_MOD1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E321000)
		{
			// Signal: NOS_TIMING_MOD2
			Holley_ECU.NOS_TIMING_MOD2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E325000)
		{
			// Signal: NOS_TIMING_MOD3
			Holley_ECU.NOS_TIMING_MOD3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E329000)
		{
			// Signal: NOS_TIMING_MOD4
			Holley_ECU.NOS_TIMING_MOD4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E32D000)
		{
			// Signal: NOS_TIMING_MOD5
			Holley_ECU.NOS_TIMING_MOD5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E331000)
		{
			// Signal: NOS_TIMING_MOD6
			Holley_ECU.NOS_TIMING_MOD6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E335000)
		{
			// Signal: NOS_TIMING_MOD7
			Holley_ECU.NOS_TIMING_MOD7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E339000)
		{
			// Signal: NOS_TIMING_MOD8
			Holley_ECU.NOS_TIMING_MOD8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E33D000)
		{
			// Signal: NOS_TIMER1
			Holley_ECU.NOS_TIMER1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E341000)
		{
			// Signal: NOS_TIMER2
			Holley_ECU.NOS_TIMER2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E345000)
		{
			// Signal: NOS_TIMER3
			Holley_ECU.NOS_TIMER3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E349000)
		{
			// Signal: NOS_TIMER4
			Holley_ECU.NOS_TIMER4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E34D000)
		{
			// Signal: NOS_TIMER5
			Holley_ECU.NOS_TIMER5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E351000)
		{
			// Signal: NOS_TIMER6
			Holley_ECU.NOS_TIMER6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E355000)
		{
			// Signal: NOS_TIMER7
			Holley_ECU.NOS_TIMER7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E359000)
		{
			// Signal: NOS_TIMER8
			Holley_ECU.NOS_TIMER8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E35D000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E361000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E365000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E369000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E36D000)
		{
			// Signal: TRANS_GEAR
			Holley_ECU.TRANS_GEAR = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E371000)
		{
			// Signal: TRANS_SPEED
			Holley_ECU.TRANS_SPEED = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E375000)
		{
			// Signal: TRANS_LINE_PRESSURE_PWM
			Holley_ECU.TRANS_LINE_PRESSURE_PWM = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E379000)
		{
			// Signal: TRANS_INPUT_SHAFT_SPEED
			Holley_ECU.TRANS_INPUT_SHAFT_SPEED = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E37D000)
		{
			// Signal: TRANS_ACCUM_PRESSURE_PWM
			Holley_ECU.TRANS_ACCUM_PRESSURE_PWM = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E381000)
		{
			// Signal: TRANS_TCC_DUTY_CYCLE
			Holley_ECU.TRANS_TCC_DUTY_CYCLE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E385000)
		{
			// Signal: TRANS_LINE_TEMP
			Holley_ECU.TRANS_LINE_TEMP = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E389000)
		{
			// Signal: TRANS_TORQUE_TIME
			Holley_ECU.TRANS_TORQUE_TIME = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E38D000)
		{
			// Signal: TRANS_MAN_US_INPUT
			Holley_ECU.TRANS_MAN_US_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E391000)
		{
			// Signal: TRANS_MAN_DS_INPUT
			Holley_ECU.TRANS_MAN_DS_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E395000)
		{
			// Signal: TRANS_AUTOMAN_INPUT
			Holley_ECU.TRANS_AUTOMAN_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E399000)
		{
			// Signal: TRANS_RANGE_SWITCH_POSITION
			Holley_ECU.TRANS_RANGE_SWITCH_POSITION = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E39D000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3A1000)
		{
			// Signal: DBW_TB_TPS_RISING
			Holley_ECU.DBW_TB_TPS_RISING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3A5000)
		{
			// Signal: DBW_TB_TPS_FALLING
			Holley_ECU.DBW_TB_TPS_FALLING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3A9000)
		{
			// Signal: DBW_PEDAL_TPS_RISING
			Holley_ECU.DBW_PEDAL_TPS_RISING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3AD000)
		{
			// Signal: DBW_PEDAL_TPS_FALLING
			Holley_ECU.DBW_PEDAL_TPS_FALLING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3B1000)
		{
			// Signal: DBW_TB2_TPS_RISING
			Holley_ECU.DBW_TB2_TPS_RISING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3B5000)
		{
			// Signal: DBW_TB2_TPS_FALLING
			Holley_ECU.DBW_TB2_TPS_FALLING = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3B9000)
		{
			// Signal: DBW_TB_POSITION
			Holley_ECU.DBW_TB_POSITION = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3BD000)
		{
			// Signal: DBW_TB2_POSITION
			Holley_ECU.DBW_TB2_POSITION = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3C1000)
		{
			// Signal: DBW_BRAKE_PEDAL
			Holley_ECU.DBW_BRAKE_PEDAL = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3C5000)
		{
			// Signal: PADDING
			Holley_ECU.PADDING = (int32_t)dbc_decode(Message.data, 24, 32, true, DBC_SIGNED, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3C9000)
		{
			// Signal: DIAGNOSTIC1
			Holley_ECU.DIAGNOSTIC1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3CD000)
		{
			// Signal: DIAGNOSTIC2
			Holley_ECU.DIAGNOSTIC2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3D1000)
		{
			// Signal: DIAGNOSTIC3
			Holley_ECU.DIAGNOSTIC3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3D5000)
		{
			// Signal: DIAGNOSTIC4
			Holley_ECU.DIAGNOSTIC4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3D9000)
		{
			// Signal: DIAGNOSTIC5
			Holley_ECU.DIAGNOSTIC5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3DD000)
		{
			// Signal: DIAGNOSTIC6
			Holley_ECU.DIAGNOSTIC6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3E1000)
		{
			// Signal: DIAGNOSTIC7
			Holley_ECU.DIAGNOSTIC7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3E5000)
		{
			// Signal: DIAGNOSTIC8
			Holley_ECU.DIAGNOSTIC8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3E9000)
		{
			// Signal: DIAGNOSTIC9
			Holley_ECU.DIAGNOSTIC9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3ED000)
		{
			// Signal: DIAGNOSTIC10
			Holley_ECU.DIAGNOSTIC10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3F1000)
		{
			// Signal: DIAGNOSTIC11
			Holley_ECU.DIAGNOSTIC11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3F5000)
		{
			// Signal: DIAGNOSTIC12
			Holley_ECU.DIAGNOSTIC12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3F9000)
		{
			// Signal: DIAGNOSTIC13
			Holley_ECU.DIAGNOSTIC13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E3FD000)
		{
			// Signal: DIAGNOSTIC14
			Holley_ECU.DIAGNOSTIC14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E401000)
		{
			// Signal: DIAGNOSTIC15
			Holley_ECU.DIAGNOSTIC15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E405000)
		{
			// Signal: DIAGNOSTIC16
			Holley_ECU.DIAGNOSTIC16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E409000)
		{
			// Signal: DIAGNOSTIC17
			Holley_ECU.DIAGNOSTIC17 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E40D000)
		{
			// Signal: DIAGNOSTIC18
			Holley_ECU.DIAGNOSTIC18 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E411000)
		{
			// Signal: DIAGNOSTIC19
			Holley_ECU.DIAGNOSTIC19 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E415000)
		{
			// Signal: DIAGNOSTIC20
			Holley_ECU.DIAGNOSTIC20 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E419000)
		{
			// Signal: ADV_LAUNCH_INPUT
			Holley_ECU.ADV_LAUNCH_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E41D000)
		{
			// Signal: ADV_SHIFT_INPUT
			Holley_ECU.ADV_SHIFT_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E421000)
		{
			// Signal: ADV_MANUAL_INPUT
			Holley_ECU.ADV_MANUAL_INPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E425000)
		{
			// Signal: ADV_GEAR
			Holley_ECU.ADV_GEAR = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E429000)
		{
			// Signal: ADV_AT_1D1
			Holley_ECU.ADV_AT_1D1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E42D000)
		{
			// Signal: ADV_AT_1D2
			Holley_ECU.ADV_AT_1D2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E431000)
		{
			// Signal: ADV_AT_1D3
			Holley_ECU.ADV_AT_1D3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E435000)
		{
			// Signal: ADV_AT_1D4
			Holley_ECU.ADV_AT_1D4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E439000)
		{
			// Signal: ADV_AT_1D5
			Holley_ECU.ADV_AT_1D5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E43D000)
		{
			// Signal: ADV_AT_1D6
			Holley_ECU.ADV_AT_1D6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E441000)
		{
			// Signal: ADV_AT_1D7
			Holley_ECU.ADV_AT_1D7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E445000)
		{
			// Signal: ADV_AT_1D8
			Holley_ECU.ADV_AT_1D8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E449000)
		{
			// Signal: ADV_AT_2D1
			Holley_ECU.ADV_AT_2D1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E44D000)
		{
			// Signal: ADV_AT_2D2
			Holley_ECU.ADV_AT_2D2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E451000)
		{
			// Signal: ADV_AT_2D3
			Holley_ECU.ADV_AT_2D3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E455000)
		{
			// Signal: ADV_AT_2D4
			Holley_ECU.ADV_AT_2D4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E459000)
		{
			// Signal: ADV_AT_2D5
			Holley_ECU.ADV_AT_2D5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E45D000)
		{
			// Signal: ADV_AT_2D6
			Holley_ECU.ADV_AT_2D6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E461000)
		{
			// Signal: ADV_AT_2D7
			Holley_ECU.ADV_AT_2D7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E465000)
		{
			// Signal: ADV_AT_2D8
			Holley_ECU.ADV_AT_2D8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E469000)
		{
			// Signal: ADV_AT_1D_GEAR1
			Holley_ECU.ADV_AT_1D_GEAR1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E46D000)
		{
			// Signal: ADV_AT_1D_GEAR2
			Holley_ECU.ADV_AT_1D_GEAR2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E471000)
		{
			// Signal: ADV_AT_1D_GEAR3
			Holley_ECU.ADV_AT_1D_GEAR3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E475000)
		{
			// Signal: ADV_AT_1D_GEAR4
			Holley_ECU.ADV_AT_1D_GEAR4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E479000)
		{
			// Signal: ADV_AT_1D_GEAR5
			Holley_ECU.ADV_AT_1D_GEAR5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E47D000)
		{
			// Signal: ADV_AT_1D_GEAR6
			Holley_ECU.ADV_AT_1D_GEAR6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E481000)
		{
			// Signal: ADV_AT_1D_GEAR7
			Holley_ECU.ADV_AT_1D_GEAR7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E485000)
		{
			// Signal: ADV_AT_1D_GEAR8
			Holley_ECU.ADV_AT_1D_GEAR8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E489000)
		{
			// Signal: ADV_AT_2D_GEAR1
			Holley_ECU.ADV_AT_2D_GEAR1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E48D000)
		{
			// Signal: ADV_AT_2D_GEAR2
			Holley_ECU.ADV_AT_2D_GEAR2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E491000)
		{
			// Signal: ADV_AT_2D_GEAR3
			Holley_ECU.ADV_AT_2D_GEAR3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E495000)
		{
			// Signal: ADV_AT_2D_GEAR4
			Holley_ECU.ADV_AT_2D_GEAR4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E499000)
		{
			// Signal: ADV_AT_2D_GEAR5
			Holley_ECU.ADV_AT_2D_GEAR5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E49D000)
		{
			// Signal: ADV_AT_2D_GEAR6
			Holley_ECU.ADV_AT_2D_GEAR6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4A1000)
		{
			// Signal: ADV_AT_2D_GEAR7
			Holley_ECU.ADV_AT_2D_GEAR7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4A5000)
		{
			// Signal: ADV_AT_2D_GEAR8
			Holley_ECU.ADV_AT_2D_GEAR8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4A9000)
		{
			// Signal: IO_INPUT1
			Holley_ECU.IO_INPUT1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4AD000)
		{
			// Signal: IO_INPUT2
			Holley_ECU.IO_INPUT2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4B1000)
		{
			// Signal: IO_INPUT3
			Holley_ECU.IO_INPUT3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4B5000)
		{
			// Signal: IO_INPUT4
			Holley_ECU.IO_INPUT4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4B9000)
		{
			// Signal: IO_INPUT5
			Holley_ECU.IO_INPUT5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4BD000)
		{
			// Signal: IO_INPUT6
			Holley_ECU.IO_INPUT6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4C1000)
		{
			// Signal: IO_INPUT7
			Holley_ECU.IO_INPUT7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4C5000)
		{
			// Signal: IO_INPUT8
			Holley_ECU.IO_INPUT8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4C9000)
		{
			// Signal: IO_INPUT9
			Holley_ECU.IO_INPUT9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4CD000)
		{
			// Signal: IO_INPUT10
			Holley_ECU.IO_INPUT10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4D1000)
		{
			// Signal: IO_INPUT11
			Holley_ECU.IO_INPUT11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4D5000)
		{
			// Signal: IO_INPUT12
			Holley_ECU.IO_INPUT12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4D9000)
		{
			// Signal: IO_INPUT13
			Holley_ECU.IO_INPUT13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4DD000)
		{
			// Signal: IO_INPUT14
			Holley_ECU.IO_INPUT14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4E1000)
		{
			// Signal: IO_INPUT15
			Holley_ECU.IO_INPUT15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4E5000)
		{
			// Signal: IO_INPUT16
			Holley_ECU.IO_INPUT16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4E9000)
		{
			// Signal: IO_INPUT17
			Holley_ECU.IO_INPUT17 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4ED000)
		{
			// Signal: IO_INPUT18
			Holley_ECU.IO_INPUT18 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4F1000)
		{
			// Signal: IO_INPUT19
			Holley_ECU.IO_INPUT19 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4F5000)
		{
			// Signal: IO_INPUT20
			Holley_ECU.IO_INPUT20 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4F9000)
		{
			// Signal: IO_INPUT21
			Holley_ECU.IO_INPUT21 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E4FD000)
		{
			// Signal: IO_INPUT22
			Holley_ECU.IO_INPUT22 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E501000)
		{
			// Signal: IO_INPUT23
			Holley_ECU.IO_INPUT23 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E505000)
		{
			// Signal: IO_INPUT24
			Holley_ECU.IO_INPUT24 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E509000)
		{
			// Signal: IO_INPUT25
			Holley_ECU.IO_INPUT25 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E50D000)
		{
			// Signal: IO_INPUT26
			Holley_ECU.IO_INPUT26 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E511000)
		{
			// Signal: IO_INPUT27
			Holley_ECU.IO_INPUT27 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E515000)
		{
			// Signal: IO_INPUT28
			Holley_ECU.IO_INPUT28 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E519000)
		{
			// Signal: IO_INPUT29
			Holley_ECU.IO_INPUT29 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E51D000)
		{
			// Signal: IO_INPUT30
			Holley_ECU.IO_INPUT30 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E521000)
		{
			// Signal: IO_INPUT31
			Holley_ECU.IO_INPUT31 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E525000)
		{
			// Signal: IO_INPUT32
			Holley_ECU.IO_INPUT32 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E529000)
		{
			// Signal: IO_INPUT33
			Holley_ECU.IO_INPUT33 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E52D000)
		{
			// Signal: IO_INPUT34
			Holley_ECU.IO_INPUT34 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E531000)
		{
			// Signal: IO_INPUT35
			Holley_ECU.IO_INPUT35 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E535000)
		{
			// Signal: IO_INPUT36
			Holley_ECU.IO_INPUT36 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E539000)
		{
			// Signal: IO_INPUT37
			Holley_ECU.IO_INPUT37 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E53D000)
		{
			// Signal: IO_INPUT38
			Holley_ECU.IO_INPUT38 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E541000)
		{
			// Signal: IO_INPUT39
			Holley_ECU.IO_INPUT39 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E545000)
		{
			// Signal: IO_INPUT40
			Holley_ECU.IO_INPUT40 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E549000)
		{
			// Signal: IO_INPUT41
			Holley_ECU.IO_INPUT41 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E54D000)
		{
			// Signal: IO_INPUT42
			Holley_ECU.IO_INPUT42 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E551000)
		{
			// Signal: IO_INPUT43
			Holley_ECU.IO_INPUT43 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E555000)
		{
			// Signal: IO_INPUT44
			Holley_ECU.IO_INPUT44 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E559000)
		{
			// Signal: IO_INPUT45
			Holley_ECU.IO_INPUT45 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E55D000)
		{
			// Signal: IO_INPUT46
			Holley_ECU.IO_INPUT46 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E561000)
		{
			// Signal: IO_INPUT47
			Holley_ECU.IO_INPUT47 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E565000)
		{
			// Signal: IO_INPUT48
			Holley_ECU.IO_INPUT48 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E569000)
		{
			// Signal: IO_INPUT49
			Holley_ECU.IO_INPUT49 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E56D000)
		{
			// Signal: IO_INPUT50
			Holley_ECU.IO_INPUT50 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E571000)
		{
			// Signal: IO_INPUT51
			Holley_ECU.IO_INPUT51 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E575000)
		{
			// Signal: IO_INPUT52
			Holley_ECU.IO_INPUT52 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E579000)
		{
			// Signal: IO_INPUT53
			Holley_ECU.IO_INPUT53 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E57D000)
		{
			// Signal: IO_INPUT54
			Holley_ECU.IO_INPUT54 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E581000)
		{
			// Signal: IO_INPUT55
			Holley_ECU.IO_INPUT55 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E585000)
		{
			// Signal: IO_INPUT56
			Holley_ECU.IO_INPUT56 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E589000)
		{
			// Signal: IO_INPUT57
			Holley_ECU.IO_INPUT57 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E58D000)
		{
			// Signal: IO_INPUT58
			Holley_ECU.IO_INPUT58 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E591000)
		{
			// Signal: IO_INPUT59
			Holley_ECU.IO_INPUT59 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E595000)
		{
			// Signal: IO_INPUT60
			Holley_ECU.IO_INPUT60 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E599000)
		{
			// Signal: IO_INPUT61
			Holley_ECU.IO_INPUT61 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E59D000)
		{
			// Signal: IO_INPUT62
			Holley_ECU.IO_INPUT62 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5A1000)
		{
			// Signal: IO_INPUT63
			Holley_ECU.IO_INPUT63 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5A5000)
		{
			// Signal: IO_INPUT64
			Holley_ECU.IO_INPUT64 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5A9000)
		{
			// Signal: IO_INPUT65
			Holley_ECU.IO_INPUT65 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5AD000)
		{
			// Signal: IO_INPUT66
			Holley_ECU.IO_INPUT66 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5B1000)
		{
			// Signal: IO_INPUT67
			Holley_ECU.IO_INPUT67 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5B5000)
		{
			// Signal: IO_INPUT68
			Holley_ECU.IO_INPUT68 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5B9000)
		{
			// Signal: IO_INPUT69
			Holley_ECU.IO_INPUT69 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5BD000)
		{
			// Signal: IO_INPUT70
			Holley_ECU.IO_INPUT70 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5C1000)
		{
			// Signal: IO_INPUT71
			Holley_ECU.IO_INPUT71 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5C5000)
		{
			// Signal: IO_INPUT72
			Holley_ECU.IO_INPUT72 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5C9000)
		{
			// Signal: IO_INPUT73
			Holley_ECU.IO_INPUT73 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5CD000)
		{
			// Signal: IO_INPUT74
			Holley_ECU.IO_INPUT74 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5D1000)
		{
			// Signal: IO_INPUT75
			Holley_ECU.IO_INPUT75 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5D5000)
		{
			// Signal: IO_INPUT76
			Holley_ECU.IO_INPUT76 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5D9000)
		{
			// Signal: IO_INPUT77
			Holley_ECU.IO_INPUT77 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5DD000)
		{
			// Signal: IO_INPUT78
			Holley_ECU.IO_INPUT78 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5E1000)
		{
			// Signal: IO_INPUT79
			Holley_ECU.IO_INPUT79 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5E5000)
		{
			// Signal: IO_INPUT80
			Holley_ECU.IO_INPUT80 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5E9000)
		{
			// Signal: IO_OUTPUT1
			Holley_ECU.IO_OUTPUT1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5ED000)
		{
			// Signal: IO_OUTPUT2
			Holley_ECU.IO_OUTPUT2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5F1000)
		{
			// Signal: IO_OUTPUT3
			Holley_ECU.IO_OUTPUT3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5F5000)
		{
			// Signal: IO_OUTPUT4
			Holley_ECU.IO_OUTPUT4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5F9000)
		{
			// Signal: IO_OUTPUT5
			Holley_ECU.IO_OUTPUT5 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E5FD000)
		{
			// Signal: IO_OUTPUT6
			Holley_ECU.IO_OUTPUT6 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E601000)
		{
			// Signal: IO_OUTPUT7
			Holley_ECU.IO_OUTPUT7 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E605000)
		{
			// Signal: IO_OUTPUT8
			Holley_ECU.IO_OUTPUT8 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E609000)
		{
			// Signal: IO_OUTPUT9
			Holley_ECU.IO_OUTPUT9 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E60D000)
		{
			// Signal: IO_OUTPUT10
			Holley_ECU.IO_OUTPUT10 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E611000)
		{
			// Signal: IO_OUTPUT11
			Holley_ECU.IO_OUTPUT11 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E615000)
		{
			// Signal: IO_OUTPUT12
			Holley_ECU.IO_OUTPUT12 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E619000)
		{
			// Signal: IO_OUTPUT13
			Holley_ECU.IO_OUTPUT13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E61D000)
		{
			// Signal: IO_OUTPUT14
			Holley_ECU.IO_OUTPUT14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E621000)
		{
			// Signal: IO_OUTPUT15
			Holley_ECU.IO_OUTPUT15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E625000)
		{
			// Signal: IO_OUTPUT16
			Holley_ECU.IO_OUTPUT16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E629000)
		{
			// Signal: IO_OUTPUT17
			Holley_ECU.IO_OUTPUT17 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E62D000)
		{
			// Signal: IO_OUTPUT18
			Holley_ECU.IO_OUTPUT18 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E631000)
		{
			// Signal: IO_OUTPUT19
			Holley_ECU.IO_OUTPUT19 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E635000)
		{
			// Signal: IO_OUTPUT20
			Holley_ECU.IO_OUTPUT20 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E639000)
		{
			// Signal: IO_OUTPUT21
			Holley_ECU.IO_OUTPUT21 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E63D000)
		{
			// Signal: IO_OUTPUT22
			Holley_ECU.IO_OUTPUT22 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E641000)
		{
			// Signal: IO_OUTPUT23
			Holley_ECU.IO_OUTPUT23 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E645000)
		{
			// Signal: IO_OUTPUT24
			Holley_ECU.IO_OUTPUT24 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E649000)
		{
			// Signal: IO_OUTPUT25
			Holley_ECU.IO_OUTPUT25 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E64D000)
		{
			// Signal: IO_OUTPUT26
			Holley_ECU.IO_OUTPUT26 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E651000)
		{
			// Signal: IO_OUTPUT27
			Holley_ECU.IO_OUTPUT27 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E655000)
		{
			// Signal: IO_OUTPUT28
			Holley_ECU.IO_OUTPUT28 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E659000)
		{
			// Signal: IO_OUTPUT29
			Holley_ECU.IO_OUTPUT29 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E65D000)
		{
			// Signal: IO_OUTPUT30
			Holley_ECU.IO_OUTPUT30 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E661000)
		{
			// Signal: IO_OUTPUT31
			Holley_ECU.IO_OUTPUT31 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E665000)
		{
			// Signal: IO_OUTPUT32
			Holley_ECU.IO_OUTPUT32 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E669000)
		{
			// Signal: IO_OUTPUT33
			Holley_ECU.IO_OUTPUT33 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E66D000)
		{
			// Signal: IO_OUTPUT34
			Holley_ECU.IO_OUTPUT34 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E671000)
		{
			// Signal: IO_OUTPUT35
			Holley_ECU.IO_OUTPUT35 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E675000)
		{
			// Signal: IO_OUTPUT36
			Holley_ECU.IO_OUTPUT36 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E679000)
		{
			// Signal: IO_OUTPUT37
			Holley_ECU.IO_OUTPUT37 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E67D000)
		{
			// Signal: IO_OUTPUT38
			Holley_ECU.IO_OUTPUT38 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E681000)
		{
			// Signal: IO_OUTPUT39
			Holley_ECU.IO_OUTPUT39 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E685000)
		{
			// Signal: IO_OUTPUT40
			Holley_ECU.IO_OUTPUT40 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E689000)
		{
			// Signal: IO_OUTPUT41
			Holley_ECU.IO_OUTPUT41 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E68D000)
		{
			// Signal: IO_OUTPUT42
			Holley_ECU.IO_OUTPUT42 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E691000)
		{
			// Signal: IO_OUTPUT43
			Holley_ECU.IO_OUTPUT43 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E695000)
		{
			// Signal: IO_OUTPUT44
			Holley_ECU.IO_OUTPUT44 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E699000)
		{
			// Signal: IO_OUTPUT45
			Holley_ECU.IO_OUTPUT45 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E69D000)
		{
			// Signal: IO_OUTPUT46
			Holley_ECU.IO_OUTPUT46 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6A1000)
		{
			// Signal: IO_OUTPUT47
			Holley_ECU.IO_OUTPUT47 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6A5000)
		{
			// Signal: IO_OUTPUT48
			Holley_ECU.IO_OUTPUT48 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6A9000)
		{
			// Signal: IO_OUTPUT49
			Holley_ECU.IO_OUTPUT49 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6AD000)
		{
			// Signal: IO_OUTPUT50
			Holley_ECU.IO_OUTPUT50 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6B1000)
		{
			// Signal: IO_OUTPUT51
			Holley_ECU.IO_OUTPUT51 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6B5000)
		{
			// Signal: IO_OUTPUT52
			Holley_ECU.IO_OUTPUT52 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6B9000)
		{
			// Signal: IO_OUTPUT53
			Holley_ECU.IO_OUTPUT53 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6BD000)
		{
			// Signal: IO_OUTPUT54
			Holley_ECU.IO_OUTPUT54 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6C1000)
		{
			// Signal: IO_OUTPUT55
			Holley_ECU.IO_OUTPUT55 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6C5000)
		{
			// Signal: IO_OUTPUT56
			Holley_ECU.IO_OUTPUT56 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6C9000)
		{
			// Signal: IO_OUTPUT57
			Holley_ECU.IO_OUTPUT57 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6CD000)
		{
			// Signal: IO_OUTPUT58
			Holley_ECU.IO_OUTPUT58 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6D1000)
		{
			// Signal: IO_OUTPUT59
			Holley_ECU.IO_OUTPUT59 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6D5000)
		{
			// Signal: IO_OUTPUT60
			Holley_ECU.IO_OUTPUT60 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6D9000)
		{
			// Signal: IO_OUTPUT61
			Holley_ECU.IO_OUTPUT61 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6DD000)
		{
			// Signal: IO_OUTPUT62
			Holley_ECU.IO_OUTPUT62 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6E1000)
		{
			// Signal: FUEL_TABLE1_PERCENT
			Holley_ECU.FUEL_TABLE1_PERCENT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6E5000)
		{
			// Signal: FUEL_TABLE2_PERCENT
			Holley_ECU.FUEL_TABLE2_PERCENT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6E9000)
		{
			// Signal: FUEL_TABLE3_PERCENT
			Holley_ECU.FUEL_TABLE3_PERCENT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6ED000)
		{
			// Signal: SYSTEM_INJ_PPH13
			Holley_ECU.SYSTEM_INJ_PPH13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6F1000)
		{
			// Signal: SYSTEM_INJ_PPH14
			Holley_ECU.SYSTEM_INJ_PPH14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6F5000)
		{
			// Signal: SYSTEM_INJ_PPH15
			Holley_ECU.SYSTEM_INJ_PPH15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6F9000)
		{
			// Signal: SYSTEM_INJ_PPH16
			Holley_ECU.SYSTEM_INJ_PPH16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E6FD000)
		{
			// Signal: SYSTEM_INJ_PPH17
			Holley_ECU.SYSTEM_INJ_PPH17 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E701000)
		{
			// Signal: SYSTEM_INJ_PPH18
			Holley_ECU.SYSTEM_INJ_PPH18 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E705000)
		{
			// Signal: SYSTEM_INJ_PPH19
			Holley_ECU.SYSTEM_INJ_PPH19 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E709000)
		{
			// Signal: SYSTEM_INJ_PPH20
			Holley_ECU.SYSTEM_INJ_PPH20 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E70D000)
		{
			// Signal: SYSTEM_INJ_PPH21
			Holley_ECU.SYSTEM_INJ_PPH21 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E711000)
		{
			// Signal: SYSTEM_INJ_PPH22
			Holley_ECU.SYSTEM_INJ_PPH22 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E715000)
		{
			// Signal: SYSTEM_INJ_PPH23
			Holley_ECU.SYSTEM_INJ_PPH23 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E719000)
		{
			// Signal: SYSTEM_INJ_PPH24
			Holley_ECU.SYSTEM_INJ_PPH24 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E71D000)
		{
			// Signal: SYSTEM_INJ_PPH25
			Holley_ECU.SYSTEM_INJ_PPH25 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E721000)
		{
			// Signal: SYSTEM_INJ_PPH26
			Holley_ECU.SYSTEM_INJ_PPH26 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E725000)
		{
			// Signal: SYSTEM_INJ_PPH27
			Holley_ECU.SYSTEM_INJ_PPH27 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E729000)
		{
			// Signal: SYSTEM_INJ_PPH28
			Holley_ECU.SYSTEM_INJ_PPH28 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E72D000)
		{
			// Signal: SYSTEM_INJ_PW13
			Holley_ECU.SYSTEM_INJ_PW13 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E731000)
		{
			// Signal: SYSTEM_INJ_PW14
			Holley_ECU.SYSTEM_INJ_PW14 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E735000)
		{
			// Signal: SYSTEM_INJ_PW15
			Holley_ECU.SYSTEM_INJ_PW15 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E739000)
		{
			// Signal: SYSTEM_INJ_PW16
			Holley_ECU.SYSTEM_INJ_PW16 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E73D000)
		{
			// Signal: SYSTEM_INJ_PW17
			Holley_ECU.SYSTEM_INJ_PW17 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E741000)
		{
			// Signal: SYSTEM_INJ_PW18
			Holley_ECU.SYSTEM_INJ_PW18 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E745000)
		{
			// Signal: SYSTEM_INJ_PW19
			Holley_ECU.SYSTEM_INJ_PW19 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E749000)
		{
			// Signal: SYSTEM_INJ_PW20
			Holley_ECU.SYSTEM_INJ_PW20 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E74D000)
		{
			// Signal: SYSTEM_INJ_PW21
			Holley_ECU.SYSTEM_INJ_PW21 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E751000)
		{
			// Signal: SYSTEM_INJ_PW22
			Holley_ECU.SYSTEM_INJ_PW22 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E755000)
		{
			// Signal: SYSTEM_INJ_PW23
			Holley_ECU.SYSTEM_INJ_PW23 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E759000)
		{
			// Signal: SYSTEM_INJ_PW24
			Holley_ECU.SYSTEM_INJ_PW24 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E75D000)
		{
			// Signal: SYSTEM_INJ_PW25
			Holley_ECU.SYSTEM_INJ_PW25 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E761000)
		{
			// Signal: SYSTEM_INJ_PW26
			Holley_ECU.SYSTEM_INJ_PW26 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E765000)
		{
			// Signal: SYSTEM_INJ_PW27
			Holley_ECU.SYSTEM_INJ_PW27 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E769000)
		{
			// Signal: SYSTEM_INJ_PW28
			Holley_ECU.SYSTEM_INJ_PW28 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E76D000)
		{
			// Signal: SYSTEM_STAGING_INPUT1
			Holley_ECU.SYSTEM_STAGING_INPUT1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E771000)
		{
			// Signal: SYSTEM_STAGING_INPUT2
			Holley_ECU.SYSTEM_STAGING_INPUT2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E775000)
		{
			// Signal: SYSTEM_STAGING_OUTPUT
			Holley_ECU.SYSTEM_STAGING_OUTPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E779000)
		{
			// Signal: TRACTION_SMARTDROP
			Holley_ECU.TRACTION_SMARTDROP = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E77D000)
		{
			// Signal: TRACTION_TIMINGRETARD
			Holley_ECU.TRACTION_TIMINGRETARD = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E781000)
		{
			// Signal: TRACTION_N2ODECREASE
			Holley_ECU.TRACTION_N2ODECREASE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E785000)
		{
			// Signal: TRACTION_BOOSTDECREASE
			Holley_ECU.TRACTION_BOOSTDECREASE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E789000)
		{
			// Signal: TRACTION_DBWDECREASE
			Holley_ECU.TRACTION_DBWDECREASE = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E78D000)
		{
			// Signal: TRACTION_DSTIMINGOFFSET
			Holley_ECU.TRACTION_DSTIMINGOFFSET = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E791000)
		{
			// Signal: TRACTION_CSTIMINGOFFSET
			Holley_ECU.TRACTION_CSTIMINGOFFSET = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E795000)
		{
			// Signal: TRACTION_DSREVLIMIT
			Holley_ECU.TRACTION_DSREVLIMIT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E799000)
		{
			// Signal: TRACTION_CSREVLIMIT
			Holley_ECU.TRACTION_CSREVLIMIT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E79D000)
		{
			// Signal: TRACTION_TCTIME
			Holley_ECU.TRACTION_TCTIME = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7A1000)
		{
			// Signal: TRACTION_TCLAUNCHINPUT
			Holley_ECU.TRACTION_TCLAUNCHINPUT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7A5000)
		{
			// Signal: DIFUEL_GRAMSPERCYLINDER
			Holley_ECU.DIFUEL_GRAMSPERCYLINDER = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7A9000)
		{
			// Signal: VVT_DESIREDINTAKECAMPOS
			Holley_ECU.VVT_DESIREDINTAKECAMPOS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7AD000)
		{
			// Signal: VVT_ACTUALINTAKECAMPOS
			Holley_ECU.VVT_ACTUALINTAKECAMPOS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7B1000)
		{
			// Signal: VVT_INTAKESOLDUTY
			Holley_ECU.VVT_INTAKESOLDUTY = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7B5000)
		{
			// Signal: VVT_DESIREDEXHAUSTCAMPOS
			Holley_ECU.VVT_DESIREDEXHAUSTCAMPOS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7B9000)
		{
			// Signal: VVT_ACTUALEXHAUSTCAMPOS
			Holley_ECU.VVT_ACTUALEXHAUSTCAMPOS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7BD000)
		{
			// Signal: VVT_EXHAUSTSOLDUTY
			Holley_ECU.VVT_EXHAUSTSOLDUTY = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7C1000)
		{
			// Signal: TRANS_GOVERNORPRESSUREPSIACTUAL
			Holley_ECU.TRANS_GOVERNORPRESSUREPSIACTUAL = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7C5000)
		{
			// Signal: TRANS_GOVERNORPRESSUREPSITARGET
			Holley_ECU.TRANS_GOVERNORPRESSUREPSITARGET = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7C9000)
		{
			// Signal: TRANS_LINEPRESSUREPSIACTUAL
			Holley_ECU.TRANS_LINEPRESSUREPSIACTUAL = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7CD000)
		{
			// Signal: RACE_LAUNCH_STATUS
			Holley_ECU.RACE_LAUNCH_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7D1000)
		{
			// Signal: RACE_SPOOL_ASSIST_OUTPUT_STATUS2
			Holley_ECU.RACE_SPOOL_ASSIST_OUTPUT_STATUS2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7D5000)
		{
			// Signal: RACE_SHIFT_SINGLE_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_SINGLE_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7D9000)
		{
			// Signal: RACE_SHIFT_1_2_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_1_2_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7DD000)
		{
			// Signal: RACE_SHIFT_2_3_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_2_3_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7E1000)
		{
			// Signal: RACE_SHIFT_3_4_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_3_4_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7E5000)
		{
			// Signal: RACE_SHIFT_4_5_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_4_5_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7E9000)
		{
			// Signal: RACE_SHIFT_5_6_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_5_6_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7ED000)
		{
			// Signal: RACE_SHIFT_6_7_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_6_7_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7F1000)
		{
			// Signal: RACE_SHIFT_7_8_OUTPUT_STATUS
			Holley_ECU.RACE_SHIFT_7_8_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7F5000)
		{
			// Signal: RACE_SHIFT_OVERRIDE_STATUS
			Holley_ECU.RACE_SHIFT_OVERRIDE_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7F9000)
		{
			// Signal: RACE_SHIFT_MASTER_ENABLE_STATUS
			Holley_ECU.RACE_SHIFT_MASTER_ENABLE_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E7FD000)
		{
			// Signal: RACE_SHIFT_IGNITION_CUT_STATUS
			Holley_ECU.RACE_SHIFT_IGNITION_CUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E801000)
		{
			// Signal: RACE_SHIFT_TIMING_MODIFIER
			Holley_ECU.RACE_SHIFT_TIMING_MODIFIER = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E805000)
		{
			// Signal: RACE_SHIFT_TIMER
			Holley_ECU.RACE_SHIFT_TIMER = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E809000)
		{
			// Signal: RACE_CONVERTER_LOCK1
			Holley_ECU.RACE_CONVERTER_LOCK1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E80D000)
		{
			// Signal: RACE_CONVERTER_LOCK2
			Holley_ECU.RACE_CONVERTER_LOCK2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E811000)
		{
			// Signal: RACE_CONVERTER_LOCK3
			Holley_ECU.RACE_CONVERTER_LOCK3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E815000)
		{
			// Signal: RACE_CONVERTER_LOCK4
			Holley_ECU.RACE_CONVERTER_LOCK4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E819000)
		{
			// Signal: RACE_CONVERTER_LOCK_DISABLE_STAT
			Holley_ECU.RACE_CONVERTER_LOCK_DISABLE_STAT = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E81D000)
		{
			// Signal: RACE_SPOOL_ASSIST_OUTPUT_STATUS
			Holley_ECU.RACE_SPOOL_ASSIST_OUTPUT_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E821000)
		{
			// Signal: RACE_TRANS_DUMP_VALVE1
			Holley_ECU.RACE_TRANS_DUMP_VALVE1 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E825000)
		{
			// Signal: RACE_TRANS_DUMP_VALVE2
			Holley_ECU.RACE_TRANS_DUMP_VALVE2 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E829000)
		{
			// Signal: RACE_TRANS_DUMP_VALVE3
			Holley_ECU.RACE_TRANS_DUMP_VALVE3 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E82D000)
		{
			// Signal: RACE_TRANS_DUMP_VALVE4
			Holley_ECU.RACE_TRANS_DUMP_VALVE4 = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		if ((Message.arbitration_id & 0x1FFFF000) == 0x1E831000)
		{
			// Signal: RACE_TRANS_DUMP_DISABLE_STATUS
			Holley_ECU.RACE_TRANS_DUMP_DISABLE_STATUS = (float)dbc_decode(Message.data, 24, 32, true, DBC_FLOAT, 1, 0, 3);

			// Signal (conventional): Status
			Holley_ECU.Status = (uint8_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);

			// Signal (enum override): Status_enum
			Holley_ECU.Status_enum = (Status_t)dbc_decode(Message.data, 56, 8, true, DBC_UNSIGNED, 1, 0, 3);
		}

		// ################ End Generated CAN Code ################
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
