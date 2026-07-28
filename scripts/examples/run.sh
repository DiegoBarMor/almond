#!/usr/bin/bash
set -eu

fbuild="build"

# bash scripts/examples/build.sh

for folder in "$fbuild/"*; do
    (cd "$folder" && ./app) &
done
wait
