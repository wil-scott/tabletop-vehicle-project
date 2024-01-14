/*
* I2C/TWI driver for the Atmega328p using polling - interrupt approach
* may interfere with interrupts necessary to measure PW for HCSR04
*
* Author: Wilson Scott
* Date: Sept 2023
*/

//Includes
#include "twi.h"

static uint8_t rec_address;

// Status Codes - TWSR - Master Mode
enum { START = 0x08, REPEAT_START = 0X10, SLAW_ACK = 0x18, SLAW_NACK = 0x20, DATA_ACK = 0x28, DATA_NACK = 0x30, ARB_LOST = 0x38 };


void twi_init(void) 
{
	//turn on TWI pins
	DDRC |= (1<<PINC4);
	DDRC |= (1<<PINC5);

	// SCL Freq = CPU Freq/(16 + 2(TWBR)*(prescaler value))
	// prescaler val = 1 (TWSR bit 0,1 are set to 0, 0)'
	// TWBR = 0x48 (decimal 72)
	// SCL Freq = 16000000/16 = 100000
	TWSR &= ~1; //0000 0001 -> 1111 1110
	TWSR &= ~(1<<1); //0000 0010 -> 1111 1101
	TWBR = 0x48;
}


//  Send START via TWCR register
//	Wait for TWINT flag set in TWCR
//	check value of TWSR (status) - mask prescaler bits using 0xF8)
//	load SLA_W into TWDR
//	clear TWINT bit in TWCR to start transmission of addr
//	wait for TWINT flag set -> SLA+W has been transmitted, ack/nack recvd
void twi_start() 
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	while (!(TWCR & (1<<TWINT))) {}
	
	TWDR = rec_address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while (!(TWCR & (1<<TWINT))) {}
	
}


//	check val of TWI Status Reg - mask prescaler bits - for MT_SLA_ACK
//	Load DATA into TDWR Register
//	clear TWINT bit in TWCR to start transmit
//	wait for TWINT Flag set, indicating DATA has been transmitted/recvd
//	check val of TWI Status Reg - mask prescaler bits - for MT_DATA_ACK
void twi_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while (!(TWCR & (1<<TWINT))) {}
}


//	Transmit STOP
void twi_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

/*****************************************************************
 * 
 * Public Functions
 *
 *****************************************************************/
void set_address(uint8_t addr)
{
	rec_address = addr;
}


void i2c_init(uint8_t addr)
{
	rec_address = addr;
	twi_init();
}


void i2c_write_array(const uint8_t* data_buffer, int data_size)
{
	twi_start();
	for (int i=0; i < data_size; i++)
	{
		twi_write(data_buffer[i]);
	}
	twi_stop();
}


void i2c_start()
{
	twi_start();
}


void i2c_write(uint8_t data)
{
	twi_write(data);
}


void i2c_stop()
{
	twi_stop();
}

