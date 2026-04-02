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
    static int counter = 0;
    static uint16_T last_ICVID = 0;
    static real_T last_VIO = 0;
    static real_T last_VDD = 0;
    static real_T last_Temp = 0;
    static real_T last_VBAT = 0;

    // This logic assumes the S-function is called every 1ms.
    // A value is read every 10ms in a staggered way.
    switch(counter) {
        case 0:
            last_ICVID = TLE92466_Get_ICVID();
            break;
        case 10:
            last_VIO = TLE92466_Get_VIO_Voltage();
            break;
        case 20:
            last_VDD = TLE92466_Get_VDD_Voltage();
            break;
        case 30:
            last_Temp = TLE92466_Get_Temperature_Celsius();
            break;
        case 40:
            last_VBAT = TLE92466_Get_VBAT_Voltage_FB();
            break;
    }

    // Assign the last read values to the outputs
    *ICVID = last_ICVID;
    *VIO = last_VIO;
    *VDD = last_VDD;
    *Temp = last_Temp;
    *VBAT = last_VBAT;

    // Increment counter and wrap around at 50ms
    counter++;
    if (counter >= 50) {
        counter = 0;
    }
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
