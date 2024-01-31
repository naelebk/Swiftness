#pragma once
#ifndef LAYER_DATA_H
#define LAYER_DATA_H

#include <cstdlib>
#include <iostream>
#include <memory>

#include "../constants.h"

#include <gf/Event.h>
#include <gf/Log.h>
#include <gf/Math.h>
#include <gf/Paths.h>
#include <gf/RenderWindow.h>
#include <gf/ResourceManager.h>
#include <gf/Texture.h>
#include <gf/TileLayer.h>
#include <gf/Tmx.h>
#include <gf/TmxOps.h>
#include <gf/VectorOps.h>
#include <gf/Views.h>
#include <gf/ViewContainer.h>
#include <gf/Window.h>
#include <gf/Matrix.h>

namespace swiftness
{
    class LayerData
    {
    public:

        LayerData(std::string nameFile);

        gf::TmxLayers loadLayers(std::string nameFile);

        gf::TmxTileLayer* getTileLayerByName(LayerName name);

        gf::TmxObjectLayer* getObjectLayerByName(LayerName name);

        gf::Vector2f getMapSize() { return m_mapSize; };

        gf::Vector2f getTileSize() { return m_tileSize; };

        gf::TmxLayers& getLayers() { return m_layers; };

        std::vector<gf::TmxCell> getCellsOfaLayer(LayerName name) { auto t = getTileLayerByName(name); return t ? t->cells : std::vector<gf::TmxCell>(); };

        std::vector<std::unique_ptr<gf::TmxObject>> getObjectsOfaLayer(LayerName name) { auto t = getObjectLayerByName(name); return t ? std::move(t->objects) : std::vector<std::unique_ptr<gf::TmxObject>>(); };

    private:
        gf::TmxLayers m_layers;
        gf::Vector2f m_mapSize;
        gf::Vector2f m_tileSize;
    };
}; // namespace swiftness

#endif // LAYER_DATA_H