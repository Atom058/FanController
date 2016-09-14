#include <atmelrc.h>


int main (void) {

	setup();

	//startup routine
		

	while(1){

	}

}

void setup(void){

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
			TCCR2A |= _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20) | _BV(WGM21); //Timer2 PWM settings

		//Set inputs for rotary encoder - all inputs with pull-ups
			//PB0 button, PB4 Left. PB5 Right
			PORTB |= _BV(PORTB0) | _BV(PORTB4) | _BV(PORTB5); //Activate pullups
			
		//Set Outputs for shift register
			DDRD |= _BV(DDD0) |	_BV(DDD1) |	_BV(DDD2) |	_BV(DDD3) |	_BV(DDD4);

		//ADC configuration
			//REFS1 & REFS0 set to 0 as standard: external AFEF pin used as reference
			ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //Set prescaler to 128 (125 kHz)
			ADCSRA |= _BV(ADEN); //Enable ADC

			//Disable digital inputs on Analog pins
			DIDR0 |= _BV(ADC0) | _BV(ADC1) | _BV(ADC2) | _BV(ADC3) | _BV(ADC4);



	sei(); //Enable interrupts again

}