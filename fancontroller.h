#ifndef HEADER_FILE
#define HEADER_FILE

	//Includes
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <avr/eeprom.h>

	//Function delcarations
	void setup(void);
	void startup(void);
	void recordFanCurrents(void); 
	uint8_t readFanCurrent(uint8_t channel);
	void checkConnection(void);

	#define SER PORTD0
	#define SRCLK PORTD1
	#define SRCLR PORTD2
	#define RCLK PORTD3
	#define OE PORTD4

	#define FAN1CONN 0
	#define FAN2CONN 1
	#define FAN3CONN 2
	#define FAN4CONN 3
	#define FAN5CONN 4

	#define FAN1PWM OCR0A
	#define FAN2PWM OCR0B
	#define FAN3PWM OCR1A
	#define FAN4PWM OCR1B
	#define FAN5PWM OCR0A

	#define FAN1CH 0b00000000
	#define FAN2CH 0b00000001
	#define FAN3CH 0b00000010
	#define FAN4CH 0b00000011
	#define FAN5CH 0b00000100

	#define CONNECTIONTHRESHOLD 2

#endif