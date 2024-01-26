#include "levelScene.h"
#include "GameCenter.h"
#include <unistd.h>
#include <iostream>
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
    levelScene::levelScene(GameCenter& game, gf::Font& font, gf::ResourceManager& resources, int level) : 
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    m_font(font), 
    game(game),
    m_levelNumber(level),
    m_levelData("level0" + std::to_string(m_levelNumber) + ".tmx"),
    quit_a("quit")
    , up("up")
    , down("down")
    , left("left")
    , right("right")
    , jump("jump")
    , upJump("upJump")
    , leftJump("leftJump")
    , rightJump("rightJump")
    , map_width(m_levelData.getMapSize().x)
    , map_height(m_levelData.getMapSize().y)
    , tile_width(m_levelData.getTileSize().x)
    , tile_height(m_levelData.getTileSize().y)
    , xcamera(m_square.getPosition().x)
    , ycamera(m_square.getPosition().y)
     {

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

    int levelScene::getLevel(){ return m_levelNumber; }

    void levelScene::updateLevel(int s_level) {
        m_levelNumber = s_level;
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void levelScene::loadLevel(int t_level) {
        if (t_level < 0) {
            exit(0);
        }
        updateLevel(t_level);
        std::string lvl = "";
        if (t_level >= 0 && t_level < 10) {
            lvl = "level0" + std::to_string(t_level) + ".tmx";
        } else {
            lvl = "level" + std::to_string(t_level) + ".tmx";
        }
        std::cout << GREEN << "File load : " << lvl << NC << std::endl;
        swiftness::Level::level leveln = Level::initializeLevel(lvl);
        m_square = leveln.square;
        m_plateform = leveln.plateform;
        m_square.setPlateforms(m_plateform);
    }

    void levelScene::doHandleActions(gf::Window& window) {
        //if (!isActive()) return;
        if (quit_a.isActive()) {
            m_square.squareReset();
            game.replaceScene(game.menu);
        }
        if(up.isActive()) {
            m_square.actionUp();
        } else {
            m_square.actionUpRelease();
        }
        if(down.isActive()){
            m_square.actionDown();
        } else {
            m_square.actionDownRelease();
        }
        if(left.isActive()){
            m_square.actionLeft();
        } else {
            m_square.actionLeftRelease();
        }
        if (right.isActive()) {
            m_square.actionRight();
        } else {
            m_square.actionRightRelease();
        }
        if (upJump.isActive()) m_square.actionUpJump();
        if (leftJump.isActive()) m_square.actionLeftJump();
        if (rightJump.isActive()) m_square.actionRightJump();
        if (jump.isActive()) m_square.actionJump();
    }

    void levelScene::doRender (gf::RenderTarget& target, const gf::RenderStates &states) {
        gf::ExtendView cam(m_camera, {SCREEN_WIDTH, SCREEN_HEIGHT});
        target.clear(gf::Color::Black);
        target.setView(cam);
        swiftness::LevelRender renderLevel;
        renderLevel.renderLevel("level0" + std::to_string(m_levelNumber) + ".tmx", target, m_square.getGravity());
        m_square.render(target);
        m_square.renderHUD(target, SCREEN_WIDTH, SCREEN_HEIGHT, m_camera);
    }

    void levelScene::doUpdate(gf::Time time) {
        float dt = time.asSeconds();
        m_square.update(dt);
        if (m_square.getLevelOver()) game.replaceAllScenes(game.menu);
        map_width=m_levelData.getMapSize().x;
        map_height=m_levelData.getMapSize().y;
        tile_width=m_levelData.getTileSize().x;
        tile_height=m_levelData.getTileSize().y;
        xcamera=m_square.getPosition().x;
        ycamera=m_square.getPosition().y;
        xcamera=std::clamp(xcamera,SCREEN_WIDTH/2+tile_width,map_width*tile_width-SCREEN_WIDTH/2-tile_width);
        ycamera=std::clamp(ycamera,SCREEN_HEIGHT/2+tile_height,map_height*tile_height-SCREEN_HEIGHT/2-tile_height);
        m_camera = {xcamera, ycamera};
    }
}