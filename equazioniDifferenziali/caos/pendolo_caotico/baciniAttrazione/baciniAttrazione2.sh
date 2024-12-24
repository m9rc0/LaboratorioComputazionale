gcc baciniAttrazione2.c -o baciniAttrazione2 -lm -pedantic -O3

# se si vuole provare il programma scegliere numero basso (eg. 100), per avere immagini ad alta risoluzione si scelga numero più alto (eq. 500) ma ci vuole molto tempo

echo "Scegliere il numero di condizioni iniziali per lato nello spazio delle fasi\n per provare il programma scegliere numero basso (eg. 100), per immagini ad alta risoluzione numero più alto(eg. 500)\n"
read SIDE


./baciniAttrazione2 92 $SIDE nero1.txt giallo1.txt

./baciniAttrazione2 92.5 $SIDE nero2.txt giallo2.txt

./baciniAttrazione2 93 $SIDE nero3.txt giallo3.txt

./baciniAttrazione2 93.5 $SIDE nero4.txt giallo4.txt

python3 baciniAttrazione2.py 92 92.5 93 93.5
