#include "helloNewPadawan.h"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define PURPLE "\x1b[35m"
#define CYAN    "\x1b[36m"
#define NC   "\x1b[0m"

namespace swiftness {
    
    // Déclaration en première instance du constructeur et du destructeur,
    // de Hello (CMD)
    Hello::Hello() {}
    Hello::~Hello() {}
    // Déclaration en seconde instance du constructeur et du destructeur,
    // de menuHello (interface graphique)
    MenuHello::MenuHello(gf::Font& font, gf::Window& window) : m_font(font), m_window(window), m_selectedLevel(-1) {
        m_text.setFont(m_font);
        m_text.setCharacterSize(20);
        m_text.setColor(gf::Color::White);
    }
    MenuHello::~MenuHello() {}
    
    int Hello::askLevel() {
        std::cout << YELLOW << "Quel niveau souhaitez vous effectuer (-1 pour quitter le script) ?\n\t=> " << NC;
        int n; std::cin >> n; return n;
    }

    void Hello::loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square) {
        int level = askLevel();
        while ((level < MIN_LEVEL || level > MAX_LEVEL) && level != -1) {
            std::cout << RED << "Erreur : le choix du niveau est incorrect" << NC << std::endl;
            std::cout << YELLOW << "Le niveau doit être compris entre " << MIN_LEVEL << " et " << MAX_LEVEL << NC << '\n';
            level = askLevel();
        } 
        if (level == -1) {
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
            std::cout << GREEN << "Level chosen : level04.tmx - Julien" << NC << std::endl;
            swiftness::Level::level level04 = Level::initializeLevel("level04.tmx");
            square = level04.square;
            plateform = level04.plateform;
        } else if (level == 5) {
            std::cout << GREEN << "Level chosen : level05 - Théo" << NC << std::endl;
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

    int MenuHello::getLevel(){ return m_selectedLevel; }

    void MenuHello::displayLevelSelection(gf::Window& window, gf::Font& font, int& selectedLevel) {
        // Vous devrez adapter ces valeurs en fonction de vos besoins
        const float buttonHeight = 40.0f, margin = 10.0f, totalHeight = (buttonHeight + margin) * (MAX_LEVEL - MIN_LEVEL + 1);
        gf::RenderWindow render(window);
        render.clear(gf::Color::White);
        gf::Event event;
        while (window.pollEvent(event)) {
            for (int level = MIN_LEVEL; level <= MAX_LEVEL; ++level) {
                gf::Text buttonText("Level " + std::to_string(level), font);
                buttonText.setCharacterSize(20);
                float buttonX = WINDOW_WIDTH / 2 - buttonText.getLocalBounds().getWidth() / 2;
                float buttonY = WINDOW_HEIGHT / 2 - totalHeight / 2 + (buttonHeight + margin) * (level - MIN_LEVEL);
                buttonText.setPosition({buttonX, buttonY});
                render.draw(buttonText);
                if (event.type == gf::EventType::MouseButtonPressed && event.mouseButton.button == gf::MouseButton::Left) {
                    selectedLevel = level;
                }
            }
        }
        render.display();
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void MenuHello::loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level) {
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

    void MenuHello::displayWelcomeMenu(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square) {
        displayLevelSelection(m_window, m_font, m_selectedLevel);
        loadLevelWithOrWithoutTMX(plateform, square, m_selectedLevel);
    }
}