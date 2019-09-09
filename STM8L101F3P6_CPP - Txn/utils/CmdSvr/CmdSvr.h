


#ifndef CmdSvr_h
#define CmdSvr_h




typedef struct
{
  uint8_t ModuleID;
  uint8_t CmdID;
  uint8_t Len;  
}CmdHdr_t;


uint8_t Cmdsvr_GetCmd(CmdHdr_t *pCmd);

uint8_t Cmdsvr_AuthenticateCmd(CmdHdr_t *pCmd);

uint8_t Cmdsvr_ExecuteCmd(CmdHdr_t *pCmd);

uint8_t Cmdsvr_SendResponse(CmdHdr_t *pCmd);























#endif