/*
 * SPI.h
 */

#ifndef SPI_H_
#define SPI_H_


#include "lpc_types.h"


/** @defgroup Libreria SPI
 *  @ingroup "Adquisidor de señales biopotenciales"
 *  Driver para controlar el protocolo SPI
 */


/** 
 * Definiciones y declaraciones
 */
#define LPC_SSP LPC_SSP1 // Modulo SPI que se utiliza


/**
 * @brief Inicializacion del modulo SPI
 */
void SPI_init();


/**
 * @brief Desinicializacion del modulo SPI
 */
void SPI_deInit();


/**
 * @brief Configuracion del formato y los datos del modulo SPI
 */
void SPI_setup();


/**
 * @brief Envia y recibe un byte a traves de SPI
 * @param out Byte a enviar
 * @return in Byte recibido
 */
uint8_t SPI_transfer(uint8_t out);

void SPI_Send(uint8_t data);
uint8_t SPI_Receive();


#endif /* SPI_H_ */