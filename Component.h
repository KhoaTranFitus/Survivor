#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Config.h"

class GameObject;

class Component
{
protected:
    std::shared_ptr<GameObject> owner; // Ch? s? h?u c?a component n�y
public:
    Component(std::shared_ptr<GameObject> owner) : owner(owner) {}
    Component() = default;
    virtual ~Component() = default;

    void setOwner(std::shared_ptr<GameObject> newOwner);
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) {}
    virtual void onCollisionEnter(std::shared_ptr<GameObject> other) {}

};

// Component Pattern for game objects' behavior
// Th? hi?n h�nh vi c� th? g�n cho game object b?t k?
// V� d? kh? n?ng di chuy?n g�n cho Player, Enemy, ...
// Ho?c kh? n?ng ?u?i theo ng??i ch?i g�n cho c�c lo?i Enemy kh�c nhau
// D? d�ng th�m b?t ho?c b?t t?t, d? debug