#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

/*
  Si modifica l'algoritmo del professore, e si applica sui tre lati di un triangolo equilatero per creare il fiocco di neve
*/

#define MY_MAX_BYTE 100000000

void checkPointer(void *p);
void initialization(int argc, char *argv[], int *numLevel, FILE **gp);
void checkMemory(int n, int level);
void printOutput(FILE *gp, int n, int level, long double *xS0, long double *yS0,
                 long double *xS1, long double *yS1,
                 long double *xS2, long double *yS2);
void updateArray(int n, int level, long double **xS0, long double **yS0);
/* ciao */
/*ciao 1*/
/******************************************************************/
int main(int argc, char *argv[])
{
  int n, level, numLevel;
  long double *xS0, *yS0, *xS1, *yS1, *xS2, *yS2;
  FILE *gp;

  initialization(argc, argv, &numLevel, &gp);

  fprintf(gp, "set key bottom right\n");
  fflush(gp);
  fprintf(gp, "set size ratio -1\n");
  fflush(gp);
  level = -1;
  n = 1;
  checkMemory(n, level);

  xS0 = malloc((n + 1) * sizeof(long double));
  checkPointer(xS0);
  yS0 = malloc((n + 1) * sizeof(long double));
  checkPointer(yS0);
  xS1 = malloc((n + 1) * sizeof(long double));
  checkPointer(xS1);
  yS1 = malloc((n + 1) * sizeof(long double));
  checkPointer(yS1);
  xS2 = malloc((n + 1) * sizeof(long double));
  checkPointer(xS2);
  yS2 = malloc((n + 1) * sizeof(long double));
  checkPointer(yS2);

  xS0[0] = -0.5;
  xS0[1] = 0.0;
  yS0[0] = 0.0;
  yS0[1] = sqrt(3) / 2;

  xS1[0] = 0.0;
  xS1[1] = 0.5;
  yS1[0] = sqrt(3) / 2;
  yS1[1] = 0.0;

  xS2[0] = 0.5;
  xS2[1] = -0.5;
  yS2[0] = 0.0;
  yS2[1] = 0.0;

  printOutput(gp, n, level, xS0, yS0, xS1, yS1, xS2, yS2);

  for (level = 0; level < numLevel; level++)
  {
    n *= 4;
    updateArray(n, level, &xS0, &yS0);
    updateArray(n, level, &xS1, &yS1);
    updateArray(n, level, &xS2, &yS2);
    printOutput(gp, n, level, xS0, yS0, xS1, yS1, xS2, yS2);
  }
  fprintf(gp, "exit\n");
  fflush(gp);
  return 0;
}

/************************** FUNZIONI **************************/

/***************************************************/

void initialization(int argc, char *argv[], int *numLevel, FILE **gp)
{
  if (argc != 2)
  {
    printf("Use parameter: numLevel\n");
    exit(-9);
  }

  *numLevel = (int)atoi(argv[1]);

  *gp = popen("gnuplot", "w");
  checkPointer(*gp);
}

/***************************************************/

void checkPointer(void *p)
{
  if (p == NULL)
  {
    printf("Errore con il puntatore!");
    exit(-1);
  }
}

/***************************************************/

void checkMemory(int n, int level)
{
  if ((n + 1) * sizeof(long double) > MY_MAX_BYTE)
  {
    printf("ABORT cowardly refusing allocation size %ld max %ld level+1 %d\n",
           (n + 1) * sizeof(long double), (long int)MY_MAX_BYTE, level + 1);
    exit(-9);
  }
}

/***************************************************/

void printOutput(FILE *gp, int n, int level, long double *xS0, long double *yS0,
                 long double *xS1, long double *yS1,
                 long double *xS2, long double *yS2)
{
  char fileName[100];
  FILE *sD;
  int i;

  sprintf(fileName, "scratchserp.dat%2.2d", level + 1);
  printf("%s\n", fileName);
  sD = fopen(fileName, "w");
  for (i = 0; i < n + 1; i++)
  {
    fprintf(sD, "%Lg %Lg\n", xS0[i], yS0[i]);
  }

  for (i = 0; i < n + 1; i++)
  {
    fprintf(sD, "%Lg %Lg\n", xS1[i], yS1[i]);
  }

  for (i = 0; i < n + 1; i++)
  {
    fprintf(sD, "%Lg %Lg\n", xS2[i], yS2[i]);
  }

  fprintf(gp, "plot [-1.05:1.05][-0.5:1.05] \"%s\" with lines t \" level %d\"\n", fileName, level + 1);
  fflush(gp);
  fprintf(gp, "pause 1 \"level %d waiting 1\"\n", level + 1);
  fflush(gp);
  fflush(sD);
  fclose(sD);
}

/***************************************************/

void updateArray(int n, int level, long double **xS, long double **yS)
{
  long double *xS1, *yS1;
  long double myPi, cos60, sin60;
  int oldSegment;

  myPi = 4. * atan(1);
  cos60 = cos(myPi / 3.);
  sin60 = sin(myPi / 3.);

  checkMemory(n, level);
  xS1 = malloc((n + 1) * sizeof(long double));
  checkPointer(xS1);
  yS1 = malloc((n + 1) * sizeof(long double));
  checkPointer(yS1);

  xS1[0] = (*xS)[0];
  yS1[0] = (*yS)[0];

  for (oldSegment = 0; oldSegment < n / 4; oldSegment++)
  {
    int a = oldSegment, b = a + 1, c = 1 + 4 * oldSegment;
    long double sXN, sYN;
    // next to minimize addressing and ops
    long double xS0A = (*xS)[a], xS0B = (*xS)[b];
    long double yS0A = (*yS)[a], yS0B = (*yS)[b];
    long double xD = xS0B - xS0A, yD = yS0B - yS0A;
    long double xD3 = xD / 3., yD3 = yD / 3.;

    xS1[c] = xS0A + xD3;
    yS1[c] = yS0A + yD3;
    sXN = cos60 * xD3 - sin60 * yD3;
    sYN = +sin60 * xD3 + cos60 * yD3;
    sXN += xD3 + xS0A;
    sYN += yD3 + yS0A;
    xS1[c + 1] = sXN;
    yS1[c + 1] = sYN;
    xS1[c + 2] = xS0A + 2. * xD3;
    yS1[c + 2] = yS0A + 2. * yD3;
    xS1[c + 3] = xS0B;
    yS1[c + 3] = yS0B;
  }
  free(*xS);
  free(*yS);

  *xS = xS1;
  *yS = yS1;
}

/***************************************************/
