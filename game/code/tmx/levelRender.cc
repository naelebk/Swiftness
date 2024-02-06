#include "levelRender.h"

namespace swiftness
{

    void LevelRender::renderLayer(gf::ResourceManager& resource, LevelData &levelData, gf::RenderTarget &target, LayerName layerName, std::string gravity)
    {
        gf::TmxTileLayer *layer = levelData.getLayersEntity().getTileLayerByName(layerName);
        if (layerName == LayerName::Gw_blue && gravity == "down")
        {
            layer->visible = false;
        }
        else if (layerName == LayerName::Gw_rose && gravity == "up")
        {
            layer->visible = false;
        }
        else if (layerName == LayerName::Gw_green && gravity == "left")
        {
            layer->visible = false;
        }
        else if (layerName == LayerName::Gw_orange && gravity == "right")
        {
            layer->visible = false;
        }
        else {
            layer->visible = true;
        }
        if (layer != nullptr && layer->visible)
        {
            // logFile << "Layer found: " << getLayerName(layerName) << std::endl; // Écrire dans le fichier de log

            // Enregistrer la valeur actuelle de l'opacité
            // logFile << "Current opacity for " << getLayerName(layerName) << ": " << layer->opacity << std::endl;
            gf::TileLayer tileLayer = gf::makeTileLayer(levelData.getLayersEntity().getLayers(), *layer, resource);
            target.draw(tileLayer);
        }

        // logFile.close(); // Fermer le fichier de log.
    }

    void LevelRender::renderLevel(gf::ResourceManager& resource, swiftness::LevelData& levelData, gf::RenderTarget &target, std::string gravity)
    {
        for (int i = 0; i < swiftness::NB_TILE_LAYERS; i++)
        {
            swiftness::LayerName layerName = static_cast<swiftness::LayerName>(i);
            renderLayer(resource, levelData, target, layerName, gravity);
        }
    }
}
