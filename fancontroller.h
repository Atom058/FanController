#ifndef HEADER_FILE
#define HEADER_FILE

	//Includes
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <avr/eeprom.h>
	#include <util/delay.h>

	//General functions
	void setup(void);
	void startup(void);

	//Fan functions
	uint16_t readFanCurrent(uint8_t channel);
	void checkConnections(void);

	//Display functions
	void refreshDisplay(void);
	uint8_t copyToBuffer(uint8_t LED);
	void setColour(uint8_t led, uint8_t redCh, uint8_t greenCh, uint8_t blueCh);
	void setAllColours(uint8_t redCh, uint8_t greenCh, uint8_t blueCh);
	void setColourType(uint8_t led, uint8_t colour[3]);
	void setAllColoursToType(uint8_t colour[3]);
	void shiftout(uint32_t input);

	//Interface Function
	void updateInterface(void);
	void parseInput(void);

	//View controllers (as functions #Yolo)
	void startController(void);
	void settingsController(void);
	void setfanController(void);
	void colouroverviewController(void);
	void coloursettingController(void);
	void colourchannelsettingController(void);

	//Debug controllers
	void debuginputController(void);
	void debugdisplayController(void);

	//Input functions
	void checkButton(uint8_t buttonStatus, uint8_t buttonTimer);

	//PORT LOCATIONS
		//Shift registry
			// Location of: SHIFTREG PORTD
			// Location of: SER PORTD0
			// Location of: SRCLK PORTD1
			// Location of: _SRCLR_ PORTD2
			// Location of: RCLK PORTD3
			// Location of: _OE_ PORTD4

		//LED refresh interrupt
			// Location of: REFRESHPORT PORTD
			// Location of: REFRESHPIN PORTD7

		//Fans' PWM channels
			// Location of: FAN1PWM OCR0A / P11 / PD5
			// Location of: FAN2PWM OCR0B / P12 / PD6
			// Location of: FAN3PWM OCR1A / P15 / PB1
			// Location of: FAN4PWM OCR1B / P16 / PB2
			// Location of: FAN5PWM OCR2A / P17 / PB3

	//Debugging switches - only one at the time!
	#define DEBUGINPUT 0
	#define DEBUGDISPLAY 0

	//Startup timings
	#define STARTUPFANWARMINGPERIOD 4000
	#define STARTUPFANWARMINGINDICATORINTERVAL 250

	//Timing functions
	#define WDTTIMOUT 16

	#define DEBOUNCETURN 150 
	#define DEBOUNCEBUTTON 250


	//Storage of fan status
	#define FAN1 0
	#define FAN2 1
	#define FAN3 2
	#define FAN4 3
	#define FAN5 4

	//Fans' analog channels
	#define FAN1CH 1
	#define FAN2CH 2
	#define FAN3CH 3
	#define FAN4CH 4
	#define FAN5CH 5

	//Minimum current reading to identify active fan
	#define CONNECTIONTHRESHOLD 20
	//Upper current bound allowed. Controls that no short or still fans are present.
	#define UPPERCURRENTTHRESHOLD 800
	//Waiting time in µs between unconnected output is turned on and current reading
	#define UNCONNECTEDFANSTARTUPTIME 50

	//Fan profile constants
	#define LPROFILE 0
	#define MPROFILE 1
	#define HPROFILE 2

	//Colour synonyms
	#define RED 0
	#define GREEN 1
	#define BLUE 2
	#define DIMMER 3 //DEPRACTED!

	#define MAXCHANNELVALUE 5

	#define REDLEDSHIFT 1
	#define GREENLEDSHIFT 1
	#define BLUELEDSHIFT -1

	//Number of unused bits at the end of the shit registry chain
	#define SHIFTREGISTEREMPTYBITS 2

	//Synonyms for LED's - these are in the opposite direction to index!
	#define LED01 9
	#define LED02 8
	#define LED03 7
	#define LED04 6
	#define LED05 5
	#define LED06 4
	#define LED07 3
	#define LED08 2
	#define LED09 1
	#define LED10 0

	#define PRIMARYCOLOUR 0
	#define COMPLEMENTCOLOUR 1
	#define SELECTCOLOUR 2

	#define RCH 0
	#define GCH 1
	#define BCH 2

	//Interface view status
	#define VIEWSTART 0
	#define VIEWSETTINGS 1
	#define VIEWSETFAN 2
	#define VIEWCOLOUROVERVIEW 3
	#define VIEWCOLOURSETTING 4
	#define VIEWCOLOURCHANNELSETTING 5

	//Input references
	#define DOWN 0
	#define LEFT 1
	#define RIGHT 2

#endif
