#pragma once
#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/ResourceManager.h>
#include <gf/Paths.h>
#include "MenuScene.h"
#include "SelectLevelScene.h"
#include "startScene.h"
#include "pauseScene.h"
#include "creditScene.h"
#include "constants.h"
#include "squareEntity.h"
#include "plateformEntity.h"
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