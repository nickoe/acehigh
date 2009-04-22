/*
 * $Id$
 *
 * Noter her som skal dukke op på den anden side
 */

#include <avr/io.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "motor_ctrl.h"
#include "datafeeder.h"
#include "plotter.h"


/* hastighedskonstanter til at tegne og flytte tegneren */
#define DRAWINGSPEED 0.5
#define RAPIDMOVESPEED 0.8


/* pladsholder til tegnehovedets koordinatet */
uint16_t X = 0; 
uint16_t Y = 0;

/* pladsholder til nuværende byte i identifikationen */
uint8_t current_byte = 0;

int main(void)
{
  lcd_init(LCD_DISP_ON);
  MotorCtrl_Init();
  Datafeeder_Init();

  /* Her skal vi indlæse data fra dataføder, forstå den m.m. */
  
  while (!Datafeeder_EOS())
  {
    switch(get_next_ins())
    {
    case HPGL_INS("PU"): /* pen up */
      MotorCtrl_Lift();
    break;


    case HPGL_INS("PD"): /* pen down */
      MotorCtrl_Lower();
    break;


    case HPGL_INS("CI"):
    {
      /* en cirkel */
      uint16_t r = (uint16_t)get_next_param();
      uint8_t c = 5;
      /* kordevinkel, indlæses fra datastrømmen hvis den findes */
      
      if (param_exists())
        c = (uint8_t)get_next_param();              // Hvis kordevinklen eksisterer, hentes den
        
        uint16_t w = c;                             // Vinkelpunkt sættes lig kordevinklen
      
        MotorCtrl_Lift();
        MotorCtrl_GotoRXY(r, 0, MAXSPEED);          // relativt til startpunkt for cirkel (r,0)
        MotorCtrl_Lower();
      
      while(w <= 360)
      {
        X = X+r;
        Y = Y+0;
        
        uint16_t x = cos(w)*r;                      // x-koordinatet bestemmes
        uint16_t y = sin(w)*r;                      // y-koordinatet bestemmes
        MotorCtrl_GotoRXY(X+x, Y+y, MAXSPEED);      // x,y-koordinaterne sendes med hastigheden v
        w += c;                                     // Kordevinklen lægges til vinklen w
      }
      
      /* Hvis vinklen v ikke går op i 360
	 if(v != 360)
	 {
	 w -=c ;
	 x = cos(w)*r;                                    // x-koordinatet bestemmes
	 y = sin(w)*r;                                    // y-koordinatet bestemmes
	 MotorCtrl_GotoXY(X+x+r, Y+y+0, v);
	 }
      */
      
      MotorCtrl_Lift();                             // Løfter pennen
      MotorCtrl_GotoXY(X, Y, MAXSPEED);             // Tilbage til centrum
    }
    break;
    
    
    case HPGL_INS("PA"):
    {
      // Plot Absolut
      // PA [X, Y [,...]] [;]
      while(param_exits())                          // Tjekker om der er flere koordinatsæt, hvis ikke break; ellers 
      {
        x = (uint16_t)get_next_param();             // Henter x-koordinat
        y = (uint16_t)get_next_param();             // Henter y-koordinat
        MotorCtrl_GotoRXY(X-x, Y-y, MAXSPEED);      // Husk at udbygge, så pennen bevæger sig hurtigt, når der ikke tegnes
        
        /* Sørger for at vi ved hvor vi er */
        X += x;
        Y += y;
      }
    }
    break;
    
    case HPGL_INS("PR"):
    {
      /* Plot Relativ */
      uint16_t x = (uint16_t)get_next_param();
      uint16_t y = (uint16_t)get_next_param();
      
      MotorCtrl_GotoRXY(x, y, MAXSPEED);
      /* Husk at udbygge, så pennen bevæger sig hurtigt, når der ikke tegnes*/
      
      X += x;
      Y += y;
    }
    break;
    
    default:
      /* ukendt/ikke-implementeret instruktion */
      break;
    }
  }  

  return 0;
}
