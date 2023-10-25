/*
 *	HC-SR04 Ultrasonic Distance Sensor Driver
 *
 *  Author: Wil Scott
 *	Created: Oct 2023
*/

#include "../inc/HCSR04.h"

#define TIMER1_START_VAL	0
#define TRIGGER_PIN			2
#define ECHO_PIN			3

volatile uint16_t timer1_compare_match = 9501;
volatile uint16_t end_time;
volatile uint8_t flag = 0;
volatile uint8_t timeout = 0;
volatile uint8_t pin_state = 0;

void init_pins()
{
	//turn on HC-SR04 pins
	DDRD |= (1<<PIND2); //output for trigger
	DDRB &= ~(1<<PINB0); //input for echo	
}

void init_timer1()
{
	//init Timer1
	TCCR1A = 0;
	TCCR1B = 0;
	
	TCNT1 = 0;
	TCCR1B = (1 << ICES1); //capture rising edge
	TCCR1B |= 0x3; //set prescaler to 64
	TIMSK1 = (1 << ICIE1) | (1 << OCIE1A); // enable inp capt and comp int
}

void trigger()
{
	PORTD &= ~(1 << PIND2);
	_delay_us(2);
	PORTD |= (1 << PIND2);
	_delay_us(10);
	PORTD &= ~(1 << PIND2);	
}

int measure()
{
	// clear interrupts
	cli();
	init_pins();
	init_timer1();
	sei();
	trigger();
	
	while(!flag) {}
	
	return end_time;
}

ISR(TIMER1_CAPT_vect)
{
	if (pin_state == 0) {
		pin_state = 1;
		TCNT1 = TIMER1_START_VAL; // set timer to 0
		OCR1A = timer1_compare_match;	// set compare val
		TCCR1B &= ~(1 << ICES1); // set interrupt to falling edge
		
	} else {
		end_time = ICR1;
		flag = 1;
	}

}

ISR(TIMER1_COMPA_vect)
{
	//ISR for Compare Match of Timer1
	timeout = 1;
}
