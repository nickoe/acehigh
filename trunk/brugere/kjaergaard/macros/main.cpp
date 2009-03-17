/*
 * $Id$
 */


/*
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
*/

#include <iostream>

using namespace std;

#define HPGL_INS(ins) (((uint8_t)ins[0])<<8 | (uint8_t)ins[1])

int main(void)
{
  cout << HPGL_INS("CR");
  cout << "\n";
  return 0;
}
