#include <stdio.h>
#include <stdlib.h>

/* questo programma calcola gli istogrammi in due dimensioni, ritorna prima colonna le coordinate delle x, come seconda colonna quelle delle y, come terza le loro frequenze
 */

int findEstremi(FILE *file, int *minX, int *maxX, int *minY, int *maxY);
void fillHist(FILE *fp, int *ris, int minX, int minY, double widthX, double widthY, int L);


int main(int argc, char * argv[])
{
  FILE *fp;
  int minX, maxX, minY, maxY, *ris, i, j, len, L = 50;
  double widthX, widthY;

    if (argc != 2)
    {
      printf("usage: ./istogramma nomefile");
      exit(-6);
    }

  // inizializzo il puntatore a file 
  fp = fopen(argv[1], "r");
  if (fp == NULL)
    {
      printf("Errore nell'apertura del file\n");
      exit(-7);
    }

  len = findEstremi(fp, &minX, &maxX, &minY, &maxY);

  widthX = (maxX - minX) / L;
  widthY = (maxY - minY) / L;
  
  
  // un altro modo per inizializzare un array come se fosse multidimensionale
  ris = calloc(L * L, sizeof(int));
  if (ris == NULL)
    {
      printf("Errore nell'allocazione dinamica della memoria\n");
      exit(-8);
    }

  fillHist(fp, ris, minX, minY, widthX, widthY, L);

  for (i = 0; i < L; i++)
    {
      for (j = 0; j < L; j++)
	{
	  printf("%lf %lf %lf\n", i * widthX + minX, j * widthY + minY, (double)ris[j * L + i]/ (double)(len));
	}
    }
  
  return 9;
}

int findEstremi(FILE *file, int *minX, int *maxX, int *minY, int *maxY)
{
  int tempX, tempY, count = 0;
  *minX = 0;
  *maxX = 0;
  *minY = 0;
  *maxY = 0;

  while(fscanf(file, "%i %i", &tempX, &tempY) != EOF)
    {
      if (*minX > tempX)
	{
	  *minX = tempX;
	}
      else if (*maxX < tempX)
	{
	  *maxX = tempX;
	}

      if (*minY > tempY)
	{
	  *minY = tempY;
	}
      else if (*maxY < tempY)
	{
	  *maxY = tempY;
	}

      count++;
    }
  // importante per ricominciare di nuovo dal file
  rewind(file);
  return count;
}


void fillHist(FILE *fp, int *ris, int minX, int minY, double widthX, double widthY, int L)
{
  int distX, distY, posX, posY;
  while (fscanf(fp, "%i %i", &distX, &distY) != EOF)
    {
      posY = (int) ((double) (distY - minY) / widthY);
      posX = (int) ((double) (distX - minX) / widthX);
      ris[L * posY + posX]++;
    }

    rewind(fp);
}
