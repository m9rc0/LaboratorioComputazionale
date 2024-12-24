/*
  Questo programma costruisce liste dirette o indirette in base a quanto richiesto dall'utentes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

struct word {
  char *pString;
  struct word *pNextWord;
  struct word *pStart;
} *wordList = NULL;


void buildInverseList(struct fromWord fW);
void printInverseList(void);
void buildDirectList(struct fromWord fW);
void printDirectList(void);

int main(int argc, char *argv[]){
  int flag;
  FILE *fp;
  void (*buildList)(), (*printList)();
  struct fromWord fW;
  fW.myEnd = 0;

  if (argc != 3){
    printf("Usage: ./nomefile flag nometesto\n");
    printf("flag = 0 for inverse list\nflag = 1 for direct list\n");
    exit(-1);
  } 

  fp = fopen(argv[2], "r");

  flag = atoi(argv[1]);
  // assegno le funzioni come deciso dall'utente
  if (flag == 0){
    buildList = buildInverseList;
    printList = printInverseList;
  } else if (flag == 1){
    buildList = buildDirectList;
    printList = printDirectList;

  } else {
    printf("Usage: ./nomefile flag\n");
    printf("flag = 0 for inverse list\nflag = 1 for direct list\n");
    exit(-1);    
  }

  
  while (fW.myEnd != 1){
    fW = readWord(fp);
    buildList(fW);
    //    printf("ciao\n");
  }
  printList();
  return 9;
}

/*********** FUNZIONI ***********/

void buildInverseList(struct fromWord fW){
  char *temp, *myString;
  struct word *wordTemp;
  myString = fW.scratch;

  temp = (char *) malloc(strlen(myString)); // ogni carattere occupa un byte
  checkPointer(temp);
  
  wordTemp = wordList; // per tenere traccia dell'elemento precedente

  wordList = (struct word*) malloc(sizeof(struct word));
  checkPointer(wordList);
          
  strcpy(temp, myString); // in questo modo rimane sempre traccia di tutte le parole che sono state create

  wordList-> pString = temp;
  wordList-> pNextWord = wordTemp;
  
}
  

/********************************/

void printInverseList(void){
  struct word *pTemp = wordList;
  //  printf("ciao\n");
  while (pTemp != NULL){
    printf("%s\n", pTemp->pString);
    pTemp = pTemp->pNextWord;
  }
}

/********************************/

void buildDirectList(struct fromWord fW){
  char *temp, *myString;
  struct word *wordTemp, *myStart;
  myString = fW.scratch;

  
  if (wordList != NULL){
    
    myStart = (wordList->pStart);
    
    temp = (char *) malloc(strlen(myString)); // ogni carattere occupa un byte
    checkPointer(temp);
    
    strcpy(temp, myString);
    
    wordTemp = (struct word *)malloc(sizeof(struct word));
    checkPointer(wordTemp);
    
    wordTemp->pString = temp;
    wordList->pNextWord = wordTemp;
    wordList = wordList->pNextWord;
    wordList->pStart = myStart;
    
  } else {
    // la prima allocazione è un po' particolare
    temp = (char *) malloc(strlen(myString)); // ogni carattere occupa un byte
    checkPointer(temp);
    
    strcpy(temp, myString);
    
    wordTemp = (struct word *)malloc(sizeof(struct word));
    checkPointer(wordTemp);
    
    wordList = wordTemp;
    wordList->pString = temp;
    wordList->pStart = wordList;
    
  }
   
}

/********************************/

void printDirectList(void){
  struct word *pTemp;
  for (pTemp = wordList->pStart; pTemp != NULL;){
    printf("%s\n", pTemp->pString);
    pTemp = pTemp->pNextWord;
  }
}

/********************************/
/********************************/
