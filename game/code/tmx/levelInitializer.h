#pragma once
#ifndef LEVEL_INTIALIZER_H
#define LEVEL_INTIALIZER_H

#include "../entity/squareEntity.h"
#include "../entity/plateformEntity.h"
#include "levelGenerator.h"
#include <map>
#include "levelRender.h"
#include <gf/RenderTarget.h>

namespace swiftness
{

    class LevelInitializer
    {

    private:
        /**
         * @brief initialization of the square and place it at the entrance of the level
         *
         * @param nameFile
         *
         * @return Square the square
         */
        static swiftness::Square& initializeSquare(std::string nameFile);

        /**
         * @brief initialization of the level
         *
         * @param nameFile
         *
         * @return std::map<int, StaticPlateform> the plateforms
         */
        static std::vector<swiftness::PlateformEntity> initializePlateforms(std::string nameFile);

        LevelGenerator levelGen;

    public:
        struct level
        {
            std::vector<swiftness::PlateformEntity> plateform;
            Square square;

            level() : plateform(), square() {}
        };

        /**
         * @brief initialization of the level
         *
         * @param nameFile
         *
         * @return level the level
         */
        static level initializeLevel(std::string nameFile);

        // static std::vector<swiftness::PlateformEntity> initializeLevel03();
  
    };

} // namespace swiftness

#endif // LEVEL_INITIALIZER_H
