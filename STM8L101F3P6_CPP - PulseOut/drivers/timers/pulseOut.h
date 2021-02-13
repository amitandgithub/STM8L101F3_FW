/******************
** CLASS: pulseOut
**
** DESCRIPTION:
**  Implements the pulseOut driver
**
** CREATED: 15 Jan 2021, by Amit Chaudhary
**
** FILE: pulseOut.h
**
******************/
#ifndef pulseOut_h
#define pulseOut_h

#include"system.h"
#include"gpt.h"
#include"stm8l10x_tim2.h"
#include"stm8l10x_tim3.h"
#include"interrupt.h"

#define GPT_PARAMS Timerx,Tick_125ns,(uint16_t)(16000000/Frequency/2 - 1),1

template<TIMx_t Timerx, Timer_Channel_t Channel,uint32_t Frequency = 10000>

class pulseOut : public gpt<GPT_PARAMS>
{
  typedef gpt<GPT_PARAMS> Gpt;
protected:
  
  static const uint16_t ARR_F = (16000000/Frequency/2)/100;
public:
  
  uint8_t HwInit(void)
  {
    Gpt::HwInit();
    
    GpioHwInit();
    
    TIM2->CCMR1 = (uint8_t)(0x60 | TIM_CCMR_OCxPE);
    
    TIM2->CCER1 |= TIM_CCER1_CC1E;
    
    Gpt::EnableAutoLoadPreload();
    
    Gpt::InterruptDisable(0xff);
    
    SetDutyCycle(50);
      
    TIM2->BKR |= TIM_BKR_MOE;
    
    return 0;
  }
  
  void GpioHwInit(void)
  {
    if(Timerx == TIMER2)
    {
      if(Channel == Timer_Channel_1)
      {
        DigitalOut<B0> PB0; 
        PB0.HwInit();
      }
      else if(Channel == Timer_Channel_2)
      {
        DigitalOut<B2> PB2; 
        PB2.HwInit();
      }
    }
    else if(Timerx == TIMER3)
    {
      if(Channel == Timer_Channel_1)
      {
        DigitalOut<B1> PB1; 
        PB1.HwInit();
      }
      else if(Channel == Timer_Channel_2)
      {
        DigitalOut<D0> PD0; 
        PD0.HwInit();
      }
    }
    
  }
  void Start(void)
  {
    //Gpt::InterruptEnable(TIM_IER_UIE | TIM_IER_CC1IE); 
    Gpt::Start();
  }
  
  void Stop(void)
  {
    Gpt::Stop();
  }  
  
  void IRQ_Handler(void)
  {
    
  }
  
  void SetDutyCycle(uint8_t dutycycle)
  {
    uint16_t arr = ARR_F*(dutycycle%99); 
    
    TIM2->CCR1H = (uint8_t)( (uint16_t)arr >> 8);
    TIM2->CCR1L = (uint8_t)((uint16_t)arr);      
  }      
  
  void SetFrequency(uint32_t Freq)
  {
    Gpt::SetAutoReloadRegister((16000000/Freq/2 - 1));
  }
  
};




#endif // pulseIn_h