
#ifndef SYSTEM_H
#define SYSTEM_H



#include "stm8l10x.h"
#include "Gpio.h"
#include "i2c.h"


#include "i2c_tests.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE (!TRUE)
#endif




extern const uint8_t CLZ[];


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