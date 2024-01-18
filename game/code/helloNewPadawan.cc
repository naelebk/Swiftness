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
    MenuHello::MenuHello(gf::Font& font, gf::Window& window) : m_font(font), m_window(window), m_selectedLevel(-2) {
        m_text.setFont(m_font);
        m_text.setCharacterSize(20);
        m_text.setColor(gf::Color::Yellow);
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
            std::cout << GREEN << "Level chosen : level05 - Julien" << NC << std::endl;
            swiftness::Level::level level05 = Level::initializeLevel("level05.tmx");
            square = level05.square;
            plateform = level05.plateform;
        // } else if (level == 6) {
        //     std::cout << GREEN << "Level chosen : level06 - Théo" << NC << std::endl;
        //     square = swiftness::Square({100, 100}, 20.0f, gf::Color::Red, GRAVITY);
        //     plateform = swiftness::Level::initializeLevel03();
        // }
        } else if (level == 6) {
            std::cout << GREEN << "Level chosen : level05 - Julien" << NC << std::endl;
            swiftness::Level::level level06 = Level::initializeLevel("level06.tmx");
            square = level06.square;
            plateform = level06.plateform;
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

    bool MenuHello::displayLevelSelection(gf::RenderWindow& render, gf::Window& window, gf::Font& font, int& selectedLevel) {
        const float buttonHeight = 45.0f, margin = 20.0f;
        const int buttonCount = MAX_LEVEL + 2;
        while (true) {
            gf::RenderWindow render(window);
            render.clear(gf::Color::Black);
            for (int i = 0; i < buttonCount; ++i) {
                gf::RectangleShape shape({150.0f, buttonHeight});
                gf::Text buttonText;
                buttonText.setFont(font);
                buttonText.setColor(gf::Color::Black);
                buttonText.setCharacterSize(35);
                if (i == buttonCount - 1) {
                    buttonText.setString("Quit");
                    shape.setColor(gf::Color::Rose);
                } else {
                    buttonText.setString("Level " + std::to_string(i));
                    shape.setColor(gf::Color::Cyan);
                }
                float buttonX = WINDOW_WIDTH / 2;
                float buttonY = window.getSize().y / 2 - (buttonCount * (buttonHeight + margin)) / 2 + (buttonHeight + margin) * i;
                buttonText.setPosition({buttonX, buttonY});
                buttonText.setAnchor(gf::Anchor::Center);
                shape.setPosition({buttonX, buttonY});
                shape.setAnchor(gf::Anchor::Center);
                render.draw(shape);
                render.draw(buttonText);
            }
            render.display();
            gf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == gf::EventType::Closed) {
                    selectedLevel = -1;
                    window.close();
                    return true;
                }
                if (event.type == gf::EventType::MouseButtonPressed && event.mouseButton.button == gf::MouseButton::Left) {
                    float ystart=window.getSize().y / 2 - (buttonCount * (buttonHeight + margin)) / 2 - buttonHeight -margin;
                    int clickedButton = ((event.mouseButton.coords.y - ystart) / (buttonHeight/2 + 1.65f*margin)) - 1.3;
                    float xMouse=event.mouseButton.coords.x;
                    if (event.mouseButton.coords.y>= ystart - 500.0f && xMouse<=(window.getSize().x/2)+150.0f && xMouse>=(window.getSize().x/2)-150.0f && clickedButton >= 0 && clickedButton <= MAX_LEVEL) {
                        selectedLevel = clickedButton;
                        return true;
                    } else if (clickedButton == MAX_LEVEL + 1) {
                        selectedLevel = -1;
                        return true;
                    }
                }
            }
        }
        selectedLevel = -1;
        return false;
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void MenuHello::loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level) {
        if (level == -1) {
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
            std::cout << GREEN << "Level chosen : level05.tmx - Julien" << NC << std::endl;
            swiftness::Level::level level05 = Level::initializeLevel("level05.tmx");
            square = level05.square;
            plateform = level05.plateform;
        // } else if (level == 6) {
        //     std::cout << GREEN << "Level chosen : level06 - Théo" << NC << std::endl;
        //     square = swiftness::Square({100, 100}, 20.0f, gf::Color::Red, GRAVITY);
        //     plateform = swiftness::Level::initializeLevel03();
        // }
        } else if (level == 6) {
            std::cout << GREEN << "Level chosen : level06 - Théo" << NC << std::endl;
            swiftness::Level::level level06 = Level::initializeLevel("level06.tmx");
            square = level06.square;
            plateform = level06.plateform;
        }
        else if (level == 7) {
            std::cout << GREEN << "Level chosen : level07 - Julien" << NC << std::endl;
            swiftness::Level::level level06 = Level::initializeLevel("level07.tmx");
            square = level06.square;
            plateform = level06.plateform;
        }
    }
}