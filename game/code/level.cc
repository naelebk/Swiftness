#include "level.h"

namespace swiftness
{

    std::vector<swiftness::StaticPlateform> Level::initializePlateforms(std::string nameFile)
    {
        std::vector<swiftness::StaticPlateform> plateform;

        LevelEntity levelEntity(nameFile);

        int index = 0;

        // Ajout des plateformes verticales
        plateform = levelEntity.generateVerticalPlateform(index, LayerName::Collision_v,plateform);
        std::cout << "Vertical plateform generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes horizontales
        plateform = levelEntity.generateHorizontalPlateform(index, LayerName::Collision_h,plateform);
        std::cout << "Horizontal plateform generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes bloc
        plateform = levelEntity.generateBlocPlateforms(index, LayerName::Collision_bloc,plateform);
        std::cout << "Bloc plateform generated : index->" << index << std::endl;
        index = plateform.size();
        // Ajout des plateformes tueuses !!

        // Ajout des plateformes verticales
        plateform = levelEntity.generateVerticalPlateform(index, LayerName::Wall_of_death_v,plateform);
        std::cout << "Vertical death generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes horizontales
        plateform = levelEntity.generateHorizontalPlateform(index, LayerName::Wall_of_death_h,plateform);
        std::cout << "Horizontal death generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes bloc
        plateform = levelEntity.generateBlocPlateforms(index, LayerName::Wall_of_death_bloc,plateform);
        std::cout << "Bloc death generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des gravity switch
        plateform = levelEntity.generateGravitySwitchs(index,plateform);
        std::cout << "Gravity switch generated : index->" << index << std::endl;
        index = plateform.size();

        // ajout des murs invisible
        plateform = levelEntity.generateBorder(index,plateform);
        std::cout << "Border generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des gravity walls
        plateform = levelEntity.generateGravityWalls(index,plateform);
        std::cout << "Gravity wall generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout de la sortie
        plateform = levelEntity.generateExit(index,plateform);
        std::cout << "Exit generated : index->" << index << std::endl;

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
