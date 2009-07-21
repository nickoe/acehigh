/* 
 * Test program for AceHigh Control Protocol test program
 *
 * This program will return every recieved byte incremented (sending
 * "a" will return "b")
 *
 * $Id$
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


/* interrupt on recieve complete */
ISR(USART_RX_vect)
{
  uint8_t c = UDR0;

  /* wait to data register is empty */
  while (!(UCSR0A & (1<<UDRE0)));

  /* return incremented to make sure data has been processed by the
     mcu */
  UDR0 = ++c;
}

int main()
{
  /* interrupt on recieve complete, enable reciever and transmitter */
  UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
  /* 8 data bits */
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
  /* 9600 baud (cpu frequency is 20 MHz */
  UBRR0L = 129;

  sei();

  while (1) {
  }

  return 0;
}
