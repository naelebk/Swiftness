#ifndef TILES_ENUM_DATA_H
#define TILES_ENUM_DATA_H

namespace hg {

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
            Collision_v = 20,
            Collision_h = 1,
            Collision_bloc = 25,
            CollisionWallWalk = 17,
            Filling = 16,
            Decoration = 3,
            Power = 18,
            Button = 19,
            IO = 26
        };


}

#endif // TILES_ENUM_DATA_H