


#include "CmdSvr.h"

#include"I2C_Commands.h"


static const CmdHandler CmdTable[MODULE_ID_MAX] = 
{       
  I2C_CmdHandler1,                                        
};


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
  return CMD_STATUS_OK;
}