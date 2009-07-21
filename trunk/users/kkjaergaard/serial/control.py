#!/usr/bin/python

import serial, time

print "AceHigh Control Program"

s = serial.Serial("/dev/ttyUSB0", 9600)

s.write("a")
# apparently, I need to wait a moment while recieving the responce -
# perhaps we should wait the total allowed time-out before reading the
# responce?
time.sleep(0.1)

i = s.inWaiting()

if i > 0:
    print s.read(i)

s.close()
