#!/bin/bash
F=knowhow.c
I=./test_interface/interface/test_public/public/test_protected/protected/test_private/private/test_knowhow/knowhow
rm ./libtreeavl.so
gcc -shared -o libtreeavl.so -fPIC ${F} -I${I}
cp libtreeavl.so ..
cp libtreeavl.h ..
