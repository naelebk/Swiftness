#pragma once
#ifndef GAME_CENTER_H
#define GAME_CENTER_H

#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/ResourceManager.h>
#include <gf/Paths.h>
#include "scene/MenuScene.h"
#include "scene/SelectLevelScene.h"
#include "scene/startScene.h"
#include "scene/pauseScene.h"
#include "scene/creditScene.h"
#include "constants.h"
#include "entity/squareEntity.h"
#include "entity/plateformEntity.h"
#include <vector>
#include <map>
#include <memory>
#include <stdlib.h>

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::ResourceManager& resources, gf::Font& font);
        SelectLevel level;
        Menu menu;
        CreditScene credits;
        StartScene start;
        pauseScene s_pause;
        gf::Font& font;
    };
}

#endif // GAME_CENTER_H