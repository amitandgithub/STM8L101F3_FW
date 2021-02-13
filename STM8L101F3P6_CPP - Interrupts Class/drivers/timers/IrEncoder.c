
/******************
** CLASS: IrEncoder
**
** DESCRIPTION:
**  Implements the IrEncoder driver
**
** CREATED: 15 Jan 2021, by Amit Chaudhary
**
** FILE: IrEncoder.h
**
******************/


#ifndef IrEncoder_h
#define IrEncoder_h


#include"pulseIn.h"

template< TIMx_t Timerx, Timer_Channel_t Channel, uint16_t IR_BITS,  uint16_t HDR_MARK,  uint16_t HDR_SPACE,  uint16_t BIT_MARK,  uint16_t ONE_SPACE, uint16_t ZERO_SPACE, uint16_t RPT_SPACE>
class IrEncoder //: public pulseOut<PULSE_PARAMS> 
{

public:       
  
  void HwInit()
  {
   
  }
  
  
  void Start()
  {
   
  }
  
  void Stop()
  {
   
  }
  
  void Run(void)
  {    
  
  }
  

  void IRQ_Handler(void)
  {
    
  }
  
  void Encode(uint32_t pResult)
  {
   
  }
  
};

#endif //IrDecoder_h
