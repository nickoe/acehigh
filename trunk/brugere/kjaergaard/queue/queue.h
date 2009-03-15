/*
 *  FILE   : queue.h
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Define queue record structure and
 *           all forward declarations.
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

template<typename E>
struct QueueRecord
{
  int Capacity;
  int Front;
  int Rear;
  int Size;
  E *Array;
};


template<typename E>
int Queue_IsEmpty(QueueRecord<E> *Q);

template<typename E>
int Queue_IsFull(QueueRecord<E> *Q);

template<typename E>
QueueRecord<E>* Queue_Create(int size);

template<typename E>
void Queue_Dispose(QueueRecord<E> *Q);

template<typename E>
void Queue_Empty(QueueRecord<E> *Q);

template<typename E>
void Queue_Enqueue(E X, QueueRecord<E> *Q);

template<typename E>
E Queue_Front(QueueRecord<E> *Q);

template<typename E>
void Queue_Dequeue(QueueRecord<E> *Q);

template<typename E>
E Queue_FrontAndDequeue(QueueRecord<E> *Q);





template<typename E>
int Queue_IsEmpty(QueueRecord<E> *Q)
{
  return Q->Size == 0;
}

template<typename E>
int Queue_IsFull(QueueRecord<E> *Q)
{
  return Q->Size == Q->Capacity;
}

template<typename E>
QueueRecord<E>* Queue_Create(int size) {
  QueueRecord<E> *Q;

  // tjek evt. at vi har en mindste størrelse her

  Q = (QueueRecord<E>*)malloc(sizeof(struct QueueRecord<E>));
  if (Q == NULL)
  {
    //FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Array = (E*)malloc(sizeof(E) * size);
  if (Q->Array == NULL)
  {
    //FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Capacity = size;
  Queue_Empty<E>(Q);

  return Q;
}

template<typename E>
void Queue_Empty(QueueRecord<E> *Q)
{
  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;
}

template<typename E>
void Queue_Dispose(QueueRecord<E> *Q)
{
  if (Q != NULL)
  {
    free(Q->Array);
    free(Q);
  }
}

template<typename E>
static int Succ(int Value, QueueRecord<E> *Q) {
  if (++Value == Q->Capacity) {
    Value = 0;
  }
  return Value;
}

template<typename E>
void Queue_Enqueue(E X, QueueRecord<E> *Q)
{
  if (Queue_IsFull<E>(Q))
  {
    //Error("Enqueue Error: The queue is full.");
  }
  else
  {
    Q->Size++;
    Q->Rear = Succ<E>(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
  }
}

template<typename E>
E Queue_Front(QueueRecord<E> *Q)
{
  if (!Queue_IsEmpty<E>(Q))
  {
    return Q->Array[Q->Front];
  }
  //Error("Front Error: The queue is empty.");

  /* Return value to avoid warnings from the compiler */
  return 0;

}

template<typename E>
void Queue_Dequeue(QueueRecord<E> *Q)
{
  if (Queue_IsEmpty<E>(Q))
  {
    //Error("Dequeue Error: The queue is empty.");
  }
  else
  {
    Q->Size--;
    Q->Front = Succ<E>(Q->Front, Q);
  }
}

template<typename E>
E Queue_FrontAndDequeue(QueueRecord<E> *Q)
{
  E X;

  if (Queue_IsEmpty<E>(Q))
  {
    //Error("FrontAndDequeue Error: The queue is empty.");
  }
  else
  {
    Q->Size--;
    X = Q->Array[Q->Front];
    Q->Front = Succ<E>(Q->Front, Q);
  }
  return X;
}
