#include "level.h"

namespace swiftness
{

    std::map<int, StaticPlateform> Level::initializeLevelNoBloc(std::string nameFile)
    {
        std::map<int, StaticPlateform> plateform;

        LevelEntity levelEntity(nameFile);

        // Ajout des plateformes verticales
        plateform = levelEntity.generateVerticalPlateform(0);
        std::cout << "Vertical plateform generated" << std::endl;

        // Ajout des plateformes horizontales
        std::map<int, StaticPlateform> plateform_h = levelEntity.generateHorizontalPlateform(plateform.size());
        std::cout << "Horizontal plateform generated" << std::endl;

        // ajout des murs invisible
        std::map<int, StaticPlateform> plateform_invisible = levelEntity.generateInvisiblePlateforms(plateform.size() + plateform_h.size());
        std::cout << "Invisible plateform generated" << std::endl;

        plateform.insert(plateform_h.begin(), plateform_h.end());
        plateform.insert(plateform_invisible.begin(), plateform_invisible.end());

        return plateform;
    }

    std::map<int, StaticPlateform> Level::initializeLevelWithBloc(std::string nameFile)
    {
        std::map<int, StaticPlateform> plateform;

        LevelEntity levelEntity(nameFile);

        // Ajout des plateformes verticales
        plateform = levelEntity.generateVerticalPlateform(0);
        std::cout << "Vertical plateform generated" << std::endl;

        // Ajout des plateformes horizontales
        std::map<int, StaticPlateform> plateform_h = levelEntity.generateHorizontalPlateform(plateform.size());
        std::cout << "Horizontal plateform generated" << std::endl;

        // Ajout des plateformes bloc
        std::map<int, StaticPlateform> plateform_bloc = levelEntity.generateBlocPlateforms(plateform.size() + plateform_h.size());
        std::cout << "Bloc plateform generated" << std::endl;

        // ajout des murs invisible
        std::map<int, StaticPlateform> plateform_invisible = levelEntity.generateInvisiblePlateforms(plateform.size() + plateform_h.size() + plateform_bloc.size());

        plateform.insert(plateform_h.begin(), plateform_h.end());
        plateform.insert(plateform_bloc.begin(), plateform_bloc.end());
        plateform.insert(plateform_invisible.begin(), plateform_invisible.end());

        return plateform;
    }

    swiftness::Square Level::initializeSquare(std::string nameFile)
    {
        LevelEntity levelEntity(nameFile);
        return levelEntity.getSquareEntity();
    }

    Level::level Level::initializeLevel(std::string nameFile, bool bloc)
    {
        level newLevel;
        newLevel.square = initializeSquare(nameFile);
        if (bloc)
        {
            newLevel.plateform = initializeLevelWithBloc(nameFile);
        }
        else
        {
            newLevel.plateform = initializeLevelNoBloc(nameFile);
        }
        return newLevel;
    }

} // namespace swiftness
