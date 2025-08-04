#pragma once
#include "Component.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Speed : public Component
{
    float multiplier;
    float duration;
    float timer = 0.f;
    float originalSpeed = 0.f;

public:
    Speed(std::shared_ptr<GameObject> owner, float multiplier, float duration);

    void onCollisionEnter(std::shared_ptr<GameObject> other) override {}
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    float getTimer() const { return timer; }
    float getDuration() const { return duration; }
};

