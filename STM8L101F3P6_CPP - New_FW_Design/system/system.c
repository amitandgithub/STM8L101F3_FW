/******************
** FILE: system.c
**
** DESCRIPTION:
**  System level utilities implementation
**
** CREATED: 7/31/2019, by Amit Chaudhary
******************/
#include "system.h"
#include"DigitalInOut.h"
inline void Dummy_ISR(){};

/* Array of EXTI interrupts*/
GpioFptr_t EXTI_ISRs[8] = {Dummy_ISR,Dummy_ISR,Dummy_ISR,Dummy_ISR,Dummy_ISR,Dummy_ISR,Dummy_ISR,Dummy_ISR};
  
const uint8_t CLZ[0xff] = 
{
255,
0,                      /* 1,1 */
1,1,                    /* 2,2 */
2,2,2,2,                /* 3,4 */
3,3,3,3,3,3,3,3,        /* 4,8 */
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,        /* 5,16 */
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,        /* 6,32 */
6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,        /* 7,64 */
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,        /* 7,128 */
7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
};


