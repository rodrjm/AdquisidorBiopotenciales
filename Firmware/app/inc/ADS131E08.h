/*
 	 * ADS131E08.h
*/

#ifndef ADS131E08_H_
#define ADS131E08_H_

#include "lpc_types.h"
#include "stdint.h"
#include "stdbool.h"


/** 	@defgroup Libreria ADS131E08
 	 *  @ingroup "Adquisidor de señales biopotenciales"
 	 *  Driver para controlar el ADS131E08
*/


/** 
 	 * Definiciones y declaraciones
*/

// Declaracion de pines y puertos para la conexion entre el ADS131E08 y la EDU-CIAA-NXP
#define ADS_RST_PORT    2	// ADS Reset port
#define ADS_RST_PIN		5	// ADS Reset pin

//#define ADS_CLK_PIN	12	// ADS CLK pin
//#define ADS_CLK_PORT	5	// ADS CLK port

#define ADS_PWDN_PORT   5   // ADS Power Down port
#define ADS_PWDN_PIN	   12   // ADS Power Down pin

#define ADS_DRDY_PORT	5	// ADS Data Ready port
#define ADS_DRDY_PIN	   14	// ADS Data Ready pin

#define ADS_CS_PORT  	0   // Master ADS Chip Select port
#define ADS_CS_PIN		15  // Master ADS Chip Select pin

#define BOARD_ADS	      1   // ADS Chip Select


// ADS131E08 Definicion de comandos SPI, Asignacion de bytes
#define _WAKEUP      ((uint8_t) 0x02)   // Wake-up from standby mode
#define _STANDBY     ((uint8_t) 0x04)   // Enter standby mode
#define _RESET       ((uint8_t) 0x06)   // Reset the device
#define _START       ((uint8_t) 0x08)   // Start or restart (synchronize) conversions
#define _STOP        ((uint8_t) 0x0A)   // Stop conversions
#define _OFFSETCAL   ((uint8_t) 0x1A)   // Channel offset calibration
#define _RDATAC      ((uint8_t) 0x10)   // Enable Read Data Continuous Mode (default mode at power-up)
#define _SDATAC      ((uint8_t) 0x11)   // Stop Read Data Continuous Mode
#define _RDATA       ((uint8_t) 0x12)   // Read data by command
#define _RREG        ((uint8_t) 0x20)   // Read n nnnn registers starting at address r rrrr
#define _WREG        ((uint8_t) 0x40)   // Write n nnnn registers starting at address r rrrr


// ADS131E08 Mapa de registros
#define _NUM_REGISTERS		((uint8_t) 21)

/* Register 0x00 (ID) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |             REV_ID[2:0]           |      1    |      0    |     0     |      NU_CH[1:0]       |
 	 * -------------------------------------------------------------------------------------------------
*/

/* ID register address */
#define _ID_ADDRESS				((uint8_t) 0x00)

/* ID register field masks */
#define _ID_REV_ID_MASK			((uint8_t) 0xE0)

/* NU_CH field values */
#define _ID_REV_ID_ADS131E0X	((uint8_t) 0xD0)

/* ID register field masks */
#define _ID_NU_CH_MASK			((uint8_t) 0x03)

/* NU_CH field values */
#define _ID_NU_CH_4				((uint8_t) 0x00)
#define _ID_NU_CH_6				((uint8_t) 0x01)
#define _ID_NU_CH_8				((uint8_t) 0x02)

/* Register 0x01 (CONFIG1) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |     1     |  DAISY_IN |   CLK_EN  |      1    |      0    |               DR[2:0]             |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CONFIG1 register address */
#define _CONFIG1_ADDRESS		((uint8_t) 0x01)

/* CONFIG1 default (reset) value */
#define _CONFIG1_DEFAULT		((uint8_t) 0x91)

/* CONFIG1 register field masks */
#define _CONFIG1_DAISY_IN_MASK	((uint8_t) 0x40)
#define _CONFIG1_CLK_EN_MASK	((uint8_t) 0x20)
#define _CONFIG1_DR_MASK		((uint8_t) 0x07)

/* DR field values */
#define _DR_64KSPS   			((uint8_t) 0x00)	// 64 kSPS
#define _DR_32KSPS   			((uint8_t) 0x01)    // 32 kSPS Default Value
#define _DR_16KSPS   			((uint8_t) 0x02)	// 16 kSPS
#define _DR_8KSPS   			((uint8_t) 0x03)    // 8 kSPS
#define _DR_4KSPS   			((uint8_t) 0x04)    // 4 kSPS
#define _DR_2KSPS   			((uint8_t) 0x05)	// 2 kSPS
#define _DR_1KSPS   			((uint8_t) 0x06)    // 1 kSPS
#define _DR_NOT_USE   			((uint8_t) 0x07)    // Do not use

/* Register 0x02 (CONFIG2) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |     1     |     1     |     1     |  INT_TEST |     0     |  TEST_AMP |     TEST_FREQ[1:0]    |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CONFIG2 register address */
#define _CONFIG2_ADDRESS			((uint8_t) 0x02)

/* CONFIG2 default (reset) value */
#define _CONFIG2_DEFAULT			((uint8_t) 0xE0)

/* CONFIG2 register field masks */
#define _CONFIG2_INT_TEST_MASK		((uint8_t) 0x10)
#define _CONFIG2_TEST_AMP_MASK		((uint8_t) 0x04)
#define _CONFIG2_TEST_FREQ_MASK		((uint8_t) 0x03)

/* INT_TEST field values */
#define _CONFIG2_INT_TEST_ENABLE    ((uint8_t) 0x10)    // Test Signals are generated internally
#define _CONFIG2_INT_TEST_DISABLE   ((uint8_t) 0x00)    // Test Signals are driven externally


/* TEST_AMP field values */
#define _CONFIG2_TEST_AMP_1X        ((uint8_t) 0x00)
#define _CONFIG2_TEST_AMP_2X        ((uint8_t) 0x01)

/* TEST_FREQ field values */
#define _CONFIG2_TEST_FREQ_21       ((uint8_t) 0x00)    // Pulsed at fclk / 2^21
#define _CONFIG2_TEST_FREQ_20       ((uint8_t) 0x01)    // Pulsed at fclk / 2^20
#define _CONFIG2_TEST_FREQ_NOT_USE  ((uint8_t) 0x02)	// Not used
#define _CONFIG2_TEST_FREQ_AT_DC    ((uint8_t) 0x03)	// At dc

/* Used for no change freq or amp */
#define _CONFIG2_TEST_NOCHANGE      ((uint8_t) 0xFF)

/* Register 0x03 (CONFIG3) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * | PDB_REFBUF|     1     |  VREF_4V  |     0     | OPAMP_REF | PDB_OPAMP |     0     |     0     |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CONFIG3 register address */
#define _CONFIG3_ADDRESS			((uint8_t) 0x03)

/* CONFIG3 default (reset) value */
#define _CONFIG3_DEFAULT			((uint8_t) 0x40)

/* CONFIG3 register field masks */
#define _CONFIG3_PDB_REFBUF_MASK	(uint8_t) 0x80)
#define _CONFIG3_VREF_4V_MASK		((uint8_t) 0x20)
#define _CONFIG3_OPAMP_REF_MASK		((uint8_t) 0x08)
#define _CONFIG3_PDB_OPAMP_MASK		((uint8_t) 0x04)


/* Register 0x04 (FAULT) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |            COMP_TH[2:0]           |     0     |     0     |     0     |     0     |     0     |
 	 * -------------------------------------------------------------------------------------------------
*/

/* FAULT register address */
#define _FAULT_ADDRESS				((uint8_t) 0x04)

/* FAULT default (reset) value */
#define _FAULT_DEFAULT				((uint8_t) 0x00)

/* FAULT register field masks */
#define _FAULT_MASK					((uint8_t) 0xE0)

/* COMP_TH field values */
#define _FAULT_COMP_TH_HS_95P       ((uint8_t) 0x00)    // HS 95P: High side 95%
#define _FAULT_COMP_TH_HS_92_5P     ((uint8_t) 0x01)	// HS 92.5P: High side 92.5%
#define _FAULT_COMP_TH_HS_90P       ((uint8_t) 0x02)	// HS 90P: High side 90%
#define _FAULT_COMP_TH_HS_87_5P     ((uint8_t) 0x03)	// HS 87.5P: High side 87.5%
#define _FAULT_COMP_TH_HS_85P       ((uint8_t) 0x04)	// HS 85P: High side 85%
#define _FAULT_COMP_TH_HS_80P       ((uint8_t) 0x05)	// HS 80P: High side 80%
#define _FAULT_COMP_TH_HS_75P       ((uint8_t) 0x06)	// HS 75P: High side 75%
#define _FAULT_COMP_TH_HS_70P       ((uint8_t) 0x07)	// HS 70P: High side 70%

/* Register 0x05 (CH1SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CH1SET register address */
#define _CH1SET_ADDRESS						((uint8_t) 0x05)

/* CH1SET default (reset) value */
#define _CH1SET_DEFAULT						((uint8_t) 0x10)

/* CH1SET register field masks */
#define _CH1SET_PD_MASK						((uint8_t) 0x80)
#define _CH1SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH1SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH1SET_PGA_GAIN_NOTUSE				((uint8_t) 0x00)	// Do not  use
#define _CH1SET_PGA_GAIN_1          		((uint8_t) 0x10)
#define _CH1SET_PGA_GAIN_2          		((uint8_t) 0x20)
#define _CH1SET_PGA_GAIN_4          		((uint8_t) 0x40)
#define _CH1SET_PGA_GAIN_8          		((uint8_t) 0x50)
#define _CH1SET_PGA_GAIN_12         		((uint8_t) 0x60)

/* MUX field values */
#define _CH1SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH1SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH1SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH1SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH1SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal

/* Register 0x06 (CH2SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CH2SET register address */
#define _CH2SET_ADDRESS						((uint8_t) 0x06)

/* CH2SET default (reset) value */
#define _CH2SET_DEFAULT						((uint8_t) 0x10)

/* CH2SET register field masks */
#define _CH2SET_PD_MASK						((uint8_t) 0x80)
#define _CH2SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH2SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH2SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH2SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH2SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH2SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH2SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH2SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH2SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH2SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH2SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH2SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH2SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal

/* Register 0x07 (CH3SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CH3SET register address */
#define _CH3SET_ADDRESS						((uint8_t) 0x07)

/* CH3SET default (reset) value */
#define _CH3SET_DEFAULT						((uint8_t) 0x10)

/* CH3SET register field masks */
#define _CH3SET_PD_MASK						((uint8_t) 0x80)
#define _CH3SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH3SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH3SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH3SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH3SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH3SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH3SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH3SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH3SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH3SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH3SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH3SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH3SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal


/* Register 0x08 (CH4SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CH4SET register address */
#define _CH4SET_ADDRESS						((uint8_t) 0x08)

/* CH4SET default (reset) value */
#define _CH4SET_DEFAULT						((uint8_t) 0x10)

/* CH4SET register field masks */
#define _CH4SET_PD_MASK						((uint8_t) 0x80)
#define _CH4SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH4SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH4SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH4SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH4SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH4SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH4SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH4SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH4SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH4SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH4SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH4SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH4SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal


/* Register 0x09 (CH5SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CH5SET register address */

#define _CH5SET_ADDRESS						((uint8_t) 0x09)

/* CH5SET default (reset) value */
#define _CH5SET_DEFAULT						((uint8_t) 0x10)

/* CH5SET register field masks */
#define _CH5SET_PD_MASK						((uint8_t) 0x80)
#define _CH5SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH5SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH5SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH5SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH5SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH5SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH5SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH5SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH5SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH5SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH5SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH5SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH5SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal

/* Register 0x0A (CH6SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
 	 * -------------------------------------------------------------------------------------------------
*/
/* CH6SET register address */
#define _CH6SET_ADDRESS						((uint8_t) 0x0A)

/* CH6SET default (reset) value */
#define _CH6SET_DEFAULT						((uint8_t) 0x10)

/* CH6SET register field masks */
#define _CH6SET_PD_MASK						((uint8_t) 0x80)
#define _CH6SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH6SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH6SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH6SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH6SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH6SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH6SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH6SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH6SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH6SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH6SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH6SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH6SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal

/* Register 0x0B (CH7SET) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
	 * -------------------------------------------------------------------------------------------------
*/
/* CH7SET register address */
#define _CH7SET_ADDRESS						((uint8_t) 0x0B)

/* CH7SET default (reset) value */
#define _CH7SET_DEFAULT						((uint8_t) 0x10)

/* CH7SET register field masks */
#define _CH7SET_PD_MASK						((uint8_t) 0x80)
#define _CH7SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH7SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH7SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH7SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH7SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH7SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH7SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH7SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH7SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH7SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH7SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH7SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH7SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal

/* Register 0x0C (CH8SET) definition
 	 * -------------------------------------------------------------------------------------------------
	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * |    PD    |             GAIN[2:0]             |     0     |              MUX[2:0]            |
	 * -------------------------------------------------------------------------------------------------
*/
/* CH8SET register address */
#define _CH8SET_ADDRESS						((uint8_t) 0x0C)

/* CH8SET default (reset) value */
#define _CH8SET_DEFAULT						((uint8_t) 0x10)

/* CH8SET register field masks */
#define _CH8SET_PD_MASK						((uint8_t) 0x80)
#define _CH8SET_GAIN_MASK					((uint8_t) 0x70)
#define _CH8SET_MUX_MASK					((uint8_t) 0x07)

/* PGA Gain field values */
#define _CH8SET_PGA_GAIN_NOTUSE             ((uint8_t) 0x00)	// Do not  use
#define _CH8SET_PGA_GAIN_1                  ((uint8_t) 0x10)
#define _CH8SET_PGA_GAIN_2                  ((uint8_t) 0x20)
#define _CH8SET_PGA_GAIN_4                  ((uint8_t) 0x40)
#define _CH8SET_PGA_GAIN_8                  ((uint8_t) 0x50)
#define _CH8SET_PGA_GAIN_12                 ((uint8_t) 0x60)

/* MUX field values */
#define _CH8SET_MUX_NORMAL_INPUT    		((uint8_t) 0x00)	// Normal input
#define _CH8SET_MUX_INPUT_SHORT_TO_MID		((uint8_t) 0x01) 	// Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CH8SET_MUX_MVDD_FOR_SUPPLY         ((uint8_t) 0x03)	// MVDD for supply measurement
#define _CH8SET_MUX_TEMP_SENSOR             ((uint8_t) 0x04)	// Temperature sensor
#define _CH8SET_MUX_TEST_SIGNAL             ((uint8_t) 0x05)	// Test Signal

/* Register 0x0D (RESERVED0) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |     0     |     0     |     0     |     0     |     0     |     0     |     0     |     0     |
 	 * -------------------------------------------------------------------------------------------------
*/

/* Register 0x0E (RESERVED1) definition
 	 * -------------------------------------------------------------------------------------------------
	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * |     0     |     0     |     0     |     0     |     0     |     0     |     0     |     0     |
	 * -------------------------------------------------------------------------------------------------
*/

/* Register 0x0F (RESERVED2) definition
	 * -------------------------------------------------------------------------------------------------
	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * |     0     |     0     |     0     |     0     |     0     |     0     |     0     |     0     |
	 * -------------------------------------------------------------------------------------------------
*/

/* Register 0x10 (RESERVED3) definition
	 * -------------------------------------------------------------------------------------------------
	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * |     0     |     0     |     0     |     0     |     0     |     0     |     0     |     0     |
	 * -------------------------------------------------------------------------------------------------
*/

/* Register 0x11 (RESERVED4) definition
	 * -------------------------------------------------------------------------------------------------
	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * |     0     |     0     |     0     |     0     |     0     |     0     |     0     |     0     |
	 * -------------------------------------------------------------------------------------------------
*/

/* Register 0x12 (FAULT_STATP) definition
	 * -------------------------------------------------------------------------------------------------
	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
	 * -------------------------------------------------------------------------------------------------
	 * | IN8P_FAULT| IN7P_FAULT| IN6P_FAULT| IN5P_FAULT| IN4P_FAULT| IN3P_FAULT| IN2P_FAULT| IN1P_FAULT|
	 * -------------------------------------------------------------------------------------------------
*/
/* FAULT_STATP register address */
#define _FAULT_STATP_ADDRESS				((uint8_t) 0x12)

/* FAULT_STATP default (reset) value */
#define _FAULT_STATP_DEFAULT				((uint8_t) 0x00)

/* FAULT_STATP register field masks */
#define _FAULT_STATP_IN8P_FAULT_MASK		((uint8_t) 0x80)
#define _FAULT_STATP_IN7P_FAULT_MASK		((uint8_t) 0x40)
#define _FAULT_STATP_IN6P_FAULT_MASK		((uint8_t) 0x20)
#define _FAULT_STATP_IN5P_FAULT_MASK		((uint8_t) 0x10)
#define _FAULT_STATP_IN4P_FAULT_MASK		((uint8_t) 0x08)
#define _FAULT_STATP_IN3P_FAULT_MASK		((uint8_t) 0x04)
#define _FAULT_STATP_IN2P_FAULT_MASK		((uint8_t) 0x02)
#define _FAULT_STATP_IN1P_FAULT_MASK		((uint8_t) 0x01)

/* Register 0x13 (FAULT_STATN) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * | IN8_NFAULT| IN7N_FAULT| IN6N_FAULT| IN5N_FAULT| IN4N_FAULT| IN3N_FAULT| IN2N_FAULT| IN1N_FAULT|
 	 * -------------------------------------------------------------------------------------------------
*/
/* FAULT_STATN register address */
#define _FAULT_STATN_ADDRESS				((uint8_t) 0x13)

/* FAULT_STATN default (reset) value */
#define _FAULT_STATN_DEFAULT				((uint8_t) 0x00)

/* FAULT_STATN register field masks */
#define _FAULT_STATN_IN8N_FAULT_MASK		((uint8_t) 0x80)
#define _FAULT_STATN_IN7N_FAULT_MASK		((uint8_t) 0x40)
#define _FAULT_STATN_IN6N_FAULT_MASK		((uint8_t) 0x20)
#define _FAULT_STATN_IN5N_FAULT_MASK		((uint8_t) 0x10)
#define _FAULT_STATN_IN4N_FAULT_MASK		((uint8_t) 0x08)
#define _FAULT_STATN_IN3N_FAULT_MASK		((uint8_t) 0x04)
#define _FAULT_STATN_IN2N_FAULT_MASK		((uint8_t) 0x02)
#define _FAULT_STATN_IN1N_FAULT_MASK		((uint8_t) 0x01)

/* Register 0x14 (GPIO) definition
 	 * -------------------------------------------------------------------------------------------------
 	 * |   Bit 7   |   Bit 6   |   Bit 5   |   Bit 4   |   Bit 3   |   Bit 2   |   Bit 1   |   Bit 0   |
 	 * -------------------------------------------------------------------------------------------------
 	 * |                   GPIOD[7:4]                  |                   GPIOC[4:1]                  |
 	 * -------------------------------------------------------------------------------------------------
*/
/* GPIO register address */
#define _GPIO_ADDRESS						((uint8_t) 0x14)

/* GPIO default (reset) value */
#define _GPIO_DEFAULT						((uint8_t) 0x0F)

/* GPIO register field masks */
#define _GPIO_GPIOD_MASK					((uint8_t) 0xF0)
#define _GPIO_GPIOC_MASK					((uint8_t) 0x0F)


// Configuraciones de cada canal
#define POWER_DOWN_		(0)
#define GAIN_SET        (1)
#define INPUT_TYPE_SET  (2)
#define YES      	    (0x01)
#define NO      	    (0x00)

/* CHxSET default (reset) value */
#define _CHSET_DEFAULT						((uint8_t) 0x10)

/* CHxSET register field masks */
#define _CHSET_PD_MASK						((uint8_t) 0x80)
#define _CHSET_GAIN_MASK					((uint8_t) 0x70)
#define _CHSET_MUX_MASK						((uint8_t) 0x07)

/* PGA Gain field values */
#define _CHSET_PGA_GAIN_NOTUSE              ((uint8_t) 0x00)
#define _CHSET_PGA_GAIN_1                   ((uint8_t) 0x10)
#define _CHSET_PGA_GAIN_2                   ((uint8_t) 0x20)
#define _CHSET_PGA_GAIN_4                   ((uint8_t) 0x40)
#define _CHSET_PGA_GAIN_8                   ((uint8_t) 0x50)
#define _CHSET_PGA_GAIN_12                  ((uint8_t) 0x60)

/* MUX field values */
#define _CHSET_MUX_NORMAL_INPUT             ((uint8_t) 0x00)
#define _CHSET_MUX_INPUT_SHORT_TO_MID       ((uint8_t) 0x01) // Input shorted to (AVDD + AVSS) / 2 (for offset or noisemeasurements)
#define _CHSET_MUX_MVDD_FOR_SUPPLY          ((uint8_t) 0x03)
#define _CHSET_MUX_TEMP_SENSOR              ((uint8_t) 0x04)
#define _CHSET_MUX_TEST_SIGNAL              ((uint8_t) 0x05)


/**
 	 * @brief Indica si es el primer paquete de datos
*/
extern bool firstDataPacket;

/**
 	 * @brief Numero de canales
*/
extern uint8_t numChannels;

/**
 	 * @brief Contador de muestras
*/
extern uint8_t sampleCounter;

/**
 	 * @brief Contador de muestras
*/
extern uint8_t sampleCnt;

/**
 	 * @brief Arreglo utilizado al leer los datos de los registros
*/
extern uint8_t regData[24];

/**
 * @brief Variable utilizada para mantener el registro de estado
 */
uint32_t boardStat;

/**
 	 * @brief Arreglo utilizado al leer los datos de los registros
*/
extern uint32_t channelData[8];

/**
 	 * @brief Configuración inicial de los pines con los que cuenta el ADS en bajo
*/
void ADS131E08_signalDown();

/**
 	 * @brief Configuracion de los pines con los que cuenta el ADS
*/
void ADS131E08_initialize();

/**
 	 * @brief Iniciar la adquisicion continua de datos
*/
void ADS131E08_startADS();

/**
 	 * @brief Detener la adquisicion continua de datos
*/
void ADS131E08_stopADS();

/**
 	 * @brief SPI chip select metodo
*/
void ADS131E08_csLow();

/**
 	 * @brief SPI chip de-select
*/
void ADS131E08_csHigh();

/**
 	 * @brief Transferencia a traves de SPI
 	 * @param _data Byte a transferir
 	 * @return Byte recibido a traves de la transferencia por SPI
*/
uint8_t ADS131E08_transfer(uint8_t _data);

/**
 	 * @brief Enviar un comando SPI predeterminado del ADS
 	 * @param command Comando a enviar
*/
void ADS131E08_sendCommand(uint8_t command);

/**
 	 * @brief Lee un registro del ADS
 	 * @param _address Direccion del registro a leer
 	 * @return Valor del registro requerido
*/
uint8_t ADS131E08_RREG(uint8_t _address);

/**
 	 * @brief Escribe un registro del ADS
 	 * @param _address Direccion del registro a escribir
 	 * @param _value Byte a escribir en el registro
*/
void ADS131E08_WREG(uint8_t _address, uint8_t _value);

/**
 	 * @brief Consulta para ver si hay datos disponibles del ADS131E08
 	 * @return TRUE si hay datos disponibles, FALSE en caso contrario
*/
bool ADS131E08_isDataAvailable();

/**
 	 * @brief Retorna el ID del dispositivo
 	 * @return ID del dispositivo
*/
uint8_t ADS131E08_getDeviceID();

void ADS131E08_getChannelData(uint8_t *sampleCnt, uint32_t *data);

#endif /* ADS131E08_H_ */
