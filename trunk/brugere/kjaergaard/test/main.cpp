/*
 * Tester til softwaren
 *
 * $Id$
 */

#include "../inc/queue.h"
#include <stdio.h>
#include <math.h>

using namespace std;

/* instruktioner til motorkontrollen, kan sammensættes */
#define STP_MOVE_UP 0x01
#define STP_MOVE_DOWN 0x02
#define STP_MOVE_LEFT 0x04
#define STP_MOVE_RIGHT 0x08
/* instruktioner til motorkontrollen, kan ikke sammensættes */
#define STP_ON 0x10
#define STP_OFF 0x20


#define MC_CMD_MOVE_UP 0x01    /* flyt op */
#define MC_CMD_MOVE_DOWN 0x02  /* flyt ned */
#define MC_CMD_MOVE_LEFT 0x04  /* flyt til venstre */
#define MC_CMD_MOVE_RIGHT 0x08 /* flyt til højre */
#define MC_CMD_LIFT 0x10       /* løft skrivehovedet */
#define MC_CMD_LOWER 0x20      /* sænk skrivehovedet */
#define MC_CMD_RESTART 0x40    /* genstart timeren */


/* job-strukturen */
struct Task
{
  uint16_t Time;
  uint8_t Ins;
};

/* køen af instruktioner */
typedef struct QueueRecord<Task> *TaskQueue;

/* køen */
TaskQueue Q;

/* pladholder til positionen */
uint16_t X = 0, Y = 0;

/* timeren */
uint16_t timer = 0;



/* initialiser motorerne */
void MotorCtrl_Init(void)
{
  Queue_Create<Task>(Q, 128);
  //Stp_Init();
}

/* flytter angivne koordinater, relativt */
uint8_t MotorCtrl_GotoRXY(int16_t x, int16_t y, float v)
{
  /* hvis vi ikke skal flytte */
  if (x == 0 && y == 0)
    return 0;

  /* pladsholder til instruktionerne */
  uint8_t ins_x = 0, ins_y = 0;

  /* vi gemmer instruktionerne til x- og y-flyt */
  if (x > 0)
    ins_x = MC_CMD_MOVE_RIGHT;
  else if (x < 0)
    ins_x = MC_CMD_MOVE_LEFT;
  
  /* tjek retning igen */
  if (y > 0)
    ins_y = MC_CMD_MOVE_DOWN;
  else if (y < 0)
    ins_y = MC_CMD_MOVE_UP;

  /* optimering */
  x = abs(x);
  y = abs(y);

  /* konstanten L/(x*v) beregnes, se hvilket afsnit i rapport? */
  double L = sqrt(x*x + y*y);
  double k_x = L / (x*v);
  double k_y = L / (y*v);

  /* pladsholder til hvilket skridt vi arbejder på lige nu, vi bruger
     de samme */
  uint8_t cur_x = 1, cur_y = 1;

  /* pladsholder til tidspunkter */
  uint16_t time_x = round(cur_x * k_x);
  uint16_t time_y = round(cur_y * k_y);

  do {

    Task task;

    /* tidspunkt og instruktion SKAL initialiseres */
    task.Time = 0;
    task.Ins = 0;

    /* vi har brug for en midlertidig pladsholder */
    uint16_t tmp_time_x = time_x;

    /* hvis tidspunktet for at flytte x kommer før eller samtidig med
       y, skal vi behandle x */
    if (time_x <= time_y)
    {
      /* nuværende behandles */
      task.Time = time_x;
      task.Ins |= ins_x;

      /* der gøres klar til næste tidspunkt */
      time_x = round(++cur_x * k_x);
    }

    /* hvis tidspunktet for at flytte y kommer før eller samtidig med
       x, skal vi behandle y */
    if (tmp_time_x >= time_y)
    {
      /* nuværende tidspunkt behandles */
      task.Time = time_y;
      task.Ins |= ins_y;

      /* der gøres klar til næste tidspunkt */
      time_y = round(++cur_y * k_y);
    }

    /* vi må vente til der er plads i køen */
    while (Queue_IsFull<Task>(Q));

    printf("Lægger job{Time=%d,Ins=%d} i køen\n", task.Time, task.Ins);

    /* jobbet sættes i k */
    Queue_Enqueue<Task>(Q, task);

  } while (cur_x <= x || cur_y <= y);
  
  Task task;
  task.Time = 0;
  task.Ins = MC_CMD_RESTART;

  /* læg instruktion til at genstarte timeren i det sidste job */
  Queue_Enqueue<Task>(Q, task);

  return 0;
}

/* flytter til koordinater, absolut */
uint8_t MotorCtrl_GotoXY(uint16_t x, uint16_t y, float v)
{
  /* vi sender forespørgslen videre til den relative del */
  return MotorCtrl_GotoRXY(x-X, y-Y, v);
}

/* returnerer den absolutte x-position */
uint16_t MotorCtrl_GetX()
{
  return X;
}

/* returnerer den absolutte y-position */
uint16_t MotorCtrl_GetY()
{
  return Y;
}

/*
 * Tik-funktion til motorkontrollen
 *
 * Kaldes 1000 gange i sekundet
 */
void MotorCtrl_Tick()
{
  Task t;

  int r = Queue_Front<Task>(Q, t);
  /* tjek resultatet af r */
  if (r != QUEUE_SUCCES)
    return ;

  /* udfør alle de jobs hvor deadlinen er nået eller overskredet */
  while (t.Time <= timer)
  {
    /* her fortolkes instruktionerne */

    if (t.Ins & MC_CMD_MOVE_UP)
    {
      /* flyt op */
      printf("timer=%d, job-id=%d: Flyt skrivehoved op\n", timer, Q->Front);
    }

    if (t.Ins & MC_CMD_MOVE_DOWN)
    {
      /* flyt ned */
      printf("timer=%d, job-id=%d: Flyt skrivehoved ned\n", timer, Q->Front);
    }

    if (t.Ins & MC_CMD_MOVE_LEFT)
    {
      /* flyt til venstre */
      printf("timer=%d, job-id=%d: Flyt skrivehoved til venstre\n", timer, Q->Front);
    }

    if (t.Ins & MC_CMD_MOVE_RIGHT)
    {
      /* flyt til højre */
      printf("timer=%d, job-id=%d: Flyt skrivehoved til højre\n", timer, Q->Front);
    }

    if (t.Ins & MC_CMD_LIFT)
    {
      /* løft skrivehovedet */
      printf("timer=%d, job-id=%d: Løft skrivehoved\n", timer, Q->Front);
    }

    if (t.Ins & MC_CMD_LOWER)
    {
      /* sænk skrivehovedet */
      printf("timer=%d, job-id=%d: Sænk skrivehoved\n", timer, Q->Front);
    }

    if (t.Ins & MC_CMD_RESTART)
    {
      /* genstart timeren */
      printf("timer=%d, job-id=%d: Genstart timer\n", timer, Q->Front);
      timer = 0;
    }

    Queue_Dequeue<Task>(Q);

    int r = Queue_Front<Task>(Q, t);
    /* tjek resultatet af r */
    if (r != QUEUE_SUCCES)
      return;
  }

  /* forhøj tik-tæller */
  timer++;
}


/* */
int main()
{
  MotorCtrl_Init();

  MotorCtrl_GotoRXY(5, 8, 1);

  for (int i = 0; i < 20; i++)
  {
    printf("Kø{pos=%d}: job{Time=%d,Ins=%d}\n", i, Q->Array[i].Time, Q->Array[i].Ins);
  }

  while (!Queue_IsEmpty<Task>(Q))
    MotorCtrl_Tick();

  return 0;
}
