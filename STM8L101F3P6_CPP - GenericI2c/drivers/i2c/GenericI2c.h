


#ifndef GI2c_h
#define GI2c_h

#include"system.h"
#include"DigitalOut.h"
#include"QueueCpp.h"


#define I2C_DATA_REG_ I2C->DR

#define ENABLE_ACK() I2C->CR2 |= I2C_CR2_ACK

#define DISABLE_ACK() I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK)

#define START() I2C->CR2 |= I2C_CR2_START

#define STOP() I2C->CR2 |= I2C_CR2_STOP

#define BYTE_IN() 

#define BYTE_OUT()

#define START_CONDITION_GENERATED() (I2C->SR1 & I2C_SR1_SB)

#define SLAVE_ADDRESS_SENT() (I2C->SR1 & I2C_SR1_ADDR)

#define BYTE_SENT() (I2C->SR1 & I2C_SR1_TXE) || (I2C->SR1 & I2C_SR1_BTF)

#define BYTE_RECEIVED() (I2C->SR1 & I2C_SR1_RXNE) || (I2C->SR1 & I2C_SR1_BTF)

#define STOP_DETECTED() (I2C->SR1 & I2C_SR1_STOPF)

#define ADDRESS_MATCHED() (I2C->SR1 & I2C_SR1_ADDR)

#define ADDRESS10_MATCHED() (I2C->SR1 & I2C_SR1_ADD10)

#define ACKNOWLEDGE_FAILURE() (I2C->SR2 & I2C_SR2_AF)

#define ARBITRATION_LOST() (I2C->SR2 & I2C_SR2_AF)

#define START_CONDITION_GENERATED_HANDLER()

#define SLAVE_ADDRESS_SENT_HANDLER()

#define BYTE_RECEIVED_HANDLER()

#define BYTE_SENT_HANDLER()

#define STOP_DETECTED_HANDLER()

#define ADDRESS10_MATCHED_HANDLER()

#define ADDRESS_MATCHED_HANDLER()

#define ACKNOWLEDGE_FAILURE_HANDLER()

typedef enum 
{
  I2C_OK,
  I2C_INVALID_PARAMS,
  //I2C_BUSY,
  I2C_BUSY_TIMEOUT,
  I2C_START_TIMEOUT,
  I2C_ADDR_TIMEOUT,
  I2C_TX_TIMEOUT,
  I2C_RX_TIMEOUT,
  I2C_STOP_TIMEOUT,
  I2C_ACK_FAIL,
  I2C_ARB_LOST,
  I2C_BUS_ERROR,
  I2C_DATA_OVR,  
  I2C_XFER_DONE,
}I2CStatus_t;


typedef void(*I2CSlaveRxDoneCallback_t)(uint8_t* SlaveRxBuffer, uint8_t RxLen);

typedef void(*I2CslaveTxDoneCallback_t)(void);

I2CStatus_t I2cHwInit();

I2CStatus_t I2cSlaveInit(uint8_t OwnAddress, I2CslaveTxDoneCallback_t I2CslaveTxDoneCallback, I2CSlaveRxDoneCallback_t I2CSlaveRxDoneCallback);

void I2c_ISR(void);














#endif //GI2c_h