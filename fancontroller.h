#ifndef HEADER_FILE
#define HEADER_FILE

	//Includes
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <avr/eeprom.h>

	//Function delcarations
	void setup(void);

	#define SER PORTD0
	#define SRCLK PORTD1
	#define SRCLR PORTD2
	#define RCLK PORTD3
	#define OE PORTD4

	#define FAN0 0
	#define FAN1 1
	#define FAN2 2
	#define FAN3 3
	#define FAN4 4

#endif