#include "level.h"

namespace swiftness
{
    
    std::map<int, StaticPlateform> Level::initializeLevel0()
    {

        std::map<int, swiftness::StaticPlateform> plateform;

        // create a list of wall
        swiftness::StaticPlateform wallUp({240.0f, 0.0f}, 10.0f, 480.0f, gf::Color::Blue);
        swiftness::StaticPlateform wallDown({240.0f, 320.0f}, 10.0f, 480.0f, gf::Color::Blue);
        swiftness::StaticPlateform wallLeft({0.0f, 160.0f}, 320.0f, 10.0f, gf::Color::Blue);
        swiftness::StaticPlateform wallRight({480.0f, 160.0f}, 320.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(0, wallUp));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(1, wallDown));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(2, wallLeft));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(3, wallRight));

        // Initialize platforms
        swiftness::StaticPlateform plateform_h_1({240.0f,  275.0f}, 80.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(4, plateform_h_1));
        

        return plateform;
    }

    std::map<int, StaticPlateform> Level::initializeLevel1()
    {

        std::map<int, swiftness::StaticPlateform> plateform;

        // create a list of wall
        swiftness::StaticPlateform wallUp({500.0f, 0.0f}, 10.0f, 1020.0f, gf::Color::Blue);
        swiftness::StaticPlateform wallDown({240.0f, 320.0f}, 10.0f, 500.0f, gf::Color::Blue);
        swiftness::StaticPlateform wallLeft({0.0f, 160.0f}, 320.0f, 10.0f, gf::Color::Blue);
        swiftness::StaticPlateform wallRight({480.0f, 240.0f}, 160.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(0, wallUp));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(1, wallDown));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(2, wallLeft));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(3, wallRight));

        // Initialize platforms
        swiftness::StaticPlateform plateform_h_1({240.0f,  275.0f}, 80.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(4, plateform_h_1));
        swiftness::StaticPlateform plateform_h_2({380.0f,  270.0f}, 90.0f, 60.0f, gf::Color::Green);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(5, plateform_h_2));
        swiftness::StaticPlateform plateform_h_3({500.0f, 160.0f}, 10.0f, 250.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(6, plateform_h_3));
        swiftness::StaticPlateform plateform_h_4({625.0f, 275.0f}, 240.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(7, plateform_h_4));
        swiftness::StaticPlateform plateform_h_5({725.0f, 275.0f}, 240.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(8, plateform_h_5));
        swiftness::StaticPlateform plateform_h_6({675.0f, 395.0f}, 10.0f, 110.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(9, plateform_h_6));
        swiftness::StaticPlateform plateform_h_7({725.0f, 77.5f}, 155.0f, 10.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(10, plateform_h_7));
        

        return plateform;
    }

    std::map<int, StaticPlateform> Level::initializeLevel2(std::string nameFile)
    {

        std::map<int, swiftness::StaticPlateform> plateform;

        swiftness::LevelEntity levelEntity(nameFile);

        // ajout des plateformes verticales
        plateform = levelEntity.generateVerticalPlateform();
        std::cout << "Vertical plateform generated" << std::endl;

        // ajoute des plateformes horizontales
        std::map<int, swiftness::StaticPlateform> plateform_h = levelEntity.generateHorizontalPlateform();
        std::cout << "Horizontal plateform generated" << std::endl;

        plateform.insert(plateform_h.begin(), plateform_h.end());

        return plateform;
    }

    swiftness::Square Level::initializeSquare(std::string nameFile)
    {
        swiftness::LevelEntity levelEntity(nameFile);
        swiftness::Square square = levelEntity.getSquareEntity();
        return square;
    }
        
        
    

} // namespace swiftness
