/*
 * UART.h
 *
 * Descripci�n: Archivo de encabezado para la comunicaci�n UART en la placa EDU-CIAA-NXP.
 * Define constantes, tipos de datos y prototipos de funciones para el m�dulo UART.
 */


#ifndef UART_H_
#define UART_H_


#include "lpc_types.h" // Incluye el archivo de encabezado lpc_types.h, que define tipos de datos est�ndar para microcontroladores LPC.


/**
 * @defgroup Libreria UART
 * @ingroup "Adquisidor de senales biopotenciales"
 * Driver para controlar el protocolo UART.
 */


/**
 * Definiciones y declaraciones.
 */
#define UART_SELECTION  LPC_USART2   // Selecci�n del perif�rico UART2 para el FTDI de la EDU-CIAA-NXP.
#define IRQ_SELECTION   UART2_IRQn   // Selecci�n de la interrupci�n UART2.
#define HANDLER_NAME    UART2_IRQHandler // Nombre del manejador de interrupciones UART2.

#define BAUD_RATE       588000       // Velocidad de baudios para la comunicaci�n UART.

/* Tama�os de los buffers para enviar y recibir datos. */
#define UART_SRB_SIZE   128          // Tama�o del buffer de env�o (128 bytes).
#define UART_RRB_SIZE   32           // Tama�o del buffer de recepci�n (32 bytes).


/**
 * @brief Configuraci�n inicial e inicializaci�n de UART.
 *
 * Prototipo de la funci�n UART_Init(), que configura e inicializa el puerto UART.
 */
void UART_Init();


/**
 * @brief Desinicializaci�n de UART.
 *
 * Prototipo de la funci�n UART_DeInit(), que desinicializa el puerto UART.
 */
void UART_DeInit();


/**
 * @brief Enviar datos por UART.
 *
 * Prototipo de la funci�n UART_Send(), que env�a un arreglo de datos a trav�s del puerto UART.
 *
 * @param data[] Arreglo de datos a enviar (uint32_t).
 * @param numBytes N�mero de bytes a enviar (int).
 */
void UART_Send(uint32_t data[], int numBytes);


/**
 * @brief Recibir datos por UART.
 *
 * Prototipo de la funci�n UART_Receive(), que recibe un arreglo de datos a trav�s del puerto UART.
 *
 * @param data[] Arreglo de datos para almacenar los bytes recibidos (uint8_t).
 * @param bytes N�mero de bytes a recibir (int).
 * @return N�mero de bytes realmente recibidos.
 */
int UART_Receive(uint8_t data[], int bytes);


/**
 * @brief Leer un byte desde el UART.
 *
 * Prototipo de la funci�n UART_ReadByte(), que lee un �nico byte desde el puerto UART.
 *
 * @return Byte recibido (uint8_t).
 */
uint8_t UART_ReadByte();


/**
 * @brief Indica si hay nuevos datos disponibles para leer en el buffer UART.
 *
 * Prototipo de la funci�n UART_available(), que verifica si hay un nuevo byte disponible en el buffer de recepci�n del UART.
 *
 * @return true si hay un nuevo byte disponible, false si no.
 */
bool UART_available();


#endif /* UART_H_ */
