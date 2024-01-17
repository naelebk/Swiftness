#include "GameLevel.h"
#include "GameCenter.h"

namespace swiftness {
    SelectLevel::SelectLevel(GameCenter& game) :
    gf::Scene(gf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)),
    game(game),
    up("Up"),
    down("Down"),
    trigger("Trigger") {}

    SelectLevel::~SelectLevel() {}

    // Méthodes virtuelles privées héritant directement de gf::Scene
    /*void handleActions(gf::Window& window) {
        if (!window.isOpen()) return;
    }
    void render(gf::RenderTarget& target, const gf::RenderStates &states) {}
    void show() {}*/
}