#include "levelInitializer.h"

namespace swiftness
{

    std::vector<swiftness::PlateformEntity> LevelInitializer::initializePlateforms(std::string nameFile)
    {
        std::vector<swiftness::PlateformEntity> plateform;

        LevelGenerator levelGen(nameFile);

        int index = 0;

        // Ajout des plateformes verticales
        plateform = levelGen.generateVerticalPlateform(index, LayerName::Collision_v,plateform);
        std::cout << swiftness::BOLD << "Vertical plateform\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes horizontales
        plateform = levelGen.generateHorizontalPlateform(index, LayerName::Collision_h,plateform);
        std::cout << "Horizontal plateform\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes bloc
        plateform = levelGen.generateBlocPlateforms(index, LayerName::Collision_bloc,plateform);
        std::cout << "Bloc plateform\t\t[GENERATED]" << std::endl;
        
        // Ajout des plateformes tueuses !!

        // Ajout des plateformes verticales
        plateform = levelGen.generateVerticalPlateform(index, LayerName::Wall_of_death_v,plateform);
        std::cout << "Vertical death\t\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes horizontales
        plateform = levelGen.generateHorizontalPlateform(index, LayerName::Wall_of_death_h,plateform);
        std::cout << "Horizontal death\t[GENERATED]" << std::endl;
        

        // Ajout des plateformes bloc
        plateform = levelGen.generateBlocPlateforms(index, LayerName::Wall_of_death_bloc,plateform);
        std::cout << "Bloc death\t\t[GENERATED]" << std::endl;
        

        // Ajout des gravity switch
        plateform = levelGen.generateGravitySwitchs(index,plateform);
        std::cout << "Gravity switch\t\t[GENERATED]" << std::endl;
        

        // ajout des murs invisible
        plateform = levelGen.generateBorder(index,plateform);
        std::cout << "Border\t\t\t[GENERATED]" << std::endl;

        // Ajout des gravity walls
        plateform = levelGen.generateGravityWalls(index,plateform);
        std::cout << "Gravity wall\t\t[GENERATED]" << std::endl;

        // Ajout de la sortie
        plateform = levelGen.generateExit(index,plateform);
        std::cout << "Exit\t\t\t[GENERATED]" << swiftness::NC << std::endl;

        return plateform;
    }


    LevelInitializer::level LevelInitializer::initializeLevel(std::string nameFile)
    {
        LevelInitializer::level level;

        level.plateform = initializePlateforms(nameFile);
        level.square.copyFrom(initializeSquare(nameFile));

        return level;
    }

    swiftness::Square& LevelInitializer::initializeSquare(std::string nameFile)
    {
        LevelGenerator levelGen(nameFile);
        return levelGen.getSquareEntity();
    }

} // namespace swiftness
