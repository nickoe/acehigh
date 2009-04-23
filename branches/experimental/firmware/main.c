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

#include "motor.h"
#include "data.h"
#include "lcd.h"

int main(void)
{
  lcd_init(LCD_DISP_ON);
  Data_Init();
  Motor_Init();

  DDRE = 0xff;

while (!Datafeeder_EOS())
  {
    switch(Data_ReadIns())
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
      uint16_t r = (uint16_t)Data_ReadParamF();
      uint8_t c = 5;
      /* kordevinkel, indlæses fra datastrømmen hvis den findes */
      
      if (Data_ParamExists())
        c = (uint8_t)Data_ReadParamF();              // Hvis kordevinklen eksisterer, hentes den
        
        uint16_t w = c;                        // Vinkelpunkt sættes lig kordevinklen
      
        MotorCtrl_Lift();
        Motor_Move(r, 0, MAXSPEED);            // relativt til startpunkt for cirkel (r,0)
        MotorCtrl_Lower();
      
      while(w <= 360)
      {
        X = X+r;
        Y = Y+0;
        
        uint16_t x = cos(w)*r;                   // x-koordinatet bestemmes
        uint16_t y = sin(w)*r;                   // y-koordinatet bestemmes
        Motor_Move(X+x, Y+y, MAXSPEED);          // x,y-koordinaterne sendes med hastigheden v
        w += c;                                  // Kordevinklen lægges til vinklen w
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
      Motor_Goto(X, Y, MAXSPEED);                   // Tilbage til centrum
    }
    break;
    
    
    case HPGL_INS("PA"):
    {
      // Plot Absolute
      // PA [X, Y [,...]] [;]
     
      X = (uint16_t)Data_ReadParamF();             // Henter x-koordinat
      Y = (uint16_t)Data_ReadParamF();             // Henter y-koordinat
      Motor_MoveTo(X, Y, MAXSPEED);                // Husk at udbygge, så pennen bevæger sig hurtigt, når der ikke tegnes
    }
    break;
    
    case HPGL_INS("PR"):
    {
      /* Plot Relative */
      uint16_t x = (uint16_t)Data_ReadParamF();
      uint16_t y = (uint16_t)Data_ReadParamF();
      
      Motor_Move(x, y, MAXSPEED);
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

  while (1);

  return 0;
}


