EESchema Schematic File Version 2
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,./lm1117,valves,./sd-card-reader.cache
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "SD-card-reader"
Date "16 mar 2009"
Rev "1.1"
Comp "AATG"
Comment1 "Ace High"
Comment2 "Designet til OZ5QI's atmega128 print"
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 650  7350 0    60   ~
- Der var fejl i ver. 1.0 af diagrammet. Pin 2 og 7 på porten til MCU var byttet om.
Text Notes 650  7250 0    60   ~
- Pin 8 og 9 på SD kort adapteren er oe'erne der skal bores med 2,5 mm bor
Text Notes 650  7150 0    60   ~
Kommentar:
Wire Notes Line
	6850 2050 6850 3050
Wire Wire Line
	3950 3000 3950 2200
Wire Wire Line
	3950 2200 6100 2200
Wire Wire Line
	6100 2200 6100 2400
Wire Wire Line
	6200 2500 6200 2100
Wire Wire Line
	6300 2800 6050 2800
Wire Wire Line
	5200 4550 4950 4550
Wire Wire Line
	6050 2700 6100 2700
Wire Wire Line
	6100 2700 6100 2950
Wire Wire Line
	5200 3950 4850 3950
Connection ~ 4850 5550
Wire Wire Line
	4850 3950 4850 5700
Wire Wire Line
	3550 5550 3750 5550
Connection ~ 4150 6200
Wire Wire Line
	4850 6100 4850 6200
Wire Wire Line
	4850 6200 3550 6200
Wire Wire Line
	3550 6200 3550 6100
Wire Wire Line
	6200 2500 6050 2500
Wire Wire Line
	3650 3000 3650 2500
Wire Wire Line
	3650 2500 5250 2500
Wire Wire Line
	1100 850  1100 1000
Connection ~ 4250 3650
Wire Wire Line
	4250 3650 5200 3650
Wire Wire Line
	3650 4800 3650 4650
Wire Wire Line
	4250 4800 4250 4650
Wire Wire Line
	5200 3850 4650 3850
Connection ~ 3650 3750
Wire Wire Line
	3650 3750 5200 3750
Wire Wire Line
	3950 3850 4450 3850
Connection ~ 3950 3850
Wire Wire Line
	4450 3850 4450 4050
Wire Wire Line
	5200 4150 4650 4150
Connection ~ 4650 4150
Wire Wire Line
	3950 4650 3950 4800
Wire Wire Line
	4650 3850 4650 4800
Wire Wire Line
	800  850  800  750 
Wire Wire Line
	5250 2800 5150 2800
Wire Wire Line
	5150 2800 5150 2850
Wire Wire Line
	4250 3000 4250 2400
Wire Wire Line
	4250 2400 5250 2400
Wire Wire Line
	4250 4150 4250 3500
Wire Wire Line
	3950 3500 3950 4150
Wire Wire Line
	3650 4150 3650 3500
Wire Wire Line
	6100 2400 6050 2400
Wire Wire Line
	4850 5550 4550 5550
Wire Wire Line
	4150 6350 4150 5850
Wire Wire Line
	3550 5450 3550 5700
Connection ~ 3550 5550
Wire Wire Line
	5200 4250 4750 4250
Wire Wire Line
	4750 4250 4750 2100
Wire Wire Line
	4750 2100 6200 2100
Wire Wire Line
	5200 4850 5100 4850
Wire Wire Line
	5100 4850 5100 4950
Wire Wire Line
	4450 4050 5200 4050
Wire Wire Line
	5200 4650 5050 4650
Wire Wire Line
	5050 4650 5050 2950
Wire Wire Line
	5050 2950 6100 2950
Wire Wire Line
	5200 4750 5150 4750
Wire Wire Line
	5150 4750 5150 3050
Wire Wire Line
	5150 3050 6200 3050
Wire Wire Line
	6200 3050 6200 2600
Wire Wire Line
	6200 2600 6050 2600
Wire Notes Line
	6550 3050 6550 2050
Wire Notes Line
	6550 3050 8700 3050
Wire Notes Line
	8700 3050 8700 2050
Wire Notes Line
	8700 2050 6550 2050
Wire Wire Line
	5250 2700 4950 2700
Wire Wire Line
	4950 2700 4950 4550
Wire Notes Line
	6550 2200 8700 2200
NoConn ~ 5250 2600
Text Notes 5750 4900 0    60   ~
GND
Text Notes 5750 4800 0    60   ~
PROCTECT SWITCH
Text Notes 5750 4500 0    60   ~
N/C
Text Notes 5750 4400 0    60   ~
N/C
Text Notes 5750 4600 0    60   ~
DETECT SWITCH
Text Notes 5750 4700 0    60   ~
PROCTECT AND DETECT SWITCH
Text Notes 6600 2000 0    60   ~
Pin beskrivelse set fra SD-kort
Text Notes 6600 3000 0    60   ~
8    PROCTECT AND DETECT SWITCH
Text Notes 6600 2400 0    60   ~
2    CLK
Text Notes 6600 2800 0    60   ~
6    PROCTECT SWITCH
Text Notes 6600 2700 0    60   ~
5    N/C
Text Notes 6600 2600 0    60   ~
4    DATA OUT
Text Notes 6600 2500 0    60   ~
3    DATA IN
Text Notes 6600 2900 0    60   ~
7    DETECT SWITCH
Text Notes 6600 2300 0    60   ~
1    /CS
Text Notes 6600 2150 0    60   ~
PIN  FUNKTION
NoConn ~ 5200 4450
$Comp
L GND #PWR01
U 1 1 49D5DD9D
P 5100 4950
F 0 "#PWR01" H 5100 4950 30  0001 C C
F 1 "GND" H 5100 4880 30  0001 C C
	1    5100 4950
	1    0    0    -1  
$EndComp
NoConn ~ 5200 4350
$Comp
L CONN_13 P2
U 1 1 49D5DD07
P 5550 4250
F 0 "P2" V 5510 4250 60  0000 C C
F 1 "SD CARD" V 5620 4250 60  0000 C C
	1    5550 4250
	1    0    0    -1  
$EndComp
$Comp
L LM1117 U1
U 1 1 49C016D9
P 4150 5600
F 0 "U1" H 4300 5404 60  0000 C C
F 1 "LM1117MP-3.3" H 4150 5800 60  0000 C C
	1    4150 5600
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 49BEA08F
P 3550 5900
F 0 "C1" H 3600 6000 50  0000 L C
F 1 "10uF" H 3600 5800 50  0000 L C
	1    3550 5900
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 49BEA089
P 4850 5900
F 0 "C2" H 4900 6000 50  0000 L C
F 1 "10uF" H 4900 5800 50  0000 L C
	1    4850 5900
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P3
U 1 1 49BE9F02
P 5650 2600
F 0 "P3" H 5650 2900 60  0000 C C
F 1 "PORTB" V 5650 2600 50  0000 C C
	1    5650 2600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 4931B1F2
P 800 850
F 0 "#FLG02" H 800 1120 30  0001 C C
F 1 "PWR_FLAG" H 800 1080 30  0000 C C
	1    800  850 
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 4931B1EE
P 1100 850
F 0 "#FLG03" H 1100 1120 30  0001 C C
F 1 "PWR_FLAG" H 1100 1080 30  0000 C C
	1    1100 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 4931B1E6
P 1100 1000
F 0 "#PWR04" H 1100 1000 30  0001 C C
F 1 "GND" H 1100 930 30  0001 C C
	1    1100 1000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 4931B1E3
P 800 750
F 0 "#PWR05" H 800 850 30  0001 C C
F 1 "VCC" H 800 850 30  0000 C C
	1    800  750 
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR06
U 1 1 4931B1A2
P 6300 2800
F 0 "#PWR06" H 6300 2900 30  0001 C C
F 1 "VCC" H 6300 2900 30  0000 C C
	1    6300 2800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR07
U 1 1 4931B19C
P 5150 2850
F 0 "#PWR07" H 5150 2850 30  0001 C C
F 1 "GND" H 5150 2780 30  0001 C C
	1    5150 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 4931AFBA
P 4650 4800
F 0 "#PWR08" H 4650 4800 30  0001 C C
F 1 "GND" H 4650 4730 30  0001 C C
	1    4650 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 4931AFB5
P 4250 4800
F 0 "#PWR09" H 4250 4800 30  0001 C C
F 1 "GND" H 4250 4730 30  0001 C C
	1    4250 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 4931AFAF
P 3950 4800
F 0 "#PWR010" H 3950 4800 30  0001 C C
F 1 "GND" H 3950 4730 30  0001 C C
	1    3950 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 4931AFAC
P 3650 4800
F 0 "#PWR011" H 3650 4800 30  0001 C C
F 1 "GND" H 3650 4730 30  0001 C C
	1    3650 4800
	1    0    0    -1  
$EndComp
Text Notes 5750 4300 0    60   ~
DATA OUT
Text Notes 5750 4200 0    60   ~
GND
Text Notes 5750 4100 0    60   ~
CLK
Text Notes 5750 4000 0    60   ~
3.3V
Text Notes 5750 3900 0    60   ~
GND
Text Notes 5750 3800 0    60   ~
DATA IN
Text Notes 5750 3700 0    60   ~
/CS
$Comp
L R R6
U 1 1 4931A2D2
P 4250 4400
F 0 "R6" V 4330 4400 50  0000 C C
F 1 "3K3" V 4250 4400 50  0000 C C
	1    4250 4400
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4931A2CC
P 3950 4400
F 0 "R4" V 4030 4400 50  0000 C C
F 1 "3K3" V 3950 4400 50  0000 C C
	1    3950 4400
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4931A2C6
P 3650 4400
F 0 "R2" V 3730 4400 50  0000 C C
F 1 "3K3" V 3650 4400 50  0000 C C
	1    3650 4400
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4931A2C1
P 4250 3250
F 0 "R5" V 4330 3250 50  0000 C C
F 1 "1K8" V 4250 3250 50  0000 C C
	1    4250 3250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4931A2BD
P 3950 3250
F 0 "R3" V 4030 3250 50  0000 C C
F 1 "1K8" V 3950 3250 50  0000 C C
	1    3950 3250
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4931A278
P 3650 3250
F 0 "R1" V 3730 3250 50  0000 C C
F 1 "1K8" V 3650 3250 50  0000 C C
	1    3650 3250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR012
U 1 1 4931975A
P 3550 5450
F 0 "#PWR012" H 3550 5550 30  0001 C C
F 1 "VCC" H 3550 5550 30  0000 C C
	1    3550 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 4931974B
P 4150 6350
F 0 "#PWR013" H 4150 6350 30  0001 C C
F 1 "GND" H 4150 6280 30  0001 C C
	1    4150 6350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
