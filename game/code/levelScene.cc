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
    levelScene::levelScene(GameCenter& game, gf::Font& font, int level, std::vector<swiftness::StaticPlateform>& plateform, swiftness::Square& square, std::vector<Input>& enumVector, gf::Vector2f& camera) : 
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    m_font(font), 
    game(game), 
    level(level), 
    plateform(plateform), 
    square(square),
    enumVector(enumVector),
    m_camera(camera),
    m_levelData(LEVELS_TMX_PATH + "level0" + std::to_string(level) + ".tmx"),
    quit_a("quit")
    , up("up")
    , down("down")
    , left("left")
    , right("right")
    , jump("jump")
    , upJump("upJump")
    , leftJump("leftJump")
    , rightJump("rightJump")
     {
        m_text.setFont(m_font);
        m_text.setCharacterSize(20);
        m_text.setColor(gf::Color::Yellow);
        gf::Gamepad::initialize();

        quit_a.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
        quit_a.addKeycodeKeyControl(gf::Keycode::Escape);
        addAction(quit_a);

        up.setContinuous();
        up.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        up.addScancodeKeyControl(gf::Scancode::Up);
        up.addScancodeKeyControl(gf::Scancode::W);
        up.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        addAction(up);

        upJump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        upJump.addScancodeKeyControl(gf::Scancode::Up);
        upJump.addScancodeKeyControl(gf::Scancode::W);
        upJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        addAction(upJump);

        down.setContinuous();
        down.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
        down.addScancodeKeyControl(gf::Scancode::Down);
        down.addScancodeKeyControl(gf::Scancode::S);
        down.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
        addAction(down);

        left.setContinuous();
        left.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadLeft);
        left.addScancodeKeyControl(gf::Scancode::Left);
        left.addScancodeKeyControl(gf::Scancode::A);
        left.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
        addAction(left);

        leftJump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadLeft);
        leftJump.addScancodeKeyControl(gf::Scancode::Left);
        leftJump.addScancodeKeyControl(gf::Scancode::A);
        leftJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
        addAction(leftJump);

        right.setContinuous();
        right.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadRight);
        right.addScancodeKeyControl(gf::Scancode::Right);
        right.addScancodeKeyControl(gf::Scancode::D);
        right.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
        addAction(right);

        rightJump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadRight);
        rightJump.addScancodeKeyControl(gf::Scancode::Right);
        rightJump.addScancodeKeyControl(gf::Scancode::D);
        rightJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
        addAction(rightJump);

        jump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
        jump.addKeycodeKeyControl(gf::Keycode::Space);
        addAction(jump);
    }

    levelScene::~levelScene() {}

    int levelScene::getLevel(){ return level; }

    void levelScene::updateLevel(int s_level) {
        level = s_level;
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void levelScene::loadLevel(std::vector<swiftness::StaticPlateform> &plateform, swiftness::Square& square, int level) {
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
        square.setPlateforms(plateform);
    }

    void levelScene::doHandleActions(gf::Window& window) {
        //if (!isActive()) return;
        if (quit_a.isActive()) game.replaceScene(game.menu);
        if(up.isActive()) {
            square.actionUp();
        } else {
            square.actionUpRelease();
        }
        if(down.isActive()){
            square.actionDown();
        } else {
            square.actionDownRelease();
        }
        if(left.isActive()){
            square.actionLeft();
        } else {
            square.actionLeftRelease();
        }
        if (right.isActive()) {
            square.actionRight();
        } else {
            square.actionRightRelease();
        }
        if (upJump.isActive()) square.actionUpJump();
        if (leftJump.isActive()) square.actionLeftJump();
        if (rightJump.isActive()) square.actionRightJump();
        if (jump.isActive()) square.actionJump();
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
        square.update(dt);
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
        /*gf::Event event;
        swiftness::CommandsManager commandManager;
        while (game.getWindow().pollEvent(event))
        {
            commandManager.manageCommands(enumVector, event);
        }
        std::vector<Input>::iterator it1 = std::find(enumVector.begin(), enumVector.end(), Input::Escape);
        std::vector<Input>::iterator it2 = std::find(enumVector.begin(), enumVector.end(), Input::Closed);
        if (it1 != enumVector.end() || it2 != enumVector.end()) {
            game.replaceAllScenes(game.menu);
        }*/
    }
}