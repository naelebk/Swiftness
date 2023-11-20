#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

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

namespace hg
{
    enum class PlateformType
    {
        Plateform_solo = 4,

        Plateform_neutral = 7,
        Plateform_left = 8,
        Plateform_right = 6,

        Plateform_solo_left = 0,
        Plateform_solo_neutral = 1,
        Plateform_solo_right = 2,

        Wall_ceiling_left = 18,
        Wall_ceiling_neutral = 19,
        Wall_ceiling_right = 20,

        Wall_left = 12,
        Wall_neutral = 13,
        Wall_right = 14,

        Plateform_levitate_up = 9,
        Plateform_levitate_middle = 21,
        Plateform_levitate_down = 15,

        Deco_blue_up = 10,
        Deco_blue_middle = 16,
        Deco_blue_down = 22,

        Deco_green_up = 11,
        Deco_green_middle = 17,
        Deco_green_down = 23
    };

    enum class LayerName
    {
        Collision,
        CollisionWallWalk,
        Filling,
        Decoration,
        Power,
        Button
    };

    /**
     * @brief Load a tmx file
     *
     * @param path the path of the tmx file
     * @return gf::TmxLayers the layers of the tmx file
     */
    gf::TmxLayers loadLayers(std::string path);

    /**
     * @brief Convert a string to a LayerName
     * 
     * @param name the string to convert
     * @return hg::LayerName the LayerName
     */
    hg::LayerName toLayerName(std::string name);

} // namespace hg

#endif // LEVEL_DATA_H