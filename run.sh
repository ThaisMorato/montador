#!/bin/sh

make clean
make
./bin/montador tst/inst.amv > ../emulador/tst/ex.mv 
cat ../emulador/tst/ex.mv 
echo "\n"
../emulador/bin/vm ../emulador/tst/ex.mv
echo "\n"
