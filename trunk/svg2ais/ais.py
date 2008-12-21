#!/usr/bin/python
# -*- coding: utf-8 -*-

# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <kkjaergaard@gmail.com> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer in return
#                                                           Kristian Kjærgaard
# ----------------------------------------------------------------------------


# Denne fil beskriver AceHigh Instruction Stream - dataformatet til vores plotter


# Todo: jeg mangler en smart måde at bruge værdierne på: jeg skal kunne tilgå både byten og navnet (begge skal bruges uden for filen)
# værdierne skal også omsættes til bytes så de skrives rigtigt til outputtet

# tjek at det virker som det skal
def Empty():
  return 0

ins = {
  Empty:      0,
  'Start':      1,
  'Stop':       2,
  'Up':         3,
  'UpRight':    4,
  'Right':      5,
  'DownRight':  6,
  'Down':       7,
  'DownLeft':   8,
  'Left':       9,
  'UpLeft':     10,
  'LowerHead':  11,
  'LiftHead':   12
}


def getIns():
  return "Instruktion her"

def getByte():
  return "Byte her"

print Empty()