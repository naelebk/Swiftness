#include "GameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::Font& font, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square, std::vector<Input>& enumVector, gf::Vector2f& camera)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    level(*this, font, plateform, square, camera), 
    menu(*this),
    levels(*this, font, 0, plateform, square, enumVector, camera)
    {
        pushScene(menu);
    }
}