#!/bin/bash
set -euo pipefail

folder_tmp0=$(mktemp -d)
folder_tmp1=$(mktemp -d)

python3 scripts/pack_single_header/merge_cpp_hpp.py "almond" "$folder_tmp0"
python3 scripts/pack_single_header/pop_system_headers.py "$folder_tmp0" "$folder_tmp1" # creates "system_includes.txt"
