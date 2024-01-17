#!/bin/bash
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RED='\033[0;31m'
NC='\033[0m'

# Fonction permettant de check les commandes
check_cmd() {
    if [[ $? -eq 0 ]]; then
        if [ -z "$1" ]; then 
            echo -e "${GREEN}OK.${NC}"
        else 
            echo -e "${GREEN}OK pour $1.${NC}"
        fi
    else
        if [ -z "$1" ]; then 
            echo -e "${RED}ERREUR !${NC}"
            exit 1
        else
            echo -e "${RED}ERREUR pour $1.${NC}"
            exit 1
        fi
    fi
}

echo -ne "${YELLOW}Accès au répertoire game..... ${NC}"
cd game > /dev/null 2>&1
check_cmd ""
if [[ ! -d "build" ]]; then
	echo -ne "${YELLOW}Création du répertoire build pour compilation des sources..... ${NC}"
	mkdir build > /dev/null 2>&1
	check_cmd ""
	echo -ne "${YELLOW}Permissions du répertoire build pour compilation des sources..... ${NC}"
	chmod -R 755 build > /dev/null 2>&1
	check_cmd ""
fi
echo -ne "${YELLOW}Accès au répertoire build..... ${NC}"
cd build > /dev/null 2>&1
check_cmd ""
echo -ne "${YELLOW}Appel au script CMake pour création du Makefile..... ${NC}"
cmake .. > /dev/null 2>&1
check_cmd ""
echo -ne "${YELLOW}Compilation du projet pour production de l'exécutable game..... ${NC}"
make > /dev/null 2>&1
check_cmd ""
echo -ne "${YELLOW}Lancement du jeu..... ${NC}"
./game > /dev/null 2>&1
check_cmd ""
rm -f file
exit 0
