#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <gf/Font.h>
namespace swiftness
{
    // Gravity
    constexpr float GRAVITY = 500.0f;
    constexpr float GRAVITY_SQUARE = 500.0f;

    constexpr int SQUARE_SIZE=13.0f;
    // Speed
    constexpr float SPEED = 200.0f;
    constexpr float JUMP = -250.0f;
    constexpr float WALL_JUMP_SPEED = 95.0f;
    constexpr float WALL_JUMP_HEIGHT = -200.0f;
    constexpr float WALL_JUMP_TIME = 0.5f;
    constexpr float SPEED_SQUARE = 100.0f;
    constexpr float SPEED_LIMIT = 1000.0f;

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

    // Layers
    const int NB_TILE_LAYERS = 18;

    enum class PlateformType
    {
        // 1_utilities
        utilities1 = 1,
        utilities2,

        // 2_portals
        blue_portal_up_left,
        blue_portal_up,
        blue_portal_up_right,
        red_portal_up_left,
        red_portal_up,
        red_portal_up_right,
        blue_portal_down_left,
        blue_portal,
        blue_portal_down_right,
        red_portal_down_left,
        red_portal,
        red_portal_down_right,
        green_portal_up_left,
        green_portal_up,
        green_portal_up_right,
        orange_portal_up_left,
        orange_portal_up,
        orange_portal_up_right,
        green_portal_down_left,
        green_portal,
        green_portal_down_right,
        orange_portal_down_left,
        orange_portal,
        orange_portal_down_right,
        ground_solo_left,

        // 3_futuristic_city
        groud_solo_middle,
        ground_solo_right,
        ground_solo_left_right,
        gate_1,
        gate_2,
        ground_bloc_left,
        ground_bloc_middle,
        ground_bloc_right,
        ground_bloc_left_right,
        deco_blue_1,
        deco_green_1,
        middle_bloc_left,
        middle_bloc_middle,
        middle_bloc_right,
        middle_bloc_left_right,
        deco_blue_2,
        deco_green_2,
        top_bloc_left,
        top_bloc_middle,
        top_bloc_right,
        top_bloc_left_right,
        deco_blue_3,
        deco_green_3,

        // 4_gravity_switch
        switch_blue_down,
        switch_blue_left,
        switch_blue_up,
        switch_blue_right,
        switch_yellow_down,
        switch_yellow_left,
        switch_yellow_up,
        switch_yellow_right,
        switch_green_down,
        switch_green_left,
        switch_green_up,
        switch_green_right,
        switch_pink_down,
        switch_pink_left,
        switch_pink_up,
        switch_pink_right,

        // 5_gravity_flow
        flow_blue_up,
        flow_yellow_up,
        flow_pink_up,
        flow_green_up,
        flow_blue_middle,
        flow_yellow_middle,
        flow_pink_middle,
        flow_green_middle,
        flow_blue_down,
        flow_yellow_down,
        flow_pink_down,
        flow_green_down,

        // 6_wall_of_death
        deathG_solo_left,
        deathG_solo_middle,
        deathG_solo_right,
        deathG_solo_left_right,
        deathG_bloc_left,
        deathG_bloc_middle,
        deathG_bloc_right,
        deathG_bloc_left_right,
        deathM_bloc_left,
        deathM_bloc_middle,
        deathM_bloc_right,
        deathM_bloc_left_right,
        deathT_bloc_left,
        deathT_bloc_middle,
        deathT_bloc_right,
        deathT_bloc_left_right
    };

    enum class LayerName
    {
        IO,
        Border,
        Wall_of_death_v,
        Wall_of_death_h,
        Wall_of_death_bloc,
        Collision_v,
        Collision_h,
        Collision_bloc,
        Gw_blue,
        Gw_rose,
        Gw_green,
        Gw_orange,
        Gw_blue_open,
        Gw_rose_open,
        Gw_green_open,
        Gw_orange_open,
        Filling,
        Decoration,
        gravity_switch,
        gravity_walls
    };

    std::string getLayerName(LayerName layerName);



} // namespace swiftness

#endif // CONSTANTS_H