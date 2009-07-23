/*
 * $Id$
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__


/* Initializes serial communication and command buffering, and starts
 * acting when data i recieved. Return zero on succes.
 */
int serial_init(void);

void serial_putc(char c);


#endif /* __SERIAL_H__ */
