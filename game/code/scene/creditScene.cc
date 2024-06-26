#include "creditScene.h"
#include "../gameCenter.h"

namespace swiftness {
    CreditScene::CreditScene(GameCenter& game, gf::Font& font) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    font(font),
    game(game),
    mainmenu("Main Menu", font, 60),
    trigger("Trigger"),
    quit("Quit")
    {

        setClearColor(gf::Color::Black);

        quit.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
        quit.addKeycodeKeyControl(gf::Keycode::Escape);
        addAction(quit);

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
        createButtons(mainmenu, [&] () {
            game.replaceAllScenes(game.menu, trans, gf::milliseconds(500));
        });
    }

    CreditScene::~CreditScene() {}

    // Méthodes virtuelles privées héritant directement de gf::Scene
    void CreditScene::doHandleActions(gf::Window& window) {
        if (!window.isOpen()) return;
        if (trigger.isActive()) widgets.triggerAction();
        if (quit.isActive()) game.replaceScene(game.menu);
    }

    void CreditScene::doProcessEvent(gf::Event& event) {
        switch(event.type) {
            case gf::EventType::MouseMoved:
                widgets.pointTo(game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
                break;
            default:
                break;
        }
    }

    void CreditScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
        float size = 0.035f, space = 0.04f;
        gf::Vector2f bg_size (0.55f, 0.1f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);
        gf::Text developper("", font, 55);
        developper.setParagraphWidth(100.0f);
        /* crédits :
        - section "developpement C++ (Nael embarki, Théo humbert, Julien gauthier)"
        - section "developpement shell (Nael embarki)" ?
        - section "developpement python (Julien gauthier)" ?
        - section "référent (Julien bernard/jube)"
        - section "graphiste (Julien gauthier, Milo gauthier)"
        - section "musique (Julien gauthier)"
        - section "logo à mettre (gf, sfml)"
        */
        developper.setString("Developpers\n EMBARKI Naël\n GAUTHIER Julien\n HUMBERT Théo\nSpecials skins\n GAUTHIER Milo\nReferent\n M. Julien BERNARD\n(aka jube)");
        developper.setColor(gf::Color::Yellow);
        developper.setPosition(coords.getRelativePoint({0.5f, 0.4f}));
        developper.setAnchor(gf::Anchor::Center);
        target.draw(developper, states);
        mainmenu.setCharacterSize(r_size);
        mainmenu.setPosition(coords.getRelativePoint({0.275f, 0.85f}));
        mainmenu.setParagraphWidth(width);
        mainmenu.setPadding(padding);      
        widgets.render(target, states);
    }

    void CreditScene::doShow() {
        widgets.clear();
        mainmenu.setDefault();
        widgets.addWidget(mainmenu);
        widgets.selectNextWidget();
    }
}
