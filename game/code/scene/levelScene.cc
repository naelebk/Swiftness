#include "levelScene.h"
#include "../gameCenter.h"
#include <unistd.h>
#include <gf/Coordinates.h>
#include <iostream>
#include <gf/Sprite.h>

namespace swiftness {
    // Déclaration en seconde instance du constructeur et du destructeur,
    // de levelScene (interface graphique)
    levelScene::levelScene(GameCenter& game, gf::Font& font, int level) : 
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    m_font(font), 
    game(game),
    m_levelNumber(level),
    m_levelData("level0" + std::to_string(m_levelNumber) + ".tmx")
    , up("up")
    , down("down")
    , left("left")
    , right("right")
    , jump("jump")
    , upJump("upJump")
    , downJump("downJump")
    , leftJump("leftJump")
    , rightJump("rightJump")
    , Pause("pause")
    , map_width(m_levelData.getMapSize().x)
    , map_height(m_levelData.getMapSize().y)
    , tile_width(m_levelData.getTileSize().x)
    , tile_height(m_levelData.getTileSize().y)
    , xcamera(m_square.getPosition().x)
    , ycamera(m_square.getPosition().y)
    , konami(0)
    , konami2(0)
    , canFly(false)
    , commandsChange(false)
     {
        gf::Gamepad::initialize();

        up.setContinuous();
        up.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        up.addScancodeKeyControl(gf::Scancode::Up);
        up.addScancodeKeyControl(gf::Scancode::W);
        up.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        addAction(up);
        
        Pause.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Start);
        Pause.addScancodeKeyControl(gf::Scancode::P);
        Pause.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
        Pause.addKeycodeKeyControl(gf::Keycode::Escape);
        addAction(Pause);

        upJump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        upJump.addScancodeKeyControl(gf::Scancode::Up);
        upJump.addScancodeKeyControl(gf::Scancode::W);
        //upJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        addAction(upJump);


        down.setContinuous();
        down.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
        down.addScancodeKeyControl(gf::Scancode::Down);
        down.addScancodeKeyControl(gf::Scancode::S);
        down.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
        addAction(down);

        downJump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
        downJump.addScancodeKeyControl(gf::Scancode::Down);
        downJump.addScancodeKeyControl(gf::Scancode::S);
        addAction(downJump);

        left.setContinuous();
        left.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadLeft);
        left.addScancodeKeyControl(gf::Scancode::Left);
        left.addScancodeKeyControl(gf::Scancode::A);
        left.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
        addAction(left);

        leftJump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadLeft);
        leftJump.addScancodeKeyControl(gf::Scancode::Left);
        leftJump.addScancodeKeyControl(gf::Scancode::A);
        //leftJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
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
        //rightJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
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
            std::cout << GREEN << "Level -> 0" << std::to_string(t_level) << NC << std::endl;
        } else {
            lvl = "level" + std::to_string(t_level) + ".tmx";
            std::cout << GREEN << "Level -> " << std::to_string(t_level) << NC << std::endl;
        }
        
        swiftness::LevelInitializer::level leveln = LevelInitializer::initializeLevel(lvl);
        m_square = leveln.square;
        m_plateform = leveln.plateform;
        m_square.setPlateforms(m_plateform);
    }

    void levelScene::doHandleActions(gf::Window& window) {
        if (!isActive()) pause();
        if (Pause.isActive()) {
            isPaused() ? resume() : pause();
            game.pushScene(game.s_pause);
            return;
        }
        if (!commandsChange) {
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
            if (upJump.isActive()) {
                m_square.actionUpJump();
                if (konami == 0) {
                    konami++;
                } else if (konami == 1) {
                    konami++;
                } else if (konami == 2) {
                    konami=2;
                } 
                else {
                    konami = 1;
                }
            }
            if (downJump.isActive()){
                if (konami == 2) {
                    konami++;
                } else if (konami == 3) {
                    konami++;
                } else {
                    konami = 0;
                }
            }
            if (leftJump.isActive()) {
                m_square.actionLeftJump();
                if (konami == 4) {
                    konami++;
                } else if (konami == 6) {
                    konami++;
                } else {
                    konami = 0;
                }
            }
            if (rightJump.isActive()) {
                m_square.actionRightJump();
                if (konami == 5) {
                    konami++;
                } else if (konami == 7) {
                    konami++;
                } else {
                    konami = 0;
                }
            }
            if (jump.isActive()) {
                m_square.actionJump();
                if (konami == 8) {
                    konami++;
                } else if (konami == 9) {
                    konami++;
                } else {
                    konami = 0;
                }
            }
        } else {
            up.isActive() ? m_square.actionDown() : m_square.actionDownRelease();
            right.isActive() ? m_square.actionUp() : m_square.actionUpRelease();
            down.isActive() ? m_square.actionLeft() : m_square.actionLeftRelease();
            left.isActive() ? m_square.actionRight() : m_square.actionRightRelease();
        }
        if (konami == 10) {
            m_square.setIsFlying(true);
            canFly = true;
            commandsChange = true; 
            konami = -1;
        }
    }

    void levelScene::doRender (gf::RenderTarget& target, const gf::RenderStates &states) {
        gf::ExtendView cam(m_camera, {SCREEN_WIDTH, SCREEN_HEIGHT});
        isPaused() ? target.clear(gf::Color::Blue) :
        canFly && commandsChange ? target.clear(gf::Color::Violet/*a*/) :
        target.clear(gf::Color::fromRgb(0.2, 0.2, 0.2));
        target.setView(cam);
        swiftness::LevelRender renderLevel;
        renderLevel.renderLevel(game.resources, m_levelData, "level0" + std::to_string(m_levelNumber) + ".tmx", target, m_square.getGravity());
        m_square.render(target, states);
        m_square.renderHUD(target, SCREEN_WIDTH, SCREEN_HEIGHT, m_camera);
    }

    void levelScene::doUpdate(gf::Time time) {
        m_square.update(time);
        if (m_square.getLevelOver()) {
            game.levelTheme.stop();
            game.mainTheme.play();
            game.replaceAllScenes(game.menu, trans, gf::milliseconds(500));
        }
        map_width=m_levelData.getMapSize().x;
        map_height=m_levelData.getMapSize().y;
        tile_width=m_levelData.getTileSize().x;
        tile_height=m_levelData.getTileSize().y;
        xcamera=m_square.getPosition().x;
        ycamera=m_square.getPosition().y;
        xcamera=gf::clamp(xcamera,SCREEN_WIDTH/2+tile_width,map_width*tile_width-SCREEN_WIDTH/2-tile_width);
        ycamera=gf::clamp(ycamera,SCREEN_HEIGHT/2+tile_height,map_height*tile_height-SCREEN_HEIGHT/2-tile_height);
        m_camera = {xcamera, ycamera};
    }
}
