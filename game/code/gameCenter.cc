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
    , audioManager()
    , mainTheme(audioManager.getMainTheme())
    , levelTheme(audioManager.getLevelTheme())
    , jumpSound(audioManager.getJumpSound())
    , notifSound(audioManager.getNotifSound())
    {
        mainTheme.setLoop(true);
        mainTheme.play();
        pushScene(start);
    }
}