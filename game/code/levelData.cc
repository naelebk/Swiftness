#include "levelData.h"

namespace hg
{

    hg::LayerName toLayerName(std::string name)
    {
        hg::LayerName layerName;

        switch (name)
        {
        case name = "Collision":
            layerName = hg::LayerName::Collision;
            break;
        case name = "CollisionWallWalk":
            layerName = hg::LayerName::CollisionWallWalk;
            break;
        case name = "Filling":
            layerName = hg::LayerName::Filling;
            break;
        case name = "Decoration":
            layerName = hg::LayerName::Decoration;
            break;
        case name = "Power":
            layerName = hg::LayerName::Power;
            break;
        case name = "Button":
            layerName = hg::LayerName::Button;
            break;
        default:
            layerName = hg::LayerName::Collision;
            break;
        }
        
        return layerName;
    }

    gf::TmxLayers loadLayers(std::string path)
    {
        gf::TmxLayers layers;
        if (!layers.loadFromFile(path))
        {
            std::cerr << "Error: cannot load the file " << path << std::endl;
            exit(EXIT_FAILURE);
        }

        return file.getLayers();
    }

}