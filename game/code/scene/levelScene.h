#pragma once
#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

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
#include "../constants.h"
#include "../entity/plateformEntity.h"
#include "../entity/squareEntity.h"
#include "../tmx/levelGenerator.h"
#include "../tmx/levelRender.h"
#include "pauseScene.h"
namespace swiftness {
    struct GameCenter;
    class levelScene : public gf::Scene {
        public:
            // Constructeur
            levelScene(GameCenter& game, gf::Font& font, int level, bool custom);
            // Méthodes virtuelles privées héritant directement de gf::Scene
            void doHandleActions(gf::Window& window) override;
            void doRender (gf::RenderTarget& target, const gf::RenderStates &states) override;
            void doUpdate(gf::Time time) override;
            
            // Getter du niveau
            int getLevel();

            swiftness::Square& getSquare() { return m_level.getSquareEntity(); };
            std::vector<swiftness::PlateformEntity> getPlateforms() { return m_level.getPlateforms(); };

            // Update the scene with the menu
            void updateLevel(int s_level);

            // Cette seconde fonction permet, dans une fenêtre graphique ou non selon le premier booléen,
            // de charger les différents paramètres du jeu en fonction du level
            // Check de la valeur de level tout de même, car sinon c po drôle
            void loadLevel(int t_level);

            void customLoadLevel(int t_level);

        private:
            GameCenter& game;
            gf::Font& m_font;
            gf::Action up;
            gf::Action upJump;
            gf::Action down;
            gf::Action downJump;
            gf::Action left;
            gf::Action leftJump;
            gf::Action right;
            gf::Action rightJump;
            gf::Action jump;
            gf::Action Pause;
            int m_levelNumber;
            pauseScene s_pause;
            swiftness::LevelGenerator m_level;
            gf::Vector2f m_camera;
            float map_width, map_height, tile_width, tile_height, xcamera, ycamera;
            int konami, konami2;
            bool canFly, commandsChange, m_custom;
            gf::ZoomBlurSegueEffect trans;
    };
}

#endif // LEVEL_SCENE_H