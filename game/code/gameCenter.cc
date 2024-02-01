#include "gameCenter.h"

namespace swiftness {

    GameCenter::GameCenter(gf::Font& font)
    : GameManager("Swiftness", {RESSOURCES_PATH}) 
    , menu(*this)
    , start(*this)
    , font(font)
    , credits(*this, font)
    , level(*this, font)
    , s_pause(*this, font) 
    {
        pushScene(start);
    }
}