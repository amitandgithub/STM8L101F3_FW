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
#include"interrupt.h"
#include"queue.h"
#include"DigitalIn.h"

template<TIMx_t Timerx, Timer_Channel_t Channel, 
         Tick_t tick = Tick_1us, uint16_t Autoreload = 0xffff, 
         TimerPol_t Polarity = TimerPol_Rising, uint8_t SampleSize = 8, uint8_t Filter = 0, 
         uint8_t ChannelPrescaler = 0>
           
class pulseIn : public gpt<Timerx,tick,Autoreload,0>
{
public:
  
  typedef gpt<Timerx,tick,Autoreload,0> Gpt;
  
  typedef union
  {
    uint16_t Word;
    uint8_t Array[2];
  }Capture_t;  
  
  typedef queue<uint16_t, uint8_t, SampleSize> queue_t;
  queue_t Q;
  
public:
  
  uint8_t HwInit(void)
  {
    uint8_t IC1Selection, IC2Selection;
    
    //static_assert( (Timerx != 0), "Error: Both edges should not be same");
    
    if( (Channel == TIM2_CH1_PB0) || (Channel == TIM3_CH1_PB1) )
    {
      IC1Selection = TIM3_ICSelection_DirectTI;
      IC2Selection = TIM3_ICSelection_IndirectTI;  
    }
    else
    {
      IC1Selection = TIM3_ICSelection_IndirectTI;
      IC2Selection = TIM3_ICSelection_DirectTI;     
    }
    
    GpioHwInit();
    
    Gpt::HwInit();
    
    Gpt::InterruptDisable(0xff); 
      
    ((TIM_TypeDef*)Timerx)->CCER1 = 0;
    ((TIM_TypeDef*)Timerx)->CCMR1 = 0;
    ((TIM_TypeDef*)Timerx)->CCMR2 = 0;
    
    ((TIM_TypeDef*)Timerx)->CCMR1 |= (uint8_t)ChannelPrescaler | (uint8_t)(((uint8_t)(IC1Selection)) | ((uint8_t)(Filter << 4)));
    ((TIM_TypeDef*)Timerx)->CCMR2 |= (uint8_t)ChannelPrescaler | (uint8_t)(((uint8_t)(IC2Selection)) | ((uint8_t)(Filter << 4)));    
    
    if (Polarity == TimerPol_Falling)
    {
      ((TIM_TypeDef*)Timerx)->CCER1 |= TIM_CCER1_CC1P | TIM_CCER1_CC1E | TIM_CCER1_CC2E;
    }
    else
    {
      ((TIM_TypeDef*)Timerx)->CCER1 |= TIM_CCER1_CC2P | TIM_CCER1_CC1E | TIM_CCER1_CC2E ;
    }          
    
    Gpt::Start();
    
    return 0;
  }
  
  void GpioHwInit(void)
  {
    if(Channel == TIM2_CH1_PB0)
    {
      DigitalIn<B0> PB0; 
      PB0.HwInit();
    }
    else if(Channel == TIM2_CH2_PB2)
    {
      DigitalIn<B2> PB2; 
      PB2.HwInit();
    }
    else if(Channel == TIM3_CH1_PB1)
    {
      DigitalIn<B1> PB1; 
      PB1.HwInit();
    }
    else if(Channel == TIM3_CH1_PD0)
    {
      DigitalIn<D0> PD0; 
      PD0.HwInit();
    }
    else
    {
      // Error
    }
  }

  void Start(void)
  {
    Gpt::InterruptEnable(TIM_IER_CC2IE); //TIM_IER_UIE
  }
  
  void Stop(void)
  {
    Gpt::InterruptDisable(TIM_IER_CC2IE);
  }  
  
  void CaptureEnable(void)
  {
    ((TIM_TypeDef*)Timerx)->CCER1 |=  TIM_CCER1_CC1E | TIM_CCER1_CC2E;
  }
  
  void CaptureDisable(void)
  {
    ((TIM_TypeDef*)Timerx)->CCER1 &=  (uint8_t)~(TIM_CCER1_CC1E | TIM_CCER1_CC2E);
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
 
  // Interrupt time  = 1.92us
  void GetPulseWidth(void)
  {    
    Capture_t capture1,capture2;
    
    capture1.Array[0] = ((TIM_TypeDef*)Timerx)->CCR1H;
    capture1.Array[1] = ((TIM_TypeDef*)Timerx)->CCR1L;
    
    capture2.Array[0] = ((TIM_TypeDef*)Timerx)->CCR2H;
    capture2.Array[1] = ((TIM_TypeDef*)Timerx)->CCR2L;
    
    Q.Write(capture2.Word - capture1.Word); // 3.68 us
  }
  
  uint16_t GetFrequency(void)
  {
    return 500000/GetDiff();
  }
  
  void IRQ_Handler(void)
  {
    GetPulseWidth();
  }
  
};




#endif // pulseIn_h