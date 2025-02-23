/*
 * UART.c
 *
 * Descripción: Implementación de funciones para la comunicación UART en la placa EDU-CIAA-NXP.
 * Este módulo proporciona funciones para inicializar, desinicializar, enviar, recibir y verificar datos disponibles en el puerto UART.
 */


#include "UART.h" // Incluye el archivo de encabezado UART.h, que contiene las definiciones de las funciones y constantes.
#include "chip.h" // Incluye el archivo de encabezado chip.h, que proporciona acceso a las funciones de bajo nivel del microcontrolador.


/**
 * @brief Configuración inicial e inicialización de UART.
 *
 * Esta función configura e inicializa el puerto UART seleccionado (UART_SELECTION) con los parámetros especificados.
 *
 * Pasos:
 * 1. Inicializa el módulo UART utilizando la función Chip_UART_Init().
 * 2. Establece la velocidad de baudios utilizando la función Chip_UART_SetBaud().
 * 3. Configura las FIFOs del UART para habilitarlas y establecer el nivel de trigger.
 * 4. Habilita la transmisión de datos utilizando la función Chip_UART_TXEnable().
 * 5. Configura los pines P7_1 y P7_2 para las funciones UART2_TXD y UART2_RXD, respectivamente.
 *
 * @note Las constantes UART_SELECTION y BAUD_RATE deben estar definidas en el archivo UART.h.
 */
void UART_Init()
{
   Chip_UART_Init(UART_SELECTION); // Inicializa el módulo UART.
   Chip_UART_SetBaud(UART_SELECTION, BAUD_RATE); // Establece la velocidad de baudios.
   Chip_UART_SetupFIFOS(UART_SELECTION, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0); // Configura las FIFOs del UART.
   Chip_UART_TXEnable(UART_SELECTION); // Habilita la transmisión de datos.
   Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6); // Configura el pin P7_1 para UART2_TXD.
   Chip_SCU_PinMux(7, 2, MD_PLN | MD_EZI | MD_ZI, FUNC6); // Configura el pin P7_2 para UART2_RXD.
}


/**
 * @brief Desinicialización de UART.
 *
 * Esta función desinicializa el puerto UART seleccionado, liberando los recursos utilizados.
 */
void UART_DeInit()
{
   Chip_UART_DeInit(UART_SELECTION); // Desinicializa el módulo UART.
}


/**
 * @brief Enviar datos por UART.
 *
 * Esta función envía un arreglo de datos a través del puerto UART seleccionado.
 *
 * @param data[] Arreglo de datos a enviar (uint32_t).
 * @param numBytes Número de bytes a enviar (int).
 */
void UART_Send(uint32_t data[], int numBytes)
{
   Chip_UART_SendBlocking(UART_SELECTION, data, numBytes); // Envía los datos de forma bloqueante.
}


/**
 * @brief Recibir datos por UART.
 *
 * Esta función recibe un arreglo de datos a través del puerto UART seleccionado.
 *
 * @param data[] Arreglo de datos para almacenar los bytes recibidos (uint8_t).
 * @param numBytes Número de bytes a recibir (int).
 * @return Número de bytes realmente recibidos.
 */
int UART_Receive(uint8_t data[], int numBytes)
{
   return Chip_UART_Read(UART_SELECTION, data, numBytes); // Recibe los datos.
}


/**
 * @brief Leer un byte desde el UART.
 *
 * Esta función lee un único byte desde el puerto UART seleccionado.
 *
 * @return Byte recibido (uint8_t).
 */
uint8_t UART_ReadByte()
{
    return Chip_UART_ReadByte(UART_SELECTION); // Lee un byte del UART.
}


/**
 * @brief Indica si hay nuevos datos disponibles para leer en el buffer UART.
 *
 * Esta función verifica si hay un nuevo byte disponible en el buffer de recepción del UART.
 *
 * @return true si hay un nuevo byte disponible, false si no.
 */
bool UART_available()
{
    return (Chip_UART_ReadLineStatus(UART_SELECTION) & UART_LSR_RDR); // Verifica el estado del buffer de recepción.
}
