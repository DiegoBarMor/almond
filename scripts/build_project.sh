#!/bin/bash
set -euo pipefail

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <path_src> <path_build>"
    exit 1
fi

path_src=$1
path_build=$2

if [ ! -f "$path_src/layout.ndg" ]; then
    echo "Error: <path_src> must contain a 'layout.ndg' file."
    exit 1
fi

echo "Building '$path_src' into '$path_build'..."

mkdir -p "$path_build"
cp "$path_src/layout.ndg" "$path_build/layout.ndg"

########## Compiling
while IFS= read -r -d '' path_cpp; do
    stem="$(basename -s ".cpp" "$path_cpp")"
    path_o="$path_build/$stem.o"
    # shellcheck disable=SC2046
    g++ -c "$path_cpp" $(pkg-config --cflags sfml-all) -o "$path_o"
done <   <(find "$path_src" -name '*.cpp' -print0)

########## Linking
### the files in SFML/tools/pkg-config specify the library names without the -s "suffix"
### however, during installation, the libraries are named with the -s suffix (e.g. "libsfml-graphics-s.a" instead of "libsfml-graphics.a")
### the lines below are a workaround to fix this issue
sfml_libs=$(pkg-config --static --libs sfml-all)
sfml_libs=${sfml_libs//-lsfml-graphics/-lsfml-graphics-s}
sfml_libs=${sfml_libs//-lsfml-window/-lsfml-window-s}
sfml_libs=${sfml_libs//-lsfml-audio/-lsfml-audio-s}
sfml_libs=${sfml_libs//-lsfml-network/-lsfml-network-s}
sfml_libs=${sfml_libs//-lsfml-system/-lsfml-system-s}

# shellcheck disable=SC2086
g++ $path_build/*.o -o "$path_build/app" $sfml_libs -lX11 -lXrandr -lXi -lXcursor -ludev -ldl -pthread -lfreetype -lharfbuzz
