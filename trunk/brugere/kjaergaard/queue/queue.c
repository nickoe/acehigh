/*
 *  FILE   : queue.c
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Implement all functions required
 *           for a Queue data structure.
 */

#include "queue.h"
#include <stdlib.h>

#define QUEUE_MINSIZE 5

/* kø-definition */
struct QueueRecord {
  int Capacity;
  int Front;
  int Rear;
  int Size;
  ElementType *Array;
};

/* er køen tom? - generisk */
int Queue_IsEmpty(Queue Q) {
  return Q->Size == 0;
}

/* er køen fuld? - generisk */
int Queue_IsFull(Queue Q) {
  return Q->Size == Q->Capacity;
}

/* opretter en kø, returner med fejlkoder m.m. - delvis generisk, kan måske gøres fuldt generisk */
Queue Queue_CreateQueue(int maxElements)
{
  Queue Q;

  if (maxElements < QUEUE_MINSIZE) {
    /* Fejl: køen er mindre end det mindst tilladte */
  }

  /* alloker hukommelse til køstrukturen */
  Q = malloc(sizeof(struct QueueRecord));
  if (Q == NULL)
  {
    /* Fejl: kunne ikke allokere hukommelse */
  }

  /* alloker hukommelse til elementer i køen */
  Q->Array = malloc(sizeof(ElementType) * maxElements);
  if (Q->Array == NULL) {
    /* Fejl: kan ikke allokere hukommelse */
  }

  Q->Capacity = maxElements;
  Queue_MakeEmpty(Q);

  return Q;
}


/* Tømmer køen for alle elementer - generisk */
void Queue_MakeEmpty(Queue Q)
{
  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;
}

/* rydder køen op og fjerner den fra hukommelsen - generisk */
void Queue_DisposeQueue(Queue Q)
{
  if (Q != NULL)
  {
    free(Q->Array);
    free(Q);
  }
}

/* returnerer næste plads til et element i køen */
static int Succ(int Value, Queue Q)
{
  if (++Value == Q->Capacity) {
    Value = 0;
  }
  return Value;
}

/* indsætter element X bagerst i køen Q - delvis generisk */
void Queue_Enqueue(ElementType X, Queue Q)
{
  if (Queue_IsFull(Q))
  {
    /* Fejl: køen er fuld */
  }
  else
  {
    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
  }
}

/* returnerer forreste element i køen - delvis generisk */
ElementType Queue_Front(Queue Q)
{
  if (!Queue_IsEmpty(Q))
  {
    return Q->Array[Q->Front];
  }
  /* Fejl: køen er tom */

  /* Return value to avoid warnings from the compiler */
  return 0;

}


/* fjern element fra køen - generisk */
void Queue_Dequeue(Queue Q)
{
  if (Queue_IsEmpty(Q))
  {
    /* Fejl: køen er tom */
  }
  else
  {
    Q->Size--;
    Q->Front = Succ(Q->Front, Q);
  }
}


/* returnerer første element i køen og fjerner det - delvis generisk */
ElementType Queue_FrontAndDequeue(Queue Q)
{
  ElementType X = 0;

  if (Queue_IsEmpty(Q))
  {
    /* Fejl: køen er tom */
  }
  else
  {
    Q->Size--;
    X = Q->Array[Q->Front];
    Q->Front = Succ(Q->Front, Q);
  }

  return X;
}
