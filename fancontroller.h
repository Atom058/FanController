#ifndef HEADER_FILE
#define HEADER_FILE

	//Includes
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <avr/eeprom.h>
	#include <util/delay.h>

	//Function delcarations
	void setup(void);
	void startup(void);
	void recordFanCurrents(void); 
	uint16_t readFanCurrent(uint8_t channel);
	void checkConnection(void);
	void refreshDisplay(void);
	void shiftout(uint32_t input);

	//Synonyms for shitf registry
	#define SHIFTREG PORTD
	#define SER PORTD0
	#define SRCLK PORTD1
	#define SRCLR PORTD2
	#define RCLK PORTD3
	#define OE PORTD4

	//Synonyms for LED refresh interrupt
	#define REFRESHPORT PORTD
	#define REFRESH PORTD7

	//Storage of fan status
	#define FAN1CONN 0
	#define FAN2CONN 1
	#define FAN3CONN 2
	#define FAN4CONN 3
	#define FAN5CONN 4

	//Fans' PWM channels
	#define FAN1PWM OCR0A
	#define FAN2PWM OCR0B
	#define FAN3PWM OCR1A
	#define FAN4PWM OCR1B
	#define FAN5PWM OCR0A

	//Fans' analog channels
	#define FAN1CH 0b00000000
	#define FAN2CH 0b00000001
	#define FAN3CH 0b00000010
	#define FAN4CH 0b00000011
	#define FAN5CH 0b00000100

	//Minimum current reading to identify active fan
	#define CONNECTIONTHRESHOLD 2

	//Colour synonyms
	#define RED 0
	#define GREEN 1
	#define BLUE 2

	//Number of unused bits at the end of the shit registry chain
	#define SHIFTREGISTEREMPTYBITS 2

	//Synonyms for LED's
	#define LED01 1
	#define LED02 2
	#define LED03 3
	#define LED04 4
	#define LED05 5
	#define LED06 6
	#define LED07 7
	#define LED08 8
	#define LED09 9
	#define LED10 10

#endif