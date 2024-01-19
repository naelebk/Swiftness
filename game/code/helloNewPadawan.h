#pragma once
#include <gf/Scene.h>
#include <gf/Entity.h>
#include <gf/Vector.h>
#include <gf/Font.h>
#include <gf/Text.h>
#include <gf/Window.h>
#include <gf/Mouse.h>
#include <gf/VectorOps.h> 
#include <gf/Gamepad.h>
#include <iostream>
#include <map>
#include <cstdlib>
#include "constants.h"
#include "staticPlateforme.h"
#include "level.h"
#include "squareEntity.h"
namespace swiftness {
    struct GameCenter;
    class MenuHello : public gf::Scene {
        public:
            // Constructeur
            MenuHello(GameCenter& game, gf::Font& font, int level);
            // Destructeur
            ~MenuHello();

            // Getter du niveau
            int getLevel();

            // Cette seconde fonction permet, dans une fenêtre graphique ou non selon le premier booléen,
            // de charger les différents paramètres du jeu en fonction du level
            // Check de la valeur de level tout de même, car sinon c po drôle
            void loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level);

        private:
            GameCenter& game;
            gf::Font& m_font;
            int level;
            gf::Text m_text;
    };
}