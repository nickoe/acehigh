void hpgl_line(int x1, int y1, int x2, int y2, float v) // Problem: Relativ absolut
{
/* Oversigt over hvad der skal med i koden
Beregn delta n_x og n_y

Beregn konstanten L/v

While_Begin
  Beregn tiden t_x1 og t_y1 med n_x=1 og n_y=1
  Lav to IF og en Else
While_End
*/
											// Givne størrelser
int x=1;									// Start skridt i x
int y=1;									// Start skridt i y

											// Beregning af variable
int dx = x2-x1;								// Her findes dx (delta n_x)
int dy = y2-y1;								// Her findes dy (delta n_y)
double k = (sqrt((x2-x1)^2+(y2-y1)^2))/v;	// Her beregnes konstanten L/v

int ins_x = 4;								// Indsæt konstant, så den bliver rigtigt
int ins_y = 8;								// Indsæt konstant, så den bliver rigtigt

/*Bemærkning
Her gemmer vi instruktionerne for retning
Vi laver else if, da hvis x2 er lig x1
(altså et lodret linie), så kan retningen ikke med
*/

if (x2 > x1)
  ins_x = 1;
else if (x2 < x1)
  ins_x = 2;
  
if (y2 > y1)
  ins_y = 4;
else if (y2 < y1)
  ins_y = 8;

while(x <= dx && y <= dy)					// Forløber sålænge x er mindre eller lig dx og y er mindre eller lig dy
{
  int time_x = x/dx*k;
  int time_y = y/dy*k;
  
  if (time_x < time_y)						// Starter udførelsen af tjek
  {
											// Her skal tiden time_x og retningen lægges i bufferen
	x++;									// Her lægger jeg en til x, så jeg kan beregne en ny time_x
  }

  else if (time_x == time_y)
  {
											// Her skal tiden time_x, time_y og retningerne lægges i bufferen
	x++;									// Her lægger jeg en til x, så jeg kan beregne en ny time_x
	y++;									// Her lægger jeg en til y, så jeg kan beregne en ny time_y
  }
  
  else
  {
											// Her skal tiden time_y og retningen lægges i bufferen
	y++;									// Her lægger jeg en til y, så jeg kan beregne en ny time_y
  }
}
}

