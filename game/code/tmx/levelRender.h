#pragma once
#ifndef LEVEL_RENDER_H
#define LEVEL_RENDER_H

#include "levelData.h"
#include "../constants.h"
#include "../gravity.h"
#include <gf/Vector.h>
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
            void renderLayer(gf::ResourceManager& resource, LevelData &levelData, gf::RenderTarget &target, LayerName layerName, GravityDirection gravity);

            /**
             * @brief render a level
             * 
             * @param layerEntity
             * @param window
            */
            void renderLevel(gf::ResourceManager& resource, swiftness::LevelData& layerData, gf::RenderTarget &target, GravityDirection gravity);
    };
}; // namespace swiftness

#endif // LEVEL_RENDER_H