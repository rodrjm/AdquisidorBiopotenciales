#include "funcionamiento.h" // Incluye el encabezado del archivo "funcionamiento.h" que contiene declaraciones de funciones y variables.
#include "UART.h" // Incluye el encabezado para la comunicaci�n UART (Universal Asynchronous Receiver-Transmitter).
#include "ADS131E08.h" // Incluye el encabezado para el manejo del ADS131E08 (convertidor anal�gico a digital).
#include "GPIO.h" // Incluye el encabezado para el manejo de los GPIO (General Purpose Input/Output).
#include "board_api.h" // Incluye el encabezado para la API de la placa (espec�fica de la placa utilizada).
#include "chip.h" // Incluye el encabezado para las funciones espec�ficas del chip.
#include <stdlib.h> // Incluye la biblioteca est�ndar de C para funciones de utilidad general.
#include "math.h" // Incluye la biblioteca matem�tica de C para funciones matem�ticas.

#define SAMPLE_RATE 1000  // Define la frecuencia de muestreo a 1000 muestras por segundo (1 kSPS).
#define AMPLITUDE_MV 3    // Define la amplitud m�xima de la se�al en milivoltios (3 mV).
#define VREF_MV 2400      // Define el voltaje de referencia del ADC en milivoltios (2400 mV).
#define RESOLUTION 24     // Define la resoluci�n del ADC en 24 bits.
#define FREQUENCY 1000    // Define la frecuencia de la se�al de prueba en hercios (1000 Hz).
#define CLOCK_CYCLES_PER_STATE 1000 // Define el n�mero de ciclos de reloj por estado (para retardos).

#define SAMPLES_PER_CYCLE 1000    // Define el n�mero de muestras por ciclo de la se�al triangular.

uint32_t max = 0x000000; // Variable global para almacenar el valor m�ximo le�do por el ADC.
uint32_t min = 0x7FFFFF; // Variable global para almacenar el valor m�nimo le�do por el ADC.

/**
 * @brief Bandera que indica si el ADS131E08 est� adquiriendo datos o no.
 */
bool is_running = FALSE; // Variable global para indicar si el ADC est� en modo de adquisici�n (TRUE) o no (FALSE).

/**
 * @brief Variable utilizada para el control de los diferentes estados del programa.
 */
uint8_t estado; // Variable global para controlar el estado actual del programa (men�, adquisici�n, etc.).

/**
 * @brief Variable utilizada para indicar el modo en el cual se leen las se�ales desde el sensor.
 */
uint8_t currentMode; // Variable global para almacenar el modo de lectura del ADC (interno, externo, etc.).

/**
 * @brief Variable utilizada para indicar el canal que se visualizar� en el v�metro.
 */
uint8_t currentChannel; // Variable global para almacenar el canal del ADC que se est� visualizando.

/**
 * @brief Variable utilizada para indicar la cantidad de muestras por segundos actual.
 */
uint8_t current_kSPS; // Variable global para almacenar la frecuencia de muestreo actual en miles de muestras por segundo (kSPS).

uint8_t i = 0; // Variable global de contador de uso general.

bool signal = true; // Variable global para controlar el estado de la se�al cuadrada (alta o baja).


/**
 * @brief Inicializar el ADS131E08 y enviar mensaje de bienvenida.
 */
void Funcionamiento_Init()
{
    // Inicializar ADS131E08
    ADS131E08_signalDown(); // Configura las se�ales de control del ADS131E08 a un estado inicial bajo.
    ADS131E08_Init(); // Inicializa el ADS131E08.
    delayMs(50); // Espera 50 milisegundos para permitir que el ADC se estabilice.
    ADS131E08_defaultConfig(); // Configura el ADS131E08 con los valores predeterminados.
    estado = 0; // Establece el estado inicial del programa a 0 (men� principal).
    currentMode = 0; // Establece el modo de lectura inicial.
    currentChannel = 5; // Establece el canal inicial.
    current_kSPS = 6; // Establece la frecuencia de muestreo inicial.
    is_running = FALSE; // Establece el estado de adquisici�n a FALSE (no adquiriendo datos).
    GPIO_stopped(currentChannel); // Actualiza la visualizaci�n del v�metro para el canal inicial.
}


/**
 * @brief Funcionamiento general del sistema.
 */
void Funcionamiento_Menu()
{
	if(!is_running)  // Si el ADC no est� en modo de adquisici�n:
	{
		switch (estado)  // Ejecuta la l�gica del men� basada en el estado actual.
		{
         case 0:  // Estado: STOPPED (Men� principal)
         {
            if (getPulsador(BOARD_TEC_1)) {  // Si se presiona el pulsador TEC1:
                  GPIO_start(currentChannel);  // Inicia la visualizaci�n de los LEDs para el canal actual.
                  is_running = 1;  // Establece el estado de adquisici�n a TRUE.
                  ADS131E08_startADS();  // Inicia la adquisici�n de datos del ADS131E08.
            }
            if (getPulsador(BOARD_TEC_2)) {  // Si se presiona el pulsador TEC2:
               GPIO_selectChannel(currentChannel);  // Actualiza la visualizaci�n de los LEDs con el canal actual.
               estado = 1;  // Cambia al estado de selecci�n de canal.
            }
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
               GPIO_select_kSPS(current_kSPS);  // Actualiza la visualizaci�n de los LEDs con la frecuencia de muestreo actual.
               estado = 2;  // Cambia al estado de selecci�n de frecuencia de muestreo.
            }
            if (getPulsador(BOARD_TEC_4))  // Si se presiona el pulsador TEC4:
            {
               GPIO_selectMode(currentMode);  // Actualiza la visualizaci�n de los LEDs con el modo de lectura actual.
               estado = 3;  // Cambia al estado de selecci�n de modo de lectura.
            }
            break;
         }
         case 1:  // Estado: SELECT CHANNEL (Selecci�n de canal)
        {
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
               currentChannel = currentChannel - 1;  // Decrementa el canal actual.
               if (currentChannel == 4)  // Si lleg� a la direcci�n '0x04' (Los canales empiezan de la direcci�n '0x05' en adelante):
               {
                  currentChannel = 12;  // Establece el canal actual al l�mite superior (Direcci�n 0x12).
               }
               GPIO_selectChannel(currentChannel);  // Actualiza la visualizaci�n de los LEDs con el canal actual.
            }
            if (getPulsador(BOARD_TEC_4))  // Si se presiona el pulsador TEC4:
            {
               currentChannel = currentChannel + 1;  // Incrementa el canal actual.
               if (currentChannel == 13)  // Si lleg� a la direcci�n '0x13' (Los canales terminan en la direcci�n '0x12'):
               {
                  currentChannel = 5;  // Establece el canal actual al l�mite inferior (Canal 1 = Direccion 0x05).
               }
               GPIO_selectChannel(currentChannel);  // Actualiza la visualizaci�n de los LEDs con el canal actual.
            }
            if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
            {
               GPIO_stopped(currentChannel);  // Actualiza la visualizaci�n de los LEDs para el canal actual.
               ADS131E08_selectChannel(currentChannel);  // Selecciona el canal actual en el ADS131E08.
               estado = 0;  // Vuelve al estado del men� principal.
               max = 0x000000;  // Reinicia el valor m�ximo.
               min = 0x7FFFFF;  // Reinicia el valor m�nimo.
            }
            break;
         }
         case 2:  // Estado: SELECT kSPS (Selecci�n de frecuencia de muestreo)
        {
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
               current_kSPS++;  // Incrementa la frecuencia de muestreo actual.
               if (current_kSPS == 7)  // Si lleg� al valor 7 o l�mite superior (Las configuraciones de tasa de muestreo van de 0 a 6, donde 0 es 64 kSPS y 6 es 1 kSPS):
               {
                  current_kSPS = 2;  // Establece la frecuencia de muestreo actual a 2 o l�mite inferior (En nuestro caso, la frecuencia de muestreo m�s alta es 16 kSPS, que equivale a 2 en la tabla de configuraciones de tasa de muestreo).
               }
               GPIO_select_kSPS(current_kSPS);  // Actualiza la visualizaci�n de los LEDs con la frecuencia de muestreo actual.
            }
            if (getPulsador(BOARD_TEC_4))  // Si se presiona el pulsador TEC4:
            {
               current_kSPS--;  // Decrementa la frecuencia de muestreo actual.
               if (current_kSPS == 1)  // Si se lleg� al valor 1 o l�mite inferior (Las configuraciones de tasa de muestreo van de 0 a 6, donde 0 es 64 kSPS y 6 es 1 kSPS, pero en nuestro caso el m�nimo valor es 2 que equivale a una frecuencia de muestreo de 16 kSPS):
               {
                  current_kSPS = 6;  // Establece la frecuencia de muestreo actual a 6 o l�mite superior (Equivalente a 1 kSPS seg�n la tabla de configuraciones de tasa de muestreo).
               }
               GPIO_select_kSPS(current_kSPS);  // Actualiza la visualizaci�n de los LEDs con la frecuencia de muestreo actual.
            }
            if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
            {
               GPIO_stopped(currentChannel);  // Actualiza la visualizaci�n de los LEDs para el canal actual.
               ADS131E08_selectkSPS(current_kSPS);  // Selecciona la frecuencia de muestreo actual en el ADS131E08.
               estado = 0;  // Vuelve al estado del men� principal.
            }
            break;
         }
         case 3:  // Estado: SELECT MODE (Selecci�n de modo de lectura)
        {
            if (getPulsador(BOARD_TEC_3))  // Si se presiona el pulsador TEC3:
            {
                currentMode++;  // Incrementa el modo de lectura actual.
                if (currentMode == 2)  // Si el modo de lectura actual es 2 o l�mite superior (0 = Modo de prueba (TEST), 1 = Modo de se�al externa):
                {
                    currentMode = 0;  // Establece el modo de lectura actual al l�mite inferior (0 = Modo de prueba (TEST)).
                }
                GPIO_selectMode(currentMode);  // Actualiza la visualizaci�n de los LEDs con el modo de lectura actual.
            }
            if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
            {
                GPIO_stopped(currentChannel);  // Actualiza la visualizaci�n de los LEDs para el canal actual.
                ADS131E08_selectMode(currentMode, currentChannel);  // Selecciona el modo de lectura actual en el ADS131E08.
                estado = 0;  // Vuelve al estado del men� principal.
            }
            break;
      }
   }
	else  // Si el ADC est� en modo de adquisici�n:
   {
      while (!(ADS131E08_isDataAvailable()));  // Espera hasta que haya datos disponibles del ADS131E08.
        ADS131E08_getChannelData(&sampleCnt, channelData);  // Obtiene los datos del ADS131E08 y los almacena en channelData.
        UART_Send(&channelData[currentChannel - 5], 4);  // Env�a los datos del canal actual por UART.
        GPIO_getSignal(channelData[currentChannel - 5]);  // Actualiza la visualizaci�n de los LEDs con los datos del canal actual.
        if (getPulsador(BOARD_TEC_1))  // Si se presiona el pulsador TEC1:
        {
            GPIO_stopped(currentChannel);  // Actualiza la visualizaci�n del v�metro para el canal actual.
            is_running = 0;  // Establece el estado de adquisici�n a FALSE.
            estado = 0;  // Vuelve al estado del men� principal.
            ADS131E08_stopADS();  // Detiene la adquisici�n de datos del ADS131E08.
        }
    }
}


/**
 * @brief Detecta si un pulsador ha sido presionado y realiza antirrebote.
 * @param pulsador N�mero del pulsador a verificar.
 * @return TRUE si el pulsador fue presionado, FALSE en caso contrario.
 */
bool getPulsador(uint8_t pulsador)
{
   if (!(Board_TEC_GetStatus(pulsador))) // Si el pulsador est� presionado:
   {
      delayMs(20); // Espera 20 milisegundos para el antirrebote.
      while (!(Board_TEC_GetStatus(pulsador))); // Espera hasta que se suelte el pulsador.
      delayMs(20); // Espera 20 milisegundos para el antirrebote.
      return true; // Devuelve TRUE (pulsador presionado).
   }
   return false; // Devuelve FALSE (pulsador no presionado).
}


/**
 * @brief Manejador de la interrupci�n del SysTick.
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
   uint32_t end = tick_ct + tk; // Calcula el tiempo de finalizaci�n del retardo.
   while (tick_ct < end) // Espera hasta que se alcance el tiempo de finalizaci�n.
      __WFI(); // Entra en modo de bajo consumo mientras espera.
}


/**
 * @brief Genera un retardo en microsegundos utilizando el SysTick.
 * @param tk Tiempo de retardo en microsegundos.
 */
void delayUs(uint32_t tk)
{
   SysTick_Config(SystemCoreClock / 1000000); // Configura el SysTick para generar interrupciones cada 1 microsegundo.
   uint32_t end = tick_ct + tk; // Calcula el tiempo de finalizaci�n del retardo.
   while (tick_ct < end) // Espera hasta que se alcance el tiempo de finalizaci�n.
      __WFI(); // Entra en modo de bajo consumo mientras espera.
}
