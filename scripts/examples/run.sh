#!/usr/bin/bash
set -eu

if [ ! -d "scripts" ]; then
    echo "Error: script must be run in the project folder containing the 'scripts' directory."
    exit 1
fi

fbuild="build"

if [ ! -d "$fbuild" ]; then
    echo "Build folder does not exist. Run 'scripts/examples/build.sh' first."
    exit 1
fi

for folder in "$fbuild/"*; do
    (cd "$folder" && ./app) &
done
wait
