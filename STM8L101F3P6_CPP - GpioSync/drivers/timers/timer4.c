

#include "timer4.h"
#include "uart.h"

uint32_t timer4_System_Ticks;

uint8_t timer4_HwInit(uint8_t Prescaler, uint8_t Autoreload)
{
    disableInterrupts();

    CLK->PCKENR |= (uint8_t)CLK_PCKENR_TIM4;
    TIM4->SR1 = 0;
    TIM4->ARR = Autoreload;
    TIM4->PSCR = Prescaler;
    TIM4->IER = TIM4_IER_UIE;
    TIM4->CR1 = TIM4_CR1_ARPE;
    TIM4->EGR |= TIM4_EGR_UG;

    enableInterrupts();

    return 0;
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler, 25)
{
    // GpioToggle(TIM_DEBUG_GPIO);
    TIM4->SR1 = (uint8_t)0x00;
    timer4_System_Ticks++;
}


uint32_t timer4_Ticks(void)
{
    uint32_t ticks;
    disableInterrupts();
    ticks = timer4_System_Ticks;
    enableInterrupts();
    return ticks;
}

uint8_t Prescaler;

void Timer4_Test(void)
{
    timer4_HwInit(Prescaler, 0xf9);
    timer4_Enable();

    //GpioSetOutputMode(TIM_DEBUG_GPIO, OUTPUT_OPEN_DRAIN_PUSH_PULL);
#if 0
    while (1)
    {

        Uart_TxHex32(DEBUG_UART, timer4_System_Ticks);
        Uart_TxStr(DEBUG_UART, "\n\r");
        delay_ms(100);
        
    }
#endif
}