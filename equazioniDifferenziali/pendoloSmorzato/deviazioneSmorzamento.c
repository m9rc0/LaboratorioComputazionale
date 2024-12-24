#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NMAX 240

/*
  Questo programma stima la variazione della precisione del metodo delle rette nella stima del tempo di dimezzamento, aumentando gamma e rendendo minimi e massimi successivi più rari
*/

/*
  ATTENZIONE:
  lo studio della precisione del "metodo delle rette" è ridotta in quanto all'aumentare di gamma diminuisce il tempo di dimezzamento e diminuiscono anche i periodi, in più capita che i periodi e i tempi di dimezzamento si "allineino", causando delle diminuzioni nella deviazione standard.
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

void integration(double l, struct massimo max[], long numberOfSteps, double dt, double w2, double x0, double v0);
double calcStd(struct massimo max[], double x0);

int main()
{
  double x0 = 1000, v0 = 0, vOld, dt = 0.001, totalTime = 250, l, w2 = 9.;
  long numberOfSteps, i, count = 1;

  struct massimo max[NMAX] = {0};
  numberOfSteps = (long)(totalTime / dt + 0.5);

  printf("# x0 = %lf, v0 = %lf dt = %lf\n# totalTime = %lf, w^2 = %lf", x0, v0, dt, totalTime, w2);

  
  for (l = 0.1; l < 0.8; l += 0.01)
    {
      integration(l, max, numberOfSteps, dt, w2, x0, v0);
      printf("%lf %lf\n", l, calcStd(max, x0));

      // si svuota l'array dei massimi
      for (i = 0; i < NMAX; i++)
	{
	  max[i].a = 0;
	  max[i].t = 0;
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
  T = (A - max2.a) * (max2.t - max1.t) / (max2.a - max1.a) + max2.t;  //usando una retta di interpolazione fra due massimi successivi troviamo t_dimezzamento
  return T;
}

/****************************+*/

void integration(double l, struct massimo max[], long numberOfSteps, double dt, double w2, double x0, double v0)
{
  // Questa funzione fa tutto il processo di integrazione e si riempie l'array con i massimi
    struct phaseSpace xandV;
    double vOld;
    int count = 1, i = 1;

    max[0].a = x0;
    max[0].t = 0;
    
    
    xandV = initOsc(x0, v0);
    
    for (i=1; i<numberOfSteps; i++) {
      vOld = xandV.v;                                                //salvo la velocità precedente in una variabile temporanea
      xandV = rungeKutta (dt, w2, l, xandV);
      if (((vOld * xandV.v) <= 0)&&(count < NMAX)&&(xandV.x)&&(xandV.x >= 0.1)) {       //se si è raggiunto il massimo (velocità consecutive discordi) e se le oscillazioni non sono troppo piccole
	max[count].a = fabs(xandV.x);                                 // salviamo le occorrenze dei massimi e i rispettivi tempi in un array   
	max[count].t = i * dt;
	count++;
      } 
    }
    
}

/****************************+*/

double calcStd(struct massimo max[], double x0)
{
  /*
    Si 
   */
  double Atreshold = x0 * 0.5, Ttemp = 0, T, x2medio = 0, xmedio = 0;
  int i, count = 0;
  
  // calcoliamo i tempi di dimezzamento
  for (i = 1; i < NMAX; i++)
    {
      if((max[i].a <= Atreshold)&&(max[i].t != 0)){  // se si è superato il limite di dimezzamento si stima il suo tempo con le rette
	T = interpolazione(max[i-1], max[i], Atreshold);
	//		printf("%lf\n", T-Ttemp);
	// si fanno le sommatorie per la deviazione standard
	x2medio += (T-Ttemp)*(T-Ttemp);
	xmedio += (T-Ttemp);
	count++;
	Ttemp = T;
	Atreshold *= 0.5;
      }
    }

  
  x2medio /= (double) count;
  xmedio /= (double) count;

  //  printf("%lf\n\n", xmedio);
  //  printf("\n%lf %lf\n\n", x2medio, xmedio*xmedio);
  return sqrt(x2medio - xmedio*xmedio);
}


/****************************+*/

