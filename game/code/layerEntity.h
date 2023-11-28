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
namespace hg
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
        gf::TileLayer getLayerByName(std::string name);

        /**
         * @brief Get a layer by its id
         * 
         * @return gf::TileLayer the layer
        */
        gf::TileLayer getLayerByID(int id);

        /**
         * @brief Get the entrance of the level
         *
         * @return gf::Vector2i the entrance of the level
         */
        gf::Vector2i getEntrance();

        /**
         * @brief Get the exit of the level
         *
         * @return gf::Vector2i the exit of the level
         */
        gf::Vector2i getExit();

    private:
        gf::ResourceManager m_resources;
        gf::TmxLayers m_layers;
        gf::Vector2i m_entrance;
        gf::Vector2i m_exit;
    };
}; // namespace hg

#endif // LAYER_ENTITY_H