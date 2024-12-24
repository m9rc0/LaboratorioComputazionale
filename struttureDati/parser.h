#define MY_MAX 50

struct fromWord{
  int myEnd;
  char *scratch;
};

struct fromWord readWord(FILE *fp);
void checkPointer(void *p);
int checkEndOfWord(char carattere);
char rmvUpperCase(char lettera);

/*********** FUNZIONI ***********/

struct fromWord readWord(FILE *fp){
  char myFlag = 1, *myString;
  int j = 0, check;
  struct fromWord fW;
  fW.myEnd = 0;
  myString = (char *) malloc(MY_MAX * sizeof(char));
  checkPointer(myString);

  while ((j < MY_MAX) && (myFlag == 1))
    {
      myString[j] = rmvUpperCase(fgetc(fp));
      check = checkEndOfWord(myString[j]);
      //      printf("%c\n", myString[j]);
      if (check == 1){
	myString[j] = '\0';
	myFlag = 0;
      } else if (myString[j] == '\n'){
	j--; // per ignorare la fine della riga
      } else if (check == 2){
	// si sfrutta il fatto che la punteggiatura è seguita da spazio
	myString[j] = '\0';
	fgetc(fp);
	myFlag = 0;
      }  else if (myString[j] == EOF){
	fW.myEnd = 1; // il programma smette di leggere l'input
	myString[j] = '\0';
	myFlag = 0;
      }
      j++;
    }

  if (j >= MY_MAX-1) {
    printf("Parola troppo lunga, interruzione del programma!\n");
    exit(-1);
  }
  //  printf("len = %lu, parola = %s\n", strlen(myString), myString);

  fW.scratch = myString;

  return fW;
}

/********************************/

void checkPointer(void *p){
  if (p == NULL){
    printf("Errore con il puntatore!\n");
    exit(-1);
  }
}

/********************************/

int checkEndOfWord(char carattere){
  // Si definise una lista di caratteri che fanno finire la parola
  int nCaratteri = 4, i;
  char fine[4] = {',', ';', '.', ':'};

  if (carattere == ' ') return 1;

  for (i = 0; i < nCaratteri; i++){
    if (carattere == fine[i]){
      //      printf("ciao\n");
      return 2; 
    }
  }

  return 0;
}

/***************************************/

char rmvUpperCase(char lettera){
  if ((lettera >= 65) && (lettera <= 90)){
    return lettera += 32;
  }
  return lettera;
}

/**************************************/

