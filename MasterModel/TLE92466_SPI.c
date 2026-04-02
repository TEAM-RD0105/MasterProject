
#ifndef _GCC_C_S32K3XX_
#define _GCC_C_S32K3XX_
#endif

#ifndef MATLAB_MEX_FILE
  #include "Spi.h"
  #include "Spi_Cfg.h"
  #include "Mcal.h"
  #include "Std_Types.h"
#endif

#include "TLE92466_SPI.h"

#include <stdint.h>
#include <stdio.h>



#define TLE92466_SPI_ACTION_WRITE (0x1)
#define TLE92466_SPI_ACTION_READ (0x0)


/*******************************************************************************
**                         CRC8_SAE_J1850 Function Definitions                **
*******************************************************************************/
uint32_t TLE92466ED_SPI_Transmit(uint32_t frame);



uint8_t crc8_sae_j1850(uint32_t frame) {
    uint8_t data[3];
    data[2] = (frame >> 16) & 0xFF;
    data[1] = (frame >> 8) & 0xFF;
    data[0] = frame & 0xFF;

    uint8_t crc = 0xFF;
    for (uint8_t i = 0; i < 3; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x1D : (crc << 1);
        }
    }
    crc ^= 0xFF;
    return crc;
}


uint32_t TLE92466_SetReg(uint16_t Address, uint32_t data){
    uint32_t snd_msg = (((Address<<17)|(TLE92466_SPI_ACTION_WRITE<<16))|data);
    uint8_t crc = crc8_sae_j1850(snd_msg);
    snd_msg = ((crc<<24)|snd_msg);
    uint32_t recv_msg = 0;
    return TLE92466ED_SPI_Transmit(snd_msg);
}

uint32_t TLE92466_GetReg(uint16_t Address, uint32_t *data){
    uint32_t snd_msg = ((TLE92466_SPI_ACTION_READ<<17)|Address);
    uint8_t crc = crc8_sae_j1850(snd_msg);
    snd_msg = ((crc<<24)|snd_msg);
    uint32_t recv_msg = 0; 
#ifndef MATLAB_MEX_FILE
    // *data = TLE92466ED_SPI_Transmit(snd_msg);  //1st send;
    *data = TLE92466ED_SPI_Transmit(snd_msg);  //recv_msg;
#endif      
      return recv_msg;
}

 
// SPI transmit
uint32_t TLE92466ED_SPI_Transmit(uint32_t frame) {
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];

    tx_buf[3] = (frame >> 24) & 0xFF;
    tx_buf[2] = (frame >> 16) & 0xFF;
    tx_buf[1] = (frame >> 8) & 0xFF;
    tx_buf[0] = frame & 0xFF;
#ifndef MATLAB_MEX_FILE
    Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_0, tx_buf);
    if (Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0) != E_OK) {
        return 0xFFFFFFFF;
    }
    Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_0, rx_buf);
#endif

    uint32_t response =
           ((uint32_t)rx_buf[3] << 24) |
           ((uint32_t)rx_buf[2] << 16) |
           ((uint32_t)rx_buf[1] << 8)  |
           ((uint32_t)rx_buf[0]);

       // Extract reply mode from bits [23:22]
       uint8_t reply_mode = (response >> 22) & 0x3;

       switch (reply_mode) {
           case 0b00: {
               // 16-bit data: bits [15:0]
               uint32_t data16 = response & 0xFFFF;
               return data16;  // zero-extended
           }
           case 0b01: {
               // 22-bit data: bits [21:0]
               uint32_t data22 = response & 0x003FFFFF;
               return data22;
           }
           case 0b10: {
               // Critical Fault Reply — return pattern or handle as needed
               return 0xBADF0010;
           }
           default: {
               // Reserved / Invalid reply mode
               return 0xDEAD0000 | (reply_mode << 16);
           }
       }
}

