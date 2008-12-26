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


class Line:
  def __init__(self, _point1, _point2):
    self.point1 = _point1
    self.point2 = _point2

  # beregner afstanden fra punktet til den linie, klassen repræsenterer
  # metoden kan bruges ved alle linier (også lodrette)
  def dst_line(self, p):
    d1 = self.dst_points(self.point2, p)
    d2 = self.dst_points(self.point1, p)
    dn = self.dst_points(self.point1, self.point2)
    return math.sin(math.acos((d2**2 + dn**2 - d1**2)/(2*d2*dn)))*d2

  # beregner afstanden mellem to punkter
  def dst_points(self, p1, p2):
    return math.sqrt((p2.pX()-p1.pX())**2 + (p2.pY()-p1.pY())**2)

  # beregner afstanden fra punktet til liniens endepunkt
  def dst_endpoint(self, point):
    return dst_points(point, self.point2)

  # returnerer de instruktioner der skal bruges for at beskrive linien
  def getins(self):
    # effektivisering
    # vi springer resten af koden over hvis liniestykket er så lille at det ikke kan plottes
    if self.point1 == self.point2:
      return

    ins = ""
    
    # FREMGANGSMÅDE
    
    
    # vi initialiserer løkken
    Q = self.point1
    
    while Q != self.point2:
      P = Q
    
      # find det punkt Q, der har kortets afstand fra linien self.point1-self.point2
      # for Q gælder, at det skal være nabo til P og det skal have kortere afstand til self.point2 end P
    
      Pn[0] = Point(P.pX() + 1, P.pY()    )
      Pn[1] = Point(P.pX() + 1, P.pY() + 1)
      Pn[2] = Point(P.pX()    , P.pY() + 1)
      Pn[3] = Point(P.pX() - 1, P.pY() + 1)
      Pn[4] = Point(P.pX() - 1, P.pY()    )
      Pn[5] = Point(P.pX() - 1, P.pY() - 1)
      Pn[6] = Point(P.pX()    , P.pY() - 1)
      Pn[7] = Point(P.pX() + 1, P.pY() - 1)
    
      # instruktioner til det nye punkt
      Pi[0] = ais.getb("Right")
      Pi[1] = ais.getb("UpRight")
      Pi[2] = ais.getb("Up")
      Pi[3] = ais.getb("UpLeft")
      Pi[4] = ais.getb("Left")
      Pi[5] = ais.getb("DownLeft")
      Pi[6] = ais.getb("Down")
      Pi[7] = ais.getb("DownRight")
    
      i = 0
      while i < 8:
        # funktionen finder afstanden fra punktet til linien
        Dl[i] = dst_line(Pn[i])
        # funktionen finder afstanden fra punktet til linien endepunkt
        Dp[i] = dst_endpoint(Pn[i])
        i += 1
    
      # find den instruktion der skal bruges for at gå fra P til Q
      # fortsæt så længe Q er forskellig fra self.point2
    
      break
    
    # løkke slut
    
    return ins


print "Converter from SVG to AceHigh Instruction Streams"

p1 = Point(1, 2)
p2 = Point(2, 3)
l = Line(p1, p2)
print l.dst_line(p2)