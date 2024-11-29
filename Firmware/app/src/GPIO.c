/*
 	 * GPIO.c
*/

#include "GPIO.h"
#include "chip.h"




/**
 	 * @brief Inicializar puerto GPIO
*/
void GPIO_Init()
{
	/* Configuracion del puerto GPIO */
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/* Mapeo de los pines del puerto GPIO */

   /* TRUE (1) para salida, FALSE (0) para entrada */
   Chip_SCU_PinMux(4,5,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO2[5] en P4_5  RESET	-------- PIN LCD2 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,2,5,1);		// Establecer RESET como Salida
   Chip_SCU_PinMux(4,8,MD_PUP|MD_EZI|MD_ZI,FUNC0);  // Mapeo GPIO5[12] en P4_8    PWDN/	-------- PIN LCD_RS ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,12,1);		// Establecer PWDN como Salida
   Chip_SCU_PinMux(4,10,MD_PUP|MD_EZI|MD_ZI,FUNC4);  // Mapeo GPIO5[14] en P4_10    DRDY/	-------- PIN LCD4 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,14,0);		// Establecer DRDY como Entrada
   Chip_SCU_PinMux(1,20,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO0[15] en P1_20   CS/	-------- PIN ENET_TXD1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,0,15,1);		// Establecer CS como Salida
   //-------------------- PIN UTILIZADO PARA DEBUG	----------------------------------
   Chip_SCU_PinMux(4,9,MD_PUP|MD_EZI|MD_ZI,FUNC4);  								  //-------- PIN LCD_EN ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,13,1);
   //				-------------------------------------------------------------------

   /* LEDs */
   Chip_SCU_PinMux(4,4,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO2[4] en P4_4   LED1/	-------- PIN LCD1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,2,4,1);		// Establecer LED1 como Salida
   Chip_SCU_PinMux(6,4,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[3] en P6_4   LED2/	-------- PIN GPIO1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,3,1);		// Establecer LED2 como Salida
   Chip_SCU_PinMux(6,5,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[4] en P6_5   LED3/	-------- PIN GPIO2 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,4,1);		// Establecer LED3 como Salida
   Chip_SCU_PinMux(6,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[0] en P6_1   LED4/	-------- PIN GPIO0 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,0,1);		// Establecer LED4 como Salida
   Chip_SCU_PinMux(4,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO2[0] en P4_0   LED5/	-------- PIN TFIL0 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,2,0,1);		// Establecer LED5 como Salida
   Chip_SCU_PinMux(7,4,MD_PUP|MD_EZI|MD_ZI,FUNC0); // Mapeo GPIO3[12] en P7_4   LED6/	-------- PIN TCOL1 ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,3,12,1);		// Establecer LED6 como Salida
   Chip_SCU_PinMux(3,2,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[9] en P3_2   LED7/	-------- PIN CAN_TD ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,9,1);		// Establecer LED7 como Salida
   Chip_SCU_PinMux(3,1,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[8] en P3_1   LED8/	-------- PIN CAN_RD ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,8,1);		// Establecer LED8 como Salida
   Chip_SCU_PinMux(2,3,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[3] en P2_3   LED9/	-------- PIN RS232_TX ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,3,1);		// Establecer LED9 como Salida
   Chip_SCU_PinMux(2,4,MD_PUP|MD_EZI|MD_ZI,FUNC4); // Mapeo GPIO5[4] en P2_4   LED10/	-------- PIN RS232_RX ----------
   Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,4,1);		// Establecer LED10 como Salida
   
   
   /*	Chip_SCU_PinMux(4,8,MD_PUP|MD_EZI|MD_ZI,FUNC4);  // Mapeo GPIO5[12] en P4_8   CLK
   		Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,12,1);
		Chip_SCU_PinMux(4,8,MD_PUP|MD_EZI|MD_ZI,FUNC4);  // Mapeo GPIO5[12] en P4_8   START
		Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,12,1);
	*/
}


/**
 	 * @brief Desinicializacion del puerto GPIO
*/
void GPIO_deInit()
{
	Chip_GPIO_DeInit(LPC_GPIO_PORT);
}


/**
 * @brief Establece el estado de un pin GPIO
 * @param port Numero del puerto GPIO 
 * @param pin Numero del pin GPIO
 * @param state TRUE para establecerlo en alto, FALSE para establecerlo el bajo
 */
void GPIO_setPinState(uint8_t port, uint8_t pin, bool state)
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,port, pin, state);
}


/**
 * @brief Obtener el estado de un pin GPIO
 * @param port Numero del puerto GPIO 
 * @param pin Numero del pin GPIO
 * @return TRUE si el pin esta en alto, FALSE si esta en bajo
 */
bool GPIO_getPinState(uint8_t port, uint8_t pin)
{
	return Chip_GPIO_GetPinState(LPC_GPIO_PORT, port, pin);
}


/**
 * @brief Establece la direccion de un pin GPIO
 * @param port Numero del puerto GPIO
 * @param pin Numero del pin GPIO
 * @param output: TRUE para salida, FALSE para entrada
 */
void GPIO_setPinDir(uint8_t port, uint8_t pin, bool output)
{
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, port, pin, output);
}


/**
 * @brief Obtener la direccion de un pin GPIO
 * @param port Numero del puerto GPIO
 * @param pin Numero del pin GPIO
 * @return TRUE si esta como salida, FALSE si esta como entrada
 */
bool GPIO_getPinDir(uint8_t port, uint8_t pin)
{
	return Chip_GPIO_GetPinDIR(LPC_GPIO_PORT, port, pin);
}


/**
 * @brief Alterna un pin GPIO al estado opuesto
 * @param port Numero del puerto GPIO
 * @param pin Numero del pin GPIO
 */
void GPIO_setPinToggle(uint8_t port, uint8_t pin)
{
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, port, pin);
}

void setLed(uint8_t port,uint8_t pin,bool state){
   Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin,!state);
}

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

void GPIO_displayCurrentChannel(uint8_t currentChannel) {
   switch (currentChannel)
   {
      case 1:
      {
         setLed(LED1_PORT,LED1_PIN, false);
         break;
      }
      case 2:
      {
         setLed(LED2_PORT,LED2_PIN, false);
         break;
      }
      case 3:
      {
         setLed(LED3_PORT,LED3_PIN, false);
         break;
      }
      case 4:
      {
         setLed(LED4_PORT,LED4_PIN, false);
         break;
      }
      case 5:
      {
         setLed(LED5_PORT,LED5_PIN, false);
         break;
      }
      case 6:
      {
         setLed(LED6_PORT,LED6_PIN, false);
         break;
      }
      case 7:
      {
         setLed(LED7_PORT,LED7_PIN, false);
         break;
      }
      case 8:
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

void GPIO_displayCurrentkSPS(uint8_t current_kSPS) {
   switch (current_kSPS)
   {
      case 1:
      {
         setLed(LED10_PORT,LED10_PIN, false);
         break;
      }
      case 2:
      {
         setLed(LED9_PORT,LED9_PIN, false);
         break;
      }
      case 4:
      {
         setLed(LED8_PORT,LED8_PIN, false);
         break;
      }
      default:
         break;
   }
}

void GPIO_setBoardLEDs(uint8_t aux) {
   switch (aux)
   {
      case 1:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 2:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 3:
      {
         Board_LED_Set(LED_1, true);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 4:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 5:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, true);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 6:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, true);
         break;
      }
      case 7:
      {
         Board_LED_Set(LED_1, false);
         Board_LED_Set(LED_2, false);
         Board_LED_Set(LED_3, false);
         break;
      }
      case 8:
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

void GPIO_stopped(uint8_t currentChannel) {
   GPIO_displayOFF();
   Board_LED_Set(LED_RED, false);
   Board_LED_Set(LED_GREEN, true);
   Board_LED_Set(LED_BLUE, true);
   GPIO_setBoardLEDs(currentChannel);
}

void GPIO_selectChannel(uint8_t currentChannel) {
   GPIO_displayOFF();
   GPIO_displayCurrentChannel(currentChannel);
   Board_LED_Set(LED_RED, true);
   Board_LED_Set(LED_GREEN, true);
   Board_LED_Set(LED_BLUE, false);
   GPIO_setBoardLEDs(currentChannel);
}

void GPIO_select_kSPS(uint8_t current_kSPS) {
   GPIO_displayOFF();
   GPIO_displayCurrentkSPS(current_kSPS);
   Board_LED_Set(LED_RED, true);
   Board_LED_Set(LED_BLUE, false);
   Board_LED_Set(LED_GREEN, false);
   GPIO_setBoardLEDs(current_kSPS);
}

void GPIO_start(uint8_t currentChannel) {
   GPIO_displayOFF();
   Board_LED_Set(LED_RED, true);
   Board_LED_Set(LED_GREEN, false);
   Board_LED_Set(LED_BLUE, true);
}

void GPIO_getSignal(uint32_t channelData) {
   if (channelData > 0x00666664) {
      setLed(LED1_PORT,LED1_PIN, false);
   }
   if (channelData > 0x004CCCCB) {
      setLed(LED2_PORT,LED2_PIN, false);
   }
   if (channelData > 0x00333332) {
      setLed(LED3_PORT,LED3_PIN, false);
   }
   if (channelData > 0x00199999) {
      setLed(LED4_PORT,LED4_PIN, false);
   }
   if (channelData > 0x00000000) {
      setLed(LED5_PORT,LED5_PIN, false);
   }
   if (channelData < 0x00000000) {
      setLed(LED6_PORT,LED6_PIN, false);
   }
   if (channelData < 0xFFE66667) {
      setLed(LED7_PORT,LED7_PIN, false);
   }
   if (channelData < 0xFFCCCCCE) {
      setLed(LED8_PORT,LED8_PIN, false);
   }
   if (channelData < 0xFFB33335) {
      setLed(LED9_PORT,LED9_PIN, false);
   }
   if (channelData < 0xFF99999C) {
      setLed(LED10_PORT,LED10_PIN, false);
   }
}