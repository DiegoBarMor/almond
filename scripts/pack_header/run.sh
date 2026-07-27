#!/bin/bash
set -euo pipefail

folder_tmp0=$(mktemp -d)
folder_tmp1=$(mktemp -d)

python3 scripts/pack_header/merge_cpp_hpp.py "almond" "$folder_tmp0"
python3 scripts/pack_header/pop_system_headers.py "$folder_tmp0" "$folder_tmp1" # creates "system_includes.txt"

echo "#include \"core/app.hpp\"" > "$folder_tmp1/main.cpp"

gcc -E -P -x c++ -std=c++17 "$folder_tmp1/main.cpp" -I "$folder_tmp1" -o "$folder_tmp1/almond.cpp"
{
    echo "#pragma once";
    cat "$folder_tmp1/system_includes.txt";
    echo;
    echo "// ALMOND v$(cat almond/version.txt)";
    echo "// Single header last modified: $(date +%Y%m%d_%H%M%S)";
    cat "$folder_tmp1/almond.cpp";
} >> "$folder_tmp1/almond.hpp"

mv "$folder_tmp1/almond.hpp" almond.hpp
