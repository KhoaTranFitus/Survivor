#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Config.h"

class GameObject;

class Component
{
protected:
    std::shared_ptr<GameObject> owner; // Ch? s? h?u c?a component này
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
// Th? hi?n hành vi có th? gán cho game object b?t k?
// Ví d? kh? n?ng di chuy?n gán cho Player, Enemy, ...
// Ho?c kh? n?ng ?u?i theo ng??i ch?i gán cho các lo?i Enemy khác nhau
// D? dàng thêm b?t ho?c b?t t?t, d? debug