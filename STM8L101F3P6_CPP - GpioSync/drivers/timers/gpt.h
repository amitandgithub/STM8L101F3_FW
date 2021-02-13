/******************
** CLASS: DigitalIn
**
** DESCRIPTION:
**  Gpio input functionality
**
** CREATED: 29-12-2020, by Amit Chaudhary
**
** FILE: gpt.h
**
******************/
#ifndef gpt_h
#define gpt_h

#include"system.h"

extern uint32_t TIM2Ticks;
extern uint32_t TIM3Ticks;
typedef enum
{
  TIMER2 = TIM2_BaseAddress,
  TIMER3 = TIM3_BaseAddress
}TIMx_t;


template<TIMx_t Timerx>
class gpt
{
  uint32_t* pTicks;
public:
  
  uint8_t HwInit(uint16_t Prescaler, uint16_t Autoreload, uint8_t mode)
  {
    disableInterrupts();
    
    if(((TIM_TypeDef*)Timerx) == TIM2)
    {
      pTicks = &TIM2Ticks;
      CLK->PCKENR |= (uint8_t) CLK_PCKENR_TIM2;
    }
    else if(((TIM_TypeDef*)Timerx) == TIM3)
    {
      pTicks = &TIM3Ticks;
      CLK->PCKENR |= (uint8_t) CLK_PCKENR_TIM3;
    }
    else
    {
      return 0xEE;
    }    
    
    ((TIM_TypeDef*)Timerx)->SR1 = (uint8_t)0x00;
    ((TIM_TypeDef*)Timerx)->SR2 = (uint8_t)0x00;

    ((TIM_TypeDef*)Timerx)->ARRH = (uint8_t)(Autoreload >> 8);
    ((TIM_TypeDef*)Timerx)->ARRL = (uint8_t)(Autoreload);

    /* Set the Prescaler value */
    ((TIM_TypeDef*)Timerx)->PSCR = (uint8_t)(Prescaler);

    /* Select the Counter Mode */
    ((TIM_TypeDef*)Timerx)->CR1 = (uint8_t)((uint8_t)(((TIM_TypeDef*)Timerx)->CR1 & (uint8_t)(~(TIM_CR1_CMS | TIM_CR1_DIR))) | (uint8_t)(mode));

    /* Set the Repetition Counter value */
    //Timerx->RCR = TIM1_RepetitionCounter;

    enableInterrupts();
    
    return 0;
  }
  
 /* 
 TIM_IER_BIE  
 TIM_IER_TIE   
 TIM_IER_CC2IE 
 TIM_IER_CC1IE 
 TIM_IER_UIE 
*/
  void InterruptEnable(uint8_t intterupts)
  {
    ((TIM_TypeDef*)Timerx)->IER |= intterupts;
  }
  
  void InterruptDisable(uint8_t intterupts)
  {
    ((TIM_TypeDef*)Timerx)->IER &= (uint8_t)(~(uint8_t)intterupts);
  }

  void OnePulseModeEnable(void)
  {
    ((TIM_TypeDef*)Timerx)->CR1 |= TIM_CR1_OPM;
  }
  
  void OnePulseModeDisable(void)
  {
    ((TIM_TypeDef*)Timerx)->CR1 &= (uint8_t)(~TIM_CR1_OPM);
  }

  void GeneratUpdateEvent(void)
  {
    ((TIM_TypeDef*)Timerx)->EGR |= (uint8_t)TIM_EGR_UG;
  }
  
  void SetAutoReloadRegister(uint16_t Val)
  {
    ((TIM_TypeDef*)Timerx)->ARRH = (uint8_t)(Val >> 8);
    ((TIM_TypeDef*)Timerx)->ARRL = (uint8_t)(Val);
  }
  
  void DisableUpdateEvent(void)
  {
    ((TIM_TypeDef*)Timerx)->CR1 |= TIM_CR1_UDIS;
  }
  
  void EnableUpdateEvent(void)
  {
    ((TIM_TypeDef*)Timerx)->CR1 &= (uint8_t)(~TIM_CR1_UDIS);
  }
  
  void Start(void)
  {
    EnableUpdateEvent();
    //InterruptEnable(TIM_IER_UIE);
    GeneratUpdateEvent();
    ((TIM_TypeDef*)Timerx)->CR1 |= TIM_CR1_CEN;
  }
  
  void Stop(void)
  {
    //InterruptDisable(TIM_IER_UIE);
    ((TIM_TypeDef*)Timerx)->CR1 &= (uint8_t)(~TIM_CR1_CEN);
  }
  
  uint32_t GetTicks(void)
  {
    uint32_t ticks;
    
    disableInterrupts();
    ticks = *pTicks;
    enableInterrupts();
    return ticks;
  }
  
  uint16_t GetCounter(void)
  {
    /* Get the Counter Register value */
    uint16_t tmpcntr = 0;
    uint8_t tmpcntrl = 0, tmpcntrh = 0;
    
    tmpcntrh = ((TIM_TypeDef*)Timerx)->CNTRH;
    tmpcntrl = ((TIM_TypeDef*)Timerx)->CNTRL;
    
    tmpcntr  = (uint16_t)(tmpcntrl);
    tmpcntr |= (uint16_t)((uint16_t)tmpcntrh << 8);
    
    /* Get the Counter Register value */
    return (uint16_t)tmpcntr;
  } 
  
};
#endif // gpt.h