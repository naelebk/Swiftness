#!/bin/dash
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RED='\033[0;31m'
NC='\033[0m'

# SCRIPT À EXÉCUTER EN TANT QUE ROOT DANS LE RÉPERTOIRE "Sources" du projet

ME=$(whoami)
if [ "$ME" != "root" ]; then
    echo "${RED}Erreur : le script doit être exécuté en tant que superutilisateur (root).${NC}" 2>&1
    exit 1
fi
MOI=$LOGNAME
apt-get install libsdl2-dev libboost-dev libfreetype6-dev zlib1g-dev libpugixml-dev cmake
if [ ! -d "gf" ]; then
	sudo -u "$MOI" git clone https://github.com/GamedevFramework/gf.git
	sudo -u "$MOI" chmod -R 755 gf
	sudo -u "$MOI" chmod -R 755 gf/*
fi
cd gf
sudo -u "$MOI" git submodule update --init
sudo -u "$MOI" mkdir build
cd build
sudo -u "$MOI" cmake ../ -DGF_BUILD_GAMES=ON -DGF_BUILD_TOOLS=ON
sudo -u "$MOI" make
make install
