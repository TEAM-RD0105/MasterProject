
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
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1
#define y_1_width 1
#define y_2_width 1
#define y_3_width 1
#define y_4_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
extern void TLE92466_Init_Device();
extern uint16_T TLE92466_Get_ICVID();
extern float TLE92466_Get_VIO_Voltage();
extern floatTLE92466_Get_VDD_Voltage();
extern float TLE92466_Get_Temperature_Celsius();
extern float TLE92466_Get_VBAT_Voltage_FB();
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void TLE92466_VFS_Outputs_wrapper(uint16_T *ICVID,
			real_T *VIO,
			real_T *VDD,
			real_T *Temp,
			real_T *VBAT)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
*ICVID = TLE92466_Get_ICVID();
*VIO = TLE92466_Get_VIO_Voltage();
*VDD = TLE92466_Get_VDD_Voltage();
*Temp = TLE92466_Get_Temperature_Celsius();
*VBAT = TLE92466_Get_VBAT_Voltage_FB();
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


