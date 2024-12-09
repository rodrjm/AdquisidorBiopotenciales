
/*
 	 * ADS131E08.c
*/


#include "ADS131E08.h"
#include "GPIO.h"
#include "SPI.h"
#include "funcionamiento.h"
#include "board_api.h"
#include "chip.h"
#include "UART.h"
#include <stdlib.h>



/**
 	 * @brief Indica si el ADS131E08 esta funcionando
*/
static bool isRunning = false; // Variable estatica privada de este archivo

/**
 	 * @brief Numero de canales
*/
uint8_t numChannels = 8;

/**
 	 * @brief
*/
uint8_t sampleCounter = 0;

/**
 	 * @brief Contador de muestras
*/
uint8_t sampleCnt = 0;

/**
 	 * @brief Arreglo utilizado al leer los datos de los registros 
*/
uint8_t regData[24];

/**
 * @brief Variable utilizada para mantener el registro de estado
 */
uint32_t boardStat;

/**
 	 * @brief Arreglo utilizado al leer los datos de los registros
*/
uint32_t channelData[8];

/**
 	 * @brief Variable utilizada para guardar el ID del ADS
*/
uint8_t id;

/**
 	 * @brief Indica si es el primer paquete de datos
*/
bool firstDataPacket = false;

/**
 	 * @brief Configuracion inicial de los pines con los que cuenta el ADS en bajo
*/
void ADS131E08_signalDown(){
	GPIO_setPinState(ADS_CS_PORT, ADS_CS_PIN, false);
	
	GPIO_setPinState(ADS_PWDN_PORT, ADS_PWDN_PIN, false);

	GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, false); 
     
	delayMs(200);
}

/**
 	 * @brief Configuracion de los pines con los que cuenta el ADS
*/
void ADS131E08_Init(){
   
	//delayMs(100);
	GPIO_setPinState(ADS_PWDN_PORT, ADS_PWDN_PIN, true); // Establece el ADS Power Down pin en HIGH
	GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, true);	// Establece el ADS Reset pin en HIGH
	delayMs(100);
   
	GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, false);	//	Establece el ADS Reset pin en LOW
	delayMs(10);
	GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, true);	// Establece el ADS Reset pin en HIGH
	delayMs(10);
	ADS131E08_sendCommand(_SDATAC);	// Se env a el comando SDATAC
	ADS131E08_sendCommand(_STOP);	// Se envia el comando STOP
	delayMs(10);
}


void ADS131E08_defaultConfig() {
	ADS131E08_WREG(_CONFIG3_ADDRESS, _CONFIG3_DEFAULT);	// Establece la configuracion por defecto del registro CONFIG3
	ADS131E08_WREG(_CONFIG1_ADDRESS, _CONFIG1_DEFAULT);	// Establece la configuracion por defecto del registro CONFIG1
	ADS131E08_WREG(_CONFIG2_ADDRESS, _CONFIG2_DEFAULT);	// Establece la configuracion por defecto del registro CONFIG2
	
	for(uint8_t channel=1;channel<=8;channel++)
	{
		ADS131E08_WREG(_CH1SET_ADDRESS+(channel-1), _CHSET_MUX_INPUT_SHORT_TO_MID);	// Establece por defecto cada canal
	}
   
   sampleCounter = 0;
   firstDataPacket = true;
   ADS131E08_sendCommand(_START);	// Iniciar la adquisicion de datos
   delayMs(1);
   ADS131E08_sendCommand(_RDATAC);  // Acceder al modo de lectura continua de datos
   delayMs(1);
   isRunning = true;
   
   ADS131E08_sendCommand(_SDATAC);	// Detener al modo de lectura continua de datos
   ADS131E08_sendCommand(_STOP);	// Detener la adquisicion de datos
   delayMs(10);
   
   for(uint8_t i=0;i<8;i++){
      ADS131E08_WREG(_CH1SET_ADDRESS+i, _CHSET_PD_MASK); // Apago todos los canales
   }
   ADS131E08_WREG(_CH1SET_ADDRESS, 0x05);	// Establecer el canal 1 para el modo de TEST
   
   ADS131E08_WREG(_CONFIG1_ADDRESS, 0x96);	// Establece la configuracion en CONFIG1 para que las muestras sean de 1kSPS 
   ADS131E08_WREG(_CONFIG2_ADDRESS, 0xF0);	// Establece la configuracion en CONFIG2 para que se generen las senales internas de test
	ADS131E08_WREG(_CONFIG3_ADDRESS, 0xC0);	// Establece la configuracion en CONFIG3 para habilitar el bufer de referencia interno
   delayMs(1);
}


/**
 	 * @brief Iniciar la adquisicion continua de datos
*/
void ADS131E08_startADS(){
	sampleCounter = 0;
	firstDataPacket = true;
	ADS131E08_sendCommand(_START); // Iniciar la adquisicion de datos
	delayMs(1);
	ADS131E08_sendCommand(_RDATAC);  // Acceder al modo de lectura continua de datos
	delayMs(1);
	isRunning = true;
}

/**
 	 * @brief Detener la adquisicion continua de datos
*/
void ADS131E08_stopADS(){
	ADS131E08_sendCommand(_STOP);     // Detener la adquisicion de datos
	ADS131E08_sendCommand(_SDATAC);   // Salir del modo continuo de lectura de datos para comunicarse con ADS
	delayMs(10);
	isRunning = false;
}


/**
 	 * @brief SPI chip select en LOW
*/
void ADS131E08_csLow(){
   	GPIO_setPinState(ADS_CS_PORT, ADS_CS_PIN, false); // Establecer el pin Chip Select del ADS en LOW
}


/**
 	 * @brief SPI chip select en HIGH
*/
void ADS131E08_csHigh(){
    GPIO_setPinState(ADS_CS_PORT, ADS_CS_PIN, true); // Establecer el pin Chip Select del ADS en HIGH
}


/**
 	 * @brief Transferencia a traves de SPI
 	 * @param _data Byte a transferir
 	 * @return Byte recibido a traves de la transferencia por SPI
*/
uint8_t ADS131E08_transfer(uint8_t _data){
	 uint8_t inByte;
	 inByte = SPI_transfer(_data); // Transmitir y recibir un byte a traves de SPI
	 return inByte;
}

/**
 	 * @brief Enviar un comando SPI predeterminado del ADS
 	 * @param command Comando a enviar
*/
void ADS131E08_sendCommand(uint8_t command){
	ADS131E08_csLow();
	delayUs(5);
	SPI_transfer(command);
	delayUs(10); // Despues de que finaliza la comunicacion, siempre esperar cuatro o mas ciclos tCLK antes que CS se establezca en HIGH
	ADS131E08_csHigh();
	delayUs(10); // debe esperar 4 ciclos tCLK antes de enviar otro comando
}


/**
 	 * @brief Lee un registro del ADS
 	 * @param _address Direccion del registro a leer
 	 * @return Valor del registro requerido
*/
uint8_t ADS131E08_RREG(uint8_t _address){
	uint8_t firstByte = _address | _RREG; //  RREG espera 001rrrrr where rrrrr = _address
	
	ADS131E08_csLow(); // Iniciar la comunicacion SPI
	delayUs(5);
	SPI_transfer(firstByte); // Enviar firstByte
	delayUs(5);
	SPI_transfer(0x00); // Enviar secondByte: 0x00 para leer solamente el registro en la direccion _address
	delayUs(5);
	regData[_address] = SPI_transfer(0x00); // Actualizar el arreglo de registros con el byte que se acaba de leer
	delayUs(10); // After the serial communication is finished, always wait four or more tCLK cycles before taking CS high
	ADS131E08_csHigh(); // Finalizar la comunicacion SPI
	delayUs(10);
	return regData[_address]; // Retornar el valor del registro requerido
}


/**
 	 * @brief Escribe un registro del ADS
 	 * @param _address Direccion del registro a escribir
 	 * @param _value Byte a escribir en el registro
*/
void ADS131E08_WREG(uint8_t _address, uint8_t _value){
	uint8_t firstByte = _address | _WREG; //  WREG espera 010rrrrr donde rrrrr = _address
	
	ADS131E08_csLow(); // Iniciar la comunicacion SPI
	delayUs(5);
   SPI_transfer(firstByte); // Enviar firstByte
	delayUs(5);
   SPI_transfer(0x00); // Enviar secondByte: 0x00 para escribir solamente el registro de la direccion _address
	delayUs(5);
   SPI_transfer(_value); // Escribir el byte en el registro
	delayUs(10); // Despues de que finaliza la comunicación, siempre esperar cuatro o mas tCLK antes que CS se establezca en HIGH
	ADS131E08_csHigh(); // Finalizar la comunicacion SPI
   delayUs(10);
   
	regData[_address] = _value; // Actualizar el arreglo de registros con el byte que se acaba de escribir
}


/**
 	* @brief Consulta para ver si hay datos disponibles del ADS131E08
 	* @return TRUE si hay datos disponibles, FALSE en caso contrario
*/
bool ADS131E08_isDataAvailable()
{
	return (!(GPIO_getPinState(ADS_DRDY_PORT, ADS_DRDY_PIN)));
}


/**
 	 * @brief Retorna el ID del dispositivo
 	 * @return ID del dispositivo
*/
uint8_t ADS131E08_getDeviceID()
{
   uint8_t idDevice;
   ADS131E08_sendCommand(_SDATAC);	// Detener al modo de lectura continua de datos
   ADS131E08_sendCommand(_STOP);	// Detener la adquisicion de datos
   delayMs(10);
   idDevice = ADS131E08_RREG(_ID_ADDRESS);
   ADS131E08_sendCommand(_START);	// Iniciar la adquisicion de datos
   ADS131E08_sendCommand(_RDATAC);  // Acceder al modo de lectura continua de datos
   delayMs(10);
	return idDevice;
}

/**
 * @brief Devuelve un arreglo con los datos de los registros ADS131E08
 * @param *regArray Puntero a un array con 24 elementos para guardar los valores de los registros del ADS
 */
void ADS131E08_getRegistersData(uint8_t *regArray)
{
	uint8_t i = 0; // Contador del loop for
	for(i=0; i<24; i++) // Hay 24 registros para obtener
	{
		regArray[i] = regData[i];
	}
}

void ADS131E08_getChannelData(uint8_t *sampleCnt, uint32_t *data)
{
	*sampleCnt = sampleCounter; // Copia el valor de sampleCounter
   
	uint8_t i,j = 0; // Contadores del loop for
	uint8_t inByte;
	uint8_t byteCounter = 0;
   uint8_t byte2,byte3;
   for(i=0; i<8; i++)
   {
      data[i] = 0;
   }
   
	ADS131E08_csLow(); // Iniciar la comunicacion SPI
	
	for(i=0; i<3; i++)
	{
		inByte = SPI_transfer(0x00)   ; // Leer el estado de los registros
		boardStat = (boardStat << 8) | inByte;
	}

	for(i=0; i<8; i++) // Leer 16 bits de datos por cada canal en 2 byte chunks
	{
      //inByte=SPI_transfer(0x00);
      //byte2=SPI_transfer(0x00);
      //byte3=SPI_transfer(0x00);
      //data[i] = (byte3<<24) | (byte2<<16) | (inByte<<8);
      //if(inByte & (1<<7)){
        // data[i] = (~(data[i]) +1); 
         //data[i] |= (0xFF);
		//}
      for(j=0; j<3; j++)
		{
			inByte = SPI_transfer(0x00);
			data[i] = (data[i]<<8) | inByte;
		}
	}
   for(i=0;i<8;i++){
      if (data[i] & 0x800000) { // Pasar de 24 bits a 32 bits
         data[i] |= 0xFF000000;
      } 
   }
	ADS131E08_csHigh(); // Finalizar la comunicacion SPI
   
	if(firstDataPacket == TRUE)
	{
		firstDataPacket = false;
	}
	
	sampleCounter++; // Incrementar sampleCounter 
}

void ADS131E08_configureTestSignal(uint8_t currentChannel){
   ADS131E08_sendCommand(_SDATAC);	// Detener al modo de lectura continua de datos
   ADS131E08_sendCommand(_STOP);	// Detener la adquisicion de datos
   delayMs(10);
   
   for(uint8_t i=0;i<8;i++){
      ADS131E08_WREG(_CH1SET_ADDRESS+i, _CHSET_PD_MASK); // Apago todos los canales
   }
   ADS131E08_WREG(currentChannel, 0x05);	// Establecer el canal 1 para el modo de TEST
   
   ADS131E08_WREG(_CONFIG1_ADDRESS, 0x96);	// Establece la configuracion en CONFIG1 para que las muestras sean de 1kSPS 
   ADS131E08_WREG(_CONFIG2_ADDRESS, 0xF0);	// Establece la configuracion en CONFIG2 para que se generen las senales internas de test
	ADS131E08_WREG(_CONFIG3_ADDRESS, 0xC0);	// Establece la configuracion en CONFIG3 para habilitar el bufer de referencia interno
   
   delayMs(1);
}

void ADS131E08_configureExternalSignal(uint8_t currentChannel) {
   ADS131E08_sendCommand(_SDATAC);	// Detener al modo de lectura continua de datos
   ADS131E08_sendCommand(_STOP);	// Detener la adquisicion de datos
   delayMs(10);
   
   for(uint8_t i=0;i<8;i++){
      ADS131E08_WREG(_CH1SET_ADDRESS+i, _CHSET_PD_MASK); // Apago todos los canales
   }
   ADS131E08_WREG(currentChannel, 0x00);	// Establecer el canal 1 para el modo de entrada normal
   
   //ADS131E08_WREG(_CONFIG1_ADDRESS, 0x96);	// Establece la configuracion en CONFIG1 para que las muestras sean de 1kSPS 
   ADS131E08_WREG(_CONFIG2_ADDRESS, 0xE0);	// Establece la configuracion en CONFIG2 para que se generen las senales externas
	//ADS131E08_WREG(_CONFIG3_ADDRESS, 0xC0);	// Establece la configuracion en CONFIG3 para habilitar el bufer de referencia interno
   
   delayMs(1);
}

void ADS131E08_selectMode(uint8_t currentMode, uint8_t currentChannel) {
   if (currentMode == 0) {
      ADS131E08_configureTestSignal(currentChannel);
   } else {
      ADS131E08_configureExternalSignal(currentChannel);
   }
}

void ADS131E08_selectChannel(uint8_t currentChannel) {
   for(uint8_t i=0;i<8;i++){
      ADS131E08_WREG(_CH1SET_ADDRESS+i, _CHSET_PD_MASK); // Apago todos los canales
   }
   ADS131E08_WREG(currentChannel, 0x05); // Establecer el canal de la direccion currentChannel para el modo de TEST
}

void ADS131E08_selectkSPS(uint8_t current_kSPS) {
   uint8_t byte = 0x90;
   byte = byte + current_kSPS;
   ADS131E08_WREG(_CONFIG1_ADDRESS, byte);
}