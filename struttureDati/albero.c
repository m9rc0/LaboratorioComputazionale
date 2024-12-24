#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"

struct word{
  char *pString;
  struct word *pLeft;
  struct word *pRight;
} *treeRoot = NULL;

struct word* addToTree(struct word *input, char *parolina);
void printTree (struct word *questaParola);

int main(int argc, char *argv[]){
  FILE *fp;
  struct fromWord fW;
  if (argc != 2){
    printf("Usage: ./programma nomefile.txt\n");
    exit(-5);
  }
  fp = fopen(argv[1], "r");
  checkPointer(fp);
  fW.myEnd = 0;

  while (fW.myEnd != 1) {
    fW = readWord(fp);
    treeRoot = addToTree(treeRoot, fW.scratch);
  }

  printTree(treeRoot);

  return 9;
}


/*********************** FUNZIONI ************************/

struct word* addToTree(struct word *input, char *parolina) {
  int diff;

  if (input == NULL) {
    input = (struct word*) malloc(sizeof(struct word));
    checkPointer(input);
    input->pString = parolina;
    input->pLeft = input->pRight = NULL;
  }
  else if ((diff = strcmp(input->pString, parolina)) != 0) {
    if (diff > 0) {
      input->pLeft = addToTree(input->pLeft, parolina);
    }
    else {
      input->pRight = addToTree(input->pRight, parolina);
    }
  }
  return input;
}

/***********************************************/

void printTree (struct word *questaParola) {
  if (questaParola != NULL) {
    printTree(questaParola->pLeft);
    printf("%s\n", questaParola->pString);
    printTree(questaParola->pRight);
  }
}

/*************************************************/
