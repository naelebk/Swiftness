# Swiftness

>
> ***Projet Licence informatique (S5)***
>
>> *Développeur :*
>>
>>- **Julien GAUTHIER**
>>- **Théo HUMBERT**
>>- **Naël EMBARKI**
>
> : : *Historique de l'avancement du projet* : :

## Test

>
>> *04/10/2023*
>> **Naël**
>
>- Création du projet GitHub, accord du projet
>

## Modification pour oral

>
>> *10/10/2023*
>> **Naël**
>
>- Modification du support pour l'oral du projet
>

## Makefile

>
>> *13/10/2023*
>> **Naël**
>
>- Ajout d'un Makefile pour compiler les sources de l'oral et du rapport
>- Prochaine étape : développement d'une interface  graphique simple en C++
>- Prochainement : modélisation du projet (diagrammes UML)
>

## Première petite interface graphique

>
>> *15/10/2023*
>> **Julien** | **Naël** | **Théo**
>
>- Installation de GF (Gamedev Framework) sur machines personnels.
>- Compilation d'un tutoriel exemple et voir que l'interface graphique fonctionne
>- Scripts ajouté pour recompiler toutes les sources du projet depuis son PC.
>

## Réorganisation du git

>
>> *23/10/2023*
>> **Julien**
>
>- Tous ce qui a un rapport avec la présentation de mars à été placé dans le dossier support
>- Tous ce qui à été tester et fait dans experiments et main à été placé dans le dossier expériments
>- Suppression de la branche expériments (les branches ne servent pas à ça : elle permettent de faire de modification en attente de merge avec la branche principale)
>- Création d'un dossier script pour le script d'installation (peut-être à supprimer)
>- Création de HISTORIC.md pour écrire les avancements du projet (prend la place du README.md)
>- Le README à été effacé pour ne mettre que le nom du projet, une breve description et comment lancer le jeux
>- Création du dossier game pour placer le code
>- Création de data pour placer les assets, sons, musique du jeu
>

## Ajout d'un .gitignore

>
>> *24/10/2023*
>> **?**
>
>- Le .gitignore sert à référencer des fichier à ignorer lors des add, commit et remove
>- Voir le fichier pour savoir ce qui est ignoré lors des command git
>

## début projet finale

>
>> *09/11/2023*
>> **Julien** | **Naël** | **Théo**
>
>- Suppression de asset
>- Ajout des fichier tester fonctionnel (à peu près) dans game bin
>- Création du dossier build
>- Création d'un tile set pour le niveau 1 avec un asset trouver sur itch.io
>

## debut de gestion de niveau

>
>> *13/11/2023*
>> **Julien**
>
>- Création de level.cc et level.h
>- Modification en conséquence de main.cc et CMakeLists.txt
>- Level permet d'initialiser toute les plateforme d'un niveau
>- L'idée derrière level est de générer une fonction par niveau qui crée les plateformes
>- C'est une classe temporaire pour simplifier main.cc le temps que l'on implémente les tiles
>

## gestion tmx

>
>> *28/11/2023*
>> **Julien**
>
>- création de la branche tmx pour modifié en profondeur les classes liée au tmx
>

## amélioration du saut

>
>> *29/11/2023*
>> **Naël** | **Théo**
>
>- ajout d'un double saut
>- ajout du wall-jump (pas encore terminé)
>

## ajout d'obstacle et d'un bouton inverseur de gravité

>
>> *20/12/2023*
>> **Théo**
>
>- création de plateforme qui tue le joueur si il les touches
>- création d'un objet qui une fois touché, change la gravité pour nous attiré vers le haut
>

## tmx loader et plateforme générer

>
>> *20/12/2023*
>> **Julien**
>
>- le fichier tmx renvoie les information demander
>- il génère toute les plateforme mais pas à la bonne position
>

## refactoring pour mieux gérer les écrans et les positions

>
>> *28/12/2023*
>> **Julien**
>
>- ajout dans constants.h des taille de screen et de windows
>- plateforme positionner au bon endroit
>

## Correction du bug du Wall Jump

>
>> *09/01/2024*
>> **Théo**
>
>- Correction du bug sur le Wall Jump, modification de squareEntity.cc
>

## Ajout d'un menu au lancement du jeu

>
>> *11-13/01/2024*
>> **Naël**
>
>- Ajout d'un menu contextuelle (en ligne de commandes dans un premier temps) proposant à l'utilisateur de choisir le niveau qu'il souhaite faire
>- Dans un second temps, ajout d'une interface graphique avec boutons pour que l'utilisateur effectue ce choix
>

## gestion des objet avec le fichier tmx

>
>> *13/01/2024*
>> **Julien**
>
>- On peut maintenant crée des bouton changement de gravité et des murs tueurs à partir des tile tmx
>- Ajout de beaucoup d'asset pixel art pour les portail de début et fin de niveau, murs tueurs, bouton gravité et portail de choix de niveau
>