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


#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__


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


/* instruktioner til motorkontrollen, kan sammensættes */
#define MC_MOVE_UP 0x01
#define MC_MOVE_DOWN 0x02
#define MC_MOVE_LEFT 0x04
#define MC_MOVE_RIGHT 0x08
/* instruktioner til motorkontrollen, kan ikke sammensættes */
#define MC_ON 16
#define MC_OFF 32


/* initialiserer stepmotorerne */
void stp_init(void);

/* flytter stepmotoren i en eller flere retninger givet som STP_UP,
   STP_DOWN, STP_LEFT og STP_RIGHT, fx stp_move(STP_UP | STP_LEFT) */
int stp_do(uint8_t dir);

/* nulstiller stepmotortælleren, så det punkt den står på er det nye
   udgangspunkt */
void stp_reset(void);


#endif /* __MOTOR_CTRL_H__ */
