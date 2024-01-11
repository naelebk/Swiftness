#ifndef TILES_ENUM_DATA_H
#define TILES_ENUM_DATA_H

#include <cstdlib>
#include <stdio.h>
#include <string>

namespace swiftness {

    enum class PlateformType
        {
            ground_solo_left = 0,
            groud_solo_middle = 1,
            ground_solo_right = 2,
            ground_solo_left_right = 3,

            ground_bloc_left = 6,
            ground_bloc_middle = 7,
            ground_bloc_right = 8,
            ground_bloc_left_right = 9,
            deco_blue_1 = 10,
            deco_green_1 = 11, 

            middle_bloc_left = 12,
            middle_bloc_middle = 13,
            middle_bloc_right = 14,
            middle_bloc_left_right = 15,
            deco_blue_2 = 16,
            deco_green_2 = 17,

            top_bloc_left = 18,
            top_bloc_middle = 19,
            top_bloc_right = 20,
            top_bloc_left_right = 21,
            deco_blue_3 = 22,
            deco_green_3 = 23,

            entrance = 25,
            exit = 26,
            
            deathG_solo_left = 27,
            deathG_solo_middle = 28,
            deathG_solo_right = 29,
            deathG_solo_left_right = 30,

            deathG_bloc_left = 31,
            deathG_bloc_middle = 32,
            deathG_bloc_right = 33,
            deathG_bloc_left_right = 34,

            deathM_bloc_left = 35,
            deathM_bloc_middle = 36,
            deathM_bloc_right = 37,
            deathM_bloc_left_right = 38,

            deathT_bloc_left = 39,
            deathT_bloc_middle = 40,
            deathT_bloc_right = 41,
            deathT_bloc_left_right = 42


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