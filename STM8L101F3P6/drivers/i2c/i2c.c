/******************
** FILE: i2c.c
**
** DESCRIPTION:
**  I2c peripheral implementation
**
** CREATED: 7/29/2019, by Amit Chaudhary
******************/
#include"i2c.h"

#if I2C_DEBUG 
I2CLogs_t I2CStates[I2C_LOG_STATES_SIZE];
#endif

void I2c_HwInit()
{ 
  I2cClockEnable();
  I2C_Init(100000,0x08,0,0,0);  
  I2cPinsInit(); 
  I2C_Cmd(ENABLE);
}

void I2cClockEnable()
{
  /* Enable the I2c Clock */
  CLK->PCKENR |= ((uint8_t)CLK_Peripheral_I2C);
}

void I2cClockDisable()
{
  /* Disable the I2c Clock */
  CLK->PCKENR &= (uint8_t)(~(uint8_t)CLK_Peripheral_I2C);
}
/*  
SCL = C1 - 19
SDA = C0 - 18
*/
void I2cPinsInit()
{
  GpioSetOutputOpenDrainFast(C0);
  GpioSetOutputOpenDrainFast(C1);  
}

void I2cScanBus(uint8_t* pFoundDevices, uint8_t size)
{
  uint8_t slave, i=0;
  
  for(slave = 0; slave < 255; slave++)
  {
    if(SendSlaveAddress(slave) == I2C_OK)
    {
      pFoundDevices[i++] = slave;
      // printf("Slave Dectected at Address = 0x%x \n",slave);
    }
    else
    {
      ClearAF();
      //GenerateStop();
    }
    GenerateStop();
    if(i == size) i=0;
  }
}

I2CStatus_t SendSlaveAddress(uint8_t SlaveAddress)
{
  /* Wait while BUSY flag is set */
  if (WaitOnFlag(&I2C->SR3, I2C_SR3_BUSY, I2C_SR3_BUSY, I2C_TIMEOUT))
  {
    I2C_LOG_STATES(I2C_LOG_BUSY_TIMEOUT);
    return I2C_BUSY_TIMEOUT; 
  }
  
  /* Disable Pos */
  DisablePOS();
  
  /* Enable Acknowledge, Generate Start */
  I2C->CR2 |= I2C_CR2_START | I2C_CR2_ACK;
  
  /* Wait while SB flag is 0 */
  if (WaitOnFlag(&I2C->SR1, I2C_SR1_SB, 0, I2C_TIMEOUT))
  {         
    I2C_LOG_STATES(I2C_LOG_START_TIMEOUT); 
    return I2C_START_TIMEOUT;                 
  } 
  
  I2C_LOG_EVENTS(I2C_LOG_START);
  
  I2C->DR = SlaveAddress & I2C_DIR_WRITE;
  
  /* Wait while ADDR flag is 0 */
  if(WaitOnFlag(&I2C->SR1, I2C_SR1_ADDR, 0, I2C_TIMEOUT))
  {
    /* if there is ack fail, clear the AF flag */
    if(I2C->SR2 & I2C_SR2_AF)
    {
      ClearAF();
      
      /* Generate Stop */
      GenerateStop();
      
      return I2C_ACK_FAIL;
    }
    
    I2C_LOG_STATES(I2C_LOG_ADDR_TIMEOUT);
    return I2C_ADDR_TIMEOUT;                
  }
  I2C_LOG_EVENTS(I2C_LOG_ADDR);
  return I2C_OK;
}
I2CStatus_t I2cTxPoll(uint8_t SlaveAddress,uint8_t* TxBuf, uint8_t TxLen, uint8_t RepeatedStart) // 104 bytes
{
  if(!TxBuf) return I2C_INVALID_PARAMS;
  
  /* Send Slave address */
  if(SendSlaveAddress(SlaveAddress & I2C_DIR_WRITE) != I2C_OK)
    return I2C_ADDR_TIMEOUT;
  
  /* Clear ADDR flag */
  ClearADDR();
  
  while(TxLen)
  {    
    /* Write data to DR */
    I2C->DR = *TxBuf++;                
    TxLen--; 
    
    /* Wait until TXE flag is set */
    if (WaitOnFlag(&I2C->SR1, I2C_SR1_TXE, 0, I2C_TIMEOUT))
    {          
      I2C_LOG_STATES(I2C_LOG_TXE_TIMEOUT);
      return I2C_TXE_TIMEOUT;                
    }  
    
    I2C_LOG_EVENTS(I2C_LOG_TXE);    
    
    if(I2C->SR1 & I2C_SR1_BTF)
    {
      I2C_LOG_EVENTS(I2C_LOG_BTF);                    
    }                               
  }             
  /* Generate Stop */
  if(!RepeatedStart)
    GenerateStop();
  
  I2C_LOG_EVENTS(I2C_LOG_STOP);
  
  return I2C_OK;
  
}

I2CStatus_t I2cRxPoll(uint8_t SlaveAddress,uint8_t* RxBuf, uint8_t RxLen) // 309 bytes
{
  if(!RxBuf) return I2C_INVALID_PARAMS;
  
  /* Send Slave address */
  if(SendSlaveAddress(SlaveAddress | I2C_DIR_READ) != I2C_OK)
    return I2C_ADDR_TIMEOUT;
  
  if(RxLen == 1)
  {
    /* Disable Acknowledge */
    DisableACK();
    
    /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
    software sequence must complete before the current byte end of transfer */
    __disable_interrupt();
    
    /* Clear ADDR flag */
    ClearADDR();
    
    /* Generate Stop */
    GenerateStop();
    
    /* Re-enable IRQs */
    __enable_interrupt();   
    
    I2C_LOG_STATES(I2C_LOG_RX_1);
  }
  else if(RxLen == 2)
  {
    /* Enable Pos */
    EnablePOS();
    
    /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
    software sequence must complete before the current byte end of transfer */
    __disable_interrupt();
    
    /* Clear ADDR flag */
    ClearADDR();
    
    /* Disable Acknowledge */
    DisableACK();
    
    /* Re-enable IRQs */
    __enable_interrupt(); 
    
    I2C_LOG_STATES(I2C_LOG_RX_2);
  }
  else
  {
    /* Enable Acknowledge */
    EnableACK();
    
    /* Clear ADDR flag */
    ClearADDR();
    
    I2C_LOG_STATES(I2C_LOG_RX_GT_2);
  }
  
  while(RxLen > 0U)
  {
    if(RxLen <= 3U)
    {
      /* One byte */
      if(RxLen == 1U)
      {
        /* Wait until RXNE flag is set */
        if(WaitOnFlag(&I2C->SR1, I2C_SR1_RXNE, 0, I2C_TIMEOUT))
        {          
          I2C_LOG_STATES(I2C_LOG_RXNE_TIMEOUT);
          return I2C_RXNE_TIMEOUT;                
        } 
        
        I2C_LOG_EVENTS(I2C_LOG_RXNE); 
        
        /* Read data from DR */
        (*RxBuf) = I2C->DR;
        RxLen--;
        I2C_LOG_STATES(I2C_LOG_RX_1_DONE);
      }
      /* Two bytes */
      else if(RxLen == 2U)
      {
        /* Wait until BTF flag is set */
        if(WaitOnFlag(&I2C->SR1, I2C_SR1_BTF, 0, I2C_TIMEOUT))
        {         
          I2C_LOG_STATES(I2C_LOG_BTF_TIMEOUT);
          return I2C_BTF_TIMEOUT;                
        }
        
        /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
        software sequence must complete before the current byte end of transfer */
        __disable_interrupt();
        
        /* Generate Stop */
        GenerateStop();
        
        /* Read data from DR */
        (*RxBuf++)= I2C->DR;
        RxLen--;
        
        /* Re-enable IRQs */
        __enable_interrupt();
        
        /* Read data from DR */
        (*RxBuf++) = I2C->DR;
        RxLen--;
        
        I2C_LOG_STATES(I2C_LOG_RX_2_DONE);
      }
      /* 3 Last bytes */
      else
      {
        /* Wait until BTF flag is set */
        if(WaitOnFlag(&I2C->SR1, I2C_SR1_BTF, 0, I2C_TIMEOUT))
        {          
          I2C_LOG_STATES(I2C_LOG_BTF_TIMEOUT);
          return I2C_BTF_TIMEOUT;               
        } 
        
        /* Disable Acknowledge */
        DisableACK();
        
        /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
        software sequence must complete before the current byte end of transfer */
        __disable_interrupt();
        
        /* Read data from DR */
        (*RxBuf++) = I2C->DR;
        RxLen--;
        
        /* Wait until BTF flag is set */
        if(WaitOnFlag(&I2C->SR1, I2C_SR1_BTF, 0, I2C_TIMEOUT))
        {         
          I2C_LOG_STATES(I2C_LOG_BTF_TIMEOUT);
          return I2C_BTF_TIMEOUT;                
        }
        
        /* Generate Stop */
        GenerateStop();
        
        /* Read data from DR */
        (*RxBuf++) = I2C->DR;
        RxLen--;
        
        /* Re-enable IRQs */
        __enable_interrupt(); 
        
        /* Read data from DR */
        (*RxBuf++) = I2C->DR;
        RxLen--;
        
        I2C_LOG_STATES(I2C_LOG_RX_3_DONE);
      }
    }
    else
    {
      /* Wait until RXNE flag is set */
      if(WaitOnFlag(&I2C->SR1, I2C_SR1_RXNE, 0, I2C_TIMEOUT))
      {          
        I2C_LOG_STATES(I2C_LOG_RXNE_TIMEOUT);
        return I2C_RXNE_TIMEOUT;                
      } 
      
      I2C_LOG_EVENTS(I2C_LOG_RXNE);
      
      /* Read data from DR */
      (*RxBuf++) = I2C->DR;
      RxLen--;
      
      if(WaitOnFlag(&I2C->SR1, I2C_SR1_BTF, 0, I2C_TIMEOUT))
      {
        /* Read data from DR */
        (*RxBuf++) = I2C->DR;
        RxLen--;
        I2C_LOG_EVENTS(I2C_LOG_BTF);
      }
    }
  }       
  
  I2C_LOG_STATES(I2C_LOG_RX_DONE);
  return I2C_OK;
}

uint8_t WaitOnFlag(volatile uint8_t* reg, uint8_t bitmask, uint8_t status, uint16_t timeout) // 35(0x25)bytes , 62(0x3e)
{
  while( ((*reg & bitmask) == status) && timeout-- );    // 35(0x25) bytes 
  return ((*reg & bitmask) == status);
}

void I2cTests(void)
{
  static uint8_t FoundDevices[10];
  I2cScanBus(FoundDevices, 10);  
}



