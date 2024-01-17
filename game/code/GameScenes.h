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
#include "constants.h"


// Concernant la création et la gestion des scènes, tout ce qui concerne également les différents rendus,
// nous nous sommes largement inspiré d'un lien Github qui nous a été fourni, concernant un jeu créé lors
// d'une global game jam (2022 ici)
// lien source : https://github.com/Hatunruna/ggj2022/tree/main/code/bits

namespace swiftness {

    // On déclare juste avant notre structure GameCenter, afin de tout pouvoir gérer
    // et de le placer en paramètre du constructeur de la classe
    struct GameCenter;

    class GameScenes : public gf::Scene {
        public:
            // Constructeur
            GameScenes(GameCenter& game);
            // Destructeur
            ~GameScenes() override;

            // Méthodes virtuelles privées héritant directement de gf::Scene
            /*void handleActions(gf::Window& window);
            void render(gf::RenderTarget& target, const gf::RenderStates &states);
            void show();*/ 
            
        private:
            // Tous ces attributs vont nous servir à gérer de manière correcte les scènes, à savoir : 
            /*
                - les boutons
                - les actions concernant ces boutons (le crédit, jouer une partie, quitter le jeu)
            */
            // Merci pour l'astuce ;) !
            //gf::Scene scene;
            //gf::Action action;
            //gf::SegueEffect effect;
            //gf::Texture& background;
            GameCenter& game;
            gf::Action quit_a;
            gf::Action up;
            gf::Action questionmark;
            gf::Action down;
            gf::Action trigger;
            gf::Font font;
            gf::TextButtonWidget quit_b;
            gf::TextButtonWidget credits;
            gf::TextButtonWidget choose_level;
            gf::TextButtonWidget questionmark_b;
            gf::WidgetContainer widgets;
    };
}
