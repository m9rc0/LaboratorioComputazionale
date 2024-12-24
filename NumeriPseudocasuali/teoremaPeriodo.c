/*
  Questo programma verifica il teorema del massimo periodo, cercando il periodo di generatori a congruenze lineari e verificando se le condizioni iniziali verificano le ipotesi del teorema
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long long int TYPE;
#define DES "%llu"

TYPE findPeriod(TYPE a, TYPE b, TYPE m, TYPE seed);
int commonDivisor(TYPE prime[], int nprimes, TYPE b, TYPE m);
TYPE primes(TYPE primi[], TYPE m);
int verifyTheorem(TYPE a, TYPE b, TYPE m);

int main(int argc, char *argv[]){
  TYPE a, b, m, seed, period;
  int proof;

  if (argc != 5){
    printf("Usage: ./nameExec a b m seed\n");
    exit(-7);
  }
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  m = atoi(argv[3]);
  seed = atoi(argv[4]);


  
  period = findPeriod(a, b, m, seed);
  proof = verifyTheorem(a, b, m);
  printf("a = " DES ", b = " DES ", seed = " DES "\n", a, b, seed);
  printf("m = " DES ", period = " DES ", proof = %i\n", m, period, proof);
  
  if ((period == m) && (proof == 1)){
    printf("Il sistema ha periodo massimo e il teorema è verificato\n");
  } else if ((period  < m) && (proof > 1)){
    printf("Il sistema non ha periodo massimo e il teorema è verificato\n");
  } else {
    printf("C'è qualche errore\n");
  }

  return 9;
}

/*
  FUNZIONI
 */


/***********************************************/

TYPE findPeriod(TYPE a, TYPE b, TYPE m, TYPE seed){
  TYPE *tau, randomNumber, period, i = 1;
  int bool = 0;

  // allocazione di memoria per i risultati
  tau = calloc(m, sizeof(TYPE));
  if (tau == NULL){
    printf("Errore nell'allocazinoe di memoria!\n");
    exit(-9);
  }

  // inizializzo il generatore con il seed
  randomNumber = seed;
  tau[randomNumber] = 1;
  
  while ((bool == 0) && (i <= m)){
    randomNumber = (a * randomNumber + b) % m;
    i++;
    if (tau[randomNumber] == 0){
      //      printf(DES "\n", randomNumber);

      tau[randomNumber] = i;
    } else {
      period = i - tau[randomNumber];
      bool = 1;

    }
  }
  free(tau);

  if (bool != 0){
    return period;    
  } else {
    printf("Errore con la ricerca del periodo\n");
    exit(-8);
  }

}

/***********************************************/

int verifyTheorem(TYPE a, TYPE b, TYPE m){

  int proof = 1, i;
  TYPE *primi, nprimes;

  // allocazione di memorie per i numeri primi minori di m
  primi = malloc(m * sizeof(TYPE));
  if (primi == NULL){
    printf("Errore con allocazione memoria\n");
    exit(-8);
  }

  nprimes = primes(primi, m);

  // controllo che b e m non abbiano divisori in comune 
  proof += commonDivisor(primi, nprimes, b, m);
  //  printf("proof = %i\n", proof);

  // controllo che a-1 sia multiplo di ogni primo divisore di m
  for (i = 0; i < nprimes; i++){
    if (((m % primi[i]) == 0) && (((a-1) % primi[i]) != 0)){
      proof += 1;
    }
  }
  // printf("proof = %i\n", proof);
  
  // controllo che se m è multiplo di 4 lo sia anche a-1
  if (((m % 4) == 0) && (((a-1) % 4) != 0)){
    proof += 1;
  }
  //  printf("proof = %i\n", proof);

  free(primi);
  // se proof è ancora uguale a 1 le ipotesi sono confermate, se maggiore allora qualche ipotesi non lo è
  return proof;
}

/***********************************************/

TYPE primes(TYPE primi[], TYPE m){
  TYPE i, count = 0;
  // cerca tutti i numeri primi minori di m 
  for (i = 2; i < m; i++){
    int j = 2, jMax = (int)sqrt(i) + 1;
    while((j < jMax)&&(i % j)){
      j++;
    }
    if (j == jMax){
      primi[count] = i;
      //      printf("err, primo = " DES "\n", i);
      count++;
    }
  }
  return count;
}

/***********************************************/

int commonDivisor(TYPE prime[], int nprimes, TYPE b, TYPE m){
  // ritorna 1 se ci sono divisori in comune, 0 se non ci sono 
  for (int i = 0; i < nprimes; i++){
    if (((b % prime[i]) == 0) && ((m % prime[i]) == 0)) {
      return 1;
    }
  }
  return 0;
}

/***********************************************/
/***********************************************/
