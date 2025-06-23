#!/bin/bash

set -e

echo "Instalando dependencias del sistema para Counter-Strike 2D..."

sudo apt-get update
sudo apt-get install -y build-essential cmake \
    libopus-dev libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth libwavpack1 libwavpack-dev libfreetype-dev wavpack libsdl2-gfx-dev \
    libsdl2-mixer-dev libsdl2-ttf-dev \
    qtbase5-dev qt5-qmake qtbase5-dev-tools libyaml-cpp-dev \
    
echo "Dependencias instaladas correctamente."
