#ifndef FUNCIONAMIENTO_H_
#define FUNCIONAMIENTO_H_


#include "lpc_types.h" // Incluye definiciones de tipos de datos para microcontroladores LPC.


/**
 * @brief Bandera que indica si el ADS131E08 está adquiriendo datos o no.
 */
extern bool is_running; 

/**
 * @brief Variable utilizada para el funcionamiento del delay a través del SysTick.
 */
static volatile uint32_t tick_ct = 0; 

/**
 * @brief Variable utilizada para el control de los diferentes estados del programa.
 */
uint8_t estado;

/**
 * @brief Variable utilizada para indicar el modo en el cual se leen las señales desde el sensor.
 */
uint8_t currentMode;

/**
 * @brief Variable utilizada para indicar el canal que se visualizará en el vúmetro.
 */
uint8_t currentChannel;

/**
 * @brief Variable utilizada para indicar la cantidad de muestras por segundos actual.
 */
uint8_t current_kSPS;


/**
 * @brief Inicializar el ADS131E09 y enviar mensaje de bienvenida.
 */
void Funcionamiento_Init();


/**
 * @brief Funcionamiento general del sistema.
 */
void Funcionamiento_Menu();


/**
 * @brief Detecta si un pulsador ha sido presionado y realiza antirrebote.
 * @param pulsador Número del pulsador a verificar.
 * @return TRUE si el pulsador fue presionado, FALSE en caso contrario.
 */
bool getPulsador(uint8_t pulsador);


/**
 * @brief Manejador de la interrupción del SysTick.
 * Incrementa el contador de ticks del SysTick.
 */
void SysTick_Handler(void);


/**
 * @brief Genera un retardo en milisegundos utilizando el SysTick.
 * @param tk Tiempo de retardo en milisegundos.
 */
void delayMs(uint32_t tk);


/**
 * @brief Genera un retardo en microsegundos utilizando el SysTick.
 * @param tk Tiempo de retardo en microsegundos.
 */
void delayUs(uint32_t tk);


#endif /* FUNCIONAMIENTO_H_ */
