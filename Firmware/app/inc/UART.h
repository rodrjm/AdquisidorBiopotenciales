/*
 * UART.h
 */

#ifndef UART_H_
#define UART_H_


#include "lpc_types.h"


/** @defgroup Libreria UART
 *  @ingroup "Adquisidor de senales biopotenciales"
 *  Driver para controlar el protocolo UART
 */


/** 
 * Definiciones y declaraciones
 */
#define UART_SELECTION 	LPC_USART2  // UART 2 para el FTDI de la EDU CIAA
#define IRQ_SELECTION 	UART0_IRQn
#define HANDLER_NAME 	UART0_IRQHandler

#define BAUD_RATE	256000
/* Tamanos de los buffers para enviar y recibir datos */
#define UART_SRB_SIZE 128	/* Enviar */
#define UART_RRB_SIZE 32	/* Recibir */


/**
 *  @brief Configuracion inicial e inicializacion de UART
 */
void UART_setup();


/** 
 * @brief Desinicializacion de UART
 */
void UART_DeInit ();


/**
 * @brief Enviar datos por UART
 * @param data[] Arreglo de datos a enviar
 * @param numByte Numero de bytes a enviar  
 */
void UART_Send(int data[], int numBytes);


/**
 * @brief Recibir datos por UART
 * @param data[] Arreglo de datos a recibir
 * @param numByte Numero de bytes a recibir 
 */
int UART_Receive(uint8_t data[], int bytes);


/**
 * @brief Leer un byte
 * @return Byte recibido
 */
uint8_t UART_ReadByte();


/**
 * @brief Indica si hay nuevos datos para leer
 * @return TRUE si hay un nuevo byte en el buffer UART, FALSE si no
 */
bool UART_available();


#endif /* UART_H_ */