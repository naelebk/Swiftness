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
        std::cout << "Vertical plateform generated : index->" << index << std::endl;
        index += plateform.size();

        // Ajout des plateformes horizontales
        std::map<int, StaticPlateform> plateform_h = levelEntity.generateHorizontalPlateform(index, LayerName::Collision_h);
        std::cout << "Horizontal plateform generated : index->" << index << std::endl;
        index += plateform_h.size();

        // Ajout des plateformes bloc
        std::map<int, StaticPlateform> plateform_bloc = levelEntity.generateBlocPlateforms(index, LayerName::Collision_bloc);
        std::cout << "Bloc plateform generated : index->" << index << std::endl;
        index += plateform_bloc.size();
        // Ajout des plateformes tueuses !!

        // Ajout des plateformes verticales
        std::map<int, StaticPlateform> Death_v = levelEntity.generateVerticalPlateform(index, LayerName::Wall_of_death_v);
        std::cout << "Vertical death generated : index->" << index << std::endl;
        index += Death_v.size();

        // Ajout des plateformes horizontales
        std::map<int, StaticPlateform> Death_h = levelEntity.generateHorizontalPlateform(index, LayerName::Wall_of_death_h);
        std::cout << "Horizontal death generated : index->" << index << std::endl;
        index += Death_h.size();

        // Ajout des plateformes bloc
        std::map<int, StaticPlateform> Death_bloc = levelEntity.generateBlocPlateforms(index, LayerName::Wall_of_death_bloc);
        std::cout << "Bloc death generated : index->" << index << std::endl;
        index += Death_bloc.size();

        // Ajout des gravity switch
        std::map<int, StaticPlateform> gravitySwitch = levelEntity.generateGravitySwitchs(index);
        std::cout << "Gravity switch generated : index->" << index << std::endl;
        index += gravitySwitch.size();

        // ajout des murs invisible
        std::map<int, StaticPlateform> border = levelEntity.generateBorder(index);
        std::cout << "Border generated : index->" << index << std::endl;
        index += border.size();

        // Ajout des gravity walls
        std::map<int, StaticPlateform> gravityWall = levelEntity.generateGravityWalls(index);
        std::cout << "Gravity wall generated : index->" << index << std::endl;
        index += gravityWall.size();

        // Ajout de la sortie
        std::map<int, StaticPlateform> exit = levelEntity.generateExit(index);
        std::cout << "Exit generated : index->" << index << std::endl;

        plateform.insert(plateform_h.begin(), plateform_h.end());
        plateform.insert(plateform_bloc.begin(), plateform_bloc.end());
        plateform.insert(Death_v.begin(), Death_v.end());
        plateform.insert(Death_h.begin(), Death_h.end());
        plateform.insert(Death_bloc.begin(), Death_bloc.end());
        plateform.insert(gravitySwitch.begin(), gravitySwitch.end());
        plateform.insert(border.begin(), border.end());
        plateform.insert(gravityWall.begin(), gravityWall.end());
        plateform.insert(exit.begin(), exit.end());

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
