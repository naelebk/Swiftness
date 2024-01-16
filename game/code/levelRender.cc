#include "levelRender.h"


namespace swiftness{

    void LevelRender::renderLayer(LayerEntity &layerEntity, gf::RenderWindow &window, LayerName layerName)
    {
        gf::TmxTileLayer *layer = layerEntity.getTileLayerByName(layerName);
        if (layer->visible == true){
            gf::TmxRenderOrder::LeftUp;
            gf::TileLayer tileLayer = gf::makeTileLayer(layerEntity.getLayers(), *layer, layerEntity.getResources());
            window.draw(tileLayer);
        }
    }

    void LevelRender::renderLevel(std::string nameFile, gf::RenderWindow &window)
    {
        swiftness::LayerEntity layerEntity(nameFile);

        for (int i = 0 ; i < swiftness::NB_TILE_LAYERS ; i++) {
            swiftness::LayerName layerName = static_cast<swiftness::LayerName>(i);
            renderLayer(layerEntity, window, layerName);
        }
        

    }
}