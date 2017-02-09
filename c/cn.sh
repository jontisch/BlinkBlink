#!/bin/sh
gcc -std=c++0x -c test.cpp
echo "test.cpp is compiled\n"
#gcc -c RCSwitch.cpp
#gcc -c Transmit.cpp
gcc -Wall -o a.out test.o RCSwitch.o Transmit.o -lwiringPi `mysql_config --cflags --libs`

#./a.out
