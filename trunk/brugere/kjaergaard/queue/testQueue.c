/*
 *  FILE   : testQueue.c
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Example program that tests the
 *           Queue implementation.
 */

#include <stdio.h>
#include "queue.h"

main() {

  Queue Q;
  int i;

  printf("\n");
  printf("Create Queue(15)...\n\n");
  Q = Queue_CreateQueue(15);

  printf("Enqueue 10 elements...\n");
  for (i=0; i<10; i++) {
    Queue_Enqueue(i, Q);
  }

  printf("Print all 10 elements...\n");
  while (!Queue_IsEmpty(Q)) {
    printf("%d ", Queue_Front(Q));
    Queue_Dequeue(Q);
  }
  printf("\n\n");

  printf("Enqueue 10 more elements...\n");
  for (i=10; i<20; i++) {
    Queue_Enqueue(i, Q);
  }

  printf("Print the new queue...\n");
  while (!Queue_IsEmpty(Q)) {
    printf("%d ", Queue_Front(Q));
    Queue_Dequeue(Q);
  }
  printf("\n\n");

  printf("Dispose of the queue...\n");
  Queue_DisposeQueue(Q);
  printf("\n");

  return 0;

}
