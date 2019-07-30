/******************
** FILE: i2c.h
**
** DESCRIPTION:
**  i2c implementation
**
** CREATED: 7/29/2019, by Amit Chaudhary
******************/
#ifndef i2c_h
#define i2c_h

#include"system.h"

#define I2C_DEBUG 1

#define FORCED_INLINE 1
#define I2C_TIMEOUT 5000u
#define DGB_PRINT(x) 


#define I2C_DIR_READ  0x01u
#define I2C_DIR_WRITE 0xFEu

typedef enum 
{
  I2C_OK,
  I2C_BUSY,
  I2C_BUSY_TIMEOUT,
  I2C_START_TIMEOUT,
  I2C_ADDR_TIMEOUT,
  I2C_BTF_TIMEOUT,
  I2C_RXNE_TIMEOUT,
  I2C_TXE_TIMEOUT,
  I2C_STOP_TIMEOUT,
  I2C_ACK_FAIL,
  I2C_ARB_LOST,
  I2C_INTR_PENDING,
  I2C_BUS_ERROR,
  I2C_DATA_OVR,
  I2C_INVALID_PARAMS,
  I2C_XFER_DONE,
  I2C_TXN_POSTED,
  I2C_TXN_QUEUE_ERROR,
}I2CStatus_t;

/* I2c APIs */
void I2c_HwInit();
void I2cClockEnable();
void I2cClockDisable();
I2CStatus_t I2cTxPoll(uint8_t SlaveAddress,uint8_t* TxBuf, uint8_t TxLen);        
I2CStatus_t I2cRxPoll(uint8_t SlaveAddress,uint8_t* RxBuf, uint8_t RxLen);
I2CStatus_t XferPoll(uint8_t SlaveAddress,uint8_t* TxBuf, uint8_t TxLen, uint8_t* RxBuf, uint8_t RxLen,uint8_t RepeatedStart);
I2CStatus_t SendSlaveAddress(uint8_t SlaveAddress);
void I2cPinsInit();
void I2cScanBus(uint8_t* pFoundDevices, uint8_t size);
void I2cTests(void);

/* I2c local functions */

//static inline 
uint8_t WaitOnFlag(volatile uint8_t* reg, uint8_t bitmask, uint8_t status, uint16_t timeout);

#pragma inline=forced
void GenerateStart()
{
  /* Generate a START condition */
  I2C->CR2 |= I2C_CR2_START;
}
#pragma inline=forced
void GenerateStop()
{
  /* Generate a STOP condition */
  I2C->CR2 |= I2C_CR2_STOP;
}
#pragma inline=forced
void EnableACK()
{
  /* Enable the acknowledgement */
  I2C->CR2 |= I2C_CR2_ACK;
}
#pragma inline=forced
void DisableACK()
{
  /* Disable the acknowledgement */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
}
#pragma inline=forced
void EnablePOS()
{
  /* Enable POS*/
  I2C->CR2 |= (uint8_t)I2C_CR2_POS; 
}
#pragma inline=forced
void DisablePOS()
{
  /* Disable POS */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_POS);
}
#pragma inline=forced
void EnableI2c()
{
  /* Enable I2C peripheral */
  I2C->CR1 |= I2C_CR1_PE;
}
#pragma inline=forced
void DisableI2c()
{
  /* Disable I2C peripheral */
  I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);
}

#pragma inline=forced
void Softreset()
{
  /* Reset the Peripheral */
  I2C->CR2 |= I2C_CR2_SWRST;
  
  /* Release the Reset */
  I2C->CR2 &= (uint8_t)(~I2C_CR2_SWRST);
}

#pragma inline=forced
void TxData(uint8_t* pdata, uint8_t len)
{
  I2C->DR = *pdata++;
  len--;
}

#pragma inline=forced
void ClearADDR()
{
  uint8_t dummy;
  dummy = I2C->SR1;
  dummy = I2C->SR3;
  (void) dummy;
}

#pragma inline=forced
void ClearAF()
{
  I2C->SR2 &= (uint8_t)(~I2C_SR2_AF);
}


#define DBG_LOG_CREATE_ID(__MODULE_ID,__X) __X

typedef enum
{														  
  I2C_LOG_STOPF_FLAG                           	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,1),
  I2C_LOG_STOPF_NOT_CLEARED                    	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,2),
  I2C_LOG_START_MASTER_TX                      	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,3),
  I2C_LOG_START_MASTER_RX                      	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,4),
  I2C_LOG_START_MASTER_TXRX                    	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,5),
  I2C_LOG_ADDR_INTR_MASTER_RX_SIZE_0           	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,6),
  I2C_LOG_ADDR_INTR_MASTER_RX_SIZE_1_DMA       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,7),
  I2C_LOG_ADDR_INTR_MASTER_RX_SIZE_1           	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,8),
  I2C_LOG_ADDR_INTR_MASTER_RX_SIZE_2_DMA       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,9),
  I2C_LOG_ADDR_INTR_MASTER_RX_SIZE_2           	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,10),
  I2C_LOG_ADDR_INTR_MASTER_RX_SIZE_OTHER       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,11),
  I2C_LOG_ADDR_INTR_MASTER_TX_SIZE_GT_0        	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,12),
  I2C_LOG_ADDR_INTR_MASTER_TX_REPEATED_START   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,13),
  I2C_LOG_ADDR_INTR_MASTER_TX_STOP             	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,14),
  I2C_LOG_TXE_GT_0                              =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,15),
  I2C_LOG_TXE_DONE                             	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,16),
  I2C_LOG_REPEATED_START                       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,17),
  I2C_LOG_BTF_MASTER_TX_GT_0                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,18),
  I2C_LOG_BTF_MASTER_TX_REPEATED_START         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,19),
  I2C_LOG_BTF_MASTER_TX_STOP                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,20),
  I2C_LOG_BTF_MASTER_RX_SIZE_3                 	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,21),
  I2C_LOG_BTF_MASTER_RX_SIZE_2_STOPED          	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,22),
  I2C_LOG_BTF_MASTER_RX_SIZE_GT_3              	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,23),
  I2C_LOG_RXNE_MASTER_SIZE_GT_3                	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,24),
  I2C_LOG_RXNE_MASTER                          	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,25),
  I2C_LOG_RXNE_MASTER_SIZE_1                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,26),
  I2C_LOG_RXNE_MASTER_SIZE_2                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,27),
  I2C_LOG_RXNE_MASTER_SIZE_2_OR_3              	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,28),
  I2C_LOG_BTF_MASTER_RXNE_LAST              	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,29),
  I2C_LOG_RXNE_MASTER_LAST                     	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,30),
  I2C_LOG_BTF_MASTER_BERR                      	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,31),
  I2C_LOG_BTF_MASTER_ACK_FAIL                  	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,32),
  I2C_LOG_BTF_MASTER_ARB_LOST                  	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,33),
  I2C_LOG_SB_MASTER_TX                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,34),
  I2C_LOG_SB_MASTER_RX                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,35),
  I2C_LOG_SB_MASTER_RX_2                       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,36),
  I2C_LOG_SB_MASTER_RX_REPEATED_START          	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,37),
  I2C_LOG_STOP_MASTER_RX_WITHOUT_REPEATED_START	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,38),
  I2C_LOG_STOP_XFER_DONE                       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,39),
  I2C_LOG_BTF_MASTER_DATA_OVR                  	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,40),
  I2C_LOG_START_SLAVE_RX                       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,41),
  I2C_LOG_BTF_SLAVE_RX                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,42),
  I2C_LOG_RXNE_SLAVE_RX                        	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,43),
  I2C_LOG_BTF_SLAVE_RX_QUEUED                  	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,44),
  I2C_LOG_BTF_SLAVE_RX_QUEUE_FULL              	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,45),
  I2C_LOG_RXNE_SLAVE_RX_QUEUED                 	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,46),
  I2C_LOG_RXNE_SLAVE_RX_QUEUE_FULL             	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,47),
  I2C_LOG_AF_SLAVE_ACK_FAIL                    	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,48),
  I2C_LOG_TxE_SLAVE_TX                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,49),
  I2C_LOG_TxE_SLAVE_TX_QUEUE_EMPTY             	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,50),
  I2C_LOG_BTF_SLAVE_TX                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,51),
  I2C_LOG_BTF_SLAVE_TX_QUEUE_EMPTY             	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,52),
  I2C_LOG_MASTER_BTF_XFER_DONE                 	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,53),
  I2C_LOG_ADDR_XFER_DONE                       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,54),
  I2C_LOG_TXN_QUEUED                           	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,55),
  I2C_LOG_TXN_DEQUEUED                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,56),
  I2C_LOG_TXN_QUEUE_EMPTY                      	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,57),
  I2C_LOG_TXN_QUEUE_ERROR                      	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,58),
  I2C_LOG_TXN_DONE                             	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,59),
  I2C_LOG_TXN_DONE_ALL                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,60),
  I2C_LOG_DMA_TX_DONE                          	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,61),
  I2C_LOG_DMA_HALF_TX_DONE                     	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,62),
  I2C_LOG_DMA_TX_ERROR                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,63),
  I2C_LOG_ADDR_INTR_MASTER_TX_DMA              	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,64),
  I2C_LOG_ADDR_INTR_MASTER_RX_DMA              	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,65),
  I2C_LOG_BTF_MASTER_RX_DMA_STOP               	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,66),
  I2C_LOG_BTF_MASTER_TX_DMA_STOP               	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,67),
  I2C_LOG_START_MASTER_TX_DMA                  	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,68),
  I2C_LOG_START_MASTER_RX_DMA                  	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,69),
  I2C_LOG_REPEATED_START_MASTER_RX_DMA         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,70),
  I2C_LOG_DMA_HALF_RX_DONE                     	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,71),
  I2C_LOG_DMA_RX_ERROR                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,72),
  I2C_LOG_DMA_RX_DONE                          	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,73),
  I2C_LOG_ADDR_INTR_MASTER_RX_DMA_SIZE_1       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,74),
  I2C_LOG_ADDR_INTR_MASTER_RX_DMA_SIZE_2       	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,75),
  I2C_LOG_DMA_TX_BTF_TIMEOUT                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,76),
  I2C_LOG_DMA_REPEATED_START                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,77),
  I2C_LOG_DMA_STOP_GENERATED                   	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,78),
  I2C_LOG_DMA_TXN_DONE                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,79),
  I2C_LOG_SB									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,80),
  I2C_LOG_ADDR									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,81),
  I2C_LOG_BTF									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,82),
  I2C_LOG_RXNE									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,83),
  I2C_LOG_TXE									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,84),
  I2C_LOG_STOPF									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,85),
  I2C_LOG_BERR									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,86),
  I2C_LOG_ARLO									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,87),
  I2C_LOG_AF									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,88),
  I2C_LOG_OVR									=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,89),
  I2C_LOG_PECERR								=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,90),
  I2C_LOG_ADD10                                	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,91),
  I2C_LOG_START_TIMEOUT                        	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,92),
  I2C_LOG_START_DONE                            =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,93),
  I2C_LOG_ADDR_TIMEOUT                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,94),
  I2C_LOG_ADDR_SENT                             =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,95),
  I2C_LOG_TXE_TIMEOUT                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,96),
  I2C_LOG_TX_DONE                               =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,97),
  I2C_LOG_RX_DONE                               =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,98),
  I2C_LOG_RXNE_TIMEOUT                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,99),
  I2C_LOG_BTF_TIMEOUT                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,100),
  I2C_LOG_RX_1                                  =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,101),
  I2C_LOG_RX_2                                  =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,102),
  I2C_LOG_RX_GT_2                               =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,103),
  I2C_LOG_RX_1_DONE                             =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,104),
  I2C_LOG_RX_2_DONE                             =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,105),
  I2C_LOG_RX_3_DONE                             =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,106),
  I2C_LOG_START                                 =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,107),
  I2C_LOG_STOP                                  =	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,108),
  I2C_LOG_STOP_TIMEOUT                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,109),
  I2C_LOG_BUSY_TIMEOUT                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,110),/*
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,111),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,112),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,113),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,114),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,115),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,116),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,117),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,118),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,119),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,120),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,121),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,122),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,123),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,124),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,125),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,126),
  I2C_LOG_                         	=	DBG_LOG_CREATE_ID(DBG_LOG_MODULE_ID_I2C,127) */           
}I2CLogs_t;

#if I2C_DEBUG 

#define I2C_LOG_STATES_SIZE 255
#define I2C_LOG_EVENTS(x) I2cLogStates(x)
#define I2C_LOG_STATES(x) I2cLogStates(x)

#pragma inline = forced
void I2cLogStates(I2CLogs_t log)
{
  extern I2CLogs_t I2CStates[];
  static uint8_t I2CStates_Idx;
  I2CStates[I2CStates_Idx++] = log;
  if(I2CStates_Idx == I2C_LOG_STATES_SIZE )
    I2CStates_Idx = 0;
}
#else
#define I2C_LOG_EVENTS(x) 
#define I2C_LOG_STATES(x)
#endif








#endif //i2c.h
