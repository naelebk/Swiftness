#include "GameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::Font& font)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    level(*this, font), 
    menu(*this)
    {
        /*for (int i = 0 ; i <= 0 ; ++i) {
            helloWorld.emplace_back(*this, font, i);
        }*/
        pushScene(menu);
    }
}