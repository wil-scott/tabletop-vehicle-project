#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// set Port to write
	PORTE.DIR |= PIN2_bm;
	
	while(1)
	{
		PORTE.OUT |= PIN2_bm;
		_delay_ms(500);
		PORTE.OUT &= ~PIN2_bm;
		_delay_ms(500);
	}
	
	return 0;
}
	
