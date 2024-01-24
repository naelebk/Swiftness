#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <gf/Font.h>
namespace swiftness
{
    // Gravity
    constexpr float GRAVITY = 500.0f;
    // constexpr float GRAVITY = 0.0f;
    constexpr float GRAVITY_SQUARE = 500.0f;
    // constexpr float GRAVITY_SQUARE = 0.0f;

    constexpr int SQUARE_SIZE=13.0f;
    // Speed
    constexpr float SPEED = 200.0f;
    constexpr float JUMP = -250.0f;
    constexpr float WALL_JUMP_SPEED = 500.0f;
    constexpr float WALL_JUMP_HEIGHT = -240.0f;
    constexpr float SPEED_SQUARE = 100.0f;

    // Window
    constexpr int WINDOW_WIDTH = 1366.0f;
    constexpr int WINDOW_HEIGHT = 768.0f;

    // Screen
    constexpr float SCREEN_WIDTH = WINDOW_WIDTH/4.0f;
    constexpr float SCREEN_HEIGHT = WINDOW_HEIGHT/4.0f;

    // Levels
    constexpr int MIN_LEVEL = 0;
    constexpr int MAX_LEVEL = 7;

    // Resources
    const std::string PATH_FONT = "../../ressources/font/KarmaFuture.ttf";
    const std::string LEVELS_TMX_PATH = "../../ressources/Levels/Maps/";
    const std::string TILESETS_TSX_PATH = "../../ressources/Levels/Tilesets/";
    const std::string IMAGES_GAME = "../../ressources/Images/";
    const std::string TEXTURE_SKIN_PATH = "../../ressources/Levels/Images/skin/";
    const std::string RESSOURCES_PATH = "../../ressources";

    const int NB_TILE_LAYERS = 18;

} // namespace swiftness

#endif // CONSTANTS_H