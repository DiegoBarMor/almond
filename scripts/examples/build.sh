#!/bin/bash
set -euo pipefail

if [ ! -d "scripts" ]; then
    echo "Error: script must be run in the project folder containing the 'scripts' directory."
    exit 1
fi

build_example() {
    local folder_src="$1"
    local folder_build
    if [ ! -d "$folder_src" ]; then
        echo "Error: source '$folder_src' is not a directory."
        return
    fi

    folder_build="build/$(basename "$folder_src")"
    cp almond.hpp "$folder_src/almond.hpp"
    bash scripts/build_project.sh "$folder_src" "$folder_build"
}

bash scripts/pack_header/run.sh # generates "almond.hpp"

(build_example "examples/00_basics") &
(build_example "examples/01_buttons") &
(build_example "examples/02_checkboxes") &
(build_example "examples/03_radiobuttons") &
(build_example "examples/04_tins_sliders") &
wait

rm almond.hpp
