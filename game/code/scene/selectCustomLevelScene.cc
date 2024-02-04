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
    trigger("Trigger"),
    quit("Quit"),
    level01(game, font, 1),
    level02(game, font, 2),
    level03(game, font, 3),
    level04(game, font, 4),
    level05(game, font, 5)
    {
        for (int i = MIN_CUSTOM_LEVEL ; i < MAX_CUSTOM_LEVEL + 2 ; ++i) {
            if (i == MAX_CUSTOM_LEVEL + 1) {
                levels_b.emplace_back("Main Menu", font, 60);
            } else {
                levels_b.emplace_back("Custom level " + std::to_string(i), font, 60);
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

        trigger.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
        trigger.addScancodeKeyControl(gf::Scancode::Return);
        trigger.addScancodeKeyControl(gf::Scancode::Space);
        trigger.addMouseButtonControl(gf::MouseButton::Left);
        addAction(trigger);

        auto createButtons = [&] (gf::TextButtonWidget& button, auto callback) {
            button.setDefaultTextColor(gf::Color::Black);
            button.setDefaultBackgroundColor(gf::Color::Gray(0.7f));
            button.setSelectedTextColor(gf::Color::Black);
            button.setSelectedBackgroundColor(gf::Color::Green);
            button.setDisabledTextColor(gf::Color::Black);
            button.setDisabledBackgroundColor(gf::Color::Red);
            button.setAnchor(gf::Anchor::TopLeft);
            button.setAlignment(gf::Alignment::Center);
            button.setCallback(callback);
            widgets.addWidget(button);
        };
        createButtons(levels_b[MAX_LEVEL], [&] () {
            game.replaceAllScenes(game.menu, trans, gf::milliseconds(500));
        });

        createButtons(levels_b[0], [&] () {
            level01.loadLevel(8);
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level01, pixel, gf::milliseconds(500));
            
        });

        createButtons(levels_b[1], [&] () {
            level02.loadLevel(9);
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level02, pixel, gf::milliseconds(500));
        });

        createButtons(levels_b[2], [&] () {
            level03.loadLevel(10);
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level03, pixel, gf::milliseconds(500));
        });

        createButtons(levels_b[3], [&] () {
            level04.loadLevel(11);
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level04, pixel, gf::milliseconds(500));
        });

        createButtons(levels_b[4], [&] () {
            level05.loadLevel(12);
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level05, pixel, gf::milliseconds(500));
        });

    }

    SelectCustomLevel::~SelectCustomLevel() {}

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void SelectCustomLevel::doHandleActions(gf::Window& window) {
        if (!window.isOpen()) return;
        if (up.isActive()) widgets.selectPreviousWidget();
        if (down.isActive()) widgets.selectNextWidget();
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

    void SelectCustomLevel::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
        float size = 0.035f, space = 0.04f;
        gf::Vector2f bg_size (0.55f, 0.1f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);
        float ne = 0.0f;
        for (int i = MIN_CUSTOM_LEVEL - 1 ; i < MAX_CUSTOM_LEVEL + 1 ; ++i) {
            ne = 0.1f + (size + space)*i;
            levels_b[i].setCharacterSize(r_size);
            levels_b[i].setPosition(coords.getRelativePoint({0.275f, ne}));
            levels_b[i].setParagraphWidth(width);
            levels_b[i].setPadding(padding);
        }        
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
