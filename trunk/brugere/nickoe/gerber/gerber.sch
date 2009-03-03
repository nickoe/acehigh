EESchema Schematic File Version 2
LIBS:power,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "12 jan 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4750 3600 4500 3600
Wire Wire Line
	4500 3400 4750 3400
Wire Wire Line
	5250 3400 5300 3400
Wire Wire Line
	5300 3400 5300 3600
Wire Wire Line
	5300 3600 5150 3600
$Comp
L LED D1
U 1 1 496AFC21
P 4950 3600
F 0 "D1" H 4950 3700 50  0000 C C
F 1 "LED" H 4950 3500 50  0000 C C
	1    4950 3600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 496AFC16
P 5000 3400
F 0 "R1" V 5080 3400 50  0000 C C
F 1 "R" V 5000 3400 50  0000 C C
	1    5000 3400
	0    -1   -1   0   
$EndComp
$Comp
L CONN_2 P1
U 1 1 496AFC11
P 4150 3500
F 0 "P1" V 4100 3500 40  0000 C C
F 1 "CONN_2" V 4200 3500 40  0000 C C
	1    4150 3500
	-1   0    0    1   
$EndComp
$EndSCHEMATC
