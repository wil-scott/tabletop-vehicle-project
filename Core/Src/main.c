/*
 * @file	: main.c
 * @brief	: Runs main program
 *************************************************
 * @note	: This is an attempt to write an i2c driver for the
 *			  SDD1306 (specifically, the .91 inch 128*32 OLED version)
 *
 *
 */
/* Includes */
#include <util/delay.h>
#include <stdio.h>
#include "../Inc/SSD1306.h"
#include "../Inc/HCSR04.h"

#include <stdlib.h>

int main(void)
{
	//enable TWI pins for read/write -> relocate to separate config file in future
	PORTA.DIR |= PIN2_bm;
	PORTA.DIR |= PIN3_bm;
	
	SSD1306_init(0x78); // 
	_delay_ms(20);
	SSD1306_clear_display();
	char row1[] = "STATUS: FUNCTIONAL";
	char row2[] = "DISTANCE: NULL";

	display_string(row1, 18, 0x00, 0x00);
	display_string(row2, 14, 0x01, 0x80);
	
	//enable PB0, PE3, PA1 for echo, trigger, and power respectively
	PORTB.DIRCLR |= PIN0_bm;
	PORTE.DIRSET |= PIN3_bm;
	PORTA.DIRSET |= PIN1_bm;
	SSD1306_clear_display();


	if ((PORTB.IN & PIN0_bm) == 0x00) {
		display_string("in is low", 9, 0x02, 0x100);
	}
	int val = distance();
	char out[20];
	sprintf(out, "%d", val);
	display_string(out, 5, 0x0, 0x0);


/*    // Read the CLKCTRL.MCLKCTRLB register*/
/*    uint8_t mclkctrlb = CLKCTRL.MCLKCTRLB;*/

/*    // Check the OSC20MS bit (bit 6) to determine the clock speed*/
/*    uint8_t is20MHz = (mclkctrlb & CLKCTRL_OSC20MS_bm) != 0;*/
/*    if (is20MHz) {*/
/*    	PORTF.DIRSET |= PIN5_bm;*/
/*    	PORTF.OUT |= PIN5_bm;*/
/*    	_delay_ms(10);*/
/*    	PORTF.OUT &= ~PIN5_bm;*/
/*    	    	_delay_ms(10);    	PORTF.OUT |= PIN5_bm;*/
/*    }*/
    
}


/*	*/
/*	if ((PORTE.OUT & PIN3_bm) == 0) {*/
/*		display_string("e low", 5, 0x00, 0x00);*/
/*	}*/

/*	PORTE.OUT |= PIN3_bm;*/
/*	if ((PORTE.OUT & PIN3_bm) == 0x08) {*/
/*		display_string("e hi", 4, 0x01, 0x80);*/
/*	}	*/

/*	PORTE.OUT &= ~PIN3_bm;*/
/*	_delay_us(2);*/
/*	PORTE.OUT |= PIN3_bm;*/
/*	_delay_us(10);*/
/*	PORTE.OUT &= ~PIN3_bm;*/

/*	if ((PORTE.OUT & PIN3_bm) == 0) {*/
/*		display_string("e low!", 6, 0x00, 0x00);*/
/*	}*/

/*    int loop_count = 0;*/
/*    float elapsed_time_ns = 0;*/

/*    // Wait for the pin to go high*/
/*	while (!(PORTB.IN & PIN0_bm)) {}*/

/*    // Loop while the pin is high and count iterations*/
/*    while (PORTB.IN & PIN0_bm) {*/
/*        // Increment the loop counter*/
/*        loop_count++;*/

/*        // Check if the loop has been running for more than 38ms (38000000 ns)*/
/*        if (loop_count >= 38000000 / 50) {*/
/*            break;*/
/*        }*/
/*    }*/

    // Calculate the elapsed time in nanoseconds
   // elapsed_time_ns = loop_count * 50;

    // Calculate distance and print it
    //float distance_cm = (elapsed_time_ns * 0.0343) / 2000000.0; // Convert nanoseconds to centimeters
	//int distance_cm = (elapsed_time_ns * 343) / 10000;
   // printf("Distance: %.2f cm\n", distance_cm);

	
	//while (!(PORTB.IN & PIN0_bm)) {}
/*	if ((PORTB.IN & PIN0_bm) == 0x01) {*/
/*		display_string("in is high", 10, 0x01, 0x80);*/
/*	}*/

	//while (PORTB.IN & PIN0_bm) {
//		time += 125;
//	}
