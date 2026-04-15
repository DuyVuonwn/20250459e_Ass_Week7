#!/bin/bash
gcc -c hashtable.c
ar rcs libhash.a hashtable.o
gcc main.c -L. -lhash -o app
./app