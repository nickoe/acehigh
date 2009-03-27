/*
 * $Id: main.cpp 191 2009-03-17 09:03:27Z kkjaergaard $
 */

#include <avr/io.h>

#include "motor_ctrl.h"

int main(void)
{
  MotorCtrl_Init();

  return 0;
}
