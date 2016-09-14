#About this project
This project aims to create a PC fan controller, based on the Arduino / Atmel frameworks.

#Fuse bits

Low:	0xF7
High:	0xD8
Ext:	0x04

#Pins with input/output

*) OCR0A: Fan1PWM
*) OCR0B: Fan2PWM
*) OCR1A: Fan3PWM
*) OCR1B: Fan4PWM
*) OCR2A: Fan5PWM
*) ADC0: FanCurrentSense1
*) ADC1: FanCurrentSense2
*) ADC2: FanCurrentSense3
*) ADC3: FanCurrentSense4
*) ADC4: FanCurrentSense5
*) PD0: SER
*) PD1: SRCLK
*) PD2: SRCLR
*) PD3: RCLK
*) PD4: OE
*) XTAL1: Crystal
*) XTAL2: Crystal
*) PB4: Switch Left
*) PB5: Switch Right
*) PB0: Switch press

##Unconnected pins
*) PC5
*) PD7

#Fuses

CKSEL0: 1
CKSEL1: 1
CKSEL2: 1
CKSEL3: 0

SUT0: 0
SUT1: 1