#ifndef GPIO_H_
#define GPIO_H_

#include "lpc_types.h"
#include "board.h"

/** @defgroup Libreria GPIO
 *  @ingroup "Adquisidor de senales biopotenciales"
 *  Driver para controlar los puertos GPIO
 */


/** 
 * Definiciones y declaraciones
 */
#define GPIO_PORT0 0
#define GPIO_PORT1 1
#define GPIO_PORT2 2
#define GPIO_PORT3 3

#define LED1_PORT 2 
#define LED1_PIN  4
#define LED2_PORT 3 
#define LED2_PIN  3
#define LED3_PORT 3 
#define LED3_PIN  4
#define LED4_PORT 3 
#define LED4_PIN  0
#define LED5_PORT 2 
#define LED5_PIN  0
#define LED6_PORT 3 
#define LED6_PIN  12
#define LED7_PORT 5 
#define LED7_PIN  9
#define LED8_PORT 5 
#define LED8_PIN  8
#define LED9_PORT 5 
#define LED9_PIN  3
#define LED10_PORT 5 
#define LED10_PIN  4

/**
 * @brief Inicializar puerto GPIO
 */
void GPIO_Init();


/**
 * @brief Desinicializacion del puerto GPIO
 */
void GPIO_deInit();


/**
 * @brief Establece el estado de un pin GPIO
 * @param port Numero del puerto GPIO 
 * @param pin Numero del pin GPIO
 * @param state TRUE para establecerlo en alto, FALSE para establecerlo el bajo
 */
void GPIO_setPinState(uint8_t port, uint8_t pin, bool state);


/**
 * @brief Obtener el estado de un pin GPIO
 * @param port Numero del puerto GPIO 
 * @param pin Numero del pin GPIO
 * @return TRUE si el pin esta en alto, FALSE si esta en bajo
 */
bool GPIO_getPinState(uint8_t port, uint8_t pin);


/**
 * @brief Establece la direccion de un pin GPIO
 * @param port Numero del puerto GPIO
 * @param pin Numero del pin GPIO
 * @param output: TRUE para salida, FALSE para entrada
 */
void GPIO_setPinDir(uint8_t port, uint8_t pin, bool output);


/**
 * @brief Obtener la direccion de un pin GPIO
 * @param port Numero del puerto GPIO
 * @param pin Numero del pin GPIO
 * @return TRUE si esta como salida, FALSE si esta como entrada
 */
bool GPIO_getPinDir(uint8_t port, uint8_t pin);


/**
 * @brief Alterna un pin GPIO al estado opuesto
 * @param port Numero del puerto GPIO
 * @param pin Numero del pin GPIO
 */
void GPIO_setPinToggle(uint8_t port, uint8_t pin);

void setLed(uint8_t port, uint8_t pin, bool state);

void GPIO_displayOFF();

void GPIO_displayON();

void GPIO_displayCurrentChannel(uint8_t currentChannel);

void GPIO_displayCurrentkSPS(uint8_t current_kSPS);

void GPIO_setBoardLEDs(uint8_t aux);

void GPIO_stopped(uint8_t currentChannel);

void GPIO_selectChannel(uint8_t currentChannel);

void GPIO_select_kSPS(uint8_t current_kSPS);

void GPIO_start(uint8_t currentChannel);

void GPIO_getSignal(uint32_t channelData);


#endif /* GPIO_H_ */