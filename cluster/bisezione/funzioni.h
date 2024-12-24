void checkPointer(void *p);
void initCluster (long int L, double p);
void inizio(long int L);
void initNeighbour(long int L);
long int siteUpdateList (long int direction, long int site);
void findConnections (long int L);
long int findExtended(long int L);

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
void initCluster (long int L, double p){
  long int i, j, a, max = L*L-1, nGuasti;
    nGuasti=(long int)(L*L*p + 0.5);
  // all'inizio sono tutti dei cluster isolati
  for (i = 0; i < L; i++){
    for (j = 0; j < L; j++){
      temp[j + L*i] = j + L*i;
      cluster[j+i*L].spin = '+';
      cluster[j+i*L].next = cluster + (j + i*L);
      cluster[j+i*L].former = cluster + (j + i*L);
      cluster[j+i*L].parent = cluster + (j + i*L);
      cluster[j+i*L].son = cluster + (j + i*L);
    }
  }
  
  for (i = nGuasti-1; i >= 0; i--){
    a = (long int)(drand48()*max);
    //    printf ("%lu %lu\n", temp[a], a);
    cluster[temp[a]].spin = '-';
    temp[a] = temp[max];
    max--;
  }

  // per vedere se fatto bene
  /* for (long int i =0; i<L; i++) { */
  /* for (long int j=0; j<L; j++) { */
  /*   printf ("%c ", cluster[j+i*L].spin); */
  /* } */
  /* printf ("\n"); */
}



/*******************************/

void inizio(long int L){
  // libero gli array se precedentemente usati
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
    //    change += siteUpdateList ((long int)RIGHT, i);
    change += siteUpdateList ((long int)LEFT, i);
    //    change += siteUpdateList ((long int)UP, i);
    change += siteUpdateList ((long int)DOWN, i);
  }
  //  printf ("#numero cambiamenti: %lu\n", change);
}


/*******************************/

long int findExtended(long int L){
  // usa la condizione che un cluster tocchi sopra e sotto, dice se nel reticolo c'è un cluster esteso
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

