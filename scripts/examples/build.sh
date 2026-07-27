#!/bin/bash
set -euo pipefail

bash scripts/pack_header/run.sh

for folder in examples/*; do
    if [ ! -d "$folder" ]; then continue; fi
    cp almond.hpp "$folder/almond.hpp"
done

bash scripts/build.sh
