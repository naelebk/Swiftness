#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include "layerEntity.h"
#include "tilesEnumData.h"

#include <cstdlib>
#include <iostream>
#include <string>

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
 * this class is used to organise information about a level
 */

namespace swiftness
{

    class LevelData
    {
    public:
        LevelData(std::string nameFile);

        /**
         * @brief Load a tmx file
         *
         * @return gf::TmxLayers the layers of the tmx file
         */
        LayerEntity& getLayersEntity() { return m_layerEntity; };

        /**
         * @brief Get the entrance of the level
         *
         * @return gf::Vector2i the entrance of the level
         */
        gf::Vector2i getEntrance() { return m_entrance; };

        /**
         * @brief Get the exit of the level
         *
         * @return gf::Vector2i the exit of the level
         */
        gf::Vector2i getExit() { return m_exit; };

        /**
         * @brief Get the name of the tmx file
         *
         * @return std::string the name of the tmx file
         */
        std::string getName() { return m_name; };

    private:
        std::string m_name;        // name of the tmx file and the level
        LayerEntity m_layerEntity; // entity of the layer
        gf::Vector2i m_entrance;   // entrance of the level
        gf::Vector2i m_exit;       // exit of the level
    };
}

#endif // LEVEL_DATA_H