#include "level.h"

namespace hg
{

    std::map<int, StaticPlateform> Level::initializeLevel0()
    {

        std::map<int, hg::StaticPlateform> plateform;

        // create a list of wall
        hg::StaticPlateform wallUp({240.0f, 0.0f}, 10.0f, 480.0f, gf::Color::Blue);
        hg::StaticPlateform wallDown({240.0f, 320.0f}, 10.0f, 480.0f, gf::Color::Blue);
        hg::StaticPlateform wallLeft({0.0f, 160.0f}, 320.0f, 10.0f, gf::Color::Blue);
        hg::StaticPlateform wallRight({480.0f, 150.0f}, 300.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(0, wallUp));
        plateform.insert(std::pair<int, hg::StaticPlateform>(1, wallDown));
        plateform.insert(std::pair<int, hg::StaticPlateform>(2, wallLeft));
        plateform.insert(std::pair<int, hg::StaticPlateform>(3, wallRight));

        // Initialize platforms
        hg::StaticPlateform plateform_h_1({240.0f,  265.0f}, 100.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, hg::StaticPlateform>(4, plateform_h_1));
        

        return plateform;
    }

} // namespace hg
