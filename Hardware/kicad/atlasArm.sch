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
LIBS:arduino
LIBS:sphParts
LIBS:switches
LIBS:Arduino_Nano-cache
LIBS:atlasArm-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L arduino_mini U?
U 1 1 597D2A45
P 5600 3050
F 0 "U?" H 6100 2100 70  0000 C CNN
F 1 "arduino_nano" H 6350 2000 70  0000 C CNN
F 2 "DIL20" H 5600 3000 60  0000 C CNN
F 3 "" H 5600 3050 60  0001 C CNN
	1    5600 3050
	1    0    0    -1  
$EndComp
$Comp
L 5WaySwitch U?
U 1 1 597E62E6
P 8250 2250
F 0 "U?" H 8350 2550 60  0000 C CNN
F 1 "5WaySwitch" H 8250 2450 60  0000 C CNN
F 2 "" H 8250 2250 60  0001 C CNN
F 3 "" H 8250 2250 60  0001 C CNN
	1    8250 2250
	1    0    0    -1  
$EndComp
$Comp
L 128x32_I2C_OLED U?
U 1 1 597E6A0E
P 2450 2200
F 0 "U?" H 3050 2450 60  0000 C CNN
F 1 "128x32_I2C_OLED" H 2450 2600 60  0000 C CNN
F 2 "" H 2450 2200 60  0001 C CNN
F 3 "" H 2450 2200 60  0001 C CNN
	1    2450 2200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X11 P?
U 1 1 597E6B10
P 6150 6000
F 0 "P?" H 6150 6600 50  0000 C CNN
F 1 "CONN_01X11" V 6250 6000 50  0000 C CNN
F 2 "" H 6150 6000 50  0000 C CNN
F 3 "" H 6150 6000 50  0000 C CNN
	1    6150 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 3250 4000 5300
Wire Wire Line
	5650 5300 5650 5800
Wire Wire Line
	1950 3250 4900 3250
Wire Wire Line
	2150 3350 4900 3350
Wire Wire Line
	4100 3350 4100 5200
Wire Wire Line
	4100 5200 5750 5200
Wire Wire Line
	5750 5200 5750 5800
Wire Wire Line
	4900 3450 4200 3450
Wire Wire Line
	4200 3450 4200 5100
Wire Wire Line
	4200 5100 5850 5100
Wire Wire Line
	5850 5100 5850 5800
Wire Wire Line
	6300 3350 6800 3350
Wire Wire Line
	5950 5100 5950 5800
Wire Wire Line
	5950 5100 6800 5100
Wire Wire Line
	6800 5100 6800 3350
Wire Wire Line
	6300 3550 6700 3550
Wire Wire Line
	6700 3550 6700 5200
Wire Wire Line
	6700 5200 6050 5200
Wire Wire Line
	6050 5200 6050 5800
$Comp
L +12V #PWR?
U 1 1 598F1509
P 6650 5800
F 0 "#PWR?" H 6650 5650 50  0001 C CNN
F 1 "+12V" H 6650 5940 50  0000 C CNN
F 2 "" H 6650 5800 50  0000 C CNN
F 3 "" H 6650 5800 50  0000 C CNN
	1    6650 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 598F1529
P 6450 5800
F 0 "#PWR?" H 6450 5550 50  0001 C CNN
F 1 "GND" H 6450 5650 50  0000 C CNN
F 2 "" H 6450 5800 50  0000 C CNN
F 3 "" H 6450 5800 50  0000 C CNN
	1    6450 5800
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR?
U 1 1 598F1549
P 6550 5600
F 0 "#PWR?" H 6550 5450 50  0001 C CNN
F 1 "+5V" H 6550 5740 50  0000 C CNN
F 2 "" H 6550 5600 50  0000 C CNN
F 3 "" H 6550 5600 50  0000 C CNN
	1    6550 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5600 6550 5800
$Comp
L emgSensor U?
U 1 1 598F16B6
P 8200 5300
F 0 "U?" H 7500 5750 60  0000 C CNN
F 1 "emgSensor" H 8200 5900 60  0000 C CNN
F 2 "" H 9000 4750 60  0001 C CNN
F 3 "" H 9000 4750 60  0001 C CNN
	1    8200 5300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 598F171A
P 9100 4950
F 0 "#PWR?" H 9100 4800 50  0001 C CNN
F 1 "+5V" H 9100 5090 50  0000 C CNN
F 2 "" H 9100 4950 50  0000 C CNN
F 3 "" H 9100 4950 50  0000 C CNN
	1    9100 4950
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 598F173D
P 9300 5050
F 0 "#PWR?" H 9300 4800 50  0001 C CNN
F 1 "GND" H 9300 4900 50  0000 C CNN
F 2 "" H 9300 5050 50  0000 C CNN
F 3 "" H 9300 5050 50  0000 C CNN
	1    9300 5050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9100 5050 9300 5050
Text GLabel 4900 3550 0    60   Input ~ 0
emgSignal
Text GLabel 9600 5150 2    60   Input ~ 0
emgSignal
Wire Wire Line
	9100 5150 9600 5150
Text GLabel 6150 5800 1    60   Input ~ 0
R
Text GLabel 6250 5650 1    60   Input ~ 0
E
Text GLabel 6350 5500 1    60   Input ~ 0
M
Wire Wire Line
	6250 5650 6250 5800
Wire Wire Line
	6350 5500 6350 5800
Text GLabel 8400 5500 3    60   Input ~ 0
R
Text GLabel 8500 5650 3    60   Input ~ 0
E
Text GLabel 8600 5800 3    60   Input ~ 0
M
Wire Wire Line
	8500 5650 8500 5500
Wire Wire Line
	8600 5500 8600 5800
Wire Wire Line
	1950 3250 1950 2700
Connection ~ 4000 3250
Wire Wire Line
	2150 3350 2150 2700
Connection ~ 4100 3350
$Comp
L GND #PWR?
U 1 1 598F1CAC
P 5600 4600
F 0 "#PWR?" H 5600 4350 50  0001 C CNN
F 1 "GND" H 5600 4450 50  0000 C CNN
F 2 "" H 5600 4600 50  0000 C CNN
F 3 "" H 5600 4600 50  0000 C CNN
	1    5600 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 598F1CCF
P 2550 2700
F 0 "#PWR?" H 2550 2450 50  0001 C CNN
F 1 "GND" H 2550 2550 50  0000 C CNN
F 2 "" H 2550 2700 50  0000 C CNN
F 3 "" H 2550 2700 50  0000 C CNN
	1    2550 2700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 598F1D06
P 2950 2700
F 0 "#PWR?" H 2950 2550 50  0001 C CNN
F 1 "+5V" H 2950 2840 50  0000 C CNN
F 2 "" H 2950 2700 50  0000 C CNN
F 3 "" H 2950 2700 50  0000 C CNN
	1    2950 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 2700 2350 4350
Wire Wire Line
	2350 4350 4900 4350
$Comp
L R R?
U 1 1 598F1DAD
P 7150 3600
F 0 "R?" V 7230 3600 50  0000 C CNN
F 1 "R" V 7150 3600 50  0000 C CNN
F 2 "" V 7080 3600 50  0000 C CNN
F 3 "" H 7150 3600 50  0000 C CNN
	1    7150 3600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 598F1E4F
P 7550 3250
F 0 "R?" V 7630 3250 50  0000 C CNN
F 1 "R" V 7550 3250 50  0000 C CNN
F 2 "" V 7480 3250 50  0000 C CNN
F 3 "" H 7550 3250 50  0000 C CNN
	1    7550 3250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 598F1E77
P 7350 3400
F 0 "R?" V 7430 3400 50  0000 C CNN
F 1 "R" V 7350 3400 50  0000 C CNN
F 2 "" V 7280 3400 50  0000 C CNN
F 3 "" H 7350 3400 50  0000 C CNN
	1    7350 3400
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 598F1EA3
P 7750 3100
F 0 "R?" V 7830 3100 50  0000 C CNN
F 1 "R" V 7750 3100 50  0000 C CNN
F 2 "" V 7680 3100 50  0000 C CNN
F 3 "" H 7750 3100 50  0000 C CNN
	1    7750 3100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 598F1EF7
P 7950 2950
F 0 "R?" V 8030 2950 50  0000 C CNN
F 1 "R" V 7950 2950 50  0000 C CNN
F 2 "" V 7880 2950 50  0000 C CNN
F 3 "" H 7950 2950 50  0000 C CNN
	1    7950 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 598F1F40
P 8100 3900
F 0 "#PWR?" H 8100 3650 50  0001 C CNN
F 1 "GND" H 8100 3750 50  0000 C CNN
F 2 "" H 8100 3900 50  0000 C CNN
F 3 "" H 8100 3900 50  0000 C CNN
	1    8100 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3750 8100 3750
Wire Wire Line
	8100 3750 8100 3900
Wire Wire Line
	7950 3100 7950 3750
Connection ~ 7950 3750
Wire Wire Line
	7750 3250 7750 3750
Connection ~ 7750 3750
Wire Wire Line
	7350 3550 7350 3750
Connection ~ 7350 3750
Wire Wire Line
	7550 3400 7550 3750
Connection ~ 7550 3750
$Comp
L +5V #PWR?
U 1 1 598F211A
P 8700 2450
F 0 "#PWR?" H 8700 2300 50  0001 C CNN
F 1 "+5V" H 8700 2590 50  0000 C CNN
F 2 "" H 8700 2450 50  0000 C CNN
F 3 "" H 8700 2450 50  0000 C CNN
	1    8700 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	8700 2450 8700 2450
Wire Wire Line
	8700 2150 9150 2150
Wire Wire Line
	9150 2800 9150 2150
Wire Wire Line
	6300 2800 9150 2800
Wire Wire Line
	7150 2150 7800 2150
Wire Wire Line
	6300 3450 7150 3450
Connection ~ 7150 3450
Wire Wire Line
	7550 3000 6300 3000
Wire Wire Line
	7550 2300 7550 3100
Wire Wire Line
	7550 2300 7800 2300
Connection ~ 7550 3000
Wire Wire Line
	6300 3100 7350 3100
Wire Wire Line
	7350 2450 7350 3250
Wire Wire Line
	7350 2450 7800 2450
Connection ~ 7350 3100
Wire Wire Line
	6300 2900 7750 2900
Wire Wire Line
	7750 2700 7750 2950
Wire Wire Line
	7750 2700 9050 2700
Wire Wire Line
	9050 2700 9050 2300
Wire Wire Line
	9050 2300 8700 2300
Wire Wire Line
	7150 3450 7150 2150
Connection ~ 7950 2800
Connection ~ 7750 2900
Connection ~ 7150 3750
Wire Wire Line
	4000 5300 5650 5300
$Comp
L +5V #PWR?
U 1 1 598F31E1
P 5600 1900
F 0 "#PWR?" H 5600 1750 50  0001 C CNN
F 1 "+5V" H 5600 2040 50  0000 C CNN
F 2 "" H 5600 1900 50  0000 C CNN
F 3 "" H 5600 1900 50  0000 C CNN
	1    5600 1900
	1    0    0    -1  
$EndComp
Text Notes 7350 7500 0    60   ~ 0
Core Module
Text Notes 10550 7650 0    60   ~ 0
V5.01
Text Notes 8150 7650 0    60   ~ 0
8-12-17
$EndSCHEMATC
