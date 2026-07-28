#!/bin/bash
set -euo pipefail

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
