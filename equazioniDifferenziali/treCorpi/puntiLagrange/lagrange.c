/*
  Questo programma studia il problema dei tre corpi ristretto, con due corpi di massa molto grande con la condizione di muoversi con orbite circolari attorno al centro di massa del sistema, è poi aggiunto un terzo corpo di massa molto più piccola che non influenza il moto degli altri due corpi.
  Il moto del sistema è studiato in un sistema di riferimento che ruota insieme alle due masse così che esse risultino stazionarie. Nelle equazioni differenziali del moto sono così aggiunti i termini della forza centrifuga e della forza di Coriolis.
  Sono state scelte unità di misura opportune per distanze e tempo così da ottenere pulsazione unitaria e distanza tra le due masse anch'essa unitaria.
  Si è definita MU = m2/m1+m2 con valori realistici per la terra
 */

/*
  Si integra usando Runge Kutta al 4 ordine
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MU 1.2151E-2

struct pianeta {
  double x;
  double y;
  double vx;
  double vy;
};

double calcR(double x, double y);
double phix(double x, double y, double vy);
double phiy(double x, double y, double vx);
struct pianeta runge4(struct pianeta p, double dt);
struct pianeta initPar(char *argv[]);

int main(int argc, char *argv[])
{
  double dt = 0.001, totalTime = 50;
  struct pianeta sonda;
  int nSteps, i;

  if (argc != 5){
    printf("Usage: ./nomefile x0 y0 vx0 vy0\n");
    exit(-9);
  }

  sonda = initPar(argv);

  nSteps = (int)(totalTime/dt + 0.5);

  for (i = 1; i < nSteps; i++){
    sonda = runge4(sonda, dt);
    printf("%lf %lf\n", sonda.x, sonda.y);
  }
  
  return 9;
}

/*
  FUNZIONI
 */

double calcR(double x, double y){
  //ritorna la distanza già elevata alla 3/2
  return pow(x*x + y*y, 1.5);
}

/***************************/

double phix(double x, double y, double vy){
  double R1, R2, fCoriolis, fCentrif, fGrav;

  R1 = calcR(x+MU, y);
  R2 = calcR(x-1+MU, y);

  fCoriolis = 2*vy;
  fCentrif = x;
  fGrav = -(1-MU)*(x+MU)/R1 - MU*(x-1+MU)/R2;
  
  return fCoriolis + fCentrif + fGrav;
}

/***************************/

double phiy(double x, double y, double vx){
  double R1, R2, fCoriolis, fCentrif, fGrav;

  R1 = calcR(x+MU, y);
  R2 = calcR(x-1+MU, y);

  fCoriolis = -2*vx;
  fCentrif = y;
  fGrav = -(1-MU)*y/R1 - MU*y/R2;
  
  return fCoriolis + fCentrif + fGrav;
}

/***************************/

struct pianeta runge4(struct pianeta p, double dt)
{
  struct pianeta pNew, d1, d2, d3, d4;

  d1.x = p.vx * dt;
  d1.y = p.vy * dt;
  d1.vx = phix(p.x, p.y, p.vy) * dt;
  d1.vy = phiy(p.x, p.y, p.vx) * dt;

  d2.x = (p.vx + 0.5 * d1.vx) * dt;
  d2.y = (p.vy + 0.5 * d1.vy) * dt;
  d2.vx = phix(p.x + 0.5 * d1.x, p.y + 0.5 * d1.y, p.vy + 0.5 * d1.vy) * dt;
  d2.vy = phiy(p.x + 0.5 * d1.x, p.y + 0.5 * d1.y, p.vx + 0.5 * d1.vx) * dt;

  d3.x = (p.vx + 0.5 * d2.vx) * dt;
  d3.y = (p.vy + 0.5 * d2.vy) * dt;
  d3.vx = phix(p.x + 0.5 * d2.x, p.y + 0.5 * d2.y, p.vy + 0.5 * d2.vy) * dt;
  d3.vy = phiy(p.x + 0.5 * d2.x, p.y + 0.5 * d2.y, p.vx + 0.5 * d2.vx) * dt;

  d4.x = (p.vx + d3.vx) * dt;
  d4.y = (p.vy + d3.vy) * dt;
  d4.vx = phix(p.x + d3.x, p.y + d3.y, p.vy + d3.vy) * dt;
  d4.vy = phiy(p.x + d3.x, p.y + d3.y, p.vx + d3.vx) * dt;

  pNew.x = p.x + (d1.x + 2 * d2.x + 2 * d2.x + d4.x) / 6.;
  pNew.y = p.y + (d1.y + 2 * d2.y + 2 * d2.y + d4.y) / 6.;
  pNew.vx = p.vx + (d1.vx + 2 * d2.vx + 2 * d2.vx + d4.vx) / 6.;
  pNew.vy = p.vy + (d1.vy + 2 * d2.vy + 2 * d2.vy + d4.vy) / 6.;
  
  return pNew;
}
/***************************/

struct pianeta initPar(char *argv[])
{
  struct pianeta p;

  p.x = atof(argv[1]);
  p.y = atof(argv[2]);
  p.vx = atof(argv[3]);
  p.vy = atof(argv[4]);

  return p;
}
/***************************/
