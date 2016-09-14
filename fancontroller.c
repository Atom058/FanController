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
	}; //Array holding current colour for LED01

uint8_t refreshCount = 0; //PWM counter for LEDs

int main (void) {

	setup();

	startup();	

	while(1){


	}

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
				TIMSK2 |= _BV(TOIE2) | _BV(OCIE2B); //Enable interrupts

		//Set inputs for rotary encoder - all inputs with pull-ups
			//PB0 button, PB4 Left. PB5 Right
			PORTB |= _BV(PORTB0) | _BV(PORTB4) | _BV(PORTB5); //Activate pullups
			
		//Set Outputs for shift register
			DDRD |= _BV(DDD0) |	_BV(DDD1) |	_BV(DDD2) |	_BV(DDD3) |	_BV(DDD4);

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
	FAN1PWM ^= 0;
	FAN2PWM ^= 0;
	FAN3PWM ^= 0;
	FAN4PWM ^= 0;
	FAN5PWM ^= 0;

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
	out = ADCH<<sizeof(ADCL);
	out |= ADCL;

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

	refreshDisplay();

}
ISR(TIMER2_COMPB_vect, ISR_ALIASOF(TIMER2_OVF_vect));




/*
	Refresh LED's
		Each of the 10 LED's uses 3 channels (RGB)
		Each colour channel is 8 bits long
*/
void refreshDisplay(void){

	//Prepare output to display
	uint32_t output = 0;

	//For each LED, compare the value of the current colour with the refresh count
	for( int led=0; led<10; led++ ){

		if( LEDColours[led][currentColour] > refreshCount ){
			output |= _BV(currentColour)<<(led*3); //Shift value to correct position
		}

	}

	//Shift the output to the LED's
	shiftout(output<<SHIFTREGISTEREMPTYBITS);

	//Increment colours/counter
	currentColour++;
	if( currentColour > BLUE) {
		currentColour = RED;

		refreshCount++; //PWM counter for LEDs
		//counter resets automatically when it reaches 255 + 1
	}

}



/*
	My own implementation of shift register communicaiton
		There is probably already 100's of examples of this code availble,
		but I wanted to learn...
*/
void shiftout(uint32_t input){

	
	
}