#include "levelRender.h"

namespace swiftness {

    void LevelRender::renderLayer(LayerEntity &layerEntity, gf::RenderWindow &window, LayerName layerName, std::string gravity) {
        gf::TmxTileLayer *layer = layerEntity.getTileLayerByName(layerName);
        if (layer != nullptr && layer->visible) {
            if ((layerName == LayerName::Gw_blue && gravity == "down") ||
                (layerName == LayerName::Gw_rose && gravity == "up") ||
                (layerName == LayerName::Gw_green && gravity == "left") ||
                (layerName == LayerName::Gw_orange && gravity == "right")) {
                    layer->opacity = 0;
            }

            // Assurez-vous que cette méthode reflète les changements de l'opacité
            gf::TileLayer tileLayer = gf::makeTileLayer(layerEntity.getLayers(), *layer, layerEntity.getResources());
            window.draw(tileLayer);
        }
    }

    void LevelRender::renderLevel(std::string nameFile, gf::RenderWindow &window, std::string gravity) {
        swiftness::LayerEntity layerEntity(nameFile);

        for (int i = 0; i < swiftness::NB_TILE_LAYERS; i++) {
            swiftness::LayerName layerName = static_cast<swiftness::LayerName>(i);
            renderLayer(layerEntity, window, layerName, gravity);
        }
    }
}
