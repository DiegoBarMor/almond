#!/usr/bin/bash
set -eu

fbuild="build"
ftmp="tmp"

mkdir -p $ftmp/_deps/sfml-build
mv $fbuild/bin $ftmp/bin
mv $fbuild/_deps/sfml-build/lib $ftmp/_deps/sfml-build/lib

rm -rf $fbuild
mv $ftmp $fbuild

clear
