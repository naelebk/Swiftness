#include "GameCenter.h"

namespace swiftness {
    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::Font& font)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    level(*this), 
    menu(*this),
    helloWorld(*this, font) {
        pushScene(menu);
    }
}