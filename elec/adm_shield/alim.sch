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
LIBS:special
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
LIBS:adm_shield-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 14 24
Title ""
Date "28 feb 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_5 ALIM_BOARD1
U 1 1 54F28D93
P 6100 3400
F 0 "ALIM_BOARD1" V 6050 3400 50  0000 C CNN
F 1 "CONN_5" V 6150 3400 50  0000 C CNN
F 2 "~" H 6100 3400 60  0000 C CNN
F 3 "~" H 6100 3400 60  0000 C CNN
	1    6100 3400
	1    0    0    -1  
$EndComp
Text HLabel 4250 3950 0    60   Input ~ 0
GND
Text HLabel 4250 4100 0    60   Input ~ 0
POW_5V
$Comp
L SW_PUSH SECURITY_SWITCH1
U 1 1 54F28DC0
P 4550 3550
F 0 "SECURITY_SWITCH1" H 4550 3650 50  0000 C CNN
F 1 "SW_PUSH" H 4550 3470 50  0000 C CNN
F 2 "~" H 4550 3550 60  0000 C CNN
F 3 "~" H 4550 3550 60  0000 C CNN
	1    4550 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 POW_BATTERY1
U 1 1 54F28DD3
P 3900 3650
F 0 "POW_BATTERY1" V 3850 3650 40  0000 C CNN
F 1 "CONN_2" V 3950 3650 40  0000 C CNN
F 2 "~" H 3900 3650 60  0000 C CNN
F 3 "~" H 3900 3650 60  0000 C CNN
	1    3900 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 3300 5700 3300
Wire Wire Line
	4950 3300 4950 3550
Wire Wire Line
	4950 3550 4850 3550
Wire Wire Line
	4250 3750 5150 3750
Wire Wire Line
	5150 3750 5150 3400
Wire Wire Line
	5150 3400 5700 3400
Wire Wire Line
	5550 3400 5550 3500
Wire Wire Line
	5550 3500 5700 3500
Connection ~ 5550 3400
Wire Wire Line
	4400 3750 4400 3950
Wire Wire Line
	4400 3950 4250 3950
Connection ~ 4400 3750
Wire Wire Line
	5700 3600 5350 3600
Wire Wire Line
	5350 3600 5350 4100
Wire Wire Line
	5350 4100 4250 4100
$Comp
L CONN_1 ENABLE_ALIM1
U 1 1 54F2D645
P 4100 3200
F 0 "ENABLE_ALIM1" H 4180 3200 40  0000 L CNN
F 1 "CONN_1" H 4100 3255 30  0001 C CNN
F 2 "~" H 4100 3200 60  0000 C CNN
F 3 "~" H 4100 3200 60  0000 C CNN
	1    4100 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 3200 5700 3200
$EndSCHEMATC