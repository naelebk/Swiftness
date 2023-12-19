#ifndef LEVEL_H
#define LEVEL_H

#include "squareEntity.h"
#include "staticPlateforme.h"
#include "levelEntity.h"
#include <map>

namespace swiftness {

class Level {
public:
    static swiftness::Square initializeSquare(std::string nameFile);
    static std::map<int, StaticPlateform> initializeLevel0();
    static std::map<int, StaticPlateform> initializeLevel1();
    static std::map<int, StaticPlateform> initializeLevel2(std::string nameFile);
    static std::map<int, StaticPlateform> initializeLevel3();
};

} // namespace swiftness

#endif // LEVEL0_H
