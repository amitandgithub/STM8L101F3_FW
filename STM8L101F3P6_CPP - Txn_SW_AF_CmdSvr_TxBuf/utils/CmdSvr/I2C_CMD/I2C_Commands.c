


#include"I2C_Commands.h"


uint8_t I2c_Cmd_request[15];
uint8_t I2c_Cmd_response[15];



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
  struct I2C_Add_Cmd_Response* ReponseData = (struct I2C_Add_Cmd_Response*)I2c_Cmd_response;
  struct I2C_Add_Cmd_Request* RequestData =  (struct I2C_Add_Cmd_Request*)pCmd->Request;
  
   pCmd->Response = (RspHdr_t*)I2c_Cmd_response;
   
  switch(pCmd->Request->CmdID)
  {
  case I2C_CMDID_ADD_REQUEST:    
    ReponseData->CmdId  = I2C_CMDID_ADD_RESPONSE;
    ReponseData->Len    = 1;
    ReponseData->Result = RequestData->Param1 + RequestData->Param2;
    break;
  case I2C_CMDID_SUB_REQUEST:    
    ReponseData->CmdId  = I2C_CMDID_ADD_RESPONSE;
    ReponseData->Len    = 1;
    ReponseData->Result = RequestData->Param1 - RequestData->Param2;
    break;
  case I2C_CMDID_MUL_REQUEST:
    ReponseData->CmdId  = I2C_CMDID_ADD_RESPONSE;
    ReponseData->Len    = 1;
    ReponseData->Result = RequestData->Param1 * RequestData->Param2;
    break;
  case I2C_CMDID_DIV_REQUEST: 
    ReponseData->CmdId  = I2C_CMDID_ADD_RESPONSE;
    ReponseData->Len    = 1;
    ReponseData->Result = RequestData->Param1 / RequestData->Param2;
    break;
  default: 
    return CMD_STATUS_INVALID_CMDID;
    break;  
  }  
 
  return CMD_STATUS_OK;
}
//
//CmdStatus_t I2C_Add(Cmd_t *pCmd)
//{
//  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
//  //uint8_t* RequestData = (uint8_t*)((uint8_t*)(pCmd->Request) + CMDSVR_DATA_POS);
//  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_ADD_RESPONSE;
//  I2C_Response[CMDSVR_LEN_POS]          = 1;
//  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] + RequestData[1];
//  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_ADD_RESPONSE;
//  pCmd->Response = (RspHdr_t*)I2C_Response;
//  return CMD_STATUS_OK;
//}
//
//CmdStatus_t I2C_Sub(Cmd_t *pCmd)
//{
//  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
//  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_SUB_RESPONSE;
//  I2C_Response[CMDSVR_LEN_POS]          = 1;
//  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] - RequestData[1];
//  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_SUB_RESPONSE;
//  pCmd->Response = (RspHdr_t*)I2C_Response;
//  return CMD_STATUS_OK;
//}
//
//CmdStatus_t I2C_Mul(Cmd_t *pCmd)
//{
//  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
//  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_MUL_RESPONSE;
//  I2C_Response[CMDSVR_LEN_POS]          = 1;
//  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] * RequestData[1];
//  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_MUL_RESPONSE;\
//  pCmd->Response = (RspHdr_t*)I2C_Response;
//  return CMD_STATUS_OK;
//}
//
//CmdStatus_t I2C_Div(Cmd_t *pCmd)
//{
//  uint8_t* RequestData = CMDSVR_DATA_PTR(pCmd);
//  I2C_Response[CMDSVR_CMDID_POS]        = I2C_CMDID_DIV_RESPONSE;
//  I2C_Response[CMDSVR_LEN_POS]          = 1;
//  I2C_Response[CMDSVR_DATA_POS + 0] = RequestData[0] / RequestData[1];
//  I2C_Response[CMDSVR_DATA_POS + 1] = I2C_CMDID_DIV_RESPONSE;
//  pCmd->Response = (RspHdr_t*)I2C_Response;
//  return CMD_STATUS_OK;
//}




