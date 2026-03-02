#ifndef TLE92466_CONVERSION_H
#define TLE92466_CONVERSION_H

#include <stdint.h>

uint16_t Convert_mA_to_SETPOINT(float current_mA);
uint16_t Convert_Hz_to_PERIOD(float freq_Hz);

float Convert_FB_VBAT_Reg_to_Eng(uint32_t raw);
float Convert_FB_I_AVG_Reg_to_Eng(uint32_t raw);
float Convert_FB_DC_Reg_to_Eng(uint32_t raw);


float TLE92466_Decode_FB_VBAT(uint32_t fb_vbat_raw, uint32_t fb_dc_raw);
float TLE92466_Decode_FB_IAVG(uint32_t fb_i_avg_raw, uint32_t fb_dc_raw);
float TLE92466_Get_VIO_Voltage(void);
float TLE92466_Get_VDD_Voltage(void);
float TLE92466_Get_Temperature_Celsius(void);
float TLE92466_Get_VBAT_Voltage_FB(void);


#endif
