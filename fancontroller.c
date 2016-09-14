#include <atmelrc.h>

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
			TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01); //Timer0 PWM settings
			TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10) | _BV(WGM11); //Timer1 PWM settings
			TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21); //Timer2 PWM settings (only OC2A used)

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
			DIDR0 |= _BV(ADC0) | _BV(ADC1) | _BV(ADC2) | _BV(ADC3) | _BV(ADC4);

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

	while( (ADCSR>>_BV(ADSC)) & 1); //Waits for conversion to finish

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