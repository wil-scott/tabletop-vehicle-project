/*
 *	HC-SR04 Distance Sensor Driver
 *
 *  Author: Wil Scott
 *	Created: Sept 2023
*/
#include <avr/interrupt.h>
//PB1, PE3, PA1 for echo, trigger, and power respectively
#include "HCSR04.h"

// global volatile vars for tracking duration and a timeout flag
volatile uint32_t pulse_dur_us = 0;
volatile uint8_t timeout = 0;
volatile uint8_t isr_triggered = 0;

volatile uint32_t pulse_start = 0;
volatile uint32_t pulse_end = 0;
volatile uint8_t pulse_detected = 0;

/*
 * Set Trigger pin high for 19
 */
void trigger(void)
{
	PORTE.OUT &= ~PIN3_bm;
	_delay_us(2);
	PORTE.OUT |= PIN3_bm;
	_delay_us(10);
	PORTE.OUT &= ~PIN3_bm;
}

void init_pin(void)
{
	// Pin change interrupt for the input pin (PB0 in this example)

    PORTB.PIN0CTRL = PORT_ISC_BOTHEDGES_gc; // Trigger on both edges
    PORTB.DIRCLR |= PIN0_bm; // Set PB0 as input
    PORTB.INTFLAGS |= 0x01; //clear intflag
}



/*
 * Configure Timer B to count microseconds
 */
void init_tcb(void)
{
	// set up event system
	EVSYS.CHANNEL7 = EVSYS_GENERATOR_PORT1_PIN0_gc;
	
	TCB0.CTRLA = TCB_CLKSEL_CLKDIV1_gc; // no prescaler
	TCB0.CTRLB = TCB_CNTMODE_PW_gc; // count mode set to pulse width measure
	TCB0.EVCTRL = TCB_CAPTEI_bm; // Event input capture enabled
	TCB0.INTCTRL = TCB_CAPT_bm; // capture interrupt enabled
	TCB0.CTRLA = TCB_CLKSEL_CLKDIV1_gc | TCB_ENABLE_bm; //enable timer
}

/*
 * Start the timer
 */
void enable(void)
{
	pulse_detected = 0;
	pulse_start = 0;
	pulse_end = 0;
}


ISR(TCB0_INT_vect)
{
	PORTF.OUT |= PIN5_bm;
	pulse_dur_us = TCB0.CCMP;
	pulse_detected = 1;
/*	//increment counter*/
/*	pulse_detected = 1;*/
/*	pulse_end = TCA0.SINGLE.CNT;*/
/*	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;*/
	
}

/*ISR(PORTB_PORT_vect)*/
/*{*/

/*	if (PORTB.IN & PIN0_bm) {*/
/*		pulse_start = TCB0.CCMP;*/
/*	} else {*/
/*		pulse_end = TCB0.CCMP;*/
/*		pulse_detected = 1;*/
/*	}*/
/*}*/

/*
 * Set Trigger pin high for 
 */
int distance(void)
{
	PORTF.DIRSET |= PIN5_bm;
	init_pin();
	init_tcb();
	sei();
/*	// Wait for the pin to go high*/
/*	while (!(PORTB.IN & PIN0_bm)) {}*/
/*	enable();*/
/*	//enable_timer();*/
/*	while (PORTB.IN & PIN0_bm) {}*/
/*	disable();*/

	while(1) {
		trigger();
		if(pulse_detected) {
			//PORTF.OUT |= PIN5_bm;
			//pulse_dur_us = (pulse_end - pulse_start);
			return pulse_dur_us;
		}
		_delay_ms(1);
	}

}



