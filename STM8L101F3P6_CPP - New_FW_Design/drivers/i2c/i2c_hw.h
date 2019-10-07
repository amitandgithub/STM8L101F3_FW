
#ifndef I2C_HW_H
#define I2C_HW_H

#include"chip_peripheral.h"


#define I2C_GENERATE_START()    I2C->CR2 |= I2C_CR2_START

#define I2C_GENERATE_STOP()     I2C->CR2 |= I2C_CR2_STOP

#define I2C_ENABLE_ACK()        I2C->CR2 |= I2C_CR2_ACK

#define I2C_DISABLE_ACK()       I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK)
  
#define I2C_ENABLE_POS()        I2C->CR2 |= (uint8_t)I2C_CR2_POS

#define I2C_DISABLE_POS()       I2C->CR2 &= (uint8_t)(~I2C_CR2_POS)

#define I2C_ENABLE()            I2C->CR1 |= I2C_CR1_PE

#define I2C_CLOCK_ENABLE()      CLK->PCKENR |= ((uint8_t)CLK_Peripheral_I2C)

#define I2C_CLOCK_DISABLE()     CLK->PCKENR &= (uint8_t)(~(uint8_t)CLK_Peripheral_I2C)

#define I2C_DISABLE()           I2C->CR1 &= (uint8_t)(~I2C_CR1_PE)

#define I2C_SOFT_RESET()        I2C->CR2 |= I2C_CR2_SWRST; I2C->CR2 &= (uint8_t)(~I2C_CR2_SWRST)
  
#define I2C_CLEAR_ADDR()        {uint8_t dummy; dummy = I2C->SR1; dummy = I2C->SR3; dummy  = dummy;}

#define I2C_CLEAR_AF()          I2C->SR2 &= (uint8_t)(~I2C_SR2_AF)

#define I2C_CLEAR_ARLO()        I2C->SR2 &= (uint8_t)(~I2C_SR2_ARLO)

#define I2C_CLEAR_BERR()        I2C->SR2 &= (uint8_t)(~I2C_SR2_BERR)

#define I2C_CLEAR_OVR()         I2C->SR1 &= (uint8_t)(~I2C_SR2_OVR)

#define I2C_CLEAR_STOPF()       {uint8_t reg;reg = I2C->SR1;I2C->CR2 = I2C->CR2;reg = reg;}

#define I2C_ENABLE_INT_BUF()    I2C->ITR |= I2C_ITR_ITBUFEN

#define I2C_DISABLE_INT_BUF()   I2C->ITR &= (uint8_t)~I2C_ITR_ITBUFEN

#define I2C_ENABLE_INT_EVT_BUF_ERR()    I2C->ITR = I2C_ITR_ITBUFEN | I2C_ITR_ITEVTEN | I2C_ITR_ITERREN

#define I2C_DISABLE_INT_EVT_BUF_ERR()   I2C->ITR &= (uint8_t)~(I2C_ITR_ITBUFEN | I2C_ITR_ITEVTEN | I2C_ITR_ITERREN)

#define I2C_SET_STOPF(FLAG) I2C->CR2 |= FLAG

#define I2C_REG_SR1 I2C->SR1

#define I2C_REG_SR2 I2C->SR2

#define I2C_REG_SR3 I2C->SR3

#define I2C_EVENT_SB(REG)  REG & I2C_SR1_SB

#define I2C_EVENT_ADDR(REG)  REG & I2C_SR1_ADDR

#define I2C_EVENT_RXNE(REG)  REG & I2C_SR1_RXNE

#define I2C_EVENT_BTF(REG)  REG & I2C_SR1_BTF

#define I2C_EVENT_TXE(REG)  REG & I2C_SR1_TXE

#define I2C_EVENT_STOPF(REG)  REG & I2C_SR1_STOPF

#define I2C_EVENT_ADD10(REG)  REG & I2C_SR1_ADD10

#define I2C_EVENT_AF(REG)  REG & I2C_SR2_AF

#define I2C_ENABLE_ACK_AND_START() I2C->CR2 |= I2C_CR2_START | I2C_CR2_ACK


#define WAIT_WHILE_ADDR_IS(TIMEOUT) WaitOnFlag(&I2C->SR1, I2C_SR1_ADDR, 0, TIMEOUT)

#define WAIT_FOR_SB_FLAG_TO_SET(TIMEOUT) WaitOnFlag(&I2C->SR1, I2C_SR1_SB, 0, TIMEOUT)

#define WAIT_FOR_TXE_FLAG_TO_SET(TIMEOUT) WaitOnFlag(&I2C->SR1, I2C_SR1_TXE, 0, TIMEOUT)

#define WAIT_FOR_RXNE_FLAG_TO_SET(TIMEOUT) WaitOnFlag(&I2C->SR1, I2C_SR1_RXNE, 0, TIMEOUT)

#define WAIT_FOR_BTF_FLAG_TO_SET(TIMEOUT) WaitOnFlag(&I2C->SR1, I2C_SR1_BTF, 0, TIMEOUT)

#define WAIT_FOR_STOP_FLAG_TO_CLEAR(TIMEOUT) WaitOnFlag(&I2C->CR2, I2C_CR2_STOP, I2C_CR2_STOP, TIMEOUT)

#define WAIT_FOR_BUSY_FLAG_TO_CLEAR(TIMEOUT) WaitOnFlag(&I2C->SR3, I2C_SR3_BUSY, I2C_SR3_BUSY, TIMEOUT)





#endif //I2C_HW_H