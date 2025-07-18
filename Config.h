#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

template <typename T, typename U>
bool isType(const std::shared_ptr<U>& ptr)
{
    if (!ptr) return false;
    return typeid(*ptr) == typeid(T);
}
template <typename T, typename U>
bool isDerivedFrom(const std::shared_ptr<U>& ptr)
{
    return std::dynamic_pointer_cast<T>(ptr) != nullptr;
}

extern sf::Vector2f mousePosition;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const float PLAYER_SPEED = 400.f;