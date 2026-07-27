#!/usr/bin/bash
set -eu

fbuild="build"
ftmp=$(mktemp -d)

mv $fbuild/_deps "$ftmp/_deps"
rm -rf $fbuild && mkdir $fbuild
mv "$ftmp/_deps" $fbuild/_deps

clear
