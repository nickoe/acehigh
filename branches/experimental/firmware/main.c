/*
 * $Id$
 *
 * Noter her som skal dukke op på den anden side
 */


#include "plotter.h"

#include <avr/io.h>
#include <stdlib.h>

#include "motorctrl.h"
#include "lcd.h"
#include "queue.h"

int main(void)
{
  lcd_init(LCD_DISP_ON);
  MotorCtrl_Init();

  DDRE = 0xff;

  Task t;

  while (1) {
    MotorCtrl_Delay(500);

    t.Ins = 0x01 | 0x04;
    for (int i = 0; i < 500; i++) {
      t.Time = i;
      while(isfull(&queue));
      enqueue(&queue, t);
    }

    t.Time = 0;
    t.Ins = 0x40; /* genstart timeren, indlæg pause */
    while(isfull(&queue));
    enqueue(&queue, t);

    t.Time = 500;
    while(isfull(&queue));
    enqueue(&queue, t);

    t.Ins = 0x02 | 0x08;
    for (int i = 0; i < 500; i++) {
      t.Time = i;
      while(isfull(&queue));
      enqueue(&queue, t);
    }
  }

  return 0;
}
