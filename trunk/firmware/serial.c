/* 
 * $Id
 */


#include "serial.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>



#define RX_BUFFER_SIZE 10
#define TX_BUFFER_SIZE RX_BUFFER_SIZE

uint8_t volatile rx_buffer[RX_BUFFER_SIZE];
uint8_t volatile rx_head;
uint8_t volatile rx_count;

uint8_t volatile tx_buffer[TX_BUFFER_SIZE];
uint8_t volatile tx_head;
uint8_t volatile tx_count;

void enqueue(uint8_t x)
{
  /* queue is full */
  if (rx_count == RX_BUFFER_SIZE)
    return;

  rx_buffer[(rx_head + rx_count) % RX_BUFFER_SIZE] = x;
  rx_count++;
}

uint8_t dequeue()
{
  if (rx_count == 0)
    return 0;

  uint8_t x = rx_buffer[rx_head];
  rx_head = (rx_head+1) % RX_BUFFER_SIZE;
  rx_count--;
  return x;
}


/* initialize */
void serial_init()
{
  /* interrupt on recieve complete, transmit data register empty,
     enable reciever and transmitter */
  UCSR0B = (1<<RXCIE0) | (1<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0);
  /* 8 data bits */
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
  /* 19200 baud (cpu frequency is 16 MHz */
  UBRR0L = 51;

  rx_head = 0;
  rx_count = 0;
  tx_head = 0;
  tx_count = 0;
}

/* write chars in p to the usart, returns when data has been
   buffered */
void serial_write(uint8_t *p, uint8_t len)
{
  /* wait untill the transmit buffer is empty */
  while (tx_count > 0);

  /* push p into transmit buffer */
  for (uint8_t i = 0; i < len; i++) {
    tx_buffer[(tx_head + tx_count) % TX_BUFFER_SIZE] = p[i];
    tx_count++;
  }

  /* send data when usart is ready to recieve it */
  while (!(UCSR0A & (1<<UDRE0)));
  UDR0 = tx_buffer[tx_head];
}

/* interrupt on recieve complete */
ISR(USART_RX_vect)
{
  uint8_t c = UDR0;

  rx_buffer[(tx_head + tx_count) % RX_BUFFER_SIZE] = c;
  rx_count++;

  /* wait to data register is empty */
  //while (!(UCSR0A & (1<<UDRE0)));

  //UDR0 = ++c;
}

/* interrupt on data register empty */
ISR(USART_UDRE_vect)
{
  if (tx_count == 0)
    return;

  /* send next char in transmit buffer */
  uint8_t c = tx_buffer[tx_head];
  tx_head = (tx_head + 1) % TX_BUFFER_SIZE;
  tx_count--;
  UDR0 = c;
}
