#include "../lib/twi.h"
#include "../inc/SSD1306.h"
#include "../inc/HCSR04.h"
#include "../inc/dcm-driver.h"


void init_oled()
{
	SSD1306_init( SSD1306_I2C_ADDR );
	SSD1306_clear_display();
	char row1[] = "STATUS: FUNCTIONAL";
	char row2[] = "DISTANCE: NULL";

	display_string(row1, 18, PAGE_ZERO, PAGE_ZERO_COL_START);
	display_string(row2, 14, PAGE_ONE, PAGE_ONE_COL_START);
}	


/* if table surface detected, drive forward. 
 * If already driving forward, return 1 and do nothing
 * If not already driving, start driving and return 1
*/
int car_drive_forward(int driving)
{
	if (!driving) {
		drive_forward();		
	}
	return 1;
}


int main()
{
	int distance;
	int driving = 0; // 0 means not driving forward, 1 means driving forward
	char row1[20]; // STATUS: XYZ
	char row2[20]; // DISTANCE: Xcm
	
	init_oled();
	wheel_config();
	/* Logic: While the distance sensor detects a table surface, drive forward. When no surface is detected
	 * stop, back up, turn, check whether the table surface is detected. If yes, repeat. If no, turn again and repeat.
	 * NOTE: Logic loop currently assumes that vehicle will start in the middle of a table surface.
	*/
	while(1) {
		distance = measure();
		if (distance <= 5) {
			// approximate distance between HCSR04 and bottom of front wheel: ~4cm
			driving = car_drive_forward(driving);
		} else if (distance > 5) {
			driving = drive_stop();
			drive_back();
			_delay_ms(250);
			driving = drive_stop();
			turn();
			_delay_ms(400);
			driving = drive_stop();
		}
	}

//	wheel_config();
//	drive_forward();
//	_delay_ms(5000);
//	drive_stop();
//	drive_back();
//	_delay_ms(1000);
//	drive_stop();
//	turn();
//	_delay_ms(5000);
//	drive_stop();

//	while(1){
//		int distance = measure();
//		if (distance == -1) {
//			char timeout[] = "DISTANCE: TIMEOUT";
//			display_string(timeout, 17, 0x01, 0x80);
//		
//		} else {
//			char row3[20];
//			sprintf(row3, "DISTANCE: %d cm", distance);
//			display_string(row3, 18, 0x01, 0x80);
//		}
//	}

}
