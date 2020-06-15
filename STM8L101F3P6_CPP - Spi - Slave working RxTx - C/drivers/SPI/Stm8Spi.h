




#ifndef Spi_h
#define Spi_h

#include"system.h"
#include"stm8l10x_spi.h"

#define SPI_POLL_TIMEOUT ((uint16_t)5000U)

typedef enum 
{
  SPI_OK,
  SPI_DMA_ERROR,
  SPI_SLAVE_TX_DONE,
  SPI_SLAVE_RX_DONE,
  SPI_BUSY,
  SPI_INVALID_PARAMS,
  SPI_TXE_TIMEOUT,
  SPI_RXNE_TIMEOUT,
  SPI_BUSY_TIMEOUT,
}SpiStatus_t;

typedef void(*spiCallback_t)(SpiStatus_t Status);

typedef enum
{
  SPI_RESET,
  SPI_READY,
  SPI_TX_DONE,
  SPI_RX_DONE,
  SPI_SLAVE_TX,
  SPI_SLAVE_RX,
  SPI_SLAVE_TXRX,
  SPI_SLAVE_RX_LISTENING,
  SPI_MASTER_TX_DMA,
  SPI_MASTER_RX_DMA,
  SPI_SLAVE_TX_DMA,
  SPI_SLAVE_RX_DMA,
  SPI_MASTER_TXRX_DMA,
  SPI_ERROR_BUSY_TIMEOUT,
}SPIState_t;

typedef struct
{
  uint8_t                  TxLen;
  uint8_t                  RxLen; 
  uint8_t*                  TxBuf; 
  uint8_t*                  RxBuf; 
  SPIState_t                SPIState;
  spiCallback_t       XferDoneCallback;
}Transaction_t;


SpiStatus_t Spi_SlaveHwInit();

SPIState_t Spi_GetState();

 void Spi_SlaveTransmit(uint8_t* Buf, uint8_t Len);
    
 void Spi_SlaveReceive(uint8_t* Buf, uint8_t Len);  
 
 void Spi_ISR();
    
#define SPI_ENABLE(__SPI) __SPI->CR1 |= SPI_CR1_SPE

#define SPI_DISABLE(__SPI) __SPI->CR1 &= (uint8_t)(~SPI_CR1_SPE)

#define SPI_WAIT_FOR_TXE_FLAG_TO_SET(_SPI_,TIMEOUT) WaitOnFlag(&_SPI_->SR, SPI_SR_TXE, 0, TIMEOUT)
  
#define SPI_WAIT_FOR_BUSY_FLAG_TO_CLEAR(_SPI_,TIMEOUT) WaitOnFlag(&_SPI_->SR, SPI_SR_BSY, SPI_SR_BSY, TIMEOUT)
  
#define SPI_WAIT_FOR_RXNE_FLAG_TO_SET(_SPI_,TIMEOUT) WaitOnFlag(&_SPI_->SR, SPI_SR_RXNE, 0, TIMEOUT)
  
#define SPI_TXE(_SPI_) _SPI_->SR & SPI_SR_TXE
  
#define SPI_RXNE(_SPI_) _SPI_->SR & SPI_SR_RXNE
  
#define SPI_BYTE_IN_8_BIT(__BUF)      *__BUF.RxBuf++ = SPI->DR; __BUF.RxLen--
  
#define SPI_BYTE_OUT_8_BIT(__BUF)     SPI->DR = *__BUF.TxBuf++; __BUF.TxLen--
  
#define LL_SPI_ClearFlag_OVR() SPI->DR = SPI->DR; SPI->SR = SPI->SR
  
#define SPI_DISABLE_ALL_INTERRUPTS(Interrupt_Flags)  SPI->ICR = 0
 
#define SPI_CLEAR_ALL_INTERRUPTS()  SPI->SR = 0
  
#define SPI_ENABLE_INTERRUPTS(Interrupt_Flags)  SPI->ICR |= (uint8_t)Interrupt_Flags


#endif // Spi_h