/*
 * SD card reading/writing firmware
 * Copyright (C) <year>  <name of author>
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
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * $Id$
 */


/*
 * Noter om SPI som SD-kort-læser
 *
 * Følgende IO-bits sættes: spi data in (sd data out) = in, spi data
 * out (sd data in) = out, spi clock = out, spi chip select = out
 *
 * Følgende bits sættes i SPCR: SPE, MSTR, SPR1, SPR0
 *
 * Chip select: chippen er aktiv ved lav
 */


#include <avr/io.h>


/* Initialiserer SPI'en og antager, at der sidder et SD-kort for enden
   af den */
void sd_init(void);


void sd_init(void)
{
  SPCR = (1<<SPE) | (1<<MSTR);
}

int main(void)
{
  int i = 2+2;
  return 0;
}
