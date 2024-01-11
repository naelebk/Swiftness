#include <gf/Scene.h>
#include <iostream>
#include <cstdlib>
#include "constants.h"
#include "staticPlateforme.h"
#include "level.h"
#include "squareEntity.h"
namespace swiftness {
    class Hello {
        public:
            // Constructeur
            Hello();
            // Destructeur
            ~Hello();

            // Fonction permettant, dans un premier temps en ligne de commande,
            // de permettre à l'utilisateur de choisir le niveau auquel il
            // veut jouer, en fonction du niveau choisi, on appelera la fonction
            // adéquate permettant de charger ce niveau
            int askLevel();

            // Cette seconde fonction permet, dans un premier temps en ligne de commande,
            // de charger les différents paramètres du jeu en fonction du level
            // Check de la valeur de level tout de même, car sinon c po drôle
            void loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square);

            // Cette fonction permet d'effectuer les affichages sur la console 
            // pour avoir un joli affichage
            void displayWelcomeMenu(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square);
        private:
    };
}