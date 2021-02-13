/******************
** CLASS: gpio
**
** DESCRIPTION:
**  Gpio common functionality for DigitalIn and DigitalOut
**
** CREATED: 21-Jan-21, by Amit Chaudhary
**
** FILE: gpio.h
**
******************/
#ifndef gpio_h
#define gpio_h

#include"DigitalInOut.h"

class gpio
{
public:
    
    void HwInit();
    
    void SetOutputMode(Port_t Port, PIN_t Pin,Mode_t Mode)
    {
      switch(Mode)
      {
      case OUTPUT_OPEN_DRAIN:
        ((GPIO_TypeDef*)Port)->DDR |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR1 &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR2 &= ~Pin; // 0
        break;
      case OUTPUT_OPEN_DRAIN_PUSH_PULL:
        ((GPIO_TypeDef*)Port)->DDR |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR1 |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR2 &= ~Pin; // 0
        break;
      case OUTPUT_OPEN_DRAIN_FAST:
        ((GPIO_TypeDef*)Port)->DDR |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR1 &= ~Pin; // 0
        ((GPIO_TypeDef*)Port)->CR2 |=  Pin; // 1
        break;
      case OUTPUT_OPEN_DRAIN_PUSH_PULL_FAST:
        ((GPIO_TypeDef*)Port)->DDR |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR1 |=  Pin; // 1
        ((GPIO_TypeDef*)Port)->CR2 |=  Pin; // 1
      default: break;  
      }  
    }

    void SetInputMode(Port_t Port, PIN_t Pin,Mode_t Mode)
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
    
    void SetInterrupt(Port_t Port,PIN_t Pin,IntEdge_t Edge, GpioFptr_t GpioFptr)
    {
      switch(Pin)
      {
      case PIN_0:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P0IS);
        EXTI->CR1 |= (uint8_t)((Edge) << 0);
        EXTI_ISRs[0] = GpioFptr;
        break;
      case PIN_1:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P1IS);
        EXTI->CR1 |= (uint8_t)((Edge) << 2);
        EXTI_ISRs[1] = GpioFptr;
        break;
      case PIN_2:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P2IS);
        EXTI->CR1 |= (uint8_t)((Edge) << 4);
        EXTI_ISRs[2] = GpioFptr;
        break;
      case PIN_3:
        EXTI->CR1 &= (uint8_t)(~EXTI_CR1_P3IS);
        EXTI->CR1 |= (uint8_t)((Edge) << 6);
        EXTI_ISRs[3] = GpioFptr;
        break;
      case PIN_4:
        EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P4IS);
        EXTI->CR2 |= (uint8_t)((Edge) << 0);
        EXTI_ISRs[4] = GpioFptr;
        break;
      case PIN_5:
        EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P5IS);
        EXTI->CR2 |= (uint8_t)((Edge) << 2);
        EXTI_ISRs[5] = GpioFptr;
        break;
      case PIN_6:
        EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P6IS);
        EXTI->CR2 |= (uint8_t)((Edge) << 4);
        EXTI_ISRs[6] = GpioFptr;
        break;
      case PIN_7:
        EXTI->CR2 &= (uint8_t)(~EXTI_CR2_P7IS);
        EXTI->CR2 |= (uint8_t)((Edge) << 6);
        EXTI_ISRs[7] = GpioFptr;
      default: break;
      }
      
      if(Port == PORTB_FULL)
      {
        EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PBIS); 
        /* Write EXTI  port sensitivity */
        EXTI->CR3 |= (uint8_t)((uint8_t)(Edge) << (uint8_t)Port);
        EXTI_ISRs[8] = GpioFptr;
      }
      else if (Port == PORTD_FULL)
      {
        EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PDIS);
        /* Write EXTI  port sensitivity */
        EXTI->CR3 |= (uint8_t)((uint8_t)(Edge) << (uint8_t)Port);
        EXTI_ISRs[9] = GpioFptr;
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
    
    void SetPortSensitivity(Port_t Port,IntEdge_t Edge)
    {
      /* Clear EXTI  port sensitivity */
      if (Port != PORTB_FULL)
      {
        EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PDIS);
      }
      else /* PortNum == EXTI_Port_B */
      {
        EXTI->CR3 &= (uint8_t)(~EXTI_CR3_PBIS);
      }
      
      /* Write EXTI  port sensitivity */
      EXTI->CR3 |= (uint8_t)((uint8_t)(Edge) << (uint8_t)Port);
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
    void SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort, FunctionalState NewState)
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
};




















#endif // gpio_h