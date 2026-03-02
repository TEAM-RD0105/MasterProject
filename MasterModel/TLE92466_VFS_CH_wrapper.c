
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

/* once-per-bank guard (pairs 0/1, 2/3, 4/5) — not strictly needed now */
#define BANK_OF(ch) ((uint8_T)((ch) >> 1))
static uint8_T s_bank_inited[3] = {0,0,0};
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
  for (uint8_T i=0; i<3; i++) s_bank_inited[i] = 0U;

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
/* Use min(6, p_width0) for safety. Channel “6” in UI == index 5 here. */
  int_T n = p_width0;
  if (n > 6) n = 6;
  if (n <= 0) return;

  /* Pass 1: program setpoint & period, then UpdateCommand */
  for (uint8_T ch = 0U; ch < (uint8_T)n; ch++) {
    const uint8_T hw = hwIdx[ch];
    const real_T set_mA = CH_Limit_mA[ch];     /* command in mA */
    const real_T frq    = CH_Frequency_Hz[ch]; /* Hz */

    TLE92466_Channels[hw].mode          = 1U; /* ICC */
    TLE92466_Channels[hw].setpoint_mA   = TLE92466_mA_TO_SETPOINT(set_mA);
    TLE92466_Channels[hw].period_Frq_HZ = TLE92466_Convert_Frequency_to_PERIOD_Register(frq);

    TLE92466_UpdateCommand(hw);

    (void)TLE92466_Set_DITHER_STEP(hw,    0x0101);
    (void)TLE92466_Set_DITHER_CTRL(hw,    0x0000);
    (void)TLE92466_Set_DITHER_CLK_DIV(hw, 0x0A6E);
  }

  /* Pass 2: ON/OFF from exact zero */
  for (uint8_T ch = 0U; ch < (uint8_T)n; ch++) {
    const uint8_T hw = hwIdx[ch];
    const real_T set_mA = CH_Limit_mA[ch];
    const uint8_T on    = (set_mA == 0.0) ? 0U : 1U;
    TLE92466_Control_CH(hw, on);
  }

  /* Pass 3: feedback */
  for (uint8_T ch = 0U; ch < (uint8_T)n; ch++) {
    const uint8_T hw = hwIdx[ch];
    const real_T set_mA = CH_Limit_mA[ch];
    const uint8_T on    = (set_mA == 0.0) ? 0U : 1U;

    uint32_T raw = TLE92466_Get_FB_I_AVG(hw);
    uint32_T dc  = TLE92466_Get_FB_DC(hw);
    double   i   = TLE92466_Decode_FB_IAVG(raw, dc);

    uint32_T rawV = TLE92466_Get_FB_VBAT(hw);
    uint32_T dcV  = TLE92466_Get_FB_DC(hw);
    double   v   = TLE92466_Decode_FB_VBAT(rawV, dcV);
    CH_Voltage[ch] = v;

    CH_Current[ch] = on ? (real_T)i*1000 : 0.0;
    uint16_T d = TLE92466_ReportChannelDiagnostics(ch);
    Faults[ch] = d;
  }
   
  /* Zero any unused outputs if n<6 */
  for (uint8_T ch = (uint8_T)n; ch < 6U; ch++) {
    CH_Current[ch] = 0.0;
  }

  if(*Clear_Faults == 1)
  {
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

