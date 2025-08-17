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

    void play(const std::string& path, bool loop = true) {
        if (currentPath != path) {
            if (!music.openFromFile(path)) return;
            currentPath = path;
        }
        music.setVolume(musicVolume);

        music.setLoop(loop);
        if (music.getStatus() == sf::Music::Playing)
            music.stop();
		music.play();
    }

    void setVolume(float volume) { 
        musicVolume = volume;
        music.setVolume(musicVolume);
    }
    float getVolume() const { return music.getVolume(); }
    bool isPlaying() const { return music.getStatus() == sf::Music::Playing; }
    void stop() { music.stop(); }
private:
    MusicManager() = default;
    sf::Music music;
    std::string currentPath;
    float musicVolume = 30.f;
};