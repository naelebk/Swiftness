#include "tilesEnumData.h"

namespace swiftness
{
    std::string getLayerName(LayerName name)
    {
        switch (name)
        {
        case LayerName::IO:
            return "IO";
            break;
        case LayerName::Border:
            return "Border";
            break;
        case LayerName::Wall_of_death_v:
            return "Wall_of_death_v";
            break;
        case LayerName::Wall_of_death_h:
            return "Wall_of_death_h";
            break;
        case LayerName::Wall_of_death_bloc:
            return "Wall_of_death_bloc";
            break;
        case LayerName::Collision_v:
            return "Collision_v";
            break;
        case LayerName::Collision_h:
            return "Collision_h";
            break;
        case LayerName::Collision_bloc:
            return "Collision_bloc";
            break;
        case LayerName::gravity_switch:
            return "gravity_switch";
            break;
        case LayerName::Filling:
            return "Filling";
            break;
        case LayerName::Decoration:
            return "Decoration";
            break;
        default:
            return "Error";
            break;
        }
    }

    // rappel :
    /**
     * enum class PlateformType
    {
        // 1_utilities
        utilities1 = 1,
        utilities2 = 2,

        // 2_Portal
        blue_portal = 3,
        red_portal = 4,
        green_portal = 5,
        yellow_portal = 6,

        // 3_futuristic_city
        ground_solo_left = 7,
        groud_solo_middle = 8,
        ground_solo_right=9,
        ground_solo_left_right=10,

        gate_1 = 11,
        gate_2 = 12,

        ground_bloc_left=13,
        ground_bloc_middle=14,
        ground_bloc_right=15,
        ground_bloc_left_right=16,
        deco_blue_1=17,
        deco_green_1=18,

        middle_bloc_left=19,
        middle_bloc_middle=20,
        middle_bloc_right=21,
        middle_bloc_left_right=22,
        deco_blue_2=23,
        deco_green_2=24,

        top_bloc_left=25,
        top_bloc_middle=26,
        top_bloc_right=27,
        top_bloc_left_right=28,
        deco_blue_3=29,
        deco_green_3=30,

        // 4_gravity_switch
        switch_blue_down = 31,
        switch_blue_left = 32,
        switch_blue_up = 33,
        switch_blue_right = 34,

        switch_yellow_down = 35,
        switch_yellow_left = 36,
        switch_yellow_up = 37,
        switch_yellow_right = 38,

        switch_green_down = 39,
        switch_green_left = 40,
        switch_green_up = 41,
        switch_green_right = 42,

        switch_pink_down = 43,
        switch_pink_left = 44,
        switch_pink_up = 45,
        switch_pink_right = 46,

        // 5_gravity_flow
        flow_blue_up = 47,
        flow_yellow_up = 48,
        flow_pink_up = 49,
        flow_green_up = 50,

        flow_blue_middle = 51,
        flow_yellow_middle = 52,
        flow_pink_middle = 53,
        flow_green_middle = 54,

        flow_blue_down = 55,
        flow_yellow_down = 56,
        flow_pink_down = 57,
        flow_green_down = 58,

        // 6_wall_of_death
        deathG_solo_left = 59,
        deathG_solo_middle = 60,
        deathG_solo_right = 61,
        deathG_solo_left_right = 62,

        deathG_bloc_left = 63,
        deathG_bloc_middle = 64,
        deathG_bloc_right = 65,
        deathG_bloc_left_right = 66,

        deathM_bloc_left = 67,
        deathM_bloc_middle = 68,
        deathM_bloc_right = 69,
        deathM_bloc_left_right = 70,

        deathT_bloc_left = 71,
        deathT_bloc_middle = 72,
        deathT_bloc_right = 73,
        deathT_bloc_left_right = 74


    };
    */
    int getTileType(PlateformType type)
    {
        switch (type)
        {
        case PlateformType::utilities1:
            return 1;
            break;
        case PlateformType::utilities2:
            return 2;
            break;
        case PlateformType::blue_portal:
            return 3;
            break;
        case PlateformType::red_portal:

            return 4;
            break;
        case PlateformType::green_portal:
            return 5;
            break;
        case PlateformType::yellow_portal:
            return 6;
            break;
        case PlateformType::ground_solo_left:
            return 7;
            break;
        case PlateformType::groud_solo_middle:
            return 8;
            break;
        case PlateformType::ground_solo_right:
            return 9;
            break;
        case PlateformType::ground_solo_left_right:
            return 10;
            break;
        case PlateformType::gate_1:
            return 11;
            break;
        case PlateformType::gate_2:
            return 12;
            break;
        case PlateformType::ground_bloc_left:
            return 13;
            break;
        case PlateformType::ground_bloc_middle:
            return 14;
            break;
        case PlateformType::ground_bloc_right:
            return 15;
            break;
        case PlateformType::ground_bloc_left_right:
            return 16;
            break;
        case PlateformType::deco_blue_1:
            return 17;
            break;
        case PlateformType::deco_green_1:
            return 18;
            break;
        case PlateformType::middle_bloc_left:
            return 19;
            break;
        case PlateformType::middle_bloc_middle:
            return 20;
            break;
        case PlateformType::middle_bloc_right:
            return 21;
            break;
        case PlateformType::middle_bloc_left_right:
            return 22;
            break;
        case PlateformType::deco_blue_2:
            return 23;
            break;
        case PlateformType::deco_green_2:
            return 24;
            break;
        case PlateformType::top_bloc_left:
            return 25;
            break;
        case PlateformType::top_bloc_middle:
            return 26;
            break;
        case PlateformType::top_bloc_right:
            return 27;
            break;
        case PlateformType::top_bloc_left_right:
            return 28;
            break;
        case PlateformType::deco_blue_3:
            return 29;
            break;
        case PlateformType::deco_green_3:
            return 30;
            break;
        case PlateformType::switch_blue_down:
            return 31;
            break;
        case PlateformType::switch_blue_left:
            return 32;
            break;
        case PlateformType::switch_blue_up:
            return 33;
            break;
        case PlateformType::switch_blue_right:
            return 34;
            break;
        case PlateformType::switch_yellow_down:
            return 35;
            break;
        case PlateformType::switch_yellow_left:
            return 36;
            break;
        case PlateformType::switch_yellow_up:
            return 37;
            break;
        case PlateformType::switch_yellow_right:
            return 38;
            break;
        case PlateformType::switch_green_down:
            return 39;
            break;
        case PlateformType::switch_green_left:
            return 40;
            break;
        case PlateformType::switch_green_up:
            return 41;
            break;
        case PlateformType::switch_green_right:
            return 42;
            break;
        case PlateformType::switch_pink_down:
            return 43;
            break;
        case PlateformType::switch_pink_left:
            return 44;
            break;
        case PlateformType::switch_pink_up:
            return 45;
            break;
        case PlateformType::switch_pink_right:
            return 46;
            break;
        case PlateformType::flow_blue_up:
            return 47;
            break;
        case PlateformType::flow_yellow_up:
            return 48;
            break;
        case PlateformType::flow_pink_up:
            return 49;
            break;
        case PlateformType::flow_green_up:
            return 50;
            break;
        case PlateformType::flow_blue_middle:
            return 51;
            break;
        case PlateformType::flow_yellow_middle:
            return 52;
            break;
        case PlateformType::flow_pink_middle:
            return 53;
            break;
        case PlateformType::flow_green_middle:
            return 54;
            break;
        case PlateformType::flow_blue_down:
            return 55;
            break;
        case PlateformType::flow_yellow_down:
            return 56;
            break;
        case PlateformType::flow_pink_down:
            return 57;
            break;
        case PlateformType::flow_green_down:
            return 58;
            break;
        case PlateformType::deathG_solo_left:
            return 59;
            break;
        case PlateformType::deathG_solo_middle:
            return 60;
            break;
        case PlateformType::deathG_solo_right:
            return 61;
            break;
        case PlateformType::deathG_solo_left_right:
            return 62;
            break;
        case PlateformType::deathG_bloc_left:
            return 63;
            break;
        case PlateformType::deathG_bloc_middle:
            return 64;
            break;
        case PlateformType::deathG_bloc_right:
            return 65;
            break;
        case PlateformType::deathG_bloc_left_right:
            return 66;
            break;
        case PlateformType::deathM_bloc_left:
            return 67;
            break;
        case PlateformType::deathM_bloc_middle:
            return 68;
            break;
        case PlateformType::deathM_bloc_right:
            return 69;
            break;
        case PlateformType::deathM_bloc_left_right:
            return 70;
            break;
        case PlateformType::deathT_bloc_left:
            return 71;
            break;
        case PlateformType::deathT_bloc_middle:
            return 72;
            break;
        case PlateformType::deathT_bloc_right:

            return 73;
            break;
        case PlateformType::deathT_bloc_left_right:
            return 74;
            break;
        default:
            return -1;
            break;
        }
    }
} // namespace swiftness