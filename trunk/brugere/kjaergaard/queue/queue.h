/*
 *  FILE   : queue.h
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Define queue record structure and
 *           all forward declarations.
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

#ifndef __QUEUE_H__
#define __QUEUE_H__

struct QueueRecord;
typedef struct QueueRecord *Queue;

int         Queue_IsEmpty(Queue Q);
int         Queue_IsFull(Queue Q);
Queue       Queue_CreateQueue(int maxElements);
void        Queue_DisposeQueue(Queue Q);
void        Queue_MakeEmpty(Queue Q);
void        Queue_Enqueue(ElementType X, Queue Q);
ElementType Queue_Front(Queue Q);
void        Queue_Dequeue(Queue Q);
ElementType Queue_FrontAndDequeue(Queue Q);

#endif  /* __QUEUE_H__ */
