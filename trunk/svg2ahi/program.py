#!/usr/bin/python

# Converter from SVG files to Ace High instruction files
# Copyright © 2008  Kristian Kjærgaard
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see
# <http://www.gnu.org/licenses/>.


# Principper: Vi omsætter alle kurver til en række punkter, som vi
# tegner lige streger mellem.
#
# Programmet afvikles således:
#
#   Først importeres en svg-fil. Noter her.
#
#   Så omsættes alle kendte figurer til en række punkter. Hvordan
#   bestemmes opløsningen?
#
#   Så lægges alle punktsekvenser ind i en liste.
#
#   Disse lister af punktsekvenser lægges ind i en større liste. De
#   sorteres, så punktsekvenser med sammenliggende endepunkter ligger
#   efter hinanden.
#
#   Der indsættes tomme huller af en anden type: hul-typen. Disse
#   bruges til at flytte skrivehovedet til en ny position uden at
#   tegne på vejen derhen.
#
#   Alle disse punktsekvenser omsættes til AHI (Ace High
#   Instructions).
#
#   AHI løbes igennem for at tjekke, om der er
#   gentagelser. Gentagelser bør kapsles ind i en løkke.
#
#   Vores AHI eksporteres til en fil. Husk start- og slutbit.
#

import xml.parsers.expat


# Returnerer
def point2pos(n):
    return 0;



print "Jeg er et Python-program"
print point2pos(4);
