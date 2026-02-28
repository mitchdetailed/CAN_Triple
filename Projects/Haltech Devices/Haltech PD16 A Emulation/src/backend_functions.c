/*
 * backend_functions.c
 *
 */

// #include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>
#include "user_code.h"
#include "backend_functions.h"
#include "main.h"
#include "stm32g4xx_hal.h"

struct q_CAN1_Msg
{
	bool EXT_ID;
	uint32_t arb_id;
	uint8_t dlc;
	uint8_t data[CAN1_DATALENGTH];
};

struct q_CAN2_Msg
{
	bool EXT_ID;
	uint32_t arb_id;
	uint8_t dlc;
	uint8_t data[CAN2_DATALENGTH];
};

struct q_CAN3_Msg
{
	bool EXT_ID;
	uint32_t arb_id;
	uint8_t dlc;
	uint8_t data[CAN3_DATALENGTH];
};

// CAN RX Queue
uint16_t can1_Rx_qHead = 0;
uint16_t can1_Rx_qTail = 0;
struct q_CAN1_Msg can1_Rx_qData[CAN1_RX_MSG_BUFFER_SIZE];
uint16_t can1_Rx_qNextHead = 0;
uint16_t can1_Rx_qElements = 0;

// CAN 1 TX Queue
uint16_t can1_Tx_qHead = 0;
uint16_t can1_Tx_qTail = 0;
struct q_CAN1_Msg can1_Tx_qData[CAN1_TX_MSG_BUFFER_SIZE];
uint16_t can1_Tx_qNextHead = 0;
uint16_t can1_Tx_qElements = 0;

// CAN 2 RX Queue
uint16_t can2_Rx_qHead = 0;
uint16_t can2_Rx_qTail = 0;
struct q_CAN2_Msg can2_Rx_qData[CAN2_RX_MSG_BUFFER_SIZE];
uint16_t can2_Rx_qNextHead = 0;
uint16_t can2_Rx_qElements = 0;

// CAN 2 TX Queue
uint16_t can2_Tx_qHead = 0;
uint16_t can2_Tx_qTail = 0;
struct q_CAN2_Msg can2_Tx_qData[CAN2_TX_MSG_BUFFER_SIZE];
uint16_t can2_Tx_qNextHead = 0;
uint16_t can2_Tx_qElements = 0;

// CAN 3 RX Queue
uint16_t can3_Rx_qHead = 0;
uint16_t can3_Rx_qTail = 0;
struct q_CAN3_Msg can3_Rx_qData[CAN3_RX_MSG_BUFFER_SIZE];
uint16_t can3_Rx_qNextHead = 0;
uint16_t can3_Rx_qElements = 0;

// CAN 3 TX Queue
uint16_t can3_Tx_qHead = 0;
uint16_t can3_Tx_qTail = 0;
struct q_CAN3_Msg can3_Tx_qData[CAN3_TX_MSG_BUFFER_SIZE];
uint16_t can3_Tx_qNextHead = 0;
uint16_t can3_Tx_qElements = 0;

bool Can1_RxMsgEXT_ID;
uint32_t Can1_RxMsgID;
uint8_t Can1_RxMsgDLC;
uint8_t Can1_RxMsgData[CAN1_DATALENGTH];

bool Can2_RxMsgEXT_ID;
uint32_t Can2_RxMsgID;
uint8_t Can2_RxMsgDLC;
uint8_t Can2_RxMsgData[CAN2_DATALENGTH];

bool Can3_RxMsgEXT_ID;
uint32_t Can3_RxMsgID;
uint8_t Can3_RxMsgDLC;
uint8_t Can3_RxMsgData[CAN3_DATALENGTH];

FDCAN_RxHeaderTypeDef CAN1_RxHeader;
uint8_t CAN1_RxData[CAN1_DATALENGTH];
FDCAN_TxHeaderTypeDef CAN1_TxHeader;
uint8_t CAN1_TxData[CAN1_DATALENGTH];

FDCAN_RxHeaderTypeDef CAN2_RxHeader;
uint8_t CAN2_RxData[CAN2_DATALENGTH];
FDCAN_TxHeaderTypeDef CAN2_TxHeader;
uint8_t CAN2_TxData[CAN2_DATALENGTH];

FDCAN_RxHeaderTypeDef CAN3_RxHeader;
uint8_t CAN3_RxData[CAN3_DATALENGTH];
FDCAN_TxHeaderTypeDef CAN3_TxHeader;
uint8_t CAN3_TxData[CAN3_DATALENGTH];

bool storecompleted = false;

StringArray array0 = {.array = {0}, .length = 0};
StringArray array1 = {.array = {0}, .length = 0};
uint8_t uart_array = 0;
bool uart_sending = false;

uint16_t can1Reset_counter = 0; // Define the variable
uint16_t can2Reset_counter = 0; // Define the variable
uint16_t can3Reset_counter = 0; // Define the variable

/**
 * \brief Converts a HAL FDCAN DataLength code to actual byte count.
 * The HAL uses encoded values for FD frames: 9->12, 10->16, 11->20, 12->24, 13->32, 14->48, 15->64.
 * For classic CAN (0-8) the code equals the byte count.
 */
static inline uint8_t fdcan_dlc_to_bytes(uint32_t dlc_code)
{
	static const uint8_t dlc_table[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
	return (dlc_code < 16U) ? dlc_table[dlc_code] : 64U;
}

/**
 * \brief Converts actual byte count to HAL FDCAN DataLength code.
 * Rounds up to the nearest valid FD DLC if an intermediate value is given.
 */
static inline uint32_t bytes_to_fdcan_dlc(uint8_t bytes)
{
	if (bytes <= 8U)  return (uint32_t)bytes;
	if (bytes <= 12U) return 9U;
	if (bytes <= 16U) return 10U;
	if (bytes <= 20U) return 11U;
	if (bytes <= 24U) return 12U;
	if (bytes <= 32U) return 13U;
	if (bytes <= 48U) return 14U;
	return 15U; /* 64 bytes */
}

/**
 * \brief Calculates optimal CAN bit timing parameters for a given bitrate.
 *
 * Targets the following sample points based on bitrate:
 *   <= 1 Mbit/s  ->  87.5%
 *   <= 2 Mbit/s  ->  80.0%
 *   >  2 Mbit/s  ->  75.0%
 *
 * Exhaustively searches every prescaler (1..maxPrescaler) and every valid
 * TQ count (12..32) to find the combination that minimises a weighted score
 * of bitrate error and sample-point error.  TQ is constrained to 12..32 to
 * ensure the SyncJumpWidth remains a meaningful fraction of the bit time
 * (good noise immunity), with a preference for TQ values close to 16 for
 * optimal resolution.  If no combination lands within 1% bitrate error
 * (e.g. 800 kbps on a 170 MHz clock) the closest achievable bitrate wins.
 *
 * \param apb1clock     Peripheral clock in Hz.
 * \param bitrate       Target bitrate in bits per second.
 * \param maxPrescaler  Maximum prescaler allowed (512 for nominal, 32 for data).
 * \param out_prescaler Output prescaler value.
 * \param out_timeSeg1  Output TimeSeg1 value.
 * \param out_timeSeg2  Output TimeSeg2 value.
 */
static void calculateBitTiming(uint32_t apb1clock, uint32_t bitrate, uint32_t maxPrescaler,
								uint32_t *out_prescaler, uint32_t *out_timeSeg1, uint32_t *out_timeSeg2)
{
	/* Select target sample point based on bitrate range */
	float targetSP;
	if (bitrate <= 1000000UL)
		targetSP = 0.875f; /* 87.5% for <= 1 Mbit/s */
	else if (bitrate <= 2000000UL)
		targetSP = 0.800f; /* 80.0% for <= 2 Mbit/s */
	else
		targetSP = 0.750f; /* 75.0% for >  2 Mbit/s */

	/* Constrain total TQ to 12..32 for both nominal and data phases.
	 * This keeps the SyncJumpWidth (1 TQ) a meaningful fraction of the bit
	 * time and matches standard CAN controller recommendations.
	 * totalTQ = 1 (sync) + TimeSeg1 + TimeSeg2
	 */
	const uint32_t minTQ = 12;
	const uint32_t maxTQ = 32;

	/* Safe fallback – will be overwritten on the first iteration */
	uint32_t bestPrescaler = 1;
	uint32_t bestSeg1      = 13;
	uint32_t bestSeg2      = 2;
	float    bestScore     = 1e9f;
	uint32_t bestTQ        = 0;

	/* Brute-force search: try every prescaler × TQ combination.
	 *
	 *   Bitrate  = apb1clock / (prescaler * totalTQ)
	 *   SamplePt = (1 + TimeSeg1) / totalTQ
	 *
	 * Score = spError * 10 + brError
	 * Combinations within 1% bitrate error score much better thanks to the
	 * brPenalty, so they are always preferred over out-of-tolerance ones.
	 * Ties (identical score) are broken by preferring TQ closest to 16.
	 */
	for (uint32_t pres = 1; pres <= maxPrescaler; pres++)
	{
		for (uint32_t tq = minTQ; tq <= maxTQ; tq++)
		{
			/* Bitrate error for this prescaler + TQ */
			float actualBR = (float)apb1clock / ((float)pres * (float)tq);
			float brError  = actualBR - (float)bitrate;
			if (brError < 0.0f) brError = -brError;
			brError /= (float)bitrate;

			/* Compute TimeSeg1 that lands closest to the target sample point:
			 *   SP = (1 + seg1) / tq  =>  seg1 = round(SP * tq) - 1
			 */
			uint32_t seg1 = (uint32_t)(targetSP * (float)tq + 0.5f) - 1;
			if (seg1 < 1)      seg1 = 1;
			if (seg1 > tq - 2) seg1 = tq - 2;
			uint32_t seg2 = tq - 1 - seg1;
			if (seg2 < 1)
			{
				seg2 = 1;
				seg1 = tq - 2;
			}

			float actualSP = (float)(1 + seg1) / (float)tq;
			float spError  = actualSP - targetSP;
			if (spError < 0.0f) spError = -spError;

			/* Heavy penalty for >1% bitrate error so in-tolerance solutions
			 * always win, but the best out-of-tolerance option is kept as
			 * a fallback rather than leaving defaults in place. */
			float brPenalty = (brError > 0.01f) ? (brError * 100.0f) : brError;
			float score     = spError * 10.0f + brPenalty;

			/* Tie-break: prefer TQ closest to 16 (optimal resolution without
			 * sacrificing SyncJumpWidth effectiveness). */
			uint32_t tqDist     = (tq > 16) ? (tq - 16) : (16 - tq);
			uint32_t bestTQDist = (bestTQ > 16) ? (bestTQ - 16) : (16 - bestTQ);

			if (score < bestScore || (fabs(score - bestScore) < 0.0001f && tqDist < bestTQDist))
			{
				bestScore     = score;
				bestPrescaler = pres;
				bestSeg1      = seg1;
				bestSeg2      = seg2;
				bestTQ        = tq;
			}
		}
	}

	*out_prescaler = bestPrescaler;
	*out_timeSeg1  = bestSeg1;
	*out_timeSeg2  = bestSeg2;
}

/**
 * \brief Sets CANbus Bitrate
 * \param bus CAN_1, CAN_2, or CAN_3.
 * \param mainBitrate Bitrate of CANbus in bits per second.
 * \param mode "NORMAL_MODE" or "LISTEN_ONLY"
 * \return 0 if no errors, 1 for any error
 */
uint8_t setupCANbus(CAN_Bus bus, uint32_t mainBitrate, CAN_Mode mode)
{
	uint8_t returnval = 0;
	uint32_t apb1clock = HAL_RCC_GetPCLK1Freq();

	/* Calculate nominal timing (prescaler max 512) and data timing (prescaler max 32) */
	uint32_t nomPrescaler, nomSeg1, nomSeg2;
	uint32_t datPrescaler, datSeg1, datSeg2;
	calculateBitTiming(apb1clock, mainBitrate, 512, &nomPrescaler, &nomSeg1, &nomSeg2);
	calculateBitTiming(apb1clock, mainBitrate,  32, &datPrescaler, &datSeg1, &datSeg2);

	/* SJW = min(Seg2, 4) – matches resync capability to the phase buffer */
	uint32_t nomSJW = (nomSeg2 < 4) ? nomSeg2 : 4;
	uint32_t datSJW = (datSeg2 < 4) ? datSeg2 : 4;

	if ((bus & CAN_1) == CAN_1)
	{
		hfdcan1.Instance = FDCAN1;
		hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
		if (mode == NORMAL_MODE)
		{
			hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
		}
		else if (mode == LISTEN_ONLY)
		{
			hfdcan1.Init.Mode = FDCAN_MODE_BUS_MONITORING;
		}
		hfdcan1.Init.AutoRetransmission = ENABLE;
		hfdcan1.Init.TransmitPause = DISABLE;
		hfdcan1.Init.ProtocolException = ENABLE;
		hfdcan1.Init.NominalPrescaler = nomPrescaler;
		hfdcan1.Init.NominalSyncJumpWidth = nomSJW;
		hfdcan1.Init.NominalTimeSeg1 = nomSeg1;
		hfdcan1.Init.NominalTimeSeg2 = nomSeg2;
		hfdcan1.Init.DataPrescaler = datPrescaler;
		hfdcan1.Init.DataSyncJumpWidth = datSJW;
		hfdcan1.Init.DataTimeSeg1 = datSeg1;
		hfdcan1.Init.DataTimeSeg2 = datSeg2;
		hfdcan1.Init.StdFiltersNbr = 0;
		hfdcan1.Init.ExtFiltersNbr = 0;
		hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
		{
			returnval = 1;
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		hfdcan2.Instance = FDCAN2;
		hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
		if (mode == NORMAL_MODE)
		{
			hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
		}
		else if (mode == LISTEN_ONLY)
		{
			hfdcan2.Init.Mode = FDCAN_MODE_BUS_MONITORING;
		}
		hfdcan2.Init.AutoRetransmission = ENABLE;
		hfdcan2.Init.TransmitPause = DISABLE;
		hfdcan2.Init.ProtocolException = ENABLE;
		hfdcan2.Init.NominalPrescaler = nomPrescaler;
		hfdcan2.Init.NominalSyncJumpWidth = nomSJW;
		hfdcan2.Init.NominalTimeSeg1 = nomSeg1;
		hfdcan2.Init.NominalTimeSeg2 = nomSeg2;
		hfdcan2.Init.DataPrescaler = datPrescaler;
		hfdcan2.Init.DataSyncJumpWidth = datSJW;
		hfdcan2.Init.DataTimeSeg1 = datSeg1;
		hfdcan2.Init.DataTimeSeg2 = datSeg2;
		hfdcan2.Init.StdFiltersNbr = 0;
		hfdcan2.Init.ExtFiltersNbr = 0;
		hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
		{
			returnval = 1;
		}
		// Debug // 
		/*
		uint32_t can2_totalTQ    = 1 + nomSeg1 + nomSeg2;
		uint32_t can2_actualBR   = apb1clock / (nomPrescaler * can2_totalTQ);
		uint32_t can2_brErr_ppm  = (uint32_t)(((int32_t)can2_actualBR - (int32_t)mainBitrate) >= 0
		                           ? ((can2_actualBR - mainBitrate) * 1000000UL / mainBitrate)
		                           : ((mainBitrate - can2_actualBR) * 1000000UL / mainBitrate));
		*/
	}
	if ((bus & CAN_3) == CAN_3)
	{
		hfdcan3.Instance = FDCAN3;
		hfdcan3.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan3.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
		if (mode == NORMAL_MODE)
		{
			hfdcan3.Init.Mode = FDCAN_MODE_NORMAL;
		}
		else if (mode == LISTEN_ONLY)
		{
			hfdcan3.Init.Mode = FDCAN_MODE_BUS_MONITORING;
		}
		hfdcan3.Init.AutoRetransmission = ENABLE;
		hfdcan3.Init.TransmitPause = DISABLE;
		hfdcan3.Init.ProtocolException = ENABLE;
		hfdcan3.Init.NominalPrescaler = nomPrescaler;
		hfdcan3.Init.NominalSyncJumpWidth = nomSJW;
		hfdcan3.Init.NominalTimeSeg1 = nomSeg1;
		hfdcan3.Init.NominalTimeSeg2 = nomSeg2;
		hfdcan3.Init.DataPrescaler = datPrescaler;
		hfdcan3.Init.DataSyncJumpWidth = datSJW;
		hfdcan3.Init.DataTimeSeg1 = datSeg1;
		hfdcan3.Init.DataTimeSeg2 = datSeg2;
		hfdcan3.Init.StdFiltersNbr = 0;
		hfdcan3.Init.ExtFiltersNbr = 0;
		hfdcan3.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan3) != HAL_OK)
		{
			returnval = 1;
		}
	}
	return returnval;
}

/**
 * Estimate TDCO from an assumed loop delay (ns).
 *
 * fdcan_ker_hz : FDCAN kernel clock (Hz) (often 170MHz on G4 depending on clocking)
 * data_presc   : DataPrescaler value you program into HAL (DBRP+1), 1..32
 * loop_ns      : assumed transceiver+path loop delay in ns (e.g. 150)
 */
static uint32_t fdcan_tdco_from_loop_ns(uint32_t fdcan_ker_hz,
                                 uint32_t data_presc,
                                 uint32_t loop_ns)
{
  // TDCO = round(loop_ns / tDTQ) where tDTQ = data_presc / fdcan_ker_hz
  // => TDCO = round(loop_ns * fdcan_ker_hz / (data_presc * 1e9))
  uint64_t num = (uint64_t)loop_ns * (uint64_t)fdcan_ker_hz;
  uint64_t den = (uint64_t)data_presc * 1000000000ULL;

  uint64_t tdco = (num + den/2) / den;   // rounded division
  if (tdco > 127U) tdco = 127U;
  return (uint32_t)tdco;
}

/**
 * \brief Sets up a CAN FD bus with separate nominal and data phase bitrates.
 *
 * \param bus           CAN_1, CAN_2, or CAN_3.
 * \param mainBitrate   Nominal (arbitration phase) bitrate in bits per second.
 * \param dataBitrate   Data phase bitrate in bits per second.
 * \param bitrateSwitch true  = enable bitrate switching (FD with BRS),
 *                      false = FD frame format but no bitrate switch.
 * \param mode "NORMAL_MODE" or "LISTEN_ONLY"
 * \return 0 if no errors, 1 for any error.
 */
uint8_t setupCAN_FDbus(CAN_Bus bus, uint32_t mainBitrate, uint32_t dataBitrate, bool bitrateSwitch, CAN_Mode mode)
{
	uint8_t returnval = 0;
	uint32_t apb1clock = HAL_RCC_GetPCLK1Freq();

	/* Nominal timing uses mainBitrate; data timing uses the separate dataBitrate */
	uint32_t nomPrescaler, nomSeg1, nomSeg2;
	uint32_t datPrescaler, datSeg1, datSeg2;
	calculateBitTiming(apb1clock, mainBitrate, 512, &nomPrescaler, &nomSeg1, &nomSeg2);
	calculateBitTiming(apb1clock, dataBitrate,  32, &datPrescaler, &datSeg1, &datSeg2);

	/* SJW = min(Seg2, 4) – matches resync capability to the phase buffer */
	uint32_t nomSJW = (nomSeg2 < 4) ? nomSeg2 : 4;
	uint32_t datSJW = (datSeg2 < 4) ? datSeg2 : 4;

	printf("Setup CAN FD Bus %d:\r\n", bus);
	printf("  Nominal: Prescaler=%lu, Seg1=%lu, Seg2=%lu, SJW=%lu\r\n", nomPrescaler, nomSeg1, nomSeg2, nomSJW);
	printf("  Data:    Prescaler=%lu, Seg1=%lu, Seg2=%lu, SJW=%lu\r\n", datPrescaler, datSeg1, datSeg2, datSJW);

	uint32_t frameFormat = bitrateSwitch ? FDCAN_FRAME_FD_BRS : FDCAN_FRAME_FD_NO_BRS;

	if ((bus & CAN_1) == CAN_1)
	{
		hfdcan1.Instance = FDCAN1;
		hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan1.Init.FrameFormat = frameFormat;

		if (mode == NORMAL_MODE)
		{
			hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
		}
		else if (mode == LISTEN_ONLY)
		{
			hfdcan1.Init.Mode = FDCAN_MODE_BUS_MONITORING;
		}
		hfdcan1.Init.AutoRetransmission = ENABLE;
		hfdcan1.Init.TransmitPause = DISABLE;
		hfdcan1.Init.ProtocolException = ENABLE;
		hfdcan1.Init.NominalPrescaler = nomPrescaler;
		hfdcan1.Init.NominalSyncJumpWidth = nomSJW;
		hfdcan1.Init.NominalTimeSeg1 = nomSeg1;
		hfdcan1.Init.NominalTimeSeg2 = nomSeg2;
		hfdcan1.Init.DataPrescaler = datPrescaler;
		hfdcan1.Init.DataSyncJumpWidth = datSJW;
		hfdcan1.Init.DataTimeSeg1 = datSeg1;
		hfdcan1.Init.DataTimeSeg2 = datSeg2;
		hfdcan1.Init.StdFiltersNbr = 0;
		hfdcan1.Init.ExtFiltersNbr = 0;
		hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
		{
			returnval = 1;
		}

		if (frameFormat == FDCAN_FRAME_FD_BRS)
		{
			uint32_t tdco = fdcan_tdco_from_loop_ns(apb1clock, datPrescaler, CANFD_LOOP_DELAY_NS);
			HAL_FDCAN_ConfigTxDelayCompensation(&hfdcan1, tdco, 0);
			HAL_FDCAN_EnableTxDelayCompensation(&hfdcan1);
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		hfdcan2.Instance = FDCAN2;
		hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan2.Init.FrameFormat = frameFormat;
		if (mode == NORMAL_MODE)
		{
			hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
		}
		else if (mode == LISTEN_ONLY)
		{
			hfdcan2.Init.Mode = FDCAN_MODE_BUS_MONITORING;
		}
		hfdcan2.Init.AutoRetransmission = ENABLE;
		hfdcan2.Init.TransmitPause = DISABLE;
		hfdcan2.Init.ProtocolException = ENABLE;
		hfdcan2.Init.NominalPrescaler = nomPrescaler;
		hfdcan2.Init.NominalSyncJumpWidth = nomSJW;
		hfdcan2.Init.NominalTimeSeg1 = nomSeg1;
		hfdcan2.Init.NominalTimeSeg2 = nomSeg2;
		hfdcan2.Init.DataPrescaler = datPrescaler;
		hfdcan2.Init.DataSyncJumpWidth = datSJW;
		hfdcan2.Init.DataTimeSeg1 = datSeg1;
		hfdcan2.Init.DataTimeSeg2 = datSeg2;
		hfdcan2.Init.StdFiltersNbr = 0;
		hfdcan2.Init.ExtFiltersNbr = 0;
		hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
		{
			returnval = 1;
		}

		if (frameFormat == FDCAN_FRAME_FD_BRS)
		{
			uint32_t tdco = fdcan_tdco_from_loop_ns(apb1clock, datPrescaler, CANFD_LOOP_DELAY_NS);
			HAL_FDCAN_ConfigTxDelayCompensation(&hfdcan2, tdco, 0);
			HAL_FDCAN_EnableTxDelayCompensation(&hfdcan2);
		}
	}
	if ((bus & CAN_3) == CAN_3)
	{
		hfdcan3.Instance = FDCAN3;
		hfdcan3.Init.ClockDivider = FDCAN_CLOCK_DIV1;
		hfdcan3.Init.FrameFormat = frameFormat;
		if (mode == NORMAL_MODE)
		{
			hfdcan3.Init.Mode = FDCAN_MODE_NORMAL;
		}
		else if (mode == LISTEN_ONLY)
		{
			hfdcan3.Init.Mode = FDCAN_MODE_BUS_MONITORING;
		}
		hfdcan3.Init.AutoRetransmission = ENABLE;
		hfdcan3.Init.TransmitPause = DISABLE;
		hfdcan3.Init.ProtocolException = ENABLE;
		hfdcan3.Init.NominalPrescaler = nomPrescaler;
		hfdcan3.Init.NominalSyncJumpWidth = nomSJW;
		hfdcan3.Init.NominalTimeSeg1 = nomSeg1;
		hfdcan3.Init.NominalTimeSeg2 = nomSeg2;
		hfdcan3.Init.DataPrescaler = datPrescaler;
		hfdcan3.Init.DataSyncJumpWidth = datSJW;
		hfdcan3.Init.DataTimeSeg1 = datSeg1;
		hfdcan3.Init.DataTimeSeg2 = datSeg2;
		hfdcan3.Init.StdFiltersNbr = 0;
		hfdcan3.Init.ExtFiltersNbr = 0;
		hfdcan3.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
		if (HAL_FDCAN_Init(&hfdcan3) != HAL_OK)
		{
			returnval = 1;
		}

		if (frameFormat == FDCAN_FRAME_FD_BRS)
		{
			uint32_t tdco = fdcan_tdco_from_loop_ns(apb1clock, datPrescaler, CANFD_LOOP_DELAY_NS);
			HAL_FDCAN_ConfigTxDelayCompensation(&hfdcan3, tdco, 0);
			HAL_FDCAN_EnableTxDelayCompensation(&hfdcan3);
		}
	}
	return returnval;
}

/**
 * \brief Starts CANbus
 *
 * \param bus CAN_1, CAN_2, or CAN_3.
 * \return 0 if no errors, 1 for any error
 */
uint8_t startCANbus(CAN_Bus bus)
{

	uint8_t returnval = 0;

	if ((bus & CAN_1) == CAN_1)
	{
		uint8_t groupval = 0;
		if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK)
		{
			groupval += 1;
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan1,
										   FDCAN_IT_RX_FIFO0_NEW_MESSAGE |
											   FDCAN_IT_ERROR_PASSIVE |
											   FDCAN_IT_ERROR_LOGGING_OVERFLOW |
											   FDCAN_IT_BUS_OFF |
											   FDCAN_IT_ERROR_WARNING |
											   FDCAN_IT_TX_COMPLETE,
										   FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2) != HAL_OK)
		{
			groupval += 2;
		}
		/* Start the FDCAN module */
		if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
		{
			groupval += 4;
		}
		if (groupval != 7)
		{
			returnval = 1;
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		uint8_t groupval = 0;
		if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK)
		{
			groupval += 1;
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_ERROR_PASSIVE | FDCAN_IT_ERROR_LOGGING_OVERFLOW | FDCAN_IT_DATA_PROTOCOL_ERROR | FDCAN_IT_ARB_PROTOCOL_ERROR | FDCAN_IT_BUS_OFF | FDCAN_IT_ERROR_WARNING | FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2) != HAL_OK)
		{
			groupval += 2;
		}
		/* Start the FDCAN module */
		if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
		{
			groupval += 4;
		}
		if (groupval != 7)
		{
			returnval = 1;
		}
	}
	if ((bus & CAN_3) == CAN_3)
	{
		uint8_t groupval = 0;
		if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) != HAL_OK)
		{
			groupval += 1;
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE | FDCAN_IT_ERROR_PASSIVE | FDCAN_IT_ERROR_LOGGING_OVERFLOW | FDCAN_IT_DATA_PROTOCOL_ERROR | FDCAN_IT_ARB_PROTOCOL_ERROR | FDCAN_IT_BUS_OFF | FDCAN_IT_ERROR_WARNING | FDCAN_IT_TX_COMPLETE, FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2) != HAL_OK)
		{
			groupval += 2;
		}
		/* Start the FDCAN module */
		if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK)
		{
			groupval += 4;
		}
		if (groupval != 7)
		{
			returnval = 1;
		}
	}
	return returnval;
}

/**
 * \brief Stops CANbus Bitrate
 *
 * \param bus CAN_1, CAN_2, and/or CAN_3.
 * \return  0 if no errors, 1 for any error
 */
uint8_t stopCANbus(CAN_Bus bus)
{
	uint8_t returnval = 0;

	// Unused filter //

	/*  FDCAN_FilterTypeDef sFilterConfig;
	**  sFilterConfig.IdType = FDCAN_STANDARD_ID;
	**  sFilterConfig.FilterIndex = 0;
	**  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	**  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	**  sFilterConfig.FilterID1 = 0x321;
	**  sFilterConfig.FilterID2 = 0x7FF;
	**  if(HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
	** {
	**    Error_Handler();
	**  }
	*/
	if ((bus & CAN_1) == CAN_1)
	{
		if (HAL_FDCAN_Stop(&hfdcan1) != HAL_OK)
		{
			returnval = 1;
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		if (HAL_FDCAN_Stop(&hfdcan2) != HAL_OK)
		{
			returnval = 1;
		}
	}
	if ((bus & CAN_3) == CAN_3)
	{
		if (HAL_FDCAN_Stop(&hfdcan3) != HAL_OK)
		{
			returnval = 1;
		}
	}
	return returnval;
}

/**
 * \brief Enable or Disable CAN Termination across CANbuses
 *
 * \param bus CAN_1, CAN_2, or CAN_3.
 * \return  0 if no errors, 1 for any error
 */
uint8_t setCAN_Termination(CAN_Bus bus, bool activated)
{
	uint8_t returnval = 0;
	if ((bus & CAN_1) == CAN_1)
	{
		if (activated == true)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		if (activated == true)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);
		}
	}
	if ((bus & CAN_3) == CAN_3)
	{
		if (activated == true)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
		}
	}
	return returnval;
}

/**
 * \brief Reads Error Counters for CANbus
 *
 * \param bus CAN_1, CAN_2, or CAN_3.
 * \return
 */
CAN_ErrorCounts getCANErrorCounts(CAN_Bus bus)
{
	volatile uint32_t *ecr_addr;
	CAN_ErrorCounts error_counts;
	switch (bus)
	{
	case CAN_1:
		ecr_addr = (volatile uint32_t *)0x40006440UL;
		error_counts.BusResetCounter = can1Reset_counter;
		error_counts.TxErrorCounter = (uint8_t)(((*ecr_addr) & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
		error_counts.RxErrorCounter = (uint8_t)(((*ecr_addr) & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
		break;
	case CAN_2:
		ecr_addr = (volatile uint32_t *)0x40006840UL;
		error_counts.BusResetCounter = can2Reset_counter;
		error_counts.TxErrorCounter = (uint8_t)(((*ecr_addr) & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
		error_counts.RxErrorCounter = (uint8_t)(((*ecr_addr) & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
		break;
	case CAN_3:
		ecr_addr = (volatile uint32_t *)0x40006C40UL;
		error_counts.BusResetCounter = can3Reset_counter;
		error_counts.TxErrorCounter = (uint8_t)(((*ecr_addr) & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
		error_counts.RxErrorCounter = (uint8_t)(((*ecr_addr) & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
		break;
	default:
		// Handle invalid bus selection
		error_counts.BusResetCounter = 255;
		error_counts.TxErrorCounter = 255;
		error_counts.RxErrorCounter = 255;
	}
	return error_counts;
}

/* Interrupt Service Routine for Rx Messages */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
	{
		/* Retrieve Rx messages from RX FIFO0 */
		if (hfdcan->Instance == FDCAN1)
		{
			if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &CAN1_RxHeader, CAN1_RxData) != HAL_OK)
			{
				Error_Handler();
			}

			bool Callback_Rx_ID_Type;
			uint32_t Callback_Rx_ID;
			uint8_t Callback_Rx_DLC;

			if (CAN1_RxHeader.IdType == FDCAN_EXTENDED_ID)
			{
				Callback_Rx_ID_Type = true;
			}
			else
			{
				Callback_Rx_ID_Type = false;
			}
			Callback_Rx_ID = CAN1_RxHeader.Identifier;
			Callback_Rx_DLC = fdcan_dlc_to_bytes(CAN1_RxHeader.DataLength);
			if (Callback_Rx_DLC > CAN1_DATALENGTH)
			{
				Callback_Rx_DLC = CAN1_DATALENGTH;
			}
			add_to_CAN_RX_Queue(CAN_1, Callback_Rx_ID_Type, Callback_Rx_ID, Callback_Rx_DLC, CAN1_RxData);
		}
		if (hfdcan->Instance == FDCAN2)
		{
			if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO0, &CAN2_RxHeader, CAN2_RxData) != HAL_OK)
			{
				Error_Handler();
			}

			bool Callback_Rx_ID_Type;
			uint32_t Callback_Rx_ID;
			uint8_t Callback_Rx_DLC;

			if (CAN2_RxHeader.IdType == FDCAN_EXTENDED_ID)
			{
				Callback_Rx_ID_Type = true;
			}
			else
			{
				Callback_Rx_ID_Type = false;
			}
			Callback_Rx_ID = CAN2_RxHeader.Identifier;
			Callback_Rx_DLC = fdcan_dlc_to_bytes(CAN2_RxHeader.DataLength);
			if (Callback_Rx_DLC > CAN2_DATALENGTH)
			{
				Callback_Rx_DLC = CAN2_DATALENGTH;
			}
			add_to_CAN_RX_Queue(CAN_2, Callback_Rx_ID_Type, Callback_Rx_ID, Callback_Rx_DLC, CAN2_RxData);
		}
		if (hfdcan->Instance == FDCAN3)
		{
			if (HAL_FDCAN_GetRxMessage(&hfdcan3, FDCAN_RX_FIFO0, &CAN3_RxHeader, CAN3_RxData) != HAL_OK)
			{
				Error_Handler();
			}

			bool Callback_Rx_ID_Type;
			uint32_t Callback_Rx_ID;
			uint8_t Callback_Rx_DLC;

			if (CAN3_RxHeader.IdType == FDCAN_EXTENDED_ID)
			{
				Callback_Rx_ID_Type = true;
			}
			else
			{
				Callback_Rx_ID_Type = false;
			}
			Callback_Rx_ID = CAN3_RxHeader.Identifier;
			Callback_Rx_DLC = fdcan_dlc_to_bytes(CAN3_RxHeader.DataLength);
			if (Callback_Rx_DLC > CAN3_DATALENGTH)
			{
				Callback_Rx_DLC = CAN3_DATALENGTH;
			}
			add_to_CAN_RX_Queue(CAN_3, Callback_Rx_ID_Type, Callback_Rx_ID, Callback_Rx_DLC, CAN3_RxData);
		}
	}
}

/* Interrupt Service Routine for Successfully Transmitting Messages.. */
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
	if (hfdcan->Instance == FDCAN1)
	{
	}
	if (hfdcan->Instance == FDCAN2)
	{
	}
	if (hfdcan->Instance == FDCAN3)
	{
	}
}

/* Add to CAN Receive Queue
CAN_1: 1, CAN_2: 2, CAN_3: 4 */
uint8_t add_to_CAN_RX_Queue(CAN_Bus bus, bool EXT_ID, uint32_t ID, uint8_t DLC, uint8_t rxData[])
{
	uint8_t return_val = 0;
	if ((bus & CAN_1) == CAN_1)
	{
		can1_Rx_qNextHead = (can1_Rx_qHead + 1) & (CAN1_RX_MSG_BUFFER_SIZE - 1);
		/*  if there is room */
		if (can1_Rx_qNextHead != can1_Rx_qTail)
		{
			can1_Rx_qData[can1_Rx_qHead].EXT_ID = EXT_ID;
			can1_Rx_qData[can1_Rx_qHead].arb_id = ID;
			can1_Rx_qData[can1_Rx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++)
			{
				can1_Rx_qData[can1_Rx_qHead].data[i] = rxData[i];
			}
			can1_Rx_qHead = can1_Rx_qNextHead;
			can1_Rx_qElements++;
		}
		else
		{
			/* no room left in the buffer */
			return_val = 1;
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		can2_Rx_qNextHead = (can2_Rx_qHead + 1) & (CAN2_RX_MSG_BUFFER_SIZE - 1);
		/*  if there is room */
		if (can2_Rx_qNextHead != can2_Rx_qTail)
		{
			can2_Rx_qData[can2_Rx_qHead].EXT_ID = EXT_ID;
			can2_Rx_qData[can2_Rx_qHead].arb_id = ID;
			can2_Rx_qData[can2_Rx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++)
			{
				can2_Rx_qData[can2_Rx_qHead].data[i] = rxData[i];
			}
			can2_Rx_qHead = can2_Rx_qNextHead;
			can2_Rx_qElements++;
		}
		else
		{
			/* no room left in the buffer */
			return_val = 2;
		}
	}
	if ((bus & CAN_3) == CAN_3)
	{
		can3_Rx_qNextHead = (can3_Rx_qHead + 1) & (CAN3_RX_MSG_BUFFER_SIZE - 1);
		/*  if there is room */
		if (can3_Rx_qNextHead != can3_Rx_qTail)
		{
			can3_Rx_qData[can3_Rx_qHead].EXT_ID = EXT_ID;
			can3_Rx_qData[can3_Rx_qHead].arb_id = ID;
			can3_Rx_qData[can3_Rx_qHead].dlc = DLC;
			for (uint8_t i = 0; i < DLC; i++)
			{
				can3_Rx_qData[can3_Rx_qHead].data[i] = rxData[i];
			}
			can3_Rx_qHead = can3_Rx_qNextHead;
			can3_Rx_qElements++;
		}
		else
		{
			/* no room left in the buffer */
			return_val = 3;
		}
	}
	return return_val;
}

/**
 * \brief Sends message to Queue
 * \param bus CAN_1, CAN_2, and/or CAN_3.
 * \param is_extended_id True or False.
 * \param arbitration_id Message ID.
 * \param dlc Data Length.
 * \param data Message data (8 Bytes).
 * \return 1, 2, or 3 based on CAN Bus applicable
 */
uint8_t send_message(CAN_Bus bus, bool is_extended_id, uint32_t arbitration_id, uint8_t dlc, uint8_t data[])
{
	uint8_t return_val = 0;
	if ((bus & CAN_1) == CAN_1)
	{
		can1_Tx_qNextHead = (can1_Tx_qHead + 1) & (CAN1_TX_MSG_BUFFER_SIZE - 1);
		/*  if there is room */
		if (can1_Tx_qNextHead != can1_Tx_qTail)
		{
			can1_Tx_qData[can1_Tx_qHead].EXT_ID = is_extended_id;
			can1_Tx_qData[can1_Tx_qHead].arb_id = arbitration_id;
			can1_Tx_qData[can1_Tx_qHead].dlc = dlc;
			for (uint8_t i = 0; i < dlc; i++)
			{
				can1_Tx_qData[can1_Tx_qHead].data[i] = data[i];
			}
			can1_Tx_qHead = can1_Tx_qNextHead;
			can1_Tx_qElements++;
		}
		else
		{
			/* no room left in the buffer */
			return_val = 1;
		}
	}
	if ((bus & CAN_2) == CAN_2)
	{
		can2_Tx_qNextHead = (can2_Tx_qHead + 1) & (CAN2_TX_MSG_BUFFER_SIZE - 1);
		/*  if there is room */
		if (can2_Tx_qNextHead != can2_Tx_qTail)
		{
			can2_Tx_qData[can2_Tx_qHead].EXT_ID = is_extended_id;
			can2_Tx_qData[can2_Tx_qHead].arb_id = arbitration_id;
			can2_Tx_qData[can2_Tx_qHead].dlc = dlc;
			for (uint8_t i = 0; i < dlc; i++)
			{
				can2_Tx_qData[can2_Tx_qHead].data[i] = data[i];
			}
			can2_Tx_qHead = can2_Tx_qNextHead;
			can2_Tx_qElements++;
		}
		else
		{
			/* no room left in the buffer */
			return_val = 2;
		}
	}
	if ((bus & CAN_3) == CAN_3)
	{
		can3_Tx_qNextHead = (can3_Tx_qHead + 1) & (CAN3_TX_MSG_BUFFER_SIZE - 1);
		/*  if there is room */
		if (can3_Tx_qNextHead != can3_Tx_qTail)
		{
			can3_Tx_qData[can3_Tx_qHead].EXT_ID = is_extended_id;
			can3_Tx_qData[can3_Tx_qHead].arb_id = arbitration_id;
			can3_Tx_qData[can3_Tx_qHead].dlc = dlc;
			for (uint8_t i = 0; i < dlc; i++)
			{
				can3_Tx_qData[can3_Tx_qHead].data[i] = data[i];
			}
			can3_Tx_qHead = can3_Tx_qNextHead;
			can3_Tx_qElements++;
		}
		else
		{
			/* no room left in the buffer */
			return_val = 3;
		}
	}
	return return_val;
}

/* Callback for Received Messages for OnReceive Function*/
void trigger_CAN_RX()
{
	CAN_Message message;
	while (can1_Rx_qElements > 0)
	{
		__disable_irq();  // Protect queue access
		if (can1_Rx_qElements == 0) {
			__enable_irq();
			break;  // Double-check after disabling interrupts
		}
		
		message.Bus = CAN_1;
		message.is_extended_id = can1_Rx_qData[can1_Rx_qTail].EXT_ID;
		message.arbitration_id = can1_Rx_qData[can1_Rx_qTail].arb_id;
		message.dlc = can1_Rx_qData[can1_Rx_qTail].dlc;
		for (uint8_t i = 0; i < message.dlc; i++)
		{
			message.data[i] = can1_Rx_qData[can1_Rx_qTail].data[i];
		}
		can1_Rx_qTail = (can1_Rx_qTail + 1) & (CAN1_RX_MSG_BUFFER_SIZE - 1);
		can1_Rx_qElements--;
		__enable_irq();  // Re-enable interrupts
		
 		// Now, you can call onReceive with a single CANMessage struct.
		onReceive(message);
	}

	while (can2_Rx_qElements > 0)
	{
		__disable_irq();  // Protect queue access
		if (can2_Rx_qElements == 0) {
			__enable_irq();
			break;  // Double-check after disabling interrupts
		}
		
		message.Bus = CAN_2;
		message.is_extended_id = can2_Rx_qData[can2_Rx_qTail].EXT_ID;
		message.arbitration_id = can2_Rx_qData[can2_Rx_qTail].arb_id;
		message.dlc = can2_Rx_qData[can2_Rx_qTail].dlc;
		for (uint8_t i = 0; i < message.dlc; i++)
		{
			message.data[i] = can2_Rx_qData[can2_Rx_qTail].data[i];
		}
		can2_Rx_qTail = (can2_Rx_qTail + 1) & (CAN2_RX_MSG_BUFFER_SIZE - 1);
		can2_Rx_qElements--;
		__enable_irq();  // Re-enable interrupts
		
		/* */ // Do things with the  Can 2 Messages here....
		onReceive(message);
	}
	while (can3_Rx_qElements > 0)
	{
		__disable_irq();  // Protect queue access
		if (can3_Rx_qElements == 0) {
			__enable_irq();
			break;  // Double-check after disabling interrupts
		}
		
		message.Bus = CAN_3;
		message.is_extended_id = can3_Rx_qData[can3_Rx_qTail].EXT_ID;
		message.arbitration_id = can3_Rx_qData[can3_Rx_qTail].arb_id;
		message.dlc = can3_Rx_qData[can3_Rx_qTail].dlc;
		for (uint8_t i = 0; i < message.dlc; i++)
		{
			message.data[i] = can3_Rx_qData[can3_Rx_qTail].data[i];
		}
		can3_Rx_qTail = (can3_Rx_qTail + 1) & (CAN3_RX_MSG_BUFFER_SIZE - 1);
		can3_Rx_qElements--;
		__enable_irq();  // Re-enable interrupts
		
		/* */ // Do things with the  Can 3 Messages here....
		onReceive(message);
	}
}

/* Callback to Transmit Messages to CANBuses*/
void trigger_CAN_TX()
{
	if (HAL_FDCAN_GetState(&hfdcan1) == HAL_FDCAN_STATE_BUSY)
	{
		uint8_t can1_freelevel = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1);
		while ((can1_freelevel > 0) & (can1_Tx_qElements > 0))
		{
			if (can1_Tx_qData[can1_Tx_qTail].EXT_ID == true)
			{
				CAN1_TxHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else
			{
				CAN1_TxHeader.IdType = FDCAN_STANDARD_ID;
			}

			CAN1_TxHeader.Identifier = can1_Tx_qData[can1_Tx_qTail].arb_id;
			{
				uint8_t can1_tx_bytes = (can1_Tx_qData[can1_Tx_qTail].dlc <= CAN1_DATALENGTH)
				                        ? can1_Tx_qData[can1_Tx_qTail].dlc : CAN1_DATALENGTH;
				CAN1_TxHeader.DataLength = bytes_to_fdcan_dlc(can1_tx_bytes);
			}
			CAN1_TxHeader.FDFormat = (can1_Tx_qData[can1_Tx_qTail].dlc > 8) ? FDCAN_FD_CAN : FDCAN_CLASSIC_CAN;
			CAN1_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			CAN1_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
			CAN1_TxHeader.BitRateSwitch = FDCAN_BRS_ON;
			CAN1_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			CAN1_TxHeader.MessageMarker = 0;
			for (uint8_t i = 0; i < can1_Tx_qData[can1_Tx_qTail].dlc; i++)
			{
				CAN1_TxData[i] = can1_Tx_qData[can1_Tx_qTail].data[i];
			}
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &CAN1_TxHeader, CAN1_TxData);
			can1_Tx_qTail = (can1_Tx_qTail + 1) & (CAN1_TX_MSG_BUFFER_SIZE - 1);
			can1_Tx_qElements--;
			can1_freelevel--;
		}
	}

	if (HAL_FDCAN_GetState(&hfdcan2) == HAL_FDCAN_STATE_BUSY)
	{
		uint8_t can2_freelevel = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2);
		while ((can2_freelevel > 0) && (can2_Tx_qElements > 0))
		{
			if (can2_Tx_qData[can2_Tx_qTail].EXT_ID == true)
			{
				CAN2_TxHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else
			{
				CAN2_TxHeader.IdType = FDCAN_STANDARD_ID;
			}
			CAN2_TxHeader.Identifier = can2_Tx_qData[can2_Tx_qTail].arb_id;
			{
				uint8_t can2_tx_bytes = (can2_Tx_qData[can2_Tx_qTail].dlc <= CAN2_DATALENGTH)
				                        ? can2_Tx_qData[can2_Tx_qTail].dlc : CAN2_DATALENGTH;
				CAN2_TxHeader.DataLength = bytes_to_fdcan_dlc(can2_tx_bytes);
			}
			CAN2_TxHeader.FDFormat = (can2_Tx_qData[can2_Tx_qTail].dlc > 8) ? FDCAN_FD_CAN : FDCAN_CLASSIC_CAN;
			CAN2_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			CAN2_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
			CAN2_TxHeader.BitRateSwitch = FDCAN_BRS_ON;
			CAN2_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			CAN2_TxHeader.MessageMarker = 0;
			for (uint8_t i = 0; i < can2_Tx_qData[can2_Tx_qTail].dlc; i++)
			{
				CAN2_TxData[i] = can2_Tx_qData[can2_Tx_qTail].data[i];
			}
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &CAN2_TxHeader, CAN2_TxData);
			can2_Tx_qTail = (can2_Tx_qTail + 1) & (CAN2_TX_MSG_BUFFER_SIZE - 1);
			can2_Tx_qElements--;
			can2_freelevel--;
		}
	}

	if (HAL_FDCAN_GetState(&hfdcan3) == HAL_FDCAN_STATE_BUSY)
	{
		uint8_t can3_freelevel = HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan3);
		while ((can3_freelevel > 0) && (can3_Tx_qElements > 0))
		{
			if (can3_Tx_qData[can3_Tx_qTail].EXT_ID == true)
			{
				CAN3_TxHeader.IdType = FDCAN_EXTENDED_ID;
			}
			else
			{
				CAN3_TxHeader.IdType = FDCAN_STANDARD_ID;
			}

			CAN3_TxHeader.Identifier = can3_Tx_qData[can3_Tx_qTail].arb_id;
			{
				uint8_t can3_tx_bytes = (can3_Tx_qData[can3_Tx_qTail].dlc <= CAN3_DATALENGTH)
				                        ? can3_Tx_qData[can3_Tx_qTail].dlc : CAN3_DATALENGTH;
				CAN3_TxHeader.DataLength = bytes_to_fdcan_dlc(can3_tx_bytes);
			}
			CAN3_TxHeader.FDFormat = (can3_Tx_qData[can3_Tx_qTail].dlc > 8) ? FDCAN_FD_CAN : FDCAN_CLASSIC_CAN;
			CAN3_TxHeader.TxFrameType = FDCAN_DATA_FRAME;
			CAN3_TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
			CAN3_TxHeader.BitRateSwitch = FDCAN_BRS_ON;
			CAN3_TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			CAN3_TxHeader.MessageMarker = 0;
			for (uint8_t i = 0; i < can3_Tx_qData[can3_Tx_qTail].dlc; i++)
			{
				CAN3_TxData[i] = can3_Tx_qData[can3_Tx_qTail].data[i];
			}
			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &CAN3_TxHeader, CAN3_TxData);
			can3_Tx_qTail = (can3_Tx_qTail + 1) & (CAN3_TX_MSG_BUFFER_SIZE - 1);
			can3_Tx_qElements--;
			can3_freelevel--;
		}
	}
}

/* Callback for Errors occurred on CAN buses */
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs)
{
	uint16_t canTxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
	uint16_t canRxErrorCount = ((hfdcan->Instance->ECR & FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
	if (hfdcan->Instance == FDCAN1)
	{
		if (canTxErrorCount > 240 || canRxErrorCount > 120)
		{
			can1Reset_counter++;
			resetCAN(CAN_1);
		}
	}
	if (hfdcan->Instance == FDCAN2)
	{
		if (canTxErrorCount > 240 || canRxErrorCount > 120)
		{
			can2Reset_counter++;
			resetCAN(CAN_2);
		}
	}
	if (hfdcan->Instance == FDCAN3)
	{
		if (canTxErrorCount > 240 || canRxErrorCount > 120)
		{
			can3Reset_counter++;
			resetCAN(CAN_3);
		}
	}
}

/**
 * \brief Resets CANbus
 *
 * \param bus CAN_1, CAN_2, and/or CAN_3.
 * \return 0 if no errors.
 */
uint8_t resetCAN(CAN_Bus bus)
{
	uint8_t groupval = 0;
	uint8_t returnval = 0;
	if ((bus & CAN_1) == CAN_1)
	{
		if (HAL_FDCAN_Stop(&hfdcan1) != HAL_OK)
		{
			groupval += 1;
		}
		/* Start the FDCAN module */
		if (hfdcan1.State == HAL_FDCAN_STATE_READY)
		{
			if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
			{
				groupval += 2;
			}
		}
		if (groupval != 0)
		{
			returnval = 1;
		}
		groupval = 0;
	}
	if ((bus & CAN_2) == CAN_2)
	{
		if (HAL_FDCAN_Stop(&hfdcan2) != HAL_OK)
		{
			groupval += 1;
		}
		/* Start the FDCAN module */
		if (hfdcan2.State == HAL_FDCAN_STATE_READY)
		{
			if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
			{
				groupval += 2;
			}
		}
		if (groupval != 0)
		{
			returnval = 1;
		}
		groupval = 0;
	}
	if ((bus & CAN_3) == CAN_3)
	{
		if (HAL_FDCAN_Stop(&hfdcan3) != HAL_OK)
		{
			groupval += 1;
		}
		/* Start the FDCAN module */
		if (hfdcan3.State == HAL_FDCAN_STATE_READY)
		{
			if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK)
			{
				groupval += 2;
			}
		}
		if (groupval != 0)
		{
			returnval = 1;
		}
	}
	return returnval;
}

/**
 * \brief horizontally flips 1byte of data
 *
 * \param data U8 data
 * \return flipped U8 data.
 */
uint8_t reflect8(uint8_t data)
{
	uint8_t reflection = 0;
	for (uint8_t i = 0; i < 8; ++i)
	{
		if (data & (1 << i))
		{
			reflection |= (1 << (7 - i));
		}
	}
	return reflection;
}

/**
 * \brief Calculates CRC8 Checksum
 *
 * \param data pointer to data.
 * \param length length of array.
 * \param polynomial U8 polynomial.
 * \param crcInit U8 initializer.
 * \param finalXor U8 final XOR.
 * \param reflectInput Boolean reflect the input.
 * \param reflectOutput Boolean reflect the output.
 * \return CRC Value
 */
uint8_t calculateCRC8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t crcInit, uint8_t finalXor, bool reflectInput, bool reflectOutput)
{
	uint8_t crc = crcInit;
	for (size_t i = 0; i < length; ++i)
	{
		uint8_t byte = data[i];
		if (reflectInput)
		{
			byte = reflect8(byte);
		}
		crc ^= byte;
		for (uint8_t j = 0; j < 8; ++j)
		{
			if (crc & 0x80)
			{
				crc = (crc << 1) ^ polynomial;
			}
			else
			{
				crc <<= 1;
			}
		}
	}

	if (reflectOutput)
	{
		crc = reflect8(crc);
	}
	return (crc ^ finalXor);
}

/* reflect16 function */
uint16_t reflect16(uint16_t data)
{
	uint16_t reflection = 0;
	for (uint16_t i = 0; i < 16; ++i)
	{
		if (data & (1 << i))
		{
			reflection |= (1 << (15 - i));
		}
	}
	return reflection;
}

/**
 * \brief Calculates CRC16 Checksum
 *
 * \param data pointer to data.
 * \param length length of array.
 * \param polynomial u16 polynomial.
 * \param crcInit u16 initializer.
 * \param finalXor u16 final XOR.
 * \param reflectInput Boolean reflect the input.
 * \param reflectOutput Boolean reflect the output.
 * \return CRC Value
 */
uint16_t calculateCRC16(uint8_t *data, size_t length, uint16_t polynomial, uint16_t crcInit, uint16_t finalXor, bool reflectInput, bool reflectOutput)
{
	uint16_t crc = crcInit;
	for (size_t i = 0; i < length; ++i)
	{
		uint16_t byte = data[i];
		if (reflectInput)
		{
			byte = reflect8((uint8_t)byte); // Using reflect8 since each byte is reflected individually
		}
		crc ^= (byte << 8); // Shift byte to the high bits of the 16-bit CRC
		for (uint8_t j = 0; j < 8; ++j)
		{
			if (crc & 0x8000)
			{
				crc = (crc << 1) ^ polynomial;
			}
			else
			{
				crc <<= 1;
			}
		}
	}

	if (reflectOutput)
	{
		crc = reflect16(crc);
	}
	return (crc ^ finalXor);
}

/* reflect32 function */
uint32_t reflect32(uint32_t data)
{
	uint32_t reflection = 0;
	for (uint32_t i = 0; i < 32; ++i)
	{
		if (data & (1u << i))
		{
			reflection |= (1u << (31 - i));
		}
	}
	return reflection;
}

/**
 * \brief Calculates CRC32 Checksum
 *
 * \param data pointer to data.
 * \param length length of array.
 * \param polynomial u32 polynomial.
 * \param crcInit u32 initializer.
 * \param finalXor u32 final XOR.
 * \param reflectInput Boolean reflect the input.
 * \param reflectOutput Boolean reflect the output.
 * \return CRC Value
 */
uint32_t calculateCRC32(uint8_t *data, size_t length, uint32_t polynomial, uint32_t crcInit, uint32_t finalXor, bool reflectInput, bool reflectOutput)
{
	uint32_t crc = crcInit;
	for (size_t i = 0; i < length; ++i)
	{
		uint32_t byte = data[i];
		if (reflectInput)
		{
			byte = reflect8((uint8_t)byte); // Reflect each byte individually
		}
		crc ^= (byte << 24); // Shift the byte to the high bits of the 32-bit CRC
		for (uint8_t j = 0; j < 8; ++j)
		{
			if (crc & 0x80000000)
			{
				crc = (crc << 1) ^ polynomial;
			}
			else
			{
				crc <<= 1;
			}
		}
	}

	if (reflectOutput)
	{
		crc = reflect32(crc);
	}
	return (crc ^ finalXor);
}

/**
 * \brief Round a floating point value to X decimal places. --
 * Example : roundfloat(3.1415927654, 2); --
 * Returns : 3.14
 * \param num F32 number
 * \param places Decimal place Count
 * \return F32 Rounded value
 */
float roundfloat(float num, uint8_t places)
{
	float scale = 1;
	for (int i = 0; i < places; i++)
	{
		scale *= 10;
	}
	if (num >= 0)
	{
		return (int)(num * scale + 0.5) / scale;
	}
	else
	{
		return (int)(num * scale - 0.5) / scale;
	}
}

/**
 * \brief Round a floating point value to X decimal places and then decimal shift X decimal places. --
 * Example : roundAndPrepare(3.1415927654, 2); --
 * Returns : 314
 * \param num F32 number
 * \param places Decimal place Count
 * \return I32 Rounded value
 */
int32_t roundfloat_to_int32(float num, uint8_t decimal_places)
{
	float scale = 1.0;
	for (uint8_t i = 0; i < decimal_places; i++)
	{
		scale *= 10.0;
	}
	// Round the number to the nearest decimal place.
	float rounded;
	if (num >= 0)
	{
		rounded = (int)(num * scale + 0.5);
	}
	else
	{
		rounded = (int)(num * scale - 0.5);
	}
	// Multiply by 10^decimal_places to shift the decimal point.
	// Convert the result to int32_t before returning.
	return (int32_t)(rounded * scale);
}

/**
 * \brief Gets Unique Serial Number of MCU.
 * \return Serial Number of MCU
 */
uint32_t getSerialNumber(void)
{
	return (uint32_t)(READ_REG(*((uint32_t *)(0x1FFF7590UL))));
}

/**
 * \brief Gets MCU Readout Protection Level.
 * \return 0 : Unlocked, 1 : Locked, 2 : Locked Indefinetely
 */
uint8_t getRDP(void)
{
	uint8_t rdp_val = 0;
	uint8_t rdplevel = 0;
	rdp_val = (uint8_t)((0xFBFFFCAA & FLASH_OPTR_RDP_Msk) >> FLASH_OPTR_RDP_Pos);
	if (rdp_val == 0xAA)
	{
		rdplevel = 0;
	}
	else if (rdp_val == 0xCC)
	{
		rdplevel = 2;
	}
	else
	{
		rdplevel = 1;
	}
	return rdplevel;
}
/**
 * \brief Sets Readout Protection Level.
 * \note Setting Readout Protection disables debugging..
 *
 * \return 0 : Unlocked or no change, 1 : Locked
 */
uint8_t setRDP(bool on)
{
	uint8_t returnval = 0;
	uint8_t level = getRDP();
	if ((level == 0) & (on == true))
	{
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		FLASH_OBProgramInitTypeDef obConfig;
		obConfig.OptionType = OPTIONBYTE_RDP;
		obConfig.RDPLevel = 0xBB;
		HAL_FLASHEx_OBProgram(&obConfig);
		HAL_FLASH_OB_Launch();
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
		returnval = 1;
	}
	else if ((level != 0) & (on == false))
	{
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		FLASH_OBProgramInitTypeDef obConfig;
		obConfig.OptionType = OPTIONBYTE_RDP;
		obConfig.RDPLevel = 0xAA;
		HAL_FLASHEx_OBProgram(&obConfig);
		HAL_FLASH_OB_Launch();
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
		returnval = 0;
	}
	return returnval;
}

/* Initialize Powerdown Voltage Detection*/
void init_PVD()
{
	PWR_PVDTypeDef sconfigPVD;
	sconfigPVD.PVDLevel = PWR_CR2_PLS_LEV6; // 2.9 Volt Threshold Level 6
	sconfigPVD.Mode = PWR_PVD_MODE_IT_RISING_FALLING;
	HAL_PWR_ConfigPVD(&sconfigPVD);
	HAL_PWR_EnablePVD();
}

void HAL_PWR_PVDCallback()
{
	// events_Shutdown();
}

/* Read 8 bit unsigned value from address */
uint8_t read_uint8_t_from_address(void *address)
{
	return *(uint8_t *)address;
}

/* Read 8 bit signed value from address */
int8_t read_int8_t_from_address(void *address)
{
	return *(int8_t *)address;
}

/* Read 16 bit unsigned value from address */
uint16_t read_uint16_t_from_address(void *address)
{
	return *(uint16_t *)address;
}

/* Read 16 bit signed value from address */
int16_t read_int16_t_from_address(void *address)
{
	return *(int16_t *)address;
}

/* Read 32 bit unsigned value from address */
uint32_t read_uint32_t_from_address(void *address)
{
	return *(uint32_t *)address;
}

/* Read 32 bit signed value from address */
int32_t read_int32_t_from_address(void *address)
{
	return *(uint32_t *)address;
}

/* Read float value from address */
float read_float_from_address(void *address)
{
	return *(float *)address;
}

/* Read character array from address */
char *read_char_array_from_address(const void *source, size_t length)
{
	char *dest = malloc(length * sizeof(char));
	if (dest == NULL)
	{
		return NULL; // Allocation failed
	}

	const char *charSource = (const char *)source;
	memcpy(dest, charSource, length);
	return dest;
}

/**
 * \brief Writes OnBoard LED
 * \param led LED_1.
 * \param high Boolean.
 */
void writeLED(gpio_LED led, bool high)
{
	if (led == LED_1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, high);
	}
}

/**
 * \brief Toggles OnBoard LED
 * \param led LED_1.
 */
void toggleLED(gpio_LED led)
{
	if (led == LED_1)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
	}
}

/* Flash Back Data to the last Page in FLASH Memory */
void writeFlash(uint32_t page, uint8_t *Data, uint16_t dataSize)
{
	if ((storecompleted == false) && (page > 30))
	{
		static FLASH_EraseInitTypeDef EraseInitStruct;
		uint32_t PAGEError;

		/* Unlock the Flash to enable the flash control register access *************/
		HAL_FLASH_Unlock();
		/* Erase the user Flash area*/
		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.Banks = FLASH_BANK_1;
		EraseInitStruct.Page = 31;
		EraseInitStruct.NbPages = 1;

		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
		{
			/*Error occurred while page erase.*/
			HAL_FLASH_GetError();
		}
		/* Program the user Flash area word by word*/
		uint32_t pageaddress = 2048 * page + 0x08000000;
		uint16_t j = 0;
		HAL_StatusTypeDef status;
		for (uint32_t i = 0; i < dataSize; i += 8)
		{
			uint64_t writeValue = 0;

			// Construct the double word from the data array
			for (int k = 0; k < 8; ++k)
			{
				if (i + k < dataSize)
				{
					writeValue |= ((uint64_t)Data[j + k]) << (k * 8);
				}
			}

			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, pageaddress, writeValue);
			if (status == HAL_OK)
			{
				pageaddress += 8;
				j += 8;
			}
			else
			{
				// Handle error
				break;
			}
		}
		HAL_FLASH_Lock();
		storecompleted = true;
	}
}

/**
 * \brief HAL UART Transmit Complete Callback
 * \param huart UART handle.
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (uart_array == 0)
	{
		memset(array1.array, 0, sizeof(array1.array));
		array1.length = 0;
		uart_sending = false;
	}
	else if (uart_array == 1)
	{
		memset(array0.array, 0, sizeof(array0.array));
		array0.length = 0;
		uart_sending = false;
	}
}
/**
 * \brief Message(s) to be Sent to Serial Terminal..
 */
void serialPrint(const char *str)
{
	uint16_t str_length = strlen(str);
	if (uart_array == 0)
	{
		if (array0.length + str_length < UART_MSG_BUFFER_SIZE)
		{
			memcpy(&array0.array[array0.length], str, str_length);
			array0.length += str_length;
		}
		else
		{
			// Handle overflow, e.g., log error
			// Message dropped due to buffer overflow - array0 full
		}
	}
	else if (uart_array == 1)
	{
		if (array1.length + str_length < UART_MSG_BUFFER_SIZE)
		{
			memcpy(&array1.array[array1.length], str, str_length);
			array1.length += str_length;
		}
		else
		{
			// Handle overflow, e.g., log error
			// Message dropped due to buffer overflow - array1 full
		}
	}
	else
	{
		// Handle invalid array_selector, e.g., log error
	}
}

/**
 * \brief Write binary data to Serial Terminal
 * \param data Pointer to binary data buffer
 * \param length Number of bytes to write
 */
void serialWrite(const uint8_t *data, uint16_t length)
{
	if (uart_array == 0)
	{
		if (array0.length + length < UART_MSG_BUFFER_SIZE)
		{
			memcpy(&array0.array[array0.length], data, length);
			array0.length += length;
		}
		else
		{
			// Handle overflow, e.g., log error
			// Binary data dropped due to buffer overflow - array0 full
		}
	}
	else if (uart_array == 1)
	{
		if (array1.length + length < UART_MSG_BUFFER_SIZE)
		{
			memcpy(&array1.array[array1.length], data, length);
			array1.length += length;
		}
		else
		{
			// Handle overflow, e.g., log error
			// Binary data dropped due to buffer overflow - array1 full
		}
	}
	else
	{
		// Handle invalid array_selector, e.g., log error
	}
}

/**
 * \brief Backend Function to Send Messages to Serial Terminal
 */
void tx_Serial_Comms()
{
	if (uart_sending == false)
	{
		if (uart_array == 0 && array0.length > 0)
		{
			uart_array ^= 1;
			uart_sending = true;
			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)array0.array, array0.length);
		}
		else if (uart_array == 1 && array1.length > 0)
		{
			uart_array ^= 1;
			uart_sending = true;
			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)array1.array, array1.length);
		}
	}
}

/**
 * \brief Processes CAN Data to return ieee754 value.
 * \param value : Value to look at
 * \param bitmask : the Bitmask to read and right shift data if necessary
 * \param is_signed : if the Data type is Signed, True.
 * \param factor : DBC Factor.
 * \param offset : DBC Offset.
 * \param decimal_places : the amount of digits to the right to round to
 * \return Float Value.
 */
float process_ieee754(uint32_t value, uint32_t bitmask, float factor, float offset, uint8_t decimal_places)
{
	// Find the least significant bit set (LSB position)
	int lsbset = __builtin_ctz(bitmask);

	// Apply the bitmask and shift the value accordingly
	uint32_t result = (value & bitmask) >> lsbset;

	// Interpret the result as an IEEE 754 float
	union
	{
		uint32_t uint_value;
		float float_value;
	} converter;

	converter.uint_value = result;
	float ieee754_value = converter.float_value;

	// Apply factor and offset
	float processed_value = ieee754_value * factor + offset;

	// Apply rounding
	float rounding_factor = powf(10.0f, decimal_places);
	processed_value = roundf(processed_value * rounding_factor) / rounding_factor;

	return processed_value;
}

/**
 * \brief Processes CAN Data from DBC Details and Data Array.
 * \param data : The Message Bytes (Message.data)
 * \param datatype : DBC Datatype Enumeration, DBC_UNSIGNED = 0, DBC_SIGNED = 1, DBC_FLOAT = 2, DBC_DOUBLE = 4
 * \param is_big_endian : True for Big Endian/Motorola/MSB/Normal, False for Little Endian/Intel/LSB/Word Swap
 * \param dbc_start_bit : The Starting bit in DBC file
 * \param dbc_bit_length : The bit length in DBC file
 * \param factor : DBC Factor.
 * \param offset : DBC Offset.
 * \param decimal_places : the amount of digits to the right to round to
 * \return Float Value.
 */
double dbc_decode(const uint8_t *data, datatype_t datatype, bool is_big_endian, uint8_t dbc_start_bit, uint8_t dbc_bit_length, float factor, float offset, uint8_t decimal_places)
{
	uint64_t value = 0;

	// Calculate initial byte and bit index.
	int byte_index = dbc_start_bit / 8;
	int bit_index = dbc_start_bit % 8;

	// Extract bits one by one.
	for (uint8_t i = 0; i < dbc_bit_length; i++)
	{
		// Extract the bit at the current position.
		value |= ((data[byte_index] & (1 << bit_index)) >> bit_index) << i;

		// Move to the next bit.
		bit_index++;
		if (bit_index == 8)
		{
			bit_index = 0;
			if (is_big_endian)
			{
				// For big-endian, move to the previous byte.
				byte_index -= 1;
			}
			else
			{
				// For little-endian, move to the next byte.
				byte_index += 1;
			}
		}
	}

	// If the datatype is DBC_DOUBLE, use the DoubleUnion_t to convert the 64 bits.
	if (datatype == DBC_DOUBLE && dbc_bit_length == 64)
	{

		DoubleUnion_t du;
		// Copy each byte from value into the union.
		for (int i = 0; i < 8; i++)
		{
			du.bytes[i] = (value >> (i * 8)) & 0xFF;
		}
		return du.f64;
	}

	// If the datatype is DBC_FLOAT, use the FloatUnion_t to convert the 32 bits.
	if (datatype == DBC_FLOAT && dbc_bit_length == 32)
	{

		FloatUnion_t fu;
		// Copy each byte from value into the union.
		for (int i = 0; i < 4; i++)
		{
			fu.bytes[i] = (value >> (i * 8)) & 0xFF;
		}
		return fu.f32;
	}

	// For non-floating point types, perform sign extension if the signal is signed.
	int64_t signed_value = value;
	if (datatype == DBC_SIGNED && (value & (1ULL << (dbc_bit_length - 1))))
	{
		signed_value = value - (1LL << dbc_bit_length);
	}

	// Apply factor and offset.
	double result = (double)signed_value * factor + offset;

	// Round to the specified number of decimal places.
	double scaling = pow(10.0, decimal_places);
	result = round(result * scaling) / scaling;

	return result;
}


/**
 * \brief Processes CAN Data from DBC Details and Data Array.
 * \param data : The Message Bytes
 * \param msg_data_length : The data length of the Array.
 * \param datatype : DBC Datatype Enumeration, DBC_UNSIGNED = 0, DBC_SIGNED = 1, DBC_FLOAT = 2, DBC_DOUBLE = 4
 * \param is_big_endian : True for Big Endian/Motorola/MSB/Normal, False for Little Endian/Intel/LSB/Word Swap
 * \param dbc_start_bit : The Starting bit in DBC file
 * \param dbc_bit_length : The bit length in DBC file
 * \param factor : DBC Factor.
 * \param offset : DBC Offset.
 * \return 0 if Successful, -1 | -2 if bitrange is invalid.
 */
int dbc_encode(uint8_t *data, size_t msg_data_length, datatype_t datatype, bool is_big_endian, double scaled_value, uint8_t dbc_start_bit, uint8_t dbc_bit_length, float factor, float offset)
{
	// Check if the bit range fits into the provided array.
	if (!is_big_endian)
	{
		// Little-endian: Check that signal fits in total bits of the message.
		if (dbc_start_bit + dbc_bit_length > msg_data_length * 8)
		{
			return -1; // Not enough space.
		}
	}
	else
	{
		// Big-endian: Check that the signal does not underflow past the first byte.
		int starting_byte = dbc_start_bit / 8;
		int starting_bit = dbc_start_bit % 8;
		int available_bits = (starting_byte + 1) * 8 - starting_bit;
		if (dbc_bit_length > available_bits)
		{
			return -1; // Not enough space.
		}
	}

	// Convert the scaled value to a raw integer representation.
	int64_t raw = 0;

	// If the datatype is DBC_DOUBLE and the bit length is 64, use the DoubleUnion_t.
	if (datatype == DBC_DOUBLE && dbc_bit_length == 64)
	{

		DoubleUnion_t du;
		du.f64 = scaled_value;
		// Build the raw 64-bit integer from the union's bytes.
		for (int i = 0; i < 8; i++)
		{
			raw |= ((uint64_t)du.bytes[i]) << (i * 8);
		}
	}
	// If the datatype is DBC_FLOAT and the bit length is 32, use the FloatUnion_t.
	else if (datatype == DBC_FLOAT && dbc_bit_length == 32)
	{

		FloatUnion_t fu;
		fu.f32 = (float)scaled_value;
		// Build the raw 32-bit integer from the union's bytes.
		for (int i = 0; i < 4; i++)
		{
			raw |= ((uint64_t)fu.bytes[i]) << (i * 8);
		}
	}
	// Otherwise, handle the value as an integer signal.
	else
	{
		double temp = (scaled_value - offset) / factor;
		raw = (int64_t)round(temp);

		// If the signal is signed and raw is negative, convert it to two's complement.
		if (datatype == DBC_SIGNED && raw < 0)
		{
			raw = (1LL << dbc_bit_length) + raw;
		}
	}

	// Calculate the initial byte and bit index.
	int byte_index = dbc_start_bit / 8;
	int bit_index = dbc_start_bit % 8;

	// Encode each bit of the raw value into the data array.
	for (uint8_t i = 0; i < dbc_bit_length; i++)
	{
		uint8_t bit = (raw >> i) & 1;
		if (bit)
			data[byte_index] |= (1 << bit_index);
		else
			data[byte_index] &= ~(1 << bit_index);

		// Advance the bit index.
		bit_index++;
		if (bit_index == 8)
		{
			bit_index = 0;
			// Update the byte index based on endianness.
			if (is_big_endian)
				byte_index--; // For big-endian, move to the previous byte.
			else
				byte_index++; // For little-endian, move to the next byte.

			// Check that the new byte_index is still valid.
			if (byte_index < 0 || (size_t)byte_index >= msg_data_length)
			{
				return -2; // This should not happen if the input bit range is valid.
			}
		}
	}
	return 0;
}

/**
 * \brief Processes CAN Data to return a Float.
 * \param value : Value to look at
 * \param bitmask : the Bitmask to read and right shift data if necessary
 * \param is_signed : if the Data type is Signed, True.
 * \param factor : DBC Factor.
 * \param offset : DBC Offset.
 * \param decimal_places : the amount of digits to the right to round to
 * \return Float Value.
 */
float process_float_value(uint32_t value, uint32_t bitmask, bool is_signed, float factor, float offset, int8_t decimal_places)
{
	// Find the least significant bit set (LSB position)
	int lsbset = __builtin_ctz(bitmask);

	// Shift value and bitmask if LSB is not at position 0
	if (lsbset > 0)
	{
		value >>= lsbset;
		bitmask >>= lsbset;
	}

	// Identify the number of bits used
	int bit_length = 32 - __builtin_clz(bitmask); // Total bits in the bitmask
	uint32_t sign_bit = 1 << (bit_length - 1);	  // The sign bit location

	int32_t signed_value;
	if (is_signed && (value & sign_bit))
	{
		// Convert value to signed two's complement
		signed_value = (int32_t)(value | ~bitmask);
	}
	else
	{
		signed_value = (int32_t)value;
	}

	// Apply factor and offset
	float localvalue1 = signed_value * factor + offset;

	// Apply rounding
	float rounding_factor = powf(10.0f, decimal_places);
	localvalue1 = roundf(localvalue1 * rounding_factor) / rounding_factor;

	return localvalue1;
}
/**
 * \brief Processes CAN Data to return an Integer.
 * \param value : Value to look at
 * \param bitmask : the Bitmask to read and right shift data if necessary
 * \param is_signed : if the Data type is Signed, True.
 * \param factor : DBC Factor.
 * \param offset : DBC Offset.
 * \return Signed Integer Value.
 */
int32_t process_int_value(uint32_t value, uint32_t bitmask, bool is_signed, int32_t factor, int32_t offset)
{
	// Find the least significant bit set (LSB position)
	int lsbset = __builtin_ctz(bitmask);

	// Shift value and bitmask if LSB is not at position 0
	if (lsbset > 0)
	{
		value >>= lsbset;
		bitmask >>= lsbset;
	}

	// Identify the number of bits used
	int bit_length = 32 - __builtin_clz(bitmask); // Total bits in the bitmask
	uint32_t sign_bit = 1 << (bit_length - 1);	  // The sign bit location

	int32_t signed_value;
	if (is_signed && (value & sign_bit))
	{
		// Convert value to signed two's complement
		signed_value = (int32_t)(value | ~bitmask);
	}
	else
	{
		signed_value = (int32_t)value;
	}

	// Apply factor and offset
	int32_t localvalue1 = signed_value * factor + offset;

	return localvalue1;
}

/**
 * \brief Processes CAN Data to return an Unsigned Integer.
 * \param value : Value to look at
 * \param bitmask : the Bitmask to read and right shift data if necessary
 * \param factor : DBC Factor.
 * \param offset : DBC Offset.
 * \return Unsigned Integer Value.
 */
uint32_t process_unsigned_int_value(uint32_t value, uint32_t bitmask, uint32_t factor, uint32_t offset)
{
	// Find the least significant bit set (LSB position)
	int lsbset = __builtin_ctz(bitmask);

	// Shift value and bitmask if LSB is not at position 0
	if (lsbset > 0)
	{
		value >>= lsbset;
		bitmask >>= lsbset;
	}

	// Extract the relevant bits
	uint32_t result = value & bitmask;

	// Apply factor and offset
	result = result * factor + offset;

	return result;
}

/**
 * \brief Processes CAN Data to masked and shifted value.
 * \param value : Which bytes to look at
 * \param bitmask : the Bitmask to read and right shift data if necessary
 * \return Uint32_t Value
 */
uint32_t process_raw_value(uint32_t value, uint32_t bitmask)
{
	// Find the least significant bit set (LSB position)
	int lsbset = __builtin_ctz(bitmask);

	// Apply the bitmask and shift the value accordingly
	uint32_t result = (value & bitmask) >> lsbset;

	return result;
}

/**
 * \brief Prepares a signal to be Transmitted over CAN using DBC Factors and Offsets
 * \param value : Current value.
 * \param bitlength : the total bitlength of the output signal.
 * \param is_signed : false if unsigned, true if signed.
 * \param dbcFactor : the DBC Factor, usually a value between 0 and 1..
 * \param dbcOffset : the DBC Offset.
 * \return int32_t Value
 */
uint32_t prepare_output_signal(float value, uint8_t bitlength, bool is_signed, float dbcFactor, float dbcOffset)
{
	if (bitlength > 32)
	{
		//printf("Error: Bit length cannot exceed 32 bits\n");
		return 0;
	}

	// Apply inverse factor and offset
	value = (value - dbcOffset) / dbcFactor;

	uint32_t result = 0;

	if (is_signed)
	{
		int32_t int_value = (int32_t)round(value);

		int32_t min_value = -(1 << (bitlength - 1));
		int32_t max_value = (1 << (bitlength - 1)) - 1;

		// Constrain within signed bit range
		if (int_value < min_value)
			int_value = min_value;
		if (int_value > max_value)
			int_value = max_value;

		// Convert to two's complement for negative values
		if (int_value < 0)
		{
			int_value = (1 << bitlength) + int_value; // Two's complement conversion
		}

		result = (uint32_t)int_value & ((1U << bitlength) - 1);
	}
	else
	{
		// First constrain the float
		if (value < 0.0f) 
			value = 0.0f;

		uint32_t max_value = (bitlength == 32) ? 0xFFFFFFFF : ((1U << bitlength) - 1);

		if (value > (float)max_value)
			value = (float)max_value;

		uint32_t uint_value = (uint32_t)round(value);
		result = uint_value & max_value;
	}

	return result;
}

/**
 * \brief Scales (Maps) an integer value to fixed integer scalings (extrapolates)
 * \param x : Current value.
 * \param in_min : the input scaling input minimum.
 * \param in_max : the input scaling input maximum.
 * \param out_min : the output scaling input minimum.
 * \param out_max : the output scaling input maximum.
 * \return int32_t Value
 */
int32_t map_int(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * \brief Scales (Maps) an floating point value to scalings (extrapolates)
 * \param x : Current value.
 * \param in_min : the input scaling input minimum.
 * \param in_max : the input scaling input maximum.
 * \param out_min : the output scaling input minimum.
 * \param out_max : the output scaling input maximum.
 * \return float Value
 */
float map_float(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * \brief Scales (Maps) an integer value to fixed integer scalings (constrains to min and max output)
 * \param x : Current value.
 * \param in_min : the input scaling input minimum.
 * \param in_max : the input scaling input maximum.
 * \param out_min : the output scaling input minimum.
 * \param out_max : the output scaling input maximum.
 * \return int32_t Value
 */
int32_t clamped_map_int(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
	if (x < in_min)
	{
		x = in_min;
	}
	else if (x > in_max)
	{
		x = in_max;
	}
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * \brief Scales (Maps) an floating point value to fixed integer scalings (constrains to min and max output)
 * \param x : Current value.
 * \param in_min : the input scaling input minimum.
 * \param in_max : the input scaling input maximum.
 * \param out_min : the output scaling input minimum.
 * \param out_max : the output scaling input maximum.
 * \return float Value
 */
float clamped_map_float(float x, float in_min, float in_max, float out_min, float out_max)
{
	if (x < in_min)
	{
		x = in_min;
	}
	else if (x > in_max)
	{
		x = in_max;
	}
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * \brief Scales a frequency to the appropriate period for a haltech I/O Expander 12 Box A or B
 * \param frequency_value : the Targeted Frequency
 * \return Period in 10uS resolution for Haltech I/O Expander
 */
uint32_t frequency_Hz_to_period_10uS(uint32_t frequency_value)
{
	if (frequency_value == 0)
	{
		return 0;
	}
	else
	{
		// output_value = (100000 / frequency_value)
		return 100000U / frequency_value;
	}
}

uint32_t period_10uS_to_frequency_Hz(uint32_t period_value)
{
	// If period_value == 0, return 0 to avoid division by zero
	if (period_value == 0)
	{
		return 0;
	}
	else
	{
		// Frequency = 100000 / period_value
		return 100000U / period_value;
	}
}

/**
 * \brief Gets a timestamp to 0.0001 seconds..
 */
float getTimestamp()
{
	uint32_t counter_value = ((&htim2)->Instance->CNT); // Direct register access
	float newcv = (((float)counter_value) / 10000.0f);
	return newcv;
}

char *format_CAN_message(const CAN_Message *msg, char *buffer, size_t buf_size)
{
	int offset = 0;
	float ts = getTimestamp();
	offset += snprintf(buffer + offset, buf_size - offset, "(%011.4f) ", ts);
	// Format the bus and arbitration ID.
	if (msg->is_extended_id)
	{
		offset += snprintf(buffer + offset, buf_size - offset, "%u %08lX#", (8 - __builtin_clz(msg->Bus) + 24), msg->arbitration_id);
	}
	else
	{
		offset += snprintf(buffer + offset, buf_size - offset, "%u %03lX#", (8 - __builtin_clz(msg->Bus) + 24), msg->arbitration_id & 0x7FF);
	}

	// Format the data bytes into hexadecimal.
	for (int i = 0; i < msg->dlc && i < CAN_MSG_MAX_DLC; ++i)
	{
		offset += snprintf(buffer + offset, buf_size - offset, "%02X", msg->data[i]);
	}

	return buffer;
}


/**
 * \brief First Order Low Pass Filter driven by a frequency timebase.
 * \param basevalue The Original Averaged Value
 * \param newvalue The new Value to add to the Average
 * \param time_constant The Time Constant for averaging
 * \param freqency The frequency in Hz for the function call
 * \return updated Averaged Value
 */
float lowpass_filter_by_frequency(float basevalue, float newvalue, float time_constant, float frequency)
{
    float dt = 1.0f / frequency;
    float alpha = dt / (time_constant + dt);
    return basevalue + alpha * (newvalue - basevalue);
}

/**
 * \brief First Order Low Pass Filter driven from a delta timebase
 * \param basevalue The Original Averaged Value
 * \param newvalue The new Value to add to the Average
 * \param time_constant The Time Constant for averaging
 * \param freqency The frequency in Hz for the function call
 * \return updated Averaged Value
 */
float lowpass_filter_by_timedelta(float basevalue, float newvalue,  float time_constant, float last_timestamp, float current_timestamp)
{
    float dt = current_timestamp - last_timestamp;
    if (dt <= 0.0f) return basevalue;   // protect from bad timestamps

    float alpha = dt / (time_constant + dt);
    return basevalue + alpha * (newvalue - basevalue);
}
