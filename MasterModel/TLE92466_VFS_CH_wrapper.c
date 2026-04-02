/*
 * FILE GUIDE:
 * This is the main handwritten runtime wrapper for the per-channel TLE92466
 * block, and it is one of the most important files in the project.
 *
 * At a high level, each execution of this wrapper does three things:
 * 1. Push the desired command state into the TLE92466.
 * 2. Update which channels are enabled.
 * 3. Read back feedback and diagnostics for Simulink outputs.
 *
 * This file is also where performance tuning usually happens, because changing
 * how often a register is written or read directly changes SPI load.
 * If you are debugging timing, this is the first file to inspect together with
 * tle92466_control.c and TLE92466_SPI.c.
 */
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#define SIMPLIFIED_RTWTYPES_COMPATIBILITY
#include "rtwtypes.h"
#undef SIMPLIFIED_RTWTYPES_COMPATIBILITY
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include "tle92466_control.h"
#include "tle92466_conversion.h"
#include "TLE92466_SPI.h"

/* Define CH0..CH5 macros, map logical index->HW index.
   If CH0==0, CH1==1, ... CH5==5, this array is identity and harmless. */
#ifndef CH0
  #define CH0 0
  #define CH1 1
  #define CH2 2
  #define CH3 3
  #define CH4 4
  #define CH5 5
#endif
static const uint8_T hwIdx[6] = { CH0, CH1, CH2, CH3, CH4, CH5 };

#define TLE92466_MODE_ICC            ((uint16_T)1U)
#define TLE92466_CH_CONFIG_VALUE     ((uint16_T)0x0100U)
#define TLE92466_DITHER_STEP_VALUE   ((uint16_T)0x0101U)
#define TLE92466_DITHER_CTRL_VALUE   ((uint16_T)0x0000U)
#define TLE92466_DITHER_CLKDIV_VALUE ((uint16_T)0x0A6EU)

static uint8_T s_cfg_slot = 0U;
static uint8_T s_feedback_slot = 0U;
static uint8_T s_diag_bank_slot = 0U;
static uint8_T s_feedback_kind = 0U;
static uint8_T s_force_full_refresh = 1U;
static uint8_T s_ch_ctrl_valid = 0U;
static uint16_T s_ch_ctrl_shadow = 0U;
static real_T s_current_cache[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
static real_T s_voltage_cache[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
static uint16_T s_fault_cache[6] = { 0U, 0U, 0U, 0U, 0U, 0U };

static void TLE92466_ResetWrapperState(void)
{
  uint8_T ch;

  s_cfg_slot = 0U;
  s_feedback_slot = 0U;
  s_diag_bank_slot = 0U;
  s_feedback_kind = 0U;
  s_force_full_refresh = 1U;
  s_ch_ctrl_valid = 0U;
  s_ch_ctrl_shadow = 0U;

  for (ch = 0U; ch < 6U; ch++) {
    s_current_cache[ch] = 0.0;
    s_voltage_cache[ch] = 0.0;
    s_fault_cache[ch] = 0U;
  }
}

static uint16_T TLE92466_BuildFaultWord(uint8_T hw_channel, uint16_T diag_err, uint16_T diag_warn)
{
  const uint8_T shift = (uint8_T)((hw_channel & 0x1U) * 5U);

  return (uint16_T)(((diag_err >> shift) & 0x001FU) |
                    ((((diag_warn >> shift) & 0x000FU) << 8)));
}
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 6
#define u_1_width 1
#define y_width 6
#define y_1_width 6
#define y_2_width 6

/*
 * Create external references here.
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */

/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void TLE92466_VFS_CH_Start_wrapper(const real_T *CH_Frequency_Hz, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
(void)CH_Frequency_Hz; (void)p_width0;

  TLE92466_ResetWrapperState();
  TLE92466_Init_Device();
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void TLE92466_VFS_CH_Outputs_wrapper(const real_T *CH_Limit_mA,
			const uint8_T *Clear_Faults,
			real_T *CH_Current,
			uint16_T *Faults,
			real_T *CH_Voltage,
			const real_T *CH_Frequency_Hz, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* Use min(6, p_width0) for safety. Channel 6 in UI == index 5 here. */
  int_T n = p_width0;
  uint16_T enable_mask = 0U;
  uint16_T diag_err = 0U;
  uint16_T diag_warn = 0U;
  uint8_T cfg_slot = 0U;
  uint8_T feedback_slot = 0U;
  uint8_T diag_bank = 0U;

  if (n > 6) n = 6;
  if (n <= 0) return;

  cfg_slot = (uint8_T)(s_cfg_slot % (uint8_T)n);
  feedback_slot = (uint8_T)(s_feedback_slot % (uint8_T)n);
  diag_bank = (uint8_T)(s_diag_bank_slot % 3U);

  /*
   * Pass 1:
   * - SETPOINT is kept live for every channel every cycle because it is the
   *   command value most likely to change quickly.
   * - MODE/PERIOD/CH_CONFIG/DITHER are refreshed for one channel per cycle in
   *   steady state, which spreads the cost evenly instead of creating big
   *   bursts every Nth cycle.
   * - After reset/fault clear we force one full refresh cycle so the device
   *   starts from a known-good configuration.
   */
  for (uint8_T ch = 0U; ch < (uint8_T)n; ch++) {
    const uint8_T hw = hwIdx[ch];
    const real_T set_mA = CH_Limit_mA[ch];     /* command in mA */
    const real_T frq    = CH_Frequency_Hz[ch]; /* Hz */
    const uint16_T setpoint_reg = TLE92466_mA_TO_SETPOINT(set_mA);
    const uint16_T period_reg = TLE92466_Convert_Frequency_to_PERIOD_Register(frq);
    const uint8_T refresh_cfg = (uint8_T)((s_force_full_refresh != 0U) || (ch == cfg_slot));

    TLE92466_Channels[hw].mode          = TLE92466_MODE_ICC;
    TLE92466_Channels[hw].setpoint_mA   = setpoint_reg;
    TLE92466_Channels[hw].period_Frq_HZ = period_reg;

    (void)TLE92466_Set_SETPOINT(hw, setpoint_reg);

    if (refresh_cfg != 0U) {
      (void)TLE92466_Set_MODE(hw, TLE92466_MODE_ICC);
      (void)TLE92466_Set_PERIOD(hw, period_reg);
      (void)TLE92466_Set_CH_CONFIG(hw, TLE92466_CH_CONFIG_VALUE);
      (void)TLE92466_Set_DITHER_STEP(hw, TLE92466_DITHER_STEP_VALUE);
      (void)TLE92466_Set_DITHER_CTRL(hw, TLE92466_DITHER_CTRL_VALUE);
      (void)TLE92466_Set_DITHER_CLK_DIV(hw, TLE92466_DITHER_CLKDIV_VALUE);
    }

    if (set_mA != 0.0) {
      enable_mask |= (uint16_T)(1U << hw);
    } else {
      s_current_cache[ch] = 0.0;
    }
  }

  /*
   * Pass 2:
   * Shadow CH_CTRL after the first read so we do not need to fetch it every
   * cycle. We still preserve all non-enable bits by seeding the shadow from the
   * device after init/fault-clear.
   */
  {
    if (s_ch_ctrl_valid == 0U) {
      s_ch_ctrl_shadow = TLE92466_Get_CH_CTRL();
      s_ch_ctrl_valid = 1U;
    }

    const uint16_T desired_ch_ctrl =
      (uint16_T)((s_ch_ctrl_shadow & (uint16_T)~0x003FU) | enable_mask | (uint16_T)(1U << 15));

    if (desired_ch_ctrl != s_ch_ctrl_shadow) {
      TLE92466_Set_CH_CTRL(desired_ch_ctrl);
      s_ch_ctrl_shadow = desired_ch_ctrl;
    }
  }

  /*
   * Pass 3a:
   * Read only one diagnostics bank per cycle. Each bank covers two hardware
   * channels, so all six channels get fault-cache refresh across three cycles.
   * This keeps cycle cost uniform and still updates faults often enough for
   * monitoring.
   */
  switch (diag_bank) {
    case 0U:
      diag_err = TLE92466_Get_DIAG_ERR_CHGR0();
      diag_warn = TLE92466_Get_DIAG_WARN_CHGR0();
      break;
    case 1U:
      diag_err = TLE92466_Get_DIAG_ERR_CHGR1();
      diag_warn = TLE92466_Get_DIAG_WARN_CHGR1();
      break;
    default:
      diag_err = TLE92466_Get_DIAG_ERR_CHGR2();
      diag_warn = TLE92466_Get_DIAG_WARN_CHGR2();
      break;
  }

  for (uint8_T ch = 0U; ch < (uint8_T)n; ch++) {
    const uint8_T hw = hwIdx[ch];

    if ((uint8_T)(hw >> 1) == diag_bank) {
      s_fault_cache[ch] = TLE92466_BuildFaultWord(hw, diag_err, diag_warn);
    }
  }

  /*
   * Pass 3b:
   * Read feedback for only one channel per cycle and publish cached values for
   * the others. This is the biggest SPI-load reduction in the wrapper and also
   * makes the cycle-to-cycle execution time much more even.
   */
  {
    const uint8_T hw = hwIdx[feedback_slot];
    const uint8_T on = (uint8_T)((enable_mask >> hw) & 0x1U);
    const uint32_T dc = TLE92466_Get_FB_DC(hw);

    if (s_feedback_kind == 0U) {
      const uint32_T raw_i = TLE92466_Get_FB_I_AVG(hw);
      s_current_cache[feedback_slot] =
        on ? (real_T)(TLE92466_Decode_FB_IAVG(raw_i, dc) * 1000.0f) : 0.0;
    } else {
      const uint32_T raw_v = TLE92466_Get_FB_VBAT(hw);
      s_voltage_cache[feedback_slot] = (real_T)TLE92466_Decode_FB_VBAT(raw_v, dc);
    }
  }

  for (uint8_T ch = 0U; ch < (uint8_T)n; ch++) {
    CH_Current[ch] = s_current_cache[ch];
    CH_Voltage[ch] = s_voltage_cache[ch];
    Faults[ch] = s_fault_cache[ch];
  }

  /* Zero any unused outputs if n<6 */
  for (uint8_T ch = (uint8_T)n; ch < 6U; ch++) {
    CH_Current[ch] = 0.0;
    CH_Voltage[ch] = 0.0;
    Faults[ch] = 0U;
    s_current_cache[ch] = 0.0;
    s_voltage_cache[ch] = 0.0;
    s_fault_cache[ch] = 0U;
  }

  if (s_force_full_refresh != 0U) {
    s_force_full_refresh = 0U;
    s_cfg_slot = 0U;
  } else {
    s_cfg_slot++;
    if (s_cfg_slot >= (uint8_T)n) {
      s_cfg_slot = 0U;
    }
  }

  s_feedback_kind ^= 1U;
  if (s_feedback_kind == 0U) {
    s_feedback_slot++;
    if (s_feedback_slot >= (uint8_T)n) {
      s_feedback_slot = 0U;
    }
  }

  s_diag_bank_slot++;
  if (s_diag_bank_slot >= 3U) {
    s_diag_bank_slot = 0U;
  }

  if(*Clear_Faults == 1)
  {
    TLE92466_ResetWrapperState();
    TLE92466_Init_Device();
  }
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void TLE92466_VFS_CH_Terminate_wrapper(const real_T *CH_Frequency_Hz, const int_T p_width0)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
(void)CH_Frequency_Hz; (void)p_width0;

    /*
 * Custom Terminate code goes here.
 */
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}
