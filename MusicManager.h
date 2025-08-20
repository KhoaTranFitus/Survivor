#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include "Config.h"
class MusicManager {
public:
    static MusicManager& getInstance() {
        static MusicManager instance;
        return instance;
    }

    void play(const std::string& path, bool loop = true);

    void setVolume(float volume);
    float getVolume() const;
    bool isPlaying() const;
    void stop();
private:
    MusicManager() = default;
    sf::Music music;
    std::string currentPath;
    float musicVolume = 30.f;
};