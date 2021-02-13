
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


#include"pulseOut.h"

extern gpt<TIMER3,Tick_1us,0xffff,0> timer3;
extern gpt4<uint32_t> timer4;

template< TIMx_t Timerx, Timer_Channel_t Channel, uint16_t IR_BITS,  uint16_t HDR_MARK,  uint16_t HDR_SPACE,  uint16_t BIT_MARK,  uint16_t ONE_SPACE, uint16_t ZERO_SPACE, uint16_t RPT_SPACE>
class IrEncoder : public pulseOut<Timerx,Channel,38000> 
{
  typedef pulseOut<Timerx,Channel,38000> PulseOut;
public:       
  
  void HwInit()
  {
    PulseOut::HwInit();
  }
  
  
  void Start()
  {
    PulseOut::Start();
  }
  
  void Stop()
  {
    PulseOut::Stop();
  }
  
  void Run(void)
  {    
    
  }
  
  
  void IRQ_Handler(void)
  {
    
  }
  
  void space(uint16_t time)
    {
      Stop();
      if(time > 0) timer4.Delay_US(time);
    }
  
  void mark(uint16_t time)
  {
    Start();
    if(time > 0) timer4.Delay_US(time);
  }
  
  void TxProtocol(uint32_t data)
  {
    // Header
   // mark(HDR_MARK);      
   // space(HDR_SPACE);
    
    Start();
     timer4.Delay_US(HDR_MARK);
     
     Stop();
     timer4.Delay_US(HDR_SPACE);
   
   TxByte(data>>24);
   TxByte(data>>16);
   TxByte(data>>8);
   TxByte(data);
    
    // Footer
    //mark(BIT_MARK);
   // space(0);  // Always end with the LED off
   Start();
     timer4.Delay_US(BIT_MARK);
    Stop();
    
  }
  
  void TxByte(uint8_t data)
  {
    for (uint8_t  mask = 0x80;  mask;  mask >>= 1)
    {
#if 0
      mark(BIT_MARK); 
      
      if (data & mask)
      {        
        space(ONE_SPACE);
      }
      else
      {        
        space(ZERO_SPACE);
      }
#else
     Start();
     timer4.Delay_US(BIT_MARK);
     
     Stop();
     
      if (data & mask)
      {        
        //space(ONE_SPACE);
        timer4.Delay_US(ONE_SPACE);
      }
      else
      {        
        //space(ZERO_SPACE);
        timer4.Delay_US(ZERO_SPACE);
      }
      
#endif
    }
  }
  
  void TxProtocol1(uint32_t data)
  {
    // Header
    mark(HDR_MARK);      
    space(HDR_SPACE);
#if 1
    // Data
    for (uint32_t  mask = 1UL << (IR_BITS - 1);  mask;  mask >>= 1)
    {
      mark(BIT_MARK); 
      
      if (data & mask)
      {        
        space(ONE_SPACE);
      }
      else
      {        
        space(ZERO_SPACE);
      }
    }
    
    // Footer
    mark(BIT_MARK);
    space(0);  // Always end with the LED off
#else
    TxRawData(data);
    
    // Footer
    mark(BIT_MARK);
    space(0);  // Always end with the LED off
#endif
    
  }
  
  void TxRawData(uint32_t data)
  {      
      // Data
      for (uint32_t  mask = 1UL << (IR_BITS - 1);  mask;  mask >>= 1)
      {
        mark(BIT_MARK); 
        
        if (data & mask)
        {        
          space(ONE_SPACE);
        }
        else
        {        
          space(ZERO_SPACE);
        }
      }
      //space(0);  // Always end with the LED off
  }
  
};

#endif //IrDecoder_h
