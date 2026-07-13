#!/usr/bin/bash
set -eu

fbuild="build"

cmake -B $fbuild
cmake --build $fbuild
