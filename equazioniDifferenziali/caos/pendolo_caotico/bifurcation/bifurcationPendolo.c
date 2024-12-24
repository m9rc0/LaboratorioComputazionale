/*
  si studia il diagramma di biforcazione di un pendolo caotico (con forzante sinusoidale), salvando la velocità a diversi periodi della forzante, per diversi moduli di essa. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define G 9.805

struct phaseSpace
{
    double x;
    double v;
};

struct param
{
    double omega;
    double omega1;
    double gamma;
    double f0;
};

double forcePendulum(double x, double v, double t, struct param tutto);
struct phaseSpace initCond(double x0, double v0);
struct param initParam(double omega, double omega1, double gamma, double f0);
struct phaseSpace runge4(struct phaseSpace xandV, struct param tutto, double t, double dt);

int main()
{
    struct phaseSpace xandV;
    struct param tutto;
    double gamma = 0.5, omega = 1., omega1 = 2. / 3., x0=M_PI/2., v0 = 0.,
      f0 = 0.5, dt, totalTime = 500, df = 0.0005, tempx, period;

    long numberOfSteps, i, j, numberOfParams;
    int side;

    
    tutto = initParam(omega, omega1, gamma, f0);
    numberOfParams = (long)((1.7 - 0.5) / df);
    period = 2. * M_PI / omega1;

    // scelgo passo che sia un sottomultiplo intero del periodo della forzante
    dt = period / 1000.;
    numberOfSteps = (long)(totalTime / dt);

    for (i = 0; i < numberOfParams; i++)
      {
	f0 += df;
	tutto = initParam(omega, omega1, gamma, f0);
	xandV = initCond(x0, v0);

	for (j = 0; j < numberOfSteps; j++)
	  {
	    tempx = xandV.x;
	    xandV = runge4(xandV, tutto, j*dt, dt);

	    // rinormalizzo le posizioni
	    if (xandV.x > M_PI)
	      {
		xandV.x -= 2 * M_PI;
	      }
	    else if (xandV.x < - M_PI)
	      {
		xandV.x += 2 * M_PI;
	      }

	    if ((j % 1000 == 0) && (dt * j > 250))
	      {
		printf("%lf %lf\n", f0, xandV.v);
	      }
	    
	  }
      }
    

    
    return 0;
}

/*********************************/

double forcePendulum(double x, double v, double t, struct param tutto)
{
    double fPendolo, fAria, fForzata;
    fPendolo = -tutto.omega * tutto.omega * sin(x);
    fAria = -tutto.gamma * v;
    fForzata = tutto.f0 * cos(tutto.omega1 * t);
    // printf("%lf %lf %lf\n", fPendolo, fAria, fForzata);
    return fPendolo + fAria + fForzata;
}

/*********************************/

struct phaseSpace initCond(double x0, double v0)
{

    struct phaseSpace xandV;
    xandV.x = x0;
    xandV.v = v0;
    return xandV;
}

/*********************************/

struct param initParam(double omega, double omega1, double gamma, double f0)
{
    struct param tutto;
    tutto.omega = omega;
    tutto.omega1 = omega1;
    tutto.gamma = gamma;
    tutto.f0 = f0;
    return tutto;
}

/*********************************/

struct phaseSpace runge4(struct phaseSpace xandV, struct param tutto, double t, double dt)
{
    struct phaseSpace xandV_New;
    double dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;

    dx1 = xandV.v * dt;
    dv1 = forcePendulum(xandV.x, xandV.v, t, tutto) * dt;

    dx2 = (xandV.v + 0.5 * dv1) * dt;
    dv2 = forcePendulum(xandV.x + 0.5 * dx1, xandV.v + 0.5 * dv1, t + 0.5 * dt, tutto) * dt;

    dx3 = (xandV.v + 0.5 * dv2) * dt;
    dv3 = forcePendulum(xandV.x + 0.5 * dx2, xandV.v + 0.5 * dv2, t + 0.5 * dt, tutto) * dt;

    dx4 = (xandV.v + dv3) * dt;
    dv4 = forcePendulum(xandV.x + dx3, xandV.v + dv3, t + dt, tutto) * dt;

    xandV_New.x = xandV.x + (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6.;
    xandV_New.v = xandV.v + (dv1 + 2 * dv2 + 2 * dv3 + dv4) / 6.;

    return xandV_New;
}

/*********************************/
