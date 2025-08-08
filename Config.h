#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define INT(enumValue) static_cast<int>(enumValue)

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
const float BULLET_VELOCITY = 800.f;

const float ENEMY_SPEED = 200.f;

enum class PLAYER_STATE {
    IDLE = 0,
    RUN = 1,
	FIRE = 2,
    HURT  = 3,
    DIE = 4,
};

enum class ENEMY_STATE {
    RUN = 0,
};