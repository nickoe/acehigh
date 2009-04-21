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


#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

#include <stdint.h>


struct TaskRecord
{
  uint16_t Time;
  uint8_t Ins;
};
typedef struct TaskRecord Task;

struct QueueRecord
{
  int Capacity;
  int Front;
  int Rear;
  int Size;
  Task *Array;
};
typedef struct QueueRecord *Queue;

Queue queue;

uint8_t Queue_IsEmpty(Queue Q);
uint8_t Queue_IsFull(Queue Q);
Queue Queue_CreateQueue(uint16_t size);
void Queue_DisposeQueue(Queue Q);
void Queue_Empty(Queue Q);
void Queue_Enqueue(Queue Q, Task T);
Task Queue_Front(Queue Q);
void Queue_Dequeue(Queue Q);



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
 * Hæver tegneren
 */
void MotorCtrl_Lift(void);

/* 
 * Sænker tegneren
 */
void MotorCtrl_Lower(void);

/*
 * Pauser tegneren
 */
//void MotorCtrl_Pause(void);

/*
 * Fortsætter tegneren
 */
//void MotorCtrl_Resume(void);

/*
 * Indsætter en forsinkelse i ekserkveringen
 */
void MotorCtrl_Delay_MS(uint16_t t);

void MotorCtrl_Tick(void);

#endif /* __MOTORCTRL_H__ */
