#!/bin/sh

for d in */; do
  echo "Building $d"
  make -C $d clean
done
