#!/usr/bin/bash
set -eu

fbuild="build"

for folder in "$fbuild/bin/examples/"*; do
    exec_name="app_$(basename "$folder")"
    (cd "$folder" && ./"$exec_name") &
done
wait
