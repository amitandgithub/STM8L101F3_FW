/******************
** CLASS: optional_bytes
**
** DESCRIPTION:
**  optional_bytes functionality
**
** CREATED: 30 Jan 2021, by Amit Chaudhary
**
** FILE: optional_bytes.h
**
******************/
#ifndef optional_bytes_h
#define optional_bytes_h

#include"system.h"
#include"eeprom.h"


struct opt
{  
  static uint8_t Read(uint16_t Reg)
  {
    return *(reinterpret_cast<uint8_t*>(Reg));
  }
  
  static bool Write(uint16_t Reg, uint8_t val)
  {    
    eeprom_Unlock();
    
    if(eeprom_IsReady(250))
    {      
      FLASH->CR2  = 0X80;
      FLASH->NCR2 = 0X7F;
      
      *(reinterpret_cast<uint8_t*>(Reg)) = val;
      *(reinterpret_cast<uint8_t*>(Reg+1)) = (uint8_t)~val;
      
      system_Reset();
      
      return true;
    }
    
    return false;
  }
  
  static bool Set(uint16_t Reg, uint8_t val)
  {
    uint8_t temp;
    temp =  Read(Reg);
    
    // If already set then don't set it again
    if(temp & val)
    {
      return true;
    }
    return Write(Reg, temp | val);
  }
  
  static bool Clear(uint16_t Reg, uint8_t val)
  {
    uint8_t temp;
    temp =  Read(Reg);
    
    // If already cleared then don't clear it again
    if(temp & val)
    {
      return Write(Reg, temp & (uint8_t)~val);
    }    
    return true;
  }
  
  static void EnableRemap(uint8_t Remap)
  {
    Set(0x4803,Remap);
  }
  
  static void DisableRemap(uint8_t Remap)
  {
    Clear(0x4803,Remap);
  }  
};

#endif // optional_bytes_h