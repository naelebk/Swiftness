#include "tilesEnumData.h"

namespace swiftness
{
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
            case LayerName::IO:
                return "IO";
                break;
            case LayerName::Border:
                return "Border";
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