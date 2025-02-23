/*
 * adquisidorBiopotenciales.c
 */


#include "adquisidorBiopotenciales.h" // Incluye el encabezado del archivo "adquisidorBiopotenciales.h".
#include "board.h" // Incluye el encabezado para la inicialización de la placa.
#include "UART.h" // Incluye el encabezado para la comunicación UART.
#include "ADS131E08.h" // Incluye el encabezado para el manejo del ADS131E08.
#include "funcionamiento.h" // Incluye el encabezado para la lógica de funcionamiento del sistema.
#include "SPI.h" // Incluye el encabezado para la comunicación SPI.


/*
 * @brief Función de inicialización del hardware.
 */
static void InitHardware(void); // Declara la función estática InitHardware.


/**
 * @brief Inicializa el hardware necesario para el sistema.
 */
static void InitHardware(void)
{
   Board_Init(); // Inicializa la placa (configura pines, periféricos, etc.).
   SystemCoreClockUpdate(); // Actualiza la variable SystemCoreClock con la frecuencia del reloj del sistema.
   SysTick_Config(SystemCoreClock / 1000); // Configura el SysTick para generar interrupciones cada 1 milisegundo.
   GPIO_Init(); // Inicializa los GPIO (configura pines como entradas o salidas).
   SPI_Init(); // Inicializa el periférico SPI.
   SPI_Setup(); // Configura los parámetros de la comunicación SPI (velocidad, modo, etc.).
   UART_Init(); // Inicializa el periférico UART para la comunicación serial.
}


/**
 * @brief Función principal del programa.
 * @return Retorna 0 al finalizar la ejecución (aunque este programa no termina).
 */
int main(void)
{
   InitHardware(); // Llama a la función para inicializar el hardware.
   delayMs(500); // Espera 500 milisegundos para permitir que el hardware se estabilice.
   Board_LED_Toggle(1); // Invierte el estado del LED 1 (enciende si está apagado, apaga si está encendido).
   delayMs(500); // Espera 500 milisegundos.
   Board_LED_Toggle(1); // Invierte nuevamente el estado del LED 1.

   Funcionamiento_Init(); // Inicializa la lógica de funcionamiento del sistema.
   while (1) // Bucle infinito para la ejecución continua del programa.
   {
      Funcionamiento_Menu(); // Llama a la función principal de la lógica de funcionamiento.
   }
}
