EESchema Schematic File Version 2
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "Stroemforsyning til (x,y)-plotter"
Date "1 mar 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TRANSFO2 T?
U 1 1 49AAED15
P 450 2250
F 0 "T?" H 450 2750 70  0000 C C
F 1 "TRANSFO2" H 450 1750 70  0000 C C
	1    450  2250
	1    0    0    -1  
$EndComp
Connection ~ 9700 2950
Wire Wire Line
	9800 2950 9700 2950
Connection ~ 9700 2550
Wire Wire Line
	9800 2550 9700 2550
Wire Wire Line
	9700 3200 9700 2150
Wire Wire Line
	9700 2150 9800 2150
Wire Wire Line
	3050 3200 3050 3300
Wire Wire Line
	3050 3300 1950 3300
Wire Wire Line
	1950 1450 3050 1450
Wire Wire Line
	3050 1450 3050 1500
Wire Wire Line
	2200 2350 2200 1350
Wire Wire Line
	2200 1350 3900 1350
Wire Wire Line
	9800 2350 9700 2350
Connection ~ 9700 2350
Wire Wire Line
	9800 2750 9700 2750
Connection ~ 9700 2750
$Comp
L GND #PWR?
U 1 1 49AAECC2
P 9700 3200
F 0 "#PWR?" H 9700 3200 30  0001 C C
F 1 "GND" H 9700 3130 30  0001 C C
	1    9700 3200
	1    0    0    -1  
$EndComp
$Comp
L CONN_10 P?
U 1 1 49AAECAE
P 10150 2600
F 0 "P?" V 10100 2600 60  0000 C C
F 1 "CONN_10" V 10200 2600 60  0000 C C
	1    10150 2600
	1    0    0    -1  
$EndComp
$Comp
L CP C?
U 1 1 49AAEC83
P 4600 2000
F 0 "C?" H 4650 2100 50  0000 L C
F 1 "CP" H 4650 1900 50  0000 L C
	1    4600 2000
	1    0    0    -1  
$EndComp
$Comp
L BRIDGE D?
U 1 1 49AAEC2B
P 3050 2350
F 0 "D?" H 3050 2400 70  0000 C C
F 1 "BRIDGE" H 3050 2300 70  0000 C C
	1    3050 2350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P?
U 1 1 49AAEC00
P -550 2100
F 0 "P?" V -600 2100 40  0000 C C
F 1 "230VAC" V -500 2100 40  0000 C C
	1    -550 2100
	-1   0    0    1   
$EndComp
$EndSCHEMATC
