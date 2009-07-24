/*
 * Communication library for AceHigh
 *
 * $Id$
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__


/*
 * Initializes serial communication and command buffering, and starts
 * acting when data i recieved. Return zero on succes.
 *
 * The serial interface is communicating using RS-232, at 9600 baud,
 * 8N1.
 */
int serial_init(void);

/*
 * Sends a single char throuth the serial interface. The char will be
 * sent as soon as the interface is ready. Returns when the byte has
 * been buffered.
 */
void serial_putc(char c);

/*
 * Sends a character string through the serial interface. The string
 * will be sent as soon as the interface is ready. Returns when the
 * string has been buffered.
 */
void serial_puts(const char *s);


#endif /* __SERIAL_H__ */
