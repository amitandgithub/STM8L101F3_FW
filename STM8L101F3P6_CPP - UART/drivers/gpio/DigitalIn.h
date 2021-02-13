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
    
    void SetPortSensitivity(EXTI_Port_TypeDef EXTI_Port);
    
    void SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort, FunctionalState NewState);
        
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
  case PIN_0:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P0IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 0);
    break;
  case PIN_1:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P1IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 2);
    break;
  case PIN_2:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P2IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 4);
    break;
  case PIN_3:
    EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P3IS);
    EXTI->CR1 |= (uint8_t)((Edge) << 6);
    break;
  case PIN_4:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P4IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 0);
    break;
  case PIN_5:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P5IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 2);
    break;
  case PIN_6:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P6IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 4);
    break;
  case PIN_7:
    EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P7IS);
    EXTI->CR2 |= (uint8_t)((Edge) << 6);
  default: break;
  }
}

/**
  * @brief  Set the external interrupt sensitivity of the selected port.
  * @note   The modification of external interrupt sensitivity is only possible 
  *         when the interrupts are disabled.
  * @note   The normal behavior is to disable the interrupts before calling this 
  *         function, and re-enable them after.
  * @note   Global interrupts must be disabled before calling this function.
  * @param  EXTI_Port         The port number to access.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Port_B:   GPIO Port B
  *            @arg EXTI_Port_D:   GPIO Port D 
  * @param  EXTI_TriggerValue The external interrupt sensitivity value to set.
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_Trigger_Falling_Low:     Interrupt on Falling edge and Low level
  *            @arg EXTI_Trigger_Rising:          Interrupt on Rising edge
  *            @arg EXTI_Trigger_Falling:         Interrupt on Falling edge
  *            @arg EXTI_Trigger_Rising_Falling:  Interrupt on Rising and Falling edges      
  * @retval None
  */
template<Port_t Port, PIN_t Pin,Mode_t Mode,IntEdge_t Edge, GpioFptr_t GpioFptr>
void DigitalIn<Port,Pin,Mode,Edge,GpioFptr>:: SetPortSensitivity(EXTI_Port_TypeDef EXTI_Port)
{

  /* Clear EXTI  port sensitivity */
  if (EXTI_Port != EXTI_Port_B)
  {
    EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PDIS);
  }
  else /* PortNum == EXTI_Port_B */
  {
    EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PBIS);
  }

  /* Write EXTI  port sensitivity */
  EXTI->CR3 |= (uint8_t)((uint8_t)(Edge) << (uint8_t)EXTI_Port);

}

/**
  * @brief  Configure the half port interrupt selection.
  * @note   This function must be called once the port sensitivity is configured,
  *          otherwise this function call won't have any effect on the port external interrupt.
  * @param  EXTI_HalfPort The port part  to access (MSB or LSB).
  *          This parameter can be any combination of the following values:
  *            @arg EXTI_HalfPort_B_LSB:     Interrupt selector PB(3:0)
  *            @arg EXTI_HalfPort_B_MSB:     Interrupt selector PB(7:4)
  *            @arg EXTI_HalfPort_D_LSB:     Interrupt selector PE(3:0)
  *            @arg EXTI_HalfPort_D_MSB:     Interrupt selector PE(7:4)
  * @param  NewState  The external interrupt new state.
  * @retval None
  */
template<Port_t Port, PIN_t Pin,Mode_t Mode,IntEdge_t Edge, GpioFptr_t GpioFptr>
void DigitalIn<Port,Pin,Mode,Edge,GpioFptr>:: SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    EXTI->CONF |= (uint8_t)EXTI_HalfPort; /* Enable port interrupt selector */
  }
  else /*NewState == DISABLE */
  {
    EXTI->CONF &= (uint8_t)(~(uint8_t)EXTI_HalfPort); /* Disable port interrupt selector */
  }
}


#endif //DigitalIn_h