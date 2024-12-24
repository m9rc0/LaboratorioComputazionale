#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define G 9.805
#define RUNGE 0
#define VERLET 1

/*Questo programma integra le equazioni del pendolo semplice per ampiezze diverse e ne calcola il periodo delle oscillazioni. Le confronta poi con il periodo stimato approssimando il sistema con un oscillatore armonico*/

/*
  Si integrano le equazioni differenziali con metodo di verlet autopartente o runge kutta al secondo ordine
 */

struct phaseSpace
{
    double x;
    double v;
};

typedef struct phaseSpace (*func)(double, struct phaseSpace);

// Prototipi delle funzioni
int readInt(char *printMessage);
double readDouble(char *printMessage);
func getFunction(void);
double energy(struct phaseSpace xAndV);
double forcePendulum(double x);
struct phaseSpace initPendulum(double x0, double v0);

struct phaseSpace rungeKutta(double dt, struct phaseSpace xAndV);
struct phaseSpace verlet_aut(double dt, struct phaseSpace xAndV);

int main()
{
    double x0 = 0, v0 = 0, dt = 0.001, totalTime = 20,
           period, xOld, time_temp, errorPercent;
    long numberOfSteps, i, j;
    struct phaseSpace xAndV, (*nextStep)();
    int count = 0;


    nextStep = getFunction();

    numberOfSteps = (long)(totalTime / dt);
    printf("# dt = %g tempo totale = %g\n", dt, totalTime);
    printf("# numero passi = %ld\n", numberOfSteps);

    for (j = 1; j <= 180; j++)
      {
        // si parte da mezzo grado perché oscillazioni di 0 gradi non hanno senso
        period = 0.;
        count = 0;
        x0 = 0.5 * j;
	// le oscillazioni sono stampate in gradi
        printf("%.1lf ", x0);
        x0 *= (M_PI / 180);

        xAndV = initPendulum(x0, v0);

        // Ciclo principale
        time_temp = 0;
        for (i = 1; i <= numberOfSteps; i++)
	  {
            xOld = xAndV.x;
            xAndV = nextStep(dt, xAndV);

            if ((xOld <= 0) && (xAndV.x >= 0))
	      {
		if (time_temp != 0)
		  {
		    // in questo modo non si cont la mezza oscillazione iniziale
		    period += (((double)i - 0.5) * dt - time_temp);
		    count++;
		  }
                time_temp = ((double)i - 0.5) * dt;
	      }
	  }
        period /= (double)count;
        errorPercent = 100 * fabs(period - 2 * M_PI / sqrt(G)) / period;
        printf("%lf %i\n", errorPercent, count);
      }
    
    return 0;
}

// FUNZIONI

int readInt(char *printMessage)
{
    int inputData;
    printf("# %s\n", printMessage);
    fflush(stdout);
    scanf("%i", &inputData);
    return inputData;
}

/****************************+*/

double energy(struct phaseSpace xAndV)
{
    // calculates kinetic and potential energy
    return 0.5 * xAndV.v * xAndV.v + G * (1 - cos(xAndV.x));
}

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

struct phaseSpace rungeKutta(double dt, struct phaseSpace xAndV)
{
    struct phaseSpace xAndV_new;
    double dx, dv;

    dx = xAndV.v * dt;
    dv = forcePendulum(xAndV.x) * dt;

    xAndV_new.x = xAndV.x + (xAndV.v + 0.5 * dv) * dt;
    xAndV_new.v = xAndV.v + forcePendulum(xAndV.x + 0.5 * dx) * dt;

    return xAndV_new;
}

/****************************+*/

struct phaseSpace verlet_aut(double dt, struct phaseSpace xAndV)
{
    struct phaseSpace xAndV_new;

    xAndV_new.x = xAndV.x + xAndV.v * dt +
                  0.5 * forcePendulum(xAndV.x) * dt * dt;

    xAndV_new.v = xAndV.v + 0.5 * (forcePendulum(xAndV.x) + forcePendulum(xAndV_new.x)) * dt;

    return xAndV_new;
}

/****************************+*/

func getFunction(void)
{
    int algorithm;
    struct phaseSpace (*nextStep)();

    printf("# Integrare con metodo Runge-Kutta (0) o con Verlet (1)?");
    algorithm = readInt("Inserire 0 o 1");
    // Provo a usare i puntatori a funzione
    if (algorithm == 0)
    {
        nextStep = &rungeKutta;
    }
    else if (algorithm == 1)
    {
        nextStep = &verlet_aut;
    }
    else
    {
        printf("ERRORE!!!!");
        exit(1);
    }
    return nextStep;
}

/****************************+*/
