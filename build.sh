#!/bin/bash
rm ./ok
gcc main.c -o ok -L. -ltreeavl -Wl,-rpath,. -I.
