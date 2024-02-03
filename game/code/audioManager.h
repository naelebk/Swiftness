#pragma once
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

namespace swiftness
{
    class AudioManager
    {
    public:
        AudioManager();

        void playMusic(const std::string &filename);

    private:
        sf::Music music;
    };
};
#endif // AUDIO_MANAGER_H