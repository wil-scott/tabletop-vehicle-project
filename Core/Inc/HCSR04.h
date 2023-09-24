/*
 *	HCSR04 Driver
 *
 *  Author: Wil Scott
 *	Created: Sept 2023
*/

#ifndef __HCSR04_DRIVER_H__
#define __HCSR04_DRIVER_H__

#include <util/delay.h>
#include <avr/io.h>

void trigger(void);
int distance(void);

#endif
