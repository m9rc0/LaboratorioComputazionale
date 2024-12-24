gcc gas.c -o gas -lm -Wall -O3

./gas 80 0.5 1 2000 > gas.txt

python3 gas.py gas.txt
