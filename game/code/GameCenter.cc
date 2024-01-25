#include "GameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::ResourceManager& resources, gf::Font& font)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    menu(*this),
    font(font),
    level(*this, font, resources) 
    {
        pushScene(menu);
    }
}