#!/bin/bash

gcc *.c -Wall -Wextra -o z5 -lm

# Blok 1
./z5 -w Zeliezovce > z5o.txt 2>z5e.txt

# Blok 2
./z5 -w Zarnovica >> z5o.txt 2>>z5e.txt

# Blok 3
./z5 -w Velky_Meder >> z5o.txt 2>>z5e.txt

# Blok 4
./z5 -w Malacky >> z5o.txt 2>>z5e.txt

# Blok 5
./z5 -w Hrinova -a >> z5o.txt 2>>z5e.txt

# Blok 6
./z5 -w Dobsina -d >> z5o.txt 2>>z5e.txt

# Blok 7
./z5 -n 48.892 -e 18.039 >> z5o.txt 2>>z5e.txt

# Blok 8
./z5 -n 48.622 -e 18.368 -a >> z5o.txt 2>>z5e.txt

# Blok 9
./z5 -n 49.078 -e 19.940 -d >> z5o.txt 2>>z5e.txt