#include "level.h"

namespace swiftness
{

    std::map<int, StaticPlateform> Level::initializePlateforms(std::string nameFile)
    {
        std::map<int, StaticPlateform> plateform;

        LevelEntity levelEntity(nameFile);

        int index = 0;

        // Ajout des plateformes verticales
        plateform = levelEntity.generateVerticalPlateform(index, LayerName::Collision_v);
        std::cout << "Vertical plateform generated" << std::endl;
        index += plateform.size();

        // Ajout des plateformes horizontales
        std::map<int, StaticPlateform> plateform_h = levelEntity.generateHorizontalPlateform(index, LayerName::Collision_h);
        std::cout << "Horizontal plateform generated" << std::endl;
        index += plateform_h.size();

        // Ajout des plateformes bloc
        std::map<int, StaticPlateform> plateform_bloc = levelEntity.generateBlocPlateforms(index, LayerName::Collision_bloc);
        std::cout << "Bloc plateform generated" << std::endl;
        index += plateform_bloc.size();
        // Ajout des plateformes tueuses !!

        // Ajout des plateformes verticales
        std::map<int, StaticPlateform> Death_v = levelEntity.generateVerticalPlateform(index, LayerName::Wall_of_death_v);
        std::cout << "Vertical death generated" << std::endl;
        index += Death_v.size();

        // Ajout des plateformes horizontales
        std::map<int, StaticPlateform> Death_h = levelEntity.generateHorizontalPlateform(index, LayerName::Wall_of_death_h);
        std::cout << "Horizontal death generated" << std::endl;
        index += Death_h.size();

        // Ajout des plateformes bloc
        std::map<int, StaticPlateform> Death_bloc = levelEntity.generateBlocPlateforms(index, LayerName::Wall_of_death_bloc);
        std::cout << "Bloc death generated" << std::endl;
        index += Death_bloc.size();

        // Ajout des gravity switch
        std::map<int, StaticPlateform> gravitySwitch = levelEntity.generateGravitySwitchs(index);
        std::cout << "Gravity switch generated" << std::endl;
        index += gravitySwitch.size();

        // ajout des murs invisible
        std::map<int, StaticPlateform> border = levelEntity.generateBorder(index);
        index += border.size();

        // Ajout de la sortie
        std::cout << "before generate exit" << std::endl;
        std::map<int, StaticPlateform> exit = levelEntity.generateExit(index);
        std::cout << "plateforme generated : id -> " << exit.begin()->first << std::endl;

        plateform.insert(plateform_h.begin(), plateform_h.end());
        plateform.insert(plateform_bloc.begin(), plateform_bloc.end());
        plateform.insert(Death_v.begin(), Death_v.end());
        plateform.insert(Death_h.begin(), Death_h.end());
        plateform.insert(Death_bloc.begin(), Death_bloc.end());
        plateform.insert(gravitySwitch.begin(), gravitySwitch.end());
        plateform.insert(border.begin(), border.end());
        plateform.insert(exit.begin(), exit.end());

        return plateform;
    }

    std::map<int, StaticPlateform> Level::initializeLevel03()
    {

        std::map<int, swiftness::StaticPlateform> plateform;

        // create a list of wall
        swiftness::StaticPlateform wallUp({500.0f, 5.0f}, 10.0f, 1000.0f, gf::Color::Yellow);
        swiftness::StaticPlateform wallDown({500.0f, 995.0f}, 10.0f, 1000.0f, gf::Color::Yellow);
        swiftness::StaticPlateform wallLeft({5.0f, 500.0f}, 1000.0f, 10.0f, gf::Color::Yellow);
        swiftness::StaticPlateform wallRight({995.0f, 500.0f}, 1000.0f, 10.0f, gf::Color::Yellow);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(0, wallUp));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(1, wallDown));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(2, wallLeft));
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(3, wallRight));

        // Initialize platforms
        swiftness::StaticPlateform plateform_g_1({100.0f,  275.0f}, 80.0f, 60.0f, gf::Color::Violet);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(4, plateform_g_1));
        swiftness::StaticPlateform plateform_g_2({200.0f,  175.0f}, 20.0f, 40.0f, gf::Color::Violet);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(5, plateform_g_2));
        swiftness::StaticPlateform plateform_up_1({200.0f,  160.0f}, 10.0f, 10.0f, gf::Color::Cyan);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(6, plateform_up_1));
        swiftness::StaticPlateform plateform_b_1({500.0f,  50.0f}, 10.0f, 620.0f, gf::Color::Blue);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(7, plateform_b_1));
        swiftness::StaticPlateform plateform_down_1({805.0f,  60.0f}, 10.0f, 10.0f, gf::Color::Rose);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(8, plateform_down_1));
        swiftness::StaticPlateform plateform_g_3({805.0f,  950.0f}, 20.0f, 40.0f, gf::Color::Violet);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(9, plateform_g_3));
        swiftness::StaticPlateform plateform_g_4({840.0f,  950.0f}, 20.0f, 40.0f, gf::Color::Violet);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(10, plateform_g_4));
        for(int i=0;i<7;i++){
            swiftness::StaticPlateform plateform_wj_1({855.0f,  900.0f-120.0f*i}, 50.0f, 10.0f, gf::Color::Blue);
            plateform.insert(std::pair<int, swiftness::StaticPlateform>(11+2*i, plateform_wj_1));
            swiftness::StaticPlateform plateform_wj_2({950.0f,  840.0f-120.0f*i}, 50.0f, 10.0f, gf::Color::Blue);
            plateform.insert(std::pair<int, swiftness::StaticPlateform>(12+2*i, plateform_wj_2));
        }
        swiftness::StaticPlateform plateform_g_5({855.0f,  120.0f}, 20.0f, 40.0f, gf::Color::Violet);
        plateform.insert(std::pair<int, swiftness::StaticPlateform>(25, plateform_g_5));
        for(int i=0;i<5;i++){
            swiftness::StaticPlateform plateform_die_1({950.0f,  780.0f-120.0f*i}, 50.0f, 10.0f, gf::Color::Yellow);
            plateform.insert(std::pair<int, swiftness::StaticPlateform>(26+2*i, plateform_die_1));
            swiftness::StaticPlateform plateform_die_2({855.0f,  720.0f-120.0f*i}, 50.0f, 10.0f, gf::Color::Yellow);
            plateform.insert(std::pair<int, swiftness::StaticPlateform>(27+2*i, plateform_die_2));
        }
        return plateform;
    }

    Level::level Level::initializeLevel(std::string nameFile)
    {
        Level::level level;

        level.plateform = initializePlateforms(nameFile);
        level.square = initializeSquare(nameFile);

        return level;
    }

    swiftness::Square Level::initializeSquare(std::string nameFile)
    {
        LevelEntity levelEntity(nameFile);
        return levelEntity.getSquareEntity();
    }

} // namespace swiftness
