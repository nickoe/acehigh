/*
 * Motor controller (body)
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
 * Mangler: Udbyg med sensoregenskaber, så vi ikke flytter plotteren i
 * stykker med stepmotorerne
 *
 */


#include "motor_ctrl.h"

#include "queue.h"
#include "steppers.h"
#include <stdint.h>

/* c-fil bruges i c++ */
extern "C" {
#include "steppers.c"
}


/* job-strukturen */
struct Task
{
  uint16_t Time;
  uint8_t Ins;
};

/* køen af instruktioner */
typedef struct RecordQueue<Task> *TaskQueue;

/* pladholder til positionen */
uint16_t X = 0, Y = 0;

/* timeren */
uint16_t timer = 0;



/* initialiser motorerne */
void MotorCtrl_Init(void)
{
  Queue_Create(TaskQueue, 128);
  Stp_Init();
}

/* flytter til koordinater, absolut */
uint8_t MotorCtrl_GotoXY(uint16_t x, uint16_t y, float v)
{
  /* vi sender forespørgslen videre til den relative del */
  return MotorCtrl_GotoRXY(x-X, y-Y, v);
}

/* flytter angivne koordinater, relativt */
uint8_t MotorCtrl_GotoRXY(int16_t x, int16_t y, float v)
{
  /* hvis vi ikke skal flytte */
  if (x == X && y == Y)
    return;

  /* pladsholder til instruktionerne */
  uint8_t ins_x = 0, ins_y = 0;

  /* vi gemmer instruktionerne til x- og y-flyt */
  if (x > 0)
    ins_x = STP_MOVE_RIGHT;
  else if (x < 0)
    ins_x = STP_MOVE_LEFT;
  
  /* tjek retning igen */
  if (y > 0)
    ins_y = STP_MOVE_DOWN;
  else if (y < 0)
    ins_y = STP_MOVE_UP;

  /* konstanten L/(x*v) beregnes, se hvilket afsnit i rapport? */
  double L = sqrt(x^2+y^2);
  double k_x = L/(x*v);
  double k_y = L/(y*v);

  /* pladsholder til hvilket skridt vi arbejder på lige nu, vi bruger
     de samme */
  uint8_t cur_x = 1, cur_y = 1;

  /* optimering */
  x = abs(x);
  y = abs(y);

  /* første tidspunkter */
  uint16_t time_x = round(cur_x * k_x);
  uint16_t time_y = round(cur_y * k_y);

  do {

    Task task;

    /* hvis tidspunktet for at flytte x kommer før eller samtidig med
       y, skal vi behandle x */
    if (time_x <= time_y)
    {
      task.Time = time_x;
      task.Ins |= ins_x;
      cur_x++;
    }

    /* hvis tidspunktet for at flytte y kommer før eller samtidig med
       x, skal vi behandle y */
    if (time_x >= time_y)
    {
      task.Time = time_y;
      task.Ins |= ins_y;
      cur_y++;
    }

    /* vi må vente til der er plads i køen */
    while (Queue_IsFull<Task>(TaskQueue));
    /* jobbet sættes i k */
    Queue_Enqueue<Task>(TaskQueue, task);

  } while (cur_x < x || cur_y < y);
  
  /* genstart timeren */
}

/* returnerer den absolutte x-position */
uint16_t MotorCtrl_GetX()
{
  return x;
}

/* returnerer den absolutte y-position */
uint16_t MotorCtrl_GetY()
{
  return y;
}
