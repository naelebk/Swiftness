#!/bin/bash
NC="\e[0m"
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
BOLD="\e[1m"
UNDERLINE="\e[4m"
if [[ "$#" -ne 2 ]]; then
	echo -e "${RED}Deux arguments exactement sont obligatoires.${NC}${YELLOW} Synopsis : $0 \"MESSAGE DE COMMIT\" BRANCHE${NC}"
	exit 1
fi
if [[ -z "$1" || "$1" =~ ^[[:space:]]+$ ]]; then
	echo -e "${RED}Le message de commit ne doit pas être vide.${NC}${YELLOW} Synopsis : $0 \"MESSAGE DE COMMIT\" BRANCHE${NC}"
	exit 2
fi
cd game
make clean
cd ..
git add *
git commit -m "$1"
git push origin $2
