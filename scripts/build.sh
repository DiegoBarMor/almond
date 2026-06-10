#!/usr/bin/bash
set -eu

fbuild="build-linux"

cmake -B $fbuild
cmake --build $fbuild

for exec in "$fbuild/bin/examples/"*/app*; do
    parent="$(dirname "$exec")"
    rm -f "$parent/app"
    mv "$exec" "$parent/app"
done
