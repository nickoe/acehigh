/*
 * Note om parameterindlæsning
 *
 * Gyldige parametre er heltal mellem -2^30 og 2^30-1, heltal mellem
 * -32768 og 32767, decimaltal mellem -2^30 og 2^30-1, heltal mellem
 * -32768 og 32767 (tal uden for interval afrunder til nærmeste tal i
 * interval)
 *
 * Parametre er adskilt af mellemrum eller komma (ASCII)
 */

//#include "datafeeder.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>



using namespace std;

ifstream file("eksempel.hpgl");

#define HPGL_INS(ins) (((uint8_t)ins[0])<<8 | (uint8_t)ins[1])

/*
 * Returnerer næste byte fra datastrømmen
 */
uint8_t get_next_byte()
{
  uint8_t c;
  file >> c;
  if (c == NULL)
    return 0;
  return c;
}

/* hjælper til når der skal portes */
#define Datafeeder_GetNextByte get_next_byte

/* returnerer SAND hvis vi er nået til filenden
 */
bool Datafeeder_EOS()
{
  return file.eof();
}






/* pladsholder til nuværende byte */
uint8_t current_byte = 0;

/* maksimal parameterstørrelse */
#define PARAM_SIZE 12


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
  
  while (!file.eof())
  {
    uint16_t ins = get_next_ins();
    
    if (ins == 0)
      return 0;

    printf("Næste instruktion: %c%c (%d)\n", (uint8_t)(ins>>8), (uint8_t)ins, ins);

    while (param_exists())
    {
      printf("Parameter: %f\n", get_next_param());
    }

    printf("\n\n");
  }

  return 0;
}
