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
        hg::StaticPlateform wallRight({480.0f, 160.0f}, 320.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(0, wallUp));
        plateform.insert(std::pair<int, hg::StaticPlateform>(1, wallDown));
        plateform.insert(std::pair<int, hg::StaticPlateform>(2, wallLeft));
        plateform.insert(std::pair<int, hg::StaticPlateform>(3, wallRight));

        // Initialize platforms
        hg::StaticPlateform plateform_h_1({240.0f,  275.0f}, 80.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, hg::StaticPlateform>(4, plateform_h_1));
        

        return plateform;
    }

    std::map<int, StaticPlateform> Level::initializeLevel1()
    {

        std::map<int, hg::StaticPlateform> plateform;

        // create a list of wall
        hg::StaticPlateform wallUp({500.0f, 0.0f}, 10.0f, 1020.0f, gf::Color::Blue);
        hg::StaticPlateform wallDown({240.0f, 320.0f}, 10.0f, 500.0f, gf::Color::Blue);
        hg::StaticPlateform wallLeft({0.0f, 160.0f}, 320.0f, 10.0f, gf::Color::Blue);
        hg::StaticPlateform wallRight({480.0f, 240.0f}, 160.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(0, wallUp));
        plateform.insert(std::pair<int, hg::StaticPlateform>(1, wallDown));
        plateform.insert(std::pair<int, hg::StaticPlateform>(2, wallLeft));
        plateform.insert(std::pair<int, hg::StaticPlateform>(3, wallRight));

        // Initialize platforms
        hg::StaticPlateform plateform_h_1({240.0f,  275.0f}, 80.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, hg::StaticPlateform>(4, plateform_h_1));
        hg::StaticPlateform plateform_h_2({380.0f,  270.0f}, 90.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, hg::StaticPlateform>(5, plateform_h_2));
        hg::StaticPlateform plateform_h_3({500.0f, 160.0f}, 10.0f, 250.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(6, plateform_h_3));
        hg::StaticPlateform plateform_h_4({625.0f, 275.0f}, 240.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(7, plateform_h_4));
        hg::StaticPlateform plateform_h_5({725.0f, 275.0f}, 240.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(8, plateform_h_5));
        hg::StaticPlateform plateform_h_6({675.0f, 395.0f}, 10.0f, 110.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(9, plateform_h_6));
        hg::StaticPlateform plateform_h_7({725.0f, 77.5f}, 155.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, hg::StaticPlateform>(10, plateform_h_7));
        

        return plateform;
    }

} // namespace hg
