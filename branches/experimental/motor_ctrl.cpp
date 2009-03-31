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

#include <stdint.h>
#include <math.h>

#include "queue.h"
/* c-fil bruges i c++ */
extern "C" {
#include "steppers.h"
}



/* motorkontrolinstruktioner */
#define MC_CMD_MOVE_UP 0x01
#define MC_CMD_MOVE_DOWN 0x02
#define MC_CMD_MOVE_RIGHT 0x04
#define MC_CMD_MOVE_LEFT 0x08
#define MC_CMD_LIFT 0x10
#define MC_CMD_LOWER 0x20
#define MC_CMD_RESET 0x40


/* job-strukturen */
struct Task
{
  uint16_t Time;
  uint8_t Ins;
};

/* køen af instruktioner - unødvendig */
//typedef struct RecordQueue<Task> *TaskQueue;

/* den globale kø */
QueueRecord<Task> *Q;

/* pladholder til positionen */
uint16_t X = 0, Y = 0;

/* timeren */
uint16_t timer = 0;



/* initialiser motorerne */
void MotorCtrl_Init(void)
{
  Queue_Create<Task>(Q, 128);
  Stp_Init();
}

/* flytter angivne koordinater, relativt */
uint8_t MotorCtrl_GotoRXY(int16_t x, int16_t y, float v)
{
  /* hvis vi ikke skal flytte */
  if (x == 0 && y == 0)
    return 0;

  /* pladsholder til instruktionerne */
  uint8_t ins_x = 0, ins_y = 0;

  /* vi gemmer instruktionerne til x- og y-flyt */
  if (x > 0)
    ins_x = MC_CMD_MOVE_RIGHT;
  else if (x < 0)
    ins_x = MC_CMD_MOVE_LEFT;
  
  /* tjek retning igen */
  if (y > 0)
    ins_y = MC_CMD_MOVE_DOWN;
  else if (y < 0)
    ins_y = MC_CMD_MOVE_UP;

  /* optimering */
  x = abs(x);
  y = abs(y);

  /* konstanten L/(x*v) beregnes, se hvilket afsnit i rapport? */
  double L = sqrt(x*x + y*y);
  double k_x = L / (x*v);
  double k_y = L / (y*v);

  /* pladsholder til hvilket skridt vi arbejder på lige nu, vi bruger
     de samme */
  uint8_t cur_x = 1, cur_y = 1;

  /* pladsholder til tidspunkter */
  uint16_t time_x = round(cur_x * k_x);
  uint16_t time_y = round(cur_y * k_y);

  do {

    Task task;

    /* tidspunkt og instruktion SKAL initialiseres */
    task.Time = 0;
    task.Ins = 0;

    /* vi har brug for en midlertidig pladsholder */
    uint16_t tmp_time_x = time_x;

    /* hvis tidspunktet for at flytte x kommer før eller samtidig med
       y, skal vi behandle x */
    if (time_x <= time_y)
    {
      /* nuværende behandles */
      task.Time = time_x;
      task.Ins |= ins_x;

      /* der gøres klar til næste tidspunkt */
      time_x = round(++cur_x * k_x);
    }

    /* hvis tidspunktet for at flytte y kommer før eller samtidig med
       x, skal vi behandle y */
    if (tmp_time_x >= time_y)
    {
      /* nuværende tidspunkt behandles */
      task.Time = time_y;
      task.Ins |= ins_y;

      /* der gøres klar til næste tidspunkt */
      time_y = round(++cur_y * k_y);
    }

    /* vi må vente til der er plads i køen */
    while (Queue_IsFull<Task>(Q));

    /* jobbet sættes i k */
    Queue_Enqueue<Task>(Q, task);

  } while (cur_x <= x || cur_y <= y);
  
  Task task;
  task.Time = 0;
  task.Ins = MC_CMD_RESET;

  /* læg instruktion til at genstarte timeren i det sidste job */
  Queue_Enqueue<Task>(Q, task);

  return 0;
}

/* flytter til koordinater, absolut */
uint8_t MotorCtrl_GotoXY(uint16_t x, uint16_t y, float v)
{
  /* vi sender forespørgslen videre til den relative del */
  return MotorCtrl_GotoRXY(x-X, y-Y, v);
}

/* returnerer den absolutte x-position */
uint16_t MotorCtrl_GetX()
{
  return X;
}

/* returnerer den absolutte y-position */
uint16_t MotorCtrl_GetY()
{
  return Y;
}

/*
 * Tik-funktion til motorkontrollen
 *
 * Kaldes 1000 gange i sekundet
 */
void MotorCtrl_Tick()
{
  Task t;

  int r = Queue_Front<Task>(Q, t);
  /* tjek resultatet af r */
  if (r != QUEUE_SUCCES)
    return;

  /* udfør alle de jobs hvor deadlinen er nået eller overskredet */
  while (t.Time <= timer)
  {
    /* her fortolkes instruktionerne */

    if (t.Ins & MC_CMD_MOVE_UP)
    {
      /* flyt op */
      Stp_Cmd(STP_MOVE_UP);
    }

    if (t.Ins & MC_CMD_MOVE_DOWN)
    {
      /* flyt ned */
      Stp_Cmd(STP_MOVE_DOWN);
    }

    if (t.Ins & MC_CMD_MOVE_LEFT)
    {
      /* flyt til venstre */
      Stp_Cmd(STP_MOVE_LEFT);
    }

    if (t.Ins & MC_CMD_MOVE_RIGHT)
    {
      /* flyt til højre */
      Stp_Cmd(STP_MOVE_RIGHT);
    }

    if (t.Ins & MC_CMD_LIFT)
    {
      /* løft skrivehovedet */
    }

    if (t.Ins & MC_CMD_LOWER)
    {
      /* sænk skrivehovedet */
    }

    if (t.Ins & MC_CMD_RESET)
    {
      /* genstart timeren */
      timer = 0;
    }

    Queue_Dequeue<Task>(Q);

    int r = Queue_Front<Task>(Q, t);
    /* tjek resultatet af r */
    if (r != QUEUE_SUCCES)
      return;
  }

  /* forhøj tik-tæller */
  timer++;
}

