#pragma once
#include <SFML/Audio.hpp>
#include <string>

class MusicManager {
public:
    static MusicManager& getInstance() {
        static MusicManager instance;
        return instance;
    }

    void play(const std::string& path, float volume = 100.f, bool loop = true) {
        if (currentPath != path) {
            if (!music.openFromFile(path)) return;
            currentPath = path;
        }
        music.setVolume(volume);
        music.setLoop(loop);
        if (music.getStatus() != sf::Music::Playing)
            music.play();
    }

    void setVolume(float volume) { music.setVolume(volume); }
    float getVolume() const { return music.getVolume(); }
    bool isPlaying() const { return music.getStatus() == sf::Music::Playing; }
    void stop() { music.stop(); }

private:
    MusicManager() = default;
    sf::Music music;
    std::string currentPath;
};