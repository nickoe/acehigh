#!/usr/bin/python
# -*- coding: utf-8 -*-

# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <kkjaergaard@gmail.com> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer in return
#                                                           Kristian Kjærgaard
# ----------------------------------------------------------------------------


import ais


class Point:
  def __init__(self, x, y):
    # her skal der laves noget så koordinaterne læses ind i tommer
    # ELLER jeg skal lave systemet om så den regner i milimeter
    self.X = x
    self.Y = y
  def pX(self):
    return round(self.X * ais.getresx())
  def pY(self):
    return round(self.Y * ais.getresy())


class Line:
  def __init__(self, _point1, _point2):
    self.point1 = _point1
    self.point2 = _point2
  def getins(self):
    return 0


print "Converter from SVG to AceHigh Instruction Streams"

p = Point(5, 3)
print p.pX(), p.pY()