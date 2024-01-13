#ifndef TILES_ENUM_DATA_H
#define TILES_ENUM_DATA_H

#include <cstdlib>
#include <stdio.h>
#include <string>

namespace swiftness {

    enum class PlateformType
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
            gravity_switch,
            Filling,
            Decoration
        };

        std::string getLayerName(LayerName layerName);

        int getTileType(PlateformType type);


        


}

#endif // TILES_ENUM_DATA_H