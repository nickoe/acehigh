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

# TODO: Fejl i linie 51: acos(x): x er sandsynligvis uden for defineret interval

import math
import operator
import sys
import os.path
import xml.parsers.expat


# Array til instruktioner
_ins = {
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

# Getter til bestemt instruktion
def getb(s):
  return _ins[s]


# Vandret opløsning i dpi
def getresx():
  return 1.0

# Lodret opløsning i dpi
def getresy():
  return 1.0



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
  def __str__(self):
    return "Point(" + str(self.X) + "," + str(self.Y) + ")"
  def pX(self):
    return round(self.X * getresx())
  def pY(self):
    return round(self.Y * getresy())


# Klasse repræsenterende et skridt på linien
class LineStep:
  # beregner afstanden fra punktet til den linie, klassen repræsenterer
  # metoden kan bruges ved alle linier (også lodrette)
  # FEJL her... hvorfor?
  def dist_line(self):
    d1 = self.l.dist_points(self.l.point2, self.p)
    d2 = self.l.dist_points(self.l.point1, self.p)
    dn = self.l.dist_points(self.l.point1, self.l.point2)
    #print "beregner linieafstand med d1", str(d1), "d2", str(d2), "dn", str(dn)
    result = d2**2 + dn**2 - d1**2
    result /= (2*d2*dn)
    #print result
    # lille sidespring som håndterer beregningsafvigelser i algoritmerne
    if result > 1:
      result = 1
    result = math.acos(result)
    result = math.sin(result)*d2
    return result
  
  # beregner afstanden fra punktet til liniens endepunkt
  def dist_endpoint(self):
    return self.l.dist_points(self.p, self.l.point2)
  def __init__(self, _line, _point, _ins):
    self.p = _point
    self.l = _line
    self.i = _ins
    #print "beregner afstanden fra linien fra punktet", str(self.p), "liniekoordinater er", str(self.l.point1), "og", str(self.l.point2)
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
    # Pythagoras
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
      # HER STYRES ORIGO!!!
      i = []
      i.append(getb("Right"))
      i.append(getb("UpRight"))
      i.append(getb("Up"))
      i.append(getb("UpLeft"))
      i.append(getb("Left"))
      i.append(getb("DownLeft"))
      i.append(getb("Down"))
      i.append(getb("DownRight"))
  
      points = []
      j = 0
      while j < 8:
        #print "behandler punkt nr", j, "med koordinater", str(n[j])
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


# Repræsenterer en SVG-fil
class Document:
  def __init__(self, _file):
    # tjek om filen findes
    self.file = _file
    self.ins = ""
    self.lines = []
    self.parser = xml.parsers.expat.ParserCreate()
    self.parser.StartElementHandler = self.start_element
    self.parser.EndElementHandler = self.end_element
    print "Opretter dokumentklasse"

  def start_element(self, name, attrs):
    # handler til start-elementer
    if name.lower() == "line":
      #print "Håndterer linie"
      p1 = Point(float(attrs["x1"]), float(attrs["y1"]))
      p2 = Point(float(attrs["x2"]), float(attrs["y2"]))
      l = Line(p1, p2)
      self.lines.append(l)
      self.current_element = l

  def end_element(self, name):
    # tjek om alle data er behandlet
    # hvis de ikke er: kast exception
    self.current_element = None
  
  # parser dokumentet
  def parse(self):
    print "Indlæser SVG"
    f = open(self.file, "r")
    self.parser.ParseFile(f)
    f.close()
  
  # konverterer objekterne til instruktioner
  def convert(self):
    # initialisering
    ins = getb("Start")
    print "Konverterer SVG til AIS"
    previous = Line(Point(0,0), Point(0,0))
    
    for line in self.lines:
      # hvis der er et hul -- hvis vi hopper
      if (previous.point2 != line.point1):
        self.ins += getb("LiftHead")
        l = Line(previous.point2, line.point1)
        self.ins += l.getins()
        self.ins += getb("LowerHead")
      self.ins += line.getins()

    ins += getb("Stop")
  
  def writeins(self, _file):
    print "Skriver AIS til fil"
    f = open(_file, "w")
    f.write(self.ins)
    f.close()



print "Konverteringsprogram fra SVG til AIS"
print "Copyright © 2008 AceHigh Project\n"


if len(sys.argv) > 1:
  if os.path.isfile(sys.argv[1]):
    print "Påbegynder konvertering af \"" + sys.argv[1] + "\""
    d = Document(sys.argv[1])
    d.parse()
    d.convert()
    d.writeins(sys.argv[1] + ".ais")
    print "Data skrevet til \"" + sys.argv[1] + ".ais\""
  else:
    print "Filen \"" + sys.argv[1] + "\" eksisterer ikke"
else:
  print "Angiv venligst fil"
  