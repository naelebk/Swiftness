#pragma once
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

#include "constants.h"

namespace swiftness
{
    class AudioManager
    {
    public:
        AudioManager();

        sf::Music& getMainTheme() { return mainTheme; };

        sf::Music& getLevelTheme() { return levelTheme; };

        sf::Sound& getJumpSound() { return jumpSound; };

        sf::Sound& getNotifSound() { return notifSound; };

    private:
        sf::Music mainTheme;
        sf::Music levelTheme;
        sf::Sound jumpSound;
        sf::Sound notifSound;

    };
};
#endif // AUDIO_MANAGER_H