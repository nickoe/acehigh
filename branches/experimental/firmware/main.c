/*
 * $Id$
 *
 * Noter her som skal dukke op på den anden side
 */


#include "plotter.h"

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "data.h"
#include "lcd.h"

int main(void)
{
  lcd_init(LCD_DISP_ON);
  Data_Init();
  Motor_Init();

  DDRE = 0xff;

  while (1);

  return 0;
}


