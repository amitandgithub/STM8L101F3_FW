/******************
** FILE: queue.h
**
** DESCRIPTION:
**  queue implementation
**
** CREATED: 8/5/2019, by Amit Chaudhary
******************/

#ifndef queue_h
#define queue_h

//#include <stdint.h>
#include "stm8l10x.h"


typedef struct
{
  uint8_t ReadHead;
  uint8_t WriteHead;
  uint8_t Size;
  uint8_t Capacity;
  uint8_t* Buf;
}Queue_t;

void QueueInit(Queue_t* pQueue);

uint8_t QueueFull(Queue_t* pQueue);

uint8_t QueueEmpty(Queue_t* pQueue);

uint8_t Available(Queue_t* pQueue);

uint8_t QueueWrite(Queue_t* pQueue,uint8_t data);

uint8_t QueueRead(Queue_t* pQueue, uint8_t* pdata);

#endif