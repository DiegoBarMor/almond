#!/bin/bash
set -euo pipefail

folder_tmp=$(mktemp -d)

python3 scripts/pack_single_header/merge_cpp_hpp.py "almond" "$folder_tmp"
