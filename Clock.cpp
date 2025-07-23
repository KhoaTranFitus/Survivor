#include "Clock.h"

Clock::Clock() {
    clockInGame.restart();
    elapsedBeforePause = 0.f;
    paused = false;
}

void Clock::reset() {
    clockInGame.restart();
    elapsedBeforePause = 0.f;
    paused = false;
}

float Clock::getElapsedSeconds() const {
    if (paused)
        return elapsedBeforePause;
    return elapsedBeforePause + clockInGame.getElapsedTime().asSeconds();
}

void Clock::pause() {
    if (!paused) {
        elapsedBeforePause += clockInGame.getElapsedTime().asSeconds();
        paused = true;
    }
}

void Clock::resume() {
    if (paused) {
        clockInGame.restart();
        paused = false;
    }
}

bool Clock::isPaused() const {
    return paused;
}