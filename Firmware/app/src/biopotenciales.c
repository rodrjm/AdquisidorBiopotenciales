/*	
      *@brief Proyecto BIOPOTENCIALES.
*/


/*==================[inclusions]=============================================*/

#include "biopotenciales.h"
#include "board.h"
#include "UART.h"
#include "ADS131E08.h"
#include "Drv_Devices.h"
#include "SPI.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*	* @brief hardware initialization function
 	*	@return none
*/
static void initHardware(void);

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	GPIO_init();
	// Inicializacion y configuracion del protocolo SPI
	SPI_init();
	SPI_setup();
	UART_setup();
}
/*int main(void)
{
	initHardware();
	delayMs(500);
	Board_LED_Toggle(1);
	delayMs(500);
	Board_LED_Toggle(1);
   
   uint8_t leerDatos = 0;
   */
	/*Drv_Devices_startFromScratch();
   /ADS131E08_startStreaming();
   /ADS131E08_sendCommand(_SDATAC);
   ADS131E08_configureInternalTestSignal(_CONFIG2_TEST_AMP_1X,_CONFIG2_TEST_FREQ_21); // CONFIG2 = 0xF0;
   delayMs(500);
   ADS131E08_WREG(_CH1SET_ADDRESS,_CHSET_MUX_TEST_SIGNAL); // CH1SET = 0x05;
   delayMs(500);
   ADS131E08_sendCommand(_RDATAC);
   delayMs(500);
   //ADS131E08_RREG(_CH1SET_ADDRESS);
   delayMs(500);
   uint8_t dato[24];
   ADS131E08_getRegistersData(dato);
   UART_Send(dato,24);
   //ADS131E08_startStreaming();*/
/*
	while (1)
	{
      //while(!(ADS131E08_isDataAvailable()));
      //ADS131E08_getChannelData(&sampleCnt, channelData);
      //UART_Send(&sampleCnt,1); //send sample counter value
      //for(uint8_t i=0; i<24; i++)
      //{
      //   UART_Send(&channelData[i],1);
      //}
      
      if (!(Board_TEC_GetStatus(BOARD_TEC_3))) {
         setLed(LED1_PORT,LED1_PIN,false);
         setLed(LED2_PORT,LED2_PIN,false);
         setLed(LED3_PORT,LED3_PIN,false);
         setLed(LED4_PORT,LED4_PIN,false);
         setLed(LED5_PORT,LED5_PIN,false);
         setLed(LED6_PORT,LED6_PIN,false);
         setLed(LED7_PORT,LED7_PIN,false);
         setLed(LED8_PORT,LED8_PIN,false);
         setLed(LED9_PORT,LED9_PIN,false);
         setLed(LED10_PORT,LED10_PIN,false);
      }
      if (!(Board_TEC_GetStatus(BOARD_TEC_4))) {
         setLed(LED1_PORT,LED1_PIN,true);
         setLed(LED2_PORT,LED2_PIN,true);
         setLed(LED3_PORT,LED3_PIN,true);
         setLed(LED4_PORT,LED4_PIN,true);
         setLed(LED5_PORT,LED5_PIN,true);
         setLed(LED6_PORT,LED6_PIN,true);
         setLed(LED7_PORT,LED7_PIN,true);
         setLed(LED8_PORT,LED8_PIN,true);
         setLed(LED9_PORT,LED9_PIN,true);
         setLed(LED10_PORT,LED10_PIN,true);
      }
      if (!(Board_TEC_GetStatus(BOARD_TEC_1))) {
         ADS131E08_signalDown();
         ADS131E08_initialize();
         id=ADS131E08_getDeviceID();
         UART_Send((int *) &id,1);
         //ADS131E08_configureTestSignal();
         while(!(ADS131E08_isDataAvailable()));
         leerDatos = 1;
      }
      if (!(Board_TEC_GetStatus(BOARD_TEC_2))) {
         leerDatos = 0;
      }
      if (leerDatos) {
         ADS131E08_getChannelData(&sampleCnt, channelData);
         for(uint8_t i=0; i<8; i++)
         {
            UART_Send((int *) &channelData[i], 3);
         }
         //UART_Send((int *) &channelData[0], 3);
         delayUs(1000);
      }
	}
}
*/
/*==================[end of file]============================================*/
