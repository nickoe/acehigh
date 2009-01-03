#!/usr/bin/python2.5
# -*- coding: utf-8 -*-


# Todos
#
# Problem i linie 220 ca.: Hvordan vender koordinatsystemet?


import math
import operator
import sys
import os.path
import xml.parsers.expat


class Document:
    def __init__(self, _filename):
        # lav noget tjek på filnavnet
        self.i = {
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
        self.filename = _filename
        self.shapes = []

    # returnerer en instruktion
    def GetByte(self, b):
        return self.i[b]
        
    # returnerer svg-filens opløsning i uu/mm . Denne enhed er
    # konstant på 90 dpi og svg-filen ændres til 90 dpi i et andet
    # program
    def GetSvgRes(self):
        return 3.543307

    # returnerer plotterens x-opløsning i dots/mm
    def GetPlotResX(self):
        return 1

    # returnerer plotterens y-opløsning i dots/mm
    def GetPlotResY(self):
        return 1

    # håndterer elementer af forskellig facon
    def start_element(self, name, attrs):
        #håndter elementet her
        e = []

        if name.lower() == "line":
            p1 = Point(self, float(attrs["x1"]), float(attrs["y1"]))
            p2 = Point(self, float(attrs["x2"]), float(attrs["y2"]))
            l = Line(self, p1, p2)
            e.append(l)

        if len(e) > 0:
            s = Shape()
            s.elements = e
            self.shapes.append(s)

    # behandler dokumentet, udfører handlingerne
    def Process(self):
        p = xml.parsers.expat.ParserCreate()
        f = open(self.filename, "r")
        p.StartElementHandler = self.start_element
        p.ParseFile(f)
        f.close()

        f = open(self.filename + ".ais", "w")
        f.write(self.GetIns())
        f.close()

    # returnerer instruktionerne i self.shapes[]
    def GetIns(self):
        ins = self.GetByte("Start")
        last_p = DPoint(0,0)
        
        for shape in self.shapes:
            # hvis vi starter et andet sted en vi stoppede før, skal
            # vi løfte tegnehovedet, flytte det og sænke det igen
            if not last_p.sameas(shape.GetStartPoint()):
                # kontroller at vi har tegnet mere end ingenting --
                # hvis vi har, er hovedet nede nu, og det skal løftes
                if len(ins) > 1:
                    ins += self.GetByte("LiftHead")
                l = Line(self, last_p, shape.GetStartPoint())
                ins += l.GetIns()
                ins += self.GetByte("LowerHead")

            ins += shape.GetIns()
            last_p = shape.GetEndPoint()
        
        ins += self.GetByte("Stop")
        return ins


class Point:
    # instantierer klassen
    def __init__(self, _d, x, y):
        self.d = _d
        self.X = float(x)
        self.Y = float(y)
        
    # sammenligning mellem punkter
    def sameas(self, other):
        return self.GetPlotX() == other.GetPlotX() and self.GetPlotY() == other.GetPlotY()

    # returnerer punktets x-koordinat på plottet
    def GetPlotX(self):
        # x-koordinaten i mm, uu / uu/mm = mm
        x = self.X / self.d.GetSvgRes()
        # x-koortinaten i dots, mm * dots/mm = dots
        return round(x * self.d.GetPlotResX())

    # returnerer punktets y-koordinat på plottet - se Point.GetPlotX
    def GetPlotY(self):
        y = self.Y / self.d.GetSvgRes()
        return round(y * self.d.GetPlotResY())


# dummy point, fiktivt punkt hvor vi kun har brug for plotkoordinater
# og ikke svg-koordinater. DPoint er kompatibel med Point
class DPoint:
    # instantierer klassen
    def __init__(self, x, y):
        self.X = round(x)
        self.Y = round(y)

    # sammenligning mellem punkter
    def sameas(self, other):
        return self.GetPlotX() == other.GetPlotX() and self.GetPlotY() == other.GetPlotY()

    # returnerer punktets x-koordinat
    def GetPlotX(self):
        return self.X

    # returnerer punktets y-koordinat
    def GetPlotY(self):
        return self.Y


# repræsenterer en figur
class Shape:
    def __init__(self):
        # elementer i figuren
        self.elements = []

    # returnerer det sidste punkt på figuren
    def GetEndPoint(self):
        return self.elements[-1].GetEndPoint()

    # returnerer det første punkt på figuren
    def GetStartPoint(self):
        return self.elements[0].GetStartPoint()

    # returnerer de instruktioner der skal bruges for at tenge figuren
    def GetIns(self):
        ins = ""
        for element in self.elements:
            ins += element.GetIns()
        return ins




# repræsenterer en linie
class Line:
    # instantierer klassen
    def __init__(self, _document, _startpoint, _endpoint):
        self.document = _document
        self.startpoint = _startpoint
        self.endpoint = _endpoint

    # returnerer liniens startpunkt
    def GetStartPoint(self):
        return self.startpoint

    # returnerer liniens slutpunkt
    def GetEndPoint(self):
        return self.endpoint

    # returnerer afstanden mellem to punkter
    def distPoints(self, p1, p2):
        if (p1.sameas(p2)):
            return 0.0
        # Pythagoras
        return math.sqrt((p2.GetPlotX()-p1.GetPlotX())**2 + (p2.GetPlotY()-p1.GetPlotY())**2)

    # returnerer afstanden mellem et punkt og linien - funktionen
    # behøver verificering. Se grafisk bevis i dokumentationen.
    def distLine(self, p):
        s = self.distPoints(self.endpoint, p)
        e = self.distPoints(self.startpoint, p)
        d = self.distPoints(self.startpoint, self.endpoint)

        r = (e**2 + d**2 - s**2) / (2*e*d)
        # lille sidespring som håndterer beregningsafvigelser i
        # algoritmerne
        if r > 1:
            r = 1

        return math.sin(math.acos(r)) * e
    
    # returnerer de instruktioner der skal bruges for at tegne linien
    def GetIns(self):
        # effektivisering
        if self.startpoint.sameas(self.endpoint):
            return ""

        # pladsholder til alle de instruktioner vi hidtil har samlet
        ins = ""

        # pladsholder til instruktionerne for at nå det nye punkt. VÆR
        # OPMÆRKSOM PÅ hvordan koordinatsystemet vender: bruges der
        # skærmkoordinater eller koordinater fra 1. kvadrant?
        point_ins = []
        point_ins.append(self.document.GetByte("Right"))
        point_ins.append(self.document.GetByte("UpRight"))
        point_ins.append(self.document.GetByte("Up"))
        point_ins.append(self.document.GetByte("UpLeft"))
        point_ins.append(self.document.GetByte("Left"))
        point_ins.append(self.document.GetByte("DownLeft"))
        point_ins.append(self.document.GetByte("Down"))
        point_ins.append(self.document.GetByte("DownRight"))

        P = self.startpoint

        # fortsæt indtil vi når slutpunktet
        while not P.sameas(self.endpoint):
            
            points = []
            points.append(DPoint(P.GetPlotX() + 1, P.GetPlotY()    ))
            points.append(DPoint(P.GetPlotX() + 1, P.GetPlotY() + 1))
            points.append(DPoint(P.GetPlotX()    , P.GetPlotY() + 1))
            points.append(DPoint(P.GetPlotX() - 1, P.GetPlotY() + 1))
            points.append(DPoint(P.GetPlotX() - 1, P.GetPlotY()    ))
            points.append(DPoint(P.GetPlotX() - 1, P.GetPlotY() - 1))
            points.append(DPoint(P.GetPlotX()    , P.GetPlotY() - 1))
            points.append(DPoint(P.GetPlotX() + 1, P.GetPlotY() - 1))

            # FREMGANGSMÅDE: er punktet kortere fra endepunktet end P:
            # fortsæt. Er punktet kortere fra linien end tmp_p: sæt
            # tmp_p = P
            tmp_p = points[0]
            for point in points:
                # hvis punktet er tættere på end P
                if self.distPoints(point, self.endpoint) < self.distPoints(P, self.endpoint):
                    # hvis afstanden fra punktet til linien er mindre end tmp_p til linien
                    if self.distLine(point) < self.distLine(tmp_p):
                        tmp_p = point

            # vi husker punktet til næste omgang
            P = tmp_p
            # instruktionen føjes til køen
            ins += point_ins[points.index(tmp_p)]

        return ins


d = Document("sample.svg")
d.Process()
