#!/usr/bin/python2.5
# -*- coding: utf-8 -*-

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
        
    # returnerer svg-filens opløsning i uu/mm . Denne enhed er
    # konstant på 90 dpi og svg-filen ændres til 90
    # dpi i et andet program
    def GetSvgRes():
        return 3.543307

    # returnerer plotterens x-opløsning i dots/mm
    def GetPlotResX():
        return 1

    # returnerer plotterens y-opløsning i dots/mm
    def GetPlotResY():
        return 1

    # behandler dokumentet, udfører handlingerne
    def Process():
        return



class Point:
    # instantierer klassen
    def __init__(self, _d, x, y):
        self.d = _d
        self.X = x
        self.Y = y
    # returnerer punktets x-koordinat på plottet
    def GetPlotX(self):
        # x-koordinaten i mm, uu / uu/mm = mm
        x = self.X / self.d.GetSvgRes()
        # x-koortinaten i dots, mm * dots/mm = dots
        return x * self.d.GetPlotResX()
    # returnerer punktets y-koordinat på plottet - se Point.GetPlotX
    def GetPlotY(self):
        y = self.Y / self.d.GetSvgRes()
        return y * self.d.GetPlotResY()



class Shape:
    def __init__(self):
        # elementer i figuren
        self.elements = []
    # returnerer det sidste punkt på figuren
    def GetEndpoint(self):
        return None
    # returnerer det første punkt på figuren
    def GetStartpoint(self):
        return self.elements[0].GetStartpoint()
    # returnerer de instruktioner der skal bruges for at tenge figuren
    def GetIns(self):
        ins = ""
        for element in self.elements:
            ins += element.GetIns()
        return ins





class Line:
