#!/bin/bash
set -euo pipefail

sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype-dev \
    libharfbuzz-dev \
    libmbedtls-dev \
    libssh2-1-dev -y

cd ~
if [[ -d sfml ]]; then
    echo "SFML directory found, skipping cloning"
else
    git clone --depth 1 --branch 3.1.0 https://github.com/sfml/sfml.git
fi

cd "sfml"
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSFML_BUILD_EXAMPLES=OFF \
    -DSFML_BUILD_TEST_SUITE=OFF \
    -DSFML_BUILD_DOC=OFF \
    -DSFML_BUILD_AUDIO=ON \
    -DSFML_BUILD_GRAPHICS=ON \
    -DSFML_BUILD_WINDOW=ON \
    -DSFML_BUILD_NETWORK=ON \
    -DSFML_USE_SYSTEM_DEPS=ON \
    -DSFML_INSTALL_PKGCONFIG_FILES=ON
sudo cmake --build build --target install
sudo ldconfig
