#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NMAX 240

/*
 
 */

struct phaseSpace
{
    double x;
    double v;
};

struct massimo {
  double a;
  double t;
};

double phi(double w2, double x, double v, double l);
struct phaseSpace initOsc(double x0, double v0);
struct phaseSpace rungeKutta(double dt, double w2, double l, struct phaseSpace xAndV);
double interpolazione (struct massimo max1, struct massimo max2, double A);

int main()
{
  double x0 = 100, v0 = 0, vOld, dt = 0.001, totalTime = 250, l = 0.1, w2 = 9., Atreshold = 0.5 * x0;
  long numberOfSteps, i, count = 1;
  struct phaseSpace xandV;
  struct massimo max[NMAX] = {0};
  max[0].a = x0;
  max[0].t = 0;
  numberOfSteps = (long)(totalTime / dt + 0.5);
  xandV = initOsc(x0, v0);

  // Ciclo principale

  for (i=1; i<numberOfSteps; i++) {
    vOld = xandV.v;                                                //salvo la velocità precedente in una variabile temporanea
    xandV = rungeKutta (dt, w2, l, xandV);
    if (((vOld * xandV.v) <= 0)&&(count < NMAX)) {                                   //se si è raggiunto il massimo (velocità consecutive discordi)
      max[count].a = fabs(xandV.x);                                 // salviamo le occorrenze dei massimi e i rispettivi tempi in un array   
      max[count].t = i * dt;
      count++;
    } 
  }

  // calcoliamo i tempi di dimezzamento
  for (i = 1; i < NMAX; i++)
    {
      if((max[i].a <= Atreshold)&&(max[i].t != 0)){
	printf ("%lf %lf\n", interpolazione(max[i-1], max[i], Atreshold), Atreshold);
	Atreshold *= 0.5;
      }
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

double interpolazione (struct massimo max1, struct massimo max2, double A) {
  double T;
  T = (A - max2.a) * (max2.t - max1.t) / (max2.a - max1.a) + max2.t;                       //usando una retta di interpolazione fra due massimi successivi troviamo t_dimezzamento
  return T;
}

/****************************+*/
/****************************+*/
