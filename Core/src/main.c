#include "../lib/twi.h"
#include "../inc/SSD1306.h"
#include "../inc/HCSR04.h"
#include "../inc/dcm-driver.h"
#include <string.h>
#include <stdio.h>


void init_oled()
{
	SSD1306_init( SSD1306_I2C_ADDR );
	SSD1306_clear_display();
}	


int number_of_digits(int num)
{
	int count = 0;
	
	if (num == 0) { return 1; }

	while (num != 0) {
		num = num / 10;
		count++;
	}

	return count;
}


void update_distance(int distance)
{
	char *distance_str;
	int str_len = strlen("DISTANCE: ") ;
	int digits_len = number_of_digits(distance);
	int total_len = str_len + digits_len;
	
	distance_str = malloc(total_len);
	sprintf(distance_str, "DISTANCE: %d", distance);

	SSD1306_clear_page(PAGE_ONE);
	display_string(distance_str, total_len, PAGE_ONE, PAGE_ONE_MIN_COL);
	free(distance_str);
}


/* if table surface detected, drive forward. 
 * If already driving forward, return 1 and do nothing
 * If not already driving, start driving and return 1
*/
int car_forward(int driving)
{
	// update display
	char driving_str[] = "STATUS: DRIVING";
	int str_len = strlen(driving_str) ;

	if (!driving) {
		drive_forward();		
	}
	
	SSD1306_clear_page(PAGE_ZERO);
	display_string(driving_str, str_len, PAGE_ZERO, PAGE_ZERO_MIN_COL);
	
	// update driving status/flag
	return 1;
}


void car_backward()
{
	char driving_str[] = "STATUS: REVERSING";
	int str_len = strlen(driving_str) ;

	drive_back();
	SSD1306_clear_page(PAGE_ZERO);
	display_string(driving_str, str_len, PAGE_ZERO, PAGE_ZERO_MIN_COL);
}


int car_stop()
{
	char driving_str[] = "STATUS: STOPPED";
	int str_len = strlen(driving_str) ;
	int return_value;
	
	return_value = drive_stop();
	SSD1306_clear_page(PAGE_ZERO);
	display_string(driving_str, str_len, PAGE_ZERO, PAGE_ZERO_MIN_COL);
	return return_value;
}


void car_turn()
{
	char driving_str[] = "STATUS: TURNING";
	int str_len = strlen(driving_str) ;

	turn();
	SSD1306_clear_page(PAGE_ZERO);
	display_string(driving_str, str_len, PAGE_ZERO, PAGE_ZERO_MIN_COL);
}


int main()
{
	int distance;
	int driving = 0; // 0 means not driving forward, 1 means driving forward
	
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
			driving = car_forward(driving);
		} else if (distance > 5) {
			driving = car_stop();
			car_backward();
			_delay_ms(250);
			driving = car_stop();
			car_turn();
			_delay_ms(400);
			driving = car_stop();
		}
		update_distance(distance);
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
