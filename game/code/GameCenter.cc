#include "GameCenter.h"

namespace swiftness {
    // Héritage de gf::Scene, on peut utiliser *this pour instancier
    GameCenter::GameCenter()
    : GameManager("Swiftness", {RESSOURCES_PATH}), level(*this){}
}