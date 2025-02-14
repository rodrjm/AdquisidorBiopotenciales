#ifndef FUNCIONAMIENTO_H_
#define FUNCIONAMIENTO_H_

#include "lpc_types.h"



/**
 * @brief Bandera que indica si el ADS131E08 esta adquiriendo data o no
 */
extern bool is_running;

/**
 * @brief Variable utilizada para el funcionamiento del delay a traves del SysTick
 */
static volatile uint32_t tick_ct = 0;

/**
 * @brief Variable utilizada para el control de los diferentes estados del programa
 */
uint8_t estado;

/**
 * @brief Variable utilizada para indicar el modo en el cual se leen las senales desde el sensor
 */
uint8_t currentMode;

/**
 * @brief Variable utilizada para indicar el canal que se visualizara en el vumetro
 */
uint8_t currentChannel;

/**
 * @brief Variable utilizada para indicar la cantidad de muestras por segundos actual
 */
uint8_t current_kSPS;


/**
 * @brief Inicializar el ADS131E09 y enviar mensaje de bienvenida
 */
void Funcionamiento_Init();

/**
 * @brief Funcionamiento general del sistema
 */
void Funcionamiento_Menu();

bool getPulsador(uint8_t pulsador);

void SysTick_Handler(void);

void delayMs(uint32_t tk);

void delayUs(uint32_t tk);
void generate_signal(uint32_t channelData, bool signal);
void generate_triangle_wave(uint32_t channelData);

#endif /* FUNCIONAMIENTO_H_ */