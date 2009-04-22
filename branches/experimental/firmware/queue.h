#ifndef __QUEUE_H__
#define __QUEUE_H__


#include <stdint.h>


#define QUEUESIZE       50

typedef struct {
  uint16_t Time;
  uint8_t Ins;
} Task;

typedef struct {
  Task q[QUEUESIZE+1];		/* body of queue */
  int first;                      /* position of first element */
  int last;                       /* position of last element */
  int count;                      /* number of queue elements */
} Queue;

Queue queue;

void init_queue(Queue *q);
void enqueue(Queue *q, Task x);
uint8_t isfull(Queue *q);
uint8_t isempty(Queue *q);
Task dequeue(Queue *q);
Task front(Queue *p);

#endif /* __QUEUE_H__ */
