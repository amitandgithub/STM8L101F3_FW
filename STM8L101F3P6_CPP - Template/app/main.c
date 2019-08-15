
#include"system.h"
#include"tests.h"

void I2C_Callback(){};

uint8_t slaveAddress = 10;
uint8_t txBuf[10];
uint8_t txLen = 3;
uint8_t rxBuf[10];
uint8_t rxLen = 3;
uint8_t repeatedStart;
I2CStatus_t pstatus;
I2CCallback_t xferDoneCallback = I2C_Callback;

void main(void)
{
    CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
    CLK->CKDIVR = (uint8_t)0;
    
    
    while (1)
    {
//        I2cXferIntr<slaveAddress,txBuf,txLen,rxBuf,rxLen,repeatedStart,&pstatus,xferDoneCallback>();
        I2cXferIntr<(uint8_t)10>();
       // gpio_tests();
       // I2c_Poll_Tests();  
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