/*
 *	SSD1306 OLED I2C Driver
 *
 *  Author: Wil Scott
 *	Created: August 2023
*/

#include "../inc/SSD1306.h"


/*
 * Configure OLED screen
*/
void SSD1306_init( uint8_t address )
{
	_delay_ms(20); // delay to allow I2C device to turn on
	i2c_init(address); //init with standard OLED address 0x3C << 1
	
	//boot up sequence for SSD1306 via data sheet
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
		SSD_HORIZ_MODE,
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
		SSD_DISPLAY_ON,
	};

	i2c_write_array(initialize_OLED, 27);
	
}


/*
 * Set, or reset, the location of the cursor on the OLED Screen.
*/
void set_cursor(uint8_t col_min, uint8_t col_max, uint8_t page_min, uint8_t page_max)
{
	const uint8_t arr[7] = {	
		CMD_STREAM,
		SSD_PAGE_ADDR,
		page_min,
		page_max,
		SSD_COL_ADDR,
		col_min,
		col_max,
	};
	
	i2c_write_array(arr, 7);
}


/*
 * Clear display by writing empty bits/bytes to each location.
*/
void SSD1306_clear_display()
{

	set_cursor(0x00, 0x7F, 0x00, 0x03);
	i2c_start();
	i2c_write(DATA_STREAM);
	for (int col = 0; col < 512; col++) {
		i2c_write(0x00);
	}
	i2c_stop();			
}


/*
 * Take input string, and intended location (page, column), and write to OLED.
 * Used loop to iterate through each char in string, conver to ASCII value, and determine location
 * of ASCII value in font array. Iterates through each byte of the ASCII value and writes it to the display.
 */
void display_string(char* string, int str_len, uint8_t page, uint8_t col )
{

	set_cursor(col, 0x7F, page, 0x03);
	
	i2c_start();
	i2c_write(DATA_STREAM);
	for (int str_char = 0; str_char < str_len; str_char++) {
	
		int char_index = (string[str_char] - 32) * 6;

		for (int byte = 0; byte < 6; byte++) {

			int current_byte = char_index + byte;
			uint8_t col = font6x8[current_byte];
			i2c_write(col);

		}
	}
	
	i2c_stop();

}


/*
 * Write single Command or Data byte to the OLED.
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

