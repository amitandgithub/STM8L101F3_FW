


#include "CmdSvr.h"

#include"I2C_Commands.h"

static i2c I2CDevIntr;
static i2c::SlaveTxn_t I2C_SlaveTxn;

CmdSvrContext_t CmdSvrContext = {  
                                  {MODULE_ID_I2C,},
                                  {MODULE_ID_I2C,},
                                  CMD_STATUS_READY
                                };

Cmd_t myI2C_CMD = {(CmdHdr_t*)CmdSvrContext.RequestBuf,0};

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
  return CmdSvrContext.Status;
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
    I2C_SlaveTxn.TxBuf = (uint8_t*)pCmd->Response;    
    I2C_SlaveTxn.TxBufSize = pCmd->Response->Len + 4;
    CmdSvrContext.Status = CMD_STATUS_PROCESSING_DONE;
    
  }
  else
  {    
    I2C_SlaveTxn.TxBuf = (uint8_t*)&CmdSvrContext.Status;    
    I2C_SlaveTxn.TxBufSize = 1;
    CmdSvrContext.Status = CMD_STATUS_READY;
  }
  I2C_SlaveTxn.RxIndex = 0;
  I2C_SlaveTxn.RxBufSize = sizeof(CmdSvrContext.RequestBuf);
  //I2C_SlaveTxn.TxIndex = 0;
  I2CDevIntr.SlaveStartReceiving();
  return CMD_STATUS_OK;
}

CmdStatus_t Cmdsvr_Init()
{
  I2CDevIntr.HwInit();
  
  I2C_SlaveTxn.TxIndex = 0;
  I2C_SlaveTxn.TxBufSize = 1;
  I2C_SlaveTxn.TxBuf = (uint8_t*)&CmdSvrContext.Status;
  
  I2C_SlaveTxn.RxIndex = 0;  
  I2C_SlaveTxn.RxBufSize = sizeof(CmdSvrContext.RequestBuf);  
  I2C_SlaveTxn.RxBuf = CmdSvrContext.RequestBuf;
  
  I2C_SlaveTxn.XferDoneCallback = I2C_CmdSvr_Callback;
    
  while(I2CDevIntr.SlaveStartListening(&I2C_SlaveTxn) != i2c::I2C_OK);
  
  CmdSvrContext.Status = CMD_STATUS_READY;
    
  return CMD_STATUS_OK;
    
}

void I2C_CmdSvr_Callback(i2c::I2CStatus_t status)
{  
  if((status == i2c::I2C_SLAVE_RX_DONE) )
  {
    I2C_SlaveTxn.TxIndex = 0;      
    I2C_SlaveTxn.TxBufSize = 1;
    
    if((CmdSvrContext.Status == CMD_STATUS_READY) && (I2C_SlaveTxn.RxIndex >= 4))
    {
      CmdSvrContext.Status = CMD_STATUS_PROCESSING;
      
      //I2C_SlaveTxn.RxBuf = CmdSvr_SwitchBuf(I2C_SlaveTxn.RxBuf);
    }
    else
    {
      //CmdSvrContext.Status = CMD_STATUS_LEN_ERROR;
      I2C_SlaveTxn.RxIndex = 0;
    }    
    
    I2CDevIntr.SlaveStartReceiving();   
  }
  else if(status == i2c::I2C_SLAVE_RX_DONE_WITH_NACK)
  {
    //I2CDevIntr.SlaveStartReceiving();
    //I2C_SlaveTxn.RxIndex = 0; 
  }
  else if(status == i2c::I2C_SLAVE_TX_DONE)
  {
    I2C_SlaveTxn.TxIndex = 0;    
    
    if(CmdSvrContext.Status == CMD_STATUS_PROCESSING)
    {
        I2CDevIntr.SlaveStopReceiving();
    }
    else if(CmdSvrContext.Status == CMD_STATUS_PROCESSING_DONE)
    {
      if(I2C_SlaveTxn.TxIndex >= 4)
      {
        CmdSvrContext.Status = CMD_STATUS_READY;        
        I2C_SlaveTxn.TxBufSize = 1;
        I2C_SlaveTxn.TxBuf = (uint8_t*)&CmdSvrContext.Status;
        //I2CDevIntr.SlaveStartReceiving();  
      }
    }
    else if(status == i2c::I2C_ACK_FAIL)
    {
      while(1);
    }
  }
  else
  {
    
  } 
  
}

