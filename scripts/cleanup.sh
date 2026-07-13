#!/usr/bin/bash
set -eu

fbuild="build"
ftmp="_tmp_build"

mkdir -p $ftmp/_deps
mv $fbuild/_deps $ftmp/_deps

rm -rf $fbuild
mv $ftmp $fbuild

clear
