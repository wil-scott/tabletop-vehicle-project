/*
 * @file	: main.c
 * @brief	: Runs main program
 *************************************************
 * @note	: This is an attempt to write an i2c driver for the
 *			  SDD1306 (specifically, the .91 inch 128*32 OLED version)
 *
 *
 */
/* Includes */

#include <util/delay.h>
#include <stdio.h>
/* Private includes */
#include "../Inc/SSD1306.h"

int main(void)
{
	

/*	*/
/*	const uint8_t config_buff[19] = { 0x00, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC0, 0xDA, 0x02, 0x81, 0x7F, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF };*/

/*	uint8_t ret_val = i2c_write(config_buff, 19);*/
/*	*/
/*	uint8_t pg_buf[128];*/
/*	memset(pg_buf, 0xFF, sizeof(pg_buf));*/
/*	uint8_t cmd_1[] = {0x22, };*/
/*	uint8_t ret_val = i2c_write(config_buff, 19);*/
	//reset_display();
	SSD1306_init(0x78);
	//SSD1306_scroll_off();
	//SSD1306_config_addressing();
	SSD1306_clear_display();
	//_delay_ms(100);
	char test[] = "ABCDE";
/*	display_string(test, 5, 0x00);*/
/*	display_string(test, 5, 0x01);*/
/*	display_string(test, 5, 0x02);*/
	display_string(test, 5, 0x03);
				
	
}
