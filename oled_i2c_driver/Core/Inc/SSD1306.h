/*
 *	SSD1306 OLED I2C Driver
 *
 *  Author: Wil Scott
 *	Created: August 2023
*/

#ifndef __SSD1306_I2C_DRIVER_H__
#define __SSD1306_I2C_DRIVER_H__

/* include HAL for ATMEGA4809 */
#include <avr/io.h>
#include <twi.h>
 
/*
 * DEFINES
 */
#define SSD1306_I2C_ADDR			0x78 /*Default addr is 0x3C, << 1 is 0x78 */
 
#define HEIGHT 32
#define WIDTH 128

 
/* define control bytes */
/* Control byte: C D/C 0 0 0 0 0 0
 * C = 0, then the following transmission is data bytes only
 * C/D = 0, then following data byte is command
 * C/D = 1, then following data byte is data to be stored in GDDRAM
 */
#define CMD_STREAM			0x00
#define DATA_STREAM			0x40
#define SINGLE_CMD_BYTE		0x80
#define SINGLE_DATA_BYTE	0xC0

/*
 * Define Command Bytes
 */

#define SSD1306_CONTRAST_ID			0x7F
#define SSD1306_NORMAL_DISPLAY_ID	0xA6
#define SSD1306_DISPLAY_STATUS_UD	0xAE

	const uint8_t config_buff[19] = { 0x00, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC0, 0xDA, 0x02, 0x81, 0x7F, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF };



/*
 * OLED STRUCT
 */
typedef struct {
	/*may require an address struct of some kind to hold the i2c addr/object*/
	/*hold displayed data on top, bottom row - cap to 10 chars for now*/
	int cursor_location = 0;
	char top_row[11] = "";
	char bottom_row[11] = "";
} OLED;
 
/*
 * INITIALISATION
 */
uint8_t SSD1306_Init( OLED *dev );

/*
 * LOW-LEVEL FUNCTIONS
 */
uint8_t SSD1306_ReadRegister( OLED *dev, uint8_t reg, uint8_t *data );
uint8_t SSD1306_ReadRegister( OLED *dev, uint8_t reg, uint8_t *data, uint8_t length );

uint8_t SSD1306_WriteRegister( OLED *dev, uint8_t reg, uint8_t *data );

#endif

