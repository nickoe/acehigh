/* 
 * Test program for AceHigh Control Protocol test program
 *
 * $Id$
 */


#include "serial.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
  sei();
  serial_init();


  while (1) {
    _delay_ms(1000);
    serial_putc("A");
  }

  return 0;
}
