#include <fancontroller.h>


//Timer unit, updated by WD timer approximately every 16ms
	uint16_t looptime = 0;

//Fan status
	uint16_t fan1Current = 0;
	uint16_t fan2Current = 0;
	uint16_t fan3Current = 0;
	uint16_t fan4Current = 0;
	uint16_t fan5Current = 0;

	uint16_t fan1CurrentMaxSpeed = 0;
	uint16_t fan2CurrentMaxSpeed = 0;
	uint16_t fan3CurrentMaxSpeed = 0;
	uint16_t fan4CurrentMaxSpeed = 0;
	uint16_t fan5CurrentMaxSpeed = 0;

	uint8_t connectedFans = 0;
	uint8_t currentProfile = HPROFILE;

//LED display variables
	uint8_t currentChannel[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t	LEDColours[10][3] = {
			  {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
		}; //Array holding current colour of all LED's, as well as a dimmer channel
	uint8_t	buffer[10][3] = {
			  {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
			, {0, 0, 0}
		}; //Array holding current colour of all LED's, used in sweeping the LED's

	//Map of linear intensities to Gamma-corrected values
	uint8_t gammaMap[8] = {0, 2, 4, 5, 6, 7};

//Interface status
	uint8_t currentView = VIEWSTART;
	uint8_t cursorPosition = LED01;

	//Default colour settings
	uint8_t noColour[3] = {0, 0, 0};
	uint8_t primaryColour[3] = {5, 0, 0};
	uint8_t complementColour[3] = {0, 5, 0};
	uint8_t selectColour[3] = {0, 0, 5};

int main (void) {

	cli();
	setup(); //Set up arduino
	startup(); //Initiate fan controller
	sei();

	//Testcolours

	//uint32_t shiftBit = 0x80000000; //Test light :)
	//shiftout(shiftBit);

	while(1){

		/*
		for(uint8_t dimmer=0; dimmer<8; dimmer++){

			for(uint8_t colour=0; colour<8; colour++){

				setColour(1, colour, 0, 0, dimmer); //red
				setColour(3, 0, colour, 0, dimmer); //red
				setColour(5, 0, 0, colour, dimmer); //red

				setColour(2, colour, dimmer, 0, 0); //yellow
				setColour(4, 0, colour, dimmer, 0); //cyan

				setColour(6, colour, colour, dimmer, 0);
				setColour(7, dimmer, colour, dimmer, 0);
				setColour(8, dimmer, 0, colour, 0);

				PORTC ^= _BV(PORTC5); //toggle indicator
				_delay_ms(500);

			}

		}
		*/


		/*
		//testing rotary encoder input, moving through LEDs
		if( (PINB>>PINB4 & 1) != 1 ){
			if( shiftBit>>31 & 1){
				shiftBit = 0x00000004; //Move to other end
			} else{
				shiftBit <<= 1; //Move one to the right
			}
			_delay_ms(DEBOUNCETURN);
		}
		if( (PINB>>PINB5 & 1) != 1 ){
			if( shiftBit>>2 & 1){
				shiftBit = 0x80000000; //Move to other end
			} else{
				shiftBit >>= 1; //Move one to the right
			}
			_delay_ms(DEBOUNCETURN);
		}
		if( (PINB>>PINB0 & 1) != 1 ){
			if( shiftBit>>31 & 1){
				shiftBit = 0x00000004; //Move to end
			} else{
				shiftBit = 0x80000000; //Move to begining
			}
			_delay_ms(DEBOUNCEBUTTON);
		}

		shiftout(shiftBit);
		*/


	//Rotary encoder input
	//TODO

	} //while

}

void setup(void) {

	//cli(); //Disable interrupts temoprarily

		//Set prescaler to 1 (16MHz)
			CLKPR = _BV(CLKPCE);
			CLKPR = 0;

		//Timer 0-2 for PWM
			//Configure pins as outputs
			DDRD |= _BV(DDD5) | _BV(DDD6);
			DDRB |= _BV(DDB1) | _BV(DDB2) | _BV(DDB3);

			//Set prescalers to 1/256 of I/O clock
			TCCR0B |= _BV(CS02); //Timer0 Prescaler
			TCCR1B |= _BV(CS12); //Timer1 Prescaler
			TCCR2B |= _BV(CS22) | _BV(CS21); //Timer2 Prescaler

			//Set fast-PWM mode
				//Timer0 PWM settings
				TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01); 
				//Timer1 PWM settings - 8BIT timer mode
				TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
				TCCR1B |= _BV(WGM12);
				//Timer2 PWM settings (only OC2A used as output)
				TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21);
			
			//Enable interrupt for Timer2 overflow and half way (used for LED updates)
				OCR2B = 128; //Half way point
				TIMSK2 |= _BV(TOIE2) | _BV(OCIE2B); //Enable interrupts for overflow and halfway

		//Set inputs for rotary encoder - all inputs with pull-ups
			//PB0/P14 button, PB4/P18 Left. PB5/P19 Right
			PORTB |= _BV(PORTB0) | _BV(PORTB4) | _BV(PORTB5); //Activate pullups
			//Enable interrupts for inputs
			PCICR |= _BV(PCIE2) | _BV(PCIE1); //Interrupts enabled for ports 8-14 & 16-23
			PCMSK2 |= _BV(PCINT19) | _BV(PCINT18); //Interrupts for pin 18 and 19
			PCMSK1 |= _BV(PCINT14); //Interrupts for pin 14

		//Enable watchdog timer -- useful for time-keeping
			MCUSR &= ~(_BV(WDRF)); //Reset WD interrupt
			WDTCSR |= _BV(WDCE) | _BV(WDE); //Unlock WD setting
			WDTCSR = 0x00; //Clear WDE, and set new prescaler to 0-0-0-0, i.e. 16ms
			WDTCSR |= WDIE; //Enable WD interrupt mode
			
		//Set Outputs for shift register
			DDRD |= _BV(DDD0) |	_BV(DDD1) |	_BV(DDD2) |	_BV(DDD3) |	_BV(DDD4);
			PORTD |= _BV(PORTD2); //avoid clear!
			PORTD &= ~(_BV(PORTD4)); //Enable output

		//Disable pin 28 / PC6 by enabling internal pull-up (in input configuration)
			DDRC |= _BV(DDC5); //Currently used as power on signal, as well as diagnostics
			PORTC |= _BV(PORTC5);
		//Disable pin 13 by enabling internal pull-up
			PORTD |= _BV(PORTD7);

		//ADC configuration
			//ADMUX: REFS1 & REFS0 set to 0 as standard, so external AREF pin is used as reference
			ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //Set prescaler to 128 (125 kHz)
			ADCSRA |= _BV(ADEN); //Enable ADC
			ADCSRA |= _BV(ADSC); //Make an empty conversion to initiate ADC
			while(ADCSRA>>ADSC & 1); //Wait until conversion is finished

			//Disable digital inputs on Analog pins
			DIDR0 |= _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D) | _BV(ADC3D) | _BV(ADC4D);

	//sei(); //Enable interrupts again

}

/*
	Startup routine
		Sets all fans to 100% in order to ensure adequate startup power
		Records the fans current consumption at 100% speed
		Stores connection status
*/
void startup(void) {

	//Activate all fans on full speed
	OCR0A = ~(0); //Fan #1
	OCR0B = ~(0); //Fan #2
	OCR1AL = ~(0); //Fan #3
	OCR1BL = ~(0); //Fan #4
	OCR2A = ~(0); //Fan #5

	//Let the fans spin to full speed

	//Blinking status light
	uint8_t time = STARTUPFANWARMINGINDICATORINTERVAL;

	for(int i=0; i<=STARTUPFANWARMINGPERIOD;){

		PORTC ^= _BV(PORTC5);
		_delay_ms(time); 
		i += time;

	}

	//Store connection status
	checkConnections();

	PORTC &= ~(_BV(PORTC5)); //Ensure that the LED is off

	updateInterface();

}


/* ------------------------

[Fan functions]

--------------------------- */


/*
	Helper method to read and return a voltage for a sepcific fan
	Fan channels are recorded in macros FANxCH in .h file for easy reference
*/
uint16_t readFanCurrent(uint8_t chADC) {

	//Adjust analog channel in ADMUX
	switch(chADC) {

		case FAN1CH:
			//ADC0
			ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
			break;
		
		case FAN2CH:
			//ADC1
			ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1)); 
			ADMUX |= _BV(MUX0);
			break;
		
		case FAN3CH:
			//ADC2
			ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX0));
			ADMUX |= _BV(MUX1);
			break;
		
		case FAN4CH:
			//ADC3
			ADMUX &= ~(_BV(MUX3) | _BV(MUX2));
			ADMUX |= _BV(MUX1) | _BV(MUX0);
			break;
		
		case FAN5CH:
			//ADC4
			ADMUX &= ~(_BV(MUX3) | _BV(MUX1) | _BV(MUX0));
			ADMUX |= _BV(MUX2);
			break;

	}

	ADCSRA |=_BV(ADSC); //Starts conversion

	while( ADCSRA>>ADSC & 1 ); //Waits for conversion to finish

	uint16_t out = 0;
	out = ADCH<<sizeof(ADCL); //Move bit 9 & 10 to the left
	out |= ADCL; //Store the lower 8 bits

	return out;

}



/*
	Helper method to record connection status of all fans
	Turns on all unconnected channels and checks for new fan additions
*/
void checkConnections(void) {

	//TODO rewrite these segments to use universal logic

	/*
		----- FAN CHANNEL 1 -----
	*/

		//Check if this output has a newly connected fan
		if((connectedFans>>FAN1CONN & 1) != 0){

			//Check if there is any current draw with output on
			OCR0A = 255; //Turn on fan at full speed
			DDRD |= _BV(DDD5); //Turn on output
			_delay_us(UNCONNECTEDFANSTARTUPTIME); //Wait for output to turn on
			fan1Current = readFanCurrent(FAN1CH);

		} else {

			//TODO: match this with current timer status; otherwise, we might measure with output off!
			fan1Current = readFanCurrent(FAN1CH);
			
		}	

		if( fan1Current < CONNECTIONTHRESHOLD ){

			connectedFans &= ~(_BV(FAN1CONN)); //unset bit
			OCR0A = 0; //Reset timer
			DDRD &= ~(_BV(DDD5)); //Turn off output
			
		}


	/*
		----- FAN CHANNEL 2 -----
	*/

		//Check if this output has a newly connected fan
		if((connectedFans>>FAN2CONN & 1) != 0){

			//Check if there is any current draw with output on
			OCR0B = 255; //Turn on fan at full speed
			DDRD |= _BV(DDD6); //Turn on output
			_delay_us(UNCONNECTEDFANSTARTUPTIME); //Wait for output to turn on
			fan2Current = readFanCurrent(FAN2CH);

		} else {

			//TODO: match this with current timer status; otherwise, we might measure with output off!
			fan2Current = readFanCurrent(FAN2CH);
			
		}	

		if( fan2Current < CONNECTIONTHRESHOLD ){

			connectedFans &= ~(_BV(FAN2CONN)); //unset bit
			OCR0B = 0; //Reset timer
			DDRD &= ~(_BV(DDD6)); //Turn off output
			
		}


	/*
		----- FAN CHANNEL 3 -----
	*/

		//Check if this output has a newly connected fan
		if((connectedFans>>FAN3CONN & 1) != 0){

			//Check if there is any current draw with output on
			OCR1AL = 255; //Turn on fan at full speed
			DDRB |= _BV(DDB1); //Turn on output
			_delay_us(UNCONNECTEDFANSTARTUPTIME); //Wait for output to turn on
			fan3Current = readFanCurrent(FAN3CH);

		} else {

			//TODO: match this with current timer status; otherwise, we might measure with output off!
			fan3Current = readFanCurrent(FAN3CH);
			
		}	

		if( fan3Current < CONNECTIONTHRESHOLD ){

			connectedFans &= ~(_BV(FAN3CONN)); //unset bit
			OCR1AL = 0; //Reset timer
			DDRB &= ~(_BV(DDB1)); //Turn off output
			
		}


	/*
		----- FAN CHANNEL 4 -----
	*/

		//Check if this output has a newly connected fan
		if((connectedFans>>FAN4CONN & 1) != 0){

			//Check if there is any current draw with output on
			OCR1BL = 255; //Turn on fan at full speed
			DDRB |= _BV(DDB2); //Turn on output
			_delay_us(UNCONNECTEDFANSTARTUPTIME); //Wait for output to turn on
			fan4Current = readFanCurrent(FAN4CH);

		} else {

			//TODO: match this with current timer status; otherwise, we might measure with output off!
			fan4Current = readFanCurrent(FAN4CH);
			
		}	

		if( fan4Current < CONNECTIONTHRESHOLD ){

			connectedFans &= ~(_BV(FAN4CONN)); //unset bit
			OCR1BL = 0; //Reset timer
			DDRB &= ~(_BV(DDB2)); //Turn off output
			
		}


	/*
		----- FAN CHANNEL 5 -----
	*/

		//Check if this output has a newly connected fan
		if((connectedFans>>FAN5CONN & 1) != 0){

			//Check if there is any current draw with output on
			OCR2A = 255; //Turn on fan at full speed
			DDRB |= _BV(DDB3); //Turn on output
			_delay_us(UNCONNECTEDFANSTARTUPTIME); //Wait for output to turn on
			fan5Current = readFanCurrent(FAN5CH);

		} else {

			//TODO: match this with current timer status; otherwise, we might measure with output off!
			fan5Current = readFanCurrent(FAN5CH);
			
		}	

		if( fan5Current < CONNECTIONTHRESHOLD ){

			connectedFans &= ~(_BV(FAN5CONN)); //unset bit
			OCR2A = 0; //Reset timer
			DDRB &= ~(_BV(DDB3)); //Turn off output
			
		}

}


/* ------------------------

[LED functions]

--------------------------- */


/*
	Refresh LED's
		Each of the 10 LED's uses 3 channels (RGB)
		Each colour channel is 3 bits long (values ranging from 0-7)

		The logic is optimized to always never leave gaps in when possible, i.e. to maximze brightness
		Therefore, the values in the array does not represent true bit values, 
		but more of relationships between colours: how bright they are in relation to the others.
		//TODO: this will be remedied in the future, to allow for a more common RGB(a,b,c) format

		There is a fourth channel available to dim the LED, if this is required. 
		Writing to this channel will output 0 to the shift register
		//TODO: this should be set automatically by the setColour method in the future
*/
void refreshDisplay(void){

	//Prepare output to display
	uint32_t output = 0;
	uint32_t bitValue = 0;
	uint8_t channel = 0;
	uint8_t channelSearch = 0;

	/*
		Routine for searching for the next colour to display.

		The loop looks looks in the LED buffer sequentially (in sequence RED, GREEN, BLUE, DIMMER).
			If there is a value in any of these positions in the dimmer array, this will be saved 
			as the current output of the specified LED. If the channel DIMMER is chosen, there will 
			be a gap in the output. //TODO: remove dimmer channel?

		Each time the loop uses a value in the buffer, it is decreased by 1 unit. After one colour
			channel is used up, the loop will continue on to the next colour channel. When all
			channels are used up (i.e. the read zero), a new buffer is copied from the 
			LEDColours-array.
	*/
	for( int8_t led=0; led<10; led++ ){

		//find the channel to display if current channel i empty
		if( buffer[led][currentChannel[led]] == 0 ){

			channelSearch = currentChannel[led];

			while(1){

				if( channelSearch >= BLUE ){ //start search from the beginning
					channelSearch = RED;
				} else {
					channelSearch += 1;
				}

				if( buffer[led][channelSearch] > 0){

					//We found a channel with remaining value, set this to the active channel!
					currentChannel[led] = channelSearch;
					break;

				} else if( channelSearch == currentChannel[led] ){

					//nothing to display (we have looped all channels once): copy new value to buffer again
					copyToBuffer(led);
					
					//Set the LED to black until we have new data
					currentChannel[led] = DIMMER;
					break;

				}


			} //while

		}

		//Set the channel to display
		channel = currentChannel[led];

		//Reduce value in buffer if it is a colour channel
		//TODO: this if-check shouldn't be needed?
		if( currentChannel[led] != DIMMER && buffer[led][currentChannel[led]] != 0 ){
			buffer[led][currentChannel[led]] -= 1;
		}

		/*
			Advance to the next colour (avoids flickering).
			This guesses that the next channel contains display data.
			This is checked in the initial loop during the next refresh cycle.
		*/
		if( currentChannel[led] >= BLUE ){
			currentChannel[led] = RED;
		} else {
			currentChannel[led] += 1;
		}

		if(channel != DIMMER){ //push no data if the channel is empty -- already 0 for all LED outputs

			bitValue = 1;

			//These are a bit ugly, but I couldn't figure out how to shift according to a variable value #CNoobProblems

			//Shift to correct colour channel
			for( uint8_t shiftTimes = 2; shiftTimes > channel; shiftTimes-- ){

				//Shift to the correct LED channel
				bitValue <<= 1;

			}

			//Shift to correct LED
			for( uint8_t shiftTimes = 0; shiftTimes < (9 - led); shiftTimes++ ){

				//Shift the output 3 times to the right for each LED (RGB LED)
				bitValue <<= 3; //Shift value to correct position

			}

			output |= bitValue; //Merge the bit with the output

		}

	}

	shiftout(output<<SHIFTREGISTEREMPTYBITS);

}



/*
	Copies LEDColours data into the buffer, which is used for keeping track of screen refresh

	Returns: //TODO: probably won't be needed later?
		0 if no bytes was copied
		>=1 if data was copied
*/
uint8_t copyToBuffer(uint8_t led){

	uint8_t bitsum = LEDColours[led][0] + LEDColours[led][1] + LEDColours[led][2];

	//Don't bother copying anything if there is nothing to copy //TODO this is probably less efficient
	if(bitsum > 0){

		for( uint8_t i = 0; i < 3; i++ ){
			buffer[led][i] = LEDColours[led][i]; //Copy to buffer
		}

	}

	return bitsum;

}



/*
	Method to update the led colours array

	This method is used to trim the values to reasonable limits
	Maximum bit value is set in h file

	//TODO: this should be gamma corrected. How many bits are needed then?
*/
void setColour(uint8_t led, uint8_t redCh, uint8_t greenCh, uint8_t blueCh){

	if( redCh > MAXCHANNELVALUE ){
		redCh = MAXCHANNELVALUE;
	}
	if( greenCh > MAXCHANNELVALUE ){
		greenCh = MAXCHANNELVALUE;
	}
	if( blueCh > MAXCHANNELVALUE ){
		blueCh = MAXCHANNELVALUE;
	}

	//Copy gamma-corrected values to the buffer, along with brightness corrections
	if( redCh > 0 ){
		LEDColours[led][0] = gammaMap[redCh] + REDLEDSHIFT;
	} else {
		LEDColours[led][0] = gammaMap[redCh];
	}

	if( greenCh > 0 ){
		LEDColours[led][1] = gammaMap[greenCh] + GREENLEDSHIFT;
	} else {
		LEDColours[led][1] = gammaMap[greenCh];
	}


	if( blueCh > 0 ){
		LEDColours[led][2] = gammaMap[blueCh] + BLUELEDSHIFT;
	} else {
		LEDColours[led][2] = gammaMap[blueCh];
	}

}
/*
	Quick way to update all ten LEDs to the same colour
*/
void setAllColours(uint8_t redCh, uint8_t greenCh, uint8_t blueCh){

	for(uint8_t i=0; i<10; i++){
		setColour(i, redCh, greenCh, blueCh);
	}

}
/*
	Quick way to update all ten LEDs to the same colour
*/
void setColourType(uint8_t led, uint8_t type[3]){

	setColour(led, type[0], type[1], type[2]);

}


/*
	My own implementation of shift register communicaiton
		There is probably already 100's of examples of this code availble,
		but I wanted to learn...
*/
void shiftout(uint32_t input){

	//PORTD |= _BV(PORTD4); //OE high, Disable output
	PORTD &= ~(_BV(PORTD3)); //RCLK low

	for(uint8_t bit=0; bit<32; bit++){

		PORTD &= ~(_BV(PORTD1)); //SRCLK Low

		PORTD &= ~(_BV(PORTD0)); //Discards old value
		PORTD |= ((input & 1)<<PORTD0);
		input = input>>1; //Discard leftmost bit

		PORTD |= _BV(PORTD1); //SRCLK Rising edge, reading data into registry

	}

	PORTD |= _BV(PORTD3); //RCLK rising edge, loading new values in
	//PORTD &= ~(_BV(PORTD4)); //OE low, Enable output

}


/* ------------------------

[Interface functions]

--------------------------- */

/*
	Parses the current interface situation to the display
*/
void updateInterface(void){

	switch(currentView){

		case VIEWSTART:
			
			//set to black
			setAllColours(0, 0, 0);
			
			if(connectedFans>>FAN1CONN & 1)
				setColourType(LED01, primaryColour);
			if(connectedFans>>FAN2CONN & 1)
				setColourType(LED03, primaryColour);
			if(connectedFans>>FAN3CONN & 1)
				setColourType(LED05, primaryColour);
			if(connectedFans>>FAN4CONN & 1)
				setColourType(LED07, primaryColour);
			if(connectedFans>>FAN5CONN & 1)
				setColourType(LED09, primaryColour);

			break;

		case VIEWSETTINGS:

			//Fan part
			if(connectedFans>>FAN1CONN & 1)
				setColourType(LED01, primaryColour);
			if(connectedFans>>FAN2CONN & 1)
				setColourType(LED02, primaryColour);
			if(connectedFans>>FAN3CONN & 1)
				setColourType(LED03, primaryColour);
			if(connectedFans>>FAN4CONN & 1)
				setColourType(LED04, primaryColour);
			if(connectedFans>>FAN5CONN & 1)
				setColourType(LED05, primaryColour);

			//Gap LED
			setColourType(LED06, noColour);

			//Currentprofile
			if(currentProfile == LPROFILE)
				setColourType(LED07, primaryColour);
			else 
				setColourType(LED07, complementColour);

			if(currentProfile == MPROFILE)
				setColourType(LED07, primaryColour);
			else 
				setColourType(LED07, complementColour);

			if(currentProfile == HPROFILE)
				setColourType(LED07, primaryColour);
			else 
				setColourType(LED07, complementColour);

			//Cursor position

			if(cursorPosition != LED06)
				setColourType(cursorPosition, selectColour);

			break;

		case VIEWSETFAN:

			break;
		case VIEWCOLOURS:

			break;
	}

}



/* ------------------------

[ATMEL Interrupt functions] 

--------------------------- */


//Rotary encoder interrupts
ISR(PCINT1_vect){

}
ISR(PCINT2_vect, ISR_ALIASOF(PCINT1_vect));

//WD timer update
ISR(WDT_vect){
	looptime++;
}

/*
	LED refresh timout:
		When Timer2 overflows, or reaches the half-way point, the display should be updated.

*/
ISR(TIMER2_OVF_vect){

	//TEMP - currently using display as indicator instead. Uncomment below.
	refreshDisplay();
	PORTC ^= _BV(PORTC5); //toggle indicator, physical way to measure the update frequency!

}

ISR(TIMER2_COMPB_vect, ISR_ALIASOF(TIMER2_OVF_vect));