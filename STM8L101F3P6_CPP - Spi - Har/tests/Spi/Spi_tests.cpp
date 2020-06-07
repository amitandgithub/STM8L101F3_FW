


#include"Spi_tests.h"


using namespace HAL;

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
  SLAVE_INTR,
  SLAVE_DMA,
  SLAVE_INTR_RX,
  SLAVE_INTR_TX,
  SLAVE_DMA_RX,
  SLAVE_DMA_TX,
  POLL_SLAVE_TEST
};

#define SPI_RX_SIZE 256

DigitalOut<B3,OUTPUT_OPEN_DRAIN_PUSH_PULL> Cs;

uint8_t pBuffer[SPI_RX_SIZE] = "AmitC";
uint8_t SPI_RxBuf[SPI_RX_SIZE];
Spi spi;

void SpiCallback(Spi::SpiStatus_t Status)
{
  static uint32_t SpiTxnCount;
  if(Status == Spi::SPI_SLAVE_RX_DONE )
  {
    spi.SrartListeningRXIntr8bit(SPI_RxBuf,SPI_RX_SIZE);
    memset(SPI_RxBuf,0,SPI_RX_SIZE);
  }  
  SpiTxnCount++;
}
uint32_t Pc_Count;
void Spi_Master_Tests()
{
  uint8_t test_id = SLAVE_INTR;//w25qxx_POLL_TX;
  Spi::Transaction_t Transaction;
  
  
  
  Cs.HwInit();
  Cs.High();
  spi.HwInit(false);
  
  while(1)
  {
    switch(test_id)
    { 
    case w25qxx_POLL_TX:  
      Cs.Low();
      spi.Tx('A');
      spi.Tx('m');
      spi.Tx('i');
      spi.Tx('t');
      Cs.High();
      //break;
    case w25qxx_POLL_TXN:      
      Transaction.TxBuf = pBuffer;
      Transaction.TxLen = 5;
      Transaction.RxBuf = 0;
      Transaction.RxLen = 0;
      Transaction.ChipSelectPort = PORTB;
      Transaction.ChipSelectPin  = (PIN_t)3;
      Transaction.XferDoneCallback = SpiCallback;      
      Cs.Low();
      spi.XferPoll(&Transaction);
      Cs.High();
    case w25qxx_INTR_TX:         
      Cs.Low();
      spi.XferIntr(&Transaction);
      while(spi.GetState() != Spi::SPI_READY);
      Cs.High();
    case SLAVE_INTR:    
      Transaction.TxBuf = SPI_RxBuf;
      Transaction.TxLen = 5;
      Transaction.RxBuf = SPI_RxBuf;
      Transaction.RxLen = 5;
      Transaction.XferDoneCallback = SpiCallback;
      spi.HwInit(true);
      spi.CheckAndLoadTxn(&Transaction);
      spi.SrartListeningRXIntr8bit(SPI_RxBuf,SPI_RX_SIZE);
      while(1) Pc_Count++;
    default: break;
    }
    delay_ms(100);
  }
  
}