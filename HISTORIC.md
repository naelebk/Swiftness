# Swiftness
Projet du S5, développé par Julien GAUTHIER, Théo HUMBERT et Naël EMBARKI, 3 étudiants en 3ème année de Licence Informatique

# Test - 04/10/2023
Création du projet GitHub, accord du projet


# Modification pour oral - 10/10/2023
Modification du support pour l'oral du projet
PowerPoint ==> Beamer (LaTeX)
Raison ==> flemme grandissante de booter sur windows uniquement pour faire le powerpoint pour l'oral du projet

# Makefile - 13/10/2023
Ajout d'un Makefile pour compiler les sources de l'oral et du rapport
Prochaine étape : développement d'une interface graphique simple en C++
Prochainement : modélisation du projet (diagrammes UML)

# Première petite interface graphique - 15/10/2023
Installation de GF (Gamedev Framework) sur machines personnels.
Compilation d'un tutoriel exemple et voir que l'interface graphique fonctionne
Scripts ajouté pour recompiler toutes les sources du projet depuis son PC.

# Réorganisation du git - 23/10/2023
- Tous ce qui a un rapport avec la présentation de mars à été placé dans le dossier support
- tous ce qui à été tester et fait dans experiments et main à été placé dans le dossier expériments
- suppression de la branche expériments (les branches ne servent pas à ça : elle permettent de faire de modification en attente de merge avec la branche principale)
- création d'un dossier script pour le script d'installation (peut-être à supprimer)
- création de HISTORIC.md pour écrire les avancements du projet (prend la place du README.md)
- le README à été effacé pour ne mettre que le nom du projet, une breve description et comment lancer le jeux
- création du dossier game pour placer le code
- création de data pour placer les assets, sons, musique du jeu

# Ajout d'un .gitignore - 24/10/2023
le .gitignore sert à référencer des fichier à ignorer lors des add, commit et remove
voir le fichier pour savoir ce qui est ignoré lors des command git

# début projet finale - 09/11/2023
- Suppression de asset
- ajout des fichier tester fonctionnel (à peu près) dans game bin
- création du dossier build
- création d'un tile set pour le niveau 1 avec un asset trouver sur itch.io

# debut de gestion de niveau - 13/11/2023
- création de level.cc et level.h
- modification en conséquence de main.cc et CMakeLists.txt
- level permet d'initialiser toute les plateforme d'un niveau
- l'idée derrière level est de générer une fonction par niveau qui crée les plateformes
- c'est une classe temporaire pour simplifier main.cc le temps que l'on implémente les tiles

# gestion tmx - 28/11/2023
- en difficulté depuis 2 semaine
- création de la branche tmx pour modifié en profondeur les classes liée au tmx
