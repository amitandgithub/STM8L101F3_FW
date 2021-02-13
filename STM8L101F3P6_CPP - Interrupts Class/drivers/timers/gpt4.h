/******************
** CLASS: DigitalIn
**
** DESCRIPTION:
**  Gpio input functionality
**
** CREATED: 29-12-2020, by Amit Chaudhary
**
** FILE: gpt4.h
**
******************/
#ifndef gpt4_h
#define gpt4_h

#include"system.h"

extern uint32_t TIM4Ticks;

template<typename T>
class gpt4
{
  T* Ticks;
public:
  
  uint8_t HwInit(uint8_t Prescaler, uint8_t Autoreload)
  {
    disableInterrupts();

    CLK->PCKENR |= (uint8_t)CLK_PCKENR_TIM4;
    TIM4->SR1 = 0;
    TIM4->ARR = Autoreload;
    TIM4->PSCR = Prescaler;
    TIM4->IER = TIM4_IER_UIE;
    TIM4->CR1 = TIM4_CR1_ARPE;
    TIM4->EGR |= TIM4_EGR_UG;

    enableInterrupts();
    
    return 0;
  }
  
  void Start(void)
  {
    TIM4->CR1 |= TIM4_CR1_CEN;
  }
  
  void Stop(void)
  {
    TIM4->IER = 0;
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
  }
  
  T GetTicks(void)
  {
    T ticks;
    disableInterrupts();
    ticks = *Ticks;
    enableInterrupts();
    return ticks;
  }
  
  uint8_t GetCounter(void){ return TIM4->CNTR;} 
  
};


#endif // gpt4_h