#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 
 */

struct phaseSpace
{
    double x;
    double v;
};

double phi(double w2, double x, double v, double l);
struct phaseSpace initOsc(double x0, double v0);
struct phaseSpace rungeKutta(double dt, double w2, double l, struct phaseSpace xAndV);


int main(int argc, char *argv[])
{
  double x0 = 1, v0, dt = 0.001, totalTime = 100, l, w2 = 9.;
  long numberOfSteps, i;
  struct phaseSpace xandV;

  if (argc != 3){
    printf("# Usage: ./smorzamento v0 gamma\n");
    printf("# ERRORE!");
    exit(-9);
  }

  v0 = atof(argv[1]);
  l = atof(argv[2]);

  printf("# Integrazione di un oscillatore armonico smorzato, prima colonna per i tempi, seconda per le posizioni e terza per velocità\n");
  printf("# x0 = %lf, v0 = %lf, gamma = %lf\n# total time = %lf, dt = %lf, w^2 = %lf\n", x0, v0, l, totalTime, dt, w2);
  
  numberOfSteps = (long)(totalTime / dt + 0.5);
  xandV = initOsc(x0, v0);
  printf ("%lf %lf %lf\n", 0., xandV.x, xandV.v);

  // Ciclo principale

  for (i=1; i<numberOfSteps; i++) {
    xandV = rungeKutta (dt, w2, l, xandV);
    printf ("%lf %lf %lf\n", i*dt, xandV.x, xandV.v);
  }
  
  return 0;
}


/*Funzioni*/
/****************************+*/

struct phaseSpace initOsc(double x0, double v0)
{

    struct phaseSpace xandV;
    xandV.x = x0;
    xandV.v = v0;
    return xandV;
}

/****************************+*/

double phi(double w2, double x, double v, double l)
{
    return -w2 * x - l * v;
}

/****************************+*/

struct phaseSpace rungeKutta(double dt, double w2, double l, struct phaseSpace xandV)
{
    struct phaseSpace xandV_new;
    double dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;

    dx1 = xandV.v * dt;
    dv1 = phi(w2, xandV.x, xandV.v, l) * dt;
    dx2 = (xandV.v + 0.5 * dv1) * dt;
    dv2 = phi(w2, xandV.x + 0.5*dx1, xandV.v + 0.5*dv1, l) * dt;
    dx3 = (xandV.v + 0.5 * dv2) * dt;
    dv3 = phi(w2, xandV.x + 0.5*dx2, xandV.v + 0.5*dv2, l) * dt;
    dx4 = (xandV.v + dv3) * dt;
    dv4 = phi(w2, xandV.x + dx3, xandV.v + dv3, l) * dt;

    xandV_new.x = xandV.x + (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6.;
    xandV_new.v = xandV.v + (dv1 + 2 * dv2 + 2 * dv3 + dv4) / 6.;

    return xandV_new;
}

/****************************+*/
