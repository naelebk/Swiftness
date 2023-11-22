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


        private:
            gf::TmxLayers m_layers; // map of layers
    };
}

#endif // LAYER_ENTITY_H