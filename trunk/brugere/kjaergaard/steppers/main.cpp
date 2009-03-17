/*
 * $Id$
 */

#include <avr/io.h>
#include <util/delay.h>

extern "C" {
  #include "steppers.h"
}

int main(void)
{
  stp_init();

  while(true)
  {
    stp_move(STP_LEFT);
    _delay_ms(200);
  }

  return 0;
}
