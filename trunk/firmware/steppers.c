/*
 * $Id$
 */


#include "steppers.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>


/* timer/counter is always running to ensure a proper timing between
   movements - see documentation */
#define tick_start() (TIMSK0 |= 1<<OCIE0A) /* enable interrupt */
#define tick_stop() (TIMSK0 &= ~(1<<OCIE0A)) /* disable interrupt */
#define tick_running() (TIMSK0 & 1<<OCIE0A) /* is interrupt enabled? */


#define PIN_CLK 6


/* data for an axis */
struct AxisRecord {
  /* next time we toggle signal */
  uint32_t Next;
  /* steps pr. mm ratio */
  double Ratio;
  /* number of steps already taken + 1 */
  uint32_t Count;
};

/* data for the entire movement (except directions) */
struct MovementRecord {
  /* actual time in ticks (10.000 Hz) */
  uint32_t Now;
  /* time the movement has finished */
  uint32_t End;
  /* data for axes */
  struct AxisRecord X;
  struct AxisRecord Y;
};


static struct MovementRecord M;


/* Interruptet kaldes 10.000 gange i sekundet og gør, at motoren kan
   køre med 5.000 steps i sekundet. Algoritmen skal sørge for at
   tjekke, om motoren kan steppe (er den kørt ud til kanten?) og om
   den må steppe (er det tid til at steppe?). TBD (to be designed). */


ISR(TIMER0_COMPA_vect)
{
  if (++M.Now > M.End) /* vi skal også behandle sidste trin */
    tick_stop();

  if (M.Now == M.X.Next) {
    PORTD ^= 1<<PIN_CLK;
    M.X.Next = round(++M.X.Count * M.X.Ratio);
  }
}


void steppers_move(int x, int y, double v)
{
  /* prepare a temporaty MovementRecord with values for next
     movement */
  struct MovementRecord m;

  double l = sqrt(square(x) + square(y));
  m.End = (uint32_t)(round(l / v)) << 1;
  m.Now = 0;

  m.X.Count = 1;
  m.X.Ratio = (m.End >> 1) / x;
  m.X.Next = (uint32_t)round(m.X.Ratio); /* type-casting necessary */

  /* wait until the movement has ended */
  while (tick_running());

  /* push new values into record, change direction bits and start
     moving */
  M = m;
  tick_start();
}


void steppers_init()
{
  /* set up timer */
  TCCR0A = 1<<WGM01; /* CTC mode */
  OCR0A = 199; /* interrupt med 10 KHz, højeste impulsfrekvens er 5
		  KHz */
  TCCR0B |= 1<<CS01; /* præskalar på 8 */
  sei(); /* aktiver interrupts */

  /* set up ports */
  DDRD |= 1<<PIN_CLK;
}
