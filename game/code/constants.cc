#include "constants.h"

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
        case LayerName::Wall_of_death:
            return "Wall_of_death";
            break;
        case LayerName::Collision:
            return "Collision";
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