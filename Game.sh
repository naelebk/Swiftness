#!/bin/bash
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RED='\033[0;31m'
NC='\033[0m'
FILE="file.txt"

# Fonction permettant de check les commandes
check_cmd() {
    if [[ $? -eq 0 ]]; then
        if [ -z "$1" ]; then 
            echo -e "${GREEN}OK.${NC}"
            rm -f "$2" > /dev/null 2>&1
        else 
            echo -e "${GREEN}OK pour $1.${NC}"
            rm -f "$2" > /dev/null 2>&1
        fi
    else
        if [ -z "$1" ]; then 
            echo -e "${RED}ERREUR !${NC}"
            cat "$2"
            rm -f "$2" > /dev/null 2>&1
            exit 1
        else
            echo -e "${RED}ERREUR pour $1.${NC}"
            cat "$2"
            rm -f "$2" > /dev/null 2>&1
            exit 1
        fi
    fi
}
echo -ne "${YELLOW}Accès au répertoire game..... ${NC}"
cd game > "$FILE" 2>&1
check_cmd "" "../$FILE"
if [[ ! -d "build" ]]; then
	echo -ne "${YELLOW}Création du répertoire build pour compilation des sources..... ${NC}"
	mkdir build > "$FILE" 2>&1
	check_cmd "" $FILE
	echo -ne "${YELLOW}Permissions du répertoire build pour compilation des sources..... ${NC}"
	chmod -R 755 build > "$FILE" 2>&1
	check_cmd "" $FILE
fi
echo -ne "${YELLOW}Accès au répertoire build..... ${NC}"
cd build > "$FILE" 2>&1
check_cmd "" "../$FILE"
echo -ne "${YELLOW}Appel au script CMake pour création du Makefile..... ${NC}"
cmake .. > "$FILE" 2>&1
check_cmd "" $FILE
echo -ne "${YELLOW}Compilation du projet pour production de l'exécutable game..... ${NC}"
make > "$FILE" 2>&1
check_cmd "" $FILE
echo -ne "${YELLOW}Lancement du jeu..... ${NC}"
./game > /dev/null 2>&1
check_cmd "" $FILE
exit 0
