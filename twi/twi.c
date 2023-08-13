/*
 * This is an initial attempt at writing a basic I2C config/init 'driver' for
 * the ATMEGA4809 (specific to its implementation on the Arduino Nano Every)
 *
 */

// Includes
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// BUS STATES
enum { UNKNOWN = 0x00, IDLE = 0x01, OWNER = 0x02, BUSY = 0x03 };

// MSTATUS
enum { RIF = 0x80, WIF = 0x40, CLK = 0x20, RXACK = 0x10, ARBLOST = 0x08, BUSERR = 0x04 };

// MCTRLB -> xxxx FLUSH3|ACK2|CMD1,0
enum { FLUSH = 0x08, NACK = 0x04, STOP = 0x03, READ = 0x02, ACK = 0x0 };

/*
 * Initializes the TWI module on the ATMEGA4809 as Host
 */
void TWI_Init(void)
{
	// HOST INIT
	// Initialize host baud rate
	TWI0.MBAUD = 76; // CPU 16,000,000hz and TWI 100,000hz
	
	//Force Bus in Host State to idle, reset all other register bits
	TWI0.MSTATUS = 0xED;	
	
	//Enable TWI as Host
	TWI0.MCTRLA |= 0x01;
}


/*
 * Turns on RIF/WIF interrupt flags (MSTATUS register)
 */
void TWI_interrupt_init(void)
{
	TWI0.MCTRLA |= 0xC0; // 0b1100000 -> Turns on RIF and WIF interrupt/flags
	//sei(); -> enables cpu interrupt on CPU.SREG
}
/*
 * Set address before enabling TWI to prevent START sig
 * Note: addr requires 8-bit I2C address (AKA a pre-bit-shifted 7-bit address)
 */
void TWI_Set_Address(uint8_t addr)
{
	TWI0.MCTRLA &= ~1; //ensure TWI module disabled
	TWI0.MADDR = addr; 
}

/*
 * START Signal
 * 
 * Current implementation only considers Write cmd (dir bit in addr set to 0)
 */
void TWI_Start(void)
{
	//writing to MADDR sends a start signal
	TWI0.MADDR &= ~0x1; //re-write current address
}

/*
 * STOP Signal
 * OR NACK and STOP -> releases CLK line
 */
void TWI_Stop(void)
{
	TWI0.MCTRLB |= NACK|STOP;
}
/*
 * WRITE to address
 * currently waits for WIF flag (either from MADDR set, or previous MDATA write)
 * Future versions will likely rely on interrupt/ISR (move away from polling)
 */
void TWI_Write(uint8_t data)
{
	if (sizeof(data) == 1) { //if errors, blink and continue
		PORTE.OUT |= PIN3_bm;
	}
	while (!(TWI0.MSTATUS & WIF)) {	}
/*	if ((TWI0.MSTATUS & 0x10) == 1) {*/
/*		PORTE.OUT |= PIN2_bm;*/
/*	}*/
/*	if ((TWI0.MSTATUS & (ARBLOST|BUSERR))){*/
/*		PORTE.OUT |= PIN2_bm;*/
/*	}*/
	TWI0.MDATA = data;

}

/*****************************************************************
 * 
 * Public Functions
 *
 *****************************************************************/
uint8_t i2c_write(volatile uint8_t* data_buffer, int data_size)
{
	TWI_Start();
	TWI_interrupt_init();

	for (int i = 0; i < data_size; i++)
	{
		TWI_Write(data_buffer[i]);
	}
	_delay_ms(25);
	TWI_Stop();
	return 0x00;
}

//uint8_t config_buff[] = { 0x00, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC0, 0xDA, 0x02, 0x81, 0x7F, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF };
static const uint8_t *start;
static const uint8_t *end;

int main(void)
{
	//enable TWI pins for read/write
	PORTA.DIR |= PIN2_bm;
	PORTA.DIR |= PIN3_bm;
	// set LED Port to write (for debugging)
	PORTE.DIR |= PIN2_bm;
	PORTE.DIR |= PIN3_bm;
	PORTA.DIR |= PIN1_bm;
	
	_delay_ms(20); // delay to allow I2C device to turn on
	
	//init TWI Addr
	TWI_Set_Address(0x78);
	
	//init TWI
	TWI_Init();
	//TWI_Start();
	//TWI_interrupt_init();
	
	static volatile uint8_t config_buff[19] = { 0x00, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC0, 0xDA, 0x02, 0x81, 0x7F, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF };

	uint8_t ret_val = i2c_write(config_buff, 19);
	
	//_delay_ms(25); // need to wait for WIF flag after last write command
	//TWI_Stop();

	// turn off LED to confirm finished/not crashed
	if (TWI0.MSTATUS == 0x1) {
		PORTE.OUT &= ~PIN3_bm;
		PORTA.OUT &= ~PIN1_bm;
	}
	
	return 0;
}


/*	}*/
	// general config commands from SDD1306 data sheet for oled setup
/*	TWI_Write(0x00);*/
/*	TWI_Write(0xA8);*/
/*	TWI_Write(0x3F);*/
/*	TWI_Write(0xD3);*/
/*	TWI_Write(0x00);*/
/*	TWI_Write(0x40);*/
/*	TWI_Write(0xA1);*/
/*	TWI_Write(0xC0);*/
/*	TWI_Write(0xDA);*/
/*	TWI_Write(0x02);*/
/*	TWI_Write(0x81);*/
/*	TWI_Write(0x7F);*/
/*	TWI_Write(0xA4);*/
/*	TWI_Write(0xA6);*/
/*	TWI_Write(0xD5);*/
/*	TWI_Write(0x80);*/
/*	TWI_Write(0x8D);*/
/*	TWI_Write(0x14);*/
/*	TWI_Write(0xAF);*/




















































