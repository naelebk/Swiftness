#include <gf/Scene.h>
#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Font.h>
#include <gf/Text.h>
#include <gf/Window.h>
#include <gf/Mouse.h>
#include <gf/VectorOps.h> 
#include <iostream>
#include <map>
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

    class MenuHello {
        public:
            // Constructeur
            MenuHello(gf::Font& font, gf::Window& window);
            // Destructeur
            ~MenuHello();

            // Getter du niveau
            int getLevel();

            // Fonction permettant, dans une fenêtre graphique,
            // de permettre à l'utilisateur de choisir le niveau auquel il
            // veut jouer, en fonction du niveau choisi, on appelera la fonction
            // adéquate permettant de charger ce niveau
            bool displayLevelSelection(gf::RenderWindow& render, gf::Window& window, gf::Event& event, gf::Font& font, int& selectedLevel);

            // Cette seconde fonction permet, dans une fenêtre graphique,
            // de charger les différents paramètres du jeu en fonction du level
            // Check de la valeur de level tout de même, car sinon c po drôle
            void loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level);

            // Cette fonction permet d'afficher le menu dans la fenêtre graphique
            void displayWelcomeMenu(gf::RenderWindow& render, gf::Window& window, gf::Font& font, std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square);
        private:
            gf::Font& m_font;
            gf::Window& m_window;
            int m_selectedLevel;
            gf::Text m_text;
    };
}