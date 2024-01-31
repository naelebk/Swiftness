#pragma once
#ifndef LEVEL_RENDER_H
#define LEVEL_RENDER_H

#include "layerData.h"
#include "../constants.h"
#include <gf/Vector.h>
#include "../tilesEnumData.h"
#include <gf/Drawable.h>
#include <gf/Text.h>
#include <gf/Tmx.h>
#include <fstream>

namespace swiftness
{
    class LevelRender
    {
        public:

            LevelRender() = default;
            
            /**
             * @brief render a tile layer
             * 
             * @param layerEntity
             * @param window
             * @param layerName
             */
            void renderLayer(LayerData &layerEntity, gf::RenderTarget &target, LayerName layerName, std::string gravity);

            /**
             * @brief render a level
             * 
             * @param layerEntity
             * @param window
            */
            void renderLevel(std::string nameFile, gf::RenderTarget &target, std::string gravity);
    };
}; // namespace swiftness

#endif // LEVEL_RENDER_H