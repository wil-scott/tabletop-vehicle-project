/*
 *	HC-SR04 Ultrasonic Distance Sensor Driver
 *
 *  Author: Wil Scott
 *	Created: Oct 2023
*/

#include "../inc/HCSR04.h"

// Create global var to track PortDPin3 State
// if prev state low (now high), set and start timer
// if prev state high (now low), set and end timer
volatile int echo_pin_state = 0;
volatile int timeout = 0;
volatile int flag = 0;
volatile uint16_t end_time;

const uint16_t timer1_start_val = 0;
const uint16_t timer1_compare_match = 9501;
const int speed_of_sound = 343;

/*
 * Configure ATMEGA328p pins for r/w, interrupts
 */

void pin_config()
{
	//turn on HC-SR04 pins
	DDRD |= (1<<PIND2); //output for trigger
	DDRD &= ~(1<<PIND3); //input for echo
	
	//enable PCIE2 Bit2=1 for Port D
	PCICR |= 0x4 ; //0b00000100 or PCIE2
	//ENABLE PCINT19 (PortD Pin 3)
	PCMSK2 |= 0x8; //0b00001000 or PCINT19
		
}

void timer_config()
{
	//16MHz clock by default
	//1 clock tick = 62.5ns
	//prescale 16MHz by 64 to 250Khz gives us 4us per tick
	//38000/4 = 9500
	
	//16000000 / (64 x 9500 + 1) = 38ms
	
	//init Timer1
	TCCR1A = 0;
	TCCR1B = 0;
	
	//preload timer with comp match value
	//TCNT1 = 0;
	
	//set prescaler to 64
	TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << CS10);

}

/*
 * Sets the trigger pin low (clears it) for 2us, then
 * high for the 10us required to trigger the sensor's ping
 */
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
	pin_config();
	timer_config();
	sei();
	echo_pin_state = 0;
	timeout = 0;
	flag = 0;
	trigger();

	while(!flag) {}

	if(timeout) {
		return -1;
	}
	//convert counter val from ticks to us
	int microseconds = end_time * 4;
	int distance_mm = (microseconds/2) * speed_of_sound / 1000;
	cli();
	
	return microseconds;
	
	
}

ISR(PCINT2_vect)
{
	//DDRB |= (1 << DDB1);
   // PORTB |= (1 << PINB1);
	//ISR for Port D
	//if pin was low before state change
	if (echo_pin_state == 0) {

		//set pin to current state (high)
		echo_pin_state = 1;
		//RESET timer
		TCNT1 = timer1_start_val;
		OCR1A = timer1_compare_match;
		//Enable timer interrupt for compare mode
		TIMSK1 |= (1 << OCIE1A);
	} else { //if pin is high before state change
		end_time = TCNT1;
		flag = 1;
	}
	//PCIFR should be auto reset when ISR triggered
}

ISR(TIMER1_COMPA_vect)
{
	//ISR for Compare Match of Timer1
	timeout = 1;
}



