gcc treCorpi.c -o treCorpi -lm -Wall -pedantic

./treCorpi -0.3 -1.4 -0.8 0 0.1 0 0 1.4 > treCorpi1.txt

./treCorpi 0 1 1 0 0.1 0 0 1.6 > treCorpi2.txt

./treCorpi -0.4 0.3 -0.9 1.4 0.3 -0.4 0.2 0.6 > treCorpi3.txt

./treCorpi 1 0 1 0.5 1 -0.7 0.1 0.4 > treCorpi4.txt

python3 treCorpi.py 
