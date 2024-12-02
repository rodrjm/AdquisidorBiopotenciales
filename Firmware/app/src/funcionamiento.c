#include "funcionamiento.h"
#include "UART.h"
#include "ADS131E08.h"
#include "GPIO.h"
#include "board_api.h"
#include "chip.h"
#include <stdlib.h>


uint32_t max=0x000000; // Variable utilizada para llevar el maximo valor obtenido 
uint32_t min=0x7FFFFF; // Variable utilizada para llevar el minimo valor obtenido 
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

uint8_t i = 0;

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
	currentChannel = 5;
	current_kSPS = 6;
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
            if (getPulsador(BOARD_TEC_1)) {
                  GPIO_start(currentChannel);
                  is_running = 1;
                  ADS131E08_startADS();
            }
            if (getPulsador(BOARD_TEC_2)) {
               GPIO_selectChannel(currentChannel);
               estado = 1;
            }
            if (getPulsador(BOARD_TEC_3)) {
               GPIO_select_kSPS(current_kSPS);
               estado = 2;
            }
            break;
         }
         case 1: // Estado: SELECT CHANNEL
         {
            if (getPulsador(BOARD_TEC_3)) {
               currentChannel = currentChannel - 1;
               if (currentChannel == 4) {
                  currentChannel = 12;
               }
               GPIO_selectChannel(currentChannel);
            }
            if (getPulsador(BOARD_TEC_4)) {
               currentChannel = currentChannel + 1;
               if (currentChannel == 13) {
                  currentChannel = 5;
               }
               GPIO_selectChannel(currentChannel);
            }
            if (getPulsador(BOARD_TEC_1)) {
               GPIO_stopped(currentChannel);
               ADS131E08_selectChannel(currentChannel);
               estado = 0;
               max=0x000000; 
               min=0x7FFFFF;
            }
            break;
         }
         case 2: // Estado: SELECT kSPS
         {
            if (getPulsador(BOARD_TEC_3)) {
               current_kSPS++;
               if (current_kSPS == 7) {
                  current_kSPS = 2;
               }
               GPIO_select_kSPS(current_kSPS);
            }
            if (getPulsador(BOARD_TEC_4)) {
               current_kSPS--;
               if (current_kSPS == 1) {
                  current_kSPS = 6;
               }
               GPIO_select_kSPS(current_kSPS);
            }
            if (getPulsador(BOARD_TEC_1)) {
               GPIO_stopped(currentChannel);
               ADS131E08_selectkSPS(current_kSPS);
               estado = 0;
            }
            break;
         }
         default:
            break;
      }
   }
	else
	{
		while(!(ADS131E08_isDataAvailable()));
		ADS131E08_getChannelData(&sampleCnt, channelData);
      /*
      for(uint8_t i=0; i<8; i++)
      {
         UART_Send((int *) &channelData[i], 4);
      }
      */
      UART_Send(&channelData[currentChannel-5],4);
      //delayMs(1000);
      if (i == 50) {
         GPIO_getSignal(channelData[currentChannel-5],&min,&max);
         i = 0;
      } else i++;
		if (getPulsador(BOARD_TEC_1)) {
         GPIO_stopped(currentChannel);
			is_running = 0;
         estado = 0;
			ADS131E08_stopADS();
		}
	}
}


bool getPulsador(uint8_t pulsador) {
   if (!(Board_TEC_GetStatus(pulsador))) {
      delayMs(20);
      while (!(Board_TEC_GetStatus(pulsador)));
      delayMs(20);
      return true;
   }
   return false;
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