#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct phaseSpace {
  double x;
  double v;
};

double phi(double, double);
double energy(double w2, struct phaseSpace xandV);

struct phaseSpace euler(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace passo(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace central(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace cromer(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace verlet(double w2, double dt, struct phaseSpace xandV);
struct phaseSpace predizione(double w2, double dt, struct phaseSpace xandV[]);
struct phaseSpace runge(double w2, double dt, struct phaseSpace xandV);


struct phaseSpace inizPar (double, double);

int main () {
  struct phaseSpace xandV[6], xandV1[2], temp;
  double w2=3, x0=2, v0=1, dt=0, time=100, E0, rapp[7]={0};
  int nsteps, i;

  printf("# dt - eulero - cromer - centrale - verlet - runge - mezzo passo - predizione\n");
  E0 = 0.5*v0*v0 + 0.5*w2*x0*x0;  //energia al tempo iniziale

  printf("%lf ", dt);
  for(i=0; i < 7; i++)
  {
    printf("%lf ", rapp[i]);
  }
  printf("\n");
  
  // inizializziamo tutto
  for (dt = 0.001; dt<0.05; dt*=2) {
    nsteps = (int) (time/dt);
    //inizializzazione
    for (i = 0; i < 5; i++){
      xandV[i] = inizPar (x0, v0);
    }   

    //inizializzazione con verlet per il mezzo passo
    xandV[5].x = x0 + v0 * 0.5 * dt + 0.125 * phi(w2, x0) * dt * dt;
    xandV[5].v = v0 + 0.25 * (phi(w2, x0)+phi(w2, xandV[4].x))*dt;
    xandV[5].x = x0;
    
    // per il metodo di predizione - correzione c'è bisogno di un array doppio
    // Si fa il primo passo con verlet autosufficiente
    xandV1[0] = inizPar(x0, v0);
    xandV1[1].x = x0 + v0 * dt + 0.5* phi(w2, x0) * dt * dt;
    xandV1[1].v = v0 + 0.5 * (phi(w2, x0)+phi(w2, xandV1[1].x))*dt;
    
    for (i=1; i<nsteps; i++) {     
	// eulero 
	xandV[0] = euler(w2, dt, xandV[0]);
	// cromer
	xandV[1] = cromer(w2, dt, xandV[1]);
	// punto centrale 
	xandV[2] = central(w2, dt, xandV[2]);
	// verlet 
	xandV[3] = verlet(w2, dt, xandV[3]);
	// runge - kutta
	xandV[4] = runge(w2, dt, xandV[4]);
	// mezzo passo
	xandV[5] = passo(w2, dt, xandV[5]);
	// verlet
	temp = xandV1[1];
	xandV1[1] = predizione(w2, dt, xandV1);
	xandV1[0] = temp;
      }

    //ciclo di calcolo rapporti energie finali (t=2s)
    for (i=0; i<6; i++) {
      rapp[i] = (energy (w2, xandV[i]) - E0) / E0;
    }
    rapp[6] = (energy(w2, xandV1[1]) - E0) / E0;

    // stampo i risultati 
    printf("%lf ", dt);
    for(i = 0; i < 7; i++)
      {
	printf("%lf ", rapp[i]);
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

/***************************/

struct phaseSpace verlet(double w2, double dt, struct phaseSpace xandV)
{
  struct phaseSpace New;

  New.x = xandV.x + xandV.v * dt + 0.5 * phi(w2, xandV.x) * dt * dt;
  New.v = xandV.v + 0.5 * (phi(w2, xandV.x) + phi(w2, New.x))* dt;
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

