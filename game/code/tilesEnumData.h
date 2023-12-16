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
            exit = 26


        };

        enum class LayerName
        {
            Collision_v,
            Collision_h,
            Collision_bloc,
            CollisionWallWalk,
            Filling,
            Decoration,
            Power,
            Button,
            IO
        };


        std::string getLayerName(LayerName name) {
            switch (name)
            {
            case LayerName::Collision_v:
                return "Collision_v";
                break;
            case LayerName::Collision_h:
                return "Collision_h";
                break;
            case LayerName::Collision_bloc:
                return "Collision_bloc";
                break;
            case LayerName::CollisionWallWalk:
                return "CollisionWallWalk";
                break;
            case LayerName::Filling:
                return "Filling";
                break;
            case LayerName::Decoration:
                return "Decoration";
                break;
            case LayerName::Power:
                return "Power";
                break;
            case LayerName::Button:
                return "Button";
                break;
            case LayerName::IO:
                return "IO";
                break;
            default:
                return "Error";
                break;
            }
        }

        int getTileType(PlateformType type) {
            switch (type)
            {
            case PlateformType::ground_solo_left:
                return 0;
                break;
            case PlateformType::groud_solo_middle:
                return 1;
                break;
            case PlateformType::ground_solo_right:
                return 2;
                break;
            case PlateformType::ground_solo_left_right:
                return 3;
                break;
            case PlateformType::ground_bloc_left:
                return 6;
                break;
            case PlateformType::ground_bloc_middle:
                return 7;
                break;
            case PlateformType::ground_bloc_right:
                return 8;
                break;
            case PlateformType::ground_bloc_left_right:
                return 9;
                break;
            case PlateformType::deco_blue_1:
                return 10;
                break;
            case PlateformType::deco_green_1:
                return 11;
                break;
            case PlateformType::middle_bloc_left:
                return 12;
                break;
            case PlateformType::middle_bloc_middle:
                return 13;
                break;
            case PlateformType::middle_bloc_right:
                return 14;
                break;
            case PlateformType::middle_bloc_left_right:
                return 15;
                break;
            case PlateformType::deco_blue_2:
                return 16;
                break;
            case PlateformType::deco_green_2:
                return 17;
                break;
            case PlateformType::top_bloc_left:
                return 18;
                break;
            case PlateformType::top_bloc_middle:
                return 19;
                break;
            case PlateformType::top_bloc_right:
                return 20;
                break;
            case PlateformType::top_bloc_left_right:
                return 21;
                break;
            case PlateformType::deco_blue_3:
                return 22;
                break;
            case PlateformType::deco_green_3:
                return 23;
                break;
            case PlateformType::entrance:
                return 25;
                break;
            case PlateformType::exit:
                return 26;
                break;
            default:
                return -1;
                break;
            }
        }


}

#endif // TILES_ENUM_DATA_H