#ifndef LEVEL_H
#define LEVEL_H

#include "squareEntity.h"
#include "staticPlateforme.h"
#include "levelEntity.h"
#include <map>

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
         * @brief initialization of the level without bloc
         *
         * @param nameFile
         *
         * @return std::map<int, StaticPlateform> the plateforms
         */
        static std::map<int, StaticPlateform> initializeLevelNoBloc(std::string nameFile);

        /**
         * @brief initialization of the level with bloc
         *
         * @param nameFile
         *
         * @return std::map<int, StaticPlateform> the plateforms
         */
        static std::map<int, StaticPlateform> initializeLevelWithBloc(std::string nameFile);

    public:
        struct level
        {
            std::map<int, StaticPlateform> plateform;
            Square square;

            level() : plateform(), square() {}
        };

        /**
         * @brief initialization of the level
         *
         * @param nameFile
         * @param bloc
         *
         * @return level all the plateforms and the square
         */
        static level initializeLevel(std::string nameFile, bool bloc);
    };

} // namespace swiftness

#endif // LEVEL0_H
