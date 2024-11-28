#include "funcionamiento.h"
#include "UART.h"
#include "ADS131E08.h"
#include "GPIO.h"
#include "board_api.h"
#include "chip.h"
#include <stdlib.h>


/**
 * @brief Bandera que indica si el ADS131E08 esta adquiriendo data o no
 */
bool is_running = FALSE;

/**
 * @brief Variable utilizada para el control de los diferentes estados del programa
 */
uint8_t estado;

/**
 * @brief Variable utilizada para indicar el canal que se visualizara en el vumetro
 */
uint8_t currentChannel;

/**
 * @brief Variable utilizada para indicar la cantidad de muestras por segundos actual
 */
uint8_t current_kSPS;


/**
 * @brief Inicializar el ADS131E09 y enviar mensaje de bienvenida
 */
void Funcionamiento_Init()
{
	// Inicializar ADS131E08
   ADS131E08_signalDown();
	ADS131E08_Init();
	delayMs(50);
	ADS131E08_defaultConfig();
	estado = 0;
	currentChannel = 1;
	current_kSPS = 1;
	is_running = FALSE;
   GPIO_stopped(currentChannel);
}


/**
 * @brief Funcionamiento general del sistema
 */
void Funcionamiento_Menu()
{
	if(!is_running)
	{
		switch (estado)
		{
         case 0: // Estado: STOPPED
         {
            if (!(Board_TEC_GetStatus(BOARD_TEC_1))) {
               GPIO_start(currentChannel);
               is_running = 1;
               ADS131E08_startADS();
            }
            if (!(Board_TEC_GetStatus(BOARD_TEC_2))) {
               GPIO_selectChannel(currentChannel);
               estado = 1;
            }
            if (!(Board_TEC_GetStatus(BOARD_TEC_3))) {
               GPIO_select_kSPS(current_kSPS);
               estado = 2;
            }
            break;
         }
         case 1: // Estado: SELECT CHANNEL
         {
            if (!(Board_TEC_GetStatus(BOARD_TEC_3))) {
               currentChannel = currentChannel - 1;
               if (currentChannel == 0) {
                  currentChannel = 8;
               }
               GPIO_selectChannel(currentChannel);
            }
            if (!(Board_TEC_GetStatus(BOARD_TEC_4))) {
               currentChannel = currentChannel + 1;
               if (currentChannel == 9) {
                  currentChannel = 1;
               }
               GPIO_selectChannel(currentChannel);
            }
            if (!(Board_TEC_GetStatus(BOARD_TEC_1))) {
               GPIO_stopped(currentChannel);
               estado = 0;
            }
         }
         case 2: // Estado: SELECT kSPS
         {
            if (!(Board_TEC_GetStatus(BOARD_TEC_3))) {
               current_kSPS--;
               if (current_kSPS == 0) {
                  current_kSPS = 4;
               }
               GPIO_select_kSPS(current_kSPS);
            }
            if (!(Board_TEC_GetStatus(BOARD_TEC_4))) {
               current_kSPS++;
               if (current_kSPS == 3) {
                  current_kSPS = 4;
               }
               if (current_kSPS == 5) {
                  current_kSPS = 1;
               }
               GPIO_select_kSPS(current_kSPS);
            }
            if (!(Board_TEC_GetStatus(BOARD_TEC_2))) {
               GPIO_stopped(currentChannel);
               estado = 0;
            }
         }
         default:
            break;
      }
   }
	else
	{
		while(!(ADS131E08_isDataAvailable()));
		ADS131E08_getChannelData(&sampleCnt, channelData);
      /*for(uint8_t i=0; i<8; i++)
      {
         UART_Send((int *) &channelData[i], 4);
         delayMs(10000);
      }*/
      UART_Send((int *) &channelData[0],4);
      //delayMs(500);
		GPIO_getSignal(channelData[currentChannel]);
		if (!(Board_TEC_GetStatus(BOARD_TEC_1))) {
         GPIO_stopped(currentChannel);
			is_running = 0;
         estado = 0;
			ADS131E08_stopADS();
		}
	}
}


void SysTick_Handler(void) {
   tick_ct++;
}


void delayMs(uint32_t tk) {
	SysTick_Config(SystemCoreClock / 1000);
	uint32_t end = tick_ct + tk;
	while(tick_ct < end)
		__WFI();
}


void delayUs(uint32_t tk) {
	SysTick_Config(SystemCoreClock / 1000000);
	uint32_t end = tick_ct + tk;
	while(tick_ct < end)
		__WFI();
}