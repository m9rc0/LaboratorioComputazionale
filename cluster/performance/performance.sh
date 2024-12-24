gcc algoritmoNormale.c -o algoritmoNormale -Wall
gcc algoritmoListe.c -o algoritmoListe -Wall

SEED=$(date +%s)
echo "Si utilizza lo stesso seed così da far lavorare i programmi con gli stessi identici cluster"
echo "Seed: " $SEED

./algoritmoListe $1 $2 $3 $SEED
./algoritmoNormale $1 $2 $3 $SEED

