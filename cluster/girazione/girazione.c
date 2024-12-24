#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define PMIN 0.52
#define PMAX 0.68

struct siteCluster {
  char spin;
  struct siteCluster *next;
  struct siteCluster *former;
  struct siteCluster *parent;
  struct siteCluster *son;
  long int posx;
  long int posy;
};

void checkPointer(void *p);
long int inizio(long int L, double p);
void initCluster (long int L, long int nGuasti);
void initNeighbour(long int L);
void findConnections (long int L);
long int siteUpdateList (long int direction, long int site);
long int findExtended(long int L);
void findTwoGreatest(long int L);
long int findDimension(struct siteCluster *genitore);
double girazione(long int L, int b);
int findBaricentro (long int L);

struct siteCluster *cluster, **maggiori;
long int *temp, *neighbour[4], dimensioni[2];
double bar[2];

int main(int argc, char *argv[]){
  long int nGuasti, L = 100;
  double p, gir, nsimul = 40;
  
  srand48(time(0));

  //  printf("%lu\n", nGuasti);
  
    for (p = PMIN; p<=PMAX; p+=0.005) {
      nGuasti = inizio (L,p);
      gir = 0;
      for (long int i = 0; i < nsimul; i++){
	initCluster(L, nGuasti);
	findConnections(L);
	findTwoGreatest(L);
	gir += girazione(L,findBaricentro(L));
    }
      gir /= nsimul;
      printf ("%lf %lf\n", p, gir);
    }  
  return 9;
}

/*********************** FUNZIONI ****************************/

/*******************************/
void checkPointer(void *p)
{
  if (p == NULL)
    {
      printf("Errore con il puntatore!\n");
      exit(-1);
    }
  
}
/*******************************/
void initCluster (long int L, long int nGuasti){
  long int i, j, a, max = L*L-1;
  // all'inizio sono tutti dei cluster isolati
  for (i = 0; i < L; i++){
    for (j = 0; j < L; j++){
      temp[j + L*i] = j + L*i;
      cluster[j+i*L].spin = '+';
      cluster[j+i*L].next = cluster + (j + i*L);
      cluster[j+i*L].former = cluster + (j + i*L);
      cluster[j+i*L].parent = cluster + (j + i*L);
      cluster[j+i*L].son = cluster + (j + i*L);
      cluster[j+i*L].posx = j;
      cluster[j+i*L].posy = i;
    }
  }
  
  for (i = nGuasti-1; i >= 0; i--){
    a = (long int)(drand48()*max);
    //    printf ("%lu %lu\n", temp[a], a);
    cluster[temp[a]].spin = '-';
    temp[a] = temp[max];
    max--;
  }
  
}



/*******************************/

long int inizio(long int L, double p){
  long int nGuasti;
  nGuasti=(long int)(L*L*p + 0.5);
  free(cluster);
  free(temp);
  for (int i = 0; i < 4; i++){
    free(neighbour[i]);    
  }


  cluster = (struct siteCluster *) malloc(L*L*sizeof(struct siteCluster));
  checkPointer(cluster);

  temp = (long int *) malloc(L*L*sizeof(long int));
  checkPointer(temp);

  initNeighbour (L);

  return nGuasti;
}

/*******************************/

void initNeighbour(long int L){
  long int i, j;
  // riserviamo memoria per gli array
  for (i = 0; i < 4; i++){
    neighbour[i] = (long int *) malloc(L*L*sizeof(long int));
    checkPointer(neighbour);
  }

  for (i = 0; i < L; i++){
    for (j = 0; j < L; j++){
      neighbour[UP][j + L*i] = j + L*(i-1);
      neighbour[DOWN][j + L*i] = j + L*(i+1);
      neighbour[LEFT][j + L*i] = (j-1) + L*i;
      neighbour[RIGHT][j + L*i] = (j+1) + L*i;
    }
  }
  // al bordo si punta a sè stessi
  for (i = 0; i < L; i++){
    neighbour[UP][i] = i;
    neighbour[DOWN][i+L*(L-1)] = i+j*(L-1);
    neighbour[LEFT][i*L] = L*i;
    neighbour[RIGHT][L-1 + i*L] = L-1 + L*i;
  }
}

/*******************************/

long int siteUpdateList (long int direction, long int site) {
  long int n, change=0, lowerSite, upperSite;
  struct siteCluster *upperHead, *upperTail, *lowerHead, *lowerTail, *scratch;
  n = neighbour[direction][site];

  if ((cluster[site].spin == cluster[n].spin) && (cluster[site].parent != cluster[n].parent)){
    change = 1;
    if (cluster[site].parent < cluster[n].parent) {
      lowerSite = site;
      upperSite = n;
    }
    else {
      lowerSite = n;
      upperSite = site;
    }

    upperHead = cluster[upperSite].parent;
    upperTail = cluster[upperSite].son;
    lowerHead = cluster[lowerSite].parent;
    lowerTail = cluster[lowerSite].son;

    scratch = upperHead;
    scratch->parent = lowerHead;
    while (scratch != scratch->next) {
      scratch = scratch->next;
      scratch->parent = lowerHead;
    }

    scratch = lowerHead;
    scratch->son = upperTail;
    while (scratch != scratch->next) {
      scratch = scratch->next;
      scratch->son = upperTail;
    }

    lowerTail->next = upperHead;
    upperHead->former = lowerTail;    
  }

  return change;
}

/*******************************/

void findConnections (long int L){
  long int i,change = 1;

  
  for (i=0; i<L*L; i++){
    //      printf("%lu\n", i);
    change += siteUpdateList ((long int)RIGHT, i);
    change += siteUpdateList ((long int)LEFT, i);
    change += siteUpdateList ((long int)UP, i);
    change += siteUpdateList ((long int)DOWN, i);	  
  }
  //  printf ("#numero cambiamenti: %lu\n", change);
  
}


/*******************************/

long int findExtended(long int L){
  // usa la condizione che un cluster tocchi sopra e sotto
  long int i, j;

  for (i = 0; i < L; i++){
    for (j = 0; j < L; j++){
      if ((cluster[j].parent == cluster[i+L*(L-1)].parent)&&(cluster[j].spin == '-')){
	return 1;
      }      
    }
  }
  return 0;
}

/*******************************/

void findTwoGreatest(long int L){
  long int i, j, n=0, flag, k;
  free(maggiori);
  dimensioni[0] = 0;
  dimensioni[1] = 0;
  maggiori = NULL;
  for (i = 0; i < L*L; i++){
    flag = 0;
    for (j = 0; j < n; j++){
      if (cluster[i].parent == maggiori[j]){
	flag++;
      }
    }
    if ((flag == 0)&&(cluster[i].spin == '-')){
      n++;
      maggiori = (struct siteCluster **)realloc(maggiori, 2 * sizeof(struct siteCluster *));
      checkPointer(maggiori);
      
      k = findDimension(cluster[i].parent);
      if (k > dimensioni[0]) {
	dimensioni[1] = dimensioni[0];
	dimensioni[0] = k;
	maggiori[1] = maggiori[0];
	maggiori[0] = cluster[i].parent;
      }
      else if ((k < dimensioni[0]) && (k > dimensioni[1])) {
	dimensioni[1] = k;
	maggiori[1] = cluster[i].parent;
      }
    }
  }
}

/*******************************/

long int findDimension(struct siteCluster *genitore){
  long int size = 1;
  struct siteCluster *scratch;
  scratch = genitore;
  while (scratch->next != scratch){
    size++;
    scratch = scratch->next;
      }
  return size;
}

/*******************************/

int findBaricentro (long int L) {
  int k;
  bar[0] = 0;
  bar[1] = 0;
  struct siteCluster *scratch;
  k = findExtended(L);
  findTwoGreatest(L);
  if (k == 0) {
    scratch = maggiori[0];
    while (scratch->next != scratch){
      bar[0] += (double)scratch->posx;
      bar[1] += (double)scratch->posy;
      scratch = scratch->next;
    }
    bar[0] /= (double)dimensioni[0];
    bar[1] /= (double)dimensioni[0];
  }
  if (k == 1) {
    scratch = maggiori[1];
    while (scratch->next != scratch){
      bar[0] += (double)scratch->posx;
      bar[1] += (double)scratch->posy;
      scratch = scratch->next;
    }
    bar[0] /= (double)dimensioni[1];
    bar[1] /= (double)dimensioni[1];
  }
  return k;
}

/*******************************/

double girazione(long int L, int b) {
  double g=0;
  struct siteCluster *scratch;
  scratch = maggiori[b];
  while (scratch->next != scratch) {
    g += (pow((double)scratch->posx - bar[0],2) + pow((double)scratch->posy - bar[1],2));
    scratch = scratch->next;
  }
  g /= (double)dimensioni[b];
  g = pow(g,0.5);
  return g;
}

/*******************************/




