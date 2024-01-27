# Comment construire un niveau de Swiftness avec Tiled

---

## 0 : Préparer le terrain

- Installer [Tiled](https://thorbjorn.itch.io/tiled)
- si ce n'est pas fait installer python3

- Dans Tiled, ouvrez un projet (File>Open file or project |ctrl + o)
- - selection le fichier ressources/Levels/switness.tiled-project

- afficher les propriété avec View>Views and Toolbars>Properties

**Vous êtes maintenant prêt à construire vos niveau custom !**
Il y a 5 niveau customisable, si vous voulez en crée plus vous pouvez copier custom_template dans un nouveau fichier.tmx et nommé le custom0X (il ne peut y avoir que 5 niveau, donc renommer un fichier en old_custom0X)
par exemple renommé custom04 en old_custom04 et le nouveau fichier sera donc nommé custom04

## 1 : la map

avant de vous attaquer à la création de votre niveau, il faut vérifier la validité du fichier tmx. Pour cela utiliser le programme python fournit :

>
> dans un terminal :
> > si vous êtes dans le dossier custom : `python3 ../../tmxValidator.py ./nomDufichierTmxàTester`
> > si vous êtes dans ressouces/Levels : `python3 tmxValidator.py ./Maps/custom/nomDufichierTmxàTester`
>

corriger les \[ERROR\] avant de commencer

vous pouvez redimensionner la map à votre convenance en faisant Map>Resize Map

## 2 : Les Layers

voici un résumer de ce à quoi servent chaque layers :

>
> IO | tileset associé : 2_Portal
>> entrée-sortie du niveau
>> Les six tuile du portail bleu servent à indiquer le début du niveau
>> Les six tuile du portail jaune servent à indiquer la fin du niveau
>
<!---->
>
> Border | tileset associé : 1_utilities
>> les limites du niveau
>> dessiner 4 murs au limite du niveau en beige
>> attention à ne pas dessiner les coins du niveau !!!
>> pour ne pas afficher ces bordures, mettez la layer en invisible en cliquant sur l'oeil à coté du nom de la layer
>
<!---->
>
> Wall_of_death_v / Wall_of_death_h / Wall_of_death / Wall_of_death_bloc | tileset associé : 6_wall_of_death
>> murs de mort verticaux horizontaux et en bloc
>> permet de dessiner les murs de la morts,
>> ranger les murs en fonction de leurs orientation et pour les murs collé 2 par 2 metté les dans bloc
>
<!---->
>
> Collision_v / Collision_h / Collision_bloc | tileset associé : 3_futuristic_city
>> murs verticaux, horizontaux et en bloc
>> comme pour les murs de la mort mais ça ne vous tue pas
>
<!---->
>
> gravity_switch | layer objet
>> cette layer permet de crée les objet qui serviront a changer la gravité (les gravity-switch et les gravity-flows)
>> pour correspondre aux tileset il y a 4 taille d'objet validé et on ne peut faire que des rectangles
>> les 4 tailles sont :
>> W->8 H->12
>> W->12 H->8
>> W->16 H->un multiple de 16
>> W->un multiple de 16 H->16
>>
>> les objet 8/12 doivent être placé au pixel prêt au centre des tuiles pour leur valeur à 8px (à 4px du bord de la tuile)
>> les objet 16/XX doivent être placé à des coordonné modulo 16 pour rester dans la grille 16X16 de la map
>>
>> il y a 4 classes d'objet (up, down, left, right) en fonction de la nouvelle direction de la gravité
>>
>> les propriété à modifié pour chaque objet sont donc Width, Height, X, Y et class
>
<!---->
>
> Filling | tileset associé : 3_futuristic_city / 4_gravity_switch / 5_gravity_flow / 9_arrow / 10_alpha / 11_alpha_key
>> cette layer permet de remplir les tuile qui ne sont pas touchable
>> elle permet de faire le remplissage des structure, de mettre l'affichage des gravity switch et flow sur les objet
>> et de mettre les lettres pour afficher des messages
>>
>> pour les gravity switch, choisissez bien les bouton avec les fleche pointant dans la bonne direction
>>
>> pour les gravity flow, choisissez la même couleur que les bouton
>
<!---->
>
> Decoration | tileset associé : 3_futuristic_city
>> cette layer permet d'afficher les pancartes bleu et verte et les flèche sur les gravity flow
>> faite attention au code couleur entre les boutons, les gravity flow et les flèches !
>
<!---->
>
> gravity_walls | layer objet
>> cette layer permet de crée les portes qui s'ouvres en fonction de la gravité
>> pour correspondre aux tileset les tailles doivent être des multiple de 16
>>
>> les position doivent être aussi des multiple de 16 pour rester sur la grille
>>
>> il y a 4 classes d'objet (up, down, left, right) en fonction de la gravité d'ouverture de la porte (une porte qui s'ouvre quand la gravité est vers le bas sera de classe down)
>>
>> les propriété à modifié pour chaque objet sont donc Width, Height, X, Y et class
>
<!---->
>
> Gw_blue / Gw_rose / Gw_green / Gw_orange | tileset associé : 7_gravity_walls
>> ces layers permet d'afficher les portes
>> respecter le même code couleur que les boutons
>
<!---->
>
> Gw_blue_open / Gw_rose_open / Gw_green_open / Gw_orange_open | tileset associé : 8_gravity_walls_open
>> comme pour les layers précédente, ces layer servent à afficher les portes mais ouvertes cette fois
>

## 3 : truc et astuce

je vous conseil fortement de regarder comment ont été fait les niveau de ressources/Maps !!
