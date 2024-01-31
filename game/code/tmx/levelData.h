#pragma once
#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include "layerData.h"
#include "../tilesEnumData.h"

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
        LayerData& getLayersEntity() { return m_layerEntity; };

        /**
         * @brief Get the entrance of the level
         *
         * @return gf::Vector2i the entrance of the level
         */
        gf::Vector2f getEntrance() { return m_entrance; };

        /**
         * @brief Get the exit of the level
         *
         * @return gf::Vector2i the exit of the level
         */
        gf::Vector2f getExit() { return m_exit; };

        /**
         * @brief
        */
       gf::Vector2f getMapCenter() { return gf::Vector2f(m_mapCenter); };

        /**
         * @brief Get the name of the tmx file
         *
         * @return std::string the name of the tmx file
         */
        std::string getName() { return m_name; };

        /**
         * @brief get the size of the map
         * 
         * @return gf::Vector2i the size of the map
        */
        gf::Vector2f getMapSize() { return m_layerEntity.getMapSize(); }

        /**
         * @brief get the size of the tiles
         * 
         * @return gf::Vector2i the size of the tiles
        */
        gf::Vector2f getTileSize() { return m_layerEntity.getTileSize(); }

    private:
        std::string m_name;        // name of the tmx file and the level
        std::string m_name_background; // path of the background
        LayerData m_layerEntity; // entity of the layer
        gf::Vector2f m_mapCenter;  // center of the map
        gf::Vector2f m_entrance;   // entrance of the level
        gf::Vector2f m_exit;       // exit of the level
    };
}

#endif // LEVEL_DATA_H