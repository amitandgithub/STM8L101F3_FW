
#include"system.h"
#include"tests.h"

void Gpio_1_Callback();



//template<uint8_t slaveAddress,uint8_t txLen, uint8_t rxLen, uint8_t repeatedStart>
//class TxnPoll
//{
//public:
//    uint8_t TxBuf[10]; 
//    uint8_t RxBuf[10];
//    
//    uint8_t send(){return (uint8_t)I2cXferPoll(slaveAddress,TxBuf, txLen, RxBuf, rxLen, repeatedStart);} 
//
//};


uint8_t I2C_Request[10] = {MODULE_ID_I2C,};
Cmd_t myI2C_CMD = {(CmdHdr_t*)I2C_Request,0};

void main(void)
{
    CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
    CLK->CKDIVR = (uint8_t)0;
    __enable_interrupt(); 
    I2C_Slave_Tests();
    I2C_Request[CMDSVR_CMDID_POS] = I2C_CMDID_DIV_REQUEST;
    I2C_Request[CMDSVR_LEN_POS] = 2;
    I2C_Request[CMDSVR_DATA_POS + 0] = 50;
    I2C_Request[CMDSVR_DATA_POS + 1] = 2;
    I2C_Request[CMDSVR_DATA_POS + 2] = I2C_CMDID_DIV_REQUEST;
    
    while (1)
    {
      Cmdsvr_DispatchCmd(&myI2C_CMD);
       // gpio_tests();
        //I2c_Master_Tests();
        
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