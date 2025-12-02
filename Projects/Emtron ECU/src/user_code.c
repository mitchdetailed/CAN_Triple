/*
 * user_code.c - All User Code should be applied here unless specified otherwise.
 *
 */

/* Generic Example for Reading in Emtron_'s Common Tx DataSet on CAN_1
 * You will need to write code for what you want to do with the information.
 *
 *
 *
 *
 *
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

/* Variable Declarations */
uint32_t serialnumber;
CAN_ErrorCounts errors;

uint32_t Emtron_EngineSpeed;
float Emtron_ManifoldPressure;
float Emtron_EngineTemperature;
float Emtron_InletAirTemperature;
float Emtron_ThrottlePosition;
float Emtron_ChargeTemperature;
int32_t Emtron_GearPositionECU;
float Emtron_BatteryVoltageECU;
float Emtron_OilPressure;
float Emtron_OilTemperature;
float Emtron_FuelPressure;
float Emtron_FuelTemperature;
float Emtron_ExhaustManifoldPressure1;
float Emtron_FuelPressure1DiffOffset;
float Emtron_CrankcasePressure;
float Emtron_CoolantPressure;
float Emtron_Lambda1;
float Emtron_Lambda2;
float Emtron_LambdaTarget;
float Emtron_DriveSpeed;
float Emtron_Sensor1FuelShortTerm;
float Emtron_Sensor2FuelShortTerm;
float Emtron_Sensor1FuelLongTerm;
float Emtron_Sensor2FuelLongTerm;
float Emtron_InjectorDutyCycle;
float Emtron_IgnitionAngle;
float Emtron_BarometricPressure;
float Emtron_ECUTemperature;
float Emtron_dTPS;
uint32_t Emtron_dRPM;
float Emtron_PercentageCutFuel;
float Emtron_PercentageCutIgnition;
float Emtron_EthanolContent;
float Emtron_GForceLatECU;
float Emtron_GForceLongECU;
float Emtron_GForceVertECU;
uint32_t Emtron_CrankSyncErrorCount;
uint32_t Emtron_CrankToothErrorCount;
float Emtron_SyncPositionSingle;
uint32_t Emtron_DTCErrorCount;
uint32_t Emtron_KeypadButton1;
uint32_t Emtron_KeypadButton2;
uint32_t Emtron_KeypadButton3;
uint32_t Emtron_KeypadButton4;
uint32_t Emtron_KeypadButton5;
uint32_t Emtron_KeypadButton6;
uint32_t Emtron_KeypadButton7;
uint32_t Emtron_KeypadButton8;
uint32_t Emtron_AntiLagStatus;
uint32_t Emtron_LaunchControlStatus;
uint32_t Emtron_RollingLaunchStatus;
uint32_t Emtron_TractionControlStatus;
uint32_t Emtron_DifferentialControlStatus;
uint32_t Emtron_GearshiftControlStatus;
uint32_t Emtron_NitrousControlStatus;
uint32_t Emtron_TransmissionBrakeControlStatus;
uint32_t Emtron_HighestPriorityFCut;
uint32_t Emtron_HighestPriorityICut;
uint32_t Emtron_LaunchSwitch;
uint32_t Emtron_TractionSwitch;
uint32_t Emtron_EngineOilPressureLimitStatus;
uint32_t Emtron_EngineTempLimitStatus;
uint32_t Emtron_FuelPresDiffLimitStatus;
uint32_t Emtron_EGTLimitStatus;
float Emtron_ExhaustTempCyl1;
float Emtron_ExhaustTempCyl2;
float Emtron_ExhaustTempCyl3;
float Emtron_ExhaustTempCyl4;
float Emtron_ExhaustTempCyl5;
float Emtron_ExhaustTempCyl6;
float Emtron_ExhaustTempCyl7;
float Emtron_ExhaustTempCyl8;
float Emtron_EGTPeak;
float Emtron_FuelUsed;
float Emtron_EngineTorque;
uint32_t Emtron_EnginePower;
uint32_t Emtron_EngineSpeedLimit1;
uint32_t Emtron_LaunchRPMTarget;
float Emtron_MAPLimit1;
float Emtron_GroundSpeedLimit1;

/* End Variable Declarations */

/* Startup Functions */
void events_Startup()
{
	setupCANbus(CAN_1, 1000000, NORMAL_MODE); // Emtron CAN Bus
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

	// Do nothing....
}

void onReceive(CAN_Message Message)
{
	// What do you want to do when you receive a CAN message.. ?
	if (Message.Bus == CAN_1)
	{
		if (Message.arbitration_id == 0x4E2)
		{
			// Signal: EngineSpeed
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_EngineSpeed = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: ManifoldPressure
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_ManifoldPressure = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, 0, 3);

			// Signal: EngineTemperature
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_EngineTemperature = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, -50, 3);

			// Signal: InletAirTemperature
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_InletAirTemperature = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, -50, 3);
		}

		if (Message.arbitration_id == 0x4E3)
		{
			// Signal: ThrottlePosition
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_ThrottlePosition = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, -100, 3);

			// Signal: ChargeTemperature
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_ChargeTemperature = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, -50, 3);

			// Signal: GearPositionECU
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_GearPositionECU = process_int_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 1, -10);

			// Signal: BatteryVoltageECU
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_BatteryVoltageECU = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.001, 0, 3);
		}

		if (Message.arbitration_id == 0x4E4)
		{
			// Signal: OilPressure
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_OilPressure = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, 0, 3);

			// Signal: OilTemperature
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_OilTemperature = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, -50, 3);

			// Signal: FuelPressure
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_FuelPressure = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, 0, 3);

			// Signal: FuelTemperature
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_FuelTemperature = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, -50, 3);
		}

		if (Message.arbitration_id == 0x4E5)
		{
			// Signal: ExhaustManifoldPressure1
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_ExhaustManifoldPressure1 = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, 0, 3);

			// Signal: FuelPressure1DiffOffset
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_FuelPressure1DiffOffset = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, -1000, 3);

			// Signal: CrankcasePressure
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_CrankcasePressure = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, 0, 3);

			// Signal: CoolantPressure
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_CoolantPressure = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, 0, 3);
		}

		if (Message.arbitration_id == 0x4E6)
		{
			// Signal: Lambda1
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_Lambda1 = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.001, 0, 3);

			// Signal: Lambda2
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_Lambda2 = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.001, 0, 3);

			// Signal: LambdaTarget
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_LambdaTarget = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.001, 0, 3);

			// Signal: DriveSpeed
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_DriveSpeed = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, 0, 3);
		}

		if (Message.arbitration_id == 0x4E7)
		{
			// Signal: Sensor1FuelShortTerm
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_Sensor1FuelShortTerm = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.01, -100, 3);

			// Signal: Sensor2FuelShortTerm
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_Sensor2FuelShortTerm = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.01, -100, 3);

			// Signal: Sensor1FuelLongTerm
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_Sensor1FuelLongTerm = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.01, -100, 3);

			// Signal: Sensor2FuelLongTerm
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_Sensor2FuelLongTerm = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.01, -100, 3);
		}

		if (Message.arbitration_id == 0x4E8)
		{
			// Signal: InjectorDutyCycle
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_InjectorDutyCycle = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, 0, 3);

			// Signal: IgnitionAngle
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_IgnitionAngle = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, -100, 3);

			// Signal: BarometricPressure
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_BarometricPressure = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, 0, 3);

			// Signal: ECUTemperature
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_ECUTemperature = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, -50, 3);
		}

		if (Message.arbitration_id == 0x4E9)
		{
			// Signal: dTPS
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_dTPS = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, -100, 3);

			// Signal: dRPM
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_dRPM = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: PercentageCutFuel
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_PercentageCutFuel = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, 0, 3);

			// Signal: PercentageCutIgnition
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_PercentageCutIgnition = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, 0, 3);
		}

		if (Message.arbitration_id == 0x4EA)
		{
			// Signal: EthanolContent
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_EthanolContent = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, 0, 3);

			// Signal: GForceLatECU
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_GForceLatECU = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.01, -10, 3);

			// Signal: GForceLongECU
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_GForceLongECU = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.01, -10, 3);

			// Signal: GForceVertECU
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_GForceVertECU = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.01, -10, 3);
		}

		if (Message.arbitration_id == 0x4EB)
		{
			// Signal: CrankSyncErrorCount
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_CrankSyncErrorCount = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: CrankToothErrorCount
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_CrankToothErrorCount = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: SyncPositionSingle
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_SyncPositionSingle = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, 0, 3);

			// Signal: DTCErrorCount
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_DTCErrorCount = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4EC)
		{
			// Signal: EmtronKeypadButton1
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_KeypadButton1 = process_unsigned_int_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, 1, 1);

			// Signal: EmtronKeypadButton2
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_KeypadButton2 = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: EmtronKeypadButton3
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_KeypadButton3 = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF);

			// Signal: EmtronKeypadButton4
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_KeypadButton4 = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4ED)
		{
			// Signal: EmtronKeypadButton5
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_KeypadButton5 = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: EmtronKeypadButton6
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_KeypadButton6 = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: EmtronKeypadButton7
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_KeypadButton7 = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF);

			// Signal: EmtronKeypadButton8
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_KeypadButton8 = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4EE)
		{
			// Signal: AntiLagStatus
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_AntiLagStatus = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: LaunchControlStatus
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_LaunchControlStatus = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: RollingLaunchStatus
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_RollingLaunchStatus = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF);

			// Signal: TractionControlStatus
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_TractionControlStatus = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4EF)
		{
			// Signal: DifferentialControlStatus
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_DifferentialControlStatus = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: GearshiftControlStatus
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_GearshiftControlStatus = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: NitrousControlStatus
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_NitrousControlStatus = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF);

			// Signal: TransmissionBrakeControlStatus
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_TransmissionBrakeControlStatus = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4F0)
		{
			// Signal: HighestPriorityFCut
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_HighestPriorityFCut = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: HighestPriorityICut
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_HighestPriorityICut = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: LaunchSwitch
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_LaunchSwitch = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF);

			// Signal: TractionSwitch
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_TractionSwitch = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4F1)
		{
			// Signal: EngineOilPressureLimitStatus
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_EngineOilPressureLimitStatus = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: EngineTempLimitStatus
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_EngineTempLimitStatus = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: FuelPresDiffLimitStatus
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_FuelPresDiffLimitStatus = process_raw_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF);

			// Signal: EGTLimitStatus
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_EGTLimitStatus = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4F2)
		{
			// Signal: ExhaustTempCyl1
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl1 = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, -50, 3);

			// Signal: ExhaustTempCyl2
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl2 = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, -50, 3);

			// Signal: ExhaustTempCyl3
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl3 = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, -50, 3);

			// Signal: ExhaustTempCyl4
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl4 = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, -50, 3);
		}

		if (Message.arbitration_id == 0x4F3)
		{
			// Signal: ExhaustTempCyl5
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl5 = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, -50, 3);

			// Signal: ExhaustTempCyl6
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl6 = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.1, -50, 3);

			// Signal: ExhaustTempCyl7
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl7 = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, -50, 3);

			// Signal: ExhaustTempCyl8
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_ExhaustTempCyl8 = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, -50, 3);
		}

		if (Message.arbitration_id == 0x4F4)
		{
			// Signal: EGTPeak
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_EGTPeak = process_float_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF, false, 0.1, -50, 3);

			// Signal: FuelUsed
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_FuelUsed = process_float_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF, false, 0.01, 0, 3);

			// Signal: EngineTorque
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_EngineTorque = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, -1000, 3);

			// Signal: EnginePower
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_EnginePower = process_raw_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF);
		}

		if (Message.arbitration_id == 0x4F5)
		{
			// Signal: EngineSpeedLimit1
			// Start bit: 0, Length: 16, Byte Order: little
			Emtron_EngineSpeedLimit1 = process_raw_value(((uint32_t)Message.data[1] << 8) | (uint32_t)Message.data[0], 0xFFFF);

			// Signal: LaunchRPMTarget
			// Start bit: 16, Length: 16, Byte Order: little
			Emtron_LaunchRPMTarget = process_raw_value(((uint32_t)Message.data[3] << 8) | (uint32_t)Message.data[2], 0xFFFF);

			// Signal: MAPLimit1
			// Start bit: 32, Length: 16, Byte Order: little
			Emtron_MAPLimit1 = process_float_value(((uint32_t)Message.data[5] << 8) | (uint32_t)Message.data[4], 0xFFFF, false, 0.1, 0, 3);

			// Signal: GroundSpeedLimit1
			// Start bit: 48, Length: 16, Byte Order: little
			Emtron_GroundSpeedLimit1 = process_float_value(((uint32_t)Message.data[7] << 8) | (uint32_t)Message.data[6], 0xFFFF, false, 0.1, 0, 3);
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
	toggleLED(LED_1); // Toggles LED on Board in enclosure for Sanity checking.
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
}