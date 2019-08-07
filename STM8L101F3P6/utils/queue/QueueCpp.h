/******************
** FILE: queue.h
**
** DESCRIPTION:
**  queue implementation
**
** CREATED: 8/5/2019, by Amit Chaudhary
******************/

#ifndef queueCpp_h
#define queueCpp_h

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
    
    void QueueInit();
    
    bool QueueFull();
    
    bool QueueEmpty();
    
    QueueSize_t AvailableEnteries();
    
    Queue_Status_t QueueWrite(QueueSize_t data);
    
    Queue_Status_t QueueRead(QueueSize_t* pdata);
    
private:
    Queue_t m_Queue;
    
};

#endif //queueCpp_h







