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
Sheet 7 24
Title ""
Date "1 mar 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_3 SERVO_LF1
U 1 1 54F06C2D
P 7100 3500
AR Path="/54F0EBC1/54F06B67/54F06C2D" Ref="SERVO_LF1"  Part="1" 
AR Path="/54F0EBC1/54F1C808/54F06C2D" Ref="SERVO_LF2"  Part="1" 
AR Path="/54F0EBC1/54F1C807/54F06C2D" Ref="SERVO_LF0"  Part="1" 
AR Path="/54F1C80B/54F06B67/54F06C2D" Ref="SERVO_RF1"  Part="1" 
AR Path="/54F1C80B/54F1C808/54F06C2D" Ref="SERVO_RF2"  Part="1" 
AR Path="/54F1C80B/54F1C807/54F06C2D" Ref="SERVO_RF0"  Part="1" 
AR Path="/54F1C80A/54F06B67/54F06C2D" Ref="SERVO_LB1"  Part="1" 
AR Path="/54F1C80A/54F1C808/54F06C2D" Ref="SERVO_LB2"  Part="1" 
AR Path="/54F1C80A/54F1C807/54F06C2D" Ref="SERVO_LB0"  Part="1" 
AR Path="/54F1C809/54F06B67/54F06C2D" Ref="SERVO_RB1"  Part="1" 
AR Path="/54F1C809/54F1C808/54F06C2D" Ref="SERVO_RB2"  Part="1" 
AR Path="/54F1C809/54F1C807/54F06C2D" Ref="SERVO_RB0"  Part="1" 
F 0 "SERVO_RF1" V 7050 3500 50  0000 C CNN
F 1 "CONN_3" V 7150 3500 40  0000 C CNN
F 2 "" H 7100 3500 60  0000 C CNN
F 3 "" H 7100 3500 60  0000 C CNN
	1    7100 3500
	1    0    0    -1  
$EndComp
Text HLabel 5250 3100 0    60   Input ~ 0
GND
Text HLabel 5250 3500 0    60   Input ~ 0
POW_5V
Text HLabel 5250 3900 0    60   Input ~ 0
PWM
Wire Wire Line
	5250 3900 6750 3900
Wire Wire Line
	6750 3900 6750 3600
Wire Wire Line
	6750 3400 6750 3100
Wire Wire Line
	6750 3100 5250 3100
Wire Wire Line
	5250 3500 6750 3500
$EndSCHEMATC
