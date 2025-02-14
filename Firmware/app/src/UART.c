/*
 	 * UART.c
*/


#include "UART.h"
#include "chip.h"


/**
 	 *  @brief Configuracion inicial e inicializacion de UART
*/
void UART_Init()
{
	Chip_UART_Init(UART_SELECTION);
	Chip_UART_SetBaud(UART_SELECTION, BAUD_RATE);
   	Chip_UART_SetupFIFOS(UART_SELECTION, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
   	Chip_UART_TXEnable(UART_SELECTION);
    Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
	Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */
}


/** 
 	 * @brief Desinicializacion de UART
*/
void UART_DeInit ()
{
	Chip_UART_DeInit(UART_SELECTION);
}


/**
 	 * @brief Enviar datos por UART
 	 * @param data[] Arreglo de datos a enviar
 	 * @param numByte Numero de bytes a enviar
*/
void UART_Send(uint32_t data[], int numBytes)
{
	Chip_UART_SendBlocking(UART_SELECTION, data, numBytes);
}


/**
 	 * @brief Recibir datos por UART
 	 * @param data[] Arreglo de datos a recibir
 	 * @param numByte Numero de bytes a recibir
*/
int UART_Receive(uint8_t data[], int numBytes)
{	
   Chip_UART_Read(UART_SELECTION, data, numBytes);
}


/**
 	 * @brief Leer un byte
 	 * @return Byte recibido
*/
uint8_t UART_ReadByte()
{
	uint8_t byte;
	byte = Chip_UART_ReadByte(UART_SELECTION);
	return byte;
}


/**
 	 * @brief Indica si hay nuevos datos para leer
 	 * @return TRUE si hay un nuevo byte en el buffer UART, FALSE si no
*/
bool UART_available()
{
	bool available = false;
	available = (Chip_UART_ReadLineStatus(UART_SELECTION) & UART_LSR_RDR);
	return available;
}
