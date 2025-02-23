#include "funcionamiento.h" // Incluye el encabezado del archivo "funcionamiento.h" que contiene declaraciones de funciones y variables.
#include "UART.h" // Incluye el encabezado para la comunicación UART (Universal Asynchronous Receiver-Transmitter).
#include "ADS131E08.h" // Incluye el encabezado para el manejo del ADS131E08 (convertidor analógico a digital).
#include "GPIO.h" // Incluye el encabezado para el manejo de los GPIO (General Purpose Input/Output).
#include "board_api.h" // Incluye el encabezado para la API de la placa (específica de la placa utilizada).
#include "chip.h" // Incluye el encabezado para las funciones específicas del chip.
#include <stdlib.h> // Incluye la biblioteca estándar de C para funciones de utilidad general.
#include "math.h" // Incluye la biblioteca matemática de C para funciones matemáticas.

#define SAMPLE_RATE 1000  // Define la frecuencia de muestreo a 1000 muestras por segundo (1 kSPS).
#define AMPLITUDE_MV 3    // Define la amplitud máxima de la señal en milivoltios (3 mV).
#define VREF_MV 2400      // Define el voltaje de referencia del ADC en milivoltios (2400 mV).
#define RESOLUTION 24     // Define la resolución del ADC en 24 bits.
#define FREQUENCY 1000    // Define la frecuencia de la señal de prueba en hercios (1000 Hz).
#define CLOCK_CYCLES_PER_STATE 1000 // Define el número de ciclos de reloj por estado (para retardos).

#define SAMPLES_PER_CYCLE 1000    // Define el número de muestras por ciclo de la señal triangular.

uint32_t max = 0x000000; // Variable global para almacenar el valor máximo leído por el ADC.
uint32_t min = 0x7FFFFF; // Variable global para almacenar el valor mínimo leído por el ADC.

/**
 * @brief Bandera que indica si el ADS131E08 está adquiriendo datos o no.
 */
bool is_running = FALSE; // Variable global para indicar si el ADC está en modo de adquisición (TRUE) o no (FALSE).

/**
 * @brief Variable utilizada para el control de los diferentes estados del programa.
 */
uint8_t estado; // Variable global para controlar el estado actual del programa (menú, adquisición, etc.).

/**
 * @brief Variable utilizada para indicar el modo en el cual se leen las señales desde el sensor.
 */
uint8_t currentMode; // Variable global para almacenar el modo de lectura del ADC (interno, externo, etc.).

/**
 * @brief Variable utilizada para indicar el canal que se visualizará en el vúmetro.
 */
uint8_t currentChannel; // Variable global para almacenar el canal del ADC que se está visualizando.

/**
 * @brief Variable utilizada para indicar la cantidad de muestras por segundos actual.
 */
uint8_t current_kSPS; // Variable global para almacenar la frecuencia de muestreo actual en miles de muestras por segundo (kSPS).

uint8_t i = 0; // Variable global de contador de uso general.

bool signal = true; // Variable global para controlar el estado de la señal cuadrada (alta o baja).


/**
 * @brief Inicializar el ADS131E08 y enviar mensaje de bienvenida.
 */
void Funcionamiento_Init()
{
    // Inicializar ADS131E08
    ADS131E08_signalDown(); // Configura las señales de control del ADS131E08 a un estado inicial bajo.
    ADS131E08_Init(); // Inicializa el ADS131E08.
    delayMs(50); // Espera 50 milisegundos para permitir que el ADC se estabilice.
    ADS131E08_defaultConfig(); // Configura el ADS131E08 con los valores predeterminados.
    estado = 0; // Establece el estado inicial del programa a 0 (menú principal).
    currentMode = 0; // Establece el modo de lectura inicial.
    currentChannel = 5; // Establece el canal inicial.
    current_kSPS = 6; // Establece la frecuencia de muestreo inicial.
    is_running = FALSE; // Establece el estado de adquisición a FALSE (no adquiriendo datos).
    GPIO_stopped(currentChannel); // Actualiza la visualización del vúmetro para el canal inicial.
}


/**
 * @brief Funcionamiento general del sistema.
 */
void Funcionamiento_Menu()
{
	if(!is_running)  // Si el ADC no está en modo de adquisición:
	{
		switch (estado)  // Ejecuta la lógica del menú basada en el estado actual.
		{
         case 0:  // Estado: STOPPED (Menú principal)
         {
            if (getPulsador(BOARD_TEC_1)) {  // Si se presiona el pulsador TEC1:
                  GPIO_start(currentChannel);  // Inicia la visualización de los LEDs para el canal actual.
                  is_running = 1;  // Establece el estado de adquisición a TRUE.
                  ADS131E08_startADS();  // Inicia la adquisición de datos del ADS131E08.
            }
            if (getPulsador(BOARD_TEC_2)) {  // Si se presiona el pulsador TEC2:
               GPIO_selectChannel(currentChannel);  // Actualiza la visualización de los LEDs con el canal actual.
               estado = 1;  // Cambia al estado de selección de canal.
            }
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
               GPIO_select_kSPS(current_kSPS);  // Actualiza la visualización de los LEDs con la frecuencia de muestreo actual.
               estado = 2;  // Cambia al estado de selección de frecuencia de muestreo.
            }
            if (getPulsador(BOARD_TEC_4))  // Si se presiona el pulsador TEC4:
            {
               GPIO_selectMode(currentMode);  // Actualiza la visualización de los LEDs con el modo de lectura actual.
               estado = 3;  // Cambia al estado de selección de modo de lectura.
            }
            break;
         }
         case 1:  // Estado: SELECT CHANNEL (Selección de canal)
        {
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
               currentChannel = currentChannel - 1;  // Decrementa el canal actual.
               if (currentChannel == 4)  // Si llegó a la dirección '0x04' (Los canales empiezan de la dirección '0x05' en adelante):
               {
                  currentChannel = 12;  // Establece el canal actual al límite superior (Dirección 0x12).
               }
               GPIO_selectChannel(currentChannel);  // Actualiza la visualización de los LEDs con el canal actual.
            }
            if (getPulsador(BOARD_TEC_4))  // Si se presiona el pulsador TEC4:
            {
               currentChannel = currentChannel + 1;  // Incrementa el canal actual.
               if (currentChannel == 13)  // Si llegó a la dirección '0x13' (Los canales terminan en la dirección '0x12'):
               {
                  currentChannel = 5;  // Establece el canal actual al límite inferior (Canal 1 = Direccion 0x05).
               }
               GPIO_selectChannel(currentChannel);  // Actualiza la visualización de los LEDs con el canal actual.
            }
            if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
            {
               GPIO_stopped(currentChannel);  // Actualiza la visualización de los LEDs para el canal actual.
               ADS131E08_selectChannel(currentChannel);  // Selecciona el canal actual en el ADS131E08.
               estado = 0;  // Vuelve al estado del menú principal.
               max = 0x000000;  // Reinicia el valor máximo.
               min = 0x7FFFFF;  // Reinicia el valor mínimo.
            }
            break;
         }
         case 2:  // Estado: SELECT kSPS (Selección de frecuencia de muestreo)
        {
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
               current_kSPS++;  // Incrementa la frecuencia de muestreo actual.
               if (current_kSPS == 7)  // Si llegó al valor 7 o límite superior (Las configuraciones de tasa de muestreo van de 0 a 6, donde 0 es 64 kSPS y 6 es 1 kSPS):
               {
                  current_kSPS = 2;  // Establece la frecuencia de muestreo actual a 2 o límite inferior (En nuestro caso, la frecuencia de muestreo más alta es 16 kSPS, que equivale a 2 en la tabla de configuraciones de tasa de muestreo).
               }
               GPIO_select_kSPS(current_kSPS);  // Actualiza la visualización de los LEDs con la frecuencia de muestreo actual.
            }
            if (getPulsador(BOARD_TEC_4))  // Si se presiona el pulsador TEC4:
            {
               current_kSPS--;  // Decrementa la frecuencia de muestreo actual.
               if (current_kSPS == 1)  // Si se llegó al valor 1 o límite inferior (Las configuraciones de tasa de muestreo van de 0 a 6, donde 0 es 64 kSPS y 6 es 1 kSPS, pero en nuestro caso el mínimo valor es 2 que equivale a una frecuencia de muestreo de 16 kSPS):
               {
                  current_kSPS = 6;  // Establece la frecuencia de muestreo actual a 6 o límite superior (Equivalente a 1 kSPS según la tabla de configuraciones de tasa de muestreo).
               }
               GPIO_select_kSPS(current_kSPS);  // Actualiza la visualización de los LEDs con la frecuencia de muestreo actual.
            }
            if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
            {
               GPIO_stopped(currentChannel);  // Actualiza la visualización de los LEDs para el canal actual.
               ADS131E08_selectkSPS(current_kSPS);  // Selecciona la frecuencia de muestreo actual en el ADS131E08.
               estado = 0;  // Vuelve al estado del menú principal.
            }
            break;
         }
         case 3:  // Estado: SELECT MODE (Selección de modo de lectura)
        {
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
                currentMode++;  // Incrementa el modo de lectura actual.
                if (currentMode == 2)  // Si el modo de lectura actual es 2 o límite superior (0 = Modo de prueba (TEST), 1 = Modo de señal externa):
                {
                    currentMode = 0;  // Establece el modo de lectura actual al límite inferior (0 = Modo de prueba (TEST)).
                }
                GPIO_selectMode(currentMode);  // Actualiza la visualización de los LEDs con el modo de lectura actual.
            }
            if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
            {
                GPIO_stopped(currentChannel);  // Actualiza la visualización de los LEDs para el canal actual.
                ADS131E08_selectMode(currentMode, currentChannel);  // Selecciona el modo de lectura actual en el ADS131E08.
                estado = 0;  // Vuelve al estado del menú principal.
            }
            break;
      }
   }
	else  // Si el ADC está en modo de adquisición:
   {
      while (!(ADS131E08_isDataAvailable()));  // Espera hasta que haya datos disponibles del ADS131E08.
        ADS131E08_getChannelData(&sampleCnt, channelData);  // Obtiene los datos del ADS131E08 y los almacena en channelData.
        UART_Send(&channelData[currentChannel - 5], 4);  // Envía los datos del canal actual por UART.
        GPIO_getSignal(channelData[currentChannel - 5]);  // Actualiza la visualización de los LEDs con los datos del canal actual.
        if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
        {
            GPIO_stopped(currentChannel);  // Actualiza la visualización del vúmetro para el canal actual.
            is_running = 0;  // Establece el estado de adquisición a FALSE.
            estado = 0;  // Vuelve al estado del menú principal.
            ADS131E08_stopADS();  // Detiene la adquisición de datos del ADS131E08.
        }
    }
}


/**
 * @brief Detecta si un pulsador ha sido presionado y realiza antirrebote.
 * @param pulsador Número del pulsador a verificar.
 * @return TRUE si el pulsador fue presionado, FALSE en caso contrario.
 */
bool getPulsador(uint8_t pulsador)
{
   if (!(Board_TEC_GetStatus(pulsador))) // Si el pulsador está presionado:
   {
      delayMs(20); // Espera 20 milisegundos para el antirrebote.
      while (!(Board_TEC_GetStatus(pulsador))); // Espera hasta que se suelte el pulsador.
      delayMs(20); // Espera 20 milisegundos para el antirrebote.
      return true; // Devuelve TRUE (pulsador presionado).
   }
   return false; // Devuelve FALSE (pulsador no presionado).
}


/**
 * @brief Manejador de la interrupción del SysTick.
 * Incrementa el contador de ticks del SysTick.
 */
void SysTick_Handler(void)
{
   tick_ct++; // Incrementa el contador de ticks del SysTick.
}


/**
 * @brief Genera un retardo en milisegundos utilizando el SysTick.
 * @param tk Tiempo de retardo en milisegundos.
 */
void delayMs(uint32_t tk)
{
   SysTick_Config(SystemCoreClock / 1000); // Configura el SysTick para generar interrupciones cada 1 milisegundo.
   uint32_t end = tick_ct + tk; // Calcula el tiempo de finalización del retardo.
   while (tick_ct < end) // Espera hasta que se alcance el tiempo de finalización.
      __WFI(); // Entra en modo de bajo consumo mientras espera.
}


/**
 * @brief Genera un retardo en microsegundos utilizando el SysTick.
 * @param tk Tiempo de retardo en microsegundos.
 */
void delayUs(uint32_t tk)
{
   SysTick_Config(SystemCoreClock / 1000000); // Configura el SysTick para generar interrupciones cada 1 microsegundo.
   uint32_t end = tick_ct + tk; // Calcula el tiempo de finalización del retardo.
   while (tick_ct < end) // Espera hasta que se alcance el tiempo de finalización.
      __WFI(); // Entra en modo de bajo consumo mientras espera.
}
