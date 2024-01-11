/*
 * DC Motor Driver
 *
 * Author: Wil Scott
 * Created: Jan 2024
*/

#ifndef __DCM_DRIVER_H__
#define __DCM_DRIVER_H__

#include <avr/io.h>

struct wheel {
	volatile uint8_t *speedPortReg;
	volatile uint8_t *speedDirectionReg;
	volatile uint8_t *dir1PortReg;
	volatile uint8_t *dir1DirectionReg;
	volatile uint8_t *dir2PortReg;
	volatile uint8_t *dir2DirectionReg;
};

void wheel_config();
void drive_forward();
void drive_stop();

#endif
