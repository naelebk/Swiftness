#include "helloNewPadawan.h"
#include "GameCenter.h"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define PURPLE "\x1b[35m"
#define CYAN    "\x1b[36m"
#define NC   "\x1b[0m"

namespace swiftness {
    // Déclaration en seconde instance du constructeur et du destructeur,
    // de menuHello (interface graphique)
    MenuHello::MenuHello(GameCenter& game, gf::Font& font, int level, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square) : 
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    m_font(font), game(game), level(level), plateform(plateform), square(square) {
        m_text.setFont(m_font);
        m_text.setCharacterSize(20);
        m_text.setColor(gf::Color::Yellow);
        gf::Gamepad::initialize();
    }
    MenuHello::~MenuHello() {}

    int MenuHello::getLevel(){ return level; }

    void MenuHello::updateLevel(int s_level) {
        level = s_level;
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void MenuHello::loadLevelWithOrWithoutTMX(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level) {
        if (level < 0) {
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