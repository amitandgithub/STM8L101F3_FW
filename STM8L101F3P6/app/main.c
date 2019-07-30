
#include"system.h"

#define LED B0

void Gpio_1_Callback();

void main(void)
{
   __disable_interrupt();
    GpioSetOutputOpenDrainPushPull(LED);
    GpioSetInputPullupInterrupt(B1);
    Gpio1SetInterrupt(FALLING,Gpio_1_Callback);
    __enable_interrupt();
    Gpio_On(LED);
    I2cTxPoll(1,0,1);
    I2cRxPoll(1,0,1);
    while (1)
    {
      //Gpio_Toggle(LED);
      //Gpio_On(LED);
      Gpio_Off(LED);
    }

}

void Gpio_1_Callback()
{
  Gpio_On(LED);
}
























#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/