gcc istogramma2Variables.c -o istogramma2Variables -Wall

#runnare almeno una volta lo script cammini2D.sh

# preparo i file su cui fare l'istogramma
gawk '/T 1000/ {print $6 " " $8}' cammini2D.txt > istogramma2Variables3.txt
gawk '/T 10000/ {print $6 " " $8}' cammini2D.txt > istogramma2Variables4.txt


# eseguo gli istogrammi e poi rimuovo tutte le colonne in cui non ci sono occorrenze 
./istogramma2Variables istogramma2Variables3.txt | gawk '! / 0.000000/' > istogramma2Variables33.txt

./istogramma2Variables istogramma2Variables4.txt | gawk '! / 0.000000/' > istogramma2Variables44.txt


python3 istogramma2Variables.py istogramma2Variables33.txt istogramma2Variables44.txt


# rimuovo tutti i file inutili che sono stati creati
rm istogramma2Variables3.txt istogramma2Variables4.txt istogramma2Variables33.txt istogramma2Variables44.txt
