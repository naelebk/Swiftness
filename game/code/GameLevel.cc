#include "GameLevel.h"
#include "GameCenter.h"
#include <gf/Coordinates.h>

namespace swiftness {
    SelectLevel::SelectLevel(GameCenter& game, gf::Font& font) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    font(font),
    game(game),
    up("Up"),
    down("Down"),
    trigger("Trigger"),
    quit("Quit"),
    level0_b("Level 0", font, 30),
    level1_b("Level 1", font, 30),
    level2_b("Level 2", font, 30),
    level3_b("Level 3", font, 30),
    level4_b("Level 4", font, 30),
    level5_b("Level 5", font, 30),
    level6_b("Level 6", font, 30),
    level7_b("Level 7", font, 30),
    quit_b("Quit", font, 30)
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
        createButtons(quit_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level0_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level1_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level2_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level3_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level4_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level5_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level6_b, [&] () {
            game.popAllScenes();
        });
        createButtons(level7_b, [&] () {
            game.popAllScenes();
        });
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
        float size = 0.05f, space = 0.05f;
        gf::Vector2f bg_size (0.55f, 0.2f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);
        float ne = 0.0f;
        ne = 0.1f + (size + space)*0;
        level0_b.setCharacterSize(r_size);
        level0_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level0_b.setParagraphWidth(width);
        level0_b.setPadding(padding);
        ne = 0.1f + (size + space)*1;
        level1_b.setCharacterSize(r_size);
        level1_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level1_b.setParagraphWidth(width);
        level1_b.setPadding(padding);
        ne = 0.1f + (size + space)*2;
        level2_b.setCharacterSize(r_size);
        level2_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level2_b.setParagraphWidth(width);
        level2_b.setPadding(padding);
        ne = 0.1f + (size + space)*3;
        level3_b.setCharacterSize(r_size);
        level3_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level3_b.setParagraphWidth(width);
        level3_b.setPadding(padding);
        ne = 0.1f + (size + space)*4;
        level4_b.setCharacterSize(r_size);
        level4_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level4_b.setParagraphWidth(width);
        level4_b.setPadding(padding);
        ne = 0.1f + (size + space)*5;
        level5_b.setCharacterSize(r_size);
        level5_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level5_b.setParagraphWidth(width);
        level5_b.setPadding(padding);
        ne = 0.1f + (size + space)*6;
        level6_b.setCharacterSize(r_size);
        level6_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level6_b.setParagraphWidth(width);
        level6_b.setPadding(padding);
        ne = 0.1f + (size + space)*7;
        level7_b.setCharacterSize(r_size);
        level7_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        level7_b.setParagraphWidth(width);
        level7_b.setPadding(padding);
        ne = 0.1f + (size + space)*8;
        quit_b.setCharacterSize(r_size);
        quit_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        quit_b.setParagraphWidth(width);
        quit_b.setPadding(padding);
        
        widgets.render(target, states);

    }
    void SelectLevel::doShow() {
        widgets.clear();
        level0_b.setDefault();
        widgets.addWidget(level0_b);
        level1_b.setDefault();
        widgets.addWidget(level1_b);
        level2_b.setDefault();
        widgets.addWidget(level2_b);
        level3_b.setDefault();
        widgets.addWidget(level3_b);
        level4_b.setDefault();
        widgets.addWidget(level4_b);
        level5_b.setDefault();
        widgets.addWidget(level5_b);
        level6_b.setDefault();
        widgets.addWidget(level6_b);
        level7_b.setDefault();
        widgets.addWidget(level7_b);
        quit_b.setDefault();
        widgets.addWidget(quit_b);
        widgets.selectNextWidget();
    }
}