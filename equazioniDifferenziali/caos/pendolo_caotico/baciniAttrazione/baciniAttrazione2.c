
/*
  Si studiano i bacini di attrazione per il pendolo caotico, con tempo di integrazione variabile
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

int main(int argc, char *argv[])
{
    struct phaseSpace xandV;
    struct param tutto;
    double gamma = 0.5, omega = 1., omega1 = 2. / 3., x0, v0,
           f0 = 1.47, dt = 0.01, totalTime;
    double **risultati;
    long numberOfSteps, i, j, k;
    int side;
    FILE *nero ,*giallo;


    if (argc != 5)
      {
	printf("Usage: totalTime side filenero.txt filegiallo.txt\n");
	printf("Eseguire di nuovo");
	exit(-9);
      }

   
    totalTime = atof(argv[1]);
    side = atoi(argv[2]);
    numberOfSteps = (long)(totalTime / dt);
    //    printf("#NumberOfSteps = %ld\n", numberOfSteps);
    printf("# totalTime = %.1lf, side = %i, gamma = %.1lf, omega = %.1lf\n# omega1 = %.1lf, f0 = %.1lf, dt = %lf\n", totalTime, side, gamma, omega, omega1, f0, dt);

    
    // apro i file
    nero = fopen(argv[3], "w");
    giallo = fopen(argv[4], "w");

    printf("# Nomi file:\n# %s\n# %s\n\n", argv[3], argv[4]);
    
    if ((nero == NULL) || (giallo == NULL))
      {
	printf("Errore con l'apertura del file\n");
	exit(-7);
      }
    

    tutto = initParam(omega, omega1, gamma, f0);




     // ciclo principale
    for (i = 0; i < side + 1; i++)
    {
        x0 = -M_PI + i * (2 * M_PI / side);
        for (j = 0; j < side + 1; j++)
        {
            v0 = -M_PI + j * (2 * M_PI / side);
            xandV = initCond(x0, v0);
            for (k = 1; k < numberOfSteps; k++)
            {
                xandV = runge4(xandV, tutto, k * dt, dt);
            }
            if (xandV.v >= 0)
            {
	      fprintf(giallo, "%lf %lf\n", x0, v0);
            }
            else
            {
	      fprintf(nero, "%lf %lf\n", x0, v0);
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
