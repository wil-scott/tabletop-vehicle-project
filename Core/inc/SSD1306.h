/*
 *	SSD1306 OLED I2C Driver
 *
 *  Author: Wil Scott
 *	Created: August 2023
*/

#ifndef __SSD1306_I2C_DRIVER_H__
#define __SSD1306_I2C_DRIVER_H__

/* include HAL for ATMEGA328p */
#include <avr/io.h>
#include "twi.h"
#include "font6x8.h"
#include <util/delay.h>
 
/*
 * DEFINES
 */
#define SSD1306_I2C_ADDR	0x78 /*Default addr is 0x3C, << 1 is 0x78 */
 
#define HEIGHT 		32
#define WIDTH 		128
#define MIN_PAGE 	0
#define MAX_PAGE 	3

 
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
 * Fundamental Commands
 */

#define SSD_SET_CONTRAST			0x80 //0x7F
#define SSD_DISPLAY_RAM				0xA4
#define SSD_DISPLAY_NO_RAM			0xA5
#define SSD_DISPLAY_NORMAL			0xA6
#define SSD_DISPLAY_INVERSE			0xA7
#define SSD_DISPLAY_OFF				0xAE
#define SSD_DISPLAY_ON				0xAF

/*
 * Scrolling Commands
 */
#define SSD_DEACT_SCROLL	0x2E

/*
 * Addressing Commands
 */
#define SSD_SET_ADDR_MODE	0x20 // follow w/ 0x02 for page mode
#define SSD_HORIZ_MODE		0x00

#define SSD_PAGE_MODE		0x02
#define SSD_SET_PAGE_START	0xB0 // AND addr(0, 1, 2, 3) - (Page Mode)

#define SSD_COL_ADDR		0x21 //follow with col start/end addr (0-127d)
#define SSD_PAGE_ADDR		0x22 //follow with page start/end addr (0-3d)




/*
 * Hardware Commands
 */
#define SDD_DISPLAY_START_LINE	0x40
#define SSD_SET_SEGMENT_REMAP	0xA0 // A0 is reset, A1 = col 127 is col0
#define SSD_SET_MUX_RATIO 		0xA8 // followed by 0x1F (rows - 1 = 31)
#define SSD_COM_SCAN_DIR		0xC0 // C0 is normal, C8 remapped
#define SSD_SET_DISPLAY_OFFSET 	0xD3 // followed by 0x00 for no offset
#define SSD_SET_COM_PINS		0xDA // followed by 0x02 for 128x32 oled

/*
 * Timing/Driving Commands
 */
#define SSD_SET_DISPLAY_CLK		0xD5 //followed by 0x80 for reset
#define SSD_SET_PRECHRG			0xD9 //followed by 0x22 for reset 
#define SSD_SET_VCOM			0xDB //followed by 0x20 for reset

/*
 * Charge Pump Commands
 */
#define SSD_CHARGE_PUMP			0x8D //followed by 0x14 to enable

/*
 * INITIALISATION
 */
void SSD1306_init( uint8_t address );
void SSD1306_clear_display();

/*
 * MAIN FUNCTIONALITY
 */
void display_string(char* string, int str_len, uint8_t page, uint8_t col );
void SSD1306_scroll_off();
//void set_cursor(uint8_t col_min, uint8_t col_max, uint8_t page_min, uint8_t page_max);

/*
 * LOW-LEVEL FUNCTIONS
 */
void SSD1306_WriteCommand( uint8_t byte );
void SSD1306_WriteData( uint8_t byte );


#endif
