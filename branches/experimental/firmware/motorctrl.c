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


#include "motorctrl.h"

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <math.h>


/* motorkontrolinstruktioner */
#define MC_CMD_MOVE_UP 0x01
#define MC_CMD_MOVE_DOWN 0x02
#define MC_CMD_MOVE_RIGHT 0x04
#define MC_CMD_MOVE_LEFT 0x08
#define MC_CMD_LIFT 0x10
#define MC_CMD_LOWER 0x20
#define MC_CMD_RESET 0x40


/* definitioner til motorstyringskredsen */
#define MCC_DDR        DDRA
#define MCC_PORT       PORTA
#define MCC_HALFFULL   0
#define MCC_DECAY      1
#define MCC_X_CCW      2
#define MCC_ENABLE     3
#define MCC_X_CLK      4
#define MCC_Y_CLK      5
#define MCC_RESET      6
#define MCC_Y_CCW      7



/* pladholder til positionen */
uint16_t X = 0, Y = 0;

/* timeren */
uint16_t timer = 0;



uint8_t Queue_IsEmpty(Queue Q)
{
  return Q->Size == 0;
}

uint8_t Queue_IsFull(Queue Q)
{
  return Q->Size == Q->Capacity;
}

Queue Queue_Create(uint16_t size) {
  Queue Q;

  /* her var oprindeligt en min-størrelse-tjek */

  Q = malloc(sizeof(struct QueueRecord));
  if (Q == NULL)
  {
    //FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Array = malloc(sizeof(Task) * size);
  if (Q->Array == NULL)
  {
    //FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Capacity = size;
  Queue_Empty(Q);

  return Q;
}

void Queue_Empty(Queue Q)
{
  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;
}

void Queue_Dispose(Queue Q)
{
  if (Q != NULL)
  {
    free(Q->Array);
    free(Q);
  }
}

static uint8_t Queue_Succ(int Value, Queue Q)
{
  if (++Value == Q->Capacity)
  {
    Value = 0;
  }
  return Value;
}

void Queue_Enqueue(Queue Q, Task T)
{

  if (Queue_IsFull(Q)) {
    //Error("Enqueue Error: The queue is full.");
  } else {
    Q->Size++;
    Q->Rear = Queue_Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = T;
  }
}


Task Queue_Front(Queue Q)
{
  if (!Queue_IsEmpty(Q)) {
    return Q->Array[Q->Front];
  }
  //Error("Front Error: The queue is empty.");

  /* Return value to avoid warnings from the compiler */
  Task t;
  return t;
}

void Queue_Dequeue(Queue Q)
{
  if (Queue_IsEmpty(Q)) {
    //Error("Dequeue Error: The queue is empty.");
  } else {
    Q->Size--;
    Q->Front = Queue_Succ(Q->Front, Q);
  }
}

/* initialiser motorerne */
void MotorCtrl_Init(void)
{
  queue = Queue_Create(128);

  /* her skal vi sætte motorkontrolkredsen op */
  MCC_DDR = 0xff;

  /* genstart - klodset */
  MCC_PORT = 0;
  _delay_ms(10);
  MCC_PORT |= 1 << MCC_RESET;
  _delay_ms(10);

  /* aktiver */
  MCC_PORT |= 1 << MCC_ENABLE;

  
  /* timeren sættes op */
  /* timer-clock er f_osc/128 = 125 kHz, Clear Timer on Compare */
  TCCR0 = (1<<WGM01) | (1<<CS02) | (1<<CS00);
  /* tæl op til 249, så bliver frekvensen af timeren 500 Hz */
  OCR0 = 249;
  /* aktiver interrupt */
  TIMSK = 1<<OCIE0;

  sei();
}

/* flytter angivne koordinater, relativt */
uint8_t MotorCtrl_GotoRXY(int16_t x, int16_t y, double v)
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
    while (Queue_IsFull(queue));

    /* jobbet sættes i k */
    Queue_Enqueue(queue, task);

  } while (cur_x <= x || cur_y <= y);
  
  Task task;
  task.Time = 0;
  task.Ins = MC_CMD_RESET;

  /* læg instruktion til at genstarte timeren i det sidste job */
  Queue_Enqueue(queue, task);

  return 0;
}

/* flytter til koordinater, absolut */
uint8_t MotorCtrl_GotoXY(uint16_t x, uint16_t y, double v)
{
  /* vi sender forespørgslen videre til den relative del */
  return MotorCtrl_GotoRXY(x-X, y-Y, v);
}

/* returnerer den absolutte x-position */
void MotorCtrl_Lift(void)
{
  int r = 2;
  r += 4;
}

/* returnerer den absolutte y-position */
void MotorCtrl_Lower(void)
{
  int r = 2;
  r += 4;
}

/* indlægger en forsinkelse */
void MotorCtrl_Delay_MS(uint16_t t)
{
  Task task;
  task.Time = t;
  task.Ins = MC_CMD_RESET;
  
  /* vent til der er plads i køen */
  while (Queue_IsFull(queue));
  Queue_Enqueue(queue, task);
}

ISR(TIMER0_COMP_vect)
{
  PORTE++;
  MotorCtrl_Tick();
}

/*
 * Tik-funktion til motorkontrollen
 *
 * Kaldes 1000 gange i sekundet
 */
void MotorCtrl_Tick(void)
{
  uint8_t reset = 0;

  while (1) {
    if (Queue_IsEmpty(queue))
      break;

    Task t = Queue_Front(queue);

    /* er denne deadline nået? fald ud når deadline ikke er nået */
    if (t.Time > timer)
      break;

    /* her behandles jobbet */

    if (t.Ins & MC_CMD_MOVE_UP) {
      /* flyt op */
      MCC_PORT |= 1 << MCC_Y_CCW;
      MCC_PORT |= 1 << MCC_Y_CLK;
    }

    if (t.Ins & MC_CMD_MOVE_DOWN) {
      /* flyt ned */
      MCC_PORT &= ~(1 << MCC_Y_CCW);
      MCC_PORT |= 1 << MCC_Y_CLK;
    }

    if (t.Ins & MC_CMD_MOVE_LEFT) {
      /* flyt til venstre */
      MCC_PORT |= 1 << MCC_X_CCW;
      MCC_PORT |= 1 << MCC_X_CLK;
    }

    if (t.Ins & MC_CMD_MOVE_RIGHT) {
      /* flyt til højre */
      MCC_PORT &= ~(1 << MCC_X_CCW);
      MCC_PORT |= 1 << MCC_X_CLK;
    }

    if (t.Ins & MC_CMD_LIFT) {
      /* løft skrivehovedet */
    }

    if (t.Ins & MC_CMD_LOWER) {
      /* sænk skrivehovedet */
    }

    if (t.Ins & MC_CMD_RESET) {
      /* genstart timeren - skal fortolkes sidst */
      reset = 1;
    }

    Queue_Dequeue(queue);
  }

  /* mindste høj-tid */
  _delay_us(2);
  /* gør clock-signal lavt igen */
  MCC_PORT &= ~((1<<MCC_X_CLK) | (1<<MCC_Y_CLK));

  /* forhøj tik-tæller */
  if (reset)
    timer = 0;
  else
    timer++;
}
