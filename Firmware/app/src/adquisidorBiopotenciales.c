/*
 * adquisidorBiopotenciales.c
 */


#include "adquisidorBiopotenciales.h" // Incluye el encabezado del archivo "adquisidorBiopotenciales.h".
#include "board.h" // Incluye el encabezado para la inicializaci�n de la placa.
#include "UART.h" // Incluye el encabezado para la comunicaci�n UART.
#include "ADS131E08.h" // Incluye el encabezado para el manejo del ADS131E08.
#include "funcionamiento.h" // Incluye el encabezado para la l�gica de funcionamiento del sistema.
#include "SPI.h" // Incluye el encabezado para la comunicaci�n SPI.


/*
 * @brief Funci�n de inicializaci�n del hardware.
 */
static void InitHardware(void); // Declara la funci�n est�tica InitHardware.


/**
 * @brief Inicializa el hardware necesario para el sistema.
 */
static void InitHardware(void)
{
   Board_Init(); // Inicializa la placa (configura pines, perif�ricos, etc.).
   SystemCoreClockUpdate(); // Actualiza la variable SystemCoreClock con la frecuencia del reloj del sistema.
   SysTick_Config(SystemCoreClock / 1000); // Configura el SysTick para generar interrupciones cada 1 milisegundo.
   GPIO_Init(); // Inicializa los GPIO (configura pines como entradas o salidas).
   SPI_Init(); // Inicializa el perif�rico SPI.
   SPI_Setup(); // Configura los par�metros de la comunicaci�n SPI (velocidad, modo, etc.).
   UART_Init(); // Inicializa el perif�rico UART para la comunicaci�n serial.
}


/**
 * @brief Funci�n principal del programa.
 * @return Retorna 0 al finalizar la ejecuci�n (aunque este programa no termina).
 */
int main(void)
{
   InitHardware(); // Llama a la funci�n para inicializar el hardware.
   delayMs(500); // Espera 500 milisegundos para permitir que el hardware se estabilice.
   Board_LED_Toggle(1); // Invierte el estado del LED 1 (enciende si est� apagado, apaga si est� encendido).
   delayMs(500); // Espera 500 milisegundos.
   Board_LED_Toggle(1); // Invierte nuevamente el estado del LED 1.

   Funcionamiento_Init(); // Inicializa la l�gica de funcionamiento del sistema.
   while (1) // Bucle infinito para la ejecuci�n continua del programa.
   {
      Funcionamiento_Menu(); // Llama a la funci�n principal de la l�gica de funcionamiento.
   }
}
