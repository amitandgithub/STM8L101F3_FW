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
  uint16_t Word;
  uint8_t Array[2];
}Capture_t;

typedef enum{ Tick_125ns=1,Tick_250ns=2,Tick_500ns=3,Tick_1us=4,Tick_2us=5,Tick_4us=6,Tick_8us=7}Tick_t;
typedef enum{ Timer_Channel_1 = 0, Timer_Channel_2 = 1  } Timer_Channel_t;
typedef enum{ TimerPol_Rising = 0, TimerPol_Falling = 1 } TimerPol_t;

template<TIMx_t Timerx, Timer_Channel_t Channel, 
         Tick_t tick = Tick_1us, uint16_t Autoreload = 0xffff, 
         TimerPol_t Polarity = TimerPol_Rising, uint8_t SampleSize = 16, uint8_t Filter = 0, 
         uint8_t ChannelPrescaler = 0>
           
class pulseIn
{
  gpt<Timerx,tick,Autoreload,1> timer;
  uint16_t Samples[SampleSize+2];
  uint8_t SampleIndex;
public:
  
  uint8_t HwInit(void)
  {
    uint8_t IC1Selection, IC2Selection;
    
    //static_assert( (Timerx != 0), "Error: Both edges should not be same");
    
    if(Channel == Timer_Channel_1)
    {
      IC1Selection = TIM3_ICSelection_DirectTI;
      IC2Selection = TIM3_ICSelection_IndirectTI;  
    }
    else
    {
      IC1Selection = TIM3_ICSelection_IndirectTI;
      IC2Selection = TIM3_ICSelection_DirectTI;     
    }
    
    timer.HwInit();
    
    timer.InterruptDisable(0xff); 
      
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
    return 0;
  }
  
  void Start(void)
  {
    timer.InterruptEnable(TIM_IER_CC2IE);
    timer.Start();
  }
  
  void Stop(void)
  {
    timer.InterruptDisable(0xff);
    timer.Stop();
  }  
  
  uint16_t GetCapture1(void)
  {
    Capture_t capture;
    
    capture.Array[0] = ((TIM_TypeDef*)Timerx)->CCR1H;
    capture.Array[1] = ((TIM_TypeDef*)Timerx)->CCR1L;
    
    return capture.Word;
  }
  
  uint16_t GetCapture2(void)
  {    
    Capture_t capture;
    
    capture.Array[0] = ((TIM_TypeDef*)Timerx)->CCR2H;
    capture.Array[1] = ((TIM_TypeDef*)Timerx)->CCR2L;
    return capture.Word;
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
  // It takes 2.88 us to execute
  void GetPulseWidth(void)
  {    
    Capture_t capture1,capture2;
    
    capture1.Array[0] = ((TIM_TypeDef*)Timerx)->CCR1H;
    capture1.Array[1] = ((TIM_TypeDef*)Timerx)->CCR1L;
    
    capture2.Array[0] = ((TIM_TypeDef*)Timerx)->CCR2H;
    capture2.Array[1] = ((TIM_TypeDef*)Timerx)->CCR2L;

    Samples[SampleIndex  ] = capture1.Word;
    Samples[SampleIndex+1] = capture2.Word;
#if 1
    SampleIndex = (SampleIndex + 2) & (SampleSize - 1);
#else
    SampleIndex = (SampleIndex + 2);
    if(SampleIndex >= SampleSize)
    {
      Stop();
    }
#endif
    
  }
  
  
  uint16_t GetFrequency(void)
  {
    return 500000/GetDiff();
  }
  
};




#endif // pulseIn_h