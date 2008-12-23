#!/usr/bin/python
# -*- coding: utf-8 -*-

# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <kkjaergaard@gmail.com> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer in return
#                                                           Kristian Kjærgaard
# ----------------------------------------------------------------------------

# Todo: Jeg har brug for at indlæse instruktioner fra svg2ais.py. Jeg skal kende instruktionerne


import ais

print "Plotter til AceHigh Instruction Streams\n"
print "Værdi af ais.getb_empty(): ", ais.getb("Empty")

f = open("data.ais", "w")
f.write(ais.getb_empty())
f.close()
