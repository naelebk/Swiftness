#pragma once
#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/ResourceManager.h>
#include <gf/Paths.h>
#include "MenuScene.h"
#include "SelectLevelScene.h"
#include "constants.h"
#include "squareEntity.h"
#include "staticPlateforme.h"
#include "Input.h"
#include <vector>
#include <map>
#include <memory>
#include <stdlib.h>

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::ResourceManager resources);
        SelectLevel level;
        Menu menu;
        gf::Font& font;
    };
}