#pragma once
#ifndef LEVEL_RENDER_H
#define LEVEL_RENDER_H
#include "layerEntity.h"
#include "constants.h"
#include <gf/Vector.h>
#include "tilesEnumData.h"
#include "gf/Drawable.h"
#include <gf/Text.h>
#include "gf/Tmx.h"

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
            void renderLayer(LayerEntity &layerEntity, gf::RenderTarget &target, LayerName layerName, std::string gravity);

            /**
             * @brief render the layer tutorial
             * 
             * @param layerEntity
             * @param window
             */
            void renderTutorial(LayerEntity &layerEntity, gf::RenderTarget &target);

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