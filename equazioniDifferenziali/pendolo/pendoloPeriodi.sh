gcc pendoloPeriodi.c -o pendoloPeriodi -lm -pedantic

./pendoloPeriodi | tee pendoloPeriodi.txt

python3 pendoloPeriodi.py
