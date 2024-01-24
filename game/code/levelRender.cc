#include "levelRender.h"
#include <fstream>

namespace swiftness
{

    void LevelRender::renderLayer(LayerEntity &layerEntity, gf::RenderTarget &target, LayerName layerName, std::string gravity)
    {
        gf::TmxTileLayer *layer = layerEntity.getTileLayerByName(layerName);
        if (layerName == LayerName::Gw_blue && gravity == "down")
        {
            layer->visible = false;
        }
        if (layerName == LayerName::Gw_rose && gravity == "up")
        {
            layer->visible = false;
        }
        if (layerName == LayerName::Gw_green && gravity == "left")
        {
            layer->visible = false;
        }
        if (layerName == LayerName::Gw_orange && gravity == "right")
        {
            layer->visible = false;
        }
        if (layer != nullptr && layer->visible)
        {
            // logFile << "Layer found: " << getLayerName(layerName) << std::endl; // Écrire dans le fichier de log

            // Enregistrer la valeur actuelle de l'opacité
            // logFile << "Current opacity for " << getLayerName(layerName) << ": " << layer->opacity << std::endl;

            gf::TileLayer tileLayer = gf::makeTileLayer(layerEntity.getLayers(), *layer, layerEntity.getResources());
            target.draw(tileLayer);
        }

        // logFile.close(); // Fermer le fichier de log.
    }

    void LevelRender::renderLevel(std::string nameFile, gf::RenderTarget &target, std::string gravity)
    {
        swiftness::LayerEntity layerEntity(nameFile);

        for (int i = 0; i < swiftness::NB_TILE_LAYERS; i++)
        {
            swiftness::LayerName layerName = static_cast<swiftness::LayerName>(i);
            renderLayer(layerEntity, target, layerName, gravity);
        }
    }
}
