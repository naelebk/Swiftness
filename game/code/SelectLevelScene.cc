#include "SelectLevelScene.h"
#include "GameCenter.h"
#include <gf/Coordinates.h>
#include "levelScene.h"

namespace swiftness {
    SelectLevel::SelectLevel(GameCenter& game, gf::Font& font, gf::ResourceManager& resources) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    font(font),
    game(game),
    up("Up"),
    down("Down"),
    trigger("Trigger"),
    quit("Quit"),
    level00(game, font, resources, 0),
    level01(game, font, resources, 1),
    level02(game, font, resources, 2),
    level03(game, font, resources, 3),
    level04(game, font, resources, 4),
    level05(game, font, resources, 5),
    level06(game, font, resources, 6),
    level07(game, font, resources, 7)
    {
        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            if (i >= 1 && i < MAX_LEVEL + 1) {
                levels_b.emplace_back("Level " + std::to_string(i), font, 60);
            } else if (i == 0) {
                levels_b.emplace_back("Tutorial", font, 60);
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
        createButtons(levels_b[MAX_LEVEL + 1], [&] () {
            game.replaceAllScenes(level00);
        });

        createButtons(levels_b[0], [&] () {
            level00.loadLevel(level00.getPlateforms(), level00.getSquare(), 0);
            game.replaceAllScenes(level00);
            
        });

        createButtons(levels_b[1], [&] () {
            level01.loadLevel(level01.getPlateforms(), level01.getSquare(), 1);
            game.replaceAllScenes(level01);
        });

        createButtons(levels_b[2], [&] () {
            level02.loadLevel(level02.getPlateforms(), level02.getSquare(), 2);
            game.replaceAllScenes(level02);
        });

        createButtons(levels_b[3], [&] () {
            level03.loadLevel(level03.getPlateforms(), level03.getSquare(), 3);
            game.replaceAllScenes(level03);
        });

        createButtons(levels_b[4], [&] () {
            level04.loadLevel(level04.getPlateforms(), level04.getSquare(), 4);
            game.replaceAllScenes(level04);
        });

        createButtons(levels_b[5], [&] () {
            level05.loadLevel(level05.getPlateforms(), level05.getSquare(), 5);
            game.replaceAllScenes(level05);
        });

        createButtons(levels_b[6], [&] () {
            level06.loadLevel(level06.getPlateforms(), level06.getSquare(), 6);
            game.replaceAllScenes(level06);
        });

        createButtons(levels_b[7], [&] () {
            level07.loadLevel(level07.getPlateforms(), level07.getSquare(), 7);
            game.replaceAllScenes(level07);
        });

        /*createButtons(levels_b[8], [&] () {
            game.replaceAllScenes(level08);
        });

        createButtons(levels_b[9], [&] () {
            game.replaceAllScenes(level09);
        });

        createButtons(levels_b[10], [&] () {
            game.replaceAllScenes(level10);
        });*/


    }

    SelectLevel::~SelectLevel() {}

    gf::WidgetContainer SelectLevel::GameLevel_getWidgets() {
        return widgets;
    }

    std::string getLevelNameByButton(gf::TextButtonWidget& button) {
        std::string buttonName = button.getString();
        if (buttonName == "Tutorial") {
            return "level00.tmx";
        }
        return buttonName + ".tmx";
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