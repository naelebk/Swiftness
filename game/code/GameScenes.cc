#include "GameScenes.h"
#include "GameCenter.h"

namespace swiftness {
    GameScenes::GameScenes(GameCenter& game) 
        : gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
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
            addAction(up);

            // Troisième action permattant d'aller en bas
            down.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadDown);
            down.addScancodeKeyControl(gf::Scancode::Down);
            addAction(down);

            // Quatrième action permettant d'effectuer un choix
            // (touche A du Gamepad, ou bien touche entrée, ou bien cliquer directement sur le bouton)
            trigger.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
            trigger.addScancodeKeyControl(gf::Scancode::Return);
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

            createButtons(credits, [&] () {
                game.replaceAllScenes(game.level);
            });

            createButtons(choose_level, [&] () {
                game.replaceAllScenes(game.level);
            });

            createButtons(questionmark_b, [&] () {
                game.replaceAllScenes(game.level);
            });

        }

    GameScenes::~GameScenes() {}

    gf::WidgetContainer GameScenes::GameScenes_getWidgets() {
        return widgets;
    }

    // Méthodes virtuelles privées héritant directement de gf::Scene
    // Méthodes virtuelles privées héritant directement de gf::Scene
    void GameScenes::GameScenes_HandleActions(gf::Window& window) {
        /*if (!window.isOpen()) return;
        if (up.isActive()) widgets.selectPreviousWidget();
        if (down.isActive()) widgets.selectNextWidget();
        if (trigger.isActive()) widgets.triggerAction();
        if (quit.isActive()) game.replaceScene(game.menu);*/
    }
    void GameScenes::GameScenes_Render(gf::RenderTarget& target, const gf::RenderStates &states) {
        /*float size = 0.08f, space = 0.025f;
        gf::Vector2f bg_size (0.55f, 0.4f); 
        target.setView(getHudView());
        gf::Coordinates coords(target);
        float width = coords.getRelativeSize(bg_size - 0.05f).x, padding = coords.getRelativeSize({0.01f, 0.f}).x;
        int r_size = coords.getRelativeCharacterSize(size);

        for (int i = 0 ; i < MAX_LEVEL + 2 ; ++i) {
            levels_b[i].setCharacterSize(r_size);
            levels_b[i].setPosition(coords.getRelativePoint({0.275f, 0.425f}));
            levels_b[i].setParagraphWidth(width);
            levels_b[i].setPadding(padding);
        }
        widgets.render(target, states);*/

    }
    void GameScenes::GameScenes_Show() {
        /*widgets.clear();
        for (gf::TextButtonWidget b : levels_b) {
            b.setDefault();
            widgets.addWidget(b);
        }
        widgets.selectNextWidget();*/
    }

}
