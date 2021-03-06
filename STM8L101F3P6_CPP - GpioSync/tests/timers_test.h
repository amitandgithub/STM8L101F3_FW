
#include"system.h"
#include"gpt4.h"
#include"gpt.h" 
#include"pulseIn.h"


void gpt_test(void);
void gpt4_test(void);
void pulseOut_test(void);
void pulseIn_test(void);

gpt4<uint32_t> timer4;
gpt<TIMER2> timer2;
gpt<TIMER3> timer3;

volatile uint16_t counter;
void timer_tests(void)
{
 
  //gpt4_test();
  //gpt_test();
  pulseIn_test();
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
  timer2.HwInit(0x06,249,0);
  timer3.HwInit(0x06,249,0);
  
  timer2.InterruptEnable(TIM_IER_UIE);
  timer3.InterruptEnable(TIM_IER_UIE);
  
  timer2.Start();
  timer3.Start();

  while(1)
  {
    //counter = timer3.GetCounter();
  }  
}


pulseIn<TIMER3,TIM3_Channel_2> PulseIn3;
void pulseIn_test(void)
{
  PulseIn3.HwInit();//(1,0xffff);//4-1u; 3-500ns 2-250ns 1-125ns
  PulseIn3.Start();
  while(1)
  {
    //counter = PulseIn3.GetFrequency();
  }  
}

void pulseOut_test(void)
{
 

  while(1)
  {
    
  }  
}


