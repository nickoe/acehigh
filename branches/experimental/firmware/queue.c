#include "queue.h"
#include <stdint.h>

void init_queue(Queue *q)
{
  q->first = 0;
  q->last = QUEUESIZE-1;
  q->count = 0;
}

void enqueue(Queue *q, Task x)
{
  if (isfull(q)) {
    //printf("Warning: queue overflow enqueue x=%d\n",x);
  } else {
    q->last = (q->last+1) % QUEUESIZE;
    q->q[ q->last ] = x;    
    q->count = q->count + 1;
  }
}

uint8_t isfull(Queue *q)
{
  return (q->count >= QUEUESIZE);
}

uint8_t isempty(Queue *q)
{
  return q->count <= 0;
}

Task front(Queue *q)
{
  Task x;

  if (isempty(q)) {
    //printf("Warning: empty queue dequeue.\n");
  } else {
    x = q->q[ q->first ];
  }

  return x;
}

Task dequeue(Queue *q)
{
  Task x;

  if (isempty(q)) {
    //printf("Warning: empty queue dequeue.\n");
  } else {
    x = q->q[ q->first ];
    q->first = (q->first+1) % QUEUESIZE;
    q->count = q->count - 1;
  }
  
  return(x);
}
