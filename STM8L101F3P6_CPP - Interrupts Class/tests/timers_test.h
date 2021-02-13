
#include"system.h"
#include"gpt4.h"
#include"gpt.h" 
#include"pulseIn.h"
#include"IrDecoder.h"

//#define SAMSUNG_BITS          32
//#define SAMSUNG_HDR_MARK    4500
//#define SAMSUNG_HDR_SPACE   4500
//#define SAMSUNG_BIT_MARK     560
//#define SAMSUNG_ONE_SPACE   1600
//#define SAMSUNG_ZERO_SPACE   560
//#define SAMSUNG_RPT_SPACE   2250

extern DigitalOut<C4> PC4;
void gpt_test(void);
void gpt4_test(void);
void pulseOut_test(void);
void pulseIn_test(void);
void IrDecoder_test(void);

gpt4<uint32_t> timer4;
gpt<TIMER2,Tick_4us,249,0> timer2;
gpt<TIMER3,Tick_4us,249,0> timer3;

volatile uint16_t counter;
void timer_tests(void)
{
 
  //gpt4_test();
  //gpt_test();
  //pulseIn_test();
   IrDecoder_test();
  //pulseOut_test();

}

void gpt4_test(void)
{
  timer4.HwInit(0x06,249);
  timer4.Start();

  while(1)
  {
    counter = timer4.GetCounter();
  }  
}


void gpt_test(void)
{
  timer2.HwInit();
  timer3.HwInit();
  
  timer2.InterruptEnable(TIM_IER_UIE);
  timer3.InterruptEnable(TIM_IER_UIE);
  
  timer2.Start();
  timer3.Start();

  while(1)
  {
    //counter = timer3.GetCounter();
  }  
}

#if 0
pulseIn<TIMER2,Timer_Channel_1,Tick_1us,0xffff> PulseIn3;
void pulseIn_test(void)
{
  PulseIn3.HwInit();
  PulseIn3.Start();
  while(1)
  {
    //counter = PulseIn3.GetFrequency();
  }  
}
#endif

IrDecoder<TIMER2,Timer_Channel_1,
SAMSUNG_BITS,
SAMSUNG_HDR_MARK,
SAMSUNG_HDR_SPACE,
SAMSUNG_BIT_MARK,
SAMSUNG_ONE_SPACE,
SAMSUNG_ZERO_SPACE,
SAMSUNG_RPT_SPACE> Ir_Decoder;

void IrDecoder_test(void)
{ 
  static uint32_t Results;
  Ir_Decoder.HwInit();
  Ir_Decoder.Start();
  while(1)
  {
    Ir_Decoder.Run();
    
    if(Ir_Decoder.GetStatus())
    {
      Ir_Decoder.Decode(&Results);
      if( (Results == 0xE0E0E01f) || (Results == 0x14EBE01F) )
      {
        PC4.Toggle();
      }
      Ir_Decoder.Start();     
    }
  }  
}



void pulseOut_test(void)
{ 
  
  Ir_Decoder.HwInit();
  Ir_Decoder.Start();
  while(1)
  {
   
    
  }  
}
