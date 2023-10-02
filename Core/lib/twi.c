/*
* I2C/TWI driver for the Atmega328p using interrupts
*
* Author: Wilson Scott
* Date: Sept 2023
*/

//Includes
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Bus States
//enum {}

// Mstatus
//enum {}

// mctrlb
//enum {}

void test(void)
{
	DDRB = DDRB | (1 << DDB5);
	while(1)
	{
		PORTB = PORTB | (1<<PORTB5);
		_delay_ms(1000);
		PORTB = PORTB & ~(1<<PORTB5);
		_delay_ms(1000);
	}
}
