#include "GameScenes.h"
#include "GameCenter.h"
#include <gf/Coordinates.h>
#include <cstdlib>

namespace swiftness {
    GameScenes::GameScenes(GameCenter& game) 
        : gf::Scene(game.getRenderer().getSize()),
        game(game),
        up("Up"),
        down("Down"),
        trigger("Trigger"),
        questionmark("???"),
        quit_a("Quit"),
        font(PATH_FONT),
        quit_b("Quit", font),
        credits("Credits", font),
        choose_level("Choose level", font),
        questionmark_b("???", font)
        {
            setClearColor(gf::Color::Black);
            // Première action correspondant à un bouton : quitter le jeu
            quit_a.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
            quit_a.addKeycodeKeyControl(gf::Keycode::Escape);
            addAction(quit_a);

            // Seconde action permettant d'aller en haut
            up.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
            up.addScancodeKeyControl(gf::Scancode::Up);
            up.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
            addAction(up);

            // Troisième action permattant d'aller en bas
            down.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
            down.addScancodeKeyControl(gf::Scancode::Down);
            down.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
            addAction(down);

            // Quatrième action permettant d'effectuer un choix
            // (touche A du Gamepad, ou bien touche entrée, ou bien cliquer directement sur le bouton)
            trigger.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
            trigger.addScancodeKeyControl(gf::Scancode::Return);
            trigger.addMouseButtonControl(gf::MouseButton::Left);
            addAction(trigger);

            // ????????????????????????????????????????????????????????????????????????
            // Mystère cette action, que fait-elle ?
            questionmark.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::X);
            trigger.addKeycodeKeyControl(gf::Keycode::Y);
            addAction(questionmark);

            // Création des boutons nous permettant d'effectuer les différentes actions
            // Tout d'abord, il faut gérer leur création avant de leur assigner leurs valeurs
            // ainsi que leurs actions
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

            // Maintenant le gestionnaire de création de boutons initialisé, on peut créer nos boutons
            createButtons(quit_b, [&] () {
                game.popAllScenes();
            });

            /*createButtons(credits, [&] () {
                game.replaceAllScenes(game.level);
            });*/

            createButtons(choose_level, [&] () {
                game.replaceAllScenes(game.level);
            });

            createButtons(questionmark_b, [&] () {
                system("gio open https://www.youtube.com/watch?v=xvFZjo5PgG0 > /dev/null 2>&1");
            });

        }

    GameScenes::~GameScenes() {}

    gf::WidgetContainer GameScenes::GameScenes_getWidgets() {
        return widgets;
    }

    // Méthodes virtuelles privées héritant directement de gf::Scene
    // Méthodes virtuelles privées héritant directement de gf::Scene
    void GameScenes::doHandleActions([[maybe_unused]] gf::Window& window) {
        if (!isActive()) return;
        if (up.isActive()) widgets.selectPreviousWidget();
        if (down.isActive()) widgets.selectNextWidget();
        if (trigger.isActive()) widgets.triggerAction();
        if (quit_a.isActive()) game.popAllScenes();
    }

    void GameScenes::doProcessEvent(gf::Event& event) {
        switch(event.type) {
            case gf::EventType::MouseMoved:
                widgets.pointTo(game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
                break;
            default:
                break;
        }
    }

    void GameScenes::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
        float size = 0.05f, space = 0.2f;
        gf::Vector2f bg_size (0.55f, 0.4f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);

        quit_b.setCharacterSize(r_size);
        quit_b.setPosition(coords.getRelativePoint({0.275f, 0.425f}));
        quit_b.setParagraphWidth(width);
        quit_b.setPadding(padding);

        credits.setCharacterSize(r_size);
        credits.setPosition(coords.getRelativePoint({0.275f, 0.425f + size - space}));
        credits.setParagraphWidth(width);
        credits.setPadding(padding);

        choose_level.setCharacterSize(r_size);
        choose_level.setPosition(coords.getRelativePoint({0.275f, (0.425f + size - space)*2}));
        choose_level.setParagraphWidth(width);
        choose_level.setPadding(padding);

        questionmark_b.setCharacterSize(r_size);
        questionmark_b.setPosition(coords.getRelativePoint({0.275f, (0.425f + size - space)*3}));
        questionmark_b.setParagraphWidth(width);
        questionmark_b.setPadding(padding);

        widgets.render(target, states);

    }
    void GameScenes::doShow() {
        widgets.clear();

        quit_b.setDefault();
        widgets.addWidget(quit_b);

        credits.setDefault();
        //widgets.addWidget(credits);

        choose_level.setDefault();
        widgets.addWidget(choose_level);

        questionmark_b.setDefault();
        widgets.addWidget(questionmark_b);
        
        widgets.selectNextWidget();
    }

}
