


#include"system.h"
#include"CmdSvr.h"


/* I2C Command Table*/
enum I2C_Commands
{
  I2C_CMDID_ADD_REQUEST,
  I2C_CMDID_ADD_RESPONSE,
  I2C_CMDID_SUB_REQUEST,
  I2C_CMDID_SUB_RESPONSE,
  I2C_CMDID_MUL_REQUEST,
  I2C_CMDID_MUL_RESPONSE,
  I2C_CMDID_DIV_REQUEST,
  I2C_CMDID_DIV_RESPONSE,
};

CmdStatus_t I2C_CmdHandler(Cmd_t* CmdHdr);
CmdStatus_t I2C_CmdHandler1(Cmd_t* CmdHdr);

CmdStatus_t I2C_Add(Cmd_t *pCmd);
CmdStatus_t I2C_Sub(Cmd_t *pCmd);
CmdStatus_t I2C_Mul(Cmd_t *pCmd);
CmdStatus_t I2C_Div(Cmd_t *pCmd);