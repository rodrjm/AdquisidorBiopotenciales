/*
 * SPI.h
 *
 * Descripci�n: Archivo de encabezado para la comunicaci�n SPI en la placa EDU-CIAA-NXP.
 * Define constantes, tipos de datos y prototipos de funciones para el m�dulo SPI.
 */


#ifndef SPI_H_
#define SPI_H_


#include "lpc_types.h" // Incluye el archivo de encabezado lpc_types.h, que define tipos de datos est�ndar para microcontroladores LPC.


/**
 * @defgroup Libreria SPI
 * @ingroup "Adquisidor de se�ales biopotenciales"
 * Driver para controlar el protocolo SPI.
 */


/**
 * Definiciones y declaraciones.
 */
#define LPC_SSP LPC_SSP1 // Selecci�n del perif�rico SPI1.


/**
 * @brief Inicializaci�n del m�dulo SPI.
 *
 * Prototipo de la funci�n SPI_Init(), que inicializa el puerto SPI.
 */
void SPI_Init();


/**
 * @brief Desinicializaci�n del m�dulo SPI.
 *
 * Prototipo de la funci�n SPI_deInit(), que desinicializa el puerto SPI.
 */
void SPI_deInit();


/**
 * @brief Configuraci�n del formato y los datos del m�dulo SPI.
 *
 * Prototipo de la funci�n SPI_Setup(), que configura el formato de la trama, el modo de reloj y la velocidad de comunicaci�n del m�dulo SPI.
 */
void SPI_Setup();


/**
 * @brief Env�a y recibe un byte a trav�s de SPI.
 *
 * Prototipo de la funci�n SPI_transfer(), que env�a y recibe un byte simult�neamente a trav�s del puerto SPI.
 *
 * @param out Byte a enviar (uint8_t).
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_transfer(uint8_t out);


/**
 * @brief Env�a un byte a trav�s de SPI.
 *
 * Prototipo de la funci�n SPI_Send(), que env�a un byte a trav�s del puerto SPI.
 *
 * @param data Byte a enviar (uint8_t).
 */
void SPI_Send(uint8_t data);


/**
 * @brief Recibe un byte a trav�s de SPI.
 *
 * Prototipo de la funci�n SPI_Receive(), que recibe un byte a trav�s del puerto SPI.
 *
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_Receive();


#endif /* SPI_H_ */
