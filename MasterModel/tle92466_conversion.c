#include "tle92466_conversion.h"
#include "tle92466_control.h"
#include <stdint.h>

/*------------------- Full Scale Definitions Based on Datasheet -------------*/
#define VBAT_FULL_SCALE_V         40.0f
#define VBAT_RESOLUTION           65536.0f  // 16-bit register

#define IAVG_FULL_SCALE_mA        3000.0f
#define IAVG_RESOLUTION           65536.0f

#define DC_FULL_SCALE_PCT         100.0f
#define DC_RESOLUTION             65536.0f

#define SETPOINT_MAX_mA           2000.0f    // Datasheet says 2A full scale in ICC mode
#define SETPOINT_RESOLUTION       32767.0f   // 15-bit resolution (bits [14:0]), per datasheet

#define FB_VOLTAGE_SCALE         0.0034534f

#define VBAT_SCALE_V             41.47f
#define VBAT_RESOLUTION_BITS     2047.0f   // 2^11 - 1


/*------------------- Setpoint Conversion Function --------------------------*/
uint16_t Convert_mA_to_SETPOINT(float current_mA)
{
    if (current_mA < 0.0f) current_mA = 0.0f;
    if (current_mA > SETPOINT_MAX_mA) current_mA = SETPOINT_MAX_mA;

    // Target = (I_set / 2A) * (2^15 - 1)
    return (uint16_t)((current_mA / SETPOINT_MAX_mA) * SETPOINT_RESOLUTION);
}

/*------------------- PWM Frequency Register Packing ------------------------*/
/*
 * Datasheet: t_pwm = MANT × 2^EXP × (1 / f_sys)
 *            freq_Hz = 1 / t_pwm = f_sys / (MANT × 2^EXP)
 * Assumes f_sys = 8 MHz (update if different)
 */
uint16_t Convert_Hz_to_PERIOD(float freq_Hz)
{
    const float f_sys = 8000000.0f;
    if (freq_Hz <= 0.0f) return 0x0000;

    float t_pwm = 1.0f / freq_Hz;

    for (uint8_t exp = 0; exp <= 7; exp++)
    {
        float mant = (t_pwm * f_sys) / (1 << exp);
        if (mant <= 255.0f)
        {
            uint16_t reg = ((uint8_t)mant & 0xFFU);       // PERIOD_MANT [7:0]
            reg |= ((exp & 0x07U) << 8);                  // PERIOD_EXP [10:8]
            reg |= (0U << 11);                            // LOW_FREQ_RANGE_EN = 0
            reg |= (0U << 12);                            // PWM_CTRL_PARAM = 0 (default)
            return reg;
        }
    }

    return 0x07FF; // Maxed out value (saturate)
}

/*------------------- Feedback Conversions from Raw ADC Values --------------*/
float Convert_FB_VBAT_Reg_to_Eng(uint32_t raw)
{
    return (raw / VBAT_RESOLUTION) * VBAT_FULL_SCALE_V;
}

float Convert_FB_I_AVG_Reg_to_Eng(uint32_t raw) {
    int16_t mant = (int16_t)(raw & 0x0FFF); // 12-bit two's complement mantissa
    if (mant & 0x0800) mant |= 0xF000; // Sign-extend

    uint8_t exp = (raw >> 12) & 0x0F;
    float tp_mant = 1 << exp; // TP_MANT extracted from FB_DC if needed

    return (4.0f * mant) / tp_mant;
}
float Convert_FB_DC_Reg_to_Eng(uint32_t raw)
{
    return (raw / DC_RESOLUTION) * DC_FULL_SCALE_PCT;
}

float TLE92466_Decode_FB_VBAT(uint32_t fb_vbat_raw, uint32_t fb_dc_raw) {
    uint16_t vbat_mant = fb_vbat_raw & 0x7FF;         // bits [10:0]
    uint16_t tp_mant   = fb_dc_raw & 0x7FF;           // bits [10:0]

    if (tp_mant == 0) return 0.0f;  // avoid division by zero

    return 41.47f * ((float)vbat_mant / (float)tp_mant);
}

float TLE92466_Decode_FB_IAVG__OLD(uint32_t fb_i_avg_raw, uint32_t fb_dc_raw) {
    uint16_t iavg_mant = fb_i_avg_raw & 0x0FFF;       // bits [11:0]
    uint16_t tp_mant   = fb_dc_raw & 0x07FF;          // bits [10:0]
    if (tp_mant == 0) return 0.0f;
    return 4.0f * ((float)iavg_mant / (float)tp_mant);
}

float TLE92466_Decode_FB_IAVG(uint32_t fb_i_avg_raw, uint32_t fb_dc_raw) {
    uint16_t iavg_mant = fb_i_avg_raw & 0x0FFF;  // bits [11:0]
    uint16_t tp_mant   = fb_dc_raw & 0x07FF;     // bits [10:0]

    // If TP_MANT is zero or channel is OFF, return 0 current
    if (tp_mant == 0 || iavg_mant == 0) return 0.0f;

    // Calculate average current
    float i_avg = 4.0f * ((float)iavg_mant / (float)tp_mant);

    // Optional: clip small values to zero (e.g., < 5 mA)
    if ((i_avg < 0.002f) || (i_avg > 4.0f)) return 0.0f;

    return i_avg;
}




float TLE92466_Get_VIO_Voltage(void) {
    uint32_t raw = TLE92466_Get_FB_VOLTAGE1();
    uint16_t vio_bits = (raw >> 0) & 0x07FF;   // Extract bits [10:0]
    return vio_bits * FB_VOLTAGE_SCALE;
}

float TLE92466_Get_VDD_Voltage(void) {
    uint32_t raw = TLE92466_Get_FB_VOLTAGE1();
    uint16_t vdd_bits = (raw >> 11) & 0x07FF;  // Extract bits [21:11]
    return vdd_bits * FB_VOLTAGE_SCALE;
}


float TLE92466_Get_Temperature_Celsius(void) {
    uint32_t raw = TLE92466_Get_FB_VOLTAGE2();
    uint16_t temp_raw = (raw >> 0) & 0x07FF; // bits 10:0
    float voltage = temp_raw * 0.000593f;
    return (voltage - 0.819f) / -0.0016f;
}

float TLE92466_Get_VBAT_Voltage_FB(void) {
    uint32_t raw = TLE92466_Get_FB_VOLTAGE2();
    uint16_t vbat_raw = (raw >> 11) & 0x07FF; // bits 21:11
    return (vbat_raw * VBAT_SCALE_V) / VBAT_RESOLUTION_BITS;
}

