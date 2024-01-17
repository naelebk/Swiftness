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
        case LayerName::gravity_walls:
            return "gravity_walls";
            break;
        default:
            return "Error";
            break;
        }
    }
} // namespace swiftness