/*
 * This is an initial attempt at writing a basic I2C config/init interface for
 * the ATMEGA4809 (specific to its implementation on the Arduino Nano Every)
 *
 * Author: Wilson Scott
 * Date: August 2023
 */

#ifndef __TWI_H__
#define __TWI_H__

#include <inttypes.h>

void i2c_init(uint8_t address);
uint8_t i2c_write_array(const uint8_t* data_buffer, int data_size);
void i2c_start();
void i2c_write(uint8_t byte);
void i2c_stop();

#endif
