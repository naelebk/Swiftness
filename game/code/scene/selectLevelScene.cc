#include "selectLevelScene.h"
#include "../gameCenter.h"
#include <gf/Coordinates.h>
#include "levelScene.h"

namespace swiftness
{
    SelectLevel::SelectLevel(GameCenter &game, gf::Font &font) : gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
                                                                 font(font),
                                                                 game(game),
                                                                 up("Up"),
                                                                 down("Down"),
                                                                 trigger("Trigger"),
                                                                 quit("Quit"),
                                                                 level00(game, font, 0, false),
                                                                 level01(game, font, 1, false),
                                                                 level02(game, font, 2, false),
                                                                 level03(game, font, 3, false),
                                                                 level04(game, font, 4, false),
                                                                 level05(game, font, 5, false),
                                                                 level06(game, font, 6, false),
                                                                 level07(game, font, 7, false),
                                                                 level08(game, font, 8, false),
                                                                 level09(game, font, 9, false),
                                                                 level10(game, font, 10, false)
    {
        levels_b.emplace_back("Tutorial", font, 60);
        for (int i = 1; i < MAX_LEVEL; ++i)
        {
            levels_b.emplace_back("0" + std::to_string(i), font, 60);
        }
        levels_b.emplace_back("10", font, 60);
        levels_b.emplace_back("Main Menu", font, 60);
        setClearColor(gf::Color::Black);

        quit.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
        quit.addKeycodeKeyControl(gf::Keycode::Escape);
        addAction(quit);

        up.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        up.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        up.addScancodeKeyControl(gf::Scancode::Up);
        addAction(up);

        down.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
        down.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
        down.addScancodeKeyControl(gf::Scancode::Down);
        addAction(down);

        trigger.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
        trigger.addScancodeKeyControl(gf::Scancode::Return);
        trigger.addScancodeKeyControl(gf::Scancode::Space);
        trigger.addMouseButtonControl(gf::MouseButton::Left);
        addAction(trigger);

        auto createButtons = [&](gf::TextButtonWidget &button, auto callback)
        {
            button.setDefaultTextColor(gf::Color::Black);
            button.setDefaultBackgroundColor(gf::Color::Gray(0.7f));
            button.setSelectedTextColor(gf::Color::Black);
            button.setSelectedBackgroundColor(gf::Color::Green);
            button.setDisabledTextColor(gf::Color::Black);
            button.setDisabledBackgroundColor(gf::Color::Red);
            button.setAnchor(gf::Anchor::Center);
            button.setPadding(5.0f);
            button.setCallback(callback);
            widgets.addWidget(button);
        };

        auto calculateXPos = [&](int i, int max)
        {
            return 550.0f + (i - 1) * 500.0f / (max - 1);
        };

        level00.loadLevel(0);
        level01.loadLevel(1);
        level02.loadLevel(2);
        level03.loadLevel(3);
        level04.loadLevel(4);
        level05.loadLevel(5);
        level06.loadLevel(6);
        level07.loadLevel(7);
        level08.loadLevel(8);
        level09.loadLevel(9);
        level10.loadLevel(10);

        // button tutorial
        createButtons(
            levels_b[0], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level00, pixel, gf::milliseconds(500));
            }
        );

        // button level 1 to 5
        createButtons(
            levels_b[1], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level01, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[2], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level02, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[3], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level03, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[4], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level04, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[5], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level05, pixel, gf::milliseconds(500)); 
            }
        );

        // button level 6 to 10
        createButtons(
            levels_b[6], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level06, pixel, gf::milliseconds(500));
            }
        );

        createButtons(
            levels_b[7], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level07, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[8], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level08, pixel, gf::milliseconds(500));
            }
        );

        createButtons(
            levels_b[9], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level09, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[10], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level10, pixel, gf::milliseconds(500)); 
            }
        );
        
        // button main menu
        createButtons(
            levels_b[MAX_LEVEL + 1], [&]()
            { game.replaceAllScenes(game.menu, trans, gf::milliseconds(500)); 
            }
        );
    }

    SelectLevel::~SelectLevel() {}

    gf::WidgetContainer SelectLevel::GameLevel_getWidgets()
    {
        return widgets;
    }

    std::string getLevelNameByButton(gf::TextButtonWidget &button)
    {
        std::string buttonName = button.getString();
        return buttonName == "Tutorial" ? "level00.tmx" : buttonName + ".tmx";
    }

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void SelectLevel::doHandleActions(gf::Window &window)
    {
        if (!window.isOpen())
            return;
        if (up.isActive())
            widgets.selectPreviousWidget();
        if (down.isActive())
            widgets.selectNextWidget();
        if (trigger.isActive())
            widgets.triggerAction();
        if (quit.isActive())
            game.replaceScene(game.menu, trans, gf::milliseconds(500));
    }

    void SelectLevel::doProcessEvent(gf::Event &event)
    {
        switch (event.type)
        {
        case gf::EventType::MouseMoved:
            widgets.pointTo(game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
            break;
        default:
            break;
        }
    }

    void SelectLevel::doRender(gf::RenderTarget &target, const gf::RenderStates &states)
    {
        float verticalPadding = 50.0f;
        float buttonHeight = 150.0f;
        gf::Vector2f bg_size(0.55f, 0.1f);
        target.setView(getHudView());
        gf::Coordinates coords(target);
        auto calculateXPos = [&](int i, int max, gf::Coordinates coords)
        {
            return coords.getRelativePoint(bg_size - 0.375f).x + (i - 1) * coords.getRelativePoint(bg_size + 0.1f).x / (max - 1);
        };
        auto bigButton = [&](gf::Coordinates coords)
        {
            return coords.getRelativePoint(bg_size - 0.05f).x;
        };
        float totalContentHeight = buttonHeight * 3 + verticalPadding * 2;
        float startHeight = (WINDOW_HEIGHT - totalContentHeight) / 2;
        float yPos = coords.getRelativePoint(bg_size + 0.25f).y;
        float size = 0.025f, size2 = size / 4, space = 0.03f;
        levels_b[0].setPosition({bigButton(coords), coords.getRelativePoint(bg_size).y});
        levels_b[1].setPosition({calculateXPos(1, 5, coords), yPos});
        levels_b[2].setPosition({calculateXPos(2, 5, coords), yPos});
        levels_b[3].setPosition({calculateXPos(3, 5, coords), yPos});
        levels_b[4].setPosition({calculateXPos(4, 5, coords), yPos});
        levels_b[5].setPosition({calculateXPos(5, 5, coords), yPos});
        yPos = coords.getRelativePoint(bg_size + 0.5f).y;
        levels_b[6].setPosition({calculateXPos(1, 5, coords), yPos});
        levels_b[7].setPosition({calculateXPos(2, 5, coords), yPos});
        levels_b[8].setPosition({calculateXPos(3, 5, coords), yPos});
        levels_b[9].setPosition({calculateXPos(4, 5, coords), yPos});
        levels_b[10].setPosition({calculateXPos(5, 5, coords), yPos});
        yPos = coords.getRelativePoint(bg_size + 0.75f).y;
        levels_b[MAX_LEVEL + 1].setPosition({bigButton(coords), yPos});
        widgets.render(target, states);
    }
    void SelectLevel::doShow()
    {
        widgets.clear();
        for (gf::TextButtonWidget &b : levels_b)
        {
            b.setDefault();
            widgets.addWidget(b);
        }
        widgets.selectNextWidget();
    }
}
