#include "entity/squareEntity.h"
#include "entity/plateformEntity.h"
#include "tmx/level.h"
#include "constants.h"
#include "scene/levelScene.h"
#include "tmx/levelRender.h"
#include "scene/startScene.h"
#include "scene/pauseScene.h"
#include "gameCenter.h"

#include <memory>
#include <gf/Clock.h>
#include <gf/Views.h>
#include <gf/View.h>
#include <gf/Color.h>
#include <gf/Gamepad.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/ResourceManager.h>
#include <gf/Paths.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/Window.h>
#include <gf/Math.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <thread>
#include <chrono>

using namespace swiftness;
using std::this_thread::sleep_for;

int main(int argc, char *argv[]) {
    // Initialize everything
    gf::ResourceManager resources;
    resources.addSearchDir(LEVELS_TMX_PATH);
    resources.addSearchDir(TILESETS_TSX_PATH);
    resources.addSearchDir(IMAGES_GAME);
    resources.addSearchDir(RESSOURCES_PATH);
    resources.addSearchDir(gf::Paths::getBasePath());
    resources.addSearchDir(gf::Paths::getCurrentPath());
    gf::Font font(PATH_FONT);
    swiftness::GameCenter game(resources, font);
    game.run(); 
    return 0;
}