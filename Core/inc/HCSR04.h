/*
 *	HC-SR04 Ultrasonic Distance Sensor Driver
 *
 *  Author: Wil Scott
 *	Created: Oct 2023
*/

#ifndef __HCSR04_DRIVER_H__
#define __HCSR04_DRIVER_H__

/* include HAL for ATMEGA328p */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/*
 * DEFINES
 */


/*
 * Low Level Functions
 */



/*
 * Public Functions
 */
int measure();


#endif
