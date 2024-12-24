gcc gas.c -o gas -lm -Wall -O3

# Usage: ./gas L rho coeff totalTime


./gas 80 0.3 1 2000 > gas3
echo 'Finita una simulazione\n'
./gas 80 0.4 1 2000 > gas4
echo 'Finita una simulazione\n'
./gas 80 0.5 1 2000 > gas5
echo 'Finita una simulazione\n'
./gas 80 0.6 1 2000 > gas6
echo 'Finita una simulazione\n'
./gas 80 0.7 1 2000 > gas7
echo 'Finita una simulazione\n'
./gas 80 0.8 1 2000 > gas8
echo 'Finita una simulazione\n'

paste gas3 gas4 gas5 gas6 gas7 gas8 > gas.txt

python3 gasFine.py gas.txt


rm gas3 gas4 gas5 gas6 gas7 gas8
