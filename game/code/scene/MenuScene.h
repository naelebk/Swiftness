#pragma once
#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include <gf/Action.h>
#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/GameManager.h>
#include <gf/Math.h>
#include <gf/RenderTarget.h>
#include <gf/Scene.h>
#include <gf/SegueEffects.h>
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
#include <gf/Easings.h>
#include <gf/Time.h>
#include <gf/SceneManager.h>
#include <gf/Coordinates.h>
#include <cstdlib>
#include "../constants.h"
#include "creditScene.h"


// Concernant la création et la gestion des scènes, tout ce qui concerne également les différents rendus,
// nous nous sommes largement inspiré d'un lien Github qui nous a été fourni, concernant un jeu créé lors
// d'une global game jam (2022 ici)
// lien source : https://github.com/Hatunruna/ggj2022/tree/main/code/bits

namespace swiftness {

    // On déclare juste avant notre structure GameCenter, afin de tout pouvoir gérer
    // et de le placer en paramètre du constructeur de la classe
    struct GameCenter;

    class Menu : public gf::Scene {
        public:
            // Constructeur
            Menu(GameCenter& game);
            // Destructeur
            ~Menu() override;

            gf::WidgetContainer MenuScene_getWidgets();

            // Méthodes virtuelles privées héritant directement de gf::Scene
            void doHandleActions(gf::Window& window) override;
            void doRender (gf::RenderTarget& target, const gf::RenderStates &states) override;
            void doProcessEvent(gf::Event& event) override;
            void doShow() override; 
            
        private:
            // Tous ces attributs vont nous servir à gérer de manière correcte les scènes, à savoir : 
            /*
                - les boutons
                - les actions concernant ces boutons (le crédit, jouer une partie, quitter le jeu)
            */
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
            gf::FadeSegueEffect fade;
    };
}

#endif // MENU_SCENE_H