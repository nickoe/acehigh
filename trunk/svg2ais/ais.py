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

ins = {
  'Empty':      '\x00',
  'Start':      '\x01',
  'Stop':       '\x02',
  'Up':         '\x03',
  'UpRight':    '\x04',
  'Right':      '\x05',
  'DownRight':  '\x06',
  'Down':       '\x07',
  'DownLeft':   '\x08',
  'Left':       '\x09',
  'UpLeft':     '\x0A',
  'LowerHead':  '\x0B',
  'LiftHead':   '\x0C'
}

def getb(s):
  return ins[s]


# Vandret opløsning i dpi
def getresx():
  return 1.0

# Lodret opløsning i dpi
def getresy():
  return 1.0