
#include"system.h"
#include"tests.h"

void Gpio_1_Callback();



//DigitalOut<LED> Led;
//DigitalIn<BUTTON> Button;

void main(void)
{
    __disable_interrupt();
    CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
    CLK->CKDIVR = (uint8_t)0;
    __enable_interrupt();

    
    while (1)
    {
       
        gpio_tests();
        I2c_Poll_Tests();  
    }
}









/*


*/














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