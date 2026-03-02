#ifndef TLE92466_COMMLAYER_H
#define TLE92466_COMMLAYER_H

#include <stdint.h>

#define SCB_CH_TO_BE_USED SCB3
#define SCB_CLOCK         PCLK_SCB3_CLOCK
#define SCB_INTERRUPT_NO  scb_3_interrupt_IRQn   

uint32_t TLE92466_SetReg(uint16_t Address, uint32_t data);
uint32_t TLE92466_GetReg(uint16_t Address, uint32_t *data);

#endif