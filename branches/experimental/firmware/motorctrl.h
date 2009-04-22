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
 * $Id$
 */


#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

#include <stdint.h>
#include "queue.h"
#include "plotter.h"



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
 * Indsætter en forsinkelse i ekserkveringen
 */
void MotorCtrl_Delay(uint16_t c);

#endif /* __MOTORCTRL_H__ */
