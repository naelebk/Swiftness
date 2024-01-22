#include "GameCenter.h"

namespace swiftness {

    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter(gf::Font& font, std::map<int, swiftness::StaticPlateform>& plateform, swiftness::Square& square, std::vector<Input>& enumVector)
    : GameManager("Swiftness", {RESSOURCES_PATH}), 
    level(*this, font, plateform, square), 
    menu(*this),
    helloWorld(*this, font, 0, plateform, square, enumVector)
    {
        pushScene(menu);
    }
}