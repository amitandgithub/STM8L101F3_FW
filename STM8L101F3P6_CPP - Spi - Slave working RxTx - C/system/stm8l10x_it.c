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
#include "stm8l10x_it.h"
#include"DigitalInOut.h"
extern GpioFptr_t EXTI_ISRs[];

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#include"system.h"
//HAL::Spi* m_Spi_ISR;
//extern GpioFptr_t EXTI_ISRs[8];
/* Public functions ----------------------------------------------------------*/

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
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
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
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_IRQHandler, 7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
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
  EXTI->SR1 = GPIO_Pin_0;
  EXTI_ISRs[0]();
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
  EXTI->SR1 = GPIO_Pin_1;
  EXTI_ISRs[1]();
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
  EXTI->SR1 = GPIO_Pin_2;
  EXTI_ISRs[2]();
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
  EXTI->SR1 = GPIO_Pin_3;
  EXTI_ISRs[3]();
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
  EXTI->SR1 = GPIO_Pin_4;
  EXTI_ISRs[4]();
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
  EXTI->SR1 = GPIO_Pin_5;
  EXTI_ISRs[5]();
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
  EXTI->SR1 = GPIO_Pin_6;
  EXTI_ISRs[6]();
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
  EXTI->SR1 = GPIO_Pin_7;
  EXTI_ISRs[7]();
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
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CAP_IRQHandler, 20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_IRQHandler, 21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief Timer3 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CAP_IRQHandler, 22)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief SPI Interrupt routine.
  * @param  None
  * @retval None
  */
#include"Stm8Spi.h"
extern DigitalOut<B1> PB1;
extern void Spi_ISR();
extern Transaction_t SpiConext;
INTERRUPT_HANDLER(SPI_IRQHandler, 26)
{
  PB1.High();
  //Spi_ISR();
  if( SPI->SR & SPI_SR_RXNE )
  {
    if(SpiConext.SPIState == SPI_SLAVE_TX)
    {
      SPI_BYTE_OUT_8_BIT(SpiConext);
      
      if(SpiConext.TxLen == 0)
      {             
        SpiConext.SPIState = SPI_TX_DONE;
        SPI_DISABLE_ALL_INTERRUPTS();
        //SPI_DISABLE(SPI);
        if(SpiConext.XferDoneCallback) SpiConext.XferDoneCallback(SPI_SLAVE_TX_DONE);     
      }   
    } 
    else if(SpiConext.SPIState == SPI_SLAVE_RX)
    {
      SPI_BYTE_IN_8_BIT(SpiConext);
      
      if(SpiConext.RxLen == 0)
      {               
        SPI_DISABLE_ALL_INTERRUPTS();
        //SPI_DISABLE(SPI);
        SpiConext.SPIState = SPI_RX_DONE;
        if(SpiConext.XferDoneCallback) SpiConext.XferDoneCallback(SPI_SLAVE_RX_DONE);     
      }   
    }
  }
#if 0
  if( SPI->SR & SPI_SR_RXNE )
  {
    if(HAL::Spi::m_Transaction.SPIState == HAL::Spi::SPI_SLAVE_TX)
    {
      SPI_BYTE_OUT_8_BIT(HAL::Spi::m_Transaction);
      
      if(HAL::Spi::m_Transaction.TxLen == 0)
      {             
        HAL::Spi::m_Transaction.SPIState = HAL::Spi::SPI_TX_DONE;
        //SPI_DISABLE_INTERRUPTS(SPI_ICR_TXIE | SPI_ICR_RXIE | SPI_ICR_ERRIE );
        //SPI->ICR = 0;
        SPI_DISABLE_ALL_INTERRUPTS();
        if(HAL::Spi::m_Transaction.XferDoneCallback) HAL::Spi::m_Transaction.XferDoneCallback(HAL::Spi::SPI_SLAVE_TX_DONE);     
      }   
    } 
    else if(HAL::Spi::m_Transaction.SPIState == HAL::Spi::SPI_SLAVE_RX)
    {
      SPI_BYTE_IN_8_BIT(HAL::Spi::m_Transaction);
      
      if(HAL::Spi::m_Transaction.RxLen == 0)
      {               
        //SPI_DISABLE_INTERRUPTS(SPI_ICR_TXIE | SPI_ICR_RXIE | SPI_ICR_ERRIE );
        //SPI->ICR = 0;
        SPI_DISABLE_ALL_INTERRUPTS();
        HAL::Spi::m_Transaction.SPIState = HAL::Spi::SPI_RX_DONE;
        if(HAL::Spi::m_Transaction.XferDoneCallback) HAL::Spi::m_Transaction.XferDoneCallback(HAL::Spi::SPI_SLAVE_RX_DONE);     
      }   
    }
          
  }
#endif
  
  PB1.Low();
}

/**
  * @brief USART TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART_TX_IRQHandler, 27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

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

