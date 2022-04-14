#!/bin/bash
./z4 -f -w Nitra -W > z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -i >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 42.123 -p 16 -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 48.431 -e abc >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 100.169 -e 19.302 >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -w "Spisska Bela" >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -w Detva -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -w Bratislava -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -i toast >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -i onion >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -i burger -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 48.873 -e 19.234 >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 48.789 -e 20.340 -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -t taquito >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -t avocado >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -t cake -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -t water -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -p 10 >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -p 0 >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -p 6 -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -w "Kysucke Nove Mesto" -t cookie -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -i waffle -t waffle >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -i hamburger -p 5 -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 48.272 -e 19.820 -p 10 -W >> z4o.txt
echo "Exit code: " $? >> z4o.txt
./z4 -n 49.211 -e 19.300 -t chocolate >> z4o.txt
echo "Exit code: " $? >> z4o.txt