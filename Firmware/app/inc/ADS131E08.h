#ifndef ADS131E08_H_
#define ADS131E08_H_

#include <stdint.h> // Incluye la biblioteca estándar de tipos enteros.
#include <stdbool.h> // Incluye la biblioteca estándar de booleanos.

/* Register 0x09 (CH5SET) definition
 * -------------------------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * -------------------------------------------------------------------------------------------------
 * |   PD   |          GAIN[2:0]          |    0    |          MUX[2:0]          |
 * -------------------------------------------------------------------------------------------------
 */
/* CH5SET register address */
#define _CH5SET_ADDRESS                     ((uint8_t) 0x09) // Dirección del registro CH5SET (canal 5).

/* CH5SET default (reset) value */
#define _CH5SET_DEFAULT                     ((uint8_t) 0x10) // Valor predeterminado (reset) del registro CH5SET.

/* CH5SET register field masks */
#define _CH5SET_PD_MASK                     ((uint8_t) 0x80) // Máscara para el bit de Power Down (PD).
#define _CH5SET_GAIN_MASK                   ((uint8_t) 0x70) // Máscara para los bits de ganancia (GAIN[2:0]).
#define _CH5SET_MUX_MASK                    ((uint8_t) 0x07) // Máscara para los bits del multiplexor (MUX[2:0]).

/* PGA Gain field values */
#define _CH5SET_PGA_GAIN_NOTUSE              ((uint8_t) 0x00) // No usar ganancia (Do not use).
#define _CH5SET_PGA_GAIN_1                   ((uint8_t) 0x10) // Ganancia 1x.
#define _CH5SET_PGA_GAIN_2                   ((uint8_t) 0x20) // Ganancia 2x.
#define _CH5SET_PGA_GAIN_4                   ((uint8_t) 0x40) // Ganancia 4x.
#define _CH5SET_PGA_GAIN_8                   ((uint8_t) 0x50) // Ganancia 8x.
#define _CH5SET_PGA_GAIN_12                  ((uint8_t) 0x60) // Ganancia 12x.

/* MUX field values */
#define _CH5SET_MUX_NORMAL_INPUT            ((uint8_t) 0x00) // Entrada normal.
#define _CH5SET_MUX_INPUT_SHORT_TO_MID      ((uint8_t) 0x01) // Entrada cortocircuitada a (AVDD + AVSS) / 2 (para mediciones de offset o ruido).
#define _CH5SET_MUX_MVDD_FOR_SUPPLY          ((uint8_t) 0x03) // MVDD para medición de suministro.
#define _CH5SET_MUX_TEMP_SENSOR              ((uint8_t) 0x04) // Sensor de temperatura.
#define _CH5SET_MUX_TEST_SIGNAL              ((uint8_t) 0x05) // Señal de prueba.

/* Register 0x0A (CH6SET) definition
 * -------------------------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * -------------------------------------------------------------------------------------------------
 * |   PD   |          GAIN[2:0]          |    0    |          MUX[2:0]          |
 * -------------------------------------------------------------------------------------------------
 */
/* CH6SET register address */
#define _CH6SET_ADDRESS                     ((uint8_t) 0x0A) // Dirección del registro CH6SET (canal 6).

/* CH6SET default (reset) value */
#define _CH6SET_DEFAULT                     ((uint8_t) 0x10) // Valor predeterminado (reset) del registro CH6SET.

/* CH6SET register field masks */
#define _CH6SET_PD_MASK                     ((uint8_t) 0x80) // Máscara para el bit de Power Down (PD).
#define _CH6SET_GAIN_MASK                   ((uint8_t) 0x70) // Máscara para los bits de ganancia (GAIN[2:0]).
#define _CH6SET_MUX_MASK                    ((uint8_t) 0x07) // Máscara para los bits del multiplexor (MUX[2:0]).

/* PGA Gain field values */
#define _CH6SET_PGA_GAIN_NOTUSE              ((uint8_t) 0x00) // No usar ganancia (Do not use).
#define _CH6SET_PGA_GAIN_1                   ((uint8_t) 0x10) // Ganancia 1x.
#define _CH6SET_PGA_GAIN_2                   ((uint8_t) 0x20) // Ganancia 2x.
#define _CH6SET_PGA_GAIN_4                   ((uint8_t) 0x40) // Ganancia 4x.
#define _CH6SET_PGA_GAIN_8                   ((uint8_t) 0x50) // Ganancia 8x.
#define _CH6SET_PGA_GAIN_12                  ((uint8_t) 0x60) // Ganancia 12x.

/* MUX field values */
#define _CH6SET_MUX_NORMAL_INPUT            ((uint8_t) 0x00) // Entrada normal.
#define _CH6SET_MUX_INPUT_SHORT_TO_MID      ((uint8_t) 0x01) // Entrada cortocircuitada a (AVDD + AVSS) / 2 (para mediciones de offset o ruido).
#define _CH6SET_MUX_MVDD_FOR_SUPPLY          ((uint8_t) 0x03) // MVDD para medición de suministro.
#define _CH6SET_MUX_TEMP_SENSOR              ((uint8_t) 0x04) // Sensor de temperatura.
#define _CH6SET_MUX_TEST_SIGNAL              ((uint8_t) 0x05) // Señal de prueba.

// ... (Definiciones similares para CH7SET y CH8SET) ...

/* Register 0x0D (RESERVED0) definition
 * -------------------------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * -------------------------------------------------------------------------------------------------
 * |    0    |    0    |    0    |    0    |    0    |    0    |    0    |    0    |
 * -------------------------------------------------------------------------------------------------
 */
// ... (Definiciones similares para RESERVED1, RESERVED2, RESERVED3, RESERVED4) ...

/* Register 0x12 (FAULT_STATP) definition
 * -------------------------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * -------------------------------------------------------------------------------------------------
 * | IN8P_FAULT| IN7P_FAULT| IN6P_FAULT| IN5P_FAULT| IN4P_FAULT| IN3P_FAULT| IN2P_FAULT| IN1P_FAULT|
 * -------------------------------------------------------------------------------------------------
 */
/* FAULT_STATP register address */
#define _FAULT_STATP_ADDRESS                ((uint8_t) 0x12) // Dirección del registro FAULT_STATP.

/* FAULT_STATP default (reset) value */
#define _FAULT_STATP_DEFAULT                ((uint8_t) 0x00) // Valor predeterminado (reset) del registro FAULT_STATP.

/* FAULT_STATP register field masks */
#define _FAULT__STATP_IN8P_FAULT_MASK        ((uint8_t) 0x80) // Máscara para el bit IN8P_FAULT.
#define _FAULT_STATP_IN7P_FAULT_MASK        ((uint8_t) 0x40) // Máscara para el bit IN7P_FAULT.
#define _FAULT_STATP_IN6P_FAULT_MASK        ((uint8_t) 0x20) // Máscara para el bit IN6P_FAULT.
#define _FAULT_STATP_IN5P_FAULT_MASK        ((uint8_t) 0x10) // Máscara para el bit IN5P_FAULT.
#define _FAULT_STATP_IN4P_FAULT_MASK        ((uint8_t) 0x08) // Máscara para el bit IN4P_FAULT.
#define _FAULT_STATP_IN3P_FAULT_MASK        ((uint8_t) 0x04) // Máscara para el bit IN3P_FAULT.
#define _FAULT_STATP_IN2P_FAULT_MASK        ((uint8_t) 0x02) // Máscara para el bit IN2P_FAULT.
#define _FAULT_STATP_IN1P_FAULT_MASK        ((uint8_t) 0x01) // Máscara para el bit IN1P_FAULT.

/* Register 0x13 (FAULT_STATN) definition
 * -------------------------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * -------------------------------------------------------------------------------------------------
 * | IN8_NFAULT| IN7N_FAULT| IN6N_FAULT| IN5N_FAULT| IN4N_FAULT| IN3N_FAULT| IN2N_FAULT| IN1N_FAULT|
 * -------------------------------------------------------------------------------------------------
 */
/* FAULT_STATN register address */
#define _FAULT_STATN_ADDRESS                ((uint8_t) 0x13) // Dirección del registro FAULT_STATN.

/* FAULT_STATN default (reset) value */
#define _FAULT_STATN_DEFAULT                ((uint8_t) 0x00) // Valor predeterminado (reset) del registro FAULT_STATN.

/* FAULT_STATN register field masks */
#define _FAULT_STATN_IN8N_FAULT_MASK        ((uint8_t) 0x80) // Máscara para el bit IN8N_FAULT.
#define _FAULT_STATN_IN7N_FAULT_MASK        ((uint8_t) 0x40) // Máscara para el bit IN7N_FAULT.
#define _FAULT_STATN_IN6N_FAULT_MASK        ((uint8_t) 0x20) // Máscara para el bit IN6N_FAULT.
#define _FAULT_STATN_IN5N_FAULT_MASK        ((uint8_t) 0x10) // Máscara para el bit IN5N_FAULT.
#define _FAULT_STATN_IN4N_FAULT_MASK        ((uint8_t) 0x08) // Máscara para el bit IN4N_FAULT.
#define _FAULT_STATN_IN3N_FAULT_MASK        ((uint8_t) 0x04) // Máscara para el bit IN3N_FAULT.
#define _FAULT_STATN_IN2N_FAULT_MASK        ((uint8_t) 0x02) // Máscara para el bit IN2N_FAULT.
#define _FAULT_STATN_IN1N_FAULT_MASK        ((uint8_t) 0x01) // Máscara para el bit IN1N_FAULT.

/* Register 0x14 (GPIO) definition
 * -------------------------------------------------------------------------------------------------
 * |  Bit 7  |  Bit 6  |  Bit 5  |  Bit 4  |  Bit 3  |  Bit 2  |  Bit 1  |  Bit 0  |
 * -------------------------------------------------------------------------------------------------
 * |             GPIOD[7:4]            |             GPIOC[4:1]            |
 * -------------------------------------------------------------------------------------------------
 */
/* GPIO register address */
#define _GPIO_ADDRESS                    ((uint8_t) 0x14) // Dirección del registro GPIO.

/* GPIO default (reset) value */
#define _GPIO_DEFAULT                    ((uint8_t) 0x0F) // Valor predeterminado (reset) del registro GPIO.

/* GPIO register field masks */
#define _GPIO_GPIOD_MASK                ((uint8_t) 0xF0) // Máscara para los bits GPIOD[7:4].
#define _GPIO_GPIOC_MASK                ((uint8_t) 0x0F) // Máscara para los bits GPIOC[4:1].

// Configuraciones de cada canal
#define POWER_DOWN_     (0) // Índice para la configuración de Power Down.
#define GAIN_SET        (1) // Índice para la configuración de ganancia.
#define INPUT_TYPE_SET  (2) // Índice para la configuración del tipo de entrada.
#define YES             (0x01) // Valor para habilitar una configuración.
#define NO              (0x00) // Valor para deshabilitar una configuración.

/* CHxSET default (reset) value */
#define _CHSET_DEFAULT                  ((uint8_t) 0x10) // Valor predeterminado (reset) de los registros CHxSET.

/* CHxSET register field masks */
#define _CHSET_PD_MASK                  ((uint8_t) 0x80) // Máscara para el bit de Power Down (PD).
#define _CHSET_GAIN_MASK                ((uint8_t) 0x70) // Máscara para los bits de ganancia (GAIN[2:0]).
#define _CHSET_MUX_MASK                 ((uint8_t) 0x07) // Máscara para los bits del multiplexor (MUX[2:0]).

/* PGA Gain field values */
#define _CHSET_PGA_GAIN_NOTUSE          ((uint8_t) 0x00) // No usar ganancia (Do not use).
#define _CHSET_PGA_GAIN_1               ((uint8_t) 0x10) // Ganancia 1x.
#define _CHSET_PGA_GAIN_2               ((uint8_t) 0x20) // Ganancia 2x.
#define _CHSET_PGA_GAIN_4               ((uint8_t) 0x40) // Ganancia 4x.
#define _CHSET_PGA_GAIN_8               ((uint8_t) 0x50) // Ganancia 8x.
#define _CHSET_PGA_GAIN_12              ((uint8_t) 0x60) // Ganancia 12x.

/* MUX field values */
#define _CHSET_MUX_NORMAL_INPUT        ((uint8_t) 0x00) // Entrada normal.
#define _CHSET_MUX_INPUT_SHORT_TO_MID  ((uint8_t) 0x01) // Entrada cortocircuitada a (AVDD + AVSS) / 2 (para mediciones de offset o ruido).
#define _CHSET_MUX_MVDD_FOR_SUPPLY      ((uint8_t) 0x03) // MVDD para medición de suministro.
#define _CHSET_MUX_TEMP_SENSOR          ((uint8_t) 0x04) // Sensor de temperatura.
#define _CHSET_MUX_TEST_SIGNAL          ((uint8_t) 0x05) // Señal de prueba.


/**
 * @brief Indica si es el primer paquete de datos.
 */
extern bool firstDataPacket;

/**
 * @brief Número de canales.
 */
extern uint8_t numChannels;

/**
 * @brief Contador de muestras.
 */
extern uint8_t sampleCounter;

/**
 * @brief Arreglo utilizado al leer los datos de los registros.
 */
extern uint8_t regData[24];

/**
 * @brief Variable utilizada para mantener el registro de estado.
 */
uint32_t boardStat;

/**
 * @brief Arreglo utilizado al leer los datos de los registros.
 */
extern uint32_t channelData[8];

/**
 * @brief Variable utilizada para guardar el ID del ADS.
 */
extern uint8_t id;


/**
 * @brief Configura los pines de control del ADS131E08 en estado bajo.
 *
 * Esta función inicializa los pines de control del ADS131E08 (CS, DRDY, etc.) en estado bajo,
 * preparándolos para la comunicación SPI y la adquisición de datos.
 */
void ADS131E08_signalDown();


/**
 * @brief Inicializa el ADS131E08.
 *
 * Esta función realiza la inicialización del ADS131E08, configurando los pines de control,
 * realizando un reset del dispositivo y estableciendo los valores predeterminados de los registros.
 */
void ADS131E08_Init();


/**
 * @brief Configura el ADS131E08 con los valores predeterminados.
 *
 * Esta función escribe los valores predeterminados en los registros de configuración del ADS131E08,
 * estableciendo la ganancia, el multiplexor y otros parámetros por defecto.
 */
void ADS131E08_defaultConfig();


/**
 * @brief Inicia la adquisición continua de datos del ADS131E08.
 *
 * Esta función envía el comando para iniciar la conversión continua de datos en el ADS131E08.
 */
void ADS131E08_startADS();


/**
 * @brief Detiene la adquisición continua de datos del ADS131E08.
 *
 * Esta función envía el comando para detener la conversión continua de datos en el ADS131E08.
 */
void ADS131E08_stopADS();


/**
 * @brief Selecciona el chip ADS131E08 para la comunicación SPI (CS bajo).
 *
 * Esta función pone el pin CS (Chip Select) en estado bajo, habilitando la comunicación SPI con el ADS131E08.
 */
void ADS131E08_csLow();


/**
 * @brief Deselecciona el chip ADS131E08 para la comunicación SPI (CS alto).
 *
 * Esta función pone el pin CS (Chip Select) en estado alto, deshabilitando la comunicación SPI con el ADS131E08.
 */
void ADS131E08_csHigh();


/**
 * @brief Realiza una transferencia de datos SPI con el ADS131E08.
 *
 * Esta función envía un byte de datos al ADS131E08 a través de SPI y recibe un byte de datos como respuesta.
 *
 * @param _data Byte a transferir.
 * @return Byte recibido a través de la transferencia SPI.
 */
uint8_t ADS131E08_transfer(uint8_t _data);


/**
 * @brief Envía un comando SPI predefinido al ADS131E08.
 *
 * Esta función envía un comando SPI al ADS131E08, como el comando de inicio de conversión o el comando de reset.
 *
 * @param command Comando a enviar.
 */
void ADS131E08_sendCommand(uint8_t command);


/**
 * @brief Lee un registro del ADS131E08.
 *
 * Esta función lee el valor de un registro específico del ADS131E08 a través de la comunicación SPI.
 *
 * @param _address Dirección del registro a leer.
 * @return Valor del registro leído.
 */
uint8_t ADS131E08_RREG(uint8_t _address);


/**
 * @brief Escribe un valor en un registro del ADS131E08.
 *
 * Esta función escribe un byte de datos en un registro específico del ADS131E08 a través de la comunicación SPI.
 *
 * @param _address Dirección del registro a escribir.
 * @param _value Byte a escribir en el registro.
 */
void ADS131E08_WREG(uint8_t _address, uint8_t _value);


/**
 * @brief Verifica si hay datos disponibles en el ADS131E08.
 *
 * Esta función verifica si el pin DRDY (Data Ready) del ADS131E08 está en estado bajo,
 * lo que indica que hay datos disponibles para ser leídos.
 *
 * @return TRUE si hay datos disponibles, FALSE en caso contrario.
 */
bool ADS131E08_isDataAvailable();


/**
 * @brief Obtiene el ID del dispositivo ADS131E08.
 *
 * Esta función lee el registro de ID del ADS131E08 y devuelve el valor del ID del dispositivo.
 *
 * @return ID del dispositivo.
 */
uint8_t ADS131E08_getDeviceID();


/**
 * @brief Obtiene los datos de los canales del ADS131E08.
 *
 * Esta función lee los datos convertidos de los canales del ADS131E08 y los almacena en el arreglo 'data'.
 *
 * @param sampleCnt Puntero a la variable que almacena el contador de muestras.
 * @param data Puntero al arreglo donde se almacenarán los datos de los canales.
 */
void ADS131E08_getChannelData(uint8_t *sampleCnt, uint32_t *data);


/**
 * @brief Configura la señal de prueba del ADS131E08 para un canal específico.
 *
 * Esta función configura el multiplexor del canal especificado para seleccionar la señal de prueba interna del ADS131E08.
 *
 * @param currentChannel Canal para el que se configurará la señal de prueba.
 */
void ADS131E08_configureTestSignal(uint8_t currentChannel);


/**
 * @brief Configura la señal externa del ADS131E08 para un canal específico.
 *
 * Esta función configura el multiplexor del canal especificado para seleccionar la señal externa conectada al ADS131E08.
 *
 * @param currentChannel Canal para el que se configurará la señal externa.
 */
void ADS131E08_configureExternalSignal(uint8_t currentChannel);


/**
 * @brief Selecciona el modo de lectura del ADS131E08 para un canal específico.
 *
 * Esta función configura el multiplexor y la ganancia del canal especificado según el modo de lectura seleccionado.
 *
 * @param currentMode Modo de lectura a seleccionar.
 * @param currentChannel Canal para el que se seleccionará el modo de lectura.
 */
void ADS131E08_selectMode(uint8_t currentMode, uint8_t currentChannel);


/**
 * @brief Selecciona el canal del ADS131E08 para la adquisición de datos.
 *
 * Esta función configura el multiplexor del canal especificado para habilitar la adquisición de datos de ese canal.
 *
 * @param currentChannel Canal a seleccionar.
 */
void ADS131E08_selectChannel(uint8_t currentChannel);


/**
 * @brief Selecciona la frecuencia de muestreo (kSPS) del ADS131E08.
 *
 * Esta función configura la frecuencia de muestreo del ADS131E08 según el valor de 'current_kSPS'.
 *
 * @param current_kSPS Frecuencia de muestreo en kSPS a seleccionar.
 */
void ADS131E08_selectkSPS(uint8_t current_kSPS);


#endif /* ADS131E08_H_ */
