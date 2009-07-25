/**
 * \file Communication library header for AceHigh
 *
 * $Id$
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__


/// Initialize serial communication
/**
 * Initializes serial communication and command buffering. The serial
 * interface is communicating using RS-232, at 9600 baud, 8N1 (8 data
 * bits, no parity, 1 stopbit).
 */
void serial_init(void);


/// Enable command processing
/**
 * Clears i/o buffers and enables command processing. Whenever a valid
 * command is recieved, the machine will act upon it.
 */
void serial_enable(void);


/// Disable command processing
void serial_disable(void);


/// Send a byte
/**
 * Sends a single char throuth the serial interface. The char will be
 * sent as soon as the interface is ready. Returns when the byte has
 * been buffered.
 *
 * \param c Char to send
 */
void serial_putc(char c);

/// Sends a C-style string
/**
 * Sends a character string through the serial interface. The string
 * will be sent as soon as the interface is ready. Returns when the
 * string has been buffered. The string must be null-terminated.
 *
 * \param s Pointer to C-style string to send
 */
void serial_puts(const char *s);

/// Sends a binary string
/**
 * Sends a binary string s of length len. The string will be sent as
 * soon as the interface is ready. Returns when the string has been
 * buffered.
 *
 * \param s Pointer to binary string to send
 * \param len Length of binary string
 */
void serial_putb(char *s, int len);

#endif /* __SERIAL_H__ */
