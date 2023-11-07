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
	

	display_string(row1, 18, 0x00, 0x00);


	while(1){
		int distance = measure();
		if (distance == -1) {
			char timeout[] = "DISTANCE: TIMEOUT";
			display_string(timeout, 17, 0x01, 0x80);
		
		} else {
			char row3[20];
			sprintf(row3, "DISTANCE: %d cm", distance);
			display_string(row3, 18, 0x01, 0x80);
		}
	}

}
