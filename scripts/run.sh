#!/usr/bin/bash
set -eu

fbuild="build-linux"

for folder in "$fbuild/bin/examples/"*; do
    (cd "$folder"; ./app) &
done
wait
