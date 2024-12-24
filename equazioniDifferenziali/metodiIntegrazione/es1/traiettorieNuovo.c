#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Questo programma integra le equazioni dell'oscillatore armonico con diversi metodi e stampa i valori di tempo, posizione e velocità come output*/

/*E' stato modificato per iterare tramite i metodi di integrazione con puntatori a funzione e prendere come input il passo di integrazione da linea di comando*/

struct phaseSpace {
  double x;
  double v;
};

double phi(double, double);
double energy(double w2, struct phaseSpace xandV);

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace central(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace passo(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace verlet(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace predizione(double w2, double dt, struct phaseSpace xandV[]);
struct phaseSpace runge (double w2, double dt, struct phaseSpace xandV);

struct phaseSpace inizPar (double, double);

int main (int argc, char *argv[]) {
  struct phaseSpace xandV[6], xandV1[2], temp, (*nextStep[6])() = {euler, cromer, central, verlet, runge, passo};
  double w2=1, x0=2, v0=0, dt, time=100;
  int nsteps, i, j;

  if (argc != 2){
    printf("#Usage: ./traiettorieNuovo dt\n");
    printf("#Errore con l'inserimento del passo!\n");
    exit(-9);
  }

  
  dt = atof(argv[1]);
  nsteps  = (int) (time / dt + 0.5);
  printf("#w^2 = %lf, x0 = %lf, v0 = %lf\n#total time = %lf, dt = %lf\n", w2, x0, v0, time, dt);
  printf("#Sulla prima colonna il tempo, per ogni metodo una colonna per le posizioni e una colonna per le velocità\n");
  printf("#euler - cromer - centrale - verlet - runge - passo - predizione\n");
  
  // inizializziamo tutto
  for ( i = 0; i < 5; i++){
    xandV[i] = inizPar (x0, v0);
  }

  //inizializzazione con verlet per il mezzo passo
  xandV[5].x = x0 + v0 * 0.5 * dt + 0.125 * phi(w2, x0) * dt * dt;
  xandV[5].v = v0 + 0.25 * (phi(w2, x0)+phi(w2, xandV[5].x))*dt;
  xandV[5].x = x0;

  // per il metodo di predizione - correzione c'è bisogno di un array doppio
  // Si fa il primo passo con verlet autosufficiente
  xandV1[0] = inizPar(x0, v0);
  xandV1[1].x = x0 + v0 * dt + 0.5* phi(w2, x0) * dt * dt;
  xandV1[1].v = v0 + 0.5 * (phi(w2, x0)+phi(w2, xandV1[1].x))*dt;


  // ciclo principale
  for (i=1; i<nsteps; i++) {
    printf("%lf ", dt * i);

    // faccio una iterazione per ogni metodo di integrazione
    for (j = 0; j<6 ; j++){
      xandV[j] = nextStep[j](w2, dt, xandV[j]);
      printf("%lf %lf ", xandV[j].x, xandV[j].v);
    }

    // mi comporto in modo speciale per predizione e correzione, c'è bisogno di conservare sempre le ultime due iterazioni
    if (i > 1)
      {
	temp = xandV1[1];
	xandV1[1] = predizione(w2, dt, xandV1);
	xandV1[0] = temp;
	printf("%lf %lf ", xandV1[1].x, xandV1[1].v);
      }
    else if (i == 1)
      {
	printf("%lf %lf ", xandV1[1].x, xandV1[1].v);
      }
    printf("\n");
  } 
  
  return 0;
}

/* FUNZIONI  */

double phi(double w2, double x) {
  return -w2 * x;
}

/***************************/

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV){
  struct phaseSpace New;
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + xandV.v * dt;
  return New;
}

/***************************/
struct phaseSpace inizPar (double x, double v) {
  struct phaseSpace inizio;
  inizio.x = x;
  inizio.v = v;
  return inizio;
}

/***************************/
double energy(double w2, struct phaseSpace xandV) {
  double K, V;
  K = 0.5 * xandV.v * xandV.v;
  V = 0.5 * w2 * xandV.x * xandV.x;
  return K + V;
}
/***************************/
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace New;
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + New.v * dt;
  return New;
}
/***************************/

struct phaseSpace central(double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace New;
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + (New.v + xandV.v)/2. * dt;
  return New;
}

/***************************/

struct phaseSpace passo(double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace New;
  //per le traiettorie non ci ponamo il problema che siano sfasate 
  
  New.v = xandV.v + phi(w2, xandV.x) * dt;
  New.x = xandV.x + New.v * dt;
  return New;
}

/***************************/

struct phaseSpace verlet(double w2, double dt, struct phaseSpace xandV)
{
  struct phaseSpace New;

  New.x = xandV.x + xandV.v * dt + 0.5 * phi(w2, xandV.x) * dt * dt;
  New.v = xandV.v + 0.5 * (phi(w2, xandV.x) + phi(w2, xandV.x))* dt;
  return New;
}

/***************************/

struct phaseSpace predizione(double w2, double dt, struct phaseSpace xandV[])
{
  struct phaseSpace new;
  double xtemp;

  xtemp = xandV[0].x + 2 * xandV[1].v * dt;
  new.v = xandV[1].v + 0.5 * (phi(w2, xtemp) + phi(w2, xandV[1].x)) * dt;
  new.x = xandV[1].x + 0.5 * (new.v + xandV[1].v) * dt;
  return new;
}

/***************************/

struct phaseSpace runge (double w2, double dt, struct phaseSpace xandV) {
  struct phaseSpace new;
  double dx1 = xandV.v * dt;
  double dv1 = phi(w2, xandV.x) * dt;
  double dx2 = (xandV.v + 0.5*dv1) * dt;
  double dv2 = phi(w2, xandV.x + 0.5*dx1) * dt;
  double dx3 = (xandV.v + 0.5*dv2) * dt;
  double dv3 = phi(w2, xandV.x + 0.5*dx2) * dt;
  double dx4 = (xandV.v + 0.5*dv3) * dt;
  double dv4 = phi(w2, xandV.x + 0.5*dx3) * dt;
  new.x = xandV.x + (dx1 + 2*dx2 + 2*dx3 + dx4)/6;
  new.v = xandV.v + (dv1 + 2*dv2 + 2*dv3 + dv4)/6;
  return new;
}


/***************************/
