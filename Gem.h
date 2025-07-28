#pragma once
#include "GameObject.h"

class Gem : public GameObject {
public:
    Gem(sf::Vector2f position, const std::string& tag = "gem") {
        hitbox.setSize(sf::Vector2f(15.f, 15.f));
        hitbox.setFillColor(sf::Color::Yellow);
        hitbox.setPosition(position);
        setTag(tag);
    }
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
};
