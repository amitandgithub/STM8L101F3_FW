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


template<TIMx_t Timerx, Timer_Channel_t Channel, 
         Tick_t tick = Tick_1us, uint16_t Autoreload = 0xffff, 
         uint32_t Frequency = 10000>
           
class pulseOut : public gpt<Timerx,tick,Autoreload,1>
{
protected:

public:
  
  uint8_t HwInit(void)
  {
    
    return 0;
  }
  
  void Start(void)
  {
   
  }
  
  void Stop(void)
  {
   
  }  
  
  void IRQ_Handler(void)
  {
    
  }
  
};




#endif // pulseIn_h