#pragma once
#include <gf/Action.h>
#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Font.h>
#include <gf/GameManager.h>
#include <gf/Log.h>
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
#include <vector>
#include "constants.h"
#include "staticPlateforme.h"
#include "level.h"
#include "squareEntity.h"
#include "helloNewPadawan.h"

namespace swiftness {
    struct GameCenter;
    class SelectLevel : public gf::Scene {
        public:
            // Constructeur
            SelectLevel(GameCenter& game, gf::Font& font, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square);
            // Desctructeur
            ~SelectLevel() override;

            gf::WidgetContainer GameLevel_getWidgets();

            // Méthodes virtuelles privées héritant directement de gf::Scene
            void doHandleActions(gf::Window& window) override;
            void doRender (gf::RenderTarget& target, const gf::RenderStates &states) override;
            void doProcessEvent(gf::Event& event) override;
            void doShow() override;

        private:
            GameCenter& game;
            gf::Font& font;
            gf::Action up;
            gf::Action down;
            gf::Action trigger;
            gf::Action quit;
            gf::WidgetContainer widgets;
            std::vector<gf::TextButtonWidget> levels_b;
            std::vector<MenuHello> helloWorld;
            std::size_t index;
            std::map<int, swiftness::StaticPlateform> plateform;
            swiftness::Square square;

    };
}