#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "squareEntity.h"
#include "staticPlateforme.h"
#include "levelEntity.h"
#include <map>
#include "levelRender.h"
#include <gf/RenderTarget.h>

namespace swiftness
{

    class Level
    {

    private:
        /**
         * @brief initialization of the square and place it at the entrance of the level
         *
         * @param nameFile
         *
         * @return Square the square
         */
        static swiftness::Square initializeSquare(std::string nameFile);

        /**
         * @brief initialization of the level
         *
         * @param nameFile
         *
         * @return std::map<int, StaticPlateform> the plateforms
         */
        static std::vector<swiftness::StaticPlateform> initializePlateforms(std::string nameFile);

    public:
        struct level
        {
            std::vector<swiftness::StaticPlateform> plateform;
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

        static std::vector<swiftness::StaticPlateform> initializeLevel03();
  
    };

} // namespace swiftness

#endif // LEVEL0_H
