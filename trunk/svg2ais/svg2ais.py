#!/usr/bin/python
# -*- coding: utf-8 -*-

# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <kkjaergaard@gmail.com> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer in return
#                                                           Kristian Kjærgaard
# ----------------------------------------------------------------------------


# TODO: Kontroller origo i koordinatsystemet -- det har betydning for hvilke instruktioner der skal sendes på forskellige punkter i scriptet


import ais
import math
import operator


class Point:
  def __init__(self, x, y):
    # her skal der laves noget så koordinaterne læses ind i tommer
    # ELLER jeg skal lave systemet om så den regner i milimeter
    self.X = x
    self.Y = y
  def __eq__(self, other):
    return self.pX() == other.pX() and self.pY() == other.pY()
  def __ne__(self, other):
    return not self == other
  def pX(self):
    return round(self.X * ais.getresx())
  def pY(self):
    return round(self.Y * ais.getresy())


# Klasse repræsenterende et skridt på linien
class LineStep:
  # beregner afstanden fra punktet til den linie, klassen repræsenterer
  # metoden kan bruges ved alle linier (også lodrette)
  def dist_line(self):
    d1 = self.l.dist_points(self.l.point2, self.p)
    d2 = self.l.dist_points(self.l.point1, self.p)
    dn = self.l.dist_points(self.l.point1, self.l.point2)
    return math.sin(math.acos((d2**2 + dn**2 - d1**2)/(2*d2*dn)))*d2
  # beregner afstanden fra punktet til liniens endepunkt
  def dist_endpoint(self):
    return self.l.dist_points(self.p, self.l.point2)
  def __init__(self, _line, _point, _ins):
    self.p = _point
    self.l = _line
    self.i = _ins
    self.dl = self.dist_line()
    self.dp = self.dist_endpoint()
# def __str__(self):
#   return "dl=" + str(self.dl) + " dp=" + str(self.dp)

class Line:
  def __init__(self, _point1, _point2):
    self.point1 = _point1
    self.point2 = _point2

  # beregner afstanden mellem to punkter
  def dist_points(self, p1, p2):
    if (p1 == p2):
      return 0
    return math.sqrt((p2.pX()-p1.pX())**2 + (p2.pY()-p1.pY())**2)
  
  # returnerer de instruktioner der skal bruges for at beskrive linien
  def getins(self):
    # effektivisering
    # vi springer resten af koden over hvis liniestykket er så lille at det ikke kan plottes
    if self.point1 == self.point2:
      return

    ins = ""
    
    # vi initialiserer løkken
    P = self.point1
    
    while P != self.point2:
      
      # find det punkt Q, der har kortets afstand fra linien self.point1-self.point2
      # for Q gælder, at det skal være nabo til P og det skal have kortere afstand til self.point2 end P

      # TODO: Lav en klasse/struktur der beskriver skridtet, afstand, instruktion m.m..
      # sæt dem i liste, sorter dem efter den mindste afstand til linien
      # vælg den med mindst afstand som er tættere på destinationen end det
      # nuværente punkt
      
      n = []
      n.append(Point(P.pX() + 1, P.pY()    ))
      n.append(Point(P.pX() + 1, P.pY() + 1))
      n.append(Point(P.pX()    , P.pY() + 1))
      n.append(Point(P.pX() - 1, P.pY() + 1))
      n.append(Point(P.pX() - 1, P.pY()    ))
      n.append(Point(P.pX() - 1, P.pY() - 1))
      n.append(Point(P.pX()    , P.pY() - 1))
      n.append(Point(P.pX() + 1, P.pY() - 1))
      
      # instruktioner til det nye punkt
      i = []
      i.append(ais.getb("Right"))
      i.append(ais.getb("UpRight"))
      i.append(ais.getb("Up"))
      i.append(ais.getb("UpLeft"))
      i.append(ais.getb("Left"))
      i.append(ais.getb("DownLeft"))
      i.append(ais.getb("Down"))
      i.append(ais.getb("DownRight"))
  
      points = []
      j = 0
      while j < 8:
        if (self.dist_points(n[j], self.point2) < self.dist_points(P, self.point2)):
          points.append(LineStep(self, n[j], i[j]))
        j += 1

      #print "Før sortering"
      #for ls in points:
      #  print str(ls)
      points.sort(key=operator.attrgetter("dl"))
      ins += points[0].i
      P = points[0].p

      #print "Efter sortering"
      #for ls in points:
      #  print str(ls)


    return ins


class Document:

print "Converter from SVG to AceHigh Instruction Streams"

p1 = Point(2, 2)
p2 = Point(5, 6)
l = Line(p1, p2)
f = open("instruktioner.ais", "w")
f.write(l.getins())
f.close()