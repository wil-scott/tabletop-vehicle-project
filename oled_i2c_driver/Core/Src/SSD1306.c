/*
 *	SSD1306 OLED I2C Driver
 *
 *  Author: Wil Scott
 *	Created: August 2023
*/

#include "SSD1306.h"
#include "font6x8.h"
#include <util/delay.h>


void SSD1306_init( uint8_t address )
{
	_delay_ms(20); // delay to allow I2C device to turn on
	i2c_init(SSD1306_I2C_ADDR); //init with standard OLED address 0x3C << 1
	_delay_ms(20);
	
	const uint8_t initialize_OLED[27] = {
	CMD_STREAM,
	//SET GENERAL CMDS
	SSD_DISPLAY_OFF, 
	SSD_SET_CONTRAST,
	0X7F,
	SSD_DISPLAY_NORMAL,
	//DISABLE SCROLL
	SSD_DEACT_SCROLL,
	//ADDR CMDS
	SSD_SET_ADDR_MODE,
	0X02,
	//HARDWARE CMDS
	SSD_SET_SEGMENT_REMAP,
	SSD_SET_MUX_RATIO,
	0X1F,
	SSD_COM_SCAN_DIR,
	SSD_SET_DISPLAY_OFFSET,
	0X00,
	SDD_DISPLAY_START_LINE,
	SSD_SET_COM_PINS,
	0X02,
	//TIMING CMDS
	SSD_SET_DISPLAY_CLK,
	0X80,
	SSD_SET_PRECHRG,
	0X22,
	SSD_SET_VCOM,
	0x20,
	//CHARGE PUMP
	SSD_CHARGE_PUMP,
	0X14,
	//TURN ON SCREEN
	SSD_DISPLAY_RAM,
	SSD_DISPLAY_ON
	};

	i2c_write_array(initialize_OLED, 27);
	
}

void SSD1306_clear_display()
{

	for (uint8_t page = 0; page < 4; page++) {
	
		const uint8_t arr[4] = { 0x00, 0x01, 0x02, 0x03 };
		set_cursor(0x00, arr[page]);
		
		for (int col = 0; col < 128; col++) {
			SSD1306_WriteData(0x00);
		}
	}
}

void set_cursor(uint8_t col, uint8_t page)
{
	uint8_t temp1 = 0x00 + (col & 0x0F);
	uint8_t temp2 = 0x10 + ((col >> 4) & 0x0F);
	uint8_t temp3 = 0xB0 + page;
	SSD1306_WriteCommand(temp1);
	SSD1306_WriteCommand(temp2);
	SSD1306_WriteCommand(temp3);
}

/*
 * STRING TO DISPLAY
 */

void display_string(char* string, int str_len, uint8_t page )
{
	set_cursor(0x00, page);
	
	for (int str_char = 0; str_char < str_len; str_char++) {
		int char_index = (string[str_char] - 32) * 6;
		//int char_index = string[str_char];
		//uint8_t *testarray[7] = { DATA_STREAM };
		for (int byte = 0; byte < 6; byte++) {

			int temp = char_index + byte;
			//int temp2 = byte + 1;
			uint8_t tester = font6x8[temp];
			//uint8_t tester = testarr2[char_index][byte];
			//uint8_t tester = font8x8_basic[char_index][byte];
			SSD1306_WriteData(tester);
			//testarray[temp2] = font6x8[temp];
			//i2c_write_array(testarray, 7);
		}
	}

}

/*
 * LOW-LEVEL FUNCTIONS
 */
void SSD1306_WriteCommand( uint8_t byte )
{
	i2c_start();
	i2c_write(SINGLE_CMD_BYTE);
	i2c_write(byte);
	i2c_stop();
}

void SSD1306_WriteData( uint8_t byte )
{
	i2c_start();
	i2c_write(SINGLE_DATA_BYTE);
	i2c_write(byte);
	i2c_stop();
}

/*void SSD1306_datastream( uint8_t* stream, int stream_len){*/
/*	i2c_write_array(config_buff, 19);*/
/*}*/











