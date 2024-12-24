#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct phaseSpace {
  double x;
  double v;
};

double phi(double, double);
double energy(double w2, struct phaseSpace xandV);

struct phaseSpace Euler(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace passo(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace central(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV);

struct phaseSpace inizPar (double, double);

int main () {
  struct phaseSpace xandV[4];
  double w2=1, x0=2, v0=0, dt = 0.01, time=100;
  int nsteps, i, j;

  nsteps  = (int) (time / dt + 0.5);

  // inizializziamo tutto
  for ( i = 0; i < 3; i++){
    xandV[i] = inizPar (x0, v0);
  }

  //inizializzazione con eulero per il mezzo passo
    xandV[3].x = x0;
    xandV[3].v = v0 + 0.5 * phi(w2, x0) * dt;

  // ciclo principale
  for (i=1; i<nsteps; i++) {
    printf("%lf ", dt * i);
    
    // eulero 
    xandV[0] = Euler(w2, dt, xandV[0]);
    printf("%lf %lf ", xandV[0].x, xandV[0].v);
    
    // cromer
    xandV[1] = cromer(w2, dt, xandV[1]);
    printf("%lf %lf ", xandV[1].x, xandV[1].v);
    
    // punto centrale 
    xandV[2] = central(w2, dt, xandV[2]);
    printf("%lf %lf ", xandV[2].x, xandV[2].v);
    
    // mezzo passo 
    xandV[3] = passo(w2, dt, xandV[3]);
    printf("%lf %lf\n", xandV[3].x, xandV[3].v);
  } 
  
  return 0;
}

/* FUNZIONI  */

double phi(double w2, double x) {
  return -w2 * x;
}

/***************************/

struct phaseSpace Euler(double w2, double dt, struct phaseSpace xandV){
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
