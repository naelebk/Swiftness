#ifndef LAYER_ENTITY_H
#define LAYER_ENTITY_H

#include <cstdlib>
#include <iostream>

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

/**
 * This class is used to load the layers of a tmx file
 */
namespace swiftness
{
    class LayerEntity
    {
    public:
        struct LayersMaker : public gf::TmxVisitor
        {

            virtual void visitTileLayer(const gf::TmxLayers &map, const gf::TmxTileLayer &layer) override;
        };

        LayerEntity(std::string nameFile);

        /**
         * @brief Load a tmx file
         *
         * @return gf::TmxLayers the layers of the tmx file
         */
        gf::TmxLayers loadLayers(std::string nameFile);

        /**
         * @brief Get a layer by its name
         *
         * @return gf::TileLayer the layer
         */
        gf::TmxLayer* getLayerByName(LayerName name);

        gf::Vector2i getMapSize() { return m_mapSize; }

        gf::Vector2i getTileSize() { return m_tileSize; }

    private:
        gf::ResourceManager m_resources;
        gf::TmxLayers m_layers;
        gf::Vector2i m_mapSize;
        gf::Vector2i m_tileSize;
    };
}; // namespace swiftness

#endif // LAYER_ENTITY_H