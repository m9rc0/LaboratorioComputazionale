#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* questo programma risolve numericamente le equazioni dell'oscillatore armonico con 4 metodi di integrazione diversi. Calcola ad ogni passo l'energia e stampa come output la quantità (E0-E)/E0. Lo scopo è controllare come cambia questa quantità durante tutto il corso dell'integrazione con un dt fissato. */

/* Per il metodo d'integrazione del mezzo passo si è scelto di trascurare il fatto che la velocità e la posizione sono calcolate ad istanti temporali diversi. */

struct phaseSpace {
  double x;
  double v;
};

double phi(double, double);
double energy(double w2, struct phaseSpace xandV);

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace central(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace passo(double w2, double dt, struct phaseSpace xandV);


struct phaseSpace inizPar (double, double);

int main (int argc, char *argv[]) {
  struct phaseSpace xandV[4], (*nextStep[4])() = {euler, cromer, central, passo};
  double w2=1, x0=2, v0=0, dt, time=100, E0[4], E[4];
  int nsteps, i, j;

  if (argc != 2){
    printf("Errore con l'inserimento del passo!\n");
    exit(0);
  }


  
  dt = atof(argv[1]);
  nsteps  = (int) (time / dt + 0.5);

  // inizializziamo tutto
  for ( i = 0; i < 3; i++){
    xandV[i] = inizPar (x0, v0);
  }

  //inizializzazione con eulero per il mezzo passo
  xandV[3].x = x0;
  xandV[3].v = v0 + 0.5 * phi(w2, x0) * dt;
    
  // calcolo le energie al tempo 0
  for (i = 0; i < 4; i++){
    E0[i] = energy(w2, xandV[i]);
  }
    
  // ciclo principale
  for (i=1; i<nsteps; i++) {
    printf("%lf ", dt * i);

    // faccio una iterazione per ogni metodo di integrazione
    for (j = 0; j<4 ; j++){
      xandV[j] = nextStep[j](w2, dt, xandV[j]);
      E[j] = energy(w2, xandV[j]);
      printf("%lf ", (E0[j]-E[j])/E0[j]);
    }
    printf("\n");
  } 
  
  return 0;
}

/* FUNZIONI  */

double phi(double w2, double x) {
  return -w2 * x;
}

/***************************/

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV){
  struct phaseSpace New;
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + xandV.v * dt;
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
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace New;
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + New.v * dt;
  return New;
}
/***************************/

struct phaseSpace central(double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace New;
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + (New.v + xandV.v)/2. * dt;
  return New;
}

/***************************/

struct phaseSpace passo(double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace New;
  //per le traiettorie non ci ponamo il problema che siano sfasate 
  
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + New.v * dt;
  return New;
}

/***************************/

