#!/usr/bin/bash
set -eu

fbuild="build"

bash scripts/examples/build.sh

for folder in "$fbuild/bin/examples/"*; do
    exec_name="app_$(basename "$folder")"
    (cd "$folder" && ./"$exec_name") &
done
wait
