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
Rev "1.3"
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
L +5V #PWR2
U 1 1 57C31247
P 1750 1850
F 0 "#PWR2" H 1750 1700 50  0001 C CNN
F 1 "+5V" H 1750 1990 50  0000 C CNN
F 2 "" H 1750 1850 60  0000 C CNN
F 3 "" H 1750 1850 60  0000 C CNN
	1    1750 1850
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR3
U 1 1 57C31302
P 1850 5750
F 0 "#PWR3" H 1850 5500 50  0001 C CNN
F 1 "GNDREF" H 1850 5600 50  0000 C CNN
F 2 "" H 1850 5750 60  0000 C CNN
F 3 "" H 1850 5750 60  0000 C CNN
	1    1850 5750
	1    0    0    -1  
$EndComp
$Comp
L ROTARY_ENCODER_SWITCH SW1
U 1 1 57C35CD2
P 8150 3200
F 0 "SW1" H 8150 3460 50  0000 C CNN
F 1 "ROTARY_ENCODER" H 8150 2940 50  0000 C CNN
F 2 "" H 8050 3360 50  0001 C CNN
F 3 "" H 8150 3460 50  0001 C CNN
	1    8150 3200
	1    0    0    -1  
$EndComp
$Sheet
S 4700 5850 1400 800 
U 57D7F099
F0 "Fan control" 60
F1 "Fan control.sch" 60
F2 "Fan1PWM" I L 4700 5950 60 
F3 "Fan2PWM" I L 4700 6100 60 
F4 "Fan3PWM" I L 4700 6250 60 
F5 "Fan4PWM" I L 4700 6400 60 
F6 "Fan5PWM" I L 4700 6550 60 
F7 "Fan1Current" O R 6100 5950 60 
F8 "Fan2Current" O R 6100 6100 60 
F9 "Fan3Current" O R 6100 6250 60 
F10 "Fan4Current" O R 6100 6400 60 
F11 "Fan5Current" O R 6100 6550 60 
$EndSheet
$Sheet
S 5900 1650 1050 900 
U 57D89874
F0 "LED Control" 60
F1 "LED control.sch" 60
F2 "SER" I L 5900 1800 60 
F3 "SRCLK" I L 5900 1950 60 
F4 "SRCLR" I L 5900 2100 60 
F5 "RCLK" I L 5900 2250 60 
F6 "OE" I L 5900 2400 60 
$EndSheet
$Comp
L Crystal Y1
U 1 1 57DAFD1B
P 6350 4000
F 0 "Y1" H 6350 4150 50  0000 C CNN
F 1 "16MHz" H 6350 3850 50  0000 C CNN
F 2 "" H 6350 4000 50  0000 C CNN
F 3 "" H 6350 4000 50  0000 C CNN
	1    6350 4000
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 57DB00C1
P 6000 4350
F 0 "C3" H 6025 4450 50  0000 L CNN
F 1 "22pC" H 6025 4250 50  0000 L CNN
F 2 "" H 6038 4200 50  0000 C CNN
F 3 "" H 6000 4350 50  0000 C CNN
	1    6000 4350
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 57DB0741
P 6700 4350
F 0 "C4" H 6725 4450 50  0000 L CNN
F 1 "22pC" H 6725 4250 50  0000 L CNN
F 2 "" H 6738 4200 50  0000 C CNN
F 3 "" H 6700 4350 50  0000 C CNN
	1    6700 4350
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR4
U 1 1 57DB07CE
P 6000 4600
F 0 "#PWR4" H 6000 4350 50  0001 C CNN
F 1 "GNDREF" H 6000 4450 50  0000 C CNN
F 2 "" H 6000 4600 60  0000 C CNN
F 3 "" H 6000 4600 60  0000 C CNN
	1    6000 4600
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR5
U 1 1 57DB0842
P 6700 4600
F 0 "#PWR5" H 6700 4350 50  0001 C CNN
F 1 "GNDREF" H 6700 4450 50  0000 C CNN
F 2 "" H 6700 4600 60  0000 C CNN
F 3 "" H 6700 4600 60  0000 C CNN
	1    6700 4600
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 57DBCB8F
P 4100 2450
F 0 "R2" V 4180 2450 50  0000 C CNN
F 1 "1k" V 4100 2450 50  0000 C CNN
F 2 "" V 4030 2450 50  0000 C CNN
F 3 "" H 4100 2450 50  0000 C CNN
	1    4100 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2800 2000 2800
Wire Wire Line
	1850 5000 2000 5000
Wire Wire Line
	1850 4000 1850 5750
Wire Wire Line
	2000 5100 1850 5100
Connection ~ 1850 5100
Wire Wire Line
	850  3100 2000 3100
Wire Wire Line
	6000 3500 6000 4200
Wire Wire Line
	6000 4000 6200 4000
Wire Wire Line
	6500 4000 6700 4000
Wire Wire Line
	6700 3400 6700 4200
Wire Wire Line
	6700 4500 6700 4600
Wire Wire Line
	6000 4500 6000 4600
Wire Wire Line
	6000 3500 3900 3500
Connection ~ 6000 4000
Wire Wire Line
	6700 3400 3900 3400
Connection ~ 6700 4000
Wire Wire Line
	3900 5000 4100 5000
Wire Wire Line
	4100 5000 4100 6550
Wire Wire Line
	4100 6550 4700 6550
Wire Wire Line
	3900 4900 4200 4900
Wire Wire Line
	4200 4900 4200 6400
Wire Wire Line
	4200 6400 4700 6400
Wire Wire Line
	4300 2900 4300 6250
Wire Wire Line
	4300 6250 4700 6250
Wire Wire Line
	4300 2900 3900 2900
Wire Wire Line
	3900 3000 4400 3000
Wire Wire Line
	4400 3000 4400 6100
Wire Wire Line
	4400 6100 4700 6100
Wire Wire Line
	4700 5950 4500 5950
Wire Wire Line
	4500 5950 4500 3100
Wire Wire Line
	4500 3100 3900 3100
Wire Wire Line
	6100 5950 6200 5950
Wire Wire Line
	6200 5950 6200 5350
Wire Wire Line
	6200 5350 4700 5350
Wire Wire Line
	4700 5350 4700 4050
Wire Wire Line
	4700 4050 3900 4050
Wire Wire Line
	3900 3950 4800 3950
Wire Wire Line
	4800 3950 4800 5250
Wire Wire Line
	4800 5250 6300 5250
Wire Wire Line
	6300 5250 6300 6100
Wire Wire Line
	6300 6100 6100 6100
Wire Wire Line
	6100 6250 6400 6250
Wire Wire Line
	6400 6250 6400 5150
Wire Wire Line
	6400 5150 4900 5150
Wire Wire Line
	4900 5150 4900 3850
Wire Wire Line
	4900 3850 3900 3850
Wire Wire Line
	3900 3750 5000 3750
Wire Wire Line
	5000 3750 5000 5050
Wire Wire Line
	5000 5050 6500 5050
Wire Wire Line
	6500 5050 6500 6400
Wire Wire Line
	6500 6400 6100 6400
Wire Wire Line
	6100 6550 6600 6550
Wire Wire Line
	6600 6550 6600 4950
Wire Wire Line
	6600 4950 5100 4950
Wire Wire Line
	5100 4950 5100 3650
Wire Wire Line
	5100 3650 3900 3650
Wire Wire Line
	3900 4400 5300 4400
Wire Wire Line
	5300 4400 5300 1800
Wire Wire Line
	5300 1800 5900 1800
Wire Wire Line
	3900 4500 5400 4500
Wire Wire Line
	5400 4500 5400 1950
Wire Wire Line
	5400 1950 5900 1950
Wire Wire Line
	3900 4600 5500 4600
Wire Wire Line
	5500 4600 5500 2100
Wire Wire Line
	5500 2100 5900 2100
Wire Wire Line
	3900 4700 5600 4700
Wire Wire Line
	5600 4700 5600 2250
Wire Wire Line
	5600 2250 5900 2250
Wire Wire Line
	3900 4800 5700 4800
Wire Wire Line
	5700 4800 5700 2400
Wire Wire Line
	5700 2400 5900 2400
Wire Wire Line
	4600 3100 4600 2800
Wire Wire Line
	4600 2800 3900 2800
Wire Wire Line
	4100 2200 4100 2300
Wire Wire Line
	850  2200 4100 2200
Connection ~ 1750 2200
Wire Wire Line
	4100 2600 4100 4250
Wire Wire Line
	4100 4250 3900 4250
Wire Wire Line
	4600 3100 7250 3100
Wire Wire Line
	3900 3300 7850 3300
Wire Wire Line
	3900 3200 7350 3200
$Comp
L GNDREF #PWR6
U 1 1 57D90A53
P 7450 3400
F 0 "#PWR6" H 7450 3150 50  0001 C CNN
F 1 "GNDREF" H 7450 3250 50  0000 C CNN
F 2 "" H 7450 3400 60  0000 C CNN
F 3 "" H 7450 3400 60  0000 C CNN
	1    7450 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 3200 7450 3200
Wire Wire Line
	7450 3200 7450 3400
Wire Wire Line
	7350 3200 7350 3100
Wire Wire Line
	7350 3100 7850 3100
$Comp
L GNDREF #PWR7
U 1 1 57D90E03
P 8750 3400
F 0 "#PWR7" H 8750 3150 50  0001 C CNN
F 1 "GNDREF" H 8750 3250 50  0000 C CNN
F 2 "" H 8750 3400 60  0000 C CNN
F 3 "" H 8750 3400 60  0000 C CNN
	1    8750 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 3300 8750 3300
Wire Wire Line
	8750 3300 8750 3400
Wire Wire Line
	7250 3100 7250 2850
Wire Wire Line
	7250 2850 8550 2850
Wire Wire Line
	8550 2850 8550 3100
Wire Wire Line
	8550 3100 8450 3100
$Comp
L INDUCTOR_SMALL L1
U 1 1 57D9448B
P 850 2600
F 0 "L1" H 850 2700 50  0000 C CNN
F 1 "10µH" H 850 2550 50  0000 C CNN
F 2 "" H 850 2600 50  0000 C CNN
F 3 "" H 850 2600 50  0000 C CNN
	1    850  2600
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 57D94589
P 850 3450
F 0 "C1" H 875 3550 50  0000 L CNN
F 1 "100nF" H 875 3350 50  0000 L CNN
F 2 "" H 888 3300 50  0000 C CNN
F 3 "" H 850 3450 50  0000 C CNN
	1    850  3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  2850 850  3300
Connection ~ 850  3100
Wire Wire Line
	850  2350 850  2200
Wire Wire Line
	1750 1850 1750 2800
$Comp
L GNDREF #PWR1
U 1 1 57D95279
P 850 3700
F 0 "#PWR1" H 850 3450 50  0001 C CNN
F 1 "GNDREF" H 850 3550 50  0000 C CNN
F 2 "" H 850 3700 60  0000 C CNN
F 3 "" H 850 3700 60  0000 C CNN
	1    850  3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  3600 850  3700
$Comp
L LM385-1.25 U1
U 1 1 57D96471
P 800 4250
F 0 "U1" V 1000 4000 60  0000 C CNN
F 1 "LM385-1.25" V 550 4100 60  0000 C CNN
F 2 "" H 800 4250 60  0001 C CNN
F 3 "" H 800 4250 60  0001 C CNN
	1    800  4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1350 4250 1850 4250
Connection ~ 1850 5000
$Comp
L R R1
U 1 1 57D96D6B
P 1450 2700
F 0 "R1" V 1530 2700 50  0000 C CNN
F 1 "47k" V 1450 2700 50  0000 C CNN
F 2 "" V 1380 2700 50  0000 C CNN
F 3 "" H 1450 2700 50  0000 C CNN
	1    1450 2700
	1    0    0    -1  
$EndComp
Connection ~ 1450 2200
Wire Wire Line
	1450 4150 1350 4150
Wire Wire Line
	1450 3400 2000 3400
Connection ~ 1450 3400
$Comp
L C C2
U 1 1 57D9A64A
P 1850 3850
F 0 "C2" H 1875 3950 50  0000 L CNN
F 1 "100nF" H 1875 3750 50  0000 L CNN
F 2 "" H 1888 3700 50  0000 C CNN
F 3 "" H 1850 3850 50  0000 C CNN
	1    1850 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2200 1450 2550
Wire Wire Line
	1450 2850 1450 4150
Wire Wire Line
	1850 3700 1850 3400
Connection ~ 1850 3400
Connection ~ 1850 4250
NoConn ~ 3900 5100
NoConn ~ 3900 4150
NoConn ~ 1350 4350
$EndSCHEMATC
