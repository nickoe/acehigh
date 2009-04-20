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

extern "C"{
#include "lcd.h"
}


/* maksimal parameterstørrelse */
#define PARAM_SIZE 12

/* hastighedskonstanter til at tegne og flytte tegneren */
#define DRAWINGSPEED 0.5
#define RAPIDMOVESPEED 0.8


/* pladsholder til tegnehovedets koordinatet */
uint16_t X = 0; 
uint16_t Y = 0;

/* pladsholder til nuværende byte i identifikationen */
uint8_t current_byte = 0;


/*
 * Springer frem til og returnerer næste instruktion. Alt indtil næste
 * instruktion springes over. Der tjekkes ikke om instruktionen er
 * gyldig.
 */
uint16_t get_next_ins()
{
  uint8_t ins[2];

  /* fortsæt indtil vi har et bogstav */
  while (!isalpha(current_byte))
  {
    if (Datafeeder_EOS())
      return 0;
    current_byte = Datafeeder_GetNextByte();
  }

  /* gem bogstav og tag næste byte */
  ins[0] = current_byte;
  if (Datafeeder_EOS())
    return 0;
  current_byte = Datafeeder_GetNextByte();
  
  if (isalpha(current_byte))
  {
    /* næste byte er også bogstav, og instruktionen er syntaktisk set
       gyldig */
    ins[1] = current_byte;

    if (Datafeeder_EOS())
      current_byte = 0;
    else
      current_byte = Datafeeder_GetNextByte(); /* husk at rulle frem til
						byten efter det vi har
						behandlet */
    return HPGL_INS(ins);
  }

  /* fejl i formatet */

  return 0;
}

/*
 * Returnerer sand hvis der findes flere parametre end dem der
 * allerede er identificeret
 */
bool param_exists()
{
  while (true)
  {
    /* hvis vi er på et tal er vi i starten af en parameter */
    if (isdigit(current_byte))
      return true;

    /* vi må sikre os at vi ikke springer over en instruktion - hvis
       vi har et bogstav, er vi igang med at indlæse en instruktion */
    if (isalpha(current_byte))
      return false;

    /* tegnet er hverken tal eller bogstav og er ikke en del af en
       parameter (f.eks. punktum), derfor kan vi læse videre */

    /* EKSTRA TJEK HER!!! */

    /* husk at springe ud af løkken igen ... byg tjek ind i
       dataføderen */
    if (Datafeeder_EOS())
      return false;

    current_byte = Datafeeder_GetNextByte();
  }
}

/*
 * Returnerer næste parameter som decimaltal
 */
double get_next_param()
{
  uint8_t param[PARAM_SIZE]; /* plads til parameter */

  uint8_t n = 0;

  /* denne løkke kører så længe der indlæses bytes som er gyldige som
     parametertegn */
  while (n < PARAM_SIZE)
  {
    /* tjek om byten er en gyldig værdi - hvis ikke, så hvad? gyldige
       bytes er tal eller punktum */
    if (isdigit(current_byte) || current_byte == 0x2e)
    {
      param[n] = current_byte;
    }

    /* mellemrum og komma afslutter parameteren, semikolon afslutter
       instruktionen, andre tegn i vejen afslutter også */
    else
    {
      /* parameteren er slut */
      break;
    }

    n++;

    /* findes der mere data i strømmen */ 
    if (Datafeeder_EOS())
    {
      current_byte = 0;
      break;
    }

    /* indlæs næsten bytes fra dataføderen */
    current_byte = Datafeeder_GetNextByte();
  }

  /* denne løkke fylder resten af parameterens pladser med
     null-bytes */
  while (n < PARAM_SIZE)
  {
    param[n] = 0;
    n++;
  }

  return atof((char*)param);
}


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
        c = (uint8_t)get_next_param();
      
      uint16_t w = c;
      
      MotorCtrl_Lift();
      MotorCtrl_GotoRXY(r, 0, RAPIDMOVESPEED);      // relativt til startpunkt for cirkel (r,0)
      MotorCtrl_Lower();
      
      while(w <= 360)
      {
        uint16_t x = cos(w)*r;                      // x-koordinatet bestemmes
        uint16_t y = sin(w)*r;                      // y-koordinatet bestemmes
        MotorCtrl_GotoXY(X+x, Y+y, DRAWINGSPEED);   // x,y-koordinaterne sendes med hastigheden v
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
      MotorCtrl_GotoXY(X, Y, RAPIDMOVESPEED);       // Tilbage til centrum
    }
    break;
    
    case HPGL_INS("PA"):
    {
      /* Plot Absolut*/
      X = (uint16_t)get_next_param();
      Y = (uint16_t)get_next_param();
      
      MotorCtrl_GotoXY(X, Y, DRAWINGSPEED);
      /* Husk at udbygge, så pennen bevæger sig hurtigt, når der ikke tegnes*/
    }
    break;
    
    case HPGL_INS("PR"):
    {
      /* Plot Relativ*/
      uint16_t x = (uint16_t)get_next_param();
      uint16_t y = (uint16_t)get_next_param();
      
      MotorCtrl_GotoRXY(x, y, DRAWINGSPEED);
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
