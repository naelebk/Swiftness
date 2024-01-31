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
        std::cout << "Vertical plateform generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes horizontales
        plateform = levelGen.generateHorizontalPlateform(index, LayerName::Collision_h,plateform);
        std::cout << "Horizontal plateform generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes bloc
        plateform = levelGen.generateBlocPlateforms(index, LayerName::Collision_bloc,plateform);
        std::cout << "Bloc plateform generated : index->" << index << std::endl;
        index = plateform.size();
        // Ajout des plateformes tueuses !!

        // Ajout des plateformes verticales
        plateform = levelGen.generateVerticalPlateform(index, LayerName::Wall_of_death_v,plateform);
        std::cout << "Vertical death generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes horizontales
        plateform = levelGen.generateHorizontalPlateform(index, LayerName::Wall_of_death_h,plateform);
        std::cout << "Horizontal death generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des plateformes bloc
        plateform = levelGen.generateBlocPlateforms(index, LayerName::Wall_of_death_bloc,plateform);
        std::cout << "Bloc death generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des gravity switch
        plateform = levelGen.generateGravitySwitchs(index,plateform);
        std::cout << "Gravity switch generated : index->" << index << std::endl;
        index = plateform.size();

        // ajout des murs invisible
        plateform = levelGen.generateBorder(index,plateform);
        std::cout << "Border generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout des gravity walls
        plateform = levelGen.generateGravityWalls(index,plateform);
        std::cout << "Gravity wall generated : index->" << index << std::endl;
        index = plateform.size();

        // Ajout de la sortie
        plateform = levelGen.generateExit(index,plateform);
        std::cout << "Exit generated : index->" << index << std::endl;

        return plateform;
    }


    LevelInitializer::level LevelInitializer::initializeLevel(std::string nameFile)
    {
        LevelInitializer::level level;

        level.plateform = initializePlateforms(nameFile);
        level.square = initializeSquare(nameFile);

        return level;
    }

    swiftness::Square LevelInitializer::initializeSquare(std::string nameFile)
    {
        LevelGenerator levelEntity(nameFile);
        return levelEntity.getSquareEntity();
    }

} // namespace swiftness
