gcc istogramma.c -o istogramma -lm -Wall

# runnare almeno una volta lo script cammini2D.sh 
# creo i file con le colonne da plottare utilizzando gawk

gawk '/T 10 / {print $6}' cammini2D.txt > t10.txt
gawk '/T 100 / {print $6}' cammini2D.txt > t100.txt
gawk '/T 1000 / {print $6}' cammini2D.txt > t1000.txt
gawk '/T 10000 / {print $6}' cammini2D.txt > t10000.txt

./istogramma t10.txt > hist10.txt
./istogramma t100.txt > hist100.txt
./istogramma t1000.txt > hist1000.txt
./istogramma t10000.txt > hist10000.txt

python3 istogrammiOneVariable.py

rm t10.txt t100.txt t1000.txt t10000.txt hist10.txt hist100.txt hist1000.txt hist10000.txt
