/*
 * $Id$
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "steppers.h"
#include "serial.h"

#define PIN_LED 5


int counter = 0;


ISR(TIMER2_COMPA_vect)
{
  if (++counter == 1000) {
    PORTB ^= 1<<PIN_LED;
    counter = 0;
  }
}

int main()
{
  DDRB |= 1<<PIN_LED;

  /* set timer/counter2 to interrupt */
  TCCR2A = 1<<WGM21; /* ctc mode */
  TCCR2B = 1<<CS21; /* prescaler to 8 */
  OCR2A = 249; /* interrupts with 10 KHz */
  TIMSK2 |= 1<<OCIE2A; /* enable interrupt */
  

  sei();
  serial_init();
  steppers_init();

  while (1) {
  }

  return 0;
}
