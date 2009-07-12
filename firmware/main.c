/*
 * $Id$
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "steppers.h"
#include "serial.h"

#define PIN_LED 5


int main()
{
  DDRB |= 1<<PIN_LED;

  sei();
  serial_init();
  steppers_init();

  while (1) {
  }

  return 0;
}
