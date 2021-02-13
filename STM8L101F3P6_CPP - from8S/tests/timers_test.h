
#ifndef TIMERS_TEST_H
#define TIMERS_TEST_H


#include"system.h"
#include"gpt4.h"
#include"gpt.h" 
#include"pulseIn.h"
#include"IrDecoder.h" 
#include"pulseOut.h"
#include"IrEncoder.h" 
#include"TvCodes.h"

//extern DigitalOut<C4> PC4;
//extern DigitalOut<B1> PB1;

void timer_tests(void);
void gpt_test(void);
void gpt4_test(void);
void pulseOut_test(void);
void pulseIn_test(void);
void IrDecoder_test(void);
void IR_Transmitter(void); 
void IR_Receiver(void);
void IR_Extender(void);
void IR_Loopback(void);
void WT_to_DDC(uint32_t code);
void WT_to_Samsung(uint32_t code);


typedef
IrDecoder<TIMER2,TIM2_CH1_PB0,
SAMSUNG_BITS,
SAMSUNG_HDR_MARK,
SAMSUNG_HDR_SPACE,
SAMSUNG_BIT_MARK,
SAMSUNG_ONE_SPACE,
SAMSUNG_ZERO_SPACE,
SAMSUNG_RPT_SPACE> Ir_Decoder_t;

typedef
IrEncoder<TIMER3,TIM3_CH1_PB1,
SAMSUNG_BITS,
SAMSUNG_HDR_MARK,
SAMSUNG_HDR_SPACE,
SAMSUNG_BIT_MARK,
SAMSUNG_ONE_SPACE,
SAMSUNG_ZERO_SPACE,
SAMSUNG_RPT_SPACE> Ir_Encoder_t;

extern Ir_Decoder_t Ir_Decoder;
extern Ir_Encoder_t Ir_Encoder;





#endif //TIMERS_TEST_H