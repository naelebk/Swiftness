#include "audioManager.h"

namespace swiftness
{
    AudioManager::AudioManager()
    : music()
    {
        music.openFromFile("../../ressources/music/mellow-synth-key-melody_140bpm_C_major.wav");
        music.setLoop(true);
        music.setVolume(50);
        music.play();
    }
} // namespace swiftness