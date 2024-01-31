#pragma once
#ifndef PAUSE_SCENE_H
#define PAUSE_SCENE_H

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
#include <gf/Easings.h>
#include <gf/Time.h>
#include <gf/SceneManager.h>
#include <gf/Coordinates.h>
#include <cstdlib>
#include <gf/Sprite.h>

namespace swiftness {
    struct GameCenter;
    class pauseScene : public gf::Scene {
        public:
            pauseScene(GameCenter& game, gf::Font& font);
            ~pauseScene();

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
            gf::TextButtonWidget quit_b;
            gf::TextButtonWidget back_b;
            gf::Texture& background;
            gf::WidgetContainer widgets;
    };
}

#endif // PAUSE_SCENE_H