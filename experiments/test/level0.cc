#include "plateforme.h"
#include <gf/Vector.h>
#include <gf/Color.h>
#include <map>

namespace hg {

    std::map<int, StaticPlateform> initializeLevel0(const gf::Vector2i& screenSize) {
        std::map<int, StaticPlateform> plateform;

        StaticPlateform plateformUp({static_cast<float>(screenSize.width) / 2.0f, 0.0f}, 20.0f, static_cast<float>(screenSize.width), gf::Color::Blue);
        StaticPlateform plateformDown({static_cast<float>(screenSize.width) / 2.0f, static_cast<float>(screenSize.height)}, 20.0f, static_cast<float>(screenSize.width), gf::Color::Blue);
        StaticPlateform plateformLeft({0.0f, static_cast<float>(screenSize.height) / 2.0f}, static_cast<float>(screenSize.height), 20.0f, gf::Color::Blue);
        StaticPlateform plateformRight({static_cast<float>(screenSize.width), static_cast<float>(screenSize.height) / 2.0f}, static_cast<float>(screenSize.height), 20.0f, gf::Color::Blue);

        plateform.insert(std::pair<int, StaticPlateform>(0, plateformUp));
        plateform.insert(std::pair<int, StaticPlateform>(1, plateformDown));
        plateform.insert(std::pair<int, StaticPlateform>(2, plateformLeft));
        plateform.insert(std::pair<int, StaticPlateform>(3, plateformRight));

        return plateform;
    }

} // namespace hg
