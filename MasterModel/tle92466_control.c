/*******************************************************************************
**                     TLE92466ED Multi-Channel Command & Feedback Layer      **
*******************************************************************************/
#include <stdint.h>
#include "TLE92466_SPI.h"
#include "tle92466_control.h"
#include "tle92466_conversion.h"



TLE92466_ChannelData_t TLE92466_Channels[TLE92466_CHANNEL_COUNT];
uint32_t glob_status;

/*******************************************************************************
 * Function: TLE92466_CHANNEL_SELECT
 * ----------------------------------
 * Returns the channel-specific register address offset for the given base offset.
 * This aligns with the TLE92466ED's channel address scheme (Table 66+).
 *
 * Parameters:
 *   ch     - Channel index (0-5)
 *   offset - Register offset (e.g., SETPOINT_ADDR, MODE_ADDR)
 *
 * Returns:
 *   uint8_t - Computed register address
 ******************************************************************************/
uint16_t TLE92466_CHANNEL_SELECT(uint8_t ch, uint16_t offset) {
    static const uint16_t base_addr[6] = {
        0x0040,  // CH0
        0x0050,  // CH1
        0x0060,  // CH2
        0x0070,  // CH3
        0x0020,  // CH4
        0x0030   // CH5
    };

    if (ch >= 6) return 0xFFFF;  // invalid
    return base_addr[ch] + offset;
}


void TLE92466_UpdateCommand(uint8_t ch) {
    if (ch >= TLE92466_CHANNEL_COUNT) return;
    TLE92466_ChannelData_t *channel = &TLE92466_Channels[ch];

    TLE92466_Set_MODE(ch, channel->mode);
    TLE92466_Set_SETPOINT(ch, channel->setpoint_mA);
    TLE92466_Set_PERIOD(ch, channel->period_Frq_HZ);
    TLE92466_Set_CH_CONFIG(ch, 0x0100); // OL_TH_FIXED = 2*7.8=(15 mA)

}

void TLE92466_Set_FeedbackFreeze(uint8_t ch, uint8_t enable) {
    if (ch >= TLE92466_CHANNEL_COUNT) return;

    uint16_t freeze_mask = (1U << ch);
    static uint16_t fb_frz_state = 0;

    if (enable)
        fb_frz_state |= freeze_mask;
    else
        fb_frz_state &= ~freeze_mask;

    TLE92466_SetReg(FB_FRZ_ADDR, fb_frz_state);  // FB_FRZ register
}

////////////////////////////////////////////////////
void TLE92466_Init_Device(void)
{
    // The default configuration value 0x4005 for the GLOBAL_CONFIG
	// register enables the clock watchdog, SPI CRC protection, OT
	// and selects 5V VIO operation

	// Enable CRC and clock watchdog; disable SPI watchdog for debugging
	TLE92466_Set_GLOBAL_CONFIG(0x4005);

	// Clear latched global diagnostic faults
	TLE92466_Set_GLOBAL_DIAG0(0x0000);
	TLE92466_Set_GLOBAL_DIAG1(0x0000);
	TLE92466_Set_GLOBAL_DIAG2(0x0000);

	// Clear channel-specific error diagnostics
	TLE92466_Set_DIAG_ERR_CHGR0(0x0000);
	TLE92466_Set_DIAG_ERR_CHGR1(0x0000);

	// Clear channel-specific warning diagnostics
	TLE92466_Set_DIAG_WARN_CHGR0(0x0000);
	TLE92466_Set_DIAG_WARN_CHGR1(0x0000);

	// FAULT_MASK0:
	// Enable fault indication for channels 0-5 (OLSG, OL, SG, OC, OTE)
	TLE92466_Set_FAULT_MASK0(0x003F);

	// FAULT_MASK1:
	// Enable warning indication for channels 0-5 (PWM_REG_WARN, I_REG_WARN, OTW, OLSG_WARN)
	TLE92466_Set_FAULT_MASK1(0x003F);

	// FAULT_MASK2:
	// Mask all other faults (SPI watchdog, data error) - not needed during debugging
	TLE92466_Set_FAULT_MASK2(0x0000);

	// Watchdog reload (not needed for debugging, but safe to set)
	TLE92466_Set_WD_RELOAD(0xA5A5);


	// since the CLK pin is grounded,
	// the TLE92466ED uses its internal oscillator,
	// and the system clock (f_SYS) is automatically set to approximately 28 MHz.
}

/*******************************************************************************
 * Function: TLE92466_Control_CH
 * -----------------------------
 * Enables or disables a specific output channel by setting its bit in CH_CTRL.
 *
 * Notes:
 *   - Bit 15 must always be set to 1 to activate control access (as per datasheet).
 *   - Uses bitwise operations to modify a single channel without affecting others.
 *
 * Parameters:
 *   ch     - Channel index (0-5)
 *   enable - 1 to enable, 0 to disable
 ******************************************************************************/
void TLE92466_Control_CH(uint8_t ch, uint8_t enable) {
    if (ch >= TLE92466_CHANNEL_COUNT) return;

    uint32_t reg_val = 0u;

    // Read current CH_CTRL state
    glob_status = TLE92466_GetReg(CH_CTRL_ADDR, &reg_val);

    // Bit 15 must always be set
    reg_val |= (1U << 15);

    if (enable) {
        reg_val |= (1U << ch);   // Set bit to enable this channel
    } else {
        reg_val &= ~(1U << ch);  // Clear bit to disable this channel
    }

    // Write updated CH_CTRL value back
    glob_status = TLE92466_SetReg(CH_CTRL_ADDR, reg_val);
}


TLE92466_ChannelDiagnostics TLE92466_ReportChannelDiagnostics__OLD(uint8_t channel) {
    TLE92466_ChannelDiagnostics diag;
    diag.channel_id = channel;

    // Error register (DIAG_ERR_CHGR0 covers channels 0-1)
    uint16_t err = TLE92466_Get_DIAG_ERR_CHGR0();
    uint8_t shift = channel * 5;

    diag.error_OLSG = (err >> (shift + 0)) & 0x01;
    diag.error_OL   = (err >> (shift + 1)) & 0x01;
    diag.error_OC   = (err >> (shift + 2)) & 0x01;
    diag.error_SG   = (err >> (shift + 3)) & 0x01;
    diag.error_OTE  = (err >> (shift + 4)) & 0x01;

    // Warning register (DIAG_WARN_CHGR0 covers channels 0-1)
    uint16_t warn = TLE92466_Get_DIAG_WARN_CHGR0();
    diag.warn_PWM_REG     = (warn >> (channel * 5 + 0)) & 0x01;
    diag.warn_I_REG       = (warn >> (channel * 5 + 1)) & 0x01;
    diag.warn_OTW         = (warn >> (channel * 5 + 2)) & 0x01;
    diag.warn_OLSG        = (warn >> (channel * 5 + 3)) & 0x01;

    return diag;
}

uint16_t TLE92466_ReportChannelDiagnostics__OLD_CH0(uint8_t channel) {
    uint16_t result = 0;

    // Error register (DIAG_ERR_CHGR0 covers channels 0-1)
    uint16_t err = TLE92466_Get_DIAG_ERR_CHGR0();
    uint8_t shift = channel * 5;

    // Bits 0-4: Error flags
    result |= ((err >> shift) & 0x1F); // OLSG, OL, OC, SG, OTE

    // Warning register (DIAG_WARN_CHGR0 covers channels 0-1)
    uint16_t warn = TLE92466_Get_DIAG_WARN_CHGR0();

    // Bits 8-11: Warning flags
    result |= (((warn >> shift) & 0x0F) << 8); // PWM_REG, I_REG, OTW, OLSG_WARN

    return result;
}


uint16_t TLE92466_ReportChannelDiagnostics(uint8_t channel) {
    uint16_t result = 0;
    uint16_t err = 0;
    uint16_t warn = 0;
    uint8_t shift = (channel % 2) * 5;

    // Select correct error and warning register group
    if (channel < 2) {
        err = TLE92466_Get_DIAG_ERR_CHGR0();
        warn = TLE92466_Get_DIAG_WARN_CHGR0();
    } else if (channel < 4) {
        err = TLE92466_Get_DIAG_ERR_CHGR1();
        warn = TLE92466_Get_DIAG_WARN_CHGR1();
    } else {
        err = TLE92466_Get_DIAG_ERR_CHGR2();
        warn = TLE92466_Get_DIAG_WARN_CHGR2();
    }

    // Bits 0-4: Error flags
    result |= ((err >> shift) & 0x1F); // OLSG, OL, OC, SG, OTE

    // Bits 8-11: Warning flags
    result |= (((warn >> shift) & 0x0F) << 8); // PWM_REG, I_REG, OTW, OLSG_WARN

    return result;
}



/*******************************************************************************
**                         Central Function Definitions                       **
*******************************************************************************/


void TLE92466_Set_CH_CTRL(uint16_t data){
    glob_status = TLE92466_SetReg(CH_CTRL_ADDR, data);
}

uint16_t TLE92466_Get_CH_CTRL(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(CH_CTRL_ADDR, &data);
    return data;
}

void TLE92466_Set_GLOBAL_CONFIG(uint16_t data){
    glob_status = TLE92466_SetReg(GLOBAL_CONFIG_ADDR, data);
}

uint16_t TLE92466_Get_GLOBAL_CONFIG(void)
{
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(GLOBAL_CONFIG_ADDR, &data);
    return data;
}

void TLE92466_Set_GLOBAL_DIAG0(uint16_t data){
    glob_status = TLE92466_SetReg(GLOBAL_DIAG0_ADDR, data);
}

uint16_t TLE92466_Get_GLOBAL_DIAG0(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(GLOBAL_DIAG0_ADDR, &data);
    return data;
}

void TLE92466_Set_GLOBAL_DIAG1(uint16_t data){
    glob_status = TLE92466_SetReg(GLOBAL_DIAG1_ADDR, data);
}

uint16_t TLE92466_Get_GLOBAL_DIAG1(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(GLOBAL_DIAG1_ADDR, &data);
    return data;
}

void TLE92466_Set_GLOBAL_DIAG2(uint16_t data){
    glob_status = TLE92466_SetReg(GLOBAL_DIAG2_ADDR, data);
}

uint16_t TLE92466_Get_GLOBAL_DIAG2(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(GLOBAL_DIAG2_ADDR, &data);
    return data;
}

void TLE92466_Set_VBAT_TH(uint16_t data){
    glob_status = TLE92466_SetReg(VBAT_TH_ADDR, data);
}

uint16_t TLE92466_Get_VBAT_TH(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(VBAT_TH_ADDR, &data);
    return data;
}

void TLE92466_Set_FB_FRZ(uint16_t data){
    glob_status = TLE92466_SetReg(FB_FRZ_ADDR, data);
}

uint16_t TLE92466_Get_FB_FRZ(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FB_FRZ_ADDR, &data);
    return data;
}

void TLE92466_Set_FB_UPD(uint16_t data){
    glob_status = TLE92466_SetReg(FB_UPD_ADDR, data);
}

uint16_t TLE92466_Get_FB_UPD(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FB_UPD_ADDR, &data);
    return data;
}

void TLE92466_Set_WD_RELOAD(uint16_t data){
    glob_status = TLE92466_SetReg(WD_RELOAD_ADDR, data);
}

uint16_t TLE92466_Get_WD_RELOAD(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(WD_RELOAD_ADDR, &data);
    return data;
}

void TLE92466_Set_DIAG_ERR_CHGR0(uint16_t data){
    glob_status = TLE92466_SetReg(DIAG_ERR_CHGR0_ADDR, data);
}

uint16_t TLE92466_Get_DIAG_ERR_CHGR0(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(DIAG_ERR_CHGR0_ADDR, &data);
    return data;
}

void TLE92466_Set_DIAG_ERR_CHGR1(uint16_t data){
    glob_status = TLE92466_SetReg(DIAG_ERR_CHGR1_ADDR, data);
}

void TLE92466_Set_DIAG_ERR_CHGR2(uint16_t data){
    glob_status = TLE92466_SetReg(DIAG_ERR_CHGR2_ADDR, data);
}

uint16_t TLE92466_Get_DIAG_ERR_CHGR1(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(DIAG_ERR_CHGR1_ADDR, &data);
    return data;
}

uint16_t TLE92466_Get_DIAG_ERR_CHGR2(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(DIAG_ERR_CHGR2_ADDR, &data);
    return data;
}

void TLE92466_Set_DIAG_WARN_CHGR0(uint16_t data){
    glob_status = TLE92466_SetReg(DIAG_WARN_CHGR0_ADDR, data);
}

uint16_t TLE92466_Get_DIAG_WARN_CHGR0(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(DIAG_WARN_CHGR0_ADDR, &data);
    return data;
}

void TLE92466_Set_DIAG_WARN_CHGR1(uint16_t data){
    glob_status = TLE92466_SetReg(DIAG_WARN_CHGR1_ADDR, data);
}

void TLE92466_Set_DIAG_WARN_CHGR2(uint16_t data){
    glob_status = TLE92466_SetReg(DIAG_WARN_CHGR2_ADDR, data);
}

uint16_t TLE92466_Get_DIAG_WARN_CHGR1(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(DIAG_WARN_CHGR1_ADDR, &data);
    return data;
}

uint16_t TLE92466_Get_DIAG_WARN_CHGR2(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(DIAG_WARN_CHGR2_ADDR, &data);
    return data;
}

void TLE92466_Set_FAULT_MASK0(uint16_t data){
    glob_status = TLE92466_SetReg(FAULT_MASK0_ADDR, data);
}

uint16_t TLE92466_Get_FAULT_MASK0(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FAULT_MASK0_ADDR, &data);
    return data;
}

void TLE92466_Set_FAULT_MASK1(uint16_t data){
    glob_status = TLE92466_SetReg(FAULT_MASK1_ADDR, data);
}

uint16_t TLE92466_Get_FAULT_MASK1(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FAULT_MASK1_ADDR, &data);
    return data;
}

void TLE92466_Set_FAULT_MASK2(uint16_t data){
    glob_status = TLE92466_SetReg(FAULT_MASK2_ADDR, data);
}

uint16_t TLE92466_Get_FAULT_MASK2(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FAULT_MASK2_ADDR, &data);
    return data;
}

void TLE92466_Set_CLK_DIV(uint16_t data){
    glob_status = TLE92466_SetReg(CLK_DIV_ADDR, data);
}

uint16_t TLE92466_Get_CLK_DIV(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(CLK_DIV_ADDR, &data);
    return data;
}

void TLE92466_Set_SFF_BIST(uint16_t data){
    glob_status = TLE92466_SetReg(SFF_BIST_ADDR, data);
}

uint16_t TLE92466_Get_SFF_BIST(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(SFF_BIST_ADDR, &data);
    return data;
}

uint16_t TLE92466_Get_ICVID(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(ICVID_ADDR, &data);
    return data;
}

uint16_t TLE92466_Get_PIN_STAT(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(PIN_STAT_ADDR, &data);
    return data;
}

uint32_t TLE92466_Get_FB_STAT(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FB_STAT_ADDR, &data);
    return data;
}

uint32_t TLE92466_Get_FB_VOLTAGE1(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FB_VOLTAGE1_ADDR, &data);
    return data;
}

uint32_t TLE92466_Get_FB_VOLTAGE2(void){
    uint32_t data = 0u;
    glob_status = TLE92466_GetReg(FB_VOLTAGE2_ADDR, &data);
    return data;
}


#define TLE92466_F_SYS_HZ 28000000.0f  // System clock frequency (28 MHz)

uint16_t TLE92466_Convert_Frequency_to_PERIOD_Register(float freq_Hz)
{
    if (freq_Hz <= 0.0f) return 0x0000;

    float t_pwm = 1.0f / freq_Hz;

    for (uint8_t exp = 0; exp <= 7; exp++)
    {
        float mant = (t_pwm * TLE92466_F_SYS_HZ) / (1 << exp);
        if (mant <= 255.0f)
        {
            uint16_t mant_u8 = (uint8_t)mant;
            uint16_t reg = (mant_u8 & 0xFFU);       // PERIOD_MANT [7:0]
            reg |= ((exp & 0x07U) << 8);            // PERIOD_EXP [10:8]
            // LOW_FREQ_RANGE_EN and PWM_CTRL_PARAM left at 0
            return reg;
        }
    }

    return 0x07FF; // Saturate if frequency is too low
}



/*******************************************************************************
**                         Channel Function Definitions                        **
*******************************************************************************/
void TLE92466_SetBit(uint16_t addr, uint8_t bit_pos) {
    uint32_t reg_val = 0;
    TLE92466_GetReg(addr, &reg_val);
    reg_val |= (1U << bit_pos);
    TLE92466_SetReg(addr, reg_val);
}

void TLE92466_ClearBit(uint16_t addr, uint8_t bit_pos) {
    uint32_t reg_val = 0;
    TLE92466_GetReg(addr, &reg_val);
    reg_val &= ~(1U << bit_pos);
    TLE92466_SetReg(addr, reg_val);
}



void TLE92466_Set_SETPOINT(uint8_t Channel, uint16_t data){
    //ADDRS is a Channel select address
    uint8_t SETPOINT_ADDRS = TLE92466_CHANNEL_SELECT(Channel, SETPOINT_ADDR);
    glob_status = TLE92466_SetReg(SETPOINT_ADDRS, data);
}

uint16_t TLE92466_Get_SETPOINT(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t SETPOINT_ADDRS = TLE92466_CHANNEL_SELECT(Channel, SETPOINT_ADDR);
    glob_status = TLE92466_GetReg(SETPOINT_ADDRS, &data);
    return data;
}

void TLE92466_Set_CTRL(uint8_t Channel, uint16_t data){
    uint16_t CTRL_ADDRS = TLE92466_CHANNEL_SELECT(Channel, CTRL_ADDR);
    glob_status = TLE92466_SetReg(CTRL_ADDRS, data);
}

uint16_t TLE92466_Get_CTRL(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t CTRL_ADDRS = TLE92466_CHANNEL_SELECT(Channel, SETPOINT_ADDR);
    glob_status = TLE92466_GetReg(CTRL_ADDRS, &data);
    return data;
}

void TLE92466_Set_PERIOD(uint8_t Channel, uint16_t data){
    uint16_t PERIOD_ADDRS = TLE92466_CHANNEL_SELECT(Channel, PERIOD_ADDR);
    glob_status = TLE92466_SetReg(PERIOD_ADDRS, data);
}

uint16_t TLE92466_Get_PERIOD(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t PERIOD_ADDRS = TLE92466_CHANNEL_SELECT(Channel, PERIOD_ADDR);
    glob_status = TLE92466_GetReg(PERIOD_ADDRS, &data);
    return data;
}

void TLE92466_Set_INTEGRATOR_LIMIT(uint8_t Channel, uint16_t data){
	uint16_t INTEGRATOR_LIMIT_ADDRS = TLE92466_CHANNEL_SELECT(Channel, INTEGRATOR_LIMIT_ADDR);
    glob_status = TLE92466_SetReg(INTEGRATOR_LIMIT_ADDRS, data);
}

uint16_t TLE92466_Get_INTEGRATOR_LIMIT(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t INTEGRATOR_LIMIT_ADDRS = TLE92466_CHANNEL_SELECT(Channel, INTEGRATOR_LIMIT_ADDR);
    glob_status = TLE92466_GetReg(INTEGRATOR_LIMIT_ADDRS, &data);
    return data;
}

void TLE92466_Set_DITHER_CLK_DIV(uint8_t Channel, uint16_t data){
	uint16_t DITHER_CLK_DIV_ADDRS = TLE92466_CHANNEL_SELECT(Channel, DITHER_CLK_DIV_ADDR);
    glob_status = TLE92466_SetReg(DITHER_CLK_DIV_ADDRS, data);
}

uint16_t TLE92466_Get_DITHER_CLK_DIV(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t DITHER_CLK_DIV_ADDRS = TLE92466_CHANNEL_SELECT(Channel, DITHER_CLK_DIV_ADDR);
    glob_status = TLE92466_GetReg(DITHER_CLK_DIV_ADDRS, &data);
    return data;
}

void TLE92466_Set_DITHER_STEP(uint8_t Channel, uint16_t data){
    uint16_t DITHER_STEP_ADDRS = TLE92466_CHANNEL_SELECT(Channel, DITHER_STEP_ADDR);
    glob_status = TLE92466_SetReg(DITHER_STEP_ADDRS, data);
}

uint16_t TLE92466_Get_DITHER_STEP(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t DITHER_STEP_ADDRS = TLE92466_CHANNEL_SELECT(Channel, DITHER_STEP_ADDR);
    glob_status = TLE92466_GetReg(DITHER_STEP_ADDRS, &data);
    return data;
}

void TLE92466_Set_DITHER_CTRL(uint8_t Channel, uint16_t data){
    uint16_t DITHER_CTRL_ADDRS = TLE92466_CHANNEL_SELECT(Channel, DITHER_CTRL_ADDR);
    glob_status = TLE92466_SetReg(DITHER_CTRL_ADDRS, data);
}

uint16_t TLE92466_Get_DITHER_CTRL(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t DITHER_CTRL_ADDRS = TLE92466_CHANNEL_SELECT(Channel, DITHER_CTRL_ADDR);
    glob_status = TLE92466_GetReg(DITHER_CTRL_ADDRS, &data);
    return data;
}

void TLE92466_Set_CH_CONFIG(uint8_t Channel, uint16_t data){
	uint16_t CH_CONFIG_ADDRS = TLE92466_CHANNEL_SELECT(Channel, CH_CONFIG_ADDR);
    glob_status = TLE92466_SetReg(CH_CONFIG_ADDRS, data);
}

uint16_t TLE92466_Get_CH_CONFIG(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t CH_CONFIG_ADDRS = TLE92466_CHANNEL_SELECT(Channel, CH_CONFIG_ADDR);
    glob_status = TLE92466_GetReg(CH_CONFIG_ADDRS, &data);
    return data;
}

void TLE92466_Set_MODE(uint8_t Channel, uint16_t data){
	uint16_t MODE_ADDRS = TLE92466_CHANNEL_SELECT(Channel, MODE_ADDR);
    glob_status = TLE92466_SetReg(MODE_ADDRS, data);
}

uint16_t TLE92466_Get_MODE(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t MODE_ADDRS = TLE92466_CHANNEL_SELECT(Channel, MODE_ADDR);
    glob_status = TLE92466_GetReg(MODE_ADDRS, &data);
    return data;
}

void TLE92466_Set_TON(uint8_t Channel, uint16_t data){
	uint16_t TON_ADDRS = TLE92466_CHANNEL_SELECT(Channel, TON_ADDR);
    glob_status = TLE92466_SetReg(TON_ADDRS, data);
}

uint16_t TLE92466_Get_TON(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t TON_ADDRS = TLE92466_CHANNEL_SELECT(Channel, TON_ADDR);
    glob_status = TLE92466_GetReg(TON_ADDRS, &data);
    return data;
}

void TLE92466_Set_CTRL_INT_THRESH(uint8_t Channel, uint16_t data){
	uint16_t CTRL_INT_THRESH_ADDRS = TLE92466_CHANNEL_SELECT(Channel, CTRL_INT_THRESH_ADDR);
    glob_status = TLE92466_SetReg(CTRL_INT_THRESH_ADDRS, data);
}

uint16_t TLE92466_Get_CTRL_INT_THRESH(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t CTRL_INT_THRESH_ADDRS = TLE92466_CHANNEL_SELECT(Channel, CTRL_INT_THRESH_ADDR);
    glob_status = TLE92466_GetReg(CTRL_INT_THRESH_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_DC(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_DC_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_DC_ADDR);
    glob_status = TLE92466_GetReg(FB_DC_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_VBAT(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_VBAT_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_VBAT_ADDR);
    glob_status = TLE92466_GetReg(FB_VBAT_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_I_AVG(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_I_AVG_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_I_AVG_ADDR);
    glob_status = TLE92466_GetReg(FB_I_AVG_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_IMIN_IMAX(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_IMIN_IMAX_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_IMIN_IMAX_ADDR);
    glob_status = TLE92466_GetReg(FB_IMIN_IMAX_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_I_AVG_s16(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_I_AVG_s16_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_I_AVG_s16_ADDR);
    glob_status = TLE92466_GetReg(FB_I_AVG_s16_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_INT_THRESH(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_INT_THRESH_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_INT_THRESH_ADDR);
    glob_status = TLE92466_GetReg(FB_INT_THRESH_ADDRS, &data);
    return data;
}

uint32_t TLE92466_Get_FB_PERIOD_MIN_MAX(uint8_t Channel){
    uint32_t data = 0u;
    uint16_t FB_PERIOD_MIN_MAX_ADDRS = TLE92466_CHANNEL_SELECT(Channel, FB_PERIOD_MIN_MAX_ADDR);
    glob_status = TLE92466_GetReg(FB_PERIOD_MIN_MAX_ADDRS, &data);
    return data;
}
