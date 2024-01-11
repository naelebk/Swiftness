#include "helloNewPadawan.h"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define PURPLE "\x1b[35m"
#define CYAN    "\x1b[36m"
#define NC   "\x1b[0m"

namespace swiftness {
    
    // Déclaration en première instance du constructeur et du destructeur
    Hello::Hello() {}
    Hello::~Hello() {}
    
    int Hello::askLevel() {
        std::cout << YELLOW << "Quel niveau souhaitez vous effectuer (-1 pour quitter le script) ?\n\t=> " << NC;
        int n;
        std::cin >> n;
        return n;
    }

    void Hello::loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square) {
        int level = askLevel();
        if ((level < MIN_LEVEL || level > MAX_LEVEL) && level != -1) {
            std::cout << RED << "Erreur : le choix du niveau est incorrect" << NC << std::endl;
            std::cout << YELLOW << "Le niveau doit être compris entre " << MIN_LEVEL << " et " << MAX_LEVEL << NC << '\n';
            return;
        } else if (level == -1) {
            std::cout << PURPLE << "Aurevoir....." << NC << '\n';
            exit(0);
        }
        if (level == 0) {
            std::cout << GREEN << "File load : level00.tmx - Julien" << NC << std::endl;
            swiftness::Level::level level00 = Level::initializeLevel("level00.tmx");
            square = level00.square;
            plateform = level00.plateform;
        } else if (level == 1) {
            std::cout << GREEN << "File load : level01.tmx - Julien" << NC << std::endl;
            swiftness::Level::level level01 = Level::initializeLevel("level01.tmx");
            square = level01.square;
            plateform = level01.plateform;
        } else if (level == 2) {
            std::cout << GREEN << "File load : level02.tmx - Julien" << NC << std::endl;
            swiftness::Level::level level02 = Level::initializeLevel("level02.tmx");
            square = level02.square;
            plateform = level02.plateform;
        } else if (level == 3) {
            std::cout << GREEN << "File load : level03.tmx - Julien" << NC << std::endl;
            swiftness::Level::level level03 = Level::initializeLevel("level03.tmx");
            square = level03.square;
            plateform = level03.plateform;
        } else if (level == 4) {
            std::cout << GREEN << "Level chosen : level04 - Théo" << NC << std::endl;
            square = swiftness::Square({100, 100}, 20.0f, gf::Color::Red, GRAVITY);
            plateform = swiftness::Level::initializeLevel03();
        }
    }

    void Hello::displayWelcomeMenu(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square) {
        std::cout << "############################" << '\n';
        std::cout << BLUE << "Bienvenue dans " << NC << YELLOW << "Swiftness ! " << NC << BLUE << "Un jeu développé par Julien GAUTHIER, Naël EMBARKI et Théo HUMBERT" << NC << '\n';
        std::cout << BLUE << "Un jeu de plateforme en 2D absolument passionnant !" << NC << '\n';
        std::cout << PURPLE << "Sans plus tarder, commençons !" << NC << '\n';
        loadLevelWithOrWithoutTMX(plateform, square);
    }
}