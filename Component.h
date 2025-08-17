#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Config.h"

class GameObject;

class Component
{
protected:
	std::shared_ptr<GameObject> owner; // chủ sở hữu của component
public:
    Component(std::shared_ptr<GameObject> owner) : owner(owner) {}
    Component() = default;
    virtual ~Component() = default;

    void setOwner(std::shared_ptr<GameObject> newOwner);
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) {}
    virtual void onCollisionEnter(std::shared_ptr<GameObject> other) {}

};