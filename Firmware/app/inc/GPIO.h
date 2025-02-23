#ifndef GPIO_H_
#define GPIO_H_


#include "lpc_types.h" // Incluye el archivo de encabezado lpc_types.h, que define tipos de datos est�ndar para microcontroladores LPC.
#include "board.h"     // Incluye el archivo de encabezado board.h, que define constantes y funciones relacionadas con la placa.


/**
 * @defgroup Libreria GPIO
 * @ingroup "Adquisidor de se�ales biopotenciales"
 * Driver para controlar los puertos GPIO.
 */


/**
 * Definiciones y declaraciones.
 */
#define GPIO_PORT0 0 // Definici�n del n�mero de puerto GPIO0.
#define GPIO_PORT1 1 // Definici�n del n�mero de puerto GPIO1.
#define GPIO_PORT2 2 // Definici�n del n�mero de puerto GPIO2.
#define GPIO_PORT3 3 // Definici�n del n�mero de puerto GPIO3.

#define LED1_PORT 2  // Definici�n del puerto del LED1.
#define LED1_PIN  4  // Definici�n del pin del LED1.
#define LED2_PORT 3  // Definici�n del puerto del LED2.
#define LED2_PIN  3  // Definici�n del pin del LED2.
#define LED3_PORT 3  // Definici�n del puerto del LED3.
#define LED3_PIN  4  // Definici�n del pin del LED3.
#define LED4_PORT 3  // Definici�n del puerto del LED4.
#define LED4_PIN  0  // Definici�n del pin del LED4.
#define LED5_PORT 2  // Definici�n del puerto del LED5.
#define LED5_PIN  0  // Definici�n del pin del LED5.
#define LED6_PORT 3  // Definici�n del puerto del LED6.
#define LED6_PIN  12 // Definici�n del pin del LED6.
#define LED7_PORT 5  // Definici�n del puerto del LED7.
#define LED7_PIN  9  // Definici�n del pin del LED7.
#define LED8_PORT 5  // Definici�n del puerto del LED8.
#define LED8_PIN  8  // Definici�n del pin del LED8.
#define LED9_PORT 5  // Definici�n del puerto del LED9.
#define LED9_PIN  3  // Definici�n del pin del LED9.
#define LED10_PORT 5 // Definici�n del puerto del LED10.
#define LED10_PIN 4  // Definici�n del pin del LED10.


/**
 * @brief Inicializar puerto GPIO.
 *
 * Prototipo de la funci�n GPIO_Init(), que inicializa el puerto GPIO.
 */
void GPIO_Init();


/**
 * @brief Desinicializaci�n del puerto GPIO.
 *
 * Prototipo de la funci�n GPIO_deInit(), que desinicializa el puerto GPIO.
 */
void GPIO_deInit();


/**
 * @brief Establece el estado de un pin GPIO.
 *
 * Prototipo de la funci�n GPIO_setPinState(), que establece el estado de un pin GPIO.
 *
 * @param port N�mero del puerto GPIO.
 * @param pin N�mero del pin GPIO.
 * @param state TRUE para establecerlo en alto, FALSE para establecerlo en bajo.
 */
void GPIO_setPinState(uint8_t port, uint8_t pin, bool state);


/**
 * @brief Obtener el estado de un pin GPIO.
 *
 * Prototipo de la funci�n GPIO_getPinState(), que obtiene el estado de un pin GPIO.
 *
 * @param port N�mero del puerto GPIO.
 * @param pin N�mero del pin GPIO.
 * @return TRUE si el pin est� en alto, FALSE si est� en bajo.
 */
bool GPIO_getPinState(uint8_t port, uint8_t pin);


/**
 * @brief Establece la direcci�n de un pin GPIO.
 *
 * Prototipo de la funci�n GPIO_setPinDir(), que establece la direcci�n de un pin GPIO.
 *
 * @param port N�mero del puerto GPIO.
 * @param pin N�mero del pin GPIO.
 * @param output TRUE para salida, FALSE para entrada.
 */
void GPIO_setPinDir(uint8_t port, uint8_t pin, bool output);


/**
 * @brief Obtener la direcci�n de un pin GPIO.
 *
 * Prototipo de la funci�n GPIO_getPinDir(), que obtiene la direcci�n de un pin GPIO.
 *
 * @param port N�mero del puerto GPIO.
 * @param pin N�mero del pin GPIO.
 * @return TRUE si est� configurado como salida, FALSE si est� configurado como entrada.
 */
bool GPIO_getPinDir(uint8_t port, uint8_t pin);


/**
 * @brief Alterna un pin GPIO al estado opuesto.
 *
 * Prototipo de la funci�n GPIO_setPinToggle(), que alterna el estado de un pin GPIO.
 *
 * @param port N�mero del puerto GPIO.
 * @param pin N�mero del pin GPIO.
 */
void GPIO_setPinToggle(uint8_t port, uint8_t pin);


/**
 * @brief Establece el estado de un LED.
 *
 * Prototipo de la funci�n setLed(), que establece el estado de un LED.
 *
 * @param port N�mero del puerto GPIO del LED.
 * @param pin N�mero del pin GPIO del LED.
 * @param state TRUE para apagar el LED, FALSE para encender el LED.
 */
void setLed(uint8_t port, uint8_t pin, bool state);


/**
 * @brief Apaga todos los LEDs.
 *
 * Prototipo de la funci�n GPIO_displayOFF(), que apaga todos los LEDs.
 */
void GPIO_displayOFF();


/**
 * @brief Enciende todos los LEDs.
 *
 * Prototipo de la funci�n GPIO_displayON(), que enciende todos los LEDs.
 */
void GPIO_displayON();


/**
 * @brief Muestra el canal actual a trav�s de LEDs.
 *
 * Prototipo de la funci�n GPIO_displayCurrentChannel(), que muestra el canal actual a trav�s de LEDs.
 *
 * @param currentChannel N�mero del canal actual.
 */
void GPIO_displayCurrentChannel(uint8_t currentChannel);


/**
 * @brief Muestra la frecuencia de muestreo actual (kSPS) a trav�s de LEDs.
 *
 * Prototipo de la funci�n GPIO_displayCurrentkSPS(), que muestra la frecuencia de muestreo actual (kSPS) a trav�s de LEDs.
 *
 * @param current_kSPS Frecuencia de muestreo actual (kSPS).
 */
void GPIO_displayCurrentkSPS(uint8_t current_kSPS);


/**
 * @brief Muestra el modo actual a trav�s de LEDs.
 *
 * Prototipo de la funci�n GPIO_displayCurrentMode(), que muestra el modo actual a trav�s de LEDs.
 *
 * @param currentMode Modo actual.
 */
void GPIO_displayCurrentMode(uint8_t currentMode);


/**
 * @brief Configura los LEDs de la placa para mostrar el canal actual.
 *
 * Prototipo de la funci�n GPIO_setBoardLEDs_channel(), que configura los LEDs de la placa para mostrar el canal actual.
 *
 * @param aux N�mero del canal actual.
 */
void GPIO_setBoardLEDs_channel(uint8_t aux);


/**
 * @brief Configura los LEDs de la placa para mostrar la frecuencia de muestreo actual (kSPS).
 *
 * Prototipo de la funci�n GPIO_setBoardLEDs_kSPS(), que configura los LEDs de la placa para mostrar la frecuencia de muestreo actual (kSPS).
 *
 * @param aux Frecuencia de muestreo actual (kSPS).
 */
void GPIO_setBoardLEDs_kSPS(uint8_t aux);


/**
 * @brief Configura los LEDs de la placa para mostrar el modo actual.
 *
 * Prototipo de la funci�n GPIO_setBoardLEDs_mode(), que configura los LEDs de la placa para mostrar el modo actual.
 *
 * @param aux Modo actual.
 */
void GPIO_setBoardLEDs_mode(uint8_t aux);


/**
 * @brief Configura los LEDs para indicar que el sistema est� detenido.
 *
 * Prototipo de la funci�n GPIO_stopped(), que configura los LEDs para indicar que el sistema est� detenido.
 *
 * @param currentChannel Canal actual.
 */
void GPIO_stopped(uint8_t currentChannel);


/**
 * @brief Configura los LEDs para indicar la selecci�n del canal.
 *
 * Prototipo de la funci�n GPIO_selectChannel(), que configura los LEDs para indicar la selecci�n del canal.
 *
 * @param currentChannel Canal seleccionado.
 */
void GPIO_selectChannel(uint8_t currentChannel);


/**
 * @brief Configura los LEDs para indicar la selecci�n de la frecuencia de muestreo (kSPS).
 *
 * Prototipo de la funci�n GPIO_select_kSPS(), que configura los LEDs para indicar la selecci�n de la frecuencia de muestreo (kSPS).
 *
 * @param current_kSPS Frecuencia de muestreo seleccionada (kSPS).
 */
void GPIO_select_kSPS(uint8_t current_kSPS);


/**
 * @brief Configura los LEDs para indicar la selecci�n del modo.
 *
 * Prototipo de la funci�n GPIO_selectMode(), que configura los LEDs para indicar la selecci�n del modo.
 *
 * @param currentMode Modo seleccionado.
 */
void GPIO_selectMode(uint8_t currentMode);


/**
 * @brief Configura los LEDs para indicar que el sistema est� en funcionamiento (inicio).
 *
 * Prototipo de la funci�n GPIO_start(), que configura los LEDs para indicar que el sistema est� en funcionamiento (inicio).
 */
void GPIO_start(uint8_t currentChannel);


/**
 * @brief Muestra el valor de la se�al a trav�s de LEDs.
 *
 * Prototipo de la funci�n GPIO_getSignal(), que muestra el valor de la se�al a trav�s de LEDs.
 *
 * @param channelData Valor de la se�al del canal.
 */
void GPIO_getSignal(uint32_t channelData);


#endif /* GPIO_H_ */
