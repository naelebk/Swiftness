#include "levelScene.h"
#include "../gameCenter.h"
#include <unistd.h>
#include <gf/Coordinates.h>
#include <iostream>
#include <gf/Sprite.h>

namespace swiftness
{
    // Déclaration en seconde instance du constructeur et du destructeur,
    // de levelScene (interface graphique)
    levelScene::levelScene(GameCenter &game, gf::Font &font, int level, bool custom)
        : gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)), m_font(font), game(game), m_custom(custom), m_levelNumber(level)
          // , m_level.getLevelData()("custom/custom_" + std::to_string(m_levelNumber) + ".tmx")
          // , m_level.getLevelData()("level_" + std::to_string(m_levelNumber) + ".tmx")
          ,
          m_level(game.resources, (custom ? "custom/custom_" : "level_") + std::to_string(m_levelNumber) + ".tmx"), up("up"), down("down"), left("left"), right("right"), jump("jump"), upJump("upJump"), downJump("downJump"), leftJump("leftJump"), rightJump("rightJump"), Pause("pause"), map_width(m_level.getLevelData().getMapSize().x), map_height(m_level.getLevelData().getMapSize().y), tile_width(m_level.getLevelData().getTileSize().x), tile_height(m_level.getLevelData().getTileSize().y), xcamera(m_level.getSquareEntity().getPosition().x), ycamera(m_level.getSquareEntity().getPosition().y), konami(0), konami2(0), canFly(false), commandsChange(false), s_pause(game, m_font, m_level), m_time_of_konami(0)
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
        // upJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
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
        // leftJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
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
        // rightJump.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
        addAction(rightJump);

        jump.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
        jump.addKeycodeKeyControl(gf::Keycode::Space);
        addAction(jump);

        m_level.resetLevel();
    }

    int levelScene::getLevel() { return m_levelNumber; }

    void levelScene::updateLevel(int s_level)
    {
        m_levelNumber = s_level;
    }

    // Comme on ne peut pas mettre une valeur non comprise entre MIN_LEVEL et MAX_LEVEL, on n'effectue aucune
    // vérification sur la valeur de level, car auquel cas rien ne sera fait
    void levelScene::loadLevel(int t_level)
    {
        if (t_level < 0)
        {
            exit(0);
        }
        updateLevel(t_level);
        std::string lvl = "level_" + std::to_string(t_level) + ".tmx";
        std::cout << GREEN << "Level -> " << std::to_string(t_level) << NC << std::endl;

        m_level.getSquareEntity().setPlateforms(m_level.getPlateforms());
    }

    void levelScene::customLoadLevel(int t_level)
    {
        if (t_level < 0)
        {
            exit(0);
        }
        updateLevel(t_level);
        std::string lvl = "custom/custom_" + std::to_string(t_level) + ".tmx";
        std::cout << GREEN << "Level -> 0" << std::to_string(t_level) << NC << std::endl;

        m_level.getSquareEntity().setPlateforms(m_level.getPlateforms());
    }

    void levelScene::resetAllActions() {
        up.setInstantaneous();
        up.reset();
        right.setInstantaneous();
        right.reset();
        left.setInstantaneous();
        left.reset();
        down.setInstantaneous();
        down.reset();
    }

    void levelScene::doHandleActions(gf::Window &window)
    {
        if (up.isInstantaneous() && left.isInstantaneous() && right.isInstantaneous() && down.isInstantaneous()) {
            up.setContinuous();
            down.setContinuous();
            left.setContinuous();
            right.setContinuous();
            konami = konami == 10 ? 0 : konami;
            m_level.getSquareEntity().setIsFlying(false);
            canFly = false;
            commandsChange = false;
        }
        if (!isActive()) return;
        if (Pause.isActive())
        {
            resetAllActions();
            isPaused() ? resume() : pause();
            game.pushScene(s_pause);
            return;
        }
	if (isPaused()) {
		return;
	}
        if (!commandsChange)
        {
            if (up.isActive())
            {
                m_level.getSquareEntity().actionUp();
            }
            else
            {
                m_level.getSquareEntity().actionUpRelease();
            }
            if (down.isActive())
            {
                m_level.getSquareEntity().actionDown();
            }
            else
            {
                m_level.getSquareEntity().actionDownRelease();
            }
            if (left.isActive())
            {
                m_level.getSquareEntity().actionLeft();
            }
            else
            {
                m_level.getSquareEntity().actionLeftRelease();
            }
            if (right.isActive())
            {
                m_level.getSquareEntity().actionRight();
            }
            else
            {
                m_level.getSquareEntity().actionRightRelease();
            }
            if (upJump.isActive())
            {
                m_level.getSquareEntity().actionUpJump();
                if (konami == 0)
                {
                    konami++;
                }
                else if (konami == 1)
                {
                    konami++;
                }
                else if (konami == 2)
                {
                    konami = 2;
                }
                else
                {
                    konami = 1;
                }
            }
            if (downJump.isActive())
            {
                if (konami == 2)
                {
                    konami++;
                }
                else if (konami == 3)
                {
                    konami++;
                }
                else
                {
                    konami = 0;
                }
            }
            if (leftJump.isActive())
            {
                m_level.getSquareEntity().actionLeftJump();
                if (konami == 4)
                {
                    konami++;
                }
                else if (konami == 6)
                {
                    konami++;
                }
                else
                {
                    konami = 0;
                }
            }
            if (rightJump.isActive())
            {
                m_level.getSquareEntity().actionRightJump();
                if (konami == 5)
                {
                    konami++;
                }
                else if (konami == 7)
                {
                    konami++;
                }
                else
                {
                    konami = 0;
                }
            }
            if (jump.isActive())
            {
                m_level.getSquareEntity().actionJump();
                if (konami == 8)
                {
                    konami++;
                }
                else if (konami == 9)
                {
                    konami++;
                }
                else
                {
                    konami = 0;
                }
            }
        }
        else
        {
            up.isActive() ? m_level.getSquareEntity().actionDown() : m_level.getSquareEntity().actionDownRelease();
            right.isActive() ? m_level.getSquareEntity().actionUp() : m_level.getSquareEntity().actionUpRelease();
            down.isActive() ? m_level.getSquareEntity().actionLeft() : m_level.getSquareEntity().actionLeftRelease();
            left.isActive() ? m_level.getSquareEntity().actionRight() : m_level.getSquareEntity().actionRightRelease();
        }
        if (konami == 10)
        {
            m_level.getSquareEntity().setIsFlying(true);
            canFly = true;
            commandsChange = true;
            konami = -1;
            game.levelTheme.stop();
            game.Konami.setLoop(false);
            game.Konami.play();
        }
    }

    void levelScene::doRender(gf::RenderTarget &target, const gf::RenderStates &states)
    {
        gf::ExtendView cam(m_camera, {SCREEN_WIDTH, SCREEN_HEIGHT});
        if (canFly && commandsChange) {
            double t = m_time_of_konami % 120 / 120.0;
            double red = 0.5 + 0.5 * std::cos(t * 2 * M_PI);
            double green = 0.5 + 0.5 * std::cos((t + 1.0 / 3.0) * 2 * M_PI);
            double blue = 0.5 + 0.5 * std::cos((t + 2.0 / 3.0) * 2 * M_PI);
            target.clear(gf::Color::fromRgb(red, green, blue));
        } else {
            target.clear(gf::Color::fromRgb(0.2, 0.2, 0.2));
        }
        target.setView(cam);
        swiftness::LevelRender renderLevel;
        renderLevel.renderLevel(game.resources, m_level.getLevelData(), target, m_level.getSquareEntity().getGravity());
        m_level.getSquareEntity().render(target, states);
        m_level.getSquareEntity().renderHUD(target, SCREEN_WIDTH, SCREEN_HEIGHT, m_camera);
        target.setView(getHudView());
        if (m_time_of_konami > 0) {
            float size = 0.035f, space = 0.04f;
            gf::Vector2f bg_size (0.55f, 0.1f); 
            target.setView(getHudView());
            gf::Coordinates coords(target);
            float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
            int r_size = coords.getRelativeCharacterSize(size);
            int remainingTime = (m_time_of_konami - 3600) / 60;
            if (remainingTime >= 0 && remainingTime <= 9) {
                gf::Text end("", m_font, 110 + 6 * remainingTime);
                end.setParagraphWidth(100.0f);
                end.setString("Fin dans " + std::to_string(10 - remainingTime) + "...");
                end.setColor(
                    remainingTime >= 0 && remainingTime < 2 ? gf::Color::Violet :
                    remainingTime >= 2 && remainingTime < 4 ? gf::Color::Yellow : 
                    remainingTime >= 4 && remainingTime < 6 ? gf::Color::Orange : 
                    remainingTime >= 6 && remainingTime <= 8 ? gf::Color::Red :
                    gf::Color::Black
                );
                end.setPosition(coords.getRelativePoint({0.5f, 0.4f}));
                end.setAnchor(gf::Anchor::Center);
                target.draw(end, states);
            }
        }
    }

    void levelScene::doUpdate(gf::Time time)
    {
        m_level.getSquareEntity().update(time);
        if (canFly && commandsChange) m_time_of_konami++;
        if (m_time_of_konami >= 4200) {
            canFly = false;
            commandsChange = false;
            m_level.getSquareEntity().setIsFlying(false);
            game.Konami.stop();
            game.levelTheme.setLoop(true);
            game.levelTheme.play();
            konami = -1;
            m_time_of_konami = 0;
        }
        if (m_level.getSquareEntity().getLevelOver())
        {
            m_level.getSquareEntity().setIsFlying(false);
            canFly = false;
            commandsChange = false;
            konami = -1;
            game.levelTheme.stop();
            game.Konami.stop();
            game.mainTheme.play();
            m_level.resetLevel();
            resetAllActions();
            m_time_of_konami = 0;
	    m_custom ? game.replaceAllScenes(game.custom, trans, gf::milliseconds(500)) : game.replaceAllScenes(game.level, trans, gf::milliseconds(500));
        }
        map_width = m_level.getLevelData().getMapSize().x;
        map_height = m_level.getLevelData().getMapSize().y;
        tile_width = m_level.getLevelData().getTileSize().x;
        tile_height = m_level.getLevelData().getTileSize().y;
        xcamera = m_level.getSquareEntity().getPosition().x;
        ycamera = m_level.getSquareEntity().getPosition().y;
        xcamera = gf::clamp(xcamera, SCREEN_WIDTH / 2 + tile_width, map_width * tile_width - SCREEN_WIDTH / 2 - tile_width);
        ycamera = gf::clamp(ycamera, SCREEN_HEIGHT / 2 + tile_height, map_height * tile_height - SCREEN_HEIGHT / 2 - tile_height);
        m_camera = {xcamera, ycamera};
    }
}
