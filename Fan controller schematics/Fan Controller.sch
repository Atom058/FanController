EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Fan Controller-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title "Fan Controller for PC"
Date "2016-09-14"
Rev "1.2"
Comp "Dahlström Electronics"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328-P IC1
U 1 1 57C31160
P 2900 3900
F 0 "IC1" H 2150 5150 40  0000 L BNN
F 1 "ATMEGA328-P" H 3300 2500 40  0000 L BNN
F 2 "DIL28" H 2900 3900 30  0000 C CIN
F 3 "" H 2900 3900 60  0000 C CNN
	1    2900 3900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 57C31247
P 1750 1850
F 0 "#PWR1" H 1750 1700 50  0001 C CNN
F 1 "+5V" H 1750 1990 50  0000 C CNN
F 2 "" H 1750 1850 60  0000 C CNN
F 3 "" H 1750 1850 60  0000 C CNN
	1    1750 1850
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR2
U 1 1 57C31302
P 1850 5750
F 0 "#PWR2" H 1850 5500 50  0001 C CNN
F 1 "GNDREF" H 1850 5600 50  0000 C CNN
F 2 "" H 1850 5750 60  0000 C CNN
F 3 "" H 1850 5750 60  0000 C CNN
	1    1850 5750
	1    0    0    -1  
$EndComp
$Comp
L ROTARY_ENCODER_SWITCH SW1
U 1 1 57C35CD2
P 8050 3200
F 0 "SW1" H 8050 3460 50  0000 C CNN
F 1 "ROTARY_ENCODER" H 8050 2940 50  0000 C CNN
F 2 "" H 7950 3360 50  0001 C CNN
F 3 "" H 8050 3460 50  0001 C CNN
	1    8050 3200
	1    0    0    -1  
$EndComp
$Sheet
S 4600 5850 1400 800 
U 57D7F099
F0 "Fan control" 60
F1 "Fan control.sch" 60
F2 "Fan1PWM" I L 4600 5950 60 
F3 "Fan2PWM" I L 4600 6100 60 
F4 "Fan3PWM" I L 4600 6250 60 
F5 "Fan4PWM" I L 4600 6400 60 
F6 "Fan5PWM" I L 4600 6550 60 
F7 "Fan1Current" O R 6000 5950 60 
F8 "Fan2Current" O R 6000 6100 60 
F9 "Fan3Current" O R 6000 6250 60 
F10 "Fan4Current" O R 6000 6400 60 
F11 "Fan5Current" O R 6000 6550 60 
$EndSheet
$Sheet
S 5800 1650 1050 900 
U 57D89874
F0 "LED Control" 60
F1 "LED control.sch" 60
F2 "SER" I L 5800 1800 60 
F3 "SRCLK" I L 5800 1950 60 
F4 "SRCLR" I L 5800 2100 60 
F5 "RCLK" I L 5800 2250 60 
F6 "OE" I L 5800 2400 60 
$EndSheet
$Comp
L Crystal Y1
U 1 1 57DAFD1B
P 6250 4000
F 0 "Y1" H 6250 4150 50  0000 C CNN
F 1 "16MHz" H 6250 3850 50  0000 C CNN
F 2 "" H 6250 4000 50  0000 C CNN
F 3 "" H 6250 4000 50  0000 C CNN
	1    6250 4000
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 57DB00C1
P 5900 4350
F 0 "C1" H 5925 4450 50  0000 L CNN
F 1 "22nC" H 5925 4250 50  0000 L CNN
F 2 "" H 5938 4200 50  0000 C CNN
F 3 "" H 5900 4350 50  0000 C CNN
	1    5900 4350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 57DB0741
P 6600 4350
F 0 "C2" H 6625 4450 50  0000 L CNN
F 1 "22nC" H 6625 4250 50  0000 L CNN
F 2 "" H 6638 4200 50  0000 C CNN
F 3 "" H 6600 4350 50  0000 C CNN
	1    6600 4350
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR3
U 1 1 57DB07CE
P 5900 4600
F 0 "#PWR3" H 5900 4350 50  0001 C CNN
F 1 "GNDREF" H 5900 4450 50  0000 C CNN
F 2 "" H 5900 4600 60  0000 C CNN
F 3 "" H 5900 4600 60  0000 C CNN
	1    5900 4600
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR4
U 1 1 57DB0842
P 6600 4600
F 0 "#PWR4" H 6600 4350 50  0001 C CNN
F 1 "GNDREF" H 6600 4450 50  0000 C CNN
F 2 "" H 6600 4600 60  0000 C CNN
F 3 "" H 6600 4600 60  0000 C CNN
	1    6600 4600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 57DBCB8F
P 4000 2450
F 0 "R1" V 4080 2450 50  0000 C CNN
F 1 "1k" V 4000 2450 50  0000 C CNN
F 2 "" V 3930 2450 50  0000 C CNN
F 3 "" H 4000 2450 50  0000 C CNN
	1    4000 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1850 1750 2200
Wire Wire Line
	1750 2200 1750 2800
Wire Wire Line
	1750 2800 1750 3100
Wire Wire Line
	1750 2800 2000 2800
Wire Wire Line
	2000 5000 1850 5000
Wire Wire Line
	1850 5000 1850 5100
Wire Wire Line
	1850 5100 1850 5550
Wire Wire Line
	1850 5550 1850 5750
Wire Wire Line
	2000 5100 1850 5100
Connection ~ 1850 5100
Wire Wire Line
	1750 3100 2000 3100
Connection ~ 1750 2800
Wire Wire Line
	5900 3500 5900 4000
Wire Wire Line
	5900 4000 5900 4200
Wire Wire Line
	5900 4000 6100 4000
Wire Wire Line
	6400 4000 6600 4000
Wire Wire Line
	6600 3400 6600 4000
Wire Wire Line
	6600 4000 6600 4200
Wire Wire Line
	6600 4500 6600 4600
Wire Wire Line
	5900 4500 5900 4600
Wire Wire Line
	5900 3500 3900 3500
Connection ~ 5900 4000
Wire Wire Line
	6600 3400 3900 3400
Connection ~ 6600 4000
Wire Wire Line
	3900 5000 4000 5000
Wire Wire Line
	4000 5000 4000 6550
Wire Wire Line
	4000 6550 4600 6550
Wire Wire Line
	3900 4900 4100 4900
Wire Wire Line
	4100 4900 4100 6400
Wire Wire Line
	4100 6400 4600 6400
Wire Wire Line
	4200 2900 4200 6250
Wire Wire Line
	4200 6250 4600 6250
Wire Wire Line
	4200 2900 3900 2900
Wire Wire Line
	3900 3000 4300 3000
Wire Wire Line
	4300 3000 4300 6100
Wire Wire Line
	4300 6100 4600 6100
Wire Wire Line
	4600 5950 4400 5950
Wire Wire Line
	4400 5950 4400 3100
Wire Wire Line
	4400 3100 3900 3100
Wire Wire Line
	6000 5950 6100 5950
Wire Wire Line
	6100 5950 6100 5350
Wire Wire Line
	6100 5350 4600 5350
Wire Wire Line
	4600 5350 4600 4050
Wire Wire Line
	4600 4050 3900 4050
Wire Wire Line
	3900 3950 4700 3950
Wire Wire Line
	4700 3950 4700 5250
Wire Wire Line
	4700 5250 6200 5250
Wire Wire Line
	6200 5250 6200 6100
Wire Wire Line
	6200 6100 6000 6100
Wire Wire Line
	6000 6250 6300 6250
Wire Wire Line
	6300 6250 6300 5150
Wire Wire Line
	6300 5150 4800 5150
Wire Wire Line
	4800 5150 4800 3850
Wire Wire Line
	4800 3850 3900 3850
Wire Wire Line
	3900 3750 4900 3750
Wire Wire Line
	4900 3750 4900 5050
Wire Wire Line
	4900 5050 6400 5050
Wire Wire Line
	6400 5050 6400 6400
Wire Wire Line
	6400 6400 6000 6400
Wire Wire Line
	6000 6550 6500 6550
Wire Wire Line
	6500 6550 6500 4950
Wire Wire Line
	6500 4950 5000 4950
Wire Wire Line
	5000 4950 5000 3650
Wire Wire Line
	5000 3650 3900 3650
Wire Wire Line
	3900 4400 5200 4400
Wire Wire Line
	5200 4400 5200 1800
Wire Wire Line
	5200 1800 5800 1800
Wire Wire Line
	3900 4500 5300 4500
Wire Wire Line
	5300 4500 5300 1950
Wire Wire Line
	5300 1950 5800 1950
Wire Wire Line
	3900 4600 5400 4600
Wire Wire Line
	5400 4600 5400 2100
Wire Wire Line
	5400 2100 5800 2100
Wire Wire Line
	3900 4700 5500 4700
Wire Wire Line
	5500 4700 5500 2250
Wire Wire Line
	5500 2250 5800 2250
Wire Wire Line
	3900 4800 5600 4800
Wire Wire Line
	5600 4800 5600 2400
Wire Wire Line
	5600 2400 5800 2400
Wire Wire Line
	4500 3100 4500 2800
Wire Wire Line
	4500 2800 3900 2800
Wire Wire Line
	4000 2300 4000 2200
Wire Wire Line
	4000 2200 1750 2200
Connection ~ 1750 2200
Wire Wire Line
	4000 2600 4000 4250
Wire Wire Line
	4000 4250 3900 4250
Wire Wire Line
	3900 4150 4500 4150
Wire Wire Line
	4500 4150 4500 5550
Wire Wire Line
	4500 5550 1850 5550
Connection ~ 1850 5550
Wire Wire Line
	4500 3100 7150 3100
Wire Wire Line
	3900 3300 7750 3300
Wire Wire Line
	3900 3200 7250 3200
$Comp
L GNDREF #PWR?
U 1 1 57D90A53
P 7350 3400
F 0 "#PWR?" H 7350 3150 50  0001 C CNN
F 1 "GNDREF" H 7350 3250 50  0000 C CNN
F 2 "" H 7350 3400 60  0000 C CNN
F 3 "" H 7350 3400 60  0000 C CNN
	1    7350 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3200 7350 3200
Wire Wire Line
	7350 3200 7350 3400
Wire Wire Line
	7250 3200 7250 3100
Wire Wire Line
	7250 3100 7750 3100
$Comp
L GNDREF #PWR?
U 1 1 57D90E03
P 8650 3400
F 0 "#PWR?" H 8650 3150 50  0001 C CNN
F 1 "GNDREF" H 8650 3250 50  0000 C CNN
F 2 "" H 8650 3400 60  0000 C CNN
F 3 "" H 8650 3400 60  0000 C CNN
	1    8650 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 3300 8650 3300
Wire Wire Line
	8650 3300 8650 3400
Wire Wire Line
	7150 3100 7150 2850
Wire Wire Line
	7150 2850 8450 2850
Wire Wire Line
	8450 2850 8450 3100
Wire Wire Line
	8450 3100 8350 3100
$EndSCHEMATC
