#!/bin/bash
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RED='\033[0;31m'
NC='\033[0m'
FILE="file.txt"
PATH_SKIN="../../ressources/levels/png/skin"
ext=".png"

# Fonction permettant de check les commandes
check_cmd() {
    if [[ $? -eq 0 ]]; then
        if [ -z "$1" ]; then 
            echo -e "${GREEN}OK.${NC}"
            if [[ -f "$2" ]]; then
                rm -f "$2" > /dev/null 2>&1
            fi
        else 
            echo -e "${GREEN}OK pour $1.${NC}"
            if [[ -f "$2" ]]; then
                rm -f "$2" > /dev/null 2>&1
            fi
        fi
    else
        if [ -z "$1" ]; then 
            echo -e "${RED}ERREUR !${NC}"
            if [[ -f "$2" ]]; then
                cat "$2"
                rm -f "$2" > /dev/null 2>&1
            fi
            exit 1
        else
            echo -e "${RED}ERREUR pour $1.${NC}"
            if [[ -f "$2" ]]; then
                cat "$2"
                rm -f "$2" > /dev/null 2>&1
            fi
            exit 1
        fi
    fi
}
clear
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
echo -ne "${YELLOW}Lecture du fichier skinName.txt pour sélection d'un skin..... ${NC}"
mapfile -t skinarray < "$PATH_SKIN/skinName.txt" > "$FILE" 2>&1
check_cmd "" "$FILE"
echo -ne "${YELLOW}Choix aléatoire du skin..... ${NC}"
skin="${skinarray[$((RANDOM % ${#skinarray[@]}))]}"
check_cmd "choix du skin, le choix en question : $skin"
skin="$skin$ext"
if [[ -f "$PATH_SKIN/selected$ext" ]]; then
    echo -ne "${YELLOW}Le fichier selected$ext existait déjà, renommage en selected_cc$ext..... ${NC}"
    mv "$PATH_SKIN/selected$ext" "$PATH_SKIN/selected_cc$ext" > "$FILE" 2>&1
    check_cmd "" "$FILE"
fi
echo -ne "${YELLOW}Application du skin pour le jeu..... ${NC}"
mv "$PATH_SKIN/$skin" "$PATH_SKIN/selected$ext" > "$FILE" 2>&1
check_cmd "" "$FILE"
check_cmd "renommage"
echo -ne "${YELLOW}Appel au script CMake pour création du Makefile..... ${NC}"
cmake .. > "$FILE" 2>&1
check_cmd "" $FILE
echo -e "${YELLOW}Compilation du projet pour production de l'exécutable..... ${NC}"
make
if [[ "$?" -eq 0 ]]; then
    echo -e "${GREEN}OK.${NC}"
else
    echo -e "${RED}KO !${NC}"
    exit 1
fi
echo -ne "${YELLOW}Lancement du jeu..... ${NC}"
./swiftness > /dev/null 2>&1
check_cmd "" $FILE
echo -ne "${YELLOW}Fin du script, renommage du skin de départ..... ${NC}"
mv "$PATH_SKIN/selected$ext" "$PATH_SKIN/$skin" > "$FILE" 2>&1
check_cmd "" "$FILE"
if [[ -f "$PATH_SKIN/selected_cc$ext" ]]; then
    echo -ne "${YELLOW}Renommage en selected_cc$ext en selected$ext..... ${NC}"
    mv "$PATH_SKIN/selected_cc$ext" "$PATH_SKIN/selected$ext" > "$FILE" 2>&1
    check_cmd "" "$FILE"
fi
exit 0
