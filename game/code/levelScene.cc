#include "levelScene.h"
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
    // de levelScene (interface graphique)
    levelScene::levelScene(GameCenter& game, gf::Font& font, int level, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square, std::vector<Input>& enumVector, gf::Vector2f& camera) : 
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    m_font(font), 
    game(game), 
    level(level), 
    plateform(plateform), 
    square(square),
    enumVector(enumVector),
    m_camera(camera),
    m_levelData(LEVELS_TMX_PATH + "level0" + std::to_string(level) + ".tmx"),
    quit_a("quit") {
        m_text.setFont(m_font);
        m_text.setCharacterSize(20);
        m_text.setColor(gf::Color::Yellow);
        gf::Gamepad::initialize();

        quit_a.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
        quit_a.addKeycodeKeyControl(gf::Keycode::Escape);
        addAction(quit_a);
    }

    levelScene::~levelScene() {}

    int levelScene::getLevel(){ return level; }

    void levelScene::updateLevel(int s_level) {
        level = s_level;
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void levelScene::loadLevel(std::map<int, swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level) {
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

    void levelScene::doHandleActions(gf::Window& window) {
        if (!isActive()) return;
        if (quit_a.isActive()) game.replaceScene(game.menu);
    }

    void levelScene::doRender (gf::RenderTarget& target, const gf::RenderStates &states) {
        gf::ExtendView cam(m_camera, {SCREEN_WIDTH, SCREEN_HEIGHT});
        target.clear(gf::Color::Black);
        target.setView(cam);
        swiftness::LevelRender renderLevel;
        renderLevel.renderLevel("level0" + std::to_string(level) + ".tmx", target, square.getGravity());
        square.render(target);
        square.renderHUD(target, SCREEN_WIDTH, SCREEN_HEIGHT, m_camera);
    }

    void levelScene::doUpdate(gf::Time time) {
        float dt = time.asSeconds();
        square.update(dt, plateform, enumVector);
        if (square.getLevelOver()) game.replaceAllScenes(game.menu);
        std::string lvl = "";
        if (level >= 0 && level < 10) {
            lvl = "level0" + std::to_string(level) + ".tmx";
        } else {
            lvl = "level" + std::to_string(level) + ".tmx";
        }
        swiftness::LevelData ldata(lvl);
        float map_width=ldata.getMapSize().x;
        float map_height=ldata.getMapSize().y;
        float tile_width=ldata.getTileSize().x;
        float tile_height=ldata.getTileSize().y;
        float xcamera=square.getPosition().x;
        float ycamera=square.getPosition().y;
        xcamera=std::clamp(xcamera,SCREEN_WIDTH/2+tile_width,map_width*tile_width-SCREEN_WIDTH/2-tile_width);
        ycamera=std::clamp(ycamera,SCREEN_HEIGHT/2+tile_height,map_height*tile_height-SCREEN_HEIGHT/2-tile_height);
        m_camera = {xcamera, ycamera};
        gf::Event event;
        swiftness::CommandsManager commandManager;
        while (game.getWindow().pollEvent(event))
        {
            commandManager.manageCommands(enumVector, event);
        }
        std::vector<Input>::iterator it1 = std::find(enumVector.begin(), enumVector.end(), Input::Escape);
        std::vector<Input>::iterator it2 = std::find(enumVector.begin(), enumVector.end(), Input::Closed);
        if (it1 != enumVector.end() || it2 != enumVector.end()) {
            game.replaceAllScenes(game.menu);
        }
    }
}