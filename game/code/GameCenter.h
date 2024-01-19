#pragma once
#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include "GameScenes.h"
#include "GameLevel.h"
#include "helloNewPadawan.h"

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::Font& font);
        SelectLevel level;
        GameScenes menu;
        MenuHello helloWorld;
    };
}