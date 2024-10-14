#include "selectCustomLevelScene.h"
#include "../gameCenter.h"
#include <gf/Coordinates.h>
#include "levelScene.h"

namespace swiftness {
    SelectCustomLevel::SelectCustomLevel(GameCenter& game, gf::Font& font) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    font(font),
    game(game),
    up("Up"),
    down("Down"),
    left("Left"),
    right("Right"),
    trigger("Trigger"),
    quit("Quit"),
    level01(game, font, 1, true),
    level02(game, font, 2, true),
    level03(game, font, 3, true),
    level04(game, font, 4, true),
    level05(game, font, 5, true)
    {
        for (int i = MIN_CUSTOM_LEVEL ; i < MAX_CUSTOM_LEVEL + 2 ; ++i) {
            if (i == MAX_CUSTOM_LEVEL + 1) {
                levels_b.emplace_back("Main Menu", font, 60);
            } else {
                levels_b.emplace_back(std::to_string(i), font, 60);
            }
        }
        setClearColor(gf::Color::Black);

        quit.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
        quit.addKeycodeKeyControl(gf::Keycode::Escape);
        addAction(quit);

        up.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        up.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        up.addScancodeKeyControl(gf::Scancode::Up);
        addAction(up);//

        down.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
        down.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
        down.addScancodeKeyControl(gf::Scancode::Down);
        addAction(down);

        left.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadLeft);
        left.addScancodeKeyControl(gf::Scancode::Left);
        left.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
        addAction(left);

        right.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadRight);
        right.addScancodeKeyControl(gf::Scancode::Right);
        right.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
        addAction(right);

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

        level01.customLoadLevel(1);
        level02.customLoadLevel(2);
        level03.customLoadLevel(3);
        level04.customLoadLevel(4);
        level05.customLoadLevel(5);


        createButtons(
            levels_b[MAX_CUSTOM_LEVEL], [&]()
            { game.replaceAllScenes(game.menu, trans, gf::milliseconds(500)); 
            }
        );


        createButtons(
            levels_b[0], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level01, pixel, gf::milliseconds(500));
            }
        );

        // button level 1 to 5
        createButtons(
            levels_b[1], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level02, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[2], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level03, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[3], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level04, pixel, gf::milliseconds(500)); 
            }
        );

        createButtons(
            levels_b[4], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level05, pixel, gf::milliseconds(500)); 
            }
        );    

    }

    SelectCustomLevel::~SelectCustomLevel() {}

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void SelectCustomLevel::doHandleActions(gf::Window& window) {
        if (!window.isOpen()) return;
        if (up.isActive() || left.isActive()) widgets.selectPreviousWidget();
        if (down.isActive() || right.isActive()) widgets.selectNextWidget();
        if (trigger.isActive()) widgets.triggerAction();
        if (quit.isActive()) game.replaceScene(game.menu, trans, gf::milliseconds(500));
    }

    void SelectCustomLevel::doProcessEvent(gf::Event& event) {
        switch(event.type) {
            case gf::EventType::MouseMoved:
                widgets.pointTo(game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
                break;
            default:
                break;
        }
    }

    void SelectCustomLevel::doRender(gf::RenderTarget &target, const gf::RenderStates &states)
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
        levels_b[0].setPosition({calculateXPos(1, 5, coords), yPos});
        levels_b[1].setPosition({calculateXPos(2, 5, coords), yPos});
        levels_b[2].setPosition({calculateXPos(3, 5, coords), yPos});
        levels_b[3].setPosition({calculateXPos(4, 5, coords), yPos});
        levels_b[4].setPosition({calculateXPos(5, 5, coords), yPos});
        yPos = coords.getRelativePoint(bg_size + 0.75f).y;
        levels_b[MAX_CUSTOM_LEVEL].setPosition({bigButton(coords), yPos});
        widgets.render(target, states);
    }
    void SelectCustomLevel::doShow() {
        widgets.clear();
        for (gf::TextButtonWidget& b : levels_b) {
            b.setDefault();
            widgets.addWidget(b);
        }
        widgets.selectNextWidget();
    }
}
