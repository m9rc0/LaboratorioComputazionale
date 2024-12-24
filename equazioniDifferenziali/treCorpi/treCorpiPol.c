#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
NON COMPLETO 
 */


struct pianeti {              
  double x;
  double y;
  double vx;
  double vy;
};

struct sistema {
  struct pianeti p1;
  struct pianeti p2;
};

double forzaStella (double coord1, double coord2);
double forzaPianeta (double coord1, double coord2, double Rx, double Ry);
struct sistema runge (struct sistema sOld, double dt);
struct sistema calcDelta (struct sistema s, double dt);
struct sistema initPar(char *argv[]);

int main (int argc, char *argv[]) {
  struct sistema s;
  double dt = 0.0001, totalTime = 50, dt1 = 0.01, **ris, xtemp, period, x0, omega;
  int nSteps, i, mod, count;

  if (argc != 9)
    {
      printf("ERRORE NELL'INSERIMENTO DEI DATI");
      exit(-9);
    }
  x0 = atof(argv[5]);
  s = initPar(argv);
  
  nSteps = (int) (totalTime/dt + 0.5);
  mod = (int) (dt1 / dt);

  // array per i risultati
  ris = malloc(nSteps*sizeof(double*));
  if (ris == NULL){
    printf("Errore con l'allocazione\n");
    exit(-1);
  }
  for (i = 0; i < nSteps; i++){
    ris[i]=malloc(4*sizeof(double));
    if (ris[i] == NULL){
      printf("Errore con l'allocazione\n");
      exit(-1);
    }

  }

  // integrazione 
  for (i = 1; i < nSteps; i++){
    s = runge(s, dt);
    ris[i][0] = s.p1.x;     
    ris[i][1] = s.p1.y;
    ris[i][2] = s.p2.x;
    ris[i][3] = s.p2.y;
  }

  // ricerca del periodo e di omega
  xtemp = x0;
  count = 0;
  for (i = 0; i < nSteps; i++) {
    if ((xtemp < x0) && (ris[i][2] >= x0)) {
      count++;
      period = dt * i;
    }
    xtemp = ris[i][2];
  }
  period /= (double) count;
  omega = 2 * M_PI / period;

  //ciclo per rotazione 
  for (i = 0; i < nSteps; i++) {
    double temp1, temp2; 
    temp1 =  ris[i][0] * cos(omega * dt * i) + ris[i][1] * sin (omega * dt * i);
    temp2 = -ris[i][0] * sin(omega * dt * i) + ris[i][1] * cos (omega * dt * i);
    if (i % mod == 0) {
      printf ("%lf %lf\n", temp1, temp2);
    }
  }

  return 9;
}

/*
  FUNZIONI
 */

double forzaStella (double coord1, double coord2)  {
  //semplifichiamo il problema ponendo le due masse dei pianeti uguali a condizioni iniziali speculari, così che abbiano le coordinate x e y uguali in modulo durante tutto il moto
  double f;
  f = -2*coord1 / (pow((4*(coord1*coord1 + coord2*coord2)), 1.5));
  return f;
}

double forzaPianeta (double coord1, double coord2, double Rx, double Ry) {

  double f;
  f = (coord2 + coord1) / (pow(Rx*Rx + Ry*Ry, 1.5));
  return f;
}

struct sistema runge (struct sistema sOld, double dt) {
  struct sistema sNew, delta;
  delta = calcDelta (sOld, dt);   //calcolo dei vari deltax e deltav tramite funzione calcDelta
  double r12x = (sOld.p2.x + 0.5*delta.p2.x) - (sOld.p1.x + 0.5*delta.p1.x), r12y = (sOld.p2.y + 0.5*delta.p2.y) - (sOld.p1.y + 0.5*delta.p1.y);
  double r13x = (sOld.p2.x + 0.5*delta.p2.x) + (sOld.p1.x + 0.5*delta.p1.x), r13y = (sOld.p2.y + 0.5*delta.p2.y) + (sOld.p1.y + 0.5*delta.p1.y);
  
  sNew.p1.x = sOld.p1.x + (sOld.p1.vx + 0.5*delta.p1.vx)*dt;
  sNew.p1.y = sOld.p1.y + (sOld.p1.vy + 0.5*delta.p1.vy)*dt;
  sNew.p2.x = sOld.p2.x + (sOld.p2.vx + 0.5*delta.p2.vx)*dt;
  sNew.p2.y = sOld.p2.y + (sOld.p2.vy + 0.5*delta.p2.vy)*dt;
  
  sNew.p1.vx = sOld.p1.vx + (forzaPianeta(-sOld.p1.x - 0.5*delta.p1.x, sOld.p2.x + 0.5*delta.p2.x, r12x, r12y) + forzaPianeta(-sOld.p1.x - 0.5*delta.p1.x, -sOld.p2.x - 0.5*delta.p2.x, r13x, r13y)) * dt;
  sNew.p1.vy = sOld.p1.vy + (forzaPianeta(-sOld.p1.y - 0.5*delta.p1.y, sOld.p2.y + 0.5*delta.p2.y, r12x, r12y) + forzaPianeta(-sOld.p1.y - 0.5*delta.p1.y, -sOld.p2.y - 0.5*delta.p2.y, r13x, r13y)) * dt;
  
  sNew.p2.vx = sOld.p2.vx + forzaStella(sOld.p2.x + 0.5*delta.p2.x, sOld.p2.y + 0.5*delta.p2.y) * dt;
  sNew.p2.vy = sOld.p2.vy + forzaStella(sOld.p2.y + 0.5*delta.p2.y, sOld.p2.x + 0.5*delta.p2.x) * dt;

  return sNew;
}


struct sistema calcDelta (struct sistema s, double dt) {
  struct sistema delta;
  double r12x = s.p2.x - s.p1.x, r12y = s.p2.y - s.p1.y, r13x = s.p2.x + s.p1.x, r13y = s.p2.y + s.p1.y;
  
  delta.p1.x = s.p1.vx * dt;
  delta.p1.y = s.p1.vy * dt;
  delta.p2.x = s.p2.vx * dt;
  delta.p2.y = s.p2.vy * dt;
  
  delta.p1.vx = (forzaPianeta(-s.p1.x, s.p2.x, r12x, r12y) + forzaPianeta(-s.p1.x, -s.p2.x, r13x, r13y)) * dt;
  delta.p1.vy = (forzaPianeta(-s.p1.y, s.p2.y, r12x, r12y) + forzaPianeta(-s.p1.y, -s.p2.y, r13x, r13y)) * dt;
  
  delta.p2.vx = forzaStella(s.p2.x, s.p2.y) * dt;
  delta.p2.vy = forzaStella(s.p2.y, s.p2.x) * dt;
  return delta;
}


struct sistema initPar(char *argv[]){
  struct pianeti pianeta, stella;
  struct sistema s;
  // inizializziamo cond
  pianeta.x = atof(argv[1]);
  pianeta.y = atof(argv[2]);
  pianeta.vx = atof(argv[3]);
  pianeta.vy = atof(argv[4]);

  stella.x = atof(argv[5]);
  stella.y = atof(argv[6]);
  stella.vx = atof(argv[7]);
  stella.vy = atof(argv[8]);

  s.p1 = pianeta;
  s.p2 = stella;
  return s;
}
