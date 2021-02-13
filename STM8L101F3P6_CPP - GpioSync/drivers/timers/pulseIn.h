/******************
** CLASS: pulseIn
**
** DESCRIPTION:
**  Gpio input functionality
**
** CREATED: 29-12-2020, by Amit Chaudhary
**
** FILE: pulseIn.h
**
******************/
#ifndef pulseIn_h
#define pulseIn_h

#include"system.h"
#include"gpt.h"
#include"stm8l10x_tim2.h"
#include"stm8l10x_tim3.h"

typedef union
{
  uint16_t Capture;
  uint8_t Array[2];
}Capture_t;

template<TIMx_t Timerx, TIM3_Channel_TypeDef Channel, uint16_t Prescaler = 1, uint16_t Autoreload = 0xffff, uint8_t ChannelPrescaler = 0, uint8_t Polarity = 0, uint8_t Filter = 0>
class pulseIn
{
  gpt<Timerx> timer;
public:
  
  uint8_t HwInit(void) //uint16_t Prescaler, uint16_t Autoreload
  {
    uint8_t IC1Selection, IC2Selection;
    
    //static_assert( (Timerx != 0), "Error: Both edges should not be same");
    
    if(Channel == TIM3_Channel_1)
    {
      IC1Selection = TIM3_ICSelection_DirectTI;
      IC2Selection = TIM3_ICSelection_IndirectTI;  
    }
    else
    {
      IC1Selection = TIM3_ICSelection_IndirectTI;
      IC2Selection = TIM3_ICSelection_DirectTI;     
    }
    
    timer.HwInit(Prescaler,Autoreload,1);
      
    ((TIM_TypeDef*)Timerx)->CCER1 = 0;
    ((TIM_TypeDef*)Timerx)->CCMR1 = 0;
    ((TIM_TypeDef*)Timerx)->CCMR2 = 0;
    
    ((TIM_TypeDef*)Timerx)->CCMR1 |= (uint8_t)ChannelPrescaler | (uint8_t)(((uint8_t)(IC1Selection)) | ((uint8_t)(Filter << 4)));
    ((TIM_TypeDef*)Timerx)->CCMR2 |= (uint8_t)ChannelPrescaler | (uint8_t)(((uint8_t)(IC2Selection)) | ((uint8_t)(Filter << 4)));    
    
    if (Polarity == 1)
    {
      ((TIM_TypeDef*)Timerx)->CCER1 |= TIM_CCER1_CC1P | TIM_CCER1_CC1E | TIM_CCER1_CC2E;
    }
    else
    {
      ((TIM_TypeDef*)Timerx)->CCER1 |= TIM_CCER1_CC2P | TIM_CCER1_CC1E | TIM_CCER1_CC2E ;
    }  
    
    timer.InterruptDisable(0xff);
    
    timer.InterruptEnable(TIM_IER_CC2IE);
      
    return 0;
  }
  
  void Start(void)
  {
    timer.Start();
  }
  
  void Stop(void)
  {
    timer.Stop();
  }  
  
  uint16_t GetCapture1(void)
  {
    uint16_t tmpccr1 = 0;
    uint8_t tmpccr1l, tmpccr1h;
    Capture_t Capture;
    
    tmpccr1h = ((TIM_TypeDef*)Timerx)->CCR1H;
    tmpccr1l = ((TIM_TypeDef*)Timerx)->CCR1L;

    tmpccr1 = (uint16_t)(tmpccr1l);
    tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);

    return ((uint16_t)tmpccr1);
  }
  
  uint16_t GetCapture2(void)
  {
    uint16_t tmpccr1 = 0;
    uint8_t tmpccr1l, tmpccr1h;
    
    tmpccr1h = ((TIM_TypeDef*)Timerx)->CCR2H;
    tmpccr1l = ((TIM_TypeDef*)Timerx)->CCR2L;
    
    tmpccr1 = (uint16_t)(tmpccr1l);
    tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);

    return ((uint16_t)tmpccr1);
  }
  
  uint16_t GetDiff(void)
  {
    uint16_t Cap1,Cap2;
    
    Cap1 = GetCapture1();
    Cap2 = GetCapture2();
    
    if(Cap1 >= Cap2)
    {
      return Cap1 - Cap2;
    }
    else
    {
      return Cap2 - Cap1 ; //0xffff - Cap2 + Cap1 ;
    }
  }
  
  uint16_t GetFrequency(void)
  {
    return 500000/GetDiff();
  }
  
};




#endif // pulseIn_h