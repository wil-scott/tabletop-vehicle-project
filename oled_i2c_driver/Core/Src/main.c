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
#include "twi.h"
#include <util/delay.h>

/* Private includes */
//#include "SD1306.h"

int main(void)
{
	
	_delay_ms(20); // delay to allow I2C device to turn on

	i2c_init(0x78);
	
	const uint8_t config_buff[19] = { 0x00, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC0, 0xDA, 0x02, 0x81, 0x7F, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF };

	uint8_t ret_val = i2c_write(config_buff, 19);
	
}
