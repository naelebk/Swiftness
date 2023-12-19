#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace swiftness
{
    // constexpr float GRAVITY = 500.0f;
    constexpr float GRAVITY = 0.0f;
    constexpr float SPEED = 200.0f;
    constexpr float JUMP = -250.0f;
    constexpr float WALL_JUMP_SPEED = 210.0f;
    constexpr float WALL_JUMP_HEIGHT = -240.0f;
    // constexpr float GRAVITY_SQUARE = 500.0f;
    constexpr float GRAVITY_SQUARE = 0.0f;
    constexpr float SPEED_SQUARE = 100.0f;

    const std::string LEVELS_TMX_PATH = "../../ressources/tiles/levels/";
    const std::string LEVELS_TEXTURE_PATH = "../../ressources/tiles/image/";

} // namespace swiftness

#endif // CONSTANTS_H