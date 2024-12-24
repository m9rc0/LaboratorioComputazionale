/*Si integra per diverse condizioni iniziali le equazioni del pendolo semplice*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define G 9.805

/*
  Questo programma integra le equazioni del moto del pendolo semplice con condizioni iniziali diverse per studiare le traiettorie nello spazio delle fasi. Si utilizza il metodo di runge kutta al quarto ordine.
 */

struct phaseSpace
{
    double x;
    double v;
};

double forcePendulum(double x);
struct phaseSpace initPendulum(double x0, double v0);
struct phaseSpace rungeKutta(double dt, struct phaseSpace xAndV);


int main()
{
  double x0, v0, dt = 0.001, totalTime = 10, stepx, stepy;
  long numberOfSteps, i, j;
  struct phaseSpace *xandV;
  int numberOfConditions, latox = 3, latoy = 20, count = 0;
  numberOfConditions = latox * latoy;

  // si variano di più le velocità per evitare che stesse traiettorie si ripetano più spesso, le x sono solo {-2Pi, 0, 2Pi}
  stepx =  4 * M_PI / ((double) latox-1);
  stepy =  6 * M_PI / ((double) latoy-1);
  
  // preparo dinamicamente l'array degli spazi delle fasi
  xandV = calloc(numberOfConditions, sizeof(struct phaseSpace));
  
  numberOfSteps = (long)(totalTime / dt);


  // inizializzo tutte le condizioni iniziali
  for (j = 0; j < latox; j++)
    {
      x0 = j * stepx - 2 * M_PI;
      for (i = 0; i < latoy; i++)
	{
	  v0 = i * stepy - 3 * M_PI;
	  xandV[count] = initPendulum(x0, v0);
	  count++;
	}

    }

  // Ciclo principale
  for (i = 0; i < numberOfSteps; i++)
    {
      for (j = 0; j < numberOfConditions; j++)
	{
	  xandV[j] = rungeKutta(dt, xandV[j]);
	  if (xandV[j].x > 2*M_PI)
	    {
	      xandV[j].x -= 4*M_PI;
	    } else if (xandV[j].x < -2*M_PI)
	    {
	      xandV[j].x += 4*M_PI;
	    }
	  printf("%lf %lf ", xandV[j].x, xandV[j].v);
	}
      printf("\n");
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

double forcePendulum(double x)
{
    return -G * sin(x);
}

/****************************+*/

struct phaseSpace rungeKutta(double dt, struct phaseSpace xandV)
{
    struct phaseSpace xandV_new;
    double dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;

    dx1 = xandV.v * dt;
    dv1 = forcePendulum(xandV.x) * dt;
    dx2 = (xandV.v + 0.5 * dv1) * dt;
    dv2 = forcePendulum(xandV.x + 0.5 * dx1) * dt;
    dx3 = (xandV.v + 0.5 * dv2) * dt;
    dv3 = forcePendulum(xandV.x + 0.5 * dx2) * dt;
    dx4 = (xandV.v + dv3) * dt;
    dv4 = forcePendulum(xandV.x + dx3) * dt;

    xandV_new.x = xandV.x + (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6.;
    xandV_new.v = xandV.v + (dv1 + 2 * dv2 + 2 * dv3 + dv4) / 6.;

    return xandV_new;
}

/****************************+*/
