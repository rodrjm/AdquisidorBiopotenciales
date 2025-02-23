/*
 * ADS131E08.c
 *
 * Descripción: Implementación de funciones para la comunicación y control del ADC ADS131E08.
 * Este módulo proporciona funciones para inicializar, configurar, leer datos y controlar el ADS131E08.
 */


#include "ADS131E08.h"    // Incluye el archivo de encabezado ADS131E08.h, que contiene las definiciones de las funciones y constantes.
#include "GPIO.h"         // Incluye el archivo de encabezado GPIO.h, que proporciona funciones para controlar pines GPIO.
#include "SPI.h"          // Incluye el archivo de encabezado SPI.h, que proporciona funciones para la comunicación SPI.
#include "funcionamiento.h" // Incluye el archivo de encabezado funcionamiento.h (posiblemente para funciones de retardo o control de flujo).
#include "board_api.h"    // Incluye el archivo de encabezado board_api.h, que proporciona funciones para controlar la placa.
#include "chip.h"         // Incluye el archivo de encabezado chip.h, que proporciona acceso a las funciones de bajo nivel del microcontrolador.
#include "UART.h"         // Incluye el archivo de encabezado UART.h (posiblemente para depuración o comunicación de errores).
#include <stdlib.h>       // Incluye el archivo de encabezado stdlib.h (no se usa directamente en el código proporcionado).


/**
 * @brief Indica si el ADS131E08 está funcionando.
 */
static bool isRunning = false;

/**
 * @brief Número de canales del ADS131E08.
 */
uint8_t numChannels = 8;

/**
 * @brief Contador de muestras.
 */
uint8_t sampleCounter = 0;

/**
 * @brief Arreglo utilizado al leer los datos de los registros del ADS131E08.
 */
uint8_t regData[24];

/**
 * @brief Variable utilizada para mantener el registro de estado del ADS131E08.
 */
uint32_t boardStat;

/**
 * @brief Arreglo utilizado para almacenar los datos de los canales del ADS131E08.
 */
uint32_t channelData[8];

/**
 * @brief Variable utilizada para guardar el ID del ADS131E08.
 */
uint8_t id;

/**
 * @brief Indica si es el primer paquete de datos recibido del ADS131E08.
 */
bool firstDataPacket = false;


/**
 * @brief Configuración inicial de los pines del ADS131E08 en bajo.
 */
void ADS131E08_signalDown()
{
   GPIO_setPinState(ADS_CS_PORT, ADS_CS_PIN, false); // Establece el pin CS en bajo.
   GPIO_setPinState(ADS_PWDN_PORT, ADS_PWDN_PIN, false); // Establece el pin PWDN en bajo.
   GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, false); // Establece el pin RST en bajo.
   delayMs(200); // Espera 200 milisegundos.
}


/**
 * @brief Inicialización del ADS131E08.
 */
void ADS131E08_Init()
{
   GPIO_setPinState(ADS_PWDN_PORT, ADS_PWDN_PIN, true); // Establece el pin PWDN en alto.
   GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, true); // Establece el pin RST en alto.
   delayMs(100); // Espera 100 milisegundos.
   GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, false); // Establece el pin RST en bajo.
   delayMs(10); // Espera 10 milisegundos.
   GPIO_setPinState(ADS_RST_PORT, ADS_RST_PIN, true); // Establece el pin RST en alto.
   delayMs(10); // Espera 10 milisegundos.
   ADS131E08_sendCommand(_SDATAC); // Envía el comando SDATAC.
   ADS131E08_sendCommand(_STOP); // Envía el comando STOP.
   delayMs(10); // Espera 10 milisegundos.
}


/**
 * @brief Configuración por defecto del ADS131E08.
 */
void ADS131E08_defaultConfig() {
	ADS131E08_WREG(_CONFIG3_ADDRESS, _CONFIG3_DEFAULT);  // Configura el registro CONFIG3.
	ADS131E08_WREG(_CONFIG1_ADDRESS, _CONFIG1_DEFAULT);  // Configura el registro CONFIG1.
	ADS131E08_WREG(_CONFIG2_ADDRESS, _CONFIG2_DEFAULT);  // Configura el registro CONFIG2.
	
	for(uint8_t channel=1;channel<=8;channel++)
	{
		ADS131E08_WREG(_CH1SET_ADDRESS+(channel-1), _CHSET_MUX_INPUT_SHORT_TO_MID);  // Configura los canales.
	}
   
   sampleCounter = 0;
   firstDataPacket = true;
   ADS131E08_sendCommand(_START);  // Inicia la adquisición de datos.
   delayMs(1);  // Espera 1 milisegundo.
   ADS131E08_sendCommand(_RDATAC);  // Entra en modo de lectura continua de datos.
   delayMs(1);  // Espera 1 milisegundo.
   isRunning = true;
   
   ADS131E08_sendCommand(_SDATAC);  // Sale del modo de lectura continua de datos.
   ADS131E08_sendCommand(_STOP);  // Detiene la adquisición de datos.
   delayMs(10);  // Espera 10 milisegundos.
   
   for(uint8_t i=0;i<8;i++){
      ADS131E08_WREG(_CH1SET_ADDRESS+i, _CHSET_PD_MASK); // Apago los canales.
   }
   ADS131E08_WREG(_CH1SET_ADDRESS, 0x05);  // Configura el canal 1 para el modo de prueba (TEST).
   
   ADS131E08_WREG(_CONFIG1_ADDRESS, 0x96);  // Configura la frecuencia de muestreo (1 kSPS) en CONFIG1.
   ADS131E08_WREG(_CONFIG2_ADDRESS, 0xF0);  // Configura las señales de prueba internas en CONFIG2.
	ADS131E08_WREG(_CONFIG3_ADDRESS, 0xC0);  // Habilita el buffer de referencia interno en CONFIG3.
   delayMs(1);  // Espera 1 milisegundo.
}


/**
 * @brief Inicia la adquisición continua de datos del ADS131E08.
 */
void ADS131E08_startADS(){
	sampleCounter = 0;
	firstDataPacket = true;
	ADS131E08_sendCommand(_START); // Inicia la adquisición de datos.
   delayMs(1); // Espera 1 milisegundo.
   ADS131E08_sendCommand(_RDATAC); // Entra en modo de lectura continua de datos.
   delayMs(1); // Espera 1 milisegundo.
	isRunning = true;
}


/**
 * @brief Detiene la adquisición continua de datos del ADS131E08.
 */
void ADS131E08_stopADS()
{
   ADS131E08_sendCommand(_STOP); // Detiene la adquisición de datos.
   ADS131E08_sendCommand(_SDATAC); // Sale del modo de lectura continua de datos.
   delayMs(10); // Espera 10 milisegundos.
   isRunning = false;
}


/**
 * @brief Establece el pin CS del ADS131E08 en bajo.
 */
void ADS131E08_csLow()
{
   GPIO_setPinState(ADS_CS_PORT, ADS_CS_PIN, false); // Establece el pin CS en bajo.
}


/**
 * @brief Establece el pin CS del ADS131E08 en alto.
 */
void ADS131E08_csHigh()
{
   GPIO_setPinState(ADS_CS_PORT, ADS_CS_PIN, true); // Establece el pin CS en alto.
}


/**
 * @brief Transfiere un byte a través de SPI.
 *
 * @param _data Byte a transferir.
 * @return Byte recibido durante la transferencia.
 */
uint8_t ADS131E08_transfer(uint8_t _data)
{
   uint8_t inByte;
   inByte = SPI_transfer(_data); // Transfiere el byte y recibe el byte de respuesta.
   return inByte;
}


/**
 * @brief Envía un comando al ADS131E08.
 *
 * @param command Comando a enviar.
 */
void ADS131E08_sendCommand(uint8_t command)
{
   ADS131E08_csLow(); // Establece el pin CS en bajo.
   delayUs(5); // Espera 5 microsegundos.
   SPI_transfer(command); // Transfiere el comando.
   delayUs(10); // Espera 10 microsegundos.
   ADS131E08_csHigh(); // Establece el pin CS en alto.
   delayUs(10); // Espera 10 microsegundos.
}


/**
 * @brief Lee un registro del ADS131E08.
 *
 * @param _address Dirección del registro a leer.
 * @return Valor del registro leído.
 */
uint8_t ADS131E08_RREG(uint8_t _address){
	uint8_t firstByte = _address | _RREG;  // Crea el primer byte del comando de lectura (RREG espera 001rrrrr donde rrrrr = _address).
	
	ADS131E08_csLow(); // Establece el pin CS en bajo.
   delayUs(5); // Espera 5 microsegundos.
   SPI_transfer(firstByte); // Transfiere el primer byte.
   delayUs(5); // Espera 5 microsegundos.
	SPI_transfer(0x00); // Transfiere el segundo byte (0x00). Indica que se debe leer el registro en la direccion _address.
	delayUs(5); // Espera 5 microsegundos.
   regData[_address] = SPI_transfer(0x00); // Lee el valor del registro y lo almacena.
   delayUs(10); // Espera 10 microsegundos.
   ADS131E08_csHigh(); // Establece el pin CS en alto.
   delayUs(10); // Espera 10 microsegundos.
   return regData[_address]; // Retorna el valor del registro.
}


/**
 * @brief Escribe un registro del ADS131E08.
 *
 * @param _address Dirección del registro a escribir.
 * @param _value Valor a escribir en el registro.
 */
void ADS131E08_WREG(uint8_t _address, uint8_t _value){
	uint8_t firstByte = _address | _WREG;  // Crea el primer byte del comando de escritura (WREG espera 010rrrrr donde rrrrr = _address).
	
	ADS131E08_csLow(); // Establece el pin CS en bajo.
   delayUs(5); // Espera 5 microsegundos.
   SPI_transfer(firstByte); // Transfiere el primer byte.
   delayUs(5); // Espera 5 microsegundos.
   SPI_transfer(0x00); // Transfiere el segundo byte (0x00). Indica que se debe escribir un byte en el registro de la direccion _address.
	delayUs(5); // Espera 5 microsegundos.
   SPI_transfer(_value); // Transfiere el valor a escribir.
   delayUs(10); // Espera 10 microsegundos.
   ADS131E08_csHigh(); // Establece el pin CS en alto.
   delayUs(10); // Espera 10 microsegundos.

   regData[_address] = _value; // Actualiza el valor del registro en el arreglo regData.
}


/**
 * @brief Verifica si hay datos disponibles en el ADS131E08.
 *
 * @return true si hay datos disponibles, false en caso contrario.
 */
bool ADS131E08_isDataAvailable()
{
   return (!(GPIO_getPinState(ADS_DRDY_PORT, ADS_DRDY_PIN))); // Verifica el estado del pin DRDY.
}


/**
 * @brief Obtiene el ID del dispositivo ADS131E08.
 *
 * @return ID del dispositivo.
 */
uint8_t ADS131E08_getDeviceID()
{
   uint8_t idDevice;
   ADS131E08_sendCommand(_SDATAC); // Detiene el modo de lectura continua de datos.
   ADS131E08_sendCommand(_STOP); // Detiene la adquisición de datos.
   delayMs(10); // Espera 10 milisegundos.
   idDevice = ADS131E08_RREG(_ID_ADDRESS); // Lee el ID del dispositivo.
   ADS131E08_sendCommand(_START); // Inicia la adquisición de datos.
   ADS131E08_sendCommand(_RDATAC); // Entra en modo de lectura continua de datos.
   delayMs(10); // Espera 10 milisegundos.
   return idDevice; // Retorna el ID del dispositivo.
}


/**
 * @brief Obtiene los datos de los registros del ADS131E08.
 *
 * @param regArray Puntero a un arreglo para almacenar los datos de los registros.
 */
void ADS131E08_getRegistersData(uint8_t *regArray)
{
   uint8_t i;
   for (i = 0; i < 24; i++)
   {
      regArray[i] = regData[i]; // Copia los datos de los registros al arreglo proporcionado.
   }
}


/**
 * @brief Obtiene los datos de los canales del ADS131E08.
 *
 * @param sampleCnt Contador de muestras.
 * @param data Puntero a un arreglo para almacenar los datos de los canales.
 */
void ADS131E08_getChannelData(uint8_t *sampleCnt, uint32_t *data)
{
	*sampleCnt = sampleCounter;  // Copia el contador de muestras.
   
	uint8_t i,j = 0;
	uint8_t inByte;
	uint8_t byteCounter = 0;
   uint8_t byte2,byte3;
   for(i=0; i<8; i++)
   {
      data[i] = 0;  // Inicializa los datos de los canales.
   }
   
	ADS131E08_csLow();  // Establece el pin CS en bajo.
	
	for(i=0; i<3; i++)
	{
		inByte = SPI_transfer(0x00);  // Lee el estado de los registros.
      boardStat = (boardStat << 8) | inByte;  // Construye el valor de boardStat.
      inByte = 0;
	}

	for(i=0; i<8; i++) // Lee los datos de los canales (24 bits de datos por cada canal en 3 byte chunks).
	{
      for(j=0; j<3; j++)
		{
			inByte = SPI_transfer(0x00);  // Lee un byte de datos.
         data[i] = (data[i] << 8) | inByte; // Construye el valor del canal.
         inByte = 0;
		}
	}
   for(i=0;i<8;i++){  // Extiende el signo de los datos de 24 bits a 32 bits, agregando valor '0xAA' al inicio para sincronización.
      if ((data[i] >> 23) & 1) { 
         data[i] = (~(data[i]) + 1);
         data[i] &= 0xAAFFFFFF;
         data[i] |= 0x00800000;         
      } else {
         data[i] |= 0xAA000000;
      }
   }
	ADS131E08_csHigh();  // Establece el pin CS en alto.
   
	if(firstDataPacket == TRUE)
	{
		firstDataPacket = false;  // Indica que se ha recibido el primer paquete de datos.
	}
	
	sampleCounter++;  // Incrementa el contador de muestras.
}


/**
 * @brief Configura el ADS131E08 para generar señales de prueba internas.
 *
 * @param currentChannel Canal a configurar para la señal de prueba.
 */
void ADS131E08_configureTestSignal(uint8_t currentChannel)
{
   delayMs(10); // Espera 10 milisegundos.

   for (uint8_t i = 0; i < 8; i++)
   {
      ADS131E08_WREG(_CH1SET_ADDRESS + i, _CHSET_PD_MASK); // Apaga todos los canales.
   }
   ADS131E08_WREG(currentChannel, 0x05); // Configura el canal para la señal de prueba.

   ADS131E08_WREG(_CONFIG2_ADDRESS, 0xF0); // Configura el registro CONFIG2 para señales de prueba.

   delayMs(1); // Espera 1 milisegundo.
}


/**
 * @brief Configura el ADS131E08 para adquirir señales externas.
 *
 * @param currentChannel Canal a configurar para la señal externa.
 */
void ADS131E08_configureExternalSignal(uint8_t currentChannel)
{
   delayMs(10); // Espera 10 milisegundos.

   for (uint8_t i = 0; i < 8; i++)
   {
      ADS131E08_WREG(_CH1SET_ADDRESS + i, _CHSET_PD_MASK); // Apaga todos los canales.
   }
   ADS131E08_WREG(currentChannel, 0x00); // Configura el canal para la señal externa.

   ADS131E08_WREG(_CONFIG2_ADDRESS, 0xE0); // Configura el registro CONFIG2 para señales externas.

   delayMs(1); // Espera 1 milisegundo.
}


/**
 * @brief Selecciona el modo de operación del ADS131E08 (prueba o adquisición externa).
 *
 * @param currentMode Modo a seleccionar (0 para prueba, 1 para adquisición externa).
 * @param currentChannel Canal a configurar.
 */
void ADS131E08_selectMode(uint8_t currentMode, uint8_t currentChannel)
{
   if (currentMode == 0)
   {
      ADS131E08_configureTestSignal(currentChannel); // Configura para señales de prueba.
   }
   else
   {
      ADS131E08_configureExternalSignal(currentChannel); // Configura para señales externas.
   }
}



/**
 * @brief Selecciona el canal activo del ADS131E08.
 *
 * @param currentChannel Canal a seleccionar.
 */
void ADS131E08_selectChannel(uint8_t currentChannel)
{
   delayMs(10); // Espera 10 milisegundos.

   for (uint8_t i = 0; i < 8; i++)
   {
      ADS131E08_WREG(_CH1SET_ADDRESS + i, _CHSET_PD_MASK); // Apaga todos los canales.
   }
   ADS131E08_WREG(currentChannel, 0x05); // Configura el canal seleccionado.

   delayMs(1); // Espera 1 milisegundo.
}


/**
 * @brief Selecciona la frecuencia de muestreo del ADS131E08.
 *
 * @param current_kSPS Frecuencia de muestreo en kSPS.
 */
void ADS131E08_selectkSPS(uint8_t current_kSPS)
{
   delayMs(10); // Espera 10 milisegundos.

   uint8_t byte = 0x90; // Valor base para el registro CONFIG1.
   byte = byte + current_kSPS; // Ajusta el valor según la frecuencia de muestreo.
   ADS131E08_WREG(_CONFIG1_ADDRESS, byte); // Configura el registro CONFIG1.

   delayMs(1); // Espera 1 milisegundo.
}
