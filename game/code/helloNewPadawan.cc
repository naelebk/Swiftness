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

    void Hello::displayWelcomeMenu(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square) {
        std::cout << "############################" << '\n';
        std::cout << BLUE << "Bienvenue dans " << NC << YELLOW << "Swiftness ! " << NC << BLUE << "Un jeu développé par Julien GAUTHIER, Naël EMBARKI et Théo HUMBERT" << NC << '\n';
        std::cout << BLUE << "Un jeu de plateforme en 2D absolument passionnant !" << NC << '\n';
        std::cout << PURPLE << "Sans plus tarder, commençons !" << NC << '\n';
        //loadLevelWithOrWithoutTMX(plateform, square);
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
        std::string lvl = "";
        if (level >= 0 && level < 10) {
            lvl = "level0" + std::to_string(level) + ".tmx";
        } else {
            lvl = "level" + std::to_string(level) + ".tmx";
        }
        std::cout << GREEN << "File load : " << lvl << NC << std::endl;
        swiftness::Level::level leveln = Level::initializeLevel(lvl);
        square = leveln.square;
        plateform = leveln.plateform;
    }
}