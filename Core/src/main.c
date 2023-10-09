#include "../lib/twi.h"
#include "../inc/SSD1306.h"

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

	while(1){}
	return 0;
}
