/*
 * $Id$
 *
 * Noter her som skal dukke op på den anden side
 */


#include "plotter.h"

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include "motor.h"
#include "data.h"

/* pladsholdere til hvor vi er */
uint32_t X, Y;

int main(void)
{
  Data_Init();
  Motor_Init();
  X = 0;
  Y = 0;

  while (!Data_EOS()) {
    switch (Data_ReadIns()) {

    case HPGL_PU:
      {
	Motor_Lift();
      }
      break;

    case HPGL_PD:
      {
	Motor_Lower();
      }
      break;

    case HPGL_CI:
      {
	/* en cirkel */
	uint16_t r = Data_ReadParamI();

	uint8_t c = 5;
	/* kordevinkel, indlæses fra datastrømmen hvis den findes */
      
	if (Data_ParamExists())
	  c = (uint8_t)Data_ReadParamI();
        
	/* Vinkelpunkt sættes lig kordevinklen */
        uint16_t w = c;                        
      
        Motor_Lift();
	/* relativt til startpunkt for cirkel (r,0) */
        Motor_Move(r, 0, MAXSPEED);            
        Motor_Lower();
      
	while(w <= 360) {
	  int16_t tmp_x = cos(w*M_PI/180)*r;
	  int16_t tmp_y = sin(w*M_PI/180)*r;

	  /*
	    char msg[16];
	    sprintf(msg, "r=%d", r);
	    lcd_puts(msg);
	    cli();
	    while(1);
	  */

	  Motor_MoveTo(X+tmp_x, Y+tmp_y, MAXSPEED);
	  w += c;
	}
      
	Motor_Lift();
	Motor_MoveTo(X, Y, MAXSPEED);
      }
      break;


    case HPGL_PA:
      {
	// Plot Absolute
	// PA [X, Y [,...]] [;]
	while (Data_ParamExists()) {

	  X = Data_ReadParamI();
	  Y = Data_ReadParamI();
	
	  /* tjek om der tegnes - bevæg hurtigere når der ikke tegnes */
	  Motor_MoveTo(X, Y, MAXSPEED);
	}
      }
      break;


    case HPGL_PR:
      {
	while (Data_ParamExists()) {
	  /* Plot Relative */
	  uint16_t x = Data_ReadParamI();
	  uint16_t y = Data_ReadParamI();
      
	  /* Husk at udbygge, så pennen bevæger sig hurtigt, når der
	     ikke tegnes*/
	  Motor_Move(x, y, MAXSPEED);
      
	  X += x;
	  Y += y;
	}
      }
      break;

    default:
      {
	/* endnu ikke implementeret eller ukendt */
      }
      break;
    }
  }


 LOOP:
  while (1) {
  }

  return 0;
}
