#pragma once
#ifndef GAME_CENTER_H
#define GAME_CENTER_H

#include <gf/GameManager.h>
#include <gf/Font.h>
#include <gf/Window.h>
#include <gf/ResourceManager.h>
#include <gf/Paths.h>
#include "scene/MenuScene.h"
#include "scene/selectLevelScene.h"
#include "scene/selectCustomLevelScene.h"
#include "scene/startScene.h"
//#include "scene/pauseScene.h"
#include "scene/creditScene.h"
#include "constants.h"
#include "entity/heroEntity.h"
#include "entity/plateformEntity.h"
#include "audioManager.h"
#include <vector>
#include <map>
#include <memory>
#include <stdlib.h>

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter(gf::Font& font);
        SelectLevel level;
        SelectCustomLevel custom;
        Menu menu;
        CreditScene credits;
        StartScene start;
        //pauseScene s_pause;
        gf::Font& font;
        AudioManager audioManager;
        sf::Music& mainTheme;
        sf::Music& levelTheme;
        sf::Sound& jumpSound;
        sf::Sound& notifSound;
    };
}

#endif // GAME_CENTER_H