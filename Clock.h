#pragma once

#include "GameObject.h"
#include <SFML/System/Clock.hpp>

class Clock : public GameObject
{
public:
    Clock();
    void reset();
    float getElapsedSeconds() const;
    void pause();
    void resume();
    bool isPaused() const;
private:
    sf::Clock clockInGame;
    float elapsedBeforePause = 0.f;
    bool paused = false;
};