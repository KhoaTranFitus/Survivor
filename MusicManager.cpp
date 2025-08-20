#include "MusicManager.h"

void MusicManager::play(const std::string& path, bool loop)
{
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

void MusicManager::setVolume(float volume)
{
    musicVolume = volume;
    music.setVolume(musicVolume);
}

float MusicManager::getVolume() const
{
    return music.getVolume();
}

bool MusicManager::isPlaying() const
{
    return music.getStatus() == sf::Music::Playing;
}

void MusicManager::stop()
{
    music.stop();
}
