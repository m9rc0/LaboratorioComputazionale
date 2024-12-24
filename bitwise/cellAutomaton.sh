gcc cellAutomaton.c -o cellAutomaton -Wall -lm



./cellAutomaton 90 > cell90.txt
./cellAutomaton 150 > cell150.txt
./cellAutomaton 101 > cell101.txt
./cellAutomaton 20 > cell20.txt

python3 cellAutomaton.py
