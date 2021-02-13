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
#include"gpio.h"

extern void Dummy_ISR();

template<Port_t Port, PIN_t Pin, Mode_t Mode = INPUT_PULLUP, IntEdge_t Edge = NO_INTERRUPT, GpioFptr_t GpioFptr = Dummy_ISR>
class DigitalIn : public gpio
{
public:
    //DigitalIn(){};
    
    //~DigitalIn(){};
    
  void HwInit()
  {
    __disable_interrupt();
    gpio::SetInputMode(Port,Pin,Mode);    
    gpio::SetInterrupt(Port,Pin,Edge,GpioFptr);  
    __enable_interrupt();
  }
    
//    void SetInputMode();
//    
//    void SetInterrupt();
//    
//    void SetPortSensitivity();
//    
//    void SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort, FunctionalState NewState);
        
    bool Read(){ return (bool)(((GPIO_TypeDef*)Port)->IDR & Pin);}    
    
//    FastIn& operator= (FastIn& rhs) {
//        return this->write(rhs.read());
};


#endif //DigitalIn_h