#include <atmelrc.h>


int main (void) {

	setup();

	while(1){

	}

}

void setup(void){

	cli(); //Disable interrupts temoprarily


	sei(); //Enable interrupts again

}