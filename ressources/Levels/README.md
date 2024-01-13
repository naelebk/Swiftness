# Comment construire un niveau de Swiftness avec Tiled

---

## 0 : Préparer le terrain

- Installer [Tiled](https://thorbjorn.itch.io/tiled)
***Pour faire un niveau swiftness ne faite pas les étapes marqué d'une " \* " mais faite les étapes marqué par un " # "***

>- **\*** crée cette arboresccence et placez vous dans **Levels** :
> 
>  Levels/
>
>  ├── Images
>
>  ├── Maps
> 
>  └── Tilesets
>- **#** depuis la racine de swiftness, allez dans **ressources/Levels**
>- **\*** Trouver ou créer des tilesets de ***16x16*** en png et rangez les dans **Images**
>- **\*** Avoir un tileset Special avec au moins 2 tuile que l'on nomme ***utilities*** pour plus de clarté
>- Lancer Tiled (si vous avez télécharger le fichier AppImage, rendez le éxécutable et éxécuter le)
>
>- **\*** Faites **File>New>New Project** et placé le à la racine de votre arborescence
>- **#** Faites **File>Open File or Project** et selectionner le .tiled-project
>- **\*** faite **File>New>New Tileset** et selectionner votre .png puis ranger votre nouveau .tsx dans un dossier nommer. n'oubliez pas de changer la taille des tuiles en **16x16** si necessaire
>- **\*** **répétez cette étape pour tous vos tileset**
>- faite **File>New>New Map** et choisissez le nombre de tuile. Changez la taille des tuiles en **16x16**
>
> Vous venez de créer votre première map et êtes prêts à faire votre niveau

---

## 1 : crée les layers

*tile layer* -> [t]
*object layer* -> [o]

**noms et ordre des layers :**
> [t] - IO
> 
> [t] - Border
>
> [t] - Collision_bloc
>
> [t] - Collision_v
> 
> [t] - Collision_h
> 
> [o] - Gravity_switch
> 
> [t] - Filling
> 
> [t] - Decoration

### IO

- Une tuile pour l'entrée (*utilities 0*)
- Une tuile pour la sortie (*utilities 1*)

### Border

- À chaque fois qu'un murs invisible est nécéssaire (*utilities 0*)

### Collision_bloc

- Tous les murs de 2 de largeur ou de hauteur (*tileset*)

  > **Exemple :**
  >> ||
  >> 
  >> ||
  >> 
  >> ||
  >> 
  >> est un bloc
  >>
  > <!---->
  >> \---
  >> 
  >> \---
  >> 
  >> est un bloc
  > <!---->
  >> \|-|
  >> 
  >> \|-|
  >> 
  >> \|-|
  >> 
  >> n'est pas un bloc
  > <!---->
  >> \---
  >> 
  >> |||
  >> 
  >> \---
  >> 
  >> n'est pas un bloc

### Collision_v

- Tous les murs verticaux (*tileset*)

### Collision_h

- Tous les murs horizontaux (*tileset*)

### Gravity_switch

- Crée des objet qui corresponde au bouton up et down qui inverse la gravité
  - Mettre la classe up pour le bouton qui change la gravité vers le haut
  - Mettre la classe down pour le bouton qui change la gravité vers le bas

### Filling

- Toutes les tuiles pour remplir les formes mais qui ne sont pas des murs (*tileset*)

### Decoration

- Toutes les tuiles qui ne rentre pas dans les précédentes layers (*tileset*)

---

## 2 : Création des plateformes

lorsqu'une plateforme verticale rejoint une plateforme horizontale dans un angle, toujours privilégié la plateforme verticale

> faire :
> 
> |--
> 
> |
> 
> |
>
> plutôt que :
> 
> \---
> 
> |
> 
> |

---

***N'utiliser le tileset utilities que dans des tiles invisible (Border et IO)***
