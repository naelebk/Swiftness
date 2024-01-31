#include "gameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::ResourceManager& resources, gf::Font& font)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    menu(*this),
    start(*this),
    font(font),
    credits(*this, font),
    level(*this, font, resources),
    s_pause(*this, font, resources) 
    {
        pushScene(start);
    }
}