#include <iostream>
#include "Boss.h"

Boss::Boss() : Enemies() {
    hitbox.setSize(sf::Vector2f(120.f, 120.f));
    hitbox.setFillColor(sf::Color(255, 128, 0));
}
