


#include"Spi_tests.h"


//using namespace HAL;

enum 
{
  POLL_TX_16BIT,
  w25qxx_POLL_TX,
  w25qxx_POLL_RX,
  w25qxx_POLL_TX_RX,
  w25qxx_POLL_TXN,
  INTR_TX_16BIT,
  w25qxx_INTR_TX,
  w25qxx_INTR_RX,
  w25qxx_INTR_TX_RX,
  w25qxx_INTR_TXN,
  w25qxx_INTR_TXN_Q,  
  DMA_TX_16BIT,
  w25qxx_DMA_TX,
  w25qxx_DMA_RX,
  w25qxx_DMA_TX_RX,
  w25qxx_DMA_TXN,
  w25qxx_DMA_TXN_Q,

  SLAVE_DMA,
  SLAVE_INTR_INIT,
  SLAVE_INTR_TX,
  SLAVE_INTR_RX,
  SLAVE_INTR_RX_TX,
  SLAVE_DMA_RX,
  SLAVE_DMA_TX,
  POLL_SLAVE_TEST
};

#define SPI_TX_SIZE 8
#define SPI_RX_SIZE 7


uint8_t pBuffer[SPI_RX_SIZE];
uint8_t SPI_TxBuf[SPI_TX_SIZE] = "Sumit 1";
uint8_t SPI_RxBuf[SPI_RX_SIZE];

void SpiCallback(SpiStatus_t Status)
{
  if(Status == SPI_SLAVE_RX_DONE )
  {
    SPI_TxBuf[SPI_TX_SIZE-2]++;
    Spi_SlaveTransmit(SPI_TxBuf,SPI_TX_SIZE-1);
  } 
  else  if(Status == SPI_SLAVE_TX_DONE )
  {
    Spi_SlaveReceive(SPI_RxBuf,SPI_RX_SIZE);
  }
}
uint32_t Pc_Count;
void Spi_Tests()
{
  uint8_t test_id = SLAVE_INTR_INIT;//w25qxx_POLL_TX;

  Spi_SlaveHwInit();
  test_id = SLAVE_INTR_RX_TX;
  
  while(1)
  {
    switch(test_id)
    { 
      
    case SLAVE_INTR_TX:
      Spi_SlaveTransmit(SPI_TxBuf,SPI_TX_SIZE-1);
      while(1)
      {
        if(Spi_GetState() == SPI_TX_DONE)
        {
          SPI_TxBuf[SPI_TX_SIZE-2]++;
          Spi_SlaveTransmit(SPI_TxBuf,SPI_TX_SIZE-1);
        }
        Pc_Count++;
      }
      break;  
      
    case SLAVE_INTR_RX:
      Spi_SlaveReceive(SPI_RxBuf,SPI_RX_SIZE);
      while(1)
      {
        if(Spi_GetState() == SPI_RX_DONE)
        {
          Spi_SlaveReceive(SPI_RxBuf,SPI_RX_SIZE);
        }
        Pc_Count++;
      }
      break;
      
      case SLAVE_INTR_RX_TX:
      Spi_SlaveReceive(SPI_RxBuf,SPI_RX_SIZE);
      while(1)
      {
        if(Spi_GetState() == SPI_RX_DONE)
        {
          SPI_TxBuf[SPI_TX_SIZE-2]++;
          Spi_SlaveTransmit(SPI_TxBuf,SPI_TX_SIZE-1);
        }
        else if(Spi_GetState() == SPI_TX_DONE)
        {
          Spi_SlaveReceive(SPI_RxBuf,SPI_RX_SIZE);
        }
        Pc_Count++;
      }
      break;
      
    default: break;
    }
    delay_ms(100);
  }
  
}