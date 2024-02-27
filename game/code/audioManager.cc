#include "audioManager.h"

namespace swiftness
{

    AudioManager::AudioManager()
    : mainTheme()
    , levelTheme()
    , konami()
    , jumpSound()
    , notifSound()
    {
        mainTheme.openFromFile(MAIN_THEME);
        mainTheme.setLoop(true);
        levelTheme.openFromFile(LEVEL_THEME);
        levelTheme.setLoop(true);
        konami.openFromFile(KONAMI_THEME);
        konami.setLoop(true);
        sf::SoundBuffer jumpBuffer;
        jumpBuffer.loadFromFile(JUMP_SOUND);
        jumpSound.setBuffer(jumpBuffer);
        sf::SoundBuffer notifBuffer;
        notifBuffer.loadFromFile(NOTIF_SOUND);
        notifSound.setBuffer(notifBuffer);
    }
} // namespace swiftness