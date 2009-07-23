/*
 * Problem: This does not work. Try debugging it
 *
 * $Id$
 */

#include "serial.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


/* io buffers */
#define RX_BUF_SIZE 10
char volatile rx_buf[RX_BUF_SIZE];
uint8_t volatile rx_head = 0;
uint8_t volatile rx_count = 0;

#define TX_BUF_SIZE RX_BUF_SIZE
char volatile tx_buf[TX_BUF_SIZE];
uint8_t volatile tx_head = 0;
uint8_t volatile tx_count = 0;


#define LED_PIN 5


/* initialize */
int serial_init(void)
{
  /* interrupt on recieve complete, enable reciever and transmitter */
  UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
  /* 8N1 - 8 data bits, no parity, one stopbit */
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
  /* 9600 baud (cpu frequency is 20 MHz */
  UBRR0L = 129;

  DDRB |= 1<<LED_PIN;

  return 0;
}


/* interrupt vector executed when data i recieved */
ISR(USART_RX_vect)
{
  if (rx_count == RX_BUF_SIZE) {
    /* reviece buffer is full */
  }

  rx_buf[(rx_head + rx_count) % RX_BUF_SIZE] = UDR0;
  rx_count++;
}


/* sends the data through the usart, returns when data has been
   buffered */
void serial_putc(char c)
{
  /* wait until buffer is ready */
  while (tx_count == TX_BUF_SIZE);

  /* enqueue */
  tx_buf[(tx_head + tx_count) % TX_BUF_SIZE] = c;
  tx_count++;

  /* make sure interrupt is running - interrupt is executed when
     register is ready (not just when it becomes ready) */
  UCSR0B |= 1<<UDRIE0;
}

void serial_puts(const char *s)
{
  while (*s)
    serial_putc(*s++);
}

/* data register i ready to recieve data */
ISR(USART_UDRE_vect)
{
  PORTB ^= 1<<LED_PIN;

  /* dequeue transmit buffer*/
  char c = tx_buf[tx_head];
  tx_head = (tx_head + 1) % TX_BUF_SIZE;
  tx_count--;

  UDR0 = c;

  /* if we just sent the last byte in the transmit register, we should
     disable this interrupt (because it is used as indicator of
     whether we are currently transmitting data) */
  if (tx_count == 0)
    UCSR0B &= ~(1<<UDRIE0);
}
