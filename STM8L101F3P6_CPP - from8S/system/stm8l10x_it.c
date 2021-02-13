/**
  ******************************************************************************
  * @file    stm8l10x_it.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    01-June-2012
  * @brief   This file contains all the interrupt routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include"stm8l10x_it.h"
#include"DigitalInOut.h"
#include"system.h"
#include"gpio_tests.h"
#include"interrupt.h"
#include"timers_test.h"


/**
  * @brief Dummy interrupt routine
  * @param  None
  * @retval None
  */
#ifdef _COSMIC_
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{
    //SystemInterrupts.Execute(FLASH_IRQ);
}

/**
  * @brief Auto Wake Up Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(AWU_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_IRQHandler, 6)
{
  EXTI->SR2 |= GPIO_Pin_0;

}

/**
  * @brief External IT PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_IRQHandler, 7)
{
  EXTI->SR2 |= GPIO_Pin_1;

}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler, 8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_0;

}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler, 9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_1;

}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler, 10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_2;

}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler, 11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_3;
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler, 12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_4;
  Button.IRQ_Handler();
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler, 13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_5;
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler, 14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_6;
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler, 15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  EXTI->SR1 |= GPIO_Pin_7;
}

/**
  * @brief Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(COMP_IRQHandler, 18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_IRQHandler, 19)
{
    TestGPIO.High();
    TIM2->SR1 = (uint8_t)0x00;
    TIM2->SR2 = (uint8_t)0x00;
    TestGPIO.Low();
}

/**
  * @brief Timer2 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(TIM2_CAP_IRQHandler, 20)
{
  //TestGPIO.High();
  Ir_Decoder.IRQ_Handler();
  //TestGPIO.Low();
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21)
{
    TIM3->SR1 = (uint8_t)0x00;
    TIM3->SR2 = (uint8_t)0x00;
}
/**
  * @brief Timer3 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(TIM3_CAP_IRQHandler, 22)
{
  //TestGPIO.High();
  Ir_Decoder.IRQ_Handler();
  //TestGPIO.Low();
}
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 25)
{
 timer4.IRQ_Handler();
}

/**
  * @brief SPI Interrupt routine.
  * @param  None
  * @retval None
  */

INTERRUPT_HANDLER(SPI_IRQHandler, 26)
{
  TestGPIO.High();
  if( SPI->SR & SPI_SR_RXNE )
  {
    if(HAL::Spi::m_Transaction.SPIState == HAL::Spi::SPI_SLAVE_TX)
    {
      SPI_BYTE_OUT_8_BIT(SPI,HAL::Spi::m_Transaction);
      
      if(SPI_TX_DATA_COMPLETE(HAL::Spi::m_Transaction))
      {             
        HAL::Spi::m_Transaction.SPIState = HAL::Spi::SPI_TX_DONE;
        SPI_DISABLE_ALL_INTERRUPTS(SPI);
        if(HAL::Spi::m_Transaction.XferDoneCallback) HAL::Spi::m_Transaction.XferDoneCallback(HAL::Spi::SPI_SLAVE_TX_DONE);     
      }   
    } 
    else if(HAL::Spi::m_Transaction.SPIState == HAL::Spi::SPI_SLAVE_RX)
    {
      SPI_BYTE_IN_8_BIT(SPI,HAL::Spi::m_Transaction);
      
      if(SPI_RX_DATA_COMPLETE(HAL::Spi::m_Transaction))
      {               
        SPI_DISABLE_ALL_INTERRUPTS(SPI);
        HAL::Spi::m_Transaction.SPIState = HAL::Spi::SPI_RX_DONE;
        if(HAL::Spi::m_Transaction.XferDoneCallback) HAL::Spi::m_Transaction.XferDoneCallback(HAL::Spi::SPI_SLAVE_RX_DONE);     
      }   
    }
    else
    {
      if( SPI->SR & SPI_SR_MODF )
      {
        
      }
    }
  }
  TestGPIO.Low();
}

/**
  * @brief USART TX Interrupt routine.
  * @param  None
  * @retval None
  */
//INTERRUPT_HANDLER(USART_TX_IRQHandler, 27)
//{
//    /* In order to detect unexpected events during development,
//       it is recommended to set a breakpoint on the following instruction.
//    */
//}

/**
  * @brief USART RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART_RX_IRQHandler, 28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief I2C Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C_IRQHandler, 29)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
#if I2C_SLAVE_ONLY      
  i2c::I2C_ISR_Slave();  
#elif I2C_MASTER_ONLY  
  i2c::I2C_ISR_Master();  
#else  
  i2c::I2C_ISR();  
#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

