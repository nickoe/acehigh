/*
 * Stepper motor controller
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


#ifndef __STEPPERS_H__
#define __STEPPERS_H__


#include <stdint.h>


/* ikke implementeret endnu */
//#define STP_FULLSTEP

/* port til motorerne */
#define STP_PORT PORTD
#define STP_DDR DDRD

/* bitmønster til porte for at spole A er tændt */
#define STP_XA 0x01
#define STP_XB 0x04
#define STP_XC 0x02
#define STP_XD 0x08
#define STP_YA 0x10
#define STP_YB 0x40
#define STP_YC 0x20
#define STP_YD 0x80

/* instruktioner til motorkontrollen, kan sammensættes */
#define STP_MOVE_UP 1
#define STP_MOVE_DOWN 2
#define STP_MOVE_LEFT 4
#define STP_MOVE_RIGHT 8
/* instruktioner til motorkontrollen, kan ikke sammensættes */
#define STP_ON 16
#define STP_OFF 32

/* intern spolereference */
enum{
  STP_A,
  STP_B,
  STP_C,
  STP_D
};

/* intern motorreference */
enum{
  STP_X,
  STP_Y
};


/* initialiserer stepmotorerne */
void stp_init(void);

/* flytter stepmotoren i en eller flere retninger givet som STP_UP,
   STP_DOWN, STP_LEFT og STP_RIGHT, fx stp_move(STP_UP | STP_LEFT) */
int stp_do(uint8_t dir);

/* nulstiller stepmotortælleren, så det punkt den står på er det nye
   udgangspunkt */
void stp_reset(void);


#endif /* __STEPPERS_H__ */
