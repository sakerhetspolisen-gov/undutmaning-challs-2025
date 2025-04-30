#!/bin/sh

for i in $(seq 1 $PARALLEL_RENODE_INSTANCES); do
  (while true; do ./glitch-emulator.py $i; done) &
done
./serve.sh
