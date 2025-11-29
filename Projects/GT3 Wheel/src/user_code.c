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
#include <stdio.h>

/* End File Includes */

/* Variable Declarations */
uint32_t serialnumber;
double testval = 0.0f;

/* ---------------------------------------------------------------------------
 * Config / constants
 * -------------------------------------------------------------------------*/

// IDs
#define ID_STEERING_CLUTCH      0xBF   // steering wheel clutch message (ID_0x0BF)
#define ID_BLINK_KEYPAD_IO      0x195  // Blink keypad I/O
#define ID_BLINK_KEYPAD_LED     0x215  // Blink keypad illumination
#define ID_BLINK_HEARTBEAT      0x715  // Blink keypad heartbeat
#define ID_THROTTLE_DEMAND      0x6DE  // DBWC throttle demand

// Blink keypad button codes (Data0)
#define BTN_CLUTCH_MODE         0x01
#define BTN_THROTTLE_MODE       0x02

// Throttle demand encoding (byte 0 = 0–100 %)
#define THROTTLE_MIN_PCT        0.0f
#define THROTTLE_MAX_PCT        100.0f

/*
 * 0xBF layout from DBC (Intel / little-endian, @0+):
 *
 *   B0_Validation        : 7|8@0+   (byte 0)
 *   B1_Counter05to15     : 15|8@0+  (byte 1)
 *   B2_alway00           : 23|8@0+  (byte 2)
 *   b24L1_0or1           : 24|1@0+  (bit 24)
 *   b25_L7_always30      : 31|7@0+  (bits 25..31)
 *   b32L4                : 35|4@0+
 *   b36L2_always_2       : 37|2@0+
 *   b38L2                : 39|2@0+
 *   b44L2_unknown        : 45|2@0+
 *   b46L2_Always_0       : 47|2@0+
 *   b50L10_Clutch_A      : 43|10@0+
 *   b60L10_Clutch_B      : 49|10@0+
 *
 * Clutch_A (43|10) and Clutch_B (49|10) overlap in bit-space, they’re two
 * redundant views over the same region. Decode both independently
 * and use their average as a 10-bit “clutch raw” in [0..1023] for throttle mapping.
 */

// Clutch 10-bit interpretation
#define CLUTCH10_RAW_MIN_VALID    0u
#define CLUTCH10_RAW_MAX_VALID    1023u
#define CLUTCH10_MAX_STEP_RAW     150u     // max allowed jump between frames (tune on car)
#define CLUTCH10_FULL_SCALE       1023u

// Clutch_A / Clutch_B DBC start bits and lengths
#define CLUTCH_A_START_BIT        43u
#define CLUTCH_A_LENGTH_BITS      10u
#define CLUTCH_B_START_BIT        49u
#define CLUTCH_B_LENGTH_BITS      10u

// "Static" clutch value when in throttle mode, sent to the car on 0xBF B6/B7.
// This is the OEM 0% clutch pattern measured from logs (16-bit composite).
#define CLUTCH_RAW_STATIC_0PCT    0xDAE8u

// Throttle filtering / slew limiting
#define THROTTLE_MAX_STEP_PER_FRAME  10u    // max +-10% change per 0xBF frame
#define THROTTLE_FILTER_ALPHA        0.5f   // 0..1, 1=none, smaller=more smoothing

// Timeouts
#define BF_TIMEOUT_TICKS_100HZ       50     // 50 ticks @100Hz ≈ 0.5s
#define BLINK_HB_TIMEOUT_TICKS_5HZ   10     // 10 ticks @5Hz  ≈ 2.0s

/* ---------------------------------------------------------------------------
 * Mode state / failsafe
 * -------------------------------------------------------------------------*/

typedef enum
{
    MODE_CLUTCH = 0,
    MODE_THROTTLE = 1
} gateway_mode_t;

static gateway_mode_t g_mode        = MODE_CLUTCH;
static bool           g_failsafe    = false;   // when true, always pure pass-through

// Clutch plausibility (on derived 10-bit raw)
static uint16_t g_last_clutch_raw   = 0;
static bool     g_have_last_clutch  = false;

// Throttle filtering
static uint8_t g_last_throttle_byte = 0;
static bool    g_have_last_throttle = false;
static float   g_throttle_filtered  = 0.0f;

// 0xBF timeout
static uint16_t g_bf_timeout_counter = 0;
static bool     g_bf_seen_ever       = false;

// Blink keypad heartbeat timeout
static uint16_t g_blink_hb_miss_counter = 0;
static bool     g_blink_hb_seen         = false;

// CAN error monitoring (previous snapshot)
static CAN_ErrorCounts g_prev_err_can1 = {0};
static CAN_ErrorCounts g_prev_err_can2 = {0};
static CAN_ErrorCounts g_prev_err_can3 = {0};
static bool            g_prev_err_valid = false;

/* ---------------------------------------------------------------------------
 * Helpers
 * -------------------------------------------------------------------------*/

static float clampf(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

/**
 * Extract bits from a CAN payload according to DBC Intel (=little-endian) semantics:
 *  - start_bit: bit index (0 = LSB of byte 0)
 *  - length:    number of bits
 * Bits are returned with bit 0 = value of start_bit, bit 1 = next, etc.
 */
static uint16_t extract_bits_le(const uint8_t *data, uint8_t start_bit, uint8_t length)
{
    uint32_t value = 0;

    for (uint8_t i = 0; i < length; i++)
    {
        uint8_t bit_index   = (uint8_t)(start_bit + i);
        uint8_t byte_index  = (uint8_t)(bit_index / 8u);
        uint8_t bit_in_byte = (uint8_t)(bit_index % 8u);

        uint8_t bit = (data[byte_index] >> bit_in_byte) & 0x01u;
        value |= ((uint32_t)bit << i);
    }

    return (uint16_t)value;
}

/**
 * Convert a 10-bit clutch raw value [0..1023] to percent [0..100].
 * Linear mapping using the DBC's 0..1023 range.
 */
static float clutch10_to_percent(uint16_t raw10)
{
    if (raw10 > CLUTCH10_FULL_SCALE)
        raw10 = CLUTCH10_FULL_SCALE;

    float pct = (100.0f * (float)raw10) / (float)CLUTCH10_FULL_SCALE;
    return clampf(pct, THROTTLE_MIN_PCT, THROTTLE_MAX_PCT);
}

/**
 * Plausibility check on derived 10-bit clutch raw value.
 *  - Range check
 *  - Rate-of-change check vs last frame
 */
static bool clutch_plausible(uint16_t raw10)
{
    if (raw10 < CLUTCH10_RAW_MIN_VALID || raw10 > CLUTCH10_RAW_MAX_VALID)
    {
        return false;
    }

    if (g_have_last_clutch)
    {
        uint16_t diff = (raw10 > g_last_clutch_raw)
                            ? (raw10 - g_last_clutch_raw)
                            : (g_last_clutch_raw - raw10);
        if (diff > CLUTCH10_MAX_STEP_RAW)
        {
            return false;
        }
    }

    g_last_clutch_raw  = raw10;
    g_have_last_clutch = true;
    return true;
}

/* Checksum for 0xBF Data0 (B0_Validation)
 */
static uint8_t bf_compute_data0(uint8_t dlc,
                                uint8_t d1, uint8_t d2,
                                uint8_t d3, uint8_t d4,
                                uint8_t d5, uint8_t d6, uint8_t d7)
{
    // helper to get bit
    #define B(v, bit) (((v) >> (bit)) & 1u)

    // Output bit 0
    uint8_t b0 = (uint8_t)(
        B(d1, 0) ^ B(d1, 2) ^
        B(d4, 7) ^
        B(d5, 0) ^ B(d5, 1) ^
        B(d6, 2) ^ B(d6, 5) ^ B(d6, 7) ^
        B(d7, 0) ^ B(d7, 4) ^ B(d7, 5) ^ B(d7, 6)
    );

    // Output bit 1
    uint8_t b1 = (uint8_t)(
        B(dlc, 3) ^
        B(d1, 1) ^ B(d1, 3) ^
        B(d3, 0) ^
        B(d5, 0) ^ B(d5, 1) ^ B(d5, 2) ^
        B(d6, 3) ^ B(d6, 6) ^
        B(d7, 1) ^ B(d7, 5) ^ B(d7, 6) ^ B(d7, 7)
    );

    // Output bit 2
    uint8_t b2 = (uint8_t)(
        B(dlc, 3) ^
        B(d1, 0) ^
        B(d4, 6) ^ B(d4, 7) ^
        B(d5, 0) ^ B(d5, 2) ^ B(d5, 3) ^
        B(d6, 0) ^ B(d6, 2) ^ B(d6, 4) ^ B(d6, 5) ^
        B(d7, 0) ^ B(d7, 2) ^ B(d7, 4) ^ B(d7, 5) ^ B(d7, 7)
    );

    // Output bit 3
    uint8_t b3 = (uint8_t)(
        B(d1, 0) ^ B(d1, 1) ^ B(d1, 2) ^
        B(d3, 0) ^
        B(d5, 0) ^ B(d5, 3) ^ B(d5, 4) ^
        B(d6, 2) ^ B(d6, 3) ^ B(d6, 6) ^ B(d6, 7) ^
        B(d7, 0) ^ B(d7, 1) ^ B(d7, 3) ^ B(d7, 4)
    );

    // Output bit 4
    uint8_t b4 = (uint8_t)(
        B(d1, 0) ^ B(d1, 1) ^ B(d1, 3) ^
        B(d4, 6) ^ B(d4, 7) ^
        B(d5, 4) ^ B(d5, 5) ^
        B(d6, 0) ^ B(d6, 3) ^ B(d6, 4) ^ B(d6, 5) ^
        B(d7, 0) ^ B(d7, 1) ^ B(d7, 2) ^ B(d7, 6)
    );

    // Output bit 5
    uint8_t b5 = (uint8_t)(
        B(dlc, 3) ^
        B(d1, 1) ^ B(d1, 2) ^
        B(d3, 0) ^
        B(d4, 7) ^
        B(d5, 5) ^
        B(d6, 2) ^ B(d6, 4) ^ B(d6, 5) ^ B(d6, 6) ^
        B(d7, 1) ^ B(d7, 2) ^ B(d7, 3) ^ B(d7, 7)
    );

    // Output bit 6
    uint8_t b6 = (uint8_t)(
        B(d1, 0) ^ B(d1, 2) ^ B(d1, 3) ^
        B(d3, 0) ^
        B(d6, 0) ^ B(d6, 3) ^ B(d6, 5) ^ B(d6, 6) ^ B(d6, 7) ^
        B(d7, 2) ^ B(d7, 3) ^ B(d7, 4)
    );

    // Output bit 7
    uint8_t b7 = (uint8_t)(
        B(d1, 1) ^ B(d1, 3) ^
        B(d4, 6) ^
        B(d5, 0) ^
        B(d6, 0) ^ B(d6, 4) ^ B(d6, 6) ^ B(d6, 7) ^
        B(d7, 3) ^ B(d7, 4) ^ B(d7, 5)
    );

    #undef B

    uint8_t data0 =
        (uint8_t)((b0      ) |
                  (b1 << 1) |
                  (b2 << 2) |
                  (b3 << 3) |
                  (b4 << 4) |
                  (b5 << 5) |
                  (b6 << 6) |
                  (b7 << 7));

    return data0;
}

/* ---------------------------------------------------------------------------
 * Failsafe handling
 * -------------------------------------------------------------------------*/

static void send_keypad_illumination(gateway_mode_t mode); // forward declaration

static void enter_failsafe(const char *reason)
{
    if (!g_failsafe)
    {
        g_failsafe = true;

        // In failsafe we behave like clutch/pass-through mode,
        // but log that we’ve latched into it.
        g_mode = MODE_CLUTCH;
        writeLED(LED_1, false);  // LED off to indicate clutch mode

        // Reset dynamic state so a later recovery is clean
        g_have_last_clutch   = false;
        g_have_last_throttle = false;
        g_bf_seen_ever       = false;
        g_bf_timeout_counter = 0;
        // keep blink HB flags as-is (we still want to see if it comes back)

        printf("[FAILSAFE] Entering failsafe pass-through mode: %s\r\n", reason);

        // Immediately update keypad to failsafe indication (all red)
        send_keypad_illumination(g_mode);
    }
}

/* ---------------------------------------------------------------------------
 * Mode / keypad LED handling
 * -------------------------------------------------------------------------*/

static void send_keypad_illumination(gateway_mode_t mode)
{
    uint8_t data[8] = {0};

    if (g_failsafe)
    {
        // FAILSAFE: all LEDs red: FF 00 00 00 00 00 00 00 on ID 0x215
        data[0] = 0xFF;

        send_message(CAN_3, false, ID_BLINK_KEYPAD_LED, 8, data);
        printf("[KEYPAD-LED] FAILSAFE (all red), data=[%02X %02X %02X %02X %02X %02X %02X %02X]\r\n",
               data[0], data[1], data[2], data[3],
               data[4], data[5], data[6], data[7]);
        return;
    }

    // Normal mode:
    // Clutch:   0x215 00 00 01 00 00 00 00 00
    // Throttle: 0x215 00 02 00 00 00 00 00 00
    if (mode == MODE_CLUTCH)
    {
        data[2] = 0x01;
    }
    else
    {
        data[1] = 0x02;
    }

    send_message(CAN_3, false, ID_BLINK_KEYPAD_LED, 8, data);

    printf("[KEYPAD-LED] mode=%s, data=[%02X %02X %02X %02X %02X %02X %02X %02X]\r\n",
           (mode == MODE_THROTTLE) ? "THROTTLE" : "CLUTCH",
           data[0], data[1], data[2], data[3],
           data[4], data[5], data[6], data[7]);
}

static void gateway_set_mode(gateway_mode_t new_mode)
{
    // If we were in failsafe and driver explicitly requests throttle mode,
    // clear the failsafe latch and allow normal operation again.
    if (g_failsafe && new_mode == MODE_THROTTLE)
    {
        printf("[MODE] Throttle mode requested – clearing failsafe latch\r\n");
        g_failsafe           = false;
        g_have_last_throttle = false;
        g_have_last_clutch   = false;
        g_bf_seen_ever       = false;
        g_bf_timeout_counter = 0;
    }

    g_mode = new_mode;

    // Onboard GPIO LED: ON in throttle mode, OFF otherwise
    writeLED(LED_1, (g_mode == MODE_THROTTLE) && !g_failsafe);

    send_keypad_illumination(g_mode);

    if (g_mode == MODE_THROTTLE)
    {
        printf("[MODE] Switched to THROTTLE mode\r\n");
    }
    else
    {
        if (g_failsafe)
            printf("[MODE] In CLUTCH/Failsafe pass-through mode\r\n");
        else
            printf("[MODE] Switched to CLUTCH mode\r\n");
    }
}

/* ---------------------------------------------------------------------------
 * Startup Functions
 * -------------------------------------------------------------------------*/

void events_Startup()
{
    // Bitrates:
    //  - CAN1: 1 Mbps (steering wheel)
    //  - CAN2: 1 Mbps (car)
    //  - CAN3: 500 kbps (Blink keypad + DBWC)
    setupCANbus(CAN_1, 1000000, NORMAL_MODE);
    setupCANbus(CAN_2, 1000000, NORMAL_MODE);
    setupCANbus(CAN_3, 500000,  NORMAL_MODE);

    // Termination: CAN1 & CAN2 off, CAN3 on
    setCAN_Termination(CAN_1, false);
    setCAN_Termination(CAN_2, false);
    setCAN_Termination(CAN_3, true);

    startCANbus(CAN_1);
    startCANbus(CAN_2);
    startCANbus(CAN_3);

    // Safe default: start in clutch/pass-through mode.
    g_failsafe = false;
    g_prev_err_valid = false;
    gateway_set_mode(MODE_CLUTCH);

    printf("\r\n[CAN_TRIPLE] GT3 steering/throttle gateway starting...\r\n");
    printf("[CAN_TRIPLE] CAN1=1Mbps (no term), CAN2=1Mbps (no term), CAN3=500kbps (terminated)\r\n");

    // Dump serialnumber
    printf("[INFO] serialnumber = %lu\r\n", (unsigned long)serialnumber);

    // Initial CAN error counters
    CAN_ErrorCounts e1 = getCANErrorCounts(CAN_1);
    CAN_ErrorCounts e2 = getCANErrorCounts(CAN_2);
    CAN_ErrorCounts e3 = getCANErrorCounts(CAN_3);

    printf("[CAN ERR] Startup: CAN1 Tx=%u Rx=%u Reset=%u | "
           "CAN2 Tx=%u Rx=%u Reset=%u | "
           "CAN3 Tx=%u Rx=%u Reset=%u\r\n",
           e1.TxErrorCounter, e1.RxErrorCounter, e1.BusResetCounter,
           e2.TxErrorCounter, e2.RxErrorCounter, e2.BusResetCounter,
           e3.TxErrorCounter, e3.RxErrorCounter, e3.BusResetCounter);

    // Prime previous snapshot
    g_prev_err_can1 = e1;
    g_prev_err_can2 = e2;
    g_prev_err_can3 = e3;
    g_prev_err_valid = true;
}

/* End Startup Functions */

void onSerialReceive(uint8_t *serialMessage)
{
    // UART debug hook
    // printf("%07.4f message received...\r\n",getTimestamp());
}

/* ---------------------------------------------------------------------------
 * Steering wheel 0xBF handler (ID_0x0BF from DBC)
 * -------------------------------------------------------------------------*/

static void handle_steering_0xBF_from_CAN1(CAN_Message *msg)
{
    uint8_t tx_data[8];
    memcpy(tx_data, msg->data, 8);

    // 0xBF timeout: every time we see one, reset the timer
    g_bf_timeout_counter = 0;
    g_bf_seen_ever       = true;

    // Basic sanity check: 0xBF should always be 8 bytes.
    if (msg->dlc != 8u)
    {
        enter_failsafe("0xBF DLC != 8");
    }

    // Decode Clutch_A and Clutch_B from DBC bits:
    uint16_t rawA = extract_bits_le(msg->data, CLUTCH_A_START_BIT, CLUTCH_A_LENGTH_BITS);
    uint16_t rawB = extract_bits_le(msg->data, CLUTCH_B_START_BIT, CLUTCH_B_LENGTH_BITS);

    // Combine them: use simple average as 10-bit "clutch raw"
    uint16_t raw_clutch10 = (uint16_t)((rawA + rawB) / 2u);

    if (!clutch_plausible(raw_clutch10))
    {
        enter_failsafe("0xBF clutch raw implausible (A/B)");
    }

    // If failsafe is active, always behave as simple pass-through.
    if (g_failsafe)
    {
        printf("[BF FAILSAFE] Pass-through raw frame: DLC=%u ID=0x%03lX "
               "Clutch_A=%u Clutch_B=%u\r\n",
               (unsigned)msg->dlc, (unsigned long)msg->arbitration_id,
               rawA, rawB);

        send_message(CAN_2,
                     msg->is_extended_id,
                     msg->arbitration_id,
                     msg->dlc,
                     msg->data);
        return;
    }

    float clutch_pct = clutch10_to_percent(raw_clutch10);

    if (g_mode == MODE_THROTTLE)
    {
        // Map clutch% -> throttle%, then filter + slew limit
        float throttle_pct = clutch_pct;
        throttle_pct       = clampf(throttle_pct, THROTTLE_MIN_PCT, THROTTLE_MAX_PCT);

        // Filter
        if (!g_have_last_throttle)
        {
            g_throttle_filtered  = throttle_pct;
            g_have_last_throttle = true;
        }
        else
        {
            g_throttle_filtered += THROTTLE_FILTER_ALPHA *
                                   (throttle_pct - g_throttle_filtered);
        }

        // Convert to integer, clamp
        uint8_t target_thr = (uint8_t)(g_throttle_filtered + 0.5f);
        if (target_thr > 100u)
            target_thr = 100u;

        // Slew limit
        uint8_t prev_thr = g_last_throttle_byte;
        int16_t delta    = (int16_t)target_thr - (int16_t)prev_thr;

        if (g_have_last_throttle)
        {
            if (delta > (int16_t)THROTTLE_MAX_STEP_PER_FRAME)
                target_thr = (uint8_t)(prev_thr + THROTTLE_MAX_STEP_PER_FRAME);
            else if (delta < -(int16_t)THROTTLE_MAX_STEP_PER_FRAME)
                target_thr = (uint8_t)(prev_thr - THROTTLE_MAX_STEP_PER_FRAME);
        }

        g_last_throttle_byte = target_thr;

        // Send throttle demand on CAN3, ID 0x6DE, byte 0
        uint8_t thr_msg[8] = {0};
        thr_msg[0] = target_thr;
        send_message(CAN_3, false, ID_THROTTLE_DEMAND, 8, thr_msg);

        // Freeze clutch bytes towards the car using the known 0% 
        tx_data[6] = (uint8_t)(CLUTCH_RAW_STATIC_0PCT >> 8);
        tx_data[7] = (uint8_t)(CLUTCH_RAW_STATIC_0PCT & 0xFF);

        // Recalculate validation byte (B0_Validation) based on modified bytes 1..7
        uint8_t new_validation = bf_compute_data0(msg->dlc,
                                                  tx_data[1], tx_data[2],
                                                  tx_data[3], tx_data[4],
                                                  tx_data[5], tx_data[6],
                                                  tx_data[7]);
        tx_data[0] = new_validation;

        printf("[BF THR] Clutch_A=%u Clutch_B=%u raw10=%u clutch_pct=%.1f "
               "thr_cmd=%3u filtered=%.1f val=0x%02X "
               "rx=[%02X %02X %02X %02X %02X %02X %02X %02X] "
               "tx=[%02X %02X %02X %02X %02X %02X %02X %02X]\r\n",
               rawA, rawB, raw_clutch10, clutch_pct,
               target_thr, g_throttle_filtered,
               (unsigned)new_validation,
               msg->data[0], msg->data[1], msg->data[2], msg->data[3],
               msg->data[4], msg->data[5], msg->data[6], msg->data[7],
               tx_data[0], tx_data[1], tx_data[2], tx_data[3],
               tx_data[4], tx_data[5], tx_data[6], tx_data[7]);
    }
    else
    {
        // In clutch mode, log and pass-through (0xBF unchanged)
        printf("[BF CLU] Clutch_A=%u Clutch_B=%u raw10=%u clutch_pct=%.1f "
               "rx=[%02X %02X %02X %02X %02X %02X %02X %02X]\r\n",
               rawA, rawB, raw_clutch10, clutch_pct,
               msg->data[0], msg->data[1], msg->data[2], msg->data[3],
               msg->data[4], msg->data[5], msg->data[6], msg->data[7]);
    }

    // Forward to car on CAN2 (possibly modified)
    send_message(CAN_2,
                 msg->is_extended_id,
                 msg->arbitration_id,
                 msg->dlc,
                 tx_data);
}

/* ---------------------------------------------------------------------------
 * CAN receive handler
 * -------------------------------------------------------------------------*/

void onReceive(CAN_Message Message)
{
    // CAN1: steering wheel to car
    if (Message.Bus == CAN_1)
    {
        if (!Message.is_extended_id && Message.arbitration_id == ID_STEERING_CLUTCH)
        {
            handle_steering_0xBF_from_CAN1(&Message);
        }
        else
        {
            // Straight-through for all other IDs
            send_message(CAN_2,
                         Message.is_extended_id,
                         Message.arbitration_id,
                         Message.dlc,
                         Message.data);

            printf("[CAN1->CAN2] ID=0x%03lX DLC=%u\r\n",
                   (unsigned long)Message.arbitration_id,
                   (unsigned)Message.dlc);
        }
        return;
    }

    // CAN2: car to steering wheel (always pure mirror)
    if (Message.Bus == CAN_2)
    {
        send_message(CAN_1,
                     Message.is_extended_id,
                     Message.arbitration_id,
                     Message.dlc,
                     Message.data);

        printf("[CAN2->CAN1] ID=0x%03lX DLC=%u\r\n",
               (unsigned long)Message.arbitration_id,
               (unsigned)Message.dlc);
        return;
    }

    // CAN3: Blink keypad + DBWC throttle controller
    if (Message.Bus == CAN_3)
    {
        // Heartbeat from keypad
        if (!Message.is_extended_id &&
            Message.arbitration_id == ID_BLINK_HEARTBEAT)
        {
            g_blink_hb_miss_counter = 0;
            g_blink_hb_seen         = true;
            // printf("[KEYPAD] Heartbeat 0x715 received\r\n");
        }

        // Button I/O
        if (!Message.is_extended_id &&
            Message.arbitration_id == ID_BLINK_KEYPAD_IO &&
            Message.dlc >= 1)
        {
            uint8_t button = Message.data[0];

            printf("[KEYPAD] 0x195 data0=0x%02X raw=[%02X %02X %02X %02X %02X]\r\n",
                   button,
                   Message.data[0], Message.data[1], Message.data[2],
                   Message.data[3], Message.data[4]);

            if (button == BTN_CLUTCH_MODE)
            {
                gateway_set_mode(MODE_CLUTCH);
            }
            else if (button == BTN_THROTTLE_MODE)
            {
                gateway_set_mode(MODE_THROTTLE);
            }
            else
            {
                printf("[KEYPAD] Unknown button code 0x%02X on 0x195\r\n", button);
            }
        }

        return;
    }
}

/* ---------------------------------------------------------------------------
 * Periodic event hooks
 * -------------------------------------------------------------------------*/

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
    // 0xBF timeout: if we stop seeing the clutch message for 0.5s,
    // force 0% throttle and failsafe
    if (g_bf_seen_ever && !g_failsafe)
    {
        if (g_bf_timeout_counter < 0xFFFFu)
            g_bf_timeout_counter++;

        if (g_bf_timeout_counter == BF_TIMEOUT_TICKS_100HZ)
        {
            printf("[TIMEOUT] 0xBF clutch message timeout, commanding 0%% and entering failsafe\r\n");

            // 1) Command 0% throttle once
            uint8_t thr_msg[8] = {0};
            thr_msg[0] = 0;  // 0%
            send_message(CAN_3, false, ID_THROTTLE_DEMAND, 8, thr_msg);

            // 2) Enter failsafe
            enter_failsafe("0xBF timeout (no steering wheel clutch msg)");
        }
    }
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
    // 5 Hz = every 200ms. Periodically refresh keypad LEDs 
    send_keypad_illumination(g_mode);

    // Heartbeat timeout handling for Blink keypad
    if (g_blink_hb_seen && !g_failsafe)
    {
        if (g_blink_hb_miss_counter < 0xFFFFu)
            g_blink_hb_miss_counter++;

        if (g_blink_hb_miss_counter == BLINK_HB_TIMEOUT_TICKS_5HZ)
        {
            printf("[TIMEOUT] Blink keypad heartbeat timeout (0x715), entering failsafe\r\n");
            enter_failsafe("Blink keypad heartbeat timeout (0x715)");
        }
    }
}

/* Run 2Hz Functions here */
void events_2Hz()
{
}

/* Run 1Hz Functions here */
void events_1Hz()
{
    // Read current error counts for each CAN bus
    CAN_ErrorCounts err1 = getCANErrorCounts(CAN_1);
    CAN_ErrorCounts err2 = getCANErrorCounts(CAN_2);
    CAN_ErrorCounts err3 = getCANErrorCounts(CAN_3);

    // Show all counters once a second
    printf("[CAN ERR] CAN1: Tx=%u Rx=%u Reset=%u | "
           "CAN2: Tx=%u Rx=%u Reset=%u | "
           "CAN3: Tx=%u Rx=%u Reset=%u\r\n",
           err1.TxErrorCounter, err1.RxErrorCounter, err1.BusResetCounter,
           err2.TxErrorCounter, err2.RxErrorCounter, err2.BusResetCounter,
           err3.TxErrorCounter, err3.RxErrorCounter, err3.BusResetCounter);

    if (g_prev_err_valid && !g_failsafe)
    {
        bool reset1 = (err1.BusResetCounter > g_prev_err_can1.BusResetCounter);
        bool reset2 = (err2.BusResetCounter > g_prev_err_can2.BusResetCounter);
        bool reset3 = (err3.BusResetCounter > g_prev_err_can3.BusResetCounter);

        if (reset1 || reset2 || reset3)
        {
            printf("[CAN ERR] Detected CAN bus reset: "
                   "CAN1 ΔRst=%d CAN2 ΔRst=%d CAN3 ΔRst=%d – entering failsafe\r\n",
                   (int)(err1.BusResetCounter - g_prev_err_can1.BusResetCounter),
                   (int)(err2.BusResetCounter - g_prev_err_can2.BusResetCounter),
                   (int)(err3.BusResetCounter - g_prev_err_can3.BusResetCounter));

            enter_failsafe("CAN bus reset detected (possible bus-off)");
        }
    }

    // Store for next comparison
    g_prev_err_can1 = err1;
    g_prev_err_can2 = err2;
    g_prev_err_can3 = err3;
    g_prev_err_valid = true;
}
