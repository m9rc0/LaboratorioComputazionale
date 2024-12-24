#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define G 9.805
#define NINT 6

/*
  Questo programma integra le equazioni del moto del pendolo con perno che si muove verticalmente con moduli della forzante diversi per studiare le traiettorie nello spazio delle fasi. Si utilizza il metodo di runge kutta al quarto ordine.
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
  double g0;
};

double forcePendulum(double x, double v, double t, struct parametri);
struct phaseSpace initPendulum(double x0, double v0);
struct parametri initPar (double gamma, double omega, double omBarra, double g0);
struct phaseSpace rungeKutta(double dt, double t, struct phaseSpace xandV, struct parametri costanti);


int main()
{
  double x0 = M_PI/2., v0 = 0, dt, totalTime = 100, gamma = 0.2, omega = 1, omBarra = 2./3., g0, dg = 0.0005;
  long numberOfSteps, i;
  struct phaseSpace xandV;
  struct parametri costanti;

  dt = 2*M_PI / (omBarra * 10000);
  numberOfSteps = (long)(totalTime / dt + 0.5);

  for (g0 = 1.10; g0 < 1.80; g0 += dg) {
    xandV = initPendulum (x0, v0);
    costanti = initPar (gamma, omega, omBarra, g0);
    for (i = 1; i < numberOfSteps; i++) {
      xandV = rungeKutta(dt, i*dt, xandV, costanti);
      if ((fabs(xandV.v) > 0.01)&&(i % 10000 == 0)) printf ("%lf %lf\n", g0, xandV.v);
    }
  }
  
  return 0;
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

struct parametri initPar (double gamma, double omega, double omBarra, double g0) {
  struct parametri tutto;
  tutto.gamma = gamma;
  tutto.omega = omega;
  tutto.omBarra = omBarra;
  tutto.g0 = g0;
  return tutto;
}

/****************************+*/

double forcePendulum(double x, double v, double t, struct parametri costanti) {
  double w2 = costanti.omega * costanti.omega;
  double forzante = costanti.g0 * cos(costanti.omBarra * t);
  double attrito = - costanti.gamma * v;
  double FTOTALE = - sin(x) * (w2 + forzante) + attrito;
  return FTOTALE;
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
