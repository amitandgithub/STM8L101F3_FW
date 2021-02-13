

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
#include"DigitalInOut.h"
#include"gpio.h"

template<Port_t Port, PIN_t Pin,Mode_t Mode = OUTPUT_OPEN_DRAIN_PUSH_PULL>
class DigitalOut : public gpio
{
public:

  void HwInit(){gpio::SetOutputMode(Port,Pin,Mode);}
    
    bool Read(){ return (bool)((GPIO_TypeDef*)Port)->ODR & Pin;}    
    
    void High(){((GPIO_TypeDef*)Port)->ODR |= Pin;}
    
    void Low(){((GPIO_TypeDef*)Port)->ODR &= ~Pin;}
    
    void Toggle(){ ((GPIO_TypeDef*)Port)->ODR ^= Pin;}
};


//template<Port_t Port, PIN_t Pin,Mode_t Mode>
//void DigitalOut<Port,Pin,Mode>::HwInit()
//{
//	SetOutputMode();
//}

//template<Port_t Port, PIN_t Pin,Mode_t Mode>
//void DigitalOut<Port,Pin,Mode>::High()
//{
//    ((GPIO_TypeDef*)Port)->ODR |= Pin;
//}

//template<Port_t Port, PIN_t Pin,Mode_t Mode>
//void DigitalOut<Port,Pin,Mode>::Low()
//{
//    ((GPIO_TypeDef*)Port)->ODR &= ~Pin;
//}
//
//template<Port_t Port, PIN_t Pin,Mode_t Mode>
//void DigitalOut<Port,Pin,Mode>::Toggle()
//{
//    ((GPIO_TypeDef*)Port)->ODR ^= Pin;
//}


#endif // DigitalOut