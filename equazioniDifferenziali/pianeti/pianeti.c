#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MUA 0.001
#define MUB 0.01
#define LAMBDA 4*M_PI*M_PI    //define per le masse ridotte e per la costante d'accoppiamento

struct pianeti {              
  double x;
  double y;
  double vx;
  double vy;
};

struct sistema {                 //struttura che consente di lavorare insieme sui due pianeti
  struct pianeti p1;
  struct pianeti p2;
};

struct sistema runge (struct sistema, double);
struct sistema calcDelta (struct sistema, double);
double calcMomento (struct sistema);
double calcEnergy (struct sistema);

int main () {
  double dt = 0.01, time = 200, T=0, L, E;
  int nsteps = (int) (time/dt);

  //inizializzazione dei due pianeti 
  struct pianeti terra, marte;
  terra.x = -10;
  marte.x = 30.21;
  terra.y = 0.;
  marte.y = 0;
  terra.vx = marte.vx = 0.;
  terra.vy = -1.5;
  marte.vy = -1.0;

  //inizializzazione del sistema dei due pianeti, calcolo dei valori iniziali di energia e momento e scrittura di tutti i dati iniziali
  struct sistema s;
  s.p1 = terra;
  s.p2 = marte;
  L = calcMomento (s);
  E = calcEnergy (s);
  printf ("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", T, s.p1.x, s.p1.y, s.p1.vx, s.p1.vy, s.p2.x, s.p2.y, s.p2.vx, s.p2.vy, L, E);

  //ciclo principale
  for (int i=1; i<nsteps; i++) {
    T += dt;
    s = runge (s, dt);
    L = calcMomento (s);
    E = calcEnergy (s);
    printf ("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", T, s.p1.x, s.p1.y, s.p1.vx, s.p1.vy, s.p2.x, s.p2.y, s.p2.vx, s.p2.vy, L, E);
  }

  return 0;
}

//funzione per calcolare l'accelerazione, date le equazioni del moto
double phi (double coord1, double coord2, double AB1, double AB2, double m) {
  double phi;
  phi = -LAMBDA*coord1/(pow((coord1*coord1 + coord2*coord2), 1.5)) + m*LAMBDA*AB1/(pow((AB1*AB1 + AB2*AB2), 1.5));
  return phi;
}

//funzione principale, metodo runge-kutta del secondo ordine
struct sistema runge (struct sistema sOld, double dt) {
  struct sistema sNew, delta;
  delta = calcDelta (sOld, dt);   //calcolo dei vari deltax e deltav tramite funzione calcDelta
  double ma = MUA, mb = MUB, rABx = (sOld.p2.x + 0.5*delta.p2.x) - (sOld.p1.x + 0.5*delta.p1.x), rABy = (sOld.p2.y + 0.5*delta.p2.y) - (sOld.p1.y + 0.5*delta.p1.y);         //variabili necessarie per il passaggio alla funzione phi (distanza relativa fra i due pianeti)
  sNew.p1.x = sOld.p1.x + (sOld.p1.vx + 0.5*delta.p1.vx)*dt;
  sNew.p1.y = sOld.p1.y + (sOld.p1.vy + 0.5*delta.p1.vy)*dt;
  sNew.p2.x = sOld.p2.x + (sOld.p2.vx + 0.5*delta.p2.vx)*dt;
  sNew.p2.y = sOld.p2.y + (sOld.p2.vy + 0.5*delta.p2.vy)*dt;
  sNew.p1.vx = sOld.p1.vx + phi(sOld.p1.x + 0.5*delta.p1.x, sOld.p1.y + 0.5*delta.p1.y, rABx, rABy, mb)*dt;
  sNew.p1.vy = sOld.p1.vy + phi(sOld.p1.y + 0.5*delta.p1.y, sOld.p1.x + 0.5*delta.p1.x, rABy, rABx, mb)*dt;
  sNew.p2.vx = sOld.p2.vx + phi(sOld.p2.x + 0.5*delta.p2.x, sOld.p2.y + 0.5*delta.p2.y, rABx, rABy, -ma)*dt;
  sNew.p2.vy = sOld.p2.vy + phi(sOld.p2.y + 0.5*delta.p2.y, sOld.p2.x + 0.5*delta.p2.x, rABy, rABx, -ma)*dt; 
  return sNew;
}

struct sistema calcDelta (struct sistema s, double dt) {
  struct sistema delta;
  double ma = MUA, mb = MUB, rABx = s.p2.x - s.p1.x, rABy = s.p2.y - s.p1.y;
  delta.p1.x = s.p1.vx * dt;
  delta.p1.y = s.p1.vy * dt;
  delta.p2.x = s.p2.vx * dt;
  delta.p2.y = s.p2.vy * dt;
  delta.p1.vx = phi(s.p1.x, s.p1.y, rABx, rABy, mb)*dt;
  delta.p1.vy = phi(s.p1.y, s.p1.x, rABy, rABx, mb)*dt;
  delta.p2.vx = phi(s.p2.x, s.p2.y, rABx, rABy, -ma)*dt;
  delta.p2.vy = phi(s.p2.y, s.p2.x, rABy, rABx, -ma)*dt;
  return delta;
}

//funzione per il calcolo del momento angolare come somma dei momenti angolari singoli dei due pianeti
double calcMomento (struct sistema s) {
  double L, l1, l2;
  l1 = MUA * (s.p1.x * s.p1.vy - s.p1.y * s.p1.vx);
  l2 = MUB * (s.p2.x * s.p2.vy - s.p2.y * s.p2.vx);
  L = l1 + l2;
  return L;
}

//funzione per il calcolo dell'energia meccanica totale come somma di energia potenziale (sole-pianeti e pianeta1-pianeta2) e cinetica
double calcEnergy (struct sistema s) {
  double distA = pow(s.p1.x*s.p1.x + s.p1.y*s.p1.y, 0.5), distB = pow(s.p2.x*s.p2.x + s.p2.y*s.p2.y, 0.5);
  double distAB = pow((s.p2.x-s.p1.x)*(s.p2.x-s.p1.x) + (s.p2.y-s.p1.y)*(s.p2.y-s.p1.y), 0.5);
  double potenz = -LAMBDA*MUA/distA - LAMBDA*MUB/distB - MUA*MUB/distAB;
  double kinetic = 0.5*MUA*(s.p1.vx*s.p1.vx + s.p1.vy*s.p1.vy) + 0.5*MUB*(s.p2.vx*s.p2.vx + s.p2.vy*s.p2.vy);
  double energy = kinetic + potenz;
  return energy;
}
