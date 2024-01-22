#pragma once
#include <gf/Action.h>
#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/GameManager.h>
#include <gf/Math.h>
#include <gf/RenderTarget.h>
#include <gf/Scene.h>
#include <gf/SegueEffect.h>
#include <gf/Shapes.h>
#include <gf/Text.h>
#include <gf/Texture.h>
#include <gf/Time.h>
#include <gf/Vector.h>
#include <gf/View.h>
#include <gf/Views.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include <gf/Window.h>
#include <iostream>
#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>
#include "constants.h"
#include "staticPlateforme.h"
#include "level.h"
#include "squareEntity.h"
#include "commands.h"
#include "Input.h"
#include "levelRender.h"
namespace swiftness {
    struct GameCenter;
    class MenuHello : public gf::Scene {
        public:
            // Constructeur
            MenuHello(GameCenter& game, gf::Font& font, int level, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square, std::vector<Input>& enumVector);

            ~MenuHello();
            // Méthodes virtuelles privées héritant directement de gf::Scene
            void doHandleActions(gf::Window& window) override;
            void doRender (gf::RenderTarget& target, const gf::RenderStates &states) override;
            void doUpdate(gf::Time time) override;
            
            // Getter du niveau
            int getLevel();

            // Update the scene with the menu
            void updateLevel(int s_level);

            // Cette seconde fonction permet, dans une fenêtre graphique ou non selon le premier booléen,
            // de charger les différents paramètres du jeu en fonction du level
            // Check de la valeur de level tout de même, car sinon c po drôle
            void loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level);

        private:
            GameCenter& game;
            gf::Font& m_font;
            gf::Action quit_a;
            int level;
            gf::Text m_text;
            std::map<int, swiftness::StaticPlateform> plateform;
            swiftness::Square square;
            std::vector<Input>& enumVector;
    };
}