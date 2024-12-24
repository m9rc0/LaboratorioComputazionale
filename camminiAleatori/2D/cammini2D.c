#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
  Questo programma genera cammini aleatori in due dimensioni e stampa le posizioni a tempi prefissati 
 */


struct x{
  int x1;
  int x2;
};

struct x initPos(int x10, int x20);
void nextStep(struct x *pos);

int main()
{
  int seed, nsimul, nSimul = 200000, totalTime = 10000, i, j;
  struct x posizione;
  
  // inizializzo il generatore di numeri casuali
  seed = time(0);
  srand48(seed);

  for (i = 0; i < nSimul; i++)
    {
      posizione = initPos(0,0);


      for (j = 1; j <= totalTime; j++)
	{
	  nextStep(&posizione);

	  // condizioni per stampare su file 
	  if (j == 10)
	    {
	      printf("S %i T %i X1 %i X2 %i\n", i, j, posizione.x1, posizione.x2);
	    }
	  else if (j == 100)
	    {
	      printf("S %i T %i X1 %i X2 %i\n", i, j, posizione.x1, posizione.x2);
	    }
	  else if (j == 1000)
	    {
	      printf("S %i T %i X1 %i X2 %i\n", i, j, posizione.x1, posizione.x2);
	    }
	  else if (j == 10000)
	    {
	      printf("S %i T %i X1 %i X2 %i\n", i, j, posizione.x1, posizione.x2);
	    }
	}
    }

}

/**************FUNZIONI*************/

/******************************/

struct x initPos(int x10, int x20)
{
  struct x pos;
  pos.x1 = x10;
  pos.x2 = x20;

  return pos;
}

/******************************/

void nextStep(struct x *pos)
{
  double r;
  
  r = drand48();

  if (r < 0.25)
    {
      (*pos).x1 += 1;
    }
  else if (r < 0.5)
    {
      (*pos).x1 -= 1;
    }
  else if (r < 0.75)
    {
      (*pos).x2 += 1;
    }
  else
    {
      (*pos).x2 -= 1;
    }
}

/******************************/
