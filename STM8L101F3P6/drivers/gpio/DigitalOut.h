

/******************
** FILE: DigitalOut.h
**
** DESCRIPTION:
**  Gpio related functionality
**
** CREATED: 28/7/2019, by Amit Chaudhary
******************/
#ifndef DigitalOut_h
#define DigitalOut_h

#include"system.h"
typedef enum
{
  PORTA = GPIOA_BaseAddress,
  PORTB = GPIOB_BaseAddress,
  PORTC = GPIOC_BaseAddress,
  PORTD = GPIOD_BaseAddress,
}Port_t;

typedef enum
{
  PIN0 = 1<<0,
  PIN1 = 1<<1,
  PIN2 = 1<<2,
  PIN3 = 1<<3,
  PIN4 = 1<<4,
  PIN5 = 1<<5,
  PIN6 = 1<<6,
  PIN7 = 1<<7,
}Pin_t;

typedef enum
{
  OUTPUT_OPEN_DRAIN,
  OUTPUT_OPEN_DRAIN_PUSH_PULL,
  OUTPUT_OPEN_DRAIN_FAST,
  OUTPUT_OPEN_DRAIN_PUSH_PULL_FAST,
}GpioMode_t;

template<Port_t Port, Pin_t Pin,Mode_t Mode>
class DigitalOut
{
typedef GPIO_TypeDef*       Port_t;
typedef GPIO_Pin_TypeDef    Pin_t ;
typedef GPIO_Mode_TypeDef   Mode_t ;

void HwInit();
void SetGpioMode(Port_t port,Pin_t pin,GpioMode_t mode);
void On();
void Off();
void Toggle();

};

/* Port A pin definitions */
#define A0 GPIOA,Pin_0
#define A1 GPIOA,Pin_1
#define A2 GPIOA,Pin_2
#define A3 GPIOA,Pin_3
#define A4 GPIOA,Pin_4
#define A5 GPIOA,Pin_5
#define A6 GPIOA,Pin_6
#define A7 GPIOA,Pin_7

/* Port B pin definitions */
#define B0 GPIOB,Pin_0
#define B1 GPIOB,Pin_1
#define B2 GPIOB,Pin_2
#define B3 GPIOB,Pin_3
#define B4 GPIOB,Pin_4
#define B5 GPIOB,Pin_5
#define B6 GPIOB,Pin_6
#define B7 GPIOB,Pin_7

/* Port C pin definitions */
#define C0 GPIOC,Pin_0
#define C1 GPIOC,Pin_1
#define C2 GPIOC,Pin_2
#define C3 GPIOC,Pin_3
#define C4 GPIOC,Pin_4
#define C5 GPIOC,Pin_5
#define C6 GPIOC,Pin_6
#define C7 GPIOC,Pin_7

/* Port D pin definitions */
#define D0 GPIOD,Pin_0
#define D1 GPIOD,Pin_1
#define D2 GPIOD,Pin_2
#define D3 GPIOD,Pin_3
#define D4 GPIOD,Pin_4
#define D5 GPIOD,Pin_5
#define D6 GPIOD,Pin_6
#define D7 GPIOD,Pin_7


void DigitalOut::HwInit()
{
	
}

template<Port_t Port, Pin_t Pin,Mode_t Mode>
void DigitalOut<Port,Pin,Mode>::SetGpioMode(Port_t Port,Pin_t Pin,GpioMode_t Mode)
{
  switch(Mode)
  {
  case INPUT_FLOATING:
    port->DDR &= ~(uint8_t)(pin); // 0
    port->CR1 &= ~(uint8_t)(pin); // 0
    port->CR2 &= ~(uint8_t)(pin); // 0
    break;
  case INPUT_PULLUP:
    port->DDR &= ~(uint8_t)(pin);  // 0
    port->CR1 |=  (uint8_t)(pin);  // 1
    port->CR2 &= ~(uint8_t)(pin);  // 0
    break;
  case INPUT_FLOATING_INTERRUPT:
    port->DDR &= ~(uint8_t)(pin); // 0
    port->CR1 &= ~(uint8_t)(pin); // 0
    port->CR2 |=  (uint8_t)(pin); // 1
    break;
  case INPUT_PULLUP_INTERRUPT:
    port->DDR &= ~(uint8_t)(pin); // 0
    port->CR1 |=  (uint8_t)(pin); // 1
    port->CR2 |=  (uint8_t)(pin); // 1
    break;
  case OUTPUT_OPEN_DRAIN:
    port->DDR |=  (uint8_t)(pin); // 1
    port->CR1 &= ~(uint8_t)(pin); // 0
    port->CR2 &= ~(uint8_t)(pin); // 0
    break;
  case OUTPUT_OPEN_DRAIN_PUSH_PULL:
    port->DDR |=  (uint8_t)(pin); // 1
    port->CR1 |=  (uint8_t)(pin); // 1
    port->CR2 &= ~(uint8_t)(pin); // 0
    break;
  case OUTPUT_OPEN_DRAIN_FAST:
    port->DDR |=  (uint8_t)(pin); // 1
    port->CR1 &= ~(uint8_t)(pin); // 0
    port->CR2 |=  (uint8_t)(pin); // 1
    break;
  case OUTPUT_OPEN_DRAIN_PUSH_PULL_FAST:
    port->DDR |=  (uint8_t)(pin); // 1
    port->CR1 |=  (uint8_t)(pin); // 1
    port->CR2 |=  (uint8_t)(pin); // 1
  default: break;  
  }  
}

template<Port_t Port, Pin_t Pin,Mode_t Mode>
void DigitalOut<Port,Pin,Mode>::On()
{
  port->ODR |= pin;
}

template<Port_t Port, Pin_t Pin,Mode_t Mode>
void DigitalOut<Port,Pin,Mode>::Off()
{
  port->ODR &= (uint8_t)(~pin);
}

template<Port_t Port, Pin_t Pin,Mode_t Mode>
void DigitalOut<Port,Pin,Mode>::Toggle()
{
  port->ODR ^= pin;
}

#endif // DigitalOut