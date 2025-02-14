#include "funcionamiento.h"
#include "UART.h"
#include "ADS131E08.h"
#include "GPIO.h"
#include "board_api.h"
#include "chip.h"
#include <stdlib.h>
#include "math.h"

#define SAMPLE_RATE 1000  // 1 kSPS
#define AMPLITUDE_MV 3    // Amplitud máxima en mV
#define VREF_MV 2400      // Voltaje de referencia en mV
#define RESOLUTION 24     // Resolución del ADC en bits
#define FREQUENCY 1000 // Frecuencia de la señal en Hz
#define CLOCK_CYCLES_PER_STATE 1000 // Calculado previamente

#define SAMPLES_PER_CYCLE 1000   // Número de muestras por ciclo de la triangular



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
 * @brief Variable utilizada para indicar el modo en el cual se leen las senales desde el sensor
 */
uint8_t currentMode;

/**
 * @brief Variable utilizada para indicar el canal que se visualizara en el vumetro
 */
uint8_t currentChannel;

/**
 * @brief Variable utilizada para indicar la cantidad de muestras por segundos actual
 */
uint8_t current_kSPS;

uint8_t i = 0;

bool signal=true;

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
   currentMode = 0;
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
            //generate_triangle_wave(channelData);
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
            if (getPulsador(BOARD_TEC_4)) {
               GPIO_selectMode(currentMode);
               estado = 3;
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
         case 3: // Estado: SELECT MODE
         {
            if (getPulsador(BOARD_TEC_3)) {
               currentMode++;
               if (currentMode == 2) {
                  currentMode = 0;
               }
               GPIO_selectMode(currentMode);
            }
            if (getPulsador(BOARD_TEC_1)) {
               GPIO_stopped(currentChannel);
               ADS131E08_selectMode(currentMode, currentChannel);
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
      //generate_triangle_wave(channelData[currentChannel-5]);
      //generate_signal(channelData[currentChannel-5], signal);
      //delayMs(1000);
      //if (i == 50) {
         // GPIO_getSignal(channelData[currentChannel-5],&min,&max);
      GPIO_getSignal(channelData[currentChannel-5]);
      //   i = 0;
      //} else i++;
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

// Convierte un voltaje en mV a un valor en formato de 24 bits con complemento a 2
uint32_t mv_to_digital(int32_t mv) {
    int32_t max_value = (1 << (RESOLUTION - 1)) - 1; // Máximo valor positivo (2^23 - 1)
    int32_t min_value = -(1 << (RESOLUTION - 1));   // Mínimo valor negativo (-2^23)

    // Escala el voltaje a un valor digital
    int32_t digital_value = (mv * max_value) / VREF_MV;

    // Asegura que el valor está dentro del rango permitido
    if (digital_value > max_value) {
        digital_value = max_value;
    } else if (digital_value < min_value) {
        digital_value = min_value;
    }

    // Convierte el valor a uint32_t manteniendo el formato de complemento a 2 en los 24 bits menos significativos
    return (uint32_t)(digital_value & 0xFFFFFF);
}

// Genera una señal cuadrada
void generate_signal(uint32_t channelData, bool signal) {
   for (int i=0;i<1000;i++) {
      // Generar la señal
      int32_t volt = signal ? AMPLITUDE_MV : -AMPLITUDE_MV; // Selecciona alto o bajo en mV
      channelData = mv_to_digital(volt);
      signal=!signal;
      if ((channelData>> 23) & 1) { 
         channelData = (~(channelData) + 1);
         channelData &= 0xAAFFFFFF;
         channelData |= 0x00800000;         
      } else {
         channelData |= 0xAA000000;
      }
      UART_Send(&channelData,4);
      for (int i = 0; i < CLOCK_CYCLES_PER_STATE; i++) {
         // Esperar un ciclo de reloj (esta función depende de tu microcontrolador)
         __asm__ volatile ("nop"); // Ejemplo: instrucción NOP (no-operation)
      }
   }
}
void generate_triangle_wave(uint32_t channelData) {
    // Recorre las muestras en un patrón cíclico
    for (int i = 0; i < 10000; i++) {
        // Índice dentro del ciclo (asegurando uniformidad)
        int sample_in_cycle = i % SAMPLES_PER_CYCLE;
        // Calcula el valor de la señal triangular
        int32_t volt;
        if (sample_in_cycle < SAMPLES_PER_CYCLE / 2) {
            // Fase ascendente: de -AMPLITUDE_MV a +AMPLITUDE_MV
            volt = -AMPLITUDE_MV + (2 * AMPLITUDE_MV * sample_in_cycle) / (SAMPLES_PER_CYCLE / 2);
        } else {
            // Fase descendente: de +AMPLITUDE_MV a -AMPLITUDE_MV
            volt = AMPLITUDE_MV - (2 * AMPLITUDE_MV * (sample_in_cycle - SAMPLES_PER_CYCLE / 2)) / (SAMPLES_PER_CYCLE / 2);
        }
        // Convierte el voltaje a digital
        channelData = mv_to_digital(volt);
        // Procesa los datos según tu formato
        if ((channelData >> 23) & 1) {
            channelData = (~(channelData) + 1);
            channelData &= 0xAAFFFFFF;
            channelData |= 0x00800000;
        } else {
            channelData |= 0xAA000000;
        }

        // Envía los datos por UART
        UART_Send(&channelData, 4);
    }
 }