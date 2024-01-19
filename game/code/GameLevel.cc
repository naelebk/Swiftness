#include "GameLevel.h"
#include "GameCenter.h"
#include <gf/Coordinates.h>

namespace swiftness {
    SelectLevel::SelectLevel(GameCenter& game) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    game(game),
    up("Up"),
    down("Down"),
    trigger("Trigger"),
    quit("Quit")
    {
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
        levels_b.reserve(MAX_LEVEL + 2);
        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            gf::Font font(PATH_FONT);
            if (i < MAX_LEVEL + 1) {
                gf::TextButtonWidget button("Level " + std::to_string(i), font, 30.0f);
                createButtons(button, [&] () {
                    game.popAllScenes();
                });
                levels_b.push_back(button);
            } else {
                gf::TextButtonWidget button("Quit", font, 30.0f);
                createButtons(button, [&] () {
                    game.popAllScenes();
                });
                levels_b.push_back(button);
            }
        }
    }

    SelectLevel::~SelectLevel() {}

    gf::WidgetContainer SelectLevel::GameLevel_getWidgets() {
        return widgets;
    }

    std::size_t SelectLevel::getNumberButtonsCreated() {
        return levels_b.size();
    }

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
        float size = 0.05f, space = 0.3f;
        gf::Vector2f bg_size (0.55f, 0.4f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);
        for (std::size_t i = 0 ; i < levels_b.size() ; ++i) {
            float ne = 0.425f + (size - space)*i;
            levels_b[i].setCharacterSize(r_size);
            levels_b[i].setPosition(coords.getRelativePoint({0.275f, ne}));
            levels_b[i].setParagraphWidth(width);
            levels_b[i].setPadding(padding);
        }
        widgets.render(target, states);

    }
    void SelectLevel::doShow() {
        widgets.clear();
        for (std::size_t i = 0 ; i < levels_b.size() ; ++i) {
            levels_b[i].setDefault();
            widgets.addWidget(levels_b[i]);
        }
        widgets.selectNextWidget();
    }
}