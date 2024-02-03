#include "constants.h"

namespace swiftness
{
    std::initializer_list<gf::Path> PATHS = {gf::Path(RESSOURCES_PATH), gf::Paths::getBasePath(), gf::Paths::getCurrentPath()};
    gf::ResourceManager manager(PATHS);

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
        case LayerName::Gw_blue:
            return "Gw_blue";
            break;
        case LayerName::Gw_rose:
            return "Gw_rose";
            break;
        case LayerName::Gw_green:
            return "Gw_green";
            break;
        case LayerName::Gw_orange:
            return "Gw_orange";
            break;
        case LayerName::Gw_blue_open:
            return "Gw_blue_open";
            break;
        case LayerName::Gw_rose_open:
            return "Gw_rose_open";
            break;
        case LayerName::Gw_green_open:
            return "Gw_green_open";
            break;
        case LayerName::Gw_orange_open:
            return "Gw_orange_open";
            break;
        default:
            return "Error";
            break;
        }
    }
}