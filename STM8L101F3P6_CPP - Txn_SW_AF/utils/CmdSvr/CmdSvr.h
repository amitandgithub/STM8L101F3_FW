


#ifndef CmdSvr_h
#define CmdSvr_h

#include"system.h"


#define CMDSVR_CMD_LENGTH_MAX 32

typedef enum
{
  MODULE_ID_I2C,
  
  
  MODULE_ID_MAX, 
}ModuleID_t;


typedef enum
{
  CMD_STATUS_OK,
  CMD_STATUS_INVALID_PARAMS,
  CMD_STATUS_CRC_ERROR,
  CMD_STATUS_INVALID_MODULEID,
  CMD_STATUS_INVALID_CMDID,  
}CmdStatus_t;

typedef struct
{
  uint8_t ModuleID;
  uint8_t CmdID;
  uint8_t Len;
}CmdHdr_t;

typedef struct
{
  CmdHdr_t* Request;
  CmdHdr_t* Response;
}Cmd_t;


#define CMDSVR_MODULEID_POS 0

#define CMDSVR_CMDID_POS 1

#define CMDSVR_LEN_POS 2

#define CMDSVR_DATA_POS 3

#define CMDSVR_DATA_PTR(__X) (uint8_t*)( (uint8_t*)((__X)->Request) + CMDSVR_DATA_POS)

typedef CmdStatus_t (*CmdHandler)(Cmd_t* CmdHdr);


CmdStatus_t Cmdsvr_GetCmd(Cmd_t *pCmd);

CmdStatus_t Cmdsvr_AuthenticateCmd(Cmd_t *pCmd);

CmdStatus_t Cmdsvr_DispatchCmd(Cmd_t *pCmd);

CmdStatus_t Cmdsvr_DispatchResponse(Cmd_t *pCmd);























#endif