/*
 * Note om køen her 
 *
 * $Id$
 */


#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "queue.h"

typedef struct QueueRecord<int> *Queue;

uint16_t int_counter0 = 0;
uint8_t int_counter1 = 0;
Queue Q;


void update(void)
{
  PORTA = (1 << Q->Size) - 1;
}

/* kaldes med frekvensen 1 kHz */
ISR(TIMER0_COMP_vect)
{
  if (++int_counter0 < 1000)
    return;

  int_counter0 = 0;

  if (!Queue_IsEmpty(Q))
    Queue_Dequeue(Q);

  update();
}

/* interrupt på PD2 */
ISR(INT0_vect)
{
  if (!Queue_IsFull(Q))
    Queue_Enqueue(Q, 0);
  update();
}


int main(void)
{
  /* CTC, 250 kHz tæller */
  TCCR0 = (1<<WGM01) | (1<<CS01) | (1<<CS00);
  /* tællertop = 249, interruptfrekvens = 1 kHz */
  OCR0 = 249;
  /* compare match-interrupt, output compare interrupt enable for
     timer 0 */
  TIMSK = 1<<OCIE0;

  /* aktiver interrupt på forkant af signal på PD2 */
  MCUCR = (1<<ISC01) | (1<<ISC00);
  GICR = 1<<INT0;

  DDRA = 0xff;

  Queue_Create<int>(Q, 8);

  //sei();

  while (1)
  {
    for (int i = 0; i < 2; i++)
    {
      PORTA = 0xff;
      _delay_ms(100);
      PORTA = 0;
      _delay_ms(100);
    }

    for (int i = 0; i < 8; i++)
    {
      int f = rand() % 256;
      Queue_Enqueue(Q, f);
      PORTA = f;
      _delay_ms(125);
    }

    for (int i = 0; i < 8; i++)
    {
      int f;
      Queue_FrontAndDequeue(Q, f);
      PORTA = f;
      _delay_ms(150);
      PORTA = 0;
      _delay_ms(100);
    }
  }

  Queue_Dispose(Q);

  return 0;

  /*
  DDRD = 0xff;

  //int i;
  int *p_i;

  p_i = (int*)malloc(sizeof(int));

  while (1)
  {
    PORTD = 1<<*p_i;
    _delay_ms(128);

    if (++(*p_i) > 8)
      *p_i = 0;
  }

  free(p_i);

  return 0;
  */
}
