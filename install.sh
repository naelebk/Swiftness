#!/bin/bash
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RED='\033[0;31m'
NC='\033[0m'

check_cmd() {
    if [[ $? -eq 0 ]]; then
        if [ -z "$1" ]; then 
            echo -e "${GREEN}OK.${NC}"
        else 
            echo -e "${GREEN}OK pour $1.${NC}"
        fi
    else
        if [[ -z "$1" ]]; then 
            echo -e "${RED}ERREUR !${NC}"
            exit 42
        else
            echo -e "${RED}ERREUR pour $1.${NC}"
            exit 42
        fi
    fi
}

super_echo() {
    local first_color=$1
    local message=$2
    local end=$3
    case "$first_color" in
        RED)
            echo -ne "${RED}${message}${NC}"
            ;;
        PURPLE)
            echo -ne "${PURPLE}${message}${NC}"
            ;;
        YELLOW)
            echo -ne "${YELLOW}${message}${NC}"
            ;;
        GREEN)
            echo -ne "${GREEN}${message}${NC}"
            ;;
        WHITE)
            echo -n "${message}"
            ;;
        *)
            echo "Couleur non supportée : $first_color"
            return 1
            ;;
    esac
    if [[ "$end" == "n" ]]; then
        echo -n ""
    else
        echo ""
    fi
}

install_package() {
    PACKAGES_NAME=$@
    for PACKAGE_NAME in $PACKAGES_NAME; do
        super_echo YELLOW "Installation de $PACKAGE_NAME..... " n
        if [ -f /etc/debian_version ]; then
            sudo apt-get update > /dev/null 2>&1
            sudo apt-get install -y "$PACKAGE_NAME" > /dev/null 2>&1
        elif [ -f /etc/redhat-release ]; then
            if command -v dnf >/dev/null 2>&1; then
                sudo dnf install -y "$PACKAGE_NAME" > /dev/null 2>&1 
            else
                sudo yum install -y "$PACKAGE_NAME" > /dev/null 2>&1
            fi
        elif [ -f /etc/arch-release ]; then
            sudo pacman -Sy --noconfirm "$PACKAGE_NAME" > /dev/null 2>&1
        elif [ -f /etc/SuSE-release ]; then
            sudo zypper install -y "$PACKAGE_NAME" > /dev/null 2>&1
        elif [ -f /etc/gentoo-release ]; then
            sudo emerge --ask=n "$PACKAGE_NAME" > /dev/null 2>&1
        elif [ -f /etc/void-release ]; then
            sudo xbps-install -Sy "$PACKAGE_NAME" > /dev/null 2>&1
        elif [ -f /etc/slackware-version ]; then
            sudo slackpkg install "$PACKAGE_NAME" > /dev/null 2>&1
        else
            super_echo "RED" "Distribution non supportée pour cette installation."
            return 1
        fi
        check_cmd "$PACKAGE_NAME"
    done
    return 0
}

# SCRIPT À EXÉCUTER EN TANT QUE ROOT DANS LE RÉPERTOIRE "Sources" du projet
# SCRIPT À NE PAS EXÉCUTER DANS LE DÉPÔT GIT DE CE PROJET !
if [ $(id -u) -ne 0 ]; then
    echo "${RED}Erreur : le script doit être exécuté en tant que superutilisateur (root).${NC}" 2>&1
    exit 1
fi
PROJET=$PWD
MOI=$(who | grep ":0" | awk '{print $1}' | tr -s ' ')
install_package "git" "libsdl2-dev" "libsfml-dev" "libboost-dev" "libfreetype6-dev" "zlib1g-dev" "libpugixml-dev" "cmake"
test -f "/home/$MOI/.ssh/id_rsa.pub" || (super_echo RED "Git non configuré. Appelez le script 'git_config.sh' pour configurer git. Terminaison" && exit 2) 

gf="/home/$MOI/Documents"
super_echo YELLOW "Accès au répertoire pour gf ('$gf')..... " n
cd $gf
check_cmd ""
if [ ! -d "$gf/gf" ]; then
    super_echo YELLOW "Clonage de gf..... " n
    sudo -u "$MOI" git clone https://github.com/GamedevFramework/gf.git > /dev/null 2>&1
    check_cmd ""
    super_echo YELLOW "Permissions (1/2) de gf..... " n
    sudo -u "$MOI" chmod -R 755 gf > /dev/null 2>&1
    check_cmd ""
    super_echo YELLOW "Permissions (2/2) de gf..... " n
    sudo -u "$MOI" chmod -R 755 gf/* > /dev/null 2>&1
    check_cmd ""
fi
super_echo YELLOW "Accès au répertoire gf..... " n
cd gf > /dev/null 2>&1
check_cmd ""
super_echo YELLOW "Sous-modules (1/3) de gf..... "
sudo -u "$MOI" git submodule add git@github.com:nothings/stb.git Sources/gf/library/vendor/stb
check_cmd ""
super_echo YELLOW "Sous-modules (2/3) de gf..... "
sudo -u "$MOI" git submodule add git@github.com:google/googletest.git Sources/gf/tests/googletest/
check_cmd ""
super_echo YELLOW "Sous-modules (3/3) de gf..... "
sudo -u "$MOI" git submodule update --init
check_cmd ""
super_echo YELLOW "Création du répertoire build..... " n
sudo -u "$MOI" mkdir build > /dev/null 2>&1
check_cmd ""
super_echo YELLOW "Accès au répertoire build..... " n
cd build > /dev/null 2>&1
check_cmd ""
super_echo YELLOW "Compilation (1/3)....."
sudo -u "$MOI" cmake ../ -DGF_BUILD_GAMES=ON -DGF_BUILD_TOOLS=ON
check_cmd ""
super_echo YELLOW "Compilation (2/3)....."
sudo -u "$MOI" make
check_cmd ""
super_echo YELLOW "Compilation (3/3)....."
sudo -u "$MOI" make install
check_cmd ""
super_echo GREEN "OK tout est bon ! Vous pouvez lancer le script '$PROJET/Swiftness.sh' pour commencer à jouer."
