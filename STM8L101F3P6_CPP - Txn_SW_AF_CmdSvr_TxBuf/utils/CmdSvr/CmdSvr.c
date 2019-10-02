


#include "CmdSvr.h"

#include"I2C_Commands.h"

static i2c I2CDevIntr;
static i2c::SlaveTxn_t I2C_SlaveTxn;

extern uint8_t I2c_Cmd_response[15];
extern uint8_t I2c_Cmd_request[15];

Cmd_t myI2C_CMD = {(CmdHdr_t*)I2c_Cmd_request,(RspHdr_t*)I2c_Cmd_response};

static const CmdHandler CmdTable[MODULE_ID_MAX] = 
{       
  I2C_CmdHandler1,                                        
};



uint8_t* CmdSvr_SwitchBuf(uint8_t* Buffer)
{  
  return Buffer;
}

CmdStatus_t CmdSvr_GetStatus()
{
  return (CmdStatus_t)I2C_SlaveTxn.TxBuf[0];
}


CmdStatus_t Cmdsvr_GetCmd(Cmd_t *pCmd)
{
  return CMD_STATUS_OK;  
}

CmdStatus_t Cmdsvr_AuthenticateCmd(Cmd_t *pCmd)
{
  return CMD_STATUS_OK; 
}

CmdStatus_t Cmdsvr_DispatchCmd(Cmd_t *pCmd)
{
  if((pCmd == 0) || (pCmd->Request->ModuleID >= MODULE_ID_MAX))
    return CMD_STATUS_INVALID_PARAMS;
  return CmdTable[pCmd->Request->ModuleID](pCmd);
}

CmdStatus_t Cmdsvr_DispatchResponse(Cmd_t *pCmd)
{
  if(pCmd->Response)
  {
    ((RspHdr_t*)pCmd->Response)->Status = CMD_STATUS_PROCESSING_DONE; 
    I2C_SlaveTxn.TxLen = pCmd->Response->Len + sizeof(RspHdr_t) + 1; // 1 for CRC  
  }
  else
  {      
    I2C_SlaveTxn.TxLen = 1;
    ((RspHdr_t*)pCmd->Response)->Status = CMD_STATUS_READY;
  }
  I2C_SlaveTxn.RxIndex = 0;
  I2C_SlaveTxn.TxIndex = 0;
  delay_ms(100);  
  return CMD_STATUS_OK;
}

CmdStatus_t Cmdsvr_Init()
{
  I2CDevIntr.HwInit();
  
  I2C_SlaveTxn.DefaultByte = 0xff;
  
  I2C_SlaveTxn.TxIndex = 0;
  I2C_SlaveTxn.TxLen = 1;
  I2C_SlaveTxn.TxBuf = (uint8_t*)myI2C_CMD.Response;
  
  I2C_SlaveTxn.RxIndex = 0;  
  I2C_SlaveTxn.RxLen = sizeof(I2c_Cmd_request);  
  I2C_SlaveTxn.RxBuf = (uint8_t*)myI2C_CMD.Request;
  
  I2C_SlaveTxn.TxBuf[0] = CMD_STATUS_READY;
    
  I2C_SlaveTxn.XferDoneCallback = I2C_CmdSvr_Callback;
    
  while(I2CDevIntr.SlaveStartListening(&I2C_SlaveTxn) != i2c::I2C_OK);
  
  return CMD_STATUS_OK;
    
}

void I2C_CmdSvr_Callback(i2c::I2CStatus_t status)
{  
  if((status == i2c::I2C_SLAVE_RX_DONE) )
  {
    I2C_SlaveTxn.TxIndex = 0;      
    I2C_SlaveTxn.TxLen = 1;
    
    if((I2C_SlaveTxn.TxBuf[0] == CMD_STATUS_READY) && (I2C_SlaveTxn.RxIndex >= sizeof(RspHdr_t)))
    {
      I2C_SlaveTxn.TxBuf[0] = CMD_STATUS_PROCESSING;
    }
    else
    {
      I2C_SlaveTxn.RxIndex = 0;
    }    
    I2C_SlaveTxn.RxIndex = 0; 
  }
  else if(status == i2c::I2C_SLAVE_RX_DONE_WITH_NACK)
  {
    I2C_SlaveTxn.RxIndex = 0; 
  }
  else if(status == i2c::I2C_SLAVE_TX_DONE)
  {           
    if(I2C_SlaveTxn.TxBuf[0] == CMD_STATUS_PROCESSING)
    {
        I2C_SlaveTxn.TxIndex = 0;  
    }
    else if(I2C_SlaveTxn.TxBuf[0] == CMD_STATUS_PROCESSING_DONE)
    {
      if(I2C_SlaveTxn.TxIndex >= sizeof(RspHdr_t))
      {
        I2C_SlaveTxn.TxBuf[0] = CMD_STATUS_READY;
        I2C_SlaveTxn.TxLen = 1; 
      }
    }
    else if(I2C_SlaveTxn.TxBuf[0] == CMD_STATUS_READY)
    {
      
    }
    else
    {
      while(1);
    }
    I2C_SlaveTxn.TxIndex = 0;     
  }
  else
  {
    while(1);
  } 
  
}


void CmdSvr_Run(void)
{  
  if(CmdSvr_GetStatus() == CMD_STATUS_PROCESSING)
  {
    Cmdsvr_DispatchCmd(&myI2C_CMD);
    Cmdsvr_DispatchResponse(&myI2C_CMD);
  } 
}
