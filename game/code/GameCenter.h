#pragma once
#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include "GameScenes.h"
#include "GameLevel.h"
#include "constants.h"
#include "squareEntity.h"
#include "staticPlateforme.h"

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::Font& font, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square);
        SelectLevel level;
        GameScenes menu;
        MenuHello helloWorld;
    };
}