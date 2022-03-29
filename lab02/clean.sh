#!/bin/sh

for d in */; do
  echo "Cleaning $d"
  make -C $d clean
done
