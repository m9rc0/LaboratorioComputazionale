#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Questo programma studia il comportamento del metodo di eulero e di eulero-cromer con l'oscillatore armonico dove è artificialmente aggiunto rumore ad ogni passo*/

/* Il rumore è aggiunto arrotondando le cifre di ogni risultato a 2 cifre decimali */

struct phaseSpace {
  double x;
  double v;
};

double phi(double, double);
double energy(double w2, struct phaseSpace xandV);

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV, int noise);
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV, int noise);

struct phaseSpace inizPar (double, double);


int main (int argc, char *argv[]) {
  struct phaseSpace xandV[4], (*nextStep[4])() = {euler, euler, cromer, cromer};
  double w2=3, x0=2, v0=0, dt, time=20, rapp[4], E0;
  int nsteps, i, j;

  if (argc != 2){
    printf("Errore con l'inserimento del passo!\n");
    exit(0);
  }
  
  dt = atof(argv[1]);
  nsteps  = (int) (time / dt + 0.5);


  
  // inizializziamo tutto
  for (i = 0; i < 4; i++){
    xandV[i] = inizPar (x0, v0);
  }
  E0 = energy(w2, xandV[0]);
  
  // ciclo principale
  for (i = 1; i < nsteps; i++)
    {
      printf("%lf ", dt*i);

      for (j = 0; j < 4; j++)
	{
	  xandV[j] = nextStep[j](w2, dt, xandV[j], j % 2);
	  rapp[j] = (energy(w2, xandV[j]) - E0)/E0; 
	  printf("%lf ", rapp[j]);
	}
      printf("\n");
    }


}

/* FUNZIONI  */

double phi(double w2, double x) {
  return -w2 * x;
}

/***************************/

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV, int noise){
  struct phaseSpace New;

  if (noise == 0)
    {
      New.v = xandV.v + phi(w2, xandV.x) * dt;
      New.x = xandV.x + xandV.v * dt;
    }
  if (noise == 1)
    {
      New.v = roundf((xandV.v + phi(w2, xandV.x) * dt)*100)/100.;
      New.x = roundf((xandV.x + xandV.v * dt)*100)/100.;      
    }
  return New;
}

/***************************/
struct phaseSpace inizPar (double x, double v) {
  struct phaseSpace inizio;
  inizio.x = x;
  inizio.v = v;
  return inizio;
}

/***************************/
double energy(double w2, struct phaseSpace xandV) {
  double K, V;
  K = 0.5 * xandV.v * xandV.v;
  V = 0.5 * w2 * xandV.x * xandV.x;
  return K + V;
}
/***************************/
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV, int noise) {
  struct phaseSpace New;
  if (noise == 0)
    {
      New.v = xandV.v + phi(w2, xandV.x) * dt;
      New.x = xandV.x + New.v * dt;
    }
  if (noise == 1)
    {
      New.v = roundf((xandV.v + phi(w2, xandV.x) * dt)*100)/100.;
      New.x = roundf((xandV.x + New.v * dt)*100)/100.;      
    }
  return New;
}
/***************************/
