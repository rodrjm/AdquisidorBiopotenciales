/*
 	 * GPIO.c
*/

#include "GPIO.h"
#include "chip.h"




/**
 	 * @brief Inicializar puerto GPIO
*/
void GPIO_init()
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