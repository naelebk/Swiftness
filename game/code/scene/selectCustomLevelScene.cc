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

        trigger.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
        trigger.addScancodeKeyControl(gf::Scancode::Return);
        trigger.addScancodeKeyControl(gf::Scancode::Space);
        trigger.addMouseButtonControl(gf::MouseButton::Left);
        addAction(trigger);

        auto createButtons = [&](gf::TextButtonWidget &button, auto callback, float padding, gf::Vector2f pos)
        {
            button.setDefaultTextColor(gf::Color::Black);
            button.setDefaultBackgroundColor(gf::Color::Gray(0.7f));
            button.setSelectedTextColor(gf::Color::Black);
            button.setSelectedBackgroundColor(gf::Color::Green);
            button.setDisabledTextColor(gf::Color::Black);
            button.setDisabledBackgroundColor(gf::Color::Red);
            button.setAnchor(gf::Anchor::Center);
            button.setPosition(pos); // pour la position du bouton
            button.setPadding(padding); // pour la taille du bouton
            button.setCallback(callback);
            widgets.addWidget(button);
        };

        auto calculateXPos = [&](int i, int max)
        {
            return 550.0f + (i - 1) * 500.0f / (max - 1);
        };


        float verticalPadding = 50.0f;
        float buttonHeight = 150.0f;
        float totalContentHeight = buttonHeight * 3 + verticalPadding * 2;
        float startHeight = (WINDOW_HEIGHT - totalContentHeight) / 2;
        float yPos = startHeight + buttonHeight + verticalPadding;

        yPos += buttonHeight + verticalPadding;

        createButtons(levels_b[MAX_CUSTOM_LEVEL], [&] () { 
            game.replaceAllScenes(game.menu, trans, gf::milliseconds(500)); },
            5.0f, {800.0f, yPos});

        yPos -= buttonHeight + verticalPadding;    

        createButtons(
            levels_b[0], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level01, pixel, gf::milliseconds(500)); },
            5.0f, {calculateXPos(1, 5), yPos});

        createButtons(
            levels_b[1], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level02, pixel, gf::milliseconds(500)); },
            5.0f, {calculateXPos(2, 5), yPos});

        createButtons(
            levels_b[2], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level03, pixel, gf::milliseconds(500)); },
            5.0f, {calculateXPos(3, 5), yPos});

        createButtons(
            levels_b[3], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level04, pixel, gf::milliseconds(500)); },
            5.0f, {calculateXPos(4, 5), yPos});

        createButtons(
            levels_b[4], [&]()
            {
            game.mainTheme.stop();
            game.levelTheme.play();
            game.replaceAllScenes(level05, pixel, gf::milliseconds(500)); },
            5.0f, {calculateXPos(5, 5), yPos});    

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
