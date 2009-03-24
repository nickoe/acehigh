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
 * $Id: motor_ctrl.c 203 2009-03-24 12:22:08Z kkjaergaard $
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


void stp_init(void)
{
  /* smart spolereference, se stp_get_pat */
  stp_poles[STP_X][STP_A] = STP_XA;
  stp_poles[STP_X][STP_B] = STP_XB;
  stp_poles[STP_X][STP_C] = STP_XC;
  stp_poles[STP_X][STP_D] = STP_XD;

  stp_poles[STP_Y][STP_A] = STP_YA;
  stp_poles[STP_Y][STP_B] = STP_YB;
  stp_poles[STP_Y][STP_C] = STP_YC;
  stp_poles[STP_Y][STP_D] = STP_YD;

  STP_DDR = 0xff; /* output på alle pins */
}


/* returnerer bitmønstret til porten hvis motorerne skal flyttes */
uint8_t stp_get_pat(uint8_t motor, uint8_t stp)
{
  uint8_t tmp;

#ifdef STP_FULLSTEP
  tmp = stp % 8;
#else
  tmp = (tmp % 4) << 1;
#endif

  switch (tmp)
  {
  case 0:
    return stp_poles[motor][STP_A];
  case 2:
    return stp_poles[motor][STP_C];
  case 4:
    return stp_poles[motor][STP_B];
  case 6:
    return stp_poles[motor][STP_D];
  default:
    return 0;
  }
}


int stp_cmd(uint8_t dir)
{
  uint8_t tmp;

  if (dir | STP_UP)
  {
    /* flyt tegnehovedet op */
    pos_abs[STP_Y]--;
    tmp = stp_get_pat(STP_Y, --pos_rel[STP_Y]);
  }
  else if (dir | STP_DOWN)
  {
    /* flyt tegnehovedet ned */
    pos_abs[STP_Y]++;
    tmp = stp_get_pat(STP_Y, ++pos_rel[STP_Y]);
  };

  if (dir | STP_LEFT)
  {
    /* flyt tegnehovedet til venstre */
    pos_abs[STP_X]--;
    tmp = stp_get_pat(STP_X, --pos_rel[STP_X]);
  }
  else if (dir | STP_RIGHT)
  {
    /* flyt tegnehovedet højre */
    pos_abs[STP_X]++;
    tmp = stp_get_pat(STP_X, ++pos_rel[STP_X]);
  };

  STP_PORT = tmp;

  return 0;
}
