#ifndef LEVEL_H
#define LEVEL_H

#include "squareEntity.h"
#include "staticPlateforme.h"
#include <map>

namespace hg {

class Level {
public:
    static std::map<int, StaticPlateform> initializeLevel0();
    static std::map<int, StaticPlateform> initializeLevel1();
};

} // namespace hg

#endif // LEVEL0_H
