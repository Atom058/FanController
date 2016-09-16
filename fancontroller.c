#include <fancontroller.h>

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

uint8_t currentColour = RED;
uint8_t	LEDColours[10][4] = {
		  {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
	}; //Array holding current colour of all LED's, as well as a dimmer channel
uint8_t	buffer[10][4] = {
		  {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
		, {0, 0, 0, 0}
	}; //Array holding current colour of all LED's, used in sweeping the LED's

int main (void) {

	setup();

	startup();

	//Testcolours
	//setColour(1, 5, 1, 2, 0);
	//setColour(2, 0, 0, 0, 0);

	uint32_t shiftBit = 0x80000000;
	shiftout(shiftBit);

	while(1){

		if( (PINB>>PINB4 & 1) != 1 ){
			if( shiftBit>>31 & 1){
				shiftBit = 0x01000000; //Move to other end
			} else{
				shiftBit <<= 1; //Move one to the left
			}
			_delay_ms(DEBOUNCETURN);
		}
		if( (PINB>>PINB5 & 1) != 1 ){
			if( shiftBit>>24 & 1){
				shiftBit = 0x80000000; //Move to other end
			} else{
				shiftBit >>= 1; //Move one to the left
			}
			_delay_ms(DEBOUNCETURN);
		}
		if( (PINB>>PINB0 & 1) != 1 ){
			if( shiftBit>>31 & 1){
				shiftBit = 0x01000000; //Move to end
			} else{
				shiftBit = 0x80000000; //Move to begining
			}
			_delay_ms(DEBOUNCEBUTTON);
		}

		shiftout(shiftBit);

	//Rotary encoder input
	//TODO

	} //while

}

void setup(void) {

	cli(); //Disable interrupts temoprarily

		//Set prescaler to 1 (16MHz)
			CLKPR = _BV(CLKPCE);
			CLKPR = 0;

		//Timer 0-2 for PWM
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
			
		//Set Outputs for shift register
			DDRD |= _BV(DDD0) |	_BV(DDD1) |	_BV(DDD2) |	_BV(DDD3) |	_BV(DDD4);
			PORTD |= _BV(PORTD2); //avoid clear!
			PORTD &= ~(_BV(PORTD4)); //Enable output

		//Disable pin 28 / PC6 by enabling internal pull-up (in input configuration)
			DDRC |= _BV(DDC5); //Currently used as power on signal
			PORTC |= _BV(PORTC5);
		//Disable pin 13 by enabling internal pull-up
			PORTD |= _BV(PORTD7);

		//ADC configuration
			//ADMUX: REFS1 & REFS0 set to 0 as standard, so external AREF pin is used as reference
			ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //Set prescaler to 128 (125 kHz)
			ADCSRA |= _BV(ADEN); //Enable ADC

			//Disable digital inputs on Analog pins
			DIDR0 |= _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D) | _BV(ADC3D) | _BV(ADC4D);

	sei(); //Enable interrupts again

}

/*
	Startup routine
		Sets all fans to 100% in order to ensure adequate startup power
		Records the fans current consumption at 100% speed
		Stores connection status
*/
void startup(void) {

	//Activate all fans on full speed
	OCR0A ^= 0; //Fan #1
	OCR0B ^= 0; //Fan #2
	OCR1A ^= 0; //Fan #3
	OCR1B ^= 0; //Fan #4
	OCR2A ^= 0; //Fan #5

	//Let fans spin to full speed
	_delay_ms(1000); 

	//Read max currents
	fan1CurrentMaxSpeed = readFanCurrent(FAN1CH);
	fan2CurrentMaxSpeed = readFanCurrent(FAN2CH);
	fan3CurrentMaxSpeed = readFanCurrent(FAN3CH);
	fan4CurrentMaxSpeed = readFanCurrent(FAN4CH);
	fan5CurrentMaxSpeed = readFanCurrent(FAN5CH);
	fan1Current = fan1CurrentMaxSpeed;
	fan2Current = fan2CurrentMaxSpeed;
	fan3Current = fan3CurrentMaxSpeed;
	fan4Current = fan4CurrentMaxSpeed;
	fan5Current = fan5CurrentMaxSpeed;

	checkConnection();

}



/*
	Helper method to read all fan currents and store these in variables fanXcurrent
*/
void recordFanCurrents(void) {


}



/*
	Helper method to read and return a voltage for a sepcific fan
	Fan channels are recorded in variables FANxCH in .h file for easy reference
*/
uint16_t readFanCurrent(uint8_t chADC) {

	ADMUX |= chADC;
	ADCSRA |=_BV(ADSC); //Starts conversion

	while( ADCSRA>>ADSC & 1 ); //Waits for conversion to finish

	uint16_t out = 0;
	out = ADCH<<sizeof(ADCL); //Move bit 9 & 10 to the left
	out |= ADCL; //Store the lower 8 bits

	return out;

}



/*
	Helper method to record connection status of all fans
	Uses the current reading of sensor to determine status
*/
void checkConnection(void) {

	if(fan1Current > CONNECTIONTHRESHOLD){
		connectedFans |= _BV(FAN1CONN);
	}

	if(fan2Current > CONNECTIONTHRESHOLD){
		connectedFans |= _BV(FAN2CONN);
	}

	if(fan3Current > CONNECTIONTHRESHOLD){
		connectedFans |= _BV(FAN3CONN);
	}

	if(fan4Current > CONNECTIONTHRESHOLD){
		connectedFans |= _BV(FAN4CONN);
	}

	if(fan5Current > CONNECTIONTHRESHOLD){
		connectedFans |= _BV(FAN5CONN);
	}

}



/*
	LED refresh timout:
		When Timer2 overflows, or reaches the half-way point, the display should be updated.

*/
ISR(TIMER2_OVF_vect){

	//TEMP - use display as indicator instead refreshDisplay();

}

ISR(TIMER2_COMPB_vect, ISR_ALIASOF(TIMER2_OVF_vect));




/*
	Refresh LED's
		Each of the 10 LED's uses 3 channels (RGB)
		Each colour channel is 3 bits long (values ranging from 0-7)

		The logic is optimized to always never leave gaps in when possible, i.e. to maximze brightness
		Therefore, the values in the array does not represent true bit values, 
		but more of relationships between colours: how bright they are in relation to the others.

		There is a fourth channel available to dim the LED, if this is required. 
		Writing to this channel will output 0 to the shift register
*/
void refreshDisplay(void){

	//Prepare output to display
	uint32_t output = 0;
	uint32_t bitValue = 0;
	uint8_t channel = 0;

	for( int led=10; led>0; led-- ){

		//Search for next data point to display
		if( buffer[led][0] > 0 ) {

			buffer[led][0]--; //Reduce count in buffer by one
			channel = 0;

		} else if( buffer[led][1] > 0 ){

			buffer[led][1]--; //Reduce count in buffer by one
			channel = 1;

		} else if( buffer[led][2] > 0 ){

			buffer[led][2]--; //Reduce count in buffer by one
			channel = 2;

		} else if( buffer[led][3] > 0 ){

			buffer[led][3]--; //Reduce count in buffer by one
			channel = 3;

		} else {

			//Copy new buffer data from colour channel - returns false if LEDcolour has no info
			if( copyToBuffer(led) ){

				led++; //redo the current loop

			}

			continue; //Continue with next LED -- the current LED will be updated on the next sequence

		}


		if(channel != 3){ //push no data if the channel is empty -- already 0 for all LED outputs

			bitValue = 1;

			for( uint8_t shiftTimes=2; shiftTimes>channel; shiftTimes-- ){

				//Shift to the correct LED channel
				bitValue <<= 1;

			}

			for( uint8_t shiftTimes=0; shiftTimes<(10-led); shiftTimes++ ){

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

	Returns: 
		0 if no bytes was copied
		>=1 if data was copied
*/
uint8_t copyToBuffer(uint8_t led){

	uint8_t bitsum = LEDColours[led][0] + LEDColours[led][1] + LEDColours[led][2] + LEDColours[led][3];

	if(bitsum > 0){

		//Don't bother copying anything if there is nothing to copy
		for( uint8_t i=0;  i<4; i++ ){
			buffer[led][i] = LEDColours[led][i]; //Copy to buffer
		}

	}

	return bitsum;

}

void setColour(uint8_t led, uint8_t redCh, uint8_t greenCh, uint8_t blueCh, uint8_t dimmerCh){

	if( redCh > 7 ){
		redCh = 7;
	}
	if( greenCh > 7 ){
		greenCh = 7;
	}
	if( blueCh > 7 ){
		blueCh = 7;
	}
	if( dimmerCh > 14 ){
		dimmerCh = 14;
	}

	//Copy values to the buffer
	LEDColours[led][0] = redCh;
	LEDColours[led][1] = greenCh;
	LEDColours[led][2] = blueCh;
	LEDColours[led][3] = dimmerCh;

}


/*
	My own implementation of shift register communicaiton
		There is probably already 100's of examples of this code availble,
		but I wanted to learn...
*/
void shiftout(uint32_t input){

	PORTC ^= _BV(PORTC5); //Test

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