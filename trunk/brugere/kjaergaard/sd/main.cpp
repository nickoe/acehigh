/*
 * SD-læser
 *
 * Kan læse de første 16 bytes fra et sd-kort
 *
 * $Id: main.cpp 214 2009-03-27 16:36:55Z kkjaergaard $
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C"{
#include "lcd.h"
#include "sd_raw.h"
}

int main(void)
{
  DDRD = 0xff;

  /* vi vil da have baggrundsbelysning i vores lcd! */
  DDRC = 1<<3;
  PORTC = 1<<3;

  lcd_init(LCD_DISP_ON);

  char msg[16];

 LOAD:
  
  while (true)
  {
    /* 3 sekunder til at sætte sd-kortet til mikroprocessoren */
    for (uint8_t i = 3; i > 0; i--)
    {
      lcd_clrscr();
      sprintf(msg, "Venter... %d", i);
      lcd_puts(msg);
      _delay_ms(1000);
    }

    /* timeout forbi, begynd at læse */

    uint8_t r = sd_raw_init();
    if (r != 1)
    {
      /* der er sket en fejl */
      lcd_clrscr();
      lcd_puts("Fejl ved init");
      goto LOOP;
    }

    // pladsholder til 16 bogstaver, pointer til array?
    uint8_t bf[16];

    r = sd_raw_read(0, bf, 16);
    if (r != 1)
    {
      lcd_clrscr();
      lcd_puts("Fejl ved læsning");
      goto LOOP;
    }

    lcd_clrscr();
    sprintf(msg, "Byte 0-15@SD:\n");
    lcd_puts(msg);
    lcd_puts((char*)bf); /* typecast nødvendig */

    goto LOOP;
  }

 LOOP:
  while (true)
  {
    if (PINA & (1<<0))
      goto LOAD;
  }

  return 0;
}
