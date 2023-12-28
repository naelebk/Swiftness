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

    const std::string LEVELS_TMX_PATH = "../../ressources/tiles/levels/";
    const std::string LEVELS_TEXTURE_PATH = "../../ressources/tiles/image/";

} // namespace swiftness

#endif // CONSTANTS_H