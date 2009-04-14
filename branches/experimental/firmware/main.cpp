/*
 * $Id$
 *
 * Noter her som skal dukke op på den anden side
 */

#include <avr/io.h>

#include "motor_ctrl.h"
#include "plotter.h"


uint16_t X = 0;     //Bruges til holde styr på, hvor vi er henne i koordinatsystemet
uint16_t Y = 0;

int main(void)
{
  MotorCtrl_Init();

  char ins[2];
  
  //Her skal vi indlæse data fra dataføder, forstå den m.m.
  
  
  switch(HPGL_INS(ins))
  {
    case HPGL_INS("LA"):                // Her behandles en absolut linje
      
      break;
    
    case HPGL_INS("LR"):                // Her behandles en relativ linje
      
      break;
    
    
    case HPGL_INS("CI"):                // Her behandles en cirkel
      int w = c;                        // Vinklen
      int c = 5;                        // Kordevinklen
      int r = 5;                        // Radius
      
      MotorCtrl_Lift();                 // Løfter pennen
      MotorCtrl_GotoRXY(r, 0, v);       // Relativt til startpunkt for cirkel (r,0)
      MotorCtrl_Lower();                // Sænker pennen
      
      while(w <= 360)
      {
        x = cos(w)*r;                   // x-koordinatet bestemmes
        y = sin(w)*r;                   // y-koordinatet bestemmes
        MotorCtrl_GotoXY(X+x, Y+y, v);  // x,y-koordinaterne sendes med hastigheden v
        w += c;                         // Kordevinklen lægges til vinklen w
      }
      
      /* Hvis vinklen v ikke går op i 360
      if(v != 360)
      {
        w -=c ;
        x = cos(w)*r;                   // x-koordinatet bestemmes
        y = sin(w)*r;                   // y-koordinatet bestemmes
        MotorCtrl_GotoXY(X+x+r, Y+y+0, v);
      }
      */
      
      MotorCtrl_Lift();                 // Løfter pennen
      MotorCtrl_GotoXY(X, Y, v);        // Tilbage til centrum
      
      
      break;
      
    default:
      //Hvis denne kode bliver afviklet kender vi ikke funktionen
  }
  
  return 0;
}

