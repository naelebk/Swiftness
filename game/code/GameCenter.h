#pragma once
#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/ResourceManager.h>
#include <gf/Paths.h>
#include "MenuScene.h"
#include "SelectLevelScene.h"
#include "Start.h"
#include "pauseScene.h"
#include "Credits.h"
#include "constants.h"
#include "squareEntity.h"
#include "staticPlateforme.h"
#include <vector>
#include <map>
#include <memory>
#include <stdlib.h>

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::ResourceManager& resources, gf::Font& font);
        SelectLevel level;
        Menu menu;
        Credits credits;
        Start start;
        pauseScene s_pause;
        gf::Font& font;
    };
}