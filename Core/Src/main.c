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
#include "../Inc/SSD1306.h"

int main(void)
{
	//enable TWI pins for read/write -> relocate to separate config file in future
	PORTA.DIR |= PIN2_bm;
	PORTA.DIR |= PIN3_bm;
	
	SSD1306_init(0x78); // 
	_delay_ms(20);
	SSD1306_clear_display();
	char row1[] = "STATUS: FUNCTIONAL";
	char row2[] = "DISTANCE: NULL";

	display_string(row1, 18, 0x00, 0x00);
	display_string(row2, 14, 0x01, 0x80);
			
	
}
