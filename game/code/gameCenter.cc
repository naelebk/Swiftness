#include "gameCenter.h"

namespace swiftness {

    GameCenter::GameCenter(gf::Font& font)
    : GameManager("Swiftness", PATHS)
    , menu(*this)
    , start(*this)
    , font(font)
    , credits(*this, font)
    , level(*this, font)
    , custom(*this, font)
    , audioManager()
    , mainTheme(audioManager.getMainTheme())
    , levelTheme(audioManager.getLevelTheme())
    , jumpSound(audioManager.getJumpSound())
    , notifSound(audioManager.getNotifSound())
    , Konami(audioManager.getKonamiTheme())
    {
        mainTheme.setLoop(true);
        mainTheme.play();
        pushScene(start);
    }
}