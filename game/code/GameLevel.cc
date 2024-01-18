#include "GameLevel.h"
#include "GameCenter.h"

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

        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            gf::Font font(PATH_FONT);
            gf::TextButtonWidget button("Quit", font, 30.0f);
            if (i < MAX_LEVEL + 1) {
                gf::TextButtonWidget button("Level " + std::to_string(i), font, 30.0f);
            }
            auto callback = [&, i] {
                gf::Log::debug("A button was pressed !\n");
            };
            createButtons(button, callback);
            levels_b.push_back(button);
        }
    }

    SelectLevel::~SelectLevel() {}

    gf::WidgetContainer SelectLevel::GameLevel_getWidgets() {
        return widgets;
    }

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void SelectLevel::GameLevel_HandleActions(gf::Window& window) {
        if (!window.isOpen()) return;
        if (up.isActive()) widgets.selectPreviousWidget();
        if (down.isActive()) widgets.selectNextWidget();
        if (trigger.isActive()) widgets.triggerAction();
        if (quit.isActive()) game.replaceScene(game.menu);
    }
    void SelectLevel::GameLevel_Render(gf::RenderTarget& target, const gf::RenderStates &states) {}
    void SelectLevel::GameLevel_Show() {}
}