
#ifndef SYSTEM_H
#define SYSTEM_H



#include "stm8l10x.h"
#include "stm8l10x_gpio.h"
#include "DigitalInOut.h"
#include "i2c.h"
#include "Spi.h"



#ifndef NULL
#define NULL ((void*)0)
#endif

#include "i2c_tests.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE (!TRUE)
#endif




extern const uint8_t CLZ[];


#define SIZE_OF_ARRAY(__array) sizeof(__array)/sizeof(__array[0])
//
// Delay loop
//
// Actual delay depends on clock settings
// and compiler optimization settings.
//

#define delay_1us(); delay(0);

#define delay_10us(); delay(18);

#define delay_50us(); delay(98);

#define delay_100us(); delay(198);

#define delay_1ms(); delay(1998);

#define delay_10ms(); delay(19998);

static inline void delay(unsigned int n)
{
    while (n-- > 0);
}

static inline void delay_ms(unsigned int n)
{
    while (n-- > 0)
	{
		delay_1ms();
	}
}
















#endif