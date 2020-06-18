


#ifndef __RTF_h
#define __RTF_h

#include"system.h"

#define RTF_REQUEST_BUF_SIZE    128
#define RTF_REPLY_BUF_SIZE      30
#define IS_RTF_EVENT(RTF_EVENTS,RTF_EVENT) ((RTF_EVENTS)&(RTF_EVENT) == (RTF_EVENT))
#define CLEAR_RTF_EVENT(RTF_EVENTS,RTF_EVENT) ((RTF_EVENTS) &= ~(RTF_EVENT))

typedef enum
{
  RTF_STATUS_OK,
  RTF_STATUS_INVALID_PARAMS,
  RTF_STATUS_LEN_ERROR,
  RTF_STATUS_CRC_ERROR
}RTFStatus_t;

typedef enum
{
  RTF_STATE_IDLE,
  RTF_STATE_AUTHENTICATING,
  RTF_STATE_PROCESSING, 
  RTF_STATE_PROCESSING_DONE,
  RTF_STATE_ERROR  
}RTFState_t;


enum
{
  RTF_EVENT_NONE                        = 0x00U,
  RTF_EVENT_CMD_RECEIVED                = 0x01U,
  RTF_EVENT_AUTHENTICATION_SUCCESS      = 0x02U,
  RTF_EVENT_AUTHENTICATION_FAIL         = 0x04U,
  RTF_EVENT_CMD_RESPONSE_AVAILABLE      = 0x08U,
  RTF_EVENT_CMD_RESPONSE_SENT           = 0x10U
};

typedef struct
{
  RTFState_t    State;
  uint8_t       Events;
  uint8_t*      RequestBuf;
  uint8_t*      ReplyBuf;
  uint8_t       RequestLen;
  uint8_t       ReplyLen;  
}RTF_Context_t;


RTFStatus_t RTF_Init();

RTFState_t RTF_GetState();

void RTF_SetEvent(uint8_t event);

void RTF_ClearEvent(uint8_t event);

void RTF_ClearEventFromISR(uint8_t event);

uint8_t RTF_GetEvent();

void RTF_Run();





































#endif //__RTF_h