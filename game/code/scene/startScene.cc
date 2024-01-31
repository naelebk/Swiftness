#include "startScene.h"
#include "../gameCenter.h"
#include <gf/Easings.h>
#include <gf/Time.h>
#include <gf/SceneManager.h>
#include <gf/Coordinates.h>
#include <cstdlib>
#include <gf/Sprite.h>

namespace swiftness {
    StartScene::StartScene(GameCenter& game) :
    gf::Scene(game.getRenderer().getSize()),
    game(game),
    background(game.resources.getTexture("command.png")),
    menu("menu")
    {
        setClearColor(gf::Color::Black);

        menu.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::DPadUp);
        menu.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
        menu.addScancodeKeyControl(gf::Scancode::Up);
        menu.addScancodeKeyControl(gf::Scancode::W);
        menu.addScancodeKeyControl(gf::Scancode::Space);
        menu.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
        addAction(menu);
    }

    StartScene::~StartScene() {}

    void StartScene::doHandleActions(gf::Window& window) {
        if (!isActive()) return;
        if (menu.isActive()) game.replaceAllScenes(game.menu);
    }
    void StartScene::doRender (gf::RenderTarget& target, const gf::RenderStates &states) {
        gf::Coordinates coords(target);
        float backgroundHeight = coords.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
        float backgroundScale = backgroundHeight / background.getSize().height;
        gf::Sprite M_background(background);
        M_background.setPosition(coords.getCenter());
        M_background.setAnchor(gf::Anchor::Center);
        M_background.setScale(backgroundScale);
        target.draw(M_background, states);
    }
}
