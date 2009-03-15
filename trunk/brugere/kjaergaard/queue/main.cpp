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

  if (!Queue_IsEmpty<int>(Q))
    Queue_Dequeue(Q);
  update();
}

/* interrupt på PD2 */
ISR(INT0_vect)
{
  if (!Queue_IsFull(Q))
    Queue_Enqueue<int>(0, Q);
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

  Q = Queue_Create<int>(8);

  sei();

  while (1);

  return 0;


  /*
  DDRA = 0xff;

  Queue Q;
  Q = Queue_Create<int>(8);

  while (1)
  {
    PORTA = 0xff;
    _delay_ms(200);
    PORTA = 0;

    for (int i = 0; i < 8; i++)
    {
      Queue_Enqueue<int>(i, Q);
      PORTA = 1<<i;
      _delay_ms(125);
    }

    for (int i = 0; i < 8; i++)
    {
      PORTA = 1 << Queue_Front<int>(Q);
      Queue_Dequeue(Q);
      _delay_ms(250);
    }
  }

  Queue_Dispose(Q);

  return 0;
  */

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
