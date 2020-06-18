


#include"RTF.h"


uint8_t RTF_RequestBuffer[RTF_REQUEST_BUF_SIZE];
uint8_t RTF_ReplyBuffer[RTF_REPLY_BUF_SIZE];

RTF_Context_t RTF_Context;

RTFStatus_t RTF_Init()
{
  RTF_Context.State             = RTF_STATE_IDLE;
  RTF_Context.Events            = RTF_EVENT_NONE;
  RTF_Context.RequestBuf        = RTF_RequestBuffer; 
  RTF_Context.ReplyBuf          = RTF_ReplyBuffer; 
  RTF_Context.RequestLen        = RTF_REQUEST_BUF_SIZE; 
  RTF_Context.ReplyLen          = RTF_REPLY_BUF_SIZE;  
  
  return RTF_STATUS_OK;
}

RTFState_t RTF_GetState()
{
  return RTF_Context.State;
}

void RTF_SetEvent(uint8_t event)
{
  RTF_Context.Events |= event;
}

uint8_t RTF_GetEvent()
{
  return RTF_Context.Events;
}

void RTF_ClearEvent(uint8_t event)
{
  __disable_interrupt();
  RTF_Context.Events &= ~event;
  __enable_interrupt();
}

void RTF_ClearEventFromISR(uint8_t event)
{
  RTF_Context.Events &= ~event;
}


void RTF_Run()
{
  uint8_t Current_events = RTF_GetEvent();
  
  if(IS_RTF_EVENT(Current_events,RTF_EVENT_CMD_RECEIVED))
  {
    
    RTF_ClearEvent(RTF_EVENT_CMD_RECEIVED);
  }
  else if(IS_RTF_EVENT(Current_events,RTF_EVENT_AUTHENTICATION_SUCCESS))
  {
    
    RTF_ClearEvent(RTF_EVENT_AUTHENTICATION_SUCCESS);
  }
  else if(IS_RTF_EVENT(Current_events,RTF_EVENT_AUTHENTICATION_FAIL))
  {
    
    RTF_ClearEvent(RTF_EVENT_AUTHENTICATION_FAIL);
  }
  else if(IS_RTF_EVENT(Current_events,RTF_EVENT_CMD_RESPONSE_AVAILABLE))
  {
    
    RTF_ClearEvent(RTF_EVENT_CMD_RESPONSE_AVAILABLE);
  }  
  else if(IS_RTF_EVENT(Current_events,RTF_EVENT_CMD_RESPONSE_SENT))
  {
   
    RTF_ClearEvent(RTF_EVENT_CMD_RESPONSE_SENT);
  } 
  
  
  
}