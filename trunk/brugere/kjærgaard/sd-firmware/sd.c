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




/* initialiser spi til sd-kort
void SPIinit(void) {
  DDRB &= ~(1 << SPIDI);	// set port B SPI data input to input
  DDRB |= (1 << SPICLK);	// set port B SPI clock to output
  DDRB |= (1 << SPIDO);	// set port B SPI data out to output 
  DDRB |= (1 << SPICS);	// set port B SPI chip select to output
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
  PORTB &= ~(1 << SPICS);	// set chip select to low (MMC is selected)
}
*/

/* send byte via SPI og returner resultat
char SPI(char d) {  // send character over SPI
  char received = 0;
  SPDR = d;
  while(!(SPSR & (1<<SPIF)));
  received = SPDR;
  return (received);
}
*/

/* initialiser selve sd-kortet
int MMC_Init(void) { // init SPI
  char i;
  PORTB |= (1 << SPICS); // disable MMC
  // start MMC in SPI mode
  for(i=0; i < 10; i++) SPI(0xFF); // send 10*8=80 clock pulses
  PORTB &= ~(1 << SPICS); // enable MMC

  if (Command(0x40,0,0,0x95) != 1) goto mmcerror; // reset MMC
  
 st: // if there is no MMC, prg. loops here
  if (Command(0x41,0,0,0xFF) !=0) goto st;
  return 1;
 mmcerror:
  return 0;
}
*/



/* send kommandoer til SD-kortet
char Command(char befF, uint16_t AdrH, uint16_t AdrL, char befH )
{	// sends a command to the MMC
  SPI(0xFF);
  SPI(befF);
  SPI((uint8_t)(AdrH >> 8));
  SPI((uint8_t)AdrH);
  SPI((uint8_t)(AdrL >> 8));
  SPI((uint8_t)AdrL);
  SPI(befH);
  SPI(0xFF);
  return SPI(0xFF);	// return the last received character
}
*/




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
