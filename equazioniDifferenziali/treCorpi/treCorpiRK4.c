/*Questo programma integra con metodo Runge-Kutta del quarto ordine il problema ristretto dei tre corpi, in cui una delle tre masse è ha influenza nulla sulle altre due. Semplifichiamo il problema ponendo le due masse (tra l'altro unitarie) dei pianeti uguali a condizioni iniziali speculari, così che abbiano le coordinate x e y uguali in modulo durante tutto il moto*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct pianeti {    //ogni pianeta viene dotato delle coordinate di posizione e di velocità          
  double x;
  double y;
  double vx;
  double vy;
};

struct sistema {       
  struct pianeti p1;
  struct pianeti p2;
};

//strutture necessarie per il processo di Runge-Kutta
struct deltapos {    
  double dx1;
  double dy1;
  double dx2;
  double dy2;
};

struct deltavel {
  double dvx1;
  double dvy1;
  double dvx2;
  double dvy2;
};

//dichiarazione delle funzioni
double forzaStella (double coord1, double coord2);
double forzaPianeta (double coord1, double coord2, double Rx, double Ry);
struct sistema runge (struct sistema sOld, double dt);
struct deltapos calcDeltaPos (double vx1, double vy1, double vx2, double vy2, double dt);
struct deltavel calcDeltaVel (double x1, double y1, double x2, double y2, double dt);
struct sistema initPar(char *argv[]);

int main (int argc, char *argv[]) {
  struct sistema s;
  double dt = 0.0001, totalTime = 50;
  int nSteps, i;

  //messaggio d'errore se l'inserimento da linea da comando non va a buon fine 
  if (argc != 9)
    {
      printf("ERRORE NELL'INSERIMENTO DEI DATI");
      exit(-9);
    }
  //inizializzazione parametri
  s = initPar(argv);  
  nSteps = (int) (totalTime/dt + 0.5);
 
  // ciclo principale 
  for (i = 1; i < nSteps; i++){
    s = runge(s, dt);
    printf("%lf %lf %lf %lf %lf %lf\n", s.p1.x, s.p1.y, s.p2.x, s.p2.y, -s.p2.x, -s.p2.y);
  }
  
  return 9;
}

/*
  FUNZIONI
 */

double forzaStella (double coord1, double coord2)  {
  //forza gravitazionale tra i due corpi dotati di massa
  double f;
  f = -2*coord1 / (pow((4*(coord1*coord1 + coord2*coord2)), 1.5));
  return f;
}

double forzaPianeta (double coord1, double coord2, double Rx, double Ry) {
  //forza sul corpo a massa negligibile
  double f;
  f = (coord2 + coord1) / (pow(Rx*Rx + Ry*Ry, 1.5));
  return f;
}

struct sistema runge (struct sistema sOld, double dt) {
  struct sistema sNew;
  struct deltapos dpos1, dpos2, dpos3, dpos4;
  struct deltavel dvel1, dvel2, dvel3, dvel4;

  //calcoli necessari per Runge-Kutta del quarto ordine
  dpos1 = calcDeltaPos (sOld.p1.vx, sOld.p1.vy, sOld.p2.vx, sOld.p2.vy, dt);
  dvel1 = calcDeltaVel (sOld.p1.x, sOld.p1.y, sOld.p2.x, sOld.p2.y, dt);
  dpos2 = calcDeltaPos (sOld.p1.vx + 0.5*dvel1.dvx1, sOld.p1.vy + 0.5*dvel1.dvy1, sOld.p2.vx + 0.5*dvel1.dvx2, sOld.p2.vy + 0.5*dvel1.dvy2, dt);
  dvel2 = calcDeltaVel (sOld.p1.x + 0.5*dpos1.dx1, sOld.p1.y + 0.5*dpos1.dy1, sOld.p2.x + 0.5*dpos1.dx2, sOld.p2.y + 0.5*dpos1.dy2, dt);
  dpos3 = calcDeltaPos (sOld.p1.vx + 0.5*dvel2.dvx1, sOld.p1.vy + 0.5*dvel2.dvy1, sOld.p2.vx + 0.5*dvel2.dvx2, sOld.p2.vy + 0.5*dvel2.dvy2, dt);
  dvel3 = calcDeltaVel (sOld.p1.x + 0.5*dpos2.dx1, sOld.p1.y + 0.5*dpos2.dy1, sOld.p2.x + 0.5*dpos2.dx2, sOld.p2.y + 0.5*dpos2.dy2, dt);
  dpos4 = calcDeltaPos (sOld.p1.vx + dvel3.dvx1, sOld.p1.vy + dvel3.dvy1, sOld.p2.vx + dvel3.dvx2, sOld.p2.vy + dvel3.dvy2, dt);
  dvel4 = calcDeltaVel (sOld.p1.x + dpos3.dx1, sOld.p1.y + dpos3.dy1, sOld.p2.x + dpos3.dx2, sOld.p2.y + dpos3.dy2, dt);

  //nuove posizioni e velocità salvate nel nuovo sistema
  sNew.p1.x = sOld.p1.x + (dpos1.dx1 + 2*dpos2.dx1 + 2*dpos3.dx1 + dpos4.dx1)/6.;
  sNew.p2.x = sOld.p2.x + (dpos1.dx2 + 2*dpos2.dx2 + 2*dpos3.dx2 + dpos4.dx2)/6.;
  sNew.p1.y = sOld.p1.y + (dpos1.dy1 + 2*dpos2.dy1 + 2*dpos3.dy1 + dpos4.dy1)/6.;
  sNew.p2.y = sOld.p2.y + (dpos1.dy2 + 2*dpos2.dy2 + 2*dpos3.dy2 + dpos4.dy2)/6.;

  sNew.p1.vx = sOld.p1.vx + (dvel1.dvx1 + 2*dvel2.dvx1 + 2*dvel3.dvx1 + dvel4.dvx1)/6.;
  sNew.p2.vx = sOld.p2.vx + (dvel1.dvx2 + 2*dvel2.dvx2 + 2*dvel3.dvx2 + dvel4.dvx2)/6.;
  sNew.p1.vy = sOld.p1.vy + (dvel1.dvy1 + 2*dvel2.dvy1 + 2*dvel3.dvy1 + dvel4.dvy1)/6.;
  sNew.p2.vy = sOld.p2.vy + (dvel1.dvy2 + 2*dvel2.dvy2 + 2*dvel3.dvy2 + dvel4.dvy2)/6.;

  return sNew;
}

struct deltapos calcDeltaPos (double vx1, double vy1, double vx2, double vy2, double dt) {
  //calcolo dei delta relativi alle posizioni
  struct deltapos delta;
  delta.dx1 = vx1*dt;
  delta.dy1 = vy1*dt;
  delta.dx2 = vx2*dt;
  delta.dy2 = vy2*dt;
  
  return delta;
}

struct deltavel calcDeltaVel (double x1, double y1, double x2, double y2, double dt) {
  //calcolo dei delta relativi alle velocità; il corpo a massa nulla risente della forza gravitazionale dei due corpi grandi, questi ultimi invece solo di quella tra loro reciproca
  struct deltavel delta;
  double r12x = x2 - x1, r12y = y2 - y1, r13x = x2 + x1, r13y = y2 + y1;
  
  delta.dvx1 = (forzaPianeta(-x1, x2, r12x, r12y) + forzaPianeta(-x1, -x2, r13x, r13y)) * dt;
  delta.dvy1 = (forzaPianeta(-y1, y2, r12x, r12y) + forzaPianeta(-y1, -y2, r13x, r13y)) * dt;
  
  delta.dvx2 = forzaStella(x2, y2) * dt;
  delta.dvy2 = forzaStella(y2, x2) * dt;
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
