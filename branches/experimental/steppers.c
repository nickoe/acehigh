/*
 * Stepper motor controller (body)
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


/*
 * Mangler: Udbyg med strømafbryder
 */


#include "steppers.h"

#include <avr/io.h>
#include <stdint.h>


uint8_t pos[2];          /* position inden i stepmotoren, holder styr
			    på steps */
uint8_t poles[2][4];     /* pladsholder til smart spolereference */
uint8_t power[2]; /* pladsholder til tændt/slukket */


void Stp_Init(void)
{
  /* smart spolereference, se Stp_GetPat */
  poles[STP_X][STP_A] = STP_XA;
  poles[STP_X][STP_B] = STP_XB;
  poles[STP_X][STP_C] = STP_XC;
  poles[STP_X][STP_D] = STP_XD;

  poles[STP_Y][STP_A] = STP_YA;
  poles[STP_Y][STP_B] = STP_YB;
  poles[STP_Y][STP_C] = STP_YC;
  poles[STP_Y][STP_D] = STP_YD;

  STP_DDR = 0xff; /* output på alle pins */
}


/* returnerer bitmønstret til porten hvis motorerne skal flyttes */
uint8_t Stp_GetPat(uint8_t motor, uint8_t stp)
{
  uint8_t tmp;

#ifdef STP_FULLSTEP
  tmp = stp % 8;
#else
  tmp = (stp % 4) << 1;
#endif

  switch (tmp)
  {
  case 0:
    return poles[motor][STP_A];
  case 2:
    return poles[motor][STP_C];
  case 4:
    return poles[motor][STP_B];
  case 6:
    return poles[motor][STP_D];
  default:
    return 0;
  }
}


uint8_t Stp_Cmd(uint8_t dir)
{
  uint8_t tmp;

  if (dir | STP_MOVE_UP)
    /* flyt tegnehovedet op */
    tmp = Stp_GetPat(STP_Y, --pos[STP_Y]);
  else if (dir | STP_MOVE_DOWN)
    /* flyt tegnehovedet ned */
    tmp = Stp_GetPat(STP_Y, ++pos[STP_Y]);

  if (dir | STP_MOVE_LEFT)
    /* flyt tegnehovedet til venstre */
    tmp = Stp_GetPat(STP_X, --pos[STP_X]);
  else if (dir | STP_MOVE_RIGHT)
    /* flyt tegnehovedet højre */
    tmp = Stp_GetPat(STP_X, ++pos[STP_X]);

  STP_PORT = tmp;

  return 0;
}
