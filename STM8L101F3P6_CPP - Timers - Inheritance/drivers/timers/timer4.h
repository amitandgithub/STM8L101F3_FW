#ifndef __TIMER4_H
#define __TIMER4_H

#include "system.h"





// #define TIM_DEBUG_GPIO GPIOA, PIN_3
#define TIM_DEBUG_GPIO GPIOB, PIN_4

#define TIMER4_CONFIG_1_MS 6, 0xf9 

#define TIMER4_CONFIG_250_US 4, 0xff

#define TIMER4_CONFIG_4_1_MS 8, 0xff   

#define TIMER4_CONFIG_255_MS 14, 0xff

#define TIMER4_CONFIG_X_MS 4, 0xf9

uint8_t timer4_HwInit(uint8_t Prescaler, uint8_t Autoreload);

uint32_t timer4_Ticks(void);

INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler, 25);


INLINE void timer4_Enable(void)
{
    TIM4->CR1 |= TIM4_CR1_CEN;
}

INLINE void timer4_Disable(void)
{
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
}

extern uint32_t timer4_System_Ticks;



void Timer4_Test(void);


















#endif //__TIMER4_H