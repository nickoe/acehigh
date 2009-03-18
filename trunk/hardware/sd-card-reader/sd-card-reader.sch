EESchema Schematic File Version 2
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,./lm1117,valves,./sd-card-reader.cache
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "SD-card-reader"
Date "16 mar 2009"
Rev "1.0"
Comp "AATG"
Comment1 "Ace High"
Comment2 "Designet til oz5qi's atmega128 print"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LM1117 U1
U 1 1 49C016D9
P 5400 5500
F 0 "U1" H 5550 5304 60  0000 C C
F 1 "LM1117MP-3.3" H 5400 5700 60  0000 C C
	1    5400 5500
	1    0    0    -1  
$EndComp
Connection ~ 6100 5450
Wire Wire Line
	6100 5600 6100 3850
Wire Wire Line
	4800 5450 5000 5450
Connection ~ 5400 6100
Wire Wire Line
	6100 6000 6100 6100
Wire Wire Line
	6100 6100 4800 6100
Wire Wire Line
	4800 6100 4800 6000
Wire Wire Line
	7050 2400 7200 2400
Wire Wire Line
	7200 2400 7200 2000
Wire Wire Line
	7200 2000 5850 2000
Wire Wire Line
	5850 2000 5850 4150
Wire Wire Line
	4650 2900 4650 2400
Wire Wire Line
	4650 2400 6250 2400
Wire Wire Line
	7050 2700 7150 2700
Wire Wire Line
	1100 850  1100 1000
Connection ~ 5250 3550
Wire Wire Line
	5250 3550 6200 3550
Wire Wire Line
	4650 4700 4650 4550
Wire Wire Line
	5250 4700 5250 4550
Wire Wire Line
	6200 3750 5650 3750
Connection ~ 4650 3650
Wire Wire Line
	4650 3650 6200 3650
Wire Wire Line
	4950 3750 5450 3750
Connection ~ 4950 3750
Wire Wire Line
	5450 3750 5450 3950
Wire Wire Line
	5450 3950 6200 3950
Wire Wire Line
	6200 4050 5650 4050
Connection ~ 5650 4050
Wire Wire Line
	4950 4550 4950 4700
Wire Wire Line
	5650 3750 5650 4700
Wire Wire Line
	5850 4150 6200 4150
Wire Wire Line
	800  850  800  750 
Wire Wire Line
	6100 3850 6200 3850
Wire Wire Line
	6250 2700 6150 2700
Wire Wire Line
	6150 2700 6150 2750
Wire Wire Line
	5250 2900 5250 2300
Wire Wire Line
	5250 2300 6250 2300
Wire Wire Line
	5250 4050 5250 3400
Wire Wire Line
	4950 3400 4950 4050
Wire Wire Line
	4650 4050 4650 3400
Wire Wire Line
	7050 2300 7100 2300
Wire Wire Line
	7100 2300 7100 2100
Wire Wire Line
	7100 2100 4950 2100
Wire Wire Line
	4950 2100 4950 2900
Wire Wire Line
	6100 5450 5800 5450
Wire Wire Line
	5400 6250 5400 5750
Wire Wire Line
	4800 5350 4800 5600
Connection ~ 4800 5450
Text Notes 8150 2750 0    60   ~
VCC
Text Notes 7450 2750 0    60   ~
GND
Text Notes 8150 2650 0    60   ~
NC
Text Notes 8150 2550 0    60   ~
NC
Text Notes 7450 2650 0    60   ~
NC
Text Notes 7450 2550 0    60   ~
NC
NoConn ~ 6250 2600
NoConn ~ 6250 2500
NoConn ~ 7050 2500
NoConn ~ 7050 2600
$Comp
L CP C1
U 1 1 49BEA08F
P 4800 5800
F 0 "C1" H 4850 5900 50  0000 L C
F 1 "10uF" H 4850 5700 50  0000 L C
	1    4800 5800
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 49BEA089
P 6100 5800
F 0 "C2" H 6150 5900 50  0000 L C
F 1 "10uF" H 6150 5700 50  0000 L C
	1    6100 5800
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P3
U 1 1 49BE9F02
P 6650 2500
F 0 "P3" H 6650 2800 60  0000 C C
F 1 "PORTB" V 6650 2500 50  0000 C C
	1    6650 2500
	1    0    0    -1  
$EndComp
Text Notes 8150 2450 0    60   ~
DATA OUT
Text Notes 7450 2450 0    60   ~
DATA IN
Text Notes 8150 2350 0    60   ~
CLK
Text Notes 7450 2350 0    60   ~
/CS
$Comp
L PWR_FLAG #FLG01
U 1 1 4931B1F2
P 800 850
F 0 "#FLG01" H 800 1120 30  0001 C C
F 1 "PWR_FLAG" H 800 1080 30  0000 C C
	1    800  850 
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 4931B1EE
P 1100 850
F 0 "#FLG02" H 1100 1120 30  0001 C C
F 1 "PWR_FLAG" H 1100 1080 30  0000 C C
	1    1100 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 4931B1E6
P 1100 1000
F 0 "#PWR03" H 1100 1000 30  0001 C C
F 1 "GND" H 1100 930 30  0001 C C
	1    1100 1000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR04
U 1 1 4931B1E3
P 800 750
F 0 "#PWR04" H 800 850 30  0001 C C
F 1 "VCC" H 800 850 30  0000 C C
	1    800  750 
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 4931B1A2
P 7150 2700
F 0 "#PWR05" H 7150 2800 30  0001 C C
F 1 "VCC" H 7150 2800 30  0000 C C
	1    7150 2700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 4931B19C
P 6150 2750
F 0 "#PWR06" H 6150 2750 30  0001 C C
F 1 "GND" H 6150 2680 30  0001 C C
	1    6150 2750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 4931AFBA
P 5650 4700
F 0 "#PWR07" H 5650 4700 30  0001 C C
F 1 "GND" H 5650 4630 30  0001 C C
	1    5650 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 4931AFB5
P 5250 4700
F 0 "#PWR08" H 5250 4700 30  0001 C C
F 1 "GND" H 5250 4630 30  0001 C C
	1    5250 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 4931AFAF
P 4950 4700
F 0 "#PWR09" H 4950 4700 30  0001 C C
F 1 "GND" H 4950 4630 30  0001 C C
	1    4950 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 4931AFAC
P 4650 4700
F 0 "#PWR010" H 4650 4700 30  0001 C C
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
L VCC #PWR011
U 1 1 4931975A
P 4800 5350
F 0 "#PWR011" H 4800 5450 30  0001 C C
F 1 "VCC" H 4800 5450 30  0000 C C
	1    4800 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 4931974B
P 5400 6250
F 0 "#PWR012" H 5400 6250 30  0001 C C
F 1 "GND" H 5400 6180 30  0001 C C
	1    5400 6250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
