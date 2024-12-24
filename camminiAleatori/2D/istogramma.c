#include <stdio.h>
#include <stdlib.h>

/* questo programma calcola gli istogrammi*/

int findEstremi(FILE *file, int *min, int *max);
void fillHist(FILE *fp, int *ris, int min);

int main(int argc, char *argv[])
{
  FILE *fp;
  int min, max, *ris, i, len;
  
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

  len = findEstremi(fp, &min, &max);

  ris = calloc(max - min + 1, sizeof(int));
  if (ris == NULL)
    {
      printf("Errore con l'allocazione della memoria\n");
      exit(-8);
    }

  fillHist(fp, ris, min);

  for (i = 0; i < (max - min + 1); i++)
    {
      // stampo le frequenze, dividendo per il numero di righe
      printf("%i %lf\n", i + min, (double)ris[i]/(double)len);
    }
  
  return 9;
}


int findEstremi(FILE *file, int *min, int *max)
{
  int temp, count = 0;
  *min = 0;
  *max = 0;
  while(fscanf(file, "%i", &temp) != EOF)
    {
      if (*min > temp)
	{
	  *min = temp;
	}
      else if (*max < temp)
	{
	  *max = temp;
	}
      count++;
    }
  // importante per ricominciare di nuovo dal file
  rewind(file);
  return count;
}

void fillHist(FILE *fp, int *ris, int min)
{
  int dist;
    while (fscanf(fp, "%i", &dist) != EOF)
    {
      ris[dist - min]++;
    }

    rewind(fp);
}
