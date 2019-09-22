


#include"I2C_Commands.h"


uint8_t I2C_Response[10] = {MODULE_ID_I2C,};

CmdStatus_t I2C_CmdHandler(Cmd_t* CmdHdr)
{
  CmdStatus_t CmdStatus;  
  
  switch(CmdHdr->Request->CmdID)
  {
  case I2C_CMDID_ADD_REQUEST: 
    CmdStatus = I2C_Add(CmdHdr);
    break;
  case I2C_CMDID_SUB_REQUEST: 
    CmdStatus = I2C_Sub(CmdHdr);
    break;
  case I2C_CMDID_MUL_REQUEST:
    CmdStatus = I2C_Mul(CmdHdr);
    break;
  case I2C_CMDID_DIV_REQUEST: 
    CmdStatus = I2C_Div(CmdHdr);
    break;
  default:  break;  
  }  
  return CmdStatus;
}

CmdStatus_t I2C_CmdHandler1(Cmd_t* pCmd)
{
  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);  
  
  switch(pCmd->Request->CmdID)
  {
  case I2C_CMDID_ADD_REQUEST: 
    I2C_Response[CMDSVR_CMDID_POS]      = I2C_CMDID_SUB_RESPONSE;
    I2C_Response[CMDSVR_LEN_POS]        = 1;
    I2C_Response[CMDSVR_DATA_POS + 0]   = RequestData[0] + RequestData[1];
    I2C_Response[CMDSVR_DATA_POS + 1]   = I2C_CMDID_SUB_RESPONSE;
    //return CMD_STATUS_OK;
    break;
  case I2C_CMDID_SUB_REQUEST: 
    I2C_Response[CMDSVR_CMDID_POS]      = I2C_CMDID_SUB_RESPONSE;
    I2C_Response[CMDSVR_LEN_POS]        = 1;
    I2C_Response[CMDSVR_DATA_POS + 0]   = RequestData[0] - RequestData[1];
    I2C_Response[CMDSVR_DATA_POS + 1]   = I2C_CMDID_SUB_RESPONSE;
    //return CMD_STATUS_OK;
    break;
  case I2C_CMDID_MUL_REQUEST:
    I2C_Response[CMDSVR_CMDID_POS]      = I2C_CMDID_MUL_RESPONSE;
    I2C_Response[CMDSVR_LEN_POS]        = 1;
    I2C_Response[CMDSVR_DATA_POS + 0]   = RequestData[0] * RequestData[1];
    I2C_Response[CMDSVR_DATA_POS + 1]   = I2C_CMDID_MUL_RESPONSE;
    //return CMD_STATUS_OK;
    break;
  case I2C_CMDID_DIV_REQUEST: 
    I2C_Response[CMDSVR_CMDID_POS]      = I2C_CMDID_DIV_RESPONSE;
    I2C_Response[CMDSVR_LEN_POS]        = 1;
    I2C_Response[CMDSVR_DATA_POS + 0]   = RequestData[0] / RequestData[1];
    I2C_Response[CMDSVR_DATA_POS + 1]   = I2C_CMDID_DIV_RESPONSE;    
    break;
  default: 
    return CMD_STATUS_INVALID_CMDID;
    break;  
  }  
  pCmd->Response = (CmdHdr_t*)I2C_Response;
  return CMD_STATUS_OK;
}

CmdStatus_t I2C_Add(Cmd_t *pCmd)
{
  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
  //uint8_t* RequestData = (uint8_t*)((uint8_t*)(pCmd->Request) + CMDSVR_DATA_POS);
  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_ADD_RESPONSE;
  I2C_Response[CMDSVR_LEN_POS]          = 1;
  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] + RequestData[1];
  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_ADD_RESPONSE;
  pCmd->Response = (CmdHdr_t*)I2C_Response;
  return CMD_STATUS_OK;
}

CmdStatus_t I2C_Sub(Cmd_t *pCmd)
{
  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_SUB_RESPONSE;
  I2C_Response[CMDSVR_LEN_POS]          = 1;
  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] - RequestData[1];
  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_SUB_RESPONSE;
  pCmd->Response = (CmdHdr_t*)I2C_Response;
  return CMD_STATUS_OK;
}

CmdStatus_t I2C_Mul(Cmd_t *pCmd)
{
  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_MUL_RESPONSE;
  I2C_Response[CMDSVR_LEN_POS]          = 1;
  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] * RequestData[1];
  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_MUL_RESPONSE;\
  pCmd->Response = (CmdHdr_t*)I2C_Response;
  return CMD_STATUS_OK;
}

CmdStatus_t I2C_Div(Cmd_t *pCmd)
{
  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_DIV_RESPONSE;
  I2C_Response[CMDSVR_LEN_POS]          = 1;
  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] / RequestData[1];
  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_DIV_RESPONSE;
  pCmd->Response = (CmdHdr_t*)I2C_Response;
  return CMD_STATUS_OK;
}




