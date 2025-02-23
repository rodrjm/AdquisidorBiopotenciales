/*
 * SPI.c
 *
 * Descripci�n: Implementaci�n de funciones para la comunicaci�n SPI en la placa EDU-CIAA-NXP.
 * Este m�dulo proporciona funciones para inicializar, desinicializar, configurar, enviar y recibir datos a trav�s del puerto SPI.
 */


#include "SPI.h"      // Incluye el archivo de encabezado SPI.h, que contiene las definiciones de las funciones y constantes.
#include "chip.h"     // Incluye el archivo de encabezado chip.h, que proporciona acceso a las funciones de bajo nivel del microcontrolador.
#include "UART.h"     // Incluye el archivo de encabezado UART.h (posiblemente para depuraci�n o comunicaci�n de errores).


/**
 * @brief Inicializaci�n del m�dulo SPI.
 *
 * Esta funci�n inicializa el m�dulo SPI seleccionado (LPC_SSP1) y configura los pines necesarios para la comunicaci�n.
 */
void SPI_Init()
{
   Chip_SSP_Init(LPC_SSP); // Inicializa el m�dulo SSP (SPI).

   /* Configuraci�n de los pines del m�dulo para la comunicaci�n SPI. */
   Chip_SCU_PinMuxSet(0xf, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); // Configura el pin P0_4 para SCLK1 (SPI Clock).
   Chip_SCU_PinMuxSet(0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); // Configura el pin P1_3 para MISO1 (Master In Slave Out).
   Chip_SCU_PinMuxSet(0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); // Configura el pin P1_4 para MOSI1 (Master Out Slave In).
}


/**
 * @brief Desinicializaci�n del m�dulo SPI.
 *
 * Esta funci�n desinicializa el m�dulo SPI seleccionado (LPC_SSP1), liberando los recursos utilizados.
 */
void SPI_deInit()
{
   Chip_SSP_DeInit(LPC_SSP); // Desinicializa el m�dulo SSP (SPI).
}


/**
 * @brief Configuraci�n del formato y los datos del m�dulo SPI.
 *
 * Esta funci�n configura el formato de la trama, el modo de reloj y la velocidad de comunicaci�n del m�dulo SPI.
 */
void SPI_Setup()
{
   static SSP_ConfigFormat ssp_format; // Estructura para almacenar la configuraci�n del formato SPI.
   ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI; // Configura el m�dulo con el protocolo SPI.
   ssp_format.bits = SSP_BITS_8; // Configura la trama a 8 bits por transferencia.
   ssp_format.clockMode = SSP_CLOCK_MODE1; // Configura el modo de reloj (CPOL=0, CPHA=1).

   Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode); // Aplica la configuraci�n del formato.

   Chip_SSP_Enable(LPC_SSP); // Habilita el m�dulo SPI.

   Chip_SSP_SetMaster(LPC_SSP, 1); // Configura el m�dulo SPI como maestro.

   Chip_SSP_SetBitRate(LPC_SSP, 4000000); // Configura la velocidad de comunicaci�n a 4 Mbps.
}


/**
 * @brief Env�a y recibe un byte a trav�s de SPI.
 *
 * Esta funci�n env�a un byte y recibe otro byte simult�neamente a trav�s del puerto SPI.
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
 * @brief Env�a un byte a trav�s de SPI.
 *
 * Esta funci�n env�a un byte a trav�s del puerto SPI y espera a que la transferencia se complete.
 *
 * @param data Byte a enviar (uint8_t).
 */
void SPI_Send(uint8_t data)
{
   LPC_SSP->DR = SSP_DR_BITMASK(data); // Escribe el byte a enviar en el registro de datos.
   while (LPC_SSP->SR & SSP_SR_BSY); // Espera a que la transferencia se complete.
}


/**
 * @brief Recibe un byte a trav�s de SPI.
 *
 * Esta funci�n recibe un byte a trav�s del puerto SPI.
 *
 * @return Byte recibido (uint8_t).
 */
uint8_t SPI_Receive()
{
   return (uint8_t)(SSP_DR_BITMASK(LPC_SSP->DR)); // Lee el byte recibido del registro de datos.
}
