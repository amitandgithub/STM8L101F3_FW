

/******************
** FILE: DigitalOut.h
**
** DESCRIPTION:
**  Gpio related functionality
**
** CREATED: 28/7/2019, by Amit Chaudhary
******************/
#ifndef DigitalInOut_h
#define DigitalInOut_h

typedef enum
{
  PORTA = GPIOA_BaseAddress,
  PORTB = GPIOB_BaseAddress,
  PORTC = GPIOC_BaseAddress,
  PORTD = GPIOD_BaseAddress,
}Port_t;

typedef enum
{
  PIN_0 = 1<<0,
  PIN_1 = 1<<1,
  PIN_2 = 1<<2,
  PIN_3 = 1<<3,
  PIN_4 = 1<<4,
  PIN_5 = 1<<5,
  PIN_6 = 1<<6,
  PIN_7 = 1<<7,
}PIN_t;

typedef enum
{
  INPUT_FLOATING,
  INPUT_PULLUP,
  INPUT_FLOATING_INTERRUPT,
  INPUT_PULLUP_INTERRUPT,
  OPEN_DRAIN,
  OPEN_DRAIN_PUSH_PULL,
  OPEN_DRAIN_FAST,
  OPEN_DRAIN_PUSH_PULL_FAST,
}Mode_t;

typedef enum
{
  INTERRUPT_ON_FALLING_LOW,
  INTERRUPT_ON_RISING,
  INTERRUPT_ON_FALLING,
  INTERRUPT_ON_RISING_FALLING,
  NO_INTERRUPT
}IntEdge_t;

typedef void (*GpioFptr_t)(void); 
    
/* Port A Pin definitions */
#define A0 PORTA,PIN_0
#define A1 PORTA,PIN_1
#define A2 PORTA,PIN_2
#define A3 PORTA,PIN_3
#define A4 PORTA,PIN_4
#define A5 PORTA,PIN_5
#define A6 PORTA,PIN_6
#define A7 PORTA,PIN_7

/* Port B Pin definitions */
#define B0 PORTB,PIN_0
#define B1 PORTB,PIN_1
#define B2 PORTB,PIN_2
#define B3 PORTB,PIN_3
#define B4 PORTB,PIN_4
#define B5 PORTB,PIN_5
#define B6 PORTB,PIN_6
#define B7 PORTB,PIN_7

/* Port C Pin definitions */
#define C0 PORTC,PIN_0
#define C1 PORTC,PIN_1
#define C2 PORTC,PIN_2
#define C3 PORTC,PIN_3
#define C4 PORTC,PIN_4
#define C5 PORTC,PIN_5
#define C6 PORTC,PIN_6
#define C7 PORTC,PIN_7

/* Port D Pin definitions */
#define D0 PORTD,PIN_0
#define D1 PORTD,PIN_1
#define D2 PORTD,PIN_2
#define D3 PORTD,PIN_3
#define D4 PORTD,PIN_4
#define D5 PORTD,PIN_5
#define D6 PORTD,PIN_6
#define D7 PORTD,PIN_7

#endif // DigitalInOut_h