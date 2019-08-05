/******************
** FILE: queue.c
**
** DESCRIPTION:
**  queue implementation
**
** CREATED: 8/5/2019, by Amit Chaudhary
******************/
#include"queue_8bit.h"

void QueueInit(Queue_t* pQueue)
{
  if(pQueue)
  {
    pQueue->WriteHead =  pQueue->Capacity - 1; // rear
    pQueue->ReadHead =  0; // front
  }
}

uint8_t QueueFull(Queue_t* pQueue)
{
  return (pQueue->Size == pQueue->Capacity);
}

uint8_t QueueEmpty(Queue_t* pQueue)
{
  return (pQueue->Size == 0);
}

uint8_t Available(Queue_t* pQueue)
{
  return pQueue->Size;
}
/**
 * Enqueue/Insert an element to the queue. 
 */
uint8_t QueueWrite(Queue_t* pQueue,uint8_t data)
{
    // Queue is full throw Queue out of capacity error.
    if (QueueFull(pQueue)) 
    {
        return 0;
    }

    pQueue->WriteHead += 1;// (pQueue->WriteHead + 1) % CAPACITY;
    
    if(pQueue->WriteHead == pQueue->Capacity)
        pQueue->WriteHead = 0;

    // Increment queue size
    pQueue->Size++;

    // Enqueue new element to queue
    pQueue->Buf[pQueue->WriteHead] = data;

    // Successfully enqueued element to queue
    return 1;
}

/**
 * Dequeue/Remove an element from the queue. 
 */
uint8_t QueueRead(Queue_t* pQueue, uint8_t* pdata)
{
    // Queue is empty, throw Queue underflow error
    if (QueueEmpty(pQueue))
    {
        return 1;
    }

    // Dequeue element from queue
    *pdata = pQueue->Buf[pQueue->ReadHead];

    // Ensure front never crosses array bounds
    pQueue->ReadHead +=1;// (front + 1) % CAPACITY;
    
     if(pQueue->ReadHead == pQueue->Capacity)
        pQueue->ReadHead = 0;

    // Decrease queue size
    pQueue->Size--;

    return 0;
}








