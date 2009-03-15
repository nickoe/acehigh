#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "queue.h"

typedef struct QueueRecord<int> *Queue;

int main(void)
{
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
