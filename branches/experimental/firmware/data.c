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
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "plotter.h"
#include "sd_raw.h"


/* offset at læse fra */
offset_t offset = 0;

/* pladsholder til den byte vi er på nu */
uint8_t current_byte = 0;


uint8_t Data_Init()
{
  uint8_t r = sd_raw_init();
  /* tjek resultatet af sd_raw_init(), hvis det er 1 er der succes */
  if (r == 1) {
    } 

  return 0;
}

uint8_t Data_Read()
{
  uint8_t b = 0;
  uint8_t r = sd_raw_read(offset, &b, 1);
  /* tjek b, hvis b = 1 er der succes */

  offset++;

  return b;
}

/* er sand hvis der ikke er flere bytes på strømmen */
uint8_t Data_EOS()
{
  return 0;
}

uint16_t Data_ReadIns()
{
  uint8_t ins[2];

  /* fortsæt indtil vi har et bogstav */
  while (!isalpha(current_byte))
  {
    if (Data_EOS())
      return 0;
    current_byte = Data_Read();
  }

  /* gem bogstav og tag næste byte */
  ins[0] = current_byte;
  if (Data_EOS())
    return 0;
  current_byte = Data_Read();
  
  if (isalpha(current_byte))
  {
    /* næste byte er også bogstav, og instruktionen er syntaktisk set
       gyldig */
    ins[1] = current_byte;

    if (Data_EOS())
      current_byte = 0;
    else
      current_byte = Data_Read(); /* husk at rulle frem til
                                                byten efter det vi har
                                                behandlet */

    return HPGL_INS(ins);
  }

  /* fejl i formatet */

  return 0;
}

uint8_t Data_ParamExists()
{
  while (1)
  {
    /* hvis vi er på et tal er vi i starten af en parameter */
    if (isdigit(current_byte))
      return 1;

    /* vi må sikre os at vi ikke springer over en instruktion - hvis
       vi har et bogstav, er vi igang med at indlæse en instruktion */
    if (isalpha(current_byte))
      return 0;

    /* tegnet er hverken tal eller bogstav og er ikke en del af en
       parameter (f.eks. punktum), derfor kan vi læse videre */

    /* EKSTRA TJEK HER!!! */

    /* husk at springe ud af løkken igen ... byg tjek ind i
       dataføderen */
    if (Data_EOS())
      return 0;

    current_byte = Data_Read();
  }
}

double Data_ReadParamF()
{
  uint8_t param[PARAM_SIZE]; /* plads til parameter */

  uint8_t n = 0;

  /* denne løkke kører så længe der indlæses bytes som er gyldige som
     parametertegn */
  while (n < PARAM_SIZE)
  {
    /* tjek om byten er en gyldig værdi - hvis ikke, så hvad? gyldige
       bytes er tal eller punktum */
    if (isdigit(current_byte) || current_byte == 0x2e)
    {
      param[n] = current_byte;
    }

    /* mellemrum og komma afslutter parameteren, semikolon afslutter
       instruktionen, andre tegn i vejen afslutter også */
    else
    {
      /* parameteren er slut */
      break;
    }

    n++;

    /* findes der mere data i strømmen */ 
    if (Data_EOS())
    {
      current_byte = 0;
      break;
    }

    /* indlæs næsten bytes fra dataføderen */
    current_byte = Data_Read();
  }

  /* denne løkke fylder resten af parameterens pladser med
     null-bytes */
  while (n < PARAM_SIZE)
  {
    param[n] = 0;
    n++;
  }

  return atof((char*)param);
}

