


#include "CmdSvr.h"

#include"I2C_Commands.h"

#define CMDSVR_BUF_SIZE 20

static i2c I2CDevIntr;
//static i2c::SlaveTxn_t I2C_SlaveTxn;

uint8_t CmdSvr_Buf[CMDSVR_BUF_SIZE] = {CMD_STATUS_READY,};
i2c::i2cBuf_t CmdSvr_TxBuf = {&CmdSvr_Buf[0],1,0};
i2c::i2cBuf_t CmdSvr_RxBuf = {&CmdSvr_Buf[1],CMDSVR_BUF_SIZE,0};

Cmd_t CmdSvr_Cmd = {(CmdHdr_t*)CmdSvr_RxBuf.Buf,(RspHdr_t*)CmdSvr_TxBuf.Buf};

CmdSvrContext_t CmdSvrContext = 
{
  { (CmdHdr_t*)CmdSvr_RxBuf.Buf,(RspHdr_t*)CmdSvr_TxBuf.Buf },
    CMD_STATUS_READY
};

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
  return CmdSvrContext.pStatus;
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
    CmdSvr_TxBuf.Buf = (uint8_t*)pCmd->Response;
    CmdSvr_TxBuf.Len = pCmd->Response->Len + sizeof(RspHdr_t) + 1;// 1 for CRC 
    pCmd->Response->Status = CMD_STATUS_PROCESSING_DONE;
    CmdSvrContext.pStatus = CMD_STATUS_PROCESSING_DONE;
  }
  else
  { 
    CmdSvr_TxBuf.Buf = &CmdSvr_Buf[0];
    CmdSvr_TxBuf.Len = 1;
    CmdSvr_Buf[0] = CMD_STATUS_PROCESSING_DONE;
    CmdSvrContext.pStatus = CMD_STATUS_PROCESSING_DONE;
  }
  CmdSvr_TxBuf.Idx = 0;
  CmdSvr_RxBuf.Idx = 0;
  delay_ms(100);  
  return CMD_STATUS_OK;
}

CmdStatus_t Cmdsvr_Init()
{
  I2CDevIntr.HwInit();
  
  I2CDevIntr.SetSlaveTxDefaultByte(0xff);
  
  I2CDevIntr.SetSlaveCallback(I2C_CmdSvr_Callback);
    
  while(I2CDevIntr.SlaveStartListening(&CmdSvr_TxBuf, &CmdSvr_RxBuf) != i2c::I2C_OK);
  
  //CmdSvrContext.pStatus = CMD_STATUS_READY;
  return CMD_STATUS_OK;
    
}

void I2C_CmdSvr_Callback(i2c::I2CStatus_t status)
{  
  if((status == i2c::I2C_SLAVE_RX_DONE) )
  {
    CmdSvr_TxBuf.Idx = 0;
    CmdSvr_TxBuf.Len = 1;
    
    if((CmdSvrContext.pStatus == CMD_STATUS_READY) && (CmdSvr_RxBuf.Idx >= sizeof(RspHdr_t)))
    {
      CmdSvrContext.pStatus = CMD_STATUS_PROCESSING;
    }
    else
    {
      CmdSvr_RxBuf.Idx = 0;
    }    
    CmdSvr_RxBuf.Idx = 0;
  }
  else if(status == i2c::I2C_SLAVE_RX_DONE_WITH_NACK)
  {
    CmdSvr_RxBuf.Idx = 0;
  }
  else if(status == i2c::I2C_SLAVE_TX_DONE)
  {           
    if(CmdSvrContext.pStatus == CMD_STATUS_PROCESSING)
    {
        CmdSvr_TxBuf.Idx = 0;  
    }
    else if(CmdSvrContext.pStatus == CMD_STATUS_PROCESSING_DONE)
    {
      //if(CmdSvr_TxBuf.Idx >= sizeof(RspHdr_t))
      if(CmdSvr_TxBuf.Idx >= 1)
      {
        CmdSvrContext.pStatus = CMD_STATUS_READY;
        CmdSvr_TxBuf.Len = 1;
      }
    }
    else if(CmdSvrContext.pStatus == CMD_STATUS_READY)
    {
      
    }
    else
    {
      while(1);
    }
    CmdSvr_TxBuf.Idx = 0;    
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
    Cmdsvr_DispatchCmd(&CmdSvrContext.Cmd);
    Cmdsvr_DispatchResponse(&CmdSvrContext.Cmd);
  } 
}