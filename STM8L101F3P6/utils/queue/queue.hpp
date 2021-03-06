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

class queue
{
	public:
typedef enum
{
	QUEUE_OK,
    QUEUE_INVALID_PARAMS,
	QUEUE_FULL,
	QUEUE_EMPTY,
		
}Queue_Status_t;

typedef uint8_t QueueSize_t;
typedef struct
{
  QueueSize_t   ReadHead;
  QueueSize_t   WriteHead;
  QueueSize_t   Size;
  QueueSize_t   Capacity;
  QueueSize_t*  Buf;
}Queue_t;
/*
typedef struct
{
  uint16_t   ReadHead;
  uint16_t   WriteHead;
  uint16_t   Size;
  uint16_t   Capacity;
  uint8_t*   Buf;
}Queue_t;
*/
Queue_Status_t QueueInit();

Queue_Status_t QueueFull();

Queue_Status_t QueueEmpty();

Queue_Status_t AvailableEnteries(QueueSize_t* AvailableData);

Queue_Status_t QueueWrite(QueueSize_t data);

Queue_Status_t QueueRead(QueueSize_t* pdata);
private:
Queue_t
}

#endif