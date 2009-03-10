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
 * Denne fil indeholder kode fra captain.at?
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
 *
 * Lav evt. header med sd-kommandonavne - se sd-datablad s. 102
 *
 * Man sender kommandoer som vist i tabellen s. 102 i
 * databladet. Nogle kommandoer sendes efter CMD55 - de står på
 * s. 107.
 */


#include <avr/io.h>




/* initialiser spi til sd-kort */
void spi_init(void) {
  DDRB &= ~(1 << SPIDI);	// set port B SPI data input to input
  DDRB |= (1 << SPICLK);	// set port B SPI clock to output
  DDRB |= (1 << SPIDO);	// set port B SPI data out to output 
  DDRB |= (1 << SPICS);	// set port B SPI chip select to output
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
  PORTB &= ~(1 << SPICS);	// set chip select to low (MMC is selected)
}

/* send byte via SPI og returner resultat */
char spi_send(char d) {  // send character over SPI
  char r = 0;
  SPDR = d;
  while(!(SPSR & (1<<SPIF))); /* vent til vi modtager noget */
  r = SPDR; /* for at sikre at byten fjernes fra registret så
		      en ny kan sættes ind */
  return r;
}


/* initialiser selve sd-kortet via spi'en */
int sd_init(void) { // init SPI
  char i;

  PORTB |= (1 << SPICS); /* disable SD */

  /* start MMC in SPI mode */
  for(i = 0; i < 10; i++)
  {
    /* send 10*8=80 clock pulses - HVORFOR?!?? */
    spi_send(0xff);
  }

  PORTB &= ~(1 << SPICS); /* enable SD */

  if (sd_cmd(0x40, 0, 0, 0x95) != 1) goto sderror; /* reset MMC */
  
 st: /* if there is no MMC, prg. loops here */
  if (sd_cmd(0x41, 0, 0, 0xff) != 0) goto st;
  return 1;
 sderror:
  return 0;
}




/* send kommandoer til SD-kortet */
char sd_cmd(char befF, uint16_t AdrH, uint16_t AdrL, char befH )
{
  spi_send(0xff);
  spi_send(beff);
  spi_send((uint8_t)(AdrH >> 8));
  spi_send((uint8_t)AdrH);
  spi_send((uint8_t)(AdrL >> 8));
  spi_send((uint8_t)AdrL);
  spi_send(befH);
  spi_send(0xff);
  return spi_send(0xff); /* return the last received character */
}


int main(void)
{
  int i = 2+2;
  return 0;
}
