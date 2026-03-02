/*******************************************************************************
**                      TLE92466ED Multi-Channel Control Layer                **
**                            Header File - tle92466_control.h               **
*******************************************************************************/

#ifndef TLE92466_CONTROL_H
#define TLE92466_CONTROL_H

#include <stdint.h>   // <<< This is the critical missing header

#define TLE92466_CHANNEL_COUNT     	(6)

#define CH0							(0)
#define CH1							(1)
#define CH2							(2)
#define CH3							(3)
#define CH4							(4)
#define CH5							(5)


#define ENABLE						(1)
#define DISABLE						(0)


#define TLE92466_mA_TO_SETPOINT(mA) \
    ((uint16_t)(((mA) < 0.0f ? 0.0f : ((mA) > 2000.0f ? 2000.0f : (mA)) / 2000.0f * 32767.0f)))

uint16_t TLE92466_Get_ICVID(void);
void TLE92466_UpdateCommand(uint8_t ch);

void TLE92466_Init_Device(void);
void TLE92466_Set_MODE(uint8_t Channel, uint16_t data);
void TLE92466_Set_SETPOINT(uint8_t Channel, uint16_t data);
void TLE92466_Set_PERIOD(uint8_t Channel, uint16_t data);
void TLE92466_Set_CH_CTRL(uint16_t data);
void TLE92466_Control_CH(uint8_t ch, uint8_t enable);


typedef struct {
    float vdd_volts;         // 4.5 – 5.5 V
    float vio_volts;         // 3.0 – 5.5 V
    float vbat_volts;        // 6 – 18 V (typ), up to 38 V (ext)
    float temperature_C;     // -40 to 175 °C
    uint8_t fault_flags;     // Summary of GLOBAL_DIAGx bits
    uint8_t init_done;       // INIT_DONE bit
    uint8_t spi_watchdog_err;
    uint8_t clock_fault;
} TLE92466_GlobalConfig;

typedef struct {
    // Configuration
    uint16_t setpoint_mA;        // 0–1500 mA
    uint16_t mode;               // 0–1,2
    uint16_t period_Frq_HZ;      // 250–9090 µs
    uint16_t ton_us;             // 0.07 µs – 300 ms
    uint16_t integrator_thresh;  // -128 to +127
    uint16_t dither_amplitude_mA;// 0–1800 mA
    uint8_t  enabled;            // 0 or 1

    // Feedback
    float current_mA;            // 0–2000 mA (single), up to 2700 mA (parallel)
    float duty_cycle_pct;        // 0–100%
    float vbat_volts;            // 6–18 V

    // Diagnostics
    uint8_t fault_ol;            // Open Load
    uint8_t fault_sg;            // Short to Ground
    uint8_t fault_oc;            // Overcurrent
    uint8_t fault_ot;            // Overtemperature
    uint8_t warn_pwm_reg;        // PWM regulation warning
    uint8_t warn_i_reg;          // Current regulation warning
} TLE92466_ChannelData_t;

extern TLE92466_ChannelData_t TLE92466_Channels[TLE92466_CHANNEL_COUNT];


typedef struct {
    uint8_t channel_id;

    // Error flags
    uint8_t error_OLSG;  // ON-state: Load current below threshold; cannot distinguish OL vs SG
    uint8_t error_OL;    // OFF-state: Voltage check confirms open load
    uint8_t error_SG;    // OFF-state: Voltage check confirms short to ground
    uint8_t error_OC;    // Current exceeds overcurrent threshold; channel disabled
    uint8_t error_OTE;   // Overtemperature error; channel disabled

    // Warning flags
    uint8_t warn_PWM_REG;      // ICC PWM regulation warning due to integrator undershoot
    uint8_t warn_I_REG;        // ICC current regulation warning due to integrator saturation
    uint8_t warn_OTW;          // Overtemperature warning; pre-fault indication
    uint8_t warn_OLSG;         // Voltage at LOADx < VBAT/2 after freewheeling phase
} TLE92466_ChannelDiagnostics;












/*******************************************************************************
**                          Central Macro Declarations                         **
*******************************************************************************/
#define CH_CTRL_ADDR           (0x00)

#define GLOBAL_CONFIG_ADDR     (0x02)

#define GLOBAL_DIAG0_ADDR      (0x03)
#define GLOBAL_DIAG1_ADDR      (0x04)
#define GLOBAL_DIAG2_ADDR      (0x05)

#define VBAT_TH_ADDR           (0x06)
#define FB_FRZ_ADDR            (0x07)
#define FB_UPD_ADDR            (0x08)

#define WD_RELOAD_ADDR         (0x09)

#define DIAG_ERR_CHGR0_ADDR    (0x0A)
#define DIAG_ERR_CHGR1_ADDR    (0x0B)
#define DIAG_ERR_CHGR2_ADDR    (0x0B)

#define DIAG_WARN_CHGR0_ADDR   (0x10)
#define DIAG_WARN_CHGR1_ADDR   (0x11)
#define DIAG_WARN_CHGR2_ADDR   (0x12)

#define FAULT_MASK0_ADDR       (0x16)
#define FAULT_MASK1_ADDR       (0x17)
#define FAULT_MASK2_ADDR       (0x18)

#define CLK_DIV_ADDR           (0x19)
#define SFF_BIST_ADDR          (0x3F)

#define ICVID_ADDR             (0x0200)

#define PIN_STAT_ADDR          (0x0201)
#define FB_STAT_ADDR           (0x0202)

#define FB_VOLTAGE1_ADDR       (0x0203)
#define FB_VOLTAGE2_ADDR       (0x0204)

/*******************************************************************************
**                          Individual Channel                                **
*******************************************************************************/
#define SETPOINT_ADDR          (0x0)
#define CTRL_ADDR              (0x1)
#define PERIOD_ADDR            (0x2)
#define INTEGRATOR_LIMIT_ADDR  (0x3)
#define DITHER_CLK_DIV_ADDR    (0x4)
#define DITHER_STEP_ADDR       (0x5)
#define DITHER_CTRL_ADDR       (0x6)
#define CH_CONFIG_ADDR         (0x7)
#define MODE_ADDR              (0xC)
#define TON_ADDR               (0xD)
#define CTRL_INT_THRESH_ADDR   (0xE)
#define FB_DC_ADDR             (0x200)
#define FB_VBAT_ADDR           (0x201)
#define FB_I_AVG_ADDR          (0x202)
#define FB_IMIN_IMAX_ADDR      (0x203)
#define FB_I_AVG_s16_ADDR      (0x204)
#define FB_INT_THRESH_ADDR     (0x205)
#define FB_PERIOD_MIN_MAX_ADDR (0x206)


/*******************************************************************************
**                        Central Function Declarations                        **
*******************************************************************************/
void TLE92466_Init(void);

uint16_t TLE92466_ReportChannelDiagnostics(uint8_t channel);

void TLE92466_Set_CH_CTRL(uint16_t data);
uint16_t TLE92466_Get_CH_CTRL(void);
void TLE92466_Set_GLOBAL_CONFIG(uint16_t data);
uint16_t TLE92466_Get_GLOBAL_CONFIG(void);
void TLE92466_Set_GLOBAL_DIAG0(uint16_t data);
uint16_t TLE92466_Get_GLOBAL_DIAG0(void);
void TLE92466_Set_GLOBAL_DIAG1(uint16_t data);
uint16_t TLE92466_Get_GLOBAL_DIAG1(void);
void TLE92466_Set_GLOBAL_DIAG2(uint16_t data);
uint16_t TLE92466_Get_GLOBAL_DIAG2(void);
void TLE92466_Set_VBAT_TH(uint16_t data);
uint16_t TLE92466_Get_VBAT_TH(void);
void TLE92466_Set_FB_FRZ(uint16_t data);
uint16_t TLE92466_Get_FB_FRZ(void);
void TLE92466_Set_FB_UPD(uint16_t data);
uint16_t TLE92466_Get_FB_UPD(void);
void TLE92466_Set_WD_RELOAD(uint16_t data);
uint16_t TLE92466_Get_WD_RELOAD(void);
void TLE92466_Set_DIAG_ERR_CHGR0(uint16_t data);
uint16_t TLE92466_Get_DIAG_ERR_CHGR0(void);
void TLE92466_Set_DIAG_ERR_CHGR1(uint16_t data);
void TLE92466_Set_DIAG_ERR_CHGR2(uint16_t data);
uint16_t TLE92466_Get_DIAG_ERR_CHGR1(void);
uint16_t TLE92466_Get_DIAG_ERR_CHGR2(void);
void TLE92466_Set_DIAG_WARN_CHGR0(uint16_t data);
uint16_t TLE92466_Get_DIAG_WARN_CHGR0(void);
void TLE92466_Set_DIAG_WARN_CHGR1(uint16_t data);
uint16_t TLE92466_Get_DIAG_WARN_CHGR1(void);
void TLE92466_Set_DIAG_WARN_CHGR2(uint16_t data);
uint16_t TLE92466_Get_DIAG_WARN_CHGR2(void);
void TLE92466_Set_FAULT_MASK0(uint16_t data);
uint16_t TLE92466_Get_FAULT_MASK0(void);
void TLE92466_Set_FAULT_MASK1(uint16_t data);
uint16_t TLE92466_Get_FAULT_MASK1(void);
void TLE92466_Set_FAULT_MASK2(uint16_t data);
uint16_t TLE92466_Get_FAULT_MASK2(void);
void TLE92466_Set_CLK_DIV(uint16_t data);
uint16_t TLE92466_Get_CLK_DIV(void);
void TLE92466_Set_SFF_BIST(uint16_t data);
uint16_t TLE92466_Get_SFF_BIST(void);
uint16_t TLE92466_Get_ICVID(void);
uint16_t TLE92466_Get_PIN_STAT(void);
uint32_t TLE92466_Get_FB_STAT(void);
uint32_t TLE92466_Get_FB_VOLTAGE1(void);
uint32_t TLE92466_Get_FB_VOLTAGE2(void);
uint16_t TLE92466_Convert_Frequency_to_PERIOD_Register(float freq_Hz);

/*******************************************************************************
**                        Channel Function Declarations                        **
*******************************************************************************/
uint16_t TLE92466_CHANNEL_SELECT(uint8_t Channel, uint16_t ADDRS);

void TLE92466_SetBit(uint16_t addr, uint8_t bit);
void TLE92466_ClearBit(uint16_t addr, uint8_t bit);

void TLE92466_Set_SETPOINT(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_SETPOINT(uint8_t Channel);
void TLE92466_Set_CTRL(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_CTRL(uint8_t Channel);
void TLE92466_Set_PERIOD(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_PERIOD(uint8_t Channel);
void TLE92466_Set_INTEGRATOR_LIMIT(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_INTEGRATOR_LIMIT(uint8_t Channel);
void TLE92466_Set_DITHER_CLK_DIV(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_DITHER_CLK_DIV(uint8_t Channel);
void TLE92466_Set_DITHER_STEP(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_DITHER_STEP(uint8_t Channel);
void TLE92466_Set_DITHER_CTRL(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_DITHER_CTRL(uint8_t Channel);
void TLE92466_Set_CH_CONFIG(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_CH_CONFIG(uint8_t Channel);
void TLE92466_Set_MODE(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_MODE(uint8_t Channel);
void TLE92466_Set_TON(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_TON(uint8_t Channel);
void TLE92466_Set_CTRL_INT_THRESH(uint8_t Channel, uint16_t data);
uint16_t TLE92466_Get_CTRL_INT_THRESH(uint8_t Channel);
uint32_t TLE92466_Get_FB_DC(uint8_t Channel);
uint32_t TLE92466_Get_FB_VBAT(uint8_t Channel);
uint32_t TLE92466_Get_FB_I_AVG(uint8_t Channel);
uint32_t TLE92466_Get_FB_IMIN_IMAX(uint8_t Channel);
uint32_t TLE92466_Get_FB_I_AVG_s16(uint8_t Channel);
uint32_t TLE92466_Get_FB_INT_THRESH(uint8_t Channel);
uint32_t TLE92466_Get_FB_PERIOD_MIN_MAX(uint8_t Channel);


#endif /* TLE92466_CONTROL_H */
