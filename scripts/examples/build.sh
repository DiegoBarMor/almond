#!/bin/bash
set -euo pipefail

if [ ! -d "scripts" ]; then
    echo "Error: script must be run in the project folder containing the 'scripts' directory."
    exit 1
fi

bash scripts/pack_header/run.sh # generates "almond.hpp"

for folder_src in examples/*; do
    if [ ! -d "$folder_src" ]; then continue; fi
    (
        folder_build="build/$(basename "$folder_src")"
        cp almond.hpp "$folder_src/almond.hpp"
        bash scripts/build_project.sh "$folder_src" "$folder_build"
    ) &
done
wait

rm almond.hpp
