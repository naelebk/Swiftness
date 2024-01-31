#include "pauseScene.h"
#include "../gameCenter.h"

namespace swiftness {
    pauseScene::pauseScene(GameCenter& game, gf::Font& font, gf::ResourceManager& resources) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    game(game),
    font(font),
    up("Up"),
    background(game.resources.getTexture("command.png")),
    down("Down"),
    trigger("Trigger"),
    quit_b("Quitter", font, 100),
    back_b("Annuler", font, 100) 
    {

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
            game.replaceAllScenes(game.menu);
        });

        createButtons(back_b, [&] () {
            game.popScene();
        });

    }

    pauseScene::~pauseScene() {}

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void pauseScene::doHandleActions(gf::Window& window) {
        if (!window.isOpen()) return;
        if (up.isActive()) widgets.selectPreviousWidget();
        if (down.isActive()) widgets.selectNextWidget();
        if (trigger.isActive()) widgets.triggerAction();
    }

    void pauseScene::doProcessEvent(gf::Event& event) {
        switch(event.type) {
            case gf::EventType::MouseMoved:
                widgets.pointTo(game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
                break;
            default:
                break;
        }
    }

    void pauseScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
        gf::Coordinates coords(target);
        float backgroundHeight = coords.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
        float backgroundScale = backgroundHeight / background.getSize().height;
        target.setView(getHudView());
        float size = 0.035f, space = 0.04f;
        gf::Vector2f bg_size (0.55f, 0.1f);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);
        float ne = 0.2f;
        back_b.setCharacterSize(r_size);
        back_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        back_b.setParagraphWidth(width);
        back_b.setPadding(padding);
        ne += 0.1 + size + space;
        quit_b.setCharacterSize(r_size);
        quit_b.setPosition(coords.getRelativePoint({0.275f, ne}));
        quit_b.setParagraphWidth(width);
        quit_b.setPadding(padding);      
        widgets.render(target, states);
    }

    void pauseScene::doShow() {
        widgets.clear();
        quit_b.setDefault();
        widgets.addWidget(quit_b);
        back_b.setDefault();
        widgets.addWidget(back_b);
        widgets.selectNextWidget();
    }
}
