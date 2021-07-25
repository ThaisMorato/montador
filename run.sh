#!/bin/sh

make clean
make
./bin/montador tst/med.amv > ../emulador/tst/ex.mv 
echo "\n"
../emulador/bin/emulador ../emulador/tst/ex.mv
