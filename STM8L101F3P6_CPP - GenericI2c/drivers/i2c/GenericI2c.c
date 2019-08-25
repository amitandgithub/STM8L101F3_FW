




#include"GenericI2c.h"

I2CStatus_t I2cHwInit()
{
  return I2C_OK;
}


void I2c_ISR(void)
{  
  if(START_CONDITION_GENERATED())
  {
    START_CONDITION_GENERATED_HANDLER();
  }  
  else if(SLAVE_ADDRESS_SENT())
  {
    SLAVE_ADDRESS_SENT_HANDLER();
  }
  else if(BYTE_RECEIVED())
  {
    BYTE_RECEIVED_HANDLER();
  }  
  else if(BYTE_SENT())
  {
    BYTE_SENT_HANDLER();
  }  
  else if(STOP_DETECTED())
  {
    STOP_DETECTED_HANDLER();
  }  
  else if(ADDRESS_MATCHED())
  {
    ADDRESS10_MATCHED_HANDLER();
  }  
  else if(ADDRESS_MATCHED())
  {
    ADDRESS_MATCHED_HANDLER();
  }  
  else if(ACKNOWLEDGE_FAILURE())
  {
    ACKNOWLEDGE_FAILURE_HANDLER();
  }
  
}