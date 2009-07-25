/*
 * Serial communication and command interpretation for AceHigh
 *
 * $Id$
 */

#include "serial.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


/* io buffers */
#define RX_BUF_SIZE 64 ///< Size of input buffer
char volatile rx_buf[RX_BUF_SIZE]; ///< Input buffer
uint8_t volatile rx_head = 0; ///< Input buffer head
uint8_t volatile rx_count = 0; ///< Number of byte in input buffer

#define TX_BUF_SIZE RX_BUF_SIZE ///< Size of output buffer
char volatile tx_buf[TX_BUF_SIZE]; ///< Output buffer
uint8_t volatile tx_head = 0; ///< Output buffer head
uint8_t volatile tx_count = 0; ///< Number of bytes in output buffer


/* initialize */
void serial_init(void)
{
  /* 8N1 - 8 data bits, no parity, one stopbit */
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
  /* 9600 baud (cpu frequency is 20 MHz */
  UBRR0L = 129;
}


/* clear input and output buffer, enable reciever, start acting upon
   signals */
void serial_enable(void)
{
  rx_count = 0;
  tx_count = 0;
  /* interrupt on recieve complete, enable reciever and transmitter */
  UCSR0B |= (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
}


/* disables reciever and transmitter */
void serial_disable(void)
{
  /* disable reciever, transmitter and data register empty
     interrupt */
  UCSR0B &= ~((1<<RXEN0) | (1<<TXEN0) | (1<<UDRIE0));
}


/// Interrupt executed when data is recieved
ISR(USART_RX_vect)
{
  if (rx_count == RX_BUF_SIZE) {
    /* input buffer is full and we have a very big problem, respond
       with "packet too big" */
    return;
  }

  rx_buf[(rx_head + rx_count) % RX_BUF_SIZE] = UDR0;
  rx_count++;

  /* act upon the signal here */
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


/* sends data through the usart, returns when data has been buffered,
   string must be null-terminated */
void serial_puts(const char *s)
{
  while (*s)
    serial_putc(*s++);
}


/* sends binary data stream through the usart */
void serial_putb(char *s, int len)
{
  for (int i = 0; i < len; i++)
    serial_putc(*s++);
}


/// Interrupt executed when data register is ready to reviece data
ISR(USART_UDRE_vect)
{
  /* dequeue transmit buffer*/
  char c = tx_buf[tx_head];
  tx_head = (tx_head + 1) % TX_BUF_SIZE;
  tx_count--;

  /* if we just sent the last byte in the transmit register, we should
     disable this interrupt (because it is used as indicator of
     whether we are currently transmitting data) */
  if (tx_count == 0)
    UCSR0B &= ~(1<<UDRIE0);

  UDR0 = c;
}
