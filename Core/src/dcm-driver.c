/*
 *	DC Motor Driver
 *
 *  Author: Wil Scott
 *  Created: Jan 2024
*/

#include "../inc/dcm-driver.h"

/* create wheel structs */
struct wheel leftWheel = { &PORTB, &DDRB, &PORTD, &DDRD, &PORTD, &DDRD };
struct wheel rightWheel = { &PORTB, &DDRB, &PORTB, &DDRB, &PORTB, &DDRB };

/*
 * Left and Right wheel currently connected to pins 10 (PB2), 7 (PD7), 6 (PD6) and 11 (PB3), 13 (PB5), 12 (PB4) respectively.
 * May require changing if pin configs moved to general/comprehensive config file.
*/
void wheel_config() {
	/* setup Left Wheel - reset pin to low and direction to out*/
	*leftWheel.speedPortReg &= ~(1 << PINB2); // pb2 is pwm pin - for now speed is either 0 (off) or 1 (on)
	*leftWheel.speedDirectionReg |= (1 << PINB2);
	*leftWheel.dir1PortReg &= ~(1 << PIND7);
	*leftWheel.dir1DirectionReg |= (1 << PIND7);
	*leftWheel.dir2PortReg &= ~(1 << PIND6);
	*leftWheel.dir2DirectionReg |= (1 << PIND6);
	/* setup Right Wheel - reset pin to low and direction to out*/
	*rightWheel.speedPortReg &= ~(1 << PINB3);
	*rightWheel.speedDirectionReg |= (1 << PINB3);
	*rightWheel.dir1PortReg &= ~(1 << PINB5);
	*rightWheel.dir1DirectionReg |= (1 << PINB5);
	*rightWheel.dir2PortReg &= ~(1 << PINB4);
	*rightWheel.dir2DirectionReg |= (1 << PINB4);
}

void drive_forward() {
	*leftWheel.speedPortReg |= (1 << PINB2);
	*leftWheel.dir1PortReg |= (1 << PIND7);
	*leftWheel.dir2PortReg &= ~(1 << PIND6);

	*rightWheel.speedPortReg |= (1 << PINB3);
	*rightWheel.dir1PortReg |= (1 << PINB5);
	*rightWheel.dir2PortReg &= ~(1 << PINB4);
}


void drive_stop() {
	*leftWheel.speedPortReg &= ~(1 << PINB2);
	*leftWheel.dir1PortReg &= ~(1 << PIND7);
	*leftWheel.dir2PortReg &= ~(1 << PIND6);

	*rightWheel.speedPortReg &= ~(1 << PINB3);
	*rightWheel.dir1PortReg &= ~(1 << PINB5);
	*rightWheel.dir2PortReg &= ~(1 << PINB4);
}
	


