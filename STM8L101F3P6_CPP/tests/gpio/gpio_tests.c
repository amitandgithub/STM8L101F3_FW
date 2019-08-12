


#include"gpio_tests.h"

DigitalOut<LED> Led;

DigitalIn<BUTTON,INPUT_PULLUP,INTERRUPT_ON_FALLING,Gpio_Falling_Callback> Button;

static uint8_t Highs,Lows;

void gpio_tests()
{
    Led.HwInit();
    Button.HwInit();
  while(1)
  {
    gpio_poll_test();
    gpio_intr_test();
  }
  
}

void gpio_poll_test()
{
  if(Button.Read())
  {
    Led.High();  
  }
  else
  {
    Led.Low();
  } 
}


void gpio_intr_test()
{
  
  Led.High();
  
  Led.Low();
}

void Gpio_Rising_Callback()
{
  Highs++;
}

void Gpio_Falling_Callback()
{
  Lows++;
}