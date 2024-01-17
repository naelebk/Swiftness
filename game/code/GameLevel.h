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

namespace swiftness {
    struct GameCenter;
    class SelectLevel : public gf::Scene {
        public:
            // Constructeur
            SelectLevel(GameCenter& game);
            // Desctructeur
            ~SelectLevel() override;
            // Méthodes virtuelles privées héritant directement de gf::Scene
            /*void handleActions(gf::Window& window);
            void render(gf::RenderTarget& target, const gf::RenderStates &states);
            void show();*/

        private:
            GameCenter& game;
            gf::Action up;
            gf::Action down;
            gf::Action trigger;

    };
}