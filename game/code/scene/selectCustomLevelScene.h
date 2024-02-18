#pragma once
#ifndef SELECT_CUSTOM_LEVEL_SCENE_H
#define SELECT_CUSTOM_LEVEL_SCENE_H

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
#include "../constants.h"
#include "../entity/plateformEntity.h"
#include "../entity/heroEntity.h"
#include "levelScene.h"

namespace swiftness {
    struct GameCenter;
    class SelectCustomLevel : public gf::Scene {
        public:
            // Constructeur
            SelectCustomLevel(GameCenter& game, gf::Font& font);
            // Desctructeur
            ~SelectCustomLevel() override;

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
            gf::Action left;
            gf::Action right;
            gf::Action trigger;
            gf::Action quit;
            gf::WidgetContainer widgets;
            std::vector<gf::TextButtonWidget> levels_b;
            gf::Vector2f m_camera;
            levelScene level01;
            levelScene level02;
            levelScene level03;
            levelScene level04;
	        levelScene level05;
            gf::ZoomBlurSegueEffect trans;
            gf::CheckerboardSegueEffect pixel;

    };
}

#endif // SELECT_CUSTOM_LEVEL_SCENE_H
