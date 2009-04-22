/*
 * Motor controller
 *
 * Copyright (C) 2009  Kristian Kjærgaard
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * $Id$
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/* definitioner til motorstyringskredsen */
#define MCC_DDR        DDRA
#define MCC_PORT       PORTA
#define MCC_HALFFULL   0
#define MCC_DECAY      1
#define MCC_Y_CCW      2
#define MCC_ENABLE     3
#define MCC_Y_CLK      4
#define MCC_X_CLK      5
#define MCC_RESET      6
#define MCC_X_CCW      7


#define RES_X 0.14
#define RES_Y 1.0


#define activate_timer() (TIMSK |= 1<<OCIE0)
#define deactivate_timer() (TIMSK &= ~(1<<OCIE0))


/* pladholder til positionen */
uint32_t current_x = 0, current_y = 0;

/* timeren og tid vi er færdig på */
uint32_t tick_counter = 0;
uint32_t ticks = 0;

/* konstanter til hurtigere behandling */
long double k_x;
long double k_y;


/* flytter angivne koordinater, relativt */
void Motor_Move(int32_t x, int32_t y, double v)
{
  if (x == 0 && y == 0)
    return 0;

  /* udfør alle de beregninger vi kan mens vi venter */

  /* det tidspunkt vi er færdige på for x-aksen - forholdene RES_X og
     RES_Y skal passe, da den vi først er færdige med stopper
     behandlingen */
  uint64_t tmp_ticks = sqrt(x*x + y*y) / v;

  /* genvejskonstanterne */
  long double tmp_k_x = abs(x) * RES_X / tmp_ticks;
  long double tmp_k_y = abs(y) * RES_Y / tmp_ticks;

  /* vent så længe timeren kører */
  while (TIMSK & (1<<OCIE0));

  /* få retningen på plads */
  if (x < 0)
    MCC_PORT &= ~(1<<MCC_X_CCW);
  else
    MCC_PORT |= 1<<MCC_X_CCW;

  if (y < 0)
    MCC_PORT &= ~(1<<MCC_Y_CCW);
  else
    MCC_PORT |= 1<<MCC_Y_CCW;

  /* læg alle variable over i dem timeren bruger */
  current_x = 0;
  current_y = 0;
  ticks = tmp_ticks;
  k_x = tmp_k_x;
  k_y = tmp_k_y;

  /* start timeren */
  activate_timer();

  return 0;
}

/*
 * Tik-funktion til motorkontrollen
 *
 * Kaldes 500 gange i sekundet
 */
void tick(void)
{
  tick_counter++;

  uint32_t n_x = round(tick_counter * k_x);
  if (n_x > current_x) {
    /* næste skridt er større end nuværende skridt */
    current_x = n_x;
    MCC_PORT |= (1<<MCC_X_CLK);
  }

  uint32_t n_y = round(tick_counter * k_y);
  if (n_y > current_y) {
    /* næste skridt er større end nuværende skridt */
    current_y = n_y;
    MCC_PORT |= (1<<MCC_Y_CLK);
  }

  /* mindste høj-tid for l6208n */
  _delay_us(2);
  MCC_PORT &= ~((1<<MCC_X_CLK) | (1<<MCC_Y_CLK));
  
  if (tick_counter == ticks) {
    deactivate_timer();
    tick_counter = 0;
  }
}


ISR(TIMER0_COMP_vect)
{
  tick();
}


void Motor_Init(void)
{
  /* her skal vi sætte motorkontrolkredsen op */
  MCC_DDR = 0xff;

  /* genstart - klodset */
  MCC_PORT = 0;
  _delay_ms(10);
  MCC_PORT |= 1 << MCC_RESET;
  _delay_ms(10);

  /* aktiver */
  MCC_PORT |= 1 << MCC_ENABLE;


  /* timeren sættes op */
  /* timer-clock er f_osc/128 = 125 kHz, Clear Timer on Compare */
  TCCR0 = (1<<WGM01) | (1<<CS02) | (1<<CS00);
  /* tæl op til 249, så bliver frekvensen af timeren 500 Hz */
  OCR0 = 249;
 
  /* aktiver interrupt */
  sei();

  DDRE = 0xff;
}
