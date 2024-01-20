#include "GameLevel.h"
#include "GameCenter.h"
#include <gf/Coordinates.h>

namespace swiftness {
    SelectLevel::SelectLevel(GameCenter& game, gf::Font& font, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    font(font),
    game(game),
    plateform(plateform),
    square(square),
    up("Up"),
    down("Down"),
    trigger("Trigger"),
    quit("Quit")
    {
        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            if (i < MAX_LEVEL + 1) {
                levels_b.emplace_back("Level " + std::to_string(i), font, 60);
            } else {
                levels_b.emplace_back("Main Menu", font, 60);
            }
        }
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
        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            if (i == MAX_LEVEL + 1) {
                createButtons(levels_b[i], [&] () {
                    game.replaceAllScenes(game.menu);
                });
            } else {
                game.hello.updateLevel(i);
                game.hello.loadLevelWithOrWithoutTMX(plateform, square, i);
                createButtons(levels_b[i], [&] () {
                    game.replaceAllScenes(game.hello);
                });
            }
        }
    }

    SelectLevel::~SelectLevel() {}

    gf::WidgetContainer SelectLevel::GameLevel_getWidgets() {
        return widgets;
    }

    /*std::size_t SelectLevel::getNumberButtonsCreated() {
        return levels_b.size();
    }*/

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void SelectLevel::doHandleActions(gf::Window& window) {
        if (!window.isOpen()) return;
        if (up.isActive()) widgets.selectPreviousWidget();
        if (down.isActive()) widgets.selectNextWidget();
        if (trigger.isActive()) widgets.triggerAction();
        if (quit.isActive()) game.replaceScene(game.menu);
    }

    void SelectLevel::doProcessEvent(gf::Event& event) {
        switch(event.type) {
            case gf::EventType::MouseMoved:
                widgets.pointTo(game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
                break;
            default:
                break;
        }
    }

    void SelectLevel::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
        float size = 0.035f, space = 0.04f;
        gf::Vector2f bg_size (0.55f, 0.1f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);
        float ne = 0.0f;
        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            ne = 0.1f + (size + space)*i;
            levels_b[i].setCharacterSize(r_size);
            levels_b[i].setPosition(coords.getRelativePoint({0.275f, ne}));
            levels_b[i].setParagraphWidth(width);
            levels_b[i].setPadding(padding);
        }        
        widgets.render(target, states);

    }
    void SelectLevel::doShow() {
        widgets.clear();
        for (gf::TextButtonWidget& b : levels_b) {
            b.setDefault();
            widgets.addWidget(b);
        }
        widgets.selectNextWidget();
    }
}