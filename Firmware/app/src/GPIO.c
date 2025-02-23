/*
 * GPIO.c
 *
 * Descripción: Implementación de funciones para la configuración y control de GPIO en la placa EDU-CIAA-NXP.
 * Este módulo proporciona funciones para inicializar, desinicializar, configurar pines, controlar LEDs y mostrar información a través de LEDs.
 */


#include "GPIO.h"      // Incluye el archivo de encabezado GPIO.h, que contiene las definiciones de las funciones y constantes.
#include "UART.h"      // Incluye el archivo de encabezado UART.h para depuración o comunicación de errores.
#include "ADS131E08.h"  // Incluye el archivo de encabezado ADS131E08.h para interactuar con el sensor.
#include "board_api.h"  // Incluye el archivo de encabezado board_api.h, que proporciona funciones para controlar LEDs de la placa.
#include "chip.h"     // Incluye el archivo de encabezado chip.h, que proporciona acceso a las funciones de bajo nivel del microcontrolador.
#include <stdlib.h>  // Incluye el archivo de encabezado stdlib.h.

uint8_t LED_ARRAY[10] = {LED1_PORT, LED1_PIN};  // Inicializa un arreglo con los puertos y pines de los LEDs.


/**
 * @brief Inicialización del puerto GPIO.
 *
 * Esta función inicializa el puerto GPIO y configura los pines necesarios para el proyecto, incluyendo pines para el sensor ADS131E08 y LEDs.
 */
void GPIO_Init()
{
   /* Configuración del puerto GPIO. */
   Chip_GPIO_Init(LPC_GPIO_PORT);

   /* Mapeo de los pines del puerto GPIO. */

   /* TRUE (1) para salida, FALSE (0) para entrada. */
   Chip_SCU_PinMux(4, 5, MD_PUP | MD_EZI | MD_ZI, FUNC0); // Mapeo GPIO2[5] en P4_5 RESET (Salida).      -------- PIN LCD2 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, 2, 5, 1);        // Establecer RESET como Salida.                  
   Chip_SCU_PinMux(4, 8, MD_PUP | MD_EZI | MD_ZI, FUNC0); // Mapeo GPIO5[12] en P4_8 PWDN (Salida).      -------- PIN LCD_RS ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, 5, 12, 1);       // Establecer PWDN como Salida.
   Chip_SCU_PinMux(4, 10, MD_PUP | MD_EZI | MD_ZI, FUNC4); // Mapeo GPIO5[14] en P4_10 DRDY (Entrada).   -------- PIN LCD4 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, 5, 14, 0);       // Establecer DRDY como Entrada.
   Chip_SCU_PinMux(1, 20, MD_PUP | MD_EZI | MD_ZI, FUNC0); // Mapeo GPIO0[15] en P1_20 CS (Salida).      -------- PIN ENET_TXD1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, 0, 15, 1);       // Establecer CS como Salida.

   // PIN UTILIZADO PARA DEBUG.
   Chip_SCU_PinMux(4, 9, MD_PUP | MD_EZI | MD_ZI, FUNC4); // PIN LCD_EN (Salida).
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, 5, 13, 1);

   /* LEDs. */
   Chip_SCU_PinMux(4, 4, MD_PUP | MD_EZI | MD_ZI, FUNC0); // Mapeo GPIO2[4] en P4_4 LED1 (Salida). -------- PIN LCD1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, 2, 4, 1);  // Establecer LED1 como Salida.
   Chip_SCU_PinMux(6,4,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[3] en P6_4 LED2 (Salida).	      -------- PIN GPIO1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,3,1);		// Establecer LED2 como Salida.
   Chip_SCU_PinMux(6,5,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[4] en P6_5 LED3 (Salida).        -------- PIN GPIO2 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,4,1);		// Establecer LED3 como Salida
   Chip_SCU_PinMux(6,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[0] en P6_1 LED4 (Salida).	      -------- PIN GPIO0 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,0,1);		// Establecer LED4 como Salida
   Chip_SCU_PinMux(4,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO2[0] en P4_0 LED5 (Salida).        -------- PIN TFIL0 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,2,0,1);		// Establecer LED5 como Salida
   Chip_SCU_PinMux(7,4,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[12] en P7_4 LED6 (Salida).       -------- PIN TCOL1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,12,1);		// Establecer LED6 como Salida
   Chip_SCU_PinMux(3,2,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[9] en P3_2 LED7 (Salida).        -------- PIN CAN_TD ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,9,1);		// Establecer LED7 como Salida
   Chip_SCU_PinMux(3,1,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[8] en P3_1 LED8 (Salida).	      -------- PIN CAN_RD ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,8,1);		// Establecer LED8 como Salida
   Chip_SCU_PinMux(2,3,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[3] en P2_3 LED9 (Salida).        -------- PIN RS232_TX ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,3,1);		// Establecer LED9 como Salida
   Chip_SCU_PinMux(2,4,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[4] en P2_4 LED10 (Salida).       -------- PIN RS232_RX ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,4,1);		// Establecer LED10 como Salida
}


/**
 * @brief Desinicialización del puerto GPIO.
 *
 * Esta función desinicializa el puerto GPIO, liberando los recursos utilizados.
 */
void GPIO_deInit()
{
   Chip_GPIO_DeInit(LPC_GPIO_PORT);
}


/**
 * @brief Establece el estado de un pin GPIO.
 *
 * @param port Número del puerto GPIO.
 * @param pin Número del pin GPIO.
 * @param state TRUE para establecerlo en alto, FALSE para establecerlo en bajo.
 */
void GPIO_setPinState(uint8_t port, uint8_t pin, bool state)
{
   Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, state);
}


/**
 * @brief Obtiene el estado de un pin GPIO.
 *
 * @param port Número del puerto GPIO.
 * @param pin Número del pin GPIO.
 * @return TRUE si el pin está en alto, FALSE si está en bajo.
 */
bool GPIO_getPinState(uint8_t port, uint8_t pin)
{
   return Chip_GPIO_GetPinState(LPC_GPIO_PORT, port, pin);
}


/**
 * @brief Establece la dirección de un pin GPIO.
 *
 * @param port Número del puerto GPIO.
 * @param pin Número del pin GPIO.
 * @param output TRUE para salida, FALSE para entrada.
 */
void GPIO_setPinDir(uint8_t port, uint8_t pin, bool output)
{
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, port, pin, output);
}


/**
 * @brief Obtiene la dirección de un pin GPIO.
 *
 * @param port Número del puerto GPIO.
 * @param pin Número del pin GPIO.
 * @return TRUE si está configurado como salida, FALSE si está configurado como entrada.
 */
bool GPIO_getPinDir(uint8_t port, uint8_t pin)
{
   return Chip_GPIO_GetPinDIR(LPC_GPIO_PORT, port, pin);
}


/**
 * @brief Alterna el estado de un pin GPIO al estado opuesto.
 *
 * @param port Número del puerto GPIO.
 * @param pin Número del pin GPIO.
 */
void GPIO_setPinToggle(uint8_t port, uint8_t pin)
{
   Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, port, pin);
}


/**
 * @brief Establece el estado de un LED.
 *
 * @param port Número del puerto GPIO del LED.
 * @param pin Número del pin GPIO del LED.
 * @param state TRUE para apagar el LED, FALSE para encender el LED.
 */
void setLed(uint8_t port, uint8_t pin, bool state)
{
   Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, !state);
}


/**
 * @brief Apaga todos los LEDs.
 */
void GPIO_displayOFF() {
   setLed(LED1_PORT,LED1_PIN, true);
   setLed(LED2_PORT,LED2_PIN, true);
   setLed(LED3_PORT,LED3_PIN, true);
   setLed(LED4_PORT,LED4_PIN, true);
   setLed(LED5_PORT,LED5_PIN, true);
   setLed(LED6_PORT,LED6_PIN, true);
   setLed(LED7_PORT,LED7_PIN, true);
   setLed(LED8_PORT,LED8_PIN, true);
   setLed(LED9_PORT,LED9_PIN, true);
   setLed(LED10_PORT,LED10_PIN, true);
}


/**
 * @brief Enciende todos los LEDs.
 */
void GPIO_displayON() {
   setLed(LED1_PORT,LED1_PIN, false);
   setLed(LED2_PORT,LED2_PIN, false);
   setLed(LED3_PORT,LED3_PIN, false);
   setLed(LED4_PORT,LED4_PIN, false);
   setLed(LED5_PORT,LED5_PIN, false);
   setLed(LED6_PORT,LED6_PIN, false);
   setLed(LED7_PORT,LED7_PIN, false);
   setLed(LED8_PORT,LED8_PIN, false);
   setLed(LED9_PORT,LED9_PIN, false);
   setLed(LED10_PORT,LED10_PIN, false);
}


/**
 * @brief Muestra el canal actual a través de LEDs.
 *
 * @param currentChannel Número del canal actual.
 */
void GPIO_displayCurrentChannel(uint8_t currentChannel) {
   switch (currentChannel)
   {
      case 5:
      {
         setLed(LED1_PORT,LED1_PIN, false);
         break;
      }
      case 6:
      {
         setLed(LED2_PORT,LED2_PIN, false);
         break;
      }
      case 7:
      {
         setLed(LED3_PORT,LED3_PIN, false);
         break;
      }
      case 8:
      {
         setLed(LED4_PORT,LED4_PIN, false);
         break;
      }
      case 9:
      {
         setLed(LED5_PORT,LED5_PIN, false);
         break;
      }
      case 10:
      {
         setLed(LED6_PORT,LED6_PIN, false);
         break;
      }
      case 11:
      {
         setLed(LED7_PORT,LED7_PIN, false);
         break;
      }
      case 12:
      {
         setLed(LED8_PORT,LED8_PIN, false);
         break;
      }
      default:
      {
         break;
      }
   }
}


/**
 * @brief Muestra la frecuencia de muestreo actual (kSPS) a través de LEDs.
 *
 * @param current_kSPS Frecuencia de muestreo actual.
 */
void GPIO_displayCurrentkSPS(uint8_t current_kSPS) {
   switch (current_kSPS)
   {
      case 6:
      {
         setLed(LED10_PORT,LED10_PIN, false);
         break;
      }
      case 5:
      {
         setLed(LED9_PORT,LED9_PIN, false);
         break;
      }
      case 4:
      {
         setLed(LED8_PORT,LED8_PIN, false);
         break;
      }
      case 3:
      {
         setLed(LED7_PORT,LED7_PIN, false);
         break;
      }
      case 2:
      {
         setLed(LED6_PORT,LED6_PIN, false);
         break;
      }
      default:
         break;
   }
}


/**
 * @brief Muestra el modo actual a través de LEDs.
 *
 * @param currentMode Modo actual.
 */
void GPIO_displayCurrentMode(uint8_t currentMode) {
   switch (currentMode)
   {
      case 0:
      {
         setLed(LED1_PORT,LED1_PIN, false);
         break;
      }
      case 1:
      {
         setLed(LED2_PORT,LED2_PIN, false);
         break;
      }
      default:
         break;
   }
}


/**
 * @brief Configura los LEDs de la placa para mostrar el canal actual.
 *
 * @param aux Número del canal actual.
 */
void GPIO_setBoardLEDs_channel(uint8_t aux) {
   switch (aux)
   {
      case 5:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 6:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 7:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 8:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 9:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 10:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 11:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 12:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, true);
         break;
      }
      default:
         break;
   }
}


/**
 * @brief Configura los LEDs de la placa para mostrar la frecuencia de muestreo actual (kSPS).
 *
 * @param aux Frecuencia de muestreo actual (kSPS).
 */
void GPIO_setBoardLEDs_kSPS(uint8_t aux) {
   switch (aux)
   {
      case 6:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 5:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 4:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 3:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 2:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 1:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 0:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, false);
         break;
      }
      default:
         break;
   }
}


/**
 * @brief Configura los LEDs de la placa para mostrar el modo actual.
 *
 * @param aux Modo actual.
 */
void GPIO_setBoardLEDs_mode(uint8_t aux) {
   switch (aux)
   {
      case 0:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 1:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      default:
         break;
   }
}


/**
 * @brief Configura los LEDs para indicar que el sistema está detenido.
 *
 * @param currentChannel Canal actual.
 */
void GPIO_stopped(uint8_t currentChannel) {
   GPIO_displayOFF();
   GPIO_displayCurrentChannel(currentChannel);
   Board_LED_Set(LED_RED, false);
   Board_LED_Set(LED_GREEN, true);
   Board_LED_Set(LED_BLUE, true);
   GPIO_setBoardLEDs_channel(currentChannel);
}


/**
 * @brief Configura los LEDs para indicar la selección del canal.
 *
 * @param currentChannel Canal seleccionado.
 */
void GPIO_selectChannel(uint8_t currentChannel) {
   GPIO_displayOFF();
   GPIO_displayCurrentChannel(currentChannel);
   Board_LED_Set(LED_RED, true);
   Board_LED_Set(LED_GREEN, true);
   Board_LED_Set(LED_BLUE, false);
   GPIO_setBoardLEDs_channel(currentChannel);
}


/**
 * @brief Configura los LEDs para indicar la selección de la frecuencia de muestreo (kSPS).
 *
 * @param current_kSPS Frecuencia de muestreo seleccionada (kSPS).
 */
void GPIO_select_kSPS(uint8_t current_kSPS) {
   GPIO_displayOFF();
   GPIO_displayCurrentkSPS(current_kSPS);
   Board_LED_Set(LED_RED, false);
   Board_LED_Set(LED_GREEN, true);
   Board_LED_Set(LED_BLUE, false);
   GPIO_setBoardLEDs_kSPS(current_kSPS);
}


/**
 * @brief Configura los LEDs para indicar la selección del modo.
 *
 * @param currentMode Modo seleccionado.
 */
void GPIO_selectMode(uint8_t currentMode) {
   GPIO_displayOFF();
   GPIO_displayCurrentMode(currentMode);
   Board_LED_Set(LED_RED, true);
   Board_LED_Set(LED_GREEN, false);
   Board_LED_Set(LED_BLUE, false);
   GPIO_setBoardLEDs_mode(currentMode);
}


/**
 * @brief Configura los LEDs para indicar que el sistema está en funcionamiento.
 */
void GPIO_start(uint8_t currentChannel) {
   GPIO_displayOFF();
   Board_LED_Set(LED_RED, true);
   Board_LED_Set(LED_GREEN, false);
   Board_LED_Set(LED_BLUE, true);
}


/**
 * @brief Muestra el valor de la señal a través de LEDs.
 *
 * @param channelData Valor de la señal del canal.
 */
void GPIO_getSignal(uint32_t channelData) {
   GPIO_displayOFF();
   uint8_t negativo = 0;
   int32_t data = channelData;
   uint8_t msb = (data >> 23) & 1;
   if (msb == 1) {
      negativo = 1;
   }   
   data &= 0x007FFFFF;
   if (negativo) {
      data = -data;
   }
   
   if (data > 6710484) {
      setLed(LED10_PORT,LED10_PIN, false);
   }
   if (data > 5032863) {
      setLed(LED9_PORT,LED9_PIN, false);
   }
   if (data > 3355242) {
      setLed(LED8_PORT,LED8_PIN, false);
   }
   if (data > 1677621) {
      setLed(LED7_PORT,LED7_PIN, false);
   }
   if (data > 0) {
      setLed(LED6_PORT,LED6_PIN, false);
   }
   if (data < 0) {
      setLed(LED5_PORT,LED5_PIN, false);
   }
   if (data < -1677621) {
      setLed(LED4_PORT,LED4_PIN, false);
   }
   if (data < -3355242) {
      setLed(LED3_PORT,LED3_PIN, false);
   }
   if (data < -5032863) {
      setLed(LED2_PORT,LED2_PIN, false);
   }
   if (data < -6710484) {
      setLed(LED1_PORT,LED1_PIN, false);
   }
}
