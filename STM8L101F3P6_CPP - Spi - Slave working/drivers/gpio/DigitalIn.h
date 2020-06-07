/******************
** CLASS: DigitalIn
**
** DESCRIPTION:
**  Gpio input functionality
**
** CREATED: 8/9/2019, by Amit Chaudhary
**
** FILE: DigitalIn.h
**
******************/
#ifndef DigitalIn_h
#define DigitalIn_h

#include"DigitalInOut.h"

extern void Dummy_ISR();

template<Port_t Port, PIN_t Pin, Mode_t Mode = INPUT_PULLUP, IntEdge_t Edge = NO_INTERRUPT, GpioFptr_t GpioFptr = Dummy_ISR>
class DigitalIn
{
public:
    //DigitalIn(){};
    
    //~DigitalIn(){};
    
    void HwInit();
    
    void SetInputMode();
    
    void SetInterrupt();
        
    bool Read(){ return (bool)(((GPIO_TypeDef*)Port)->IDR & Pin);}    
    
//    FastIn& operator= (FastIn& rhs) {
//        return this->write(rhs.read());
};


template<Port_t Port, PIN_t Pin,Mode_t Mode,IntEdge_t Edge, GpioFptr_t GpioFptr>
void DigitalIn<Port,Pin,Mode,Edge,GpioFptr>::HwInit()
{
    SetInputMode();
    __disable_interrupt();
    SetInterrupt();  
    __enable_interrupt();
}

template<Port_t Port, PIN_t Pin,Mode_t Mode,IntEdge_t Edge, GpioFptr_t GpioFptr>
void DigitalIn<Port,Pin,Mode,Edge,GpioFptr>::SetInputMode()
{
    switch(Mode)
    {
    case INPUT_FLOATING:
        ((GPIO_TypeDef*)Port)->DDR &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR1 &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR2 &= ~Pin; // 0
        break;
    case INPUT_PULLUP:
        ((GPIO_TypeDef*)Port)->DDR &= ~Pin;  // 0
        ((GPIO_TypeDef*)Port)->CR1 |=  Pin;  // 1
        ((GPIO_TypeDef*)Port)->CR2 &= ~Pin;  // 0
        break;
    case INPUT_FLOATING_INTERRUPT:
        ((GPIO_TypeDef*)Port)->DDR &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR1 &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR2 |=  Pin; // 1
        break;
    case INPUT_PULLUP_INTERRUPT:
        ((GPIO_TypeDef*)Port)->DDR &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR1 |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR2 |=  Pin; // 1
        break;
    default: break;  
    }  
}

template<Port_t Port, PIN_t Pin,Mode_t Mode,IntEdge_t Edge, GpioFptr_t GpioFptr>
void DigitalIn<Port,Pin,Mode,Edge,GpioFptr>::SetInterrupt()
{
  switch(Pin)
  {
  case GPIO_Pin_0:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P0IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 0);
    EXTI_ISRs[0] = GpioFptr;
    break;
  case GPIO_Pin_1:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P1IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 2);
    EXTI_ISRs[1] = GpioFptr;
    break;
  case GPIO_Pin_2:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P2IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 4);
    EXTI_ISRs[2] = GpioFptr;
    break;
  case GPIO_Pin_3:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P3IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 6);
    EXTI_ISRs[3] = GpioFptr;
    break;
  case GPIO_Pin_4:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR1_P0IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 0);
    EXTI_ISRs[4] = GpioFptr;
    break;
  case GPIO_Pin_5:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR1_P1IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 2);
    EXTI_ISRs[5] = GpioFptr;
    break;
  case GPIO_Pin_6:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR1_P2IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 4);
    EXTI_ISRs[6] = GpioFptr;
    break;
  case GPIO_Pin_7:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR1_P3IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 6);
    EXTI_ISRs[7] = GpioFptr;
  default: break;
  }
  
//  if(port == GPIOB)
//  {
//    EXTI->CR3 &= 0xFC;
//    EXTI->CR3 |= (uint8_t)((Edge) << 0);
//  }
//  else 
//  {
//    EXTI->CR3 &= 0xF3;
//    EXTI->CR3 |= (uint8_t)((Edge) << 2);
//  }
  
}




#endif //DigitalIn_h