#!/usr/bin/bash
set -eu

fbuild="build"
ftmp=$(mktemp -d)

mv $fbuild/_deps "$ftmp/_deps"
rm -rf $fbuild
mv "$ftmp/_deps" $fbuild/_deps

clear
