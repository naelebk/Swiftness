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

# Arguments : premier : PATH_SKIN, second : skin, troisième : FILE
renommage() {
    echo -ne "${YELLOW}Fin du script, renommage du skin de départ..... ${NC}"
    cp "$1/selected$ext" "$1/$2" > "$3" 2>&1
    check_cmd "" "$3"
    echo -ne "${YELLOW}Renommage en selected_cc$ext en selected$ext..... ${NC}"
    cp "$1/selected_cc$ext" "$1/selected$ext" > "$3" 2>&1
    check_cmd "" "$3"
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
#skin="jube"
check_cmd "choix du skin, le choix en question : $skin"
skin="$skin$ext"
if [[ -f "$PATH_SKIN/selected$ext" ]]; then
    echo -ne "${YELLOW}Le fichier selected$ext existait déjà, renommage en selected_cc$ext..... ${NC}"
    cp "$PATH_SKIN/selected$ext" "$PATH_SKIN/selected_cc$ext" > "$FILE" 2>&1
    check_cmd "" "$FILE"
fi
echo -ne "${YELLOW}Application du skin pour le jeu..... ${NC}"
cp "$PATH_SKIN/$skin" "$PATH_SKIN/selected$ext" > "$FILE" 2>&1
check_cmd "" "$FILE"
echo -ne "${YELLOW}Appel au script CMake pour création du Makefile..... ${NC}"
SFML=$(cmake .. | grep "SFML")
cm=$?
if [[ -z "$SFML" ]]; then
    echo -e "${RED}KO !\nErreur, vous devez installer SFML préalablement avant d'exécuter le script.${NC}"
    echo -e "${YELLOW}Synopsis : sudo COMMAND_FOR_INSTALL_A_PACKAGE libsfml-dev${NC}"
    renommage "$PATH_SKIN" "$skin" "$FILE"
    exit 1
elif [[ "$cm" -ne 0 ]]; then
    echo -e "${RED}KO !${NC}"
    renommage "$PATH_SKIN" "$skin" "$FILE"
    exit 1
else
    echo -e "${GREEN}OK.${NC}"
fi
echo -e "${YELLOW}Compilation du projet pour production de l'exécutable..... ${NC}"
make
if [[ "$?" -eq 0 ]]; then
    echo -e "${GREEN}OK.${NC}"
else
    renommage "$PATH_SKIN" "$skin" "$FILE"
    exit 1
fi
echo -ne "${YELLOW}Lancement du jeu..... ${NC}"
./swiftness > /dev/null 2>&1
if [[ "$?" -eq 0 ]]; then
    echo -e "${GREEN}OK.${NC}"
else
    echo -e "${RED}KO !${NC}"
    echo -ne "${YELLOW}Nettoyage des compilations..... ${NC}"
    make clean > "$FILE" 2>&1
    check_cmd "" "$FILE"
fi
renommage "$PATH_SKIN" "$skin" "$FILE"
exit 0
