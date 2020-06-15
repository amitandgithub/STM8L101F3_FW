


#include"Stm8Spi.h"
#include"DigitalIn.h"
#include"DigitalInOut.h"

Transaction_t SpiConext;

SpiStatus_t Spi_SlaveHwInit()
{
  //  DigitalIn<B4,INPUT_PULLUP> Cs - INPUT_PULLUP;
  //  DigitalIn<B5,INPUT_PULLUP> Clk - INPUT_PULLUP;
  //  DigitalIn<B6,INPUT_FLOATING> Mosi - INPUT_FLOATING;
  //  DigitalOut<B7,OUTPUT_OPEN_DRAIN_PUSH_PULL_FAST> Miso - OUTPUT_OPEN_DRAIN_PUSH_PULL_FAST;
  
  CLK->PCKENR |= ((uint8_t)CLK_Peripheral_SPI);
    
  DigitalIn<B4,INPUT_PULLUP> Cs;
  DigitalIn<B5,INPUT_PULLUP> Clk;
  DigitalIn<B6,INPUT_FLOATING> Mosi;
  DigitalOut<B7,OUTPUT_OPEN_DRAIN_PUSH_PULL_FAST> Miso;
  
  Cs.SetInputMode();
  Clk.SetInputMode();
  Mosi.SetInputMode();
  Miso.SetOutputMode();
  
  SPI_ENABLE(SPI);
  
  return SPI_OK;
}

void Spi_SlaveTransmit(uint8_t* Buf, uint8_t Len)
{
  SpiConext.TxBuf = Buf;
  SpiConext.TxLen = Len; 
  SpiConext.SPIState = SPI_SLAVE_TX;
  SPI_BYTE_OUT_8_BIT(SpiConext);  
  SPI_ENABLE_INTERRUPTS(SPI_ICR_TXIE);
}

SPIState_t Spi_GetState()
{
  return SpiConext.SPIState;
}

void Spi_SlaveReceive(uint8_t* Buf, uint8_t Len)
{
  SpiConext.RxBuf = Buf;
  SpiConext.RxLen = Len;      
  SpiConext.SPIState = SPI_SLAVE_RX;
  SPI_ENABLE_INTERRUPTS(SPI_ICR_RXIE);
}

void Spi_ISR()
{
  if( SPI->SR & SPI_SR_RXNE )
  {
    if(SpiConext.SPIState == SPI_SLAVE_TX)
    {
      SPI_BYTE_OUT_8_BIT(SpiConext);
      
      if(SpiConext.TxLen == 0)
      {             
        SpiConext.SPIState = SPI_TX_DONE;
        SPI_DISABLE_ALL_INTERRUPTS();
        if(SpiConext.XferDoneCallback) SpiConext.XferDoneCallback(SPI_SLAVE_TX_DONE);     
      }   
    } 
    else if(SpiConext.SPIState == SPI_SLAVE_RX)
    {
      SPI_BYTE_IN_8_BIT(SpiConext);
      
      if(SpiConext.RxLen == 0)
      {               
        SPI_DISABLE_ALL_INTERRUPTS();
        SpiConext.SPIState = SPI_RX_DONE;
        if(SpiConext.XferDoneCallback) SpiConext.XferDoneCallback(SPI_SLAVE_RX_DONE);     
      }   
    }
  }
}