/******************
** FILE: i2c_tests.c
**
** DESCRIPTION:
**  I2c Tests
**
** CREATED: 7/31/2019, by Amit Chaudhary
******************/
#include "i2c_tests.h"
#include <stdio.h>
#include <string.h>

I2CStatus_t Status;
uint8_t RepeatedStart = 0;
uint8_t SlaveAddress = 0x0010;
uint8_t TxBuf[TX_BUF_SIZE];
uint8_t RxBuf[RX_BUF_SIZE];
uint8_t TxLen,RxLen;


void I2c_Poll_Tests()
{
  uint8_t I2c_test_id = 0;
  
  I2c_HwInit();
  
  SlaveAddress = 0x68<<1;
  I2c_test_id = I2C_POLL_TX_1_RX_1;
  TxBuf[0] = 0x00;
  TxBuf[1] = 0x00;
  I2cTxPoll(SlaveAddress,TxBuf,2,0);       
  
  TxBuf[0] = 8;
  
  for(uint8_t i = 1; i<70; i++) TxBuf[i] = i;
  
  while(1)
  {
    switch(I2c_test_id)
    {            
    case I2C_POLL_TX_1_RX_1:
      TxLen = RxLen = 1;
      I2cTxPoll(SlaveAddress,TxBuf,TxLen+1,0);
      I2cTxPoll(SlaveAddress,TxBuf,1,RepeatedStart);
      I2cRxPoll(SlaveAddress,RxBuf,RxLen); 
      Test_Condition(!(memcmp( (const void*) &TxBuf[1],(const void*) RxBuf, TxLen )), STR("I2C_POLL_TX_1_RX_1 = Pass"), STR("I2C_POLL_TX_1_RX_1 = Fail"));
      I2c_test_id = I2C_POLL_TX_1_RX_2;
      break;    
    case I2C_POLL_TX_1_RX_2:
      TxLen = 1;
      RxLen = 2;
      I2cTxPoll(SlaveAddress,TxBuf,TxLen+1,0);
      I2cTxPoll(SlaveAddress,TxBuf,1,RepeatedStart);
      I2cRxPoll(SlaveAddress,RxBuf,RxLen);
      Test_Condition(!(memcmp( (const void*) &TxBuf[1],(const void*) RxBuf, TxLen )), STR("I2C_POLL_TX_1_RX_2 = Pass"), STR("I2C_POLL_TX_1_RX_2 = Fail"));
      I2c_test_id = I2C_POLL_TX_1_RX_3;
      break; 
    case I2C_POLL_TX_1_RX_3:
      TxLen = 1;
      RxLen = 3;
      I2cTxPoll(SlaveAddress,TxBuf,TxLen+1,0);
      I2cTxPoll(SlaveAddress,TxBuf,1,RepeatedStart);
      I2cRxPoll(SlaveAddress,RxBuf,RxLen);
      Test_Condition(!(memcmp( (const void*) &TxBuf[1],(const void*) RxBuf, TxLen )), STR("I2C_POLL_TX_1_RX_3 = Pass"), STR("I2C_POLL_TX_1_RX_3 = Fail"));
      I2c_test_id = I2C_POLL_TX_2_RX_2;
      break; 
    case I2C_POLL_TX_2_RX_2:  
      TxLen = RxLen = 2;
      I2cTxPoll(SlaveAddress,TxBuf,TxLen+1,0);
      I2cTxPoll(SlaveAddress,TxBuf,1,RepeatedStart);
      I2cRxPoll(SlaveAddress,RxBuf,RxLen); 
      Test_Condition(!(memcmp( (const void*) &TxBuf[1],(const void*) RxBuf, TxLen )), STR("I2C_POLL_TX_2_RX_2 = Pass"), STR("I2C_POLL_TX_2_RX_2 = Fail"));
      I2c_test_id = I2C_POLL_TX_3_RX_3;
      break;  
      
    case I2C_POLL_TX_3_RX_3:  
      TxLen = RxLen = 3;
      I2cTxPoll(SlaveAddress,TxBuf,TxLen+1,0);
      I2cTxPoll(SlaveAddress,TxBuf,1,RepeatedStart);
      I2cRxPoll(SlaveAddress,RxBuf,RxLen);  
      Test_Condition( !(memcmp( (const void*) &TxBuf[1],(const void*) RxBuf, TxLen )), STR("I2C_POLL_TX_3_RX_3 = Pass"), STR("I2C_POLL_TX_3_RX_3 = Fail"));
      I2c_test_id = I2C_INT_POLL_40_RX_40;
      break;
      
    case I2C_INT_POLL_40_RX_40: 
      TxLen = RxLen = 40;           
      I2cTxPoll(SlaveAddress,TxBuf,TxLen+1,0);
      I2cTxPoll(SlaveAddress,TxBuf,1,RepeatedStart);
      I2cRxPoll(SlaveAddress,RxBuf,RxLen);            
      Test_Condition( !(memcmp( (const void*) &TxBuf[1],(const void*) RxBuf, TxLen )), STR("I2C_INT_POLL_40_RX_40 = Pass"), STR("I2C_INT_POLL_40_RX_40 = Fail"));
      
      if(RepeatedStart == 0)
      {
        I2c_test_id = I2C_POLL_TX_1_RX_1;
        RepeatedStart = 1;	
        //printf("\n\nRe-Testing test cases with repeated start \n\n");
      }
      else
      {
        return;
      }
      break;
      
    default: break;
    }
    
    MemSet(RxBuf,0,RX_BUF_SIZE);
    //LL_mDelay(50);
  }
}


uint8_t Test_Condition(uint8_t condition, char* PassStr, char* FailStr)
{
  if(condition)
  {
    //printf(PassStr);
    // printf("\n");
    return 0;
  }
  else
  {
    // printf(FailStr);
    // printf("\n");
    return 1;
  }   
  
}

void MemSet(uint8_t* mem, uint8_t data, uint8_t size)
{
  while(size--) *mem++ = data;
}