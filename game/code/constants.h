#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace swiftness
{
    // Gravity
    constexpr float GRAVITY = 500.0f;
    // constexpr float GRAVITY = 0.0f;
    constexpr float GRAVITY_SQUARE = 500.0f;
    // constexpr float GRAVITY_SQUARE = 0.0f;

    // Speed
    constexpr float SPEED = 200.0f;
    constexpr float JUMP = -250.0f;
    constexpr float WALL_JUMP_SPEED = 210.0f;
    constexpr float WALL_JUMP_HEIGHT = -240.0f;
    constexpr float SPEED_SQUARE = 100.0f;

    // Window
    constexpr int WINDOW_WIDTH = 1920.0f;
    constexpr int WINDOW_HEIGHT = 1080.0f;

    // Screen
    constexpr float SCREEN_WIDTH = 800.0f;
    constexpr float SCREEN_HEIGHT = 600.0f;

    // Levels
    constexpr int MIN_LEVEL = 0;
    constexpr int MAX_LEVEL = 4;

    const std::string LEVELS_TMX_PATH = "../../ressources/Levels/Maps/";
    const std::string TEXTURE_BACKGROUND_PATH = "../../ressources/tiles/Images/background/";
    const std::string TEXTURE_SKIN_PATH = "../../ressources/Levels/Images/skin/";

} // namespace swiftness

#endif // CONSTANTS_H