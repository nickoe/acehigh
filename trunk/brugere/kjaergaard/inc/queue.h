/*
 *  FILE   : queue.h
 *  AUTHOR : Jeffrey Hunter (modified by Kristian Kjærgaard <kkjærgaard@gmail.com>)
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Define queue record structure and
 *           all forward declarations.
 *
 * $Id$
 */

/*
 * En kø bør defineres som "typedef struct QueueRecord<int> *Queue"
 */


#ifndef __QUEUE_H__
#define __QUEUE_H__


#include <avr/io.h>
#include <stdlib.h>
#include <inttypes.h>


/*
 * Fejlkoder
 */
enum {
  QUEUE_SUCCES, /* ingen bemærkninger */
  QUEUE_EMPTY,  /* køen er tom */
  QUEUE_FULL,   /* køen er fuld */
  QUEUE_MALLOC, /* der kan ikke allokeres mere hukommelse */
};


/* 
 * Køstrukturen, skal konkretiseres
 */
template<typename E>
struct QueueRecord
{
  int Capacity;
  int Front;
  int Rear;
  int Size;
  E *Array;
};


/*
 * Oversigt over funktioner i denne fil
 */
template<typename E> int  Queue_IsEmpty(QueueRecord<E> *Q);
template<typename E> int  Queue_IsFull(QueueRecord<E> *Q);
template<typename E> int  Queue_Create(QueueRecord<E> *&Q, int capacity);
template<typename E> void Queue_Dispose(QueueRecord<E> *Q);
template<typename E> void Queue_Empty(QueueRecord<E> *Q);
template<typename E> void Queue_Enqueue(QueueRecord<E> *Q, E X);
template<typename E> int  Queue_Front(QueueRecord<E> *Q, E &X);
template<typename E> int  Queue_Dequeue(QueueRecord<E> *Q);
template<typename E> int  Queue_FrontAndDequeue(QueueRecord<E> *Q, E &X);



/*
 * Returnerer sand hvis køen er tom
 */
template<typename E>
int Queue_IsEmpty(QueueRecord<E> *Q)
{
  return Q->Size == 0;
}


/*
 * Returnerer sand hvis køen er fuld
 */
template<typename E>
int Queue_IsFull(QueueRecord<E> *Q)
{
  return Q->Size == Q->Capacity;
}


/*
 * Opretter køen Q med angivet kapacitet
 *
 * NB: Her har vi brug for pass-by-reference, da vi skal påvirke Q (og
 * ikke den mængde hukommelse, Q peger på) i kalderen
 */
template<typename E>
int Queue_Create(QueueRecord<E> *&Q, int capacity)
{
  Q = (QueueRecord<E>*)malloc(sizeof(struct QueueRecord<E>));
  if (Q == NULL)
    return QUEUE_MALLOC;

  Q->Array = (E*)malloc(sizeof(E) * capacity);
  if (Q->Array == NULL)
    return QUEUE_MALLOC;

  Q->Capacity = capacity;
  Queue_Empty<E>(Q);

  return QUEUE_SUCCES;
}


/*
 * Tømmer køen
 */
template<typename E>
void Queue_Empty(QueueRecord<E> *Q)
{
  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;
}


/*
 * Fjerner køen fra hukommelsen
 */
template<typename E>
void Queue_Dispose(QueueRecord<E> *Q)
{
  if (Q != NULL)
  {
    free(Q->Array);
    free(Q);
  }
}


/*
 * Returnerer det næste element i cirklen
 */
template<typename E>
static int Succ(QueueRecord<E> *Q, int Value)
{
  if (++Value == Q->Capacity)
    Value = 0;

  return Value;
}


/*
 * Sætter et element i kø
 */
template<typename E>
void Queue_Enqueue(QueueRecord<E> *Q, E X)
{
  if (Queue_IsFull<E>(Q))
  {
    //Error("Enqueue Error: The queue is full.");
  }
  else
  {
    Q->Size++;
    Q->Rear = Succ<E>(Q, Q->Rear);
    Q->Array[Q->Rear] = X;
  }
}


/*
 * Returnerer forreste element i køen
 *
 * NB: Her har vi brug for referencen
 */
template<typename E>
int Queue_Front(QueueRecord<E> *Q, E &X)
{
  if (Queue_IsEmpty<E>(Q))
    return QUEUE_EMPTY;

  X = Q->Array[Q->Front];
  return QUEUE_SUCCES;
}


/*
 * Skubber køen en plads
 */
template<typename E>
int Queue_Dequeue(QueueRecord<E> *Q)
{
  if (Queue_IsEmpty<E>(Q))
    return QUEUE_EMPTY;

  Q->Size--;
  Q->Front = Succ<E>(Q, Q->Front);
  return QUEUE_SUCCES;
}


/*
 * Returnerer forreste element i køen og skubber køen en plads
 *
 * NB: Her har vi brug for referencen
 */
template<typename E>
int Queue_FrontAndDequeue(QueueRecord<E> *Q, E &X)
{
  if (Queue_IsEmpty<E>(Q))
    return QUEUE_EMPTY;

  Q->Size--;
  X = Q->Array[Q->Front];
  Q->Front = Succ<E>(Q, Q->Front);

  return QUEUE_SUCCES;
}

#endif /* __QUEUE_H__ */
