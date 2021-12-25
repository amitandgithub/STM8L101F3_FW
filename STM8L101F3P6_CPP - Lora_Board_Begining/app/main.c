
#include"system.h"
#include"tests.h"
#include"interrupt.h"
#include"eeprom.h"

extern Cmd_t myI2C_CMD;


void main(void)
{
  //SystemInterrupts.Register( afunc, FLASH_IRQ );
    CLK->CKDIVR = (uint8_t)0;
    __enable_interrupt(); 
    RST->SR = 0x3F;
    //I2C_Slave_Tests(); 
    //Cmdsvr_Init();
    //TestGPIO.HwInit();
    //TestLED.HwInit();
    //RTF_Init();
   // RST->SR  = 0xff;
    while(1)
    {
      //CmdSvr_Run();     
      // gpio_tests();
      I2c_Master_Tests();
       //Spi_Tests();
      // RTF_Run();
     // Uart_Test();
      //Templates_Test();
      //template_test();
      //timer_tests();
      // delay_ms(1000);
        
    }
}









/*
#include <cstdint>

static constexpr int BUFFER_LENGTH = 200;
typedef uint8_t(&BufferReference)[BUFFER_LENGTH];

void DoSomething(BufferReference buffer)
{
    buffer[BUFFER_LENGTH-1] = 0;	// safe, compiler errors on wrong size buffer
}

uint8_t badBuffer[100];
uint8_t goodBuffer[200];

int main()
{
    DoSomething(badBuffer);	// ERROR
    DoSomething(goodBuffer);	// OK

    return 0;
}

*/







//void Gpio_1_Callback();



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