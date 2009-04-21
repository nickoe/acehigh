/*
 * $Id$
 *
 * Noter her som skal dukke op på den anden side
 */


#include <avr/io.h>
#include <stdlib.h>

#include "motorctrl.h"
#include "plotter.h"
#include "lcd.h"

int main(void)
{
  lcd_init(LCD_DISP_ON);
  MotorCtrl_Init();

  DDRE = 0xff;

  Task t;

 LOOP:
  while (1) {
    t.Ins = 0x01 | 0x04;
    for (int i = 0; i < 500; i++) {
      t.Time = i;
      while(Queue_IsFull(queue));
      Queue_Enqueue(queue, t);
    }

    t.Time = 0;
    t.Ins = 0x40; /* genstart timeren, indlæg pause */
    while(Queue_IsFull(queue));
    Queue_Enqueue(queue, t);

    t.Time = 500;
    while(Queue_IsFull(queue));
    Queue_Enqueue(queue, t);

    t.Ins = 0x02 | 0x08;
    for (int i = 0; i < 500; i++) {
      t.Time = i;
      while(Queue_IsFull(queue));
      Queue_Enqueue(queue, t);
    }

    PORTE = 1<<0;

    /* virker tilsyneladende ikke mere */
    MotorCtrl_Delay(500);

    PORTE = 1<<7;
    while (1);
  }

  return 0;
}
