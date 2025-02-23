/*
 * SPI.h
 *
 * Descripción: Archivo de encabezado para la comunicación SPI en la placa EDU-CIAA-NXP.
 * Define constantes, tipos de datos y prototipos de funciones para el módulo SPI.
 */


#ifndef SPI_H_
#define SPI_H_


#include "lpc_types.h" // Incluye el archivo de encabezado lpc_types.h, que define tipos de datos estándar para microcontroladores LPC.


/**
 * @defgroup Libreria SPI
 * @ingroup "Adquisidor de señales biopotenciales"
 * Driver para controlar el protocolo SPI.
 */


/**
 * Definiciones y declaraciones.
 */
#define LPC_SSP LPC_SSP1 // Selección del periférico SPI1.


/**
 * @brief Inicialización del módulo SPI.
 *
 * Prototipo de la función SPI_Init(), que inicializa el puerto SPI.
 */
void SPI_Init();


/**
 * @brief Desinicialización del módulo SPI.
 *
 * Prototipo de la función SPI_deInit(), que desinicializa el puerto SPI.
 */
void SPI_deInit();


/**
 * @brief Configuración del formato y los datos del módulo SPI.
 *
 * Prototipo de la función SPI_Setup(), que configura el formato de la trama, el modo de reloj y la velocidad de comunicación del módulo SPI.
 */
void SPI_Setup();


/**
 * @brief Envía y recibe un byte a través de SPI.
 *
 * Prototipo de la función SPI_transfer(), que envía y recibe un byte simultáneamente a través del puerto SPI.
 *
 * @param out Byte a enviar (uint8_t).
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_transfer(uint8_t out);


/**
 * @brief Envía un byte a través de SPI.
 *
 * Prototipo de la función SPI_Send(), que envía un byte a través del puerto SPI.
 *
 * @param data Byte a enviar (uint8_t).
 */
void SPI_Send(uint8_t data);


/**
 * @brief Recibe un byte a través de SPI.
 *
 * Prototipo de la función SPI_Receive(), que recibe un byte a través del puerto SPI.
 *
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_Receive();


#endif /* SPI_H_ */
