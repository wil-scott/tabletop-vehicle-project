/*
 *	DC Motor Driver
 *
 *  Author: Wil Scott
 *  Created: Jan 2024
*/

#include "../inc/dcm-driver.h"

/* create wheel structs */
struct wheel leftWheel = { &PORTD, &DDRD, &PORTB, &DDRB, &PORTB, &DDRB };
struct wheel rightWheel = { &PORTD, &DDRD, &PORTB, &DDRB, &PORTB, &DDRB };

double dutyCycle = 100.0;
// motors don't have enough juice if we start with a dutyCycle that's too low.
// Solution: pulse high to start for ~400 cycles, then switch to desired dutyCycle via ISR 
double startingDutyCycle = 100.0;
double desiredDutyCycle = 95.0;
int counter = 0;

/*
 * Set up pins for each wheel struct
 * Left wheel: 5 (PD5), 10 (PB2), 11 (PB3)
 * Right Wheel: 6 (PD6), 12 (PB4), 13 (PB5)
 * May require changing if pin configs moved to general/comprehensive config file.
*/
void wheel_config() {
	/* setup Left Wheel - reset pin to low and direction to out*/
	*leftWheel.speedPortReg &= ~(1 << PIND5);
	*rightWheel.speedPortReg &= ~(1 << PIND6);

	*leftWheel.dir1PortReg &= ~(1 << PINB2);
	*rightWheel.dir1PortReg &= ~(1 << PINB4);

	*leftWheel.dir2PortReg &= ~(1 << PINB3);
	*rightWheel.dir2PortReg &= ~(1 << PINB5);

	*leftWheel.speedDirectionReg |= (1 << PIND5);	
	*rightWheel.speedDirectionReg |= (1 << PIND6);
	
	*leftWheel.dir1DirectionReg |= (1 << PINB2);
	*rightWheel.dir1DirectionReg |= (1 << PINB4);

	*leftWheel.dir2DirectionReg |= (1 << PINB3);
	*rightWheel.dir2DirectionReg |= (1 << PINB5);

	/* setup 8-bit timer for d5, d6 pwm 
	 * sets OC0B (left motor speed pin) and OC0A (right motor speed pin) registers to fast PWM
	 * sets Waveform Generation to Fast PWM
	 */
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	/* time/counter interrupt mask - sets timer behaviour - we want overflow interrupt */
	TIMSK0 = (1 << TOIE0);
	
	/* use duty cycle to determine compare register value for each pin
	 * dutyCycle is a percentage (out of 100) representing the duration that the pin should be high
	 * based on the maximum value of the timer's counter (it is 8-bit, so 255 is the max value)
	*/
	OCR0A = (dutyCycle/100) * 255;
	OCR0B = (dutyCycle/100) * 255;
	
	// enable interrupts
	sei();
}


void drive_forward() {
	/* reset global vars for juicing the motors appropriately */
	counter = 0;
	dutyCycle = startingDutyCycle;

	//*leftWheel.speedPortReg |= (1 << PIND5);
	*leftWheel.dir1PortReg |= (1 << PINB2);
	*leftWheel.dir2PortReg &= ~(1 << PINB3);

	//*rightWheel.speedPortReg |= (1 << PIND6);
	*rightWheel.dir1PortReg &= ~(1 << PINB4);
	*rightWheel.dir2PortReg |= (1 << PINB5);
	/* set prescaler to no prescaler */
	/* this starts the timer */
	TCCR0B = (1 << CS00);
}

void drive_back() {
	/* reset global vars for pumping up the motors appropriately */
	counter = 0;
	dutyCycle = startingDutyCycle;

	/* reverse left wheel */
	*leftWheel.dir1PortReg &= ~(1 << PINB2);
	*leftWheel.dir2PortReg |= (1 << PINB3);

	/* reverse right wheel */
	*rightWheel.dir1PortReg |= (1 << PINB4);
	*rightWheel.dir2PortReg &= ~(1 << PINB5);

	/* Start timer */
	TCCR0B = (1 << CS00);
}

void turn() {
	/* Goal is to turn the vehicle ~90 degrees - for now, will use _delay_ms() to turn for period of time,
	 * then disable motors. If this is to be made variable, will likely need to set up hardware timer */
	
	/* reset global vars for pumping up the motors appropriately */
	counter = 0;
	dutyCycle = startingDutyCycle;

	/* left wheel forward */	
	*leftWheel.dir1PortReg |= (1 << PINB2);
	*leftWheel.dir2PortReg &= ~(1 << PINB3);

	/* right wheel backward */
	*rightWheel.dir1PortReg |= (1 << PINB4);
	*rightWheel.dir2PortReg &= ~(1 << PINB5);

	/* Start timer */
	TCCR0B = (1 << CS00);
}

void drive_stop() {
	//*leftWheel.speedPortReg &= ~(1 << PIND5);
	*leftWheel.dir1PortReg &= ~(1 << PINB2);
	*leftWheel.dir2PortReg &= ~(1 << PINB3);

	//*rightWheel.speedPortReg &= ~(1 << PIND6);
	*rightWheel.dir1PortReg &= ~(1 << PINB4);
	*rightWheel.dir2PortReg &= ~(1 << PINB5);
	
	//stop the timer (turn off motors)
	TCCR0B &= ~(1 << CS00);
}

void updateDutyCycle(double newDutyCycle) {
	OCR0A = (newDutyCycle/100) * 255;
	OCR0B = (newDutyCycle/100) * 255;
}
	
ISR(TIMER0_OVF_vect)
{
	counter++;

	if (counter == 500 && dutyCycle != desiredDutyCycle) {
		dutyCycle = desiredDutyCycle;
		updateDutyCycle(dutyCycle);
	}
}

