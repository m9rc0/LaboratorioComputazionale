#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define G 9.805
#define NINT 6

/*
  Questo programma integra le equazioni del moto del pendolo caotico e ne studia la sezione di poincare per multipli del periodi della forzante.
 */

struct phaseSpace
{
    double x;
    double v;
};

struct parametri {
  double gamma;
  double omega;
  double omBarra;
  double f0;
};

double forcePendulum(double x, double v, double t, struct parametri);
struct phaseSpace initPendulum(double x0, double v0);
struct parametri initPar (double gamma, double omega, double omBarra, double f0);
struct phaseSpace rungeKutta(double dt, double t, struct phaseSpace xAndV, struct parametri costanti);


int main()
{
  double x0 = M_PI/2., v0 = 0, dt, totalTime = 10000, gamma = 0.5, omega = 1, omBarra = 2./3., f0[NINT] ={0.9, 1.07, 1.15, 1.35, 1.47, 1.50};
  long numberOfSteps, i, j;

  struct phaseSpace xandV[NINT];
  struct parametri costanti[NINT];


  
  for (j = 0; j < NINT; j++) {
      xandV[j] = initPendulum (x0, v0);
      costanti[j] = initPar (gamma, omega, omBarra, f0[j]);
  }

  // si sceglie un sottomultiplo intero della forzante
  dt = 2 * M_PI / (omBarra * 10000);
  numberOfSteps = (long)(totalTime / dt + 0.5);

  for (i = 1; i < numberOfSteps; i++) {
    for (j = 0; j < NINT; j++) {
      xandV[j] = rungeKutta (dt, i * dt, xandV[j], costanti[j]);
      if (xandV[j].x > M_PI) xandV[j].x -= 2*M_PI;
      else if (xandV[j].x < -M_PI) xandV[j].x += 2*M_PI;

      // buttiamo i primi 50 secondi e campioniamo ad ogni periodo della forzante
      if ((i * dt > 50)&&(i % 10000 == 0))
	{
	  printf ("%lf %lf ", xandV[j].x, xandV[j].v);
	}
    }
     if ((i * dt > 50)&&(i % 10000 == 0)) printf ("\n");
  }

  return 9;
}


/*Funzioni*/
/****************************+*/

struct phaseSpace initPendulum(double x0, double v0)
{

    struct phaseSpace xandV;
    xandV.x = x0;
    xandV.v = v0;
    return xandV;
}

/****************************+*/

struct parametri initPar (double gamma, double omega, double omBarra, double f0) {
  struct parametri tutto;
  tutto.gamma = gamma;
  tutto.omega = omega;
  tutto.omBarra = omBarra;
  tutto.f0 = f0;
  return tutto;
}

/****************************+*/

double forcePendulum(double x, double v, double t, struct parametri costanti) {
  return -costanti.omega * costanti.omega * sin(x) - v * costanti.gamma + costanti.f0 * cos(costanti.omBarra * t);
}

/****************************+*/

struct phaseSpace rungeKutta(double dt, double t, struct phaseSpace xandV, struct parametri costanti) {
    struct phaseSpace new;
    double dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;

    dx1 = xandV.v * dt;
    dv1 = forcePendulum(xandV.x, xandV.v, t, costanti) * dt;
    dx2 = (xandV.v + 0.5 * dv1) * dt;
    dv2 = forcePendulum(xandV.x + 0.5 * dx1, xandV.v + 0.5 * dv1, t + 0.5 * dt, costanti) * dt;
    dx3 = (xandV.v + 0.5 * dv2) * dt;
    dv3 = forcePendulum(xandV.x + 0.5 * dx2, xandV.v + 0.5 * dv2, t + 0.5 * dt, costanti) * dt;
    dx4 = (xandV.v + dv3) * dt;
    dv4 = forcePendulum(xandV.x + dx3, xandV.v + dv3, t +  dt, costanti) * dt;

    new.x = xandV.x + (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6.;
    new.v = xandV.v + (dv1 + 2 * dv2 + 2 * dv3 + dv4) / 6.;

    return new;
}

/****************************+*/
