#pragma once
#ifndef CREDIT_SCENE_H
#define CREDIT_SCENE_H

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
#include "constants.h"
#include <gf/Coordinates.h>

namespace swiftness {
    struct GameCenter;
    class CreditScene : public gf::Scene {
        public:
            // Constructeur
            CreditScene(GameCenter& game, gf::Font& font);
            // Desctructeur
            ~CreditScene() override;

            // Méthodes virtuelles privées héritant directement de gf::Scene
            void doHandleActions(gf::Window& window) override;
            void doRender (gf::RenderTarget& target, const gf::RenderStates &states) override;
            void doProcessEvent(gf::Event& event) override;
            void doShow() override;

        private:
            GameCenter& game;
            gf::Font& font;
            gf::Action trigger;
            gf::Action quit;
            gf::WidgetContainer widgets;
            gf::TextButtonWidget mainmenu;

    };
}

#endif // CREDIT_SCENE_H