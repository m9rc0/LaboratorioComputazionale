/*
  File con le prime funzioni per le operazioni bit a bit 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RIGHT 1
#define LEFT 0

unsigned int fieldSelect(unsigned int word, unsigned int position, unsigned int size);
void printToBinary(unsigned int word);
unsigned int fieldBack(unsigned int word, unsigned int position, unsigned int size);
unsigned int rotate(unsigned int word, unsigned int direction, unsigned int size);

int main(){
  unsigned  int  a = 0x98a24387;
  printToBinary(a);
  a = rotate(a, LEFT, 4);
  return 9;
}

/************ FUNZIONI **********/

unsigned int fieldSelect(unsigned int word, unsigned int position, unsigned int size){
  unsigned int maschera;

  // preparo la maschera: tutti 0 tranne size 1 tutti a destra
  maschera = ~(~0u << size);
  //printToBinary(maschera);
  // sposto a destra la parola per avere i bit che mi servono allineati a destra
  word = word >> (position + 1 - size);
  //printToBinary(word);
  return word & maschera;
}

/***************************************************/

void printToBinary(unsigned int word){
  unsigned  int size, i, maschera ;
  size = 8*sizeof(unsigned int);
  maschera = pow(2, size-1);
  for (i = 1; i <= size; i++){
    if (maschera == (maschera & word)){
      printf("%c", '1');
    } else{
      printf("%c", '0');
    }
    maschera /= 2;
  }
  printf("\n");
}

/***************************************************/

unsigned int fieldBack(unsigned int word, unsigned int position, unsigned int size){
  return word << (position +1 -size);
}

/***************************************************/

unsigned int rotate(unsigned int word, unsigned int direction, unsigned int size){
  unsigned int typeSize, temporaryStorage;
  
  typeSize = 8*sizeof(unsigned int);
  
  if (direction == RIGHT){
    // conservo i bit che andrebbero persi
    temporaryStorage = ~(~0u << size) & word;

    // lo sposto a destra
    temporaryStorage = temporaryStorage << (typeSize - size);
    word = (word >> size) | temporaryStorage;
    
  } else if (direction == LEFT){
    // conservo i bit che andrebbero persi
    temporaryStorage = ~(~0u >> size) & word;

    // lo sposto a sinistra
    temporaryStorage = temporaryStorage >> (typeSize - size);
    word = (word << size) | temporaryStorage;

  } else printf("ERRORE!\n");

  return word;
}
/***************************************************/
