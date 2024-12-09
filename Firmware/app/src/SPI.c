/*
 	 * SPI.c
*/

#include "SPI.h"
#include "chip.h"
#include "UART.h"


/**
 	 * @brief Inicializacion del modulo SPI
*/
void SPI_Init()
{

	Chip_SSP_Init(LPC_SSP); // Selecciona el modulo a inicializar

	/* Configuracion de los pines del modulo para la comunicacion SPI */
	Chip_SCU_PinMuxSet(0xf, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); /* SCLK1 */
	Chip_SCU_PinMuxSet(0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); /* MISO1 */
	Chip_SCU_PinMuxSet(0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); /* MOSI1 */
}


/**
 	 * @brief Desinicializacion del modulo SPI
*/
void SPI_deInit()
{
	Chip_SSP_DeInit(LPC_SSP); // Selecciona el modulo a desinicializar
}


/**
 	 * @brief Configuracion del formato y los datos del modulo SPI
*/
void SPI_Setup()
{
	static SSP_ConfigFormat ssp_format;
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI; // Configura el modulo con el protocolo SPI
	ssp_format.bits = SSP_BITS_8; // 8 bits por trama
	ssp_format.clockMode = SSP_CLOCK_MODE1; // Modos de reloj

	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);

	Chip_SSP_Enable(LPC_SSP);

	Chip_SSP_SetMaster(LPC_SSP, 1); // Configura el modulo SPI como Master

	Chip_SSP_SetBitRate(LPC_SSP, 216000); // Configura el bit rate
}


/**
 	 * @brief Envia y recibe un byte a traves de SPI
 	 * @param out Byte a enviar
 	 * @return in Byte recibido
*/
uint8_t SPI_transfer(uint8_t out)
{
  uint8_t in;
  LPC_SSP->DR = out & 0xFFFF;
  while (LPC_SSP->SR & 0x10 ) { ; }
  in = LPC_SSP->DR;
  return in;
}

void SPI_Send(uint8_t data) {
   LPC_SSP->DR = SSP_DR_BITMASK(data);
   while (LPC_SSP->SR & 0x10);
}

uint8_t SPI_Receive() {
   return (uint8_t) (SSP_DR_BITMASK(LPC_SSP->DR));
}
