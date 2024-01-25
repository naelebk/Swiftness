#include "GameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::ResourceManager resources)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    menu(*this),
    font(resources.getFont(PATH_FONT)),
    level(*this, font, resources) 
    {
        pushScene(menu);
    }
}