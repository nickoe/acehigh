/*
 * $Id$
 */

#include <avr/io.h>
#include "steppers.h"

#define PIN_LED 5


int main()
{
  DDRB |= 1<<PIN_LED;

  steppers_init();
  steppers_move(5000, 0, 1.0);

  while (1) {
  }

  return 0;
}
