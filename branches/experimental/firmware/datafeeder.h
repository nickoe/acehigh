/*
 * Data feeder implementing SD card reading/writing
 *
 * Copyright (C) 2009  Kristian Kjærgaard
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * $Id$
 */


#ifndef __DATAFEEDER_H__
#define __DATAFEEDER_H__

#include <avr/io.h>


/* Initialiserer dataføderen */
void Datafeeder_Init();

/* Returnerer næste byte i strømmen hvis det er muligt */
uint8_t Datafeeder_GetNextByte();

/* Returnerer sand hvis der ikke er mere data */
bool Datafeeder_EOS();

#endif /* __DATAFEEDER_H__ */
