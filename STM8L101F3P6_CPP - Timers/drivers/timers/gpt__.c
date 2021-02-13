

#include "gpt.h"
#include "uart.h"
uint32_t System_Ticks;

uint8_t gpt_ClockEnable(TIM1_TypeDef* Timerx)
{

    if(Timerx == (TIM1_TypeDef*)TIM1)
    {
        CLK->PCKENR2 |= (uint8_t)CLK_PCKENR2_TIM1; 
    }
    else if(Timerx == (TIM1_TypeDef*)TIM2)
    {
        CLK->PCKENR1 |= (uint8_t) CLK_PCKENR1_TIM2; 
    }
    else if(Timerx == (TIM1_TypeDef*)TIM3)
    {
        CLK->PCKENR1 |= (uint8_t) CLK_PCKENR1_TIM3; 
    }
    else if(Timerx == (TIM1_TypeDef*)TIM4)
    {
        CLK->PCKENR1 |= (uint8_t) CLK_PCKENR1_TIM4; 
    }
    else if(Timerx == (TIM1_TypeDef*)TIM5)
    {
        CLK->PCKENR3 |= (uint8_t) CLK_PCKENR3_TIM5; 
    }
    else 
    {
        Uart_TxStr(DEBUG_UART,"Timer CLK Init Error \n\r");
        return 0xff; 
    }

    return 0x00;
}



uint8_t gpt_HwInit(TIM1_TypeDef* Timerx, uint16_t Prescaler, uint16_t Autoreload, uint8_t mode)
{
    
    if( gpt_ClockEnable(Timerx) != 0 )
    {
        return 0xff; // error
    }    

    Timerx->SR1 = (uint8_t)0x00;
    Timerx->SR2 = (uint8_t)0x00;

    Timerx->ARRH = (uint8_t)(Autoreload >> 8);
    Timerx->ARRL = (uint8_t)(Autoreload);

    /* Set the Prescaler value */
    Timerx->PSCRH = (uint8_t)(Prescaler >> 8);
    Timerx->PSCRL = (uint8_t)(Prescaler);

    /* Select the Counter Mode */
    Timerx->CR1 = (uint8_t)((uint8_t)(Timerx->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR))) | (uint8_t)(mode));

    /* Set the Repetition Counter value */
    //Timerx->RCR = TIM1_RepetitionCounter;
    Uart_TxStr(DEBUG_UART,"Timer Init Done \n\r");
    return 0;
}


uint16_t gpt_GetCounter(TIM1_TypeDef* Timerx)
{
  /* Get the Counter Register value */
  uint16_t tmpcntr = 0;
  uint8_t tmpcntrl = 0, tmpcntrh = 0;

  tmpcntrh = Timerx->CNTRH;
  tmpcntrl = Timerx->CNTRL;

  tmpcntr  = (uint16_t)(tmpcntrl);
  tmpcntr |= (uint16_t)((uint16_t)tmpcntrh << 8);

  /* Get the Counter Register value */
  return (uint16_t)tmpcntr;
}

// uint32_t gpt_Millis(void)
// {
//     //uint16_t tmpcntr = 0;
//    // tmpcntr = (((uint16_t)(TIM_X->CNTRH))<<8) | TIM_X->CNTRL ;

//     //return (uint32_t)( (uint32_t)(System_Ticks_16*64) + gpt_GetCounter(TIM_X) );
//     return System_Ticks;
// }


@svlreg INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler, 23)
{
	TIM1->SR1 = (uint8_t)0x00;
	TIM1->SR2 = (uint8_t)0x00;

    System_Ticks++;
}


@svlreg INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler, 19)
{
	TIM2->SR1 = (uint8_t)0x00;
	TIM2->SR2 = (uint8_t)0x00;

    System_Ticks++;
}

@svlreg INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler, 21)
{
    TIM3->SR1 = (uint8_t)0x00;
    TIM3->SR2 = (uint8_t)0x00;

    System_Ticks++;
}



void Timer_Test(void)
{
    if( gpt_HwInit(TIM_X,GPT_TIM_CALC_PSC(16000000,1000000),1000,0) != 0)
    {
        Uart_TxStr(DEBUG_UART,"Timer Init Error \n\r");
        return;
    }

    gpt_EnableUpdateEvent(TIM_X);    

    gpt_InterruptEnable(TIM_X,TIM1_IER_UIE);

    gpt_Enable(TIM_X);

    gpt_GeneratUpdateEvent(TIM_X);

    #if 0
    Uart_TxHex8(DEBUG_UART, CLK->PCKENR1);
    Uart_TxHex8(DEBUG_UART, CLK->PCKENR2);
    Uart_TxHex8(DEBUG_UART, TIM_X->CR1);
    Uart_TxHex8(DEBUG_UART, TIM_X->ARRL);
    Uart_TxHex8(DEBUG_UART, TIM_X->PSCRL); 
    
#endif
    while(1)
    {
        Uart_TxStr(DEBUG_UART,"\n\r");
        Uart_TxHex32(DEBUG_UART, gpt_Millis());
        Uart_TxStr(DEBUG_UART," ");
        Uart_TxHex16(DEBUG_UART, gpt_GetCounter(TIM_X));
        delay_ms(1000);
    }


}