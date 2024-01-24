#pragma once
#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include "MenuScene.h"
#include "GameLevel.h"
#include "constants.h"
#include "squareEntity.h"
#include "staticPlateforme.h"
#include "Input.h"
#include <vector>

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::Font& font, std::vector<swiftness::StaticPlateform>& plateform, swiftness::Square& square, std::vector<Input>& enumVector, gf::Vector2f& camera);
        SelectLevel level;
        Menu menu;
        levelScene levels;
    };
}