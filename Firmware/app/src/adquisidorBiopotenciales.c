/*	
    * adquisidorBiopotenciales.c
*/


#include "adquisidorBiopotenciales.h"
#include "board.h"
#include "UART.h"
#include "ADS131E08.h"
#include "funcionamiento.h"
#include "SPI.h"


/*	
    * @brief Funcion de inicializacion del hardware
*/
static void InitHardware(void);

static void InitHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	GPIO_Init();
	SPI_Init();    
	SPI_Setup();
	UART_Init();
}

int main(void)
{
    InitHardware();
    delayMs(500);
    Board_LED_Toggle(1);
    delayMs(500);
    Board_LED_Toggle(1);
    
    Funcionamiento_Init();
    while (1)
	{
      Funcionamiento_Menu();
	}
}