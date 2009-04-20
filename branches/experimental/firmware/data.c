/*
 * Data feeder implementing SD card reading/writing (body)
 *
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
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * $Id$
 */

#include "data.h"

#include <avr/io.h>
#include <stdint.h>

#include "sd_raw.h"


/* offset at læse fra */
uint16_t offset = 0;


uint8_t Datafeeder_Init()
{
  uint8_t r = sd_raw_init();
  /* tjek resultatet af sd_raw_init(), hvis det er 1 er der succes */
  if (r == 1)
    return DATAFEEDER_SUCCES;

  return DATAFEEDER_UNKNOWN;
}

uint8_t Datafeeder_GetNextByte()
{
  uint8_t b = 0;
  uint8_t r = sd_raw_read(offset, &b, 1);
  /* tjek b, hvis b = 1 er der succes */

  offset++;

  return b;
}

/* er sand hvis der ikke er flere bytes på strømmen */
uint8_t Datafeeder_EOS()
{
  return 0;
}
