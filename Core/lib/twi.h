#ifndef __TWI_H__
#define __TWI_H__

#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void set_address(uint8_t addr);
void i2c_init(uint8_t addr);
void i2c_write_array(const uint8_t* data_buffer, int data_size);

void i2c_start();
void i2c_write(uint8_t data);
void i2c_stop();

#endif
