#include "../lib/twi.h"
#include "../inc/SSD1306.h"
#include "../inc/HCSR04.h"
#include <stdio.h>

int main()
{
	//turn on TWI pins
	DDRC |= (1<<PINC4);
	DDRC |= (1<<PINC5);
	
	
	SSD1306_init( SSD1306_I2C_ADDR );
	SSD1306_clear_display();
	char row1[] = "STATUS: FUNCTIONAL";
	char row2[] = "DISTANCE: NULL";

	display_string(row1, 18, 0x00, 0x00);
	display_string(row2, 14, 0x01, 0x80);
	
	_delay_ms(1000);
	SSD1306_clear_display();
	
	int distance = measure();
	
	char row3[20];
	sprintf(row2, "DISTANCE: %d mm", distance);
	display_string(row1, 18, 0x00, 0x00);
	display_string(row3, 20, 0x01, 0x80);

	while(1){}

}
