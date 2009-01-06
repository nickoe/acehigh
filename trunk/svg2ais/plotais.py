#!/usr/bin/python2.5
# -*- coding: utf-8 -*-


#   Plotter for AceHigh instruction streams
#   Copyright (C) 2009  Kristian Kjærgaard <kkjaergaard@gmail.com>
#
#   This program is free software: you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as
#   published by the Free Software Foundation, either version 3 of the
#   License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see
#   <http://www.gnu.org/licenses/>.


# Todo: Jeg har brug for at indlæse instruktioner fra svg2ais.py. Jeg
# skal kende instruktionerne


from svg2ais import Engine, DPoint


# repræsenterer dimensionerne af billedet
class Dimensions:
    def __init(self, w, h):
        self.width = w
        self.height = h


# repræsenterer motoren der plotter
class Plotter
    # instantierer klassen
    def __init__(self, filename):
        self.filename = filename
        self.file = None
        self.image = None
        self.drawing = False
        self.pos = DPoint(0,0)
        self.dim = Dimentions(1,1)

    # sætter en plet på billedet
    def Plot(self):
        self.image.setPixel(self.pos.X, self.pos.Y, 

    # behandler inputtet og skriver outputtet
    def Process(self):
        return

    # gør billedet én pixel breddere
    def IncWidth(self):
        return

    # gør billedet én pixel højere
    def IncHeight(self):
        return
