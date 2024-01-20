#include "GameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::Font& font, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    level(*this, font, plateform, square), 
    menu(*this),
    hello(*this, font, -1, plateform, square)
    {
        pushScene(menu);
    }
}