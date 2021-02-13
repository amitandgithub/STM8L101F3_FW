

#include"timers_test.h"

gpt4<0x04,255> timer4;
gpt<TIMER2,Tick_4us,249,0> timer2;
gpt<TIMER3,Tick_1us,0xffff,0> timer3;
static uint32_t Results;

Ir_Decoder_t Ir_Decoder;
Ir_Encoder_t Ir_Encoder;

void timer_tests(void)
{
 
  //gpt4_test();
  //gpt_test();
  //pulseIn_test();
  // IrDecoder_test();
 // pulseOut_test();
  //IR_Transmitter();
  //IR_Receiver();
  IR_Extender();
  //IR_Loopback();

}

void gpt4_test(void)
{
  timer4.HwInit();
  timer4.Start();

  while(1)
  {    
    TestGPIO.High();
    timer4.Delay_US(1000);
    TestGPIO.Low();
  }  
}


void gpt_test(void)
{
  //timer2.HwInit();
  timer3.HwInit();
  
  //timer2.InterruptEnable(TIM_IER_UIE);
  //timer3.InterruptEnable(TIM_IER_UIE);
  
  //timer2.Start();
  //timer3.Start();

  while(1)
  {
    //PB1.High();
    timer3.Delay_us(4);
    //timer3.Delay_ms(650);
    //PB1.Low();
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



void IR_Receiver(void)
{  
  Ir_Decoder.HwInit();
  Ir_Decoder.Start();
  while(1)
  {    
    Ir_Decoder.Run();
    if(Ir_Decoder.Available())
    {
      Results = Ir_Decoder.Read();
      
      if( (Results == SAMSUNG_32_TV_VOL_UP) )
      {
        TestLED.Toggle();
      }      
    }
  }
}

#if 0
pulseOut<TIMER2,Timer_Channel_1,38000> IrOut;
void pulseOut_test(void)
{  
  uint8_t duty = 50;
  IrOut.HwInit();
  IrOut.Start();
  //IrOut.SetFrequency(38000);
  while(1)
  {
   IrOut.SetDutyCycle(duty++);
   
   delay_ms(20);
    
  }  
}
#endif



void IR_Transmitter(void)
{
  timer4.HwInit();  
  Ir_Encoder.HwInit();
  while(1)
  {
    Ir_Encoder.TxProtocol(0xE0E0E01f); // Samsung IR code for Vol up
    delay_ms(10);
  }  
}

void IR_Extender(void)
{
  timer4.HwInit();  
  Ir_Encoder.HwInit();
  Ir_Decoder.HwInit();
  Ir_Decoder.Start();
  while(1)
  {
   Ir_Decoder.Run();
   if(Ir_Decoder.Available())
   {
     TestGPIO.High();
     WT_to_Samsung(Ir_Decoder.Read());
     TestGPIO.Low();
   }
  }  
}
void WT_to_DDC(uint32_t code)
{
  if(code == WT_CH_UP)
  {
    Ir_Encoder.TxProtocol(DDC_CH_UP);
  }
  else if(code == WT_CH_DOWN)
  {
    Ir_Encoder.TxProtocol(DDC_CH_DOWN);
  }
  else if( (code == WT_VOL_UP) || (code == WT_NAV_RIGHT) )
  {
    Ir_Encoder.TxProtocol(DDC_VOL_UP);
  }
  else if( (code == WT_VOL_DOWN) || (code == WT_NAV_LEFT) )
  {
    Ir_Encoder.TxProtocol(DDC_VOL_DOWN);
  }
  else if(code == WT_MUTE)
  {
    Ir_Encoder.TxProtocol(DDC_MUTE);
  }
  else if(code == WT_POWER)
  {
    Ir_Encoder.TxProtocol(DDC_POWER);
  }  
}

void WT_to_Samsung(uint32_t code)
{
  if(code == WT_CH_UP)
  {
    Ir_Encoder.TxProtocol(SAMSUNG_32_TV_CH_UP);
  }
  else if(code == WT_CH_DOWN)
  {
    Ir_Encoder.TxProtocol(SAMSUNG_32_TV_CH_DOWN);
  }
  else if( (code == WT_VOL_UP) || (code == WT_NAV_RIGHT) )
  {
    Ir_Encoder.TxProtocol(SAMSUNG_32_TV_VOL_UP);
  }
  else if( (code == WT_VOL_DOWN) || (code == WT_NAV_LEFT) )
  {
    Ir_Encoder.TxProtocol(SAMSUNG_32_TV_VOL_DOWN);
  }
  else if(code == WT_MUTE)
  {
    Ir_Encoder.TxProtocol(SAMSUNG_32_TV_MUTE);
  }
  else if(code == WT_POWER)
  {
    Ir_Encoder.TxProtocol(SAMSUNG_32_TV_POWER);
  }  
}

