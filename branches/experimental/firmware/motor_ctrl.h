/*
 * Motor controller
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

/*
 * Initialiserer motorkontrollen, positionerer hovedet og returnerer
 * når alt er på plads
 */
void MotorCtrl_Init(void);

/*
 * Flytter tegneren absolut til positionen (x,y), når der er
 * tid. Returnerer status når jobbet er behandlet og sat i kø.
 */
uint8_t MotorCtrl_GotoXY(uint16_t x, uint16_t y, double v);

/*
 * Flytter tegneren relativt til positionen (), når der er
 * tid. Returnerer status når kobbet er behandlet og sat i kø.
 */
uint8_t MotorCtrl_GotoRXY(int16_t x, int16_t y, double v);

/*
 * Returnerer nuværende X-position.
 */
uint16_t MotorCtrl_GetX(void);

/* 
 * Returnerer nuværende Y-position.
 */
uint16_t MotorCtrl_GetY(void);


#endif /* __MOTOR_CTRL_H__ */
