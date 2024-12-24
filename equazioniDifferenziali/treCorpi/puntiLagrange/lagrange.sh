gcc lagrange.c -o lagrange -lm -Wall -pedantic

# per studiare il comportamento attorno a i punti di lagrange si scelgono le loro coordinate come condizioni iniziali e si da una piccola perturbazione alla velocità 

# non si è riuscito a plottarli tutto insieme perché le oscillazioni attorno ai punti stabili L4 e L5 sono troppo piccole rispetto alle scale degli altri moti

# attorno al punto L4
./lagrange 0.487849 0.866025 0.001 0.0001 > lagrange1.txt

# sinistra di L1
./lagrange 0.836915 0 -0.001 0 > lagrange3.txt

# destra di L1
./lagrange 0.836915 0 +0.001 0 > lagrange4.txt

# sinistra di L2
./lagrange 1.15568 0 -0.001 0 > lagrange6.txt


python3 lagrange1.py
python3 lagrange2.py
python3 lagrange3.py

rm lagrange1.txt lagrange3.txt lagrange4.txt lagrange6.txt
