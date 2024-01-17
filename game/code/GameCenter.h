#pragma once
#include <gf/GameManager.h>
#include "GameScenes.h"
#include "GameLevel.h"

namespace swiftness {
    struct GameCenter : gf::GameManager {
        GameCenter();
        SelectLevel level;
    };
}