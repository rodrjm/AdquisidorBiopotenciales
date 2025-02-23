/*
 * SPI.c
 *
 * Descripción: Implementación de funciones para la comunicación SPI en la placa EDU-CIAA-NXP.
 * Este módulo proporciona funciones para inicializar, desinicializar, configurar, enviar y recibir datos a través del puerto SPI.
 */


#include "SPI.h"      // Incluye el archivo de encabezado SPI.h, que contiene las definiciones de las funciones y constantes.
#include "chip.h"     // Incluye el archivo de encabezado chip.h, que proporciona acceso a las funciones de bajo nivel del microcontrolador.
#include "UART.h"     // Incluye el archivo de encabezado UART.h (posiblemente para depuración o comunicación de errores).


/**
 * @brief Inicialización del módulo SPI.
 *
 * Esta función inicializa el módulo SPI seleccionado (LPC_SSP1) y configura los pines necesarios para la comunicación.
 */
void SPI_Init()
{
   Chip_SSP_Init(LPC_SSP); // Inicializa el módulo SSP (SPI).

   /* Configuración de los pines del módulo para la comunicación SPI. */
   Chip_SCU_PinMuxSet(0xf, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // Configura el pin P0_4 para SCLK1 (SPI Clock).
   Chip_SCU_PinMuxSet(0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // Configura el pin P1_3 para MISO1 (Master In Slave Out).
   Chip_SCU_PinMuxSet(0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); // Configura el pin P1_4 para MOSI1 (Master Out Slave In).
}


/**
 * @brief Desinicialización del módulo SPI.
 *
 * Esta función desinicializa el módulo SPI seleccionado (LPC_SSP1), liberando los recursos utilizados.
 */
void SPI_deInit()
{
   Chip_SSP_DeInit(LPC_SSP); // Desinicializa el módulo SSP (SPI).
}


/**
 * @brief Configuración del formato y los datos del módulo SPI.
 *
 * Esta función configura el formato de la trama, el modo de reloj y la velocidad de comunicación del módulo SPI.
 */
void SPI_Setup()
{
   static SSP_ConfigFormat ssp_format; // Estructura para almacenar la configuración del formato SPI.
   ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI; // Configura el módulo con el protocolo SPI.
   ssp_format.bits = SSP_BITS_8; // Configura la trama a 8 bits por transferencia.
   ssp_format.clockMode = SSP_CLOCK_MODE1; // Configura el modo de reloj (CPOL=0, CPHA=1).

   Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode); // Aplica la configuración del formato.

   Chip_SSP_Enable(LPC_SSP); // Habilita el módulo SPI.

   Chip_SSP_SetMaster(LPC_SSP, 1); // Configura el módulo SPI como maestro.

   Chip_SSP_SetBitRate(LPC_SSP, 4000000); // Configura la velocidad de comunicación a 4 Mbps.
}


/**
 * @brief Envía y recibe un byte a través de SPI.
 *
 * Esta función envía un byte y recibe otro byte simultáneamente a través del puerto SPI.
 *
 * @param out Byte a enviar (uint8_t).
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_transfer(uint8_t out)
{
   uint8_t in; // Variable para almacenar el byte recibido.
   LPC_SSP->DR = out & 0xFFFF; // Escribe el byte a enviar en el registro de datos.
   while (LPC_SSP->SR & SSP_SR_BSY); // Espera a que la transferencia se complete.
   in = LPC_SSP->DR; // Lee el byte recibido del registro de datos.
   return in; // Retorna el byte recibido.
}


/**
 * @brief Envía un byte a través de SPI.
 *
 * Esta función envía un byte a través del puerto SPI y espera a que la transferencia se complete.
 *
 * @param data Byte a enviar (uint8_t).
 */
void SPI_Send(uint8_t data)
{
   LPC_SSP->DR = SSP_DR_BITMASK(data); // Escribe el byte a enviar en el registro de datos.
   while (LPC_SSP->SR & SSP_SR_BSY); // Espera a que la transferencia se complete.
}


/**
 * @brief Recibe un byte a través de SPI.
 *
 * Esta función recibe un byte a través del puerto SPI.
 *
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_Receive()
{
   return (uint8_t)(SSP_DR_BITMASK(LPC_SSP->DR)); // Lee el byte recibido del registro de datos.
}
