EESchema Schematic File Version 1
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./SD-card-reader.cache
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "SD-card-reader"
Date "29 nov 2008"
Rev "1.0"
Comp "AATG"
Comment1 "Ace High"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 6100 5450
Wire Wire Line
	6100 5600 6100 3850
Wire Wire Line
	6100 3850 6200 3850
Wire Wire Line
	4700 6000 4700 6100
Wire Wire Line
	4700 5450 4900 5450
Connection ~ 5300 6100
Wire Wire Line
	6100 5450 5700 5450
Wire Wire Line
	800  850  800  750 
Wire Wire Line
	5700 2150 5500 2150
Wire Wire Line
	5500 2150 5500 2450
Wire Wire Line
	5500 2450 5850 2450
Wire Wire Line
	5850 2450 5850 4150
Wire Wire Line
	5850 4150 6200 4150
Wire Wire Line
	6700 2750 4650 2750
Wire Wire Line
	6700 2750 6700 2050
Wire Wire Line
	6700 2050 6500 2050
Wire Wire Line
	4650 2750 4650 2900
Wire Wire Line
	5650 4700 5650 3750
Wire Wire Line
	5250 3400 5250 4200
Wire Wire Line
	4650 3400 4650 4200
Wire Wire Line
	4950 4550 4950 4700
Connection ~ 5650 4050
Wire Wire Line
	6200 4050 5650 4050
Wire Wire Line
	6200 3950 5450 3950
Wire Wire Line
	5450 3950 5450 3750
Connection ~ 4950 3750
Wire Wire Line
	5450 3750 4950 3750
Wire Wire Line
	6200 3650 4650 3650
Connection ~ 4650 3650
Wire Wire Line
	5650 3750 6200 3750
Wire Wire Line
	5250 4700 5250 4550
Wire Wire Line
	4650 4700 4650 4550
Wire Wire Line
	4950 3400 4950 4200
Wire Wire Line
	6200 3550 5250 3550
Connection ~ 5250 3550
Wire Wire Line
	6500 2150 6600 2150
Wire Wire Line
	6600 2150 6600 2650
Wire Wire Line
	6600 2650 4950 2650
Wire Wire Line
	4950 2650 4950 2900
Wire Wire Line
	5700 2050 5250 2050
Wire Wire Line
	5250 2050 5250 2900
Wire Wire Line
	5700 2250 5600 2250
Wire Wire Line
	5600 2250 5600 2350
Wire Wire Line
	6850 2150 6850 2250
Wire Wire Line
	6850 2250 6500 2250
Wire Wire Line
	1100 850  1100 1000
Wire Wire Line
	5300 5950 5300 6250
Wire Wire Line
	6100 6000 6100 6100
Wire Wire Line
	4700 5600 4700 5350
Connection ~ 4700 5450
Wire Wire Line
	6100 6100 4700 6100
$Comp
L LM317 U?
U 1 1 4931B25A
P 5300 5600
F 0 "U?" H 5300 5900 60  0000 C C
F 1 "LD1086V33" H 5350 5350 60  0000 L C
	1    5300 5600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG?
U 1 1 4931B1F2
P 800 850
F 0 "#FLG?" H 800 1120 30  0001 C C
F 1 "PWR_FLAG" H 800 1080 30  0000 C C
	1    800  850 
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG?
U 1 1 4931B1EE
P 1100 850
F 0 "#FLG?" H 1100 1120 30  0001 C C
F 1 "PWR_FLAG" H 1100 1080 30  0000 C C
	1    1100 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4931B1E6
P 1100 1000
F 0 "#PWR?" H 1100 1000 30  0001 C C
F 1 "GND" H 1100 930 30  0001 C C
	1    1100 1000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 4931B1E3
P 800 750
F 0 "#PWR?" H 800 850 30  0001 C C
F 1 "VCC" H 800 850 30  0000 C C
	1    800  750 
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 4931B1A2
P 6850 2150
F 0 "#PWR?" H 6850 2250 30  0001 C C
F 1 "VCC" H 6850 2250 30  0000 C C
	1    6850 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4931B19C
P 5600 2350
F 0 "#PWR?" H 5600 2350 30  0001 C C
F 1 "GND" H 5600 2280 30  0001 C C
	1    5600 2350
	1    0    0    -1  
$EndComp
NoConn ~ 5700 1950
NoConn ~ 5700 1850
NoConn ~ 6500 1850
NoConn ~ 6500 1950
$Comp
L GND #PWR?
U 1 1 4931AFBA
P 5650 4700
F 0 "#PWR?" H 5650 4700 30  0001 C C
F 1 "GND" H 5650 4630 30  0001 C C
	1    5650 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4931AFB5
P 5250 4700
F 0 "#PWR?" H 5250 4700 30  0001 C C
F 1 "GND" H 5250 4630 30  0001 C C
	1    5250 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4931AFAF
P 4950 4700
F 0 "#PWR?" H 4950 4700 30  0001 C C
F 1 "GND" H 4950 4630 30  0001 C C
	1    4950 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4931AFAC
P 4650 4700
F 0 "#PWR?" H 4650 4700 30  0001 C C
F 1 "GND" H 4650 4630 30  0001 C C
	1    4650 4700
	1    0    0    -1  
$EndComp
Text Notes 6750 4200 0    60   ~
DATA OUT
Text Notes 6750 4100 0    60   ~
GND
Text Notes 6750 4000 0    60   ~
CLK
Text Notes 6750 3900 0    60   ~
3.3V
Text Notes 6750 3800 0    60   ~
GND
Text Notes 6750 3700 0    60   ~
DATA IN
Text Notes 6750 3600 0    60   ~
/CS
$Comp
L CONN_7 P2
U 1 1 4931AF09
P 6550 3850
F 0 "P2" V 6520 3850 60  0000 C C
F 1 "MMC / SD" V 6620 3850 60  0000 C C
	1    6550 3850
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 4931A2D2
P 5250 4300
F 0 "R6" V 5330 4300 50  0000 C C
F 1 "3K3" V 5250 4300 50  0000 C C
	1    5250 4300
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4931A2CC
P 4950 4300
F 0 "R4" V 5030 4300 50  0000 C C
F 1 "3K3" V 4950 4300 50  0000 C C
	1    4950 4300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4931A2C6
P 4650 4300
F 0 "R2" V 4730 4300 50  0000 C C
F 1 "3K3" V 4650 4300 50  0000 C C
	1    4650 4300
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4931A2C1
P 5250 3150
F 0 "R5" V 5330 3150 50  0000 C C
F 1 "1K8" V 5250 3150 50  0000 C C
	1    5250 3150
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4931A2BD
P 4950 3150
F 0 "R3" V 5030 3150 50  0000 C C
F 1 "1K8" V 4950 3150 50  0000 C C
	1    4950 3150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4931A278
P 4650 3150
F 0 "R1" V 4730 3150 50  0000 C C
F 1 "1K8" V 4650 3150 50  0000 C C
	1    4650 3150
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P1
U 1 1 4931A086
P 6100 2050
F 0 "P1" H 6100 2350 60  0000 C C
F 1 "PORT B" V 6100 2050 50  0000 C C
	1    6100 2050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR1
U 1 1 4931975A
P 4700 5350
F 0 "#PWR1" H 4700 5450 30  0001 C C
F 1 "VCC" H 4700 5450 30  0000 C C
	1    4700 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 4931974B
P 5300 6250
F 0 "#PWR2" H 5300 6250 30  0001 C C
F 1 "GND" H 5300 6180 30  0001 C C
	1    5300 6250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 49319743
P 6100 5800
F 0 "C2" H 6150 5900 50  0000 L C
F 1 "100nF" H 6150 5700 50  0000 L C
	1    6100 5800
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 49319740
P 4700 5800
F 0 "C1" H 4750 5900 50  0000 L C
F 1 "100nF" H 4750 5700 50  0000 L C
	1    4700 5800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
